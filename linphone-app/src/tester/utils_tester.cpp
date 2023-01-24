/*
 * Copyright (c) 2010-2023 Belledonne Communications SARL.
 *
 * This file is part of linphone-desktop
 * (see https://www.linphone.org).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "utils_tester.hpp"

#include "app/App.hpp"
#include "app/AppController.hpp"
#include "components/core/CoreManager.hpp"
#include "utils/Utils.hpp"

#include <QThread>

/*
#include <QtTest/qtest_gui.h>

#define L_QTEST_MAIN_IMPL(TestObject) \
	TESTLIB_SELFCOVERAGE_START(#TestObject) \
	QT_PREPEND_NAMESPACE(QTest::Internal::callInitMain)<TestObject>(); \
	AppController app(argc, argv); \
	TestObject tc(&app); \
	QTEST_SET_MAIN_SOURCE_PATH \
	return QTest::qExec(&tc, argc, argv);
	
#define L_QTEST_MAIN(TestObject) \
int main(int argc, char *argv[]) \
{ \
	L_QTEST_MAIN_IMPL(TestObject) \
}
L_QTEST_MAIN(UtilsTester)

//QTEST_MAIN(UtilsTester)
//#include "utilstester.moc"	// if hpp is in cpp
*/


#include <qloggingcategory.h>
#ifdef QT_QML_DEBUG
#include <QQmlDebuggingEnabler>
#endif
#include <QSurfaceFormat>
#ifdef _WIN32
#include <Windows.h>
FILE * gStream = NULL;
#endif

#include "components/core/CoreManager.hpp"
#include "utils/Utils.hpp"

#ifdef ENABLE_QT_KEYCHAIN
#include "components/vfs/VfsUtils.hpp"
#endif
#include <QQuickItem>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlProperty>

// =============================================================================

void _cleanStream(){
#ifdef _WIN32
	if(gStream) {
		fflush(stdout);
		fflush(stderr);
		fclose(gStream);
	}
#endif
}

class Test : public QThread{
public:
	Test(){
	}
	virtual void run();
};
void Test::run(){
	UtilsTester tc(nullptr);
	std::vector<std::string> arguments = {"dummy", "-maxwarnings", "0"};
	std::vector<char*> argv;
	for (const auto& arg : arguments)
		argv.push_back((char*)arg.data());
	argv.push_back(nullptr);

	QTest::qExec(&tc, argv.size() - 1, argv.data());
}
int main (int argc, char *argv[]) {
#ifdef __APPLE__
	qputenv("QT_ENABLE_GLYPH_CACHE_WORKAROUND", "1");	// On Mac, set this workaround to avoid glitches on M1, because of https://bugreports.qt.io/browse/QTBUG-89379
#elif defined _WIN32
	// log in console only if launched from console
	if (AttachConsole(ATTACH_PARENT_PROCESS)) {
		freopen_s(&gStream, "CONOUT$", "w", stdout);
		freopen_s(&gStream, "CONOUT$", "w", stderr);
	}
#endif
	
#ifdef ENABLE_QT_KEYCHAIN
	bool vfsEncrypted = VfsUtils::updateSDKWithKey();
#else
	bool vfsEncrypted = false;
#endif
	
	AppController controller(argc, argv);
#ifdef QT_QML_DEBUG
	QQmlDebuggingEnabler enabler;
#endif
	//QLoggingCategory::setFilterRules("*.debug=true;qml=false");
	App *app = controller.getApp();
	//	if(vfsEncrypted)
	//		qInfo() << "Activation of VFS encryption.";
	if (app->isSecondary())
	{
		qInfo() << QStringLiteral("Running secondary app success. Kill it now.");
		_cleanStream();
		return EXIT_SUCCESS;
	}
	
	qInfo() << QStringLiteral("Running app...");
	QThread * test;
	int ret = 0;
	do {
		app->initContentApp();
		if(ret == 0){
			test = QThread::create([](){
				UtilsTester tc(nullptr);
				std::vector<std::string> arguments = {"dummy", "-maxwarnings", "0"};
				std::vector<char*> argv;
				for (const auto& arg : arguments)
					argv.push_back((char*)arg.data());
				argv.push_back(nullptr);
			
				QTest::qExec(&tc, argv.size() - 1, argv.data());
			});
			test->start();
		}
		ret = app->exec();
	} while (ret == App::RestartCode);
	qWarning() << "Exiting app with the code : " << ret;
	controller.stopApp();	// Stopping app before core to let time to GUI to process needed items from linphone.
	if( CoreManager::getInstance()){
		auto core = CoreManager::getInstance()->getCore();
		if(core && core->getGlobalState() == linphone::GlobalState::On)
			core->stop();
	}
	_cleanStream();
	if( ret == App::DeleteDataCode){
		Utils::deleteAllUserDataOffline();
	}
	return ret;
}

void debugNames(QQuickItem * item){
	if(!item)
		return;
	auto childs = item->childItems();
	QString name = item->objectName();
	QString qmlProperty = QQmlProperty::read(item, "objectName").toString();
	const QMetaObject* metaObject = item->metaObject();
	QStringList properties;
	for(int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i)
		properties << QString::fromLatin1(metaObject->property(i).name());
		
	if(name != "" || qmlProperty != "")
		qDebug() << name << " / " << qmlProperty << " / " << childs.size() << properties;
	else{
		if(metaObject->propertyCount() > 0)
			qDebug() << properties;
	}
	for(int i = 0 ; i < childs.size() ; ++i){
		debugNames(childs.at(i));
	}
}

class ItemManager{
public:
	static void getItem(const QString& name, QQuickItem * item, QQuickItem ** found){
		if(*found || !item)
			return;
		auto childs = item->childItems();
		//QString itemName = item->objectName();	// not working on Repeater
		if(QQmlProperty::read(item, "objectName").toString() == name){
		//if(name == itemName){
			*found = item;
			return;
		}
		for(int i = 0 ; i < childs.size() ; ++i){
			ItemManager::getItem(name, childs.at(i), found);
		}
	}
	static QQuickItem * getItem(QQuickItem * parent, const QString& name){
		QQuickItem * item = nullptr;
		if(parent){
			ItemManager::getItem(name, parent, &item);
			if(!item){
				qWarning() << "not found : " << name;
				debugNames(parent);
				//debugNames(engine);
			}
		}
		return item;
	}
	static QQuickItem * getItem(const QString& name){
		auto engine = App::getInstance()->getEngine();
		QQuickItem * item = nullptr;
		auto roots = engine->rootObjects();
		for(int i = 0 ; !item && i < roots.size() ; ++i){
			QObject * object = roots[i];
			auto childs = object->children();
			for(int j = 0 ; !item && j < childs.size() ; ++j)
				ItemManager::getItem(name, qobject_cast<QQuickItem*>(childs[j]), &item);
		}
		
		if(!item){
			auto childs = App::getInstance()->getCallsWindow()->children();
			for(int j = 0 ; !item && j < childs.size() ; ++j)
				ItemManager::getItem(name, qobject_cast<QQuickItem*>(childs[j]), &item);
			//ItemManager::getItem(qobject_cast<QQuickItem*>(App::getInstance()->getCallsWindow()), name);
		}
		if(!item) {
			//qWarning() << "not found : " << name << " / " << roots.size();
			//debugNames(qobject_cast<QQuickItem*>(App::getInstance()->getCallsWindow()));
			/*
			auto roots = engine->rootObjects();
			for(int i = 0 ; !item && i < roots.size() ; ++i){
				QObject * object = roots[i];
				auto childs = object->children();
				for(int j = 0 ; j < childs.size() ; ++j)
					debugNames(qobject_cast<QQuickItem*>(childs[j]));
			}*/
		}
		return item;
		//return qobject_cast<QQuickItem*>(item);
	}
	
	
	static void clickItem( QQuickItem* pItem, QQuickWindow* pRootWindow ){
		QVERIFY(pItem != nullptr);
		auto oPointF = pItem->mapToScene( QPoint( 0, 0 ) );
		auto oPoint = oPointF.toPoint();
		oPoint.rx() += pItem->width() / 2;
		oPoint.ry() += pItem->height() / 2;
		QTest::mouseClick( pRootWindow, Qt::LeftButton, Qt::NoModifier, oPoint );
	}
	
	static void clickItem(const QString& name){
		QQuickItem * item = nullptr;
		QTRY_VERIFY_WITH_TIMEOUT( (item = ItemManager::getItem(name)) != nullptr, 5000);
		clickItem(item, App::getInstance()->getMainWindow());
		//wrapperItem = view->findChild<QQuickItem *>("__internalWrapper");
	}
	
	static void clickItem(const QString& parentName, const QString& name){
		QQuickItem * parentItem = nullptr;
		QQuickItem * item = nullptr;
		QTRY_VERIFY_WITH_TIMEOUT( (parentItem =ItemManager::getItem(parentName)) != nullptr, 5000);
		QTRY_VERIFY_WITH_TIMEOUT( (item = ItemManager::getItem(parentItem, name)) != nullptr, 5000);
		clickItem(item, App::getInstance()->getMainWindow());
		//wrapperItem = view->findChild<QQuickItem *>("__internalWrapper");
	}
	
	static void keyItem(const QString& sequence){
		for(int i = 0 ; i < sequence.size() ; ++i)
			QTest::keyClick(App::getInstance()->getMainWindow(), sequence[i].toLatin1() );
	}
};

UtilsTester::UtilsTester(AppController * controller){
	mController = controller;
	QTRY_VERIFY_WITH_TIMEOUT(CoreManager::getInstance() != nullptr, 5000);
	QTRY_VERIFY_WITH_TIMEOUT(CoreManager::getInstance()->isInitialized(), 5000);
}

UtilsTester::~UtilsTester(){
	if(App::getInstance())
		App::getInstance()->exit(0);
	delete mController;
}

void UtilsTester::initTestCase(){
	QTRY_VERIFY_WITH_TIMEOUT(CoreManager::getInstance() != nullptr, 5000);
	QTRY_VERIFY_WITH_TIMEOUT(CoreManager::getInstance()->isInitialized(), 5000);
	//App::main(1, (char**)&appPtr);
}

void UtilsTester::cleanupTestCase(){
	//App::getInstance()->exit(App::RestartCode);
	App::getInstance()->exit(0);
}

void UtilsTester::test_osProduct() {
	QString product = Utils::getOsProduct();
	QVERIFY(!product.contains(' '));
}

void UtilsTester::test_register(){
	QTRY_VERIFY_WITH_TIMEOUT(CoreManager::getInstance()->getCore()->getDefaultAccount()->getState() == linphone::RegistrationState::Ok, 10000);
}

void UtilsTester::test_call(){
	for(int i = 0 ; i < 100 ; ++i){
		ItemManager::clickItem("__mainSmartSearchBar");
		ItemManager::keyItem("julienw2@sip.linphone.org");
		ItemManager::clickItem("__ActionBar", "__audioCallButton");
		QQuickItem *item;
		QTRY_VERIFY_WITH_TIMEOUT( (item = ItemManager::getItem("__hangupCallButton")) != nullptr, 5000);
		QTest::qWait(2000);
		ItemManager::clickItem(item, App::getInstance()->getCallsWindow());
		QTest::qWait(2000);
	}
}


void UtilsTester::test_call2(){
	//for(int i = 0 ; i < 50 ; ++i){
	qWarning() << "A";
		ItemManager::clickItem("__mainSmartSearchBar");
		qWarning() << "B";
		ItemManager::keyItem("julienw2@sip.linphone.org");
		qWarning() << "C";
		ItemManager::clickItem("__ActionBar", "__audioCallButton");
		QQuickItem *item;
		QTRY_VERIFY_WITH_TIMEOUT( (item = ItemManager::getItem("__hangupCallButton")) != nullptr, 5000);
		QTest::qWait(1000);// Let 1 second and end of call
		ItemManager::clickItem("__hangupCallButton");
		QTest::qWait(2000);// Let 1 second and end of call
	//}
}