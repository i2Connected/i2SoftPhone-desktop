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

#include "NotificationsDefault.hpp"

#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QGuiApplication>
#include <QQuickWindow>
#include <QQuickItem>
#include <QQuickView>
#include <QScreen>
#include <QTimer>

#include "app/App.hpp"
#include "components/call/CallModel.hpp"
#include "components/core/CoreManager.hpp"
#include "components/timeline/TimelineModel.hpp"
#include "components/timeline/TimelineListModel.hpp"
#include "utils/Utils.hpp"


namespace {
	constexpr char NotificationsPath[] = "qrc:/ui/modules/Linphone/Notifications/";
	
	// ---------------------------------------------------------------------------
	// Notifications QML properties/methods.
	// ---------------------------------------------------------------------------
	
	constexpr char NotificationShowMethodName[] = "open";
	
	constexpr char NotificationPropertyData[] = "notificationData";
	
	constexpr char NotificationPropertyX[] = "popupX";
	constexpr char NotificationPropertyY[] = "popupY";
	
	constexpr char NotificationPropertyWindow[] = "__internalWindow";
	
	constexpr char NotificationPropertyTimer[] = "__timer";
	
	// ---------------------------------------------------------------------------
	// Arbitrary hardcoded values.
	// ---------------------------------------------------------------------------
	
	constexpr int NotificationSpacing = 10;
	constexpr int MaxNotificationsNumber = 5;
}

QHash<QString,int> NotificationsDefault::gScreenHeightOffset;

template<class T>
void setProperty (QObject &object, const char *property, const T &value) {
	if (!object.setProperty(property, QVariant(value))) {
		qWarning() << QStringLiteral("Unable to set property: `%1`.").arg(property);
		abort();
	}
}

NotificationsDefault::NotificationsDefault (QObject *parent){

}

QObject *NotificationsDefault::create(Notifier::NotificationType type, QVariantMap data){
	QQuickItem *wrapperItem = nullptr;

	QList<QScreen *> allScreens = QGuiApplication::screens();
	if(allScreens.size() > 0){	// Ensure to have a screen to avoid errors
		QQuickItem * previousWrapper = nullptr;
		
		bool showAsTool = false;
#ifdef Q_OS_MACOS
		for(auto w : QGuiApplication::topLevelWindows()){
			if( (w->windowState()&Qt::WindowFullScreen)==Qt::WindowFullScreen){
				showAsTool = true;
				w->raise();// Used to get focus on Mac (On Mac, A Tool is hidden if the app has not focus and the only way to rid it is to use Widget Attributes(Qt::WA_MacAlwaysShowToolWindow) that is not available)
			}
		}
#endif
		for(int i = 0 ; i < allScreens.size() ; ++i){
			QQuickView *view = new QQuickView(App::getInstance()->getEngine(), nullptr);	// Use QQuickView to create a visual root object that is independant from current application Window
			QScreen *screen = allScreens[i];
			QObject::connect(view, &QQuickView::statusChanged, [allScreens](QQuickView::Status status){	// Debug handler : show screens descriptions on Error
				if( status == QQuickView::Error){
					QScreen * primaryScreen = QGuiApplication::primaryScreen();
					qInfo() << "Primary screen : " << primaryScreen->geometry() << primaryScreen->availableGeometry() <<  primaryScreen->virtualGeometry() <<  primaryScreen->availableVirtualGeometry();
					for(int i = 0 ; i < allScreens.size() ; ++i){
						QScreen *screen = allScreens[i];
						qInfo() << QString("Screen [")+QString::number(i)+"] (hdpi, Geometry, Available, Virtual, AvailableGeometry) :" 
								<< screen->devicePixelRatio() << screen->geometry() << screen->availableGeometry() << screen->virtualGeometry() << screen->availableVirtualGeometry();
					}
				}
			});
			view->setScreen(screen);	// Bind the visual root object to the screen
			view->setProperty("flags", QVariant(Qt::BypassWindowManagerHint | Qt::WindowStaysOnBottomHint | Qt::CustomizeWindowHint | Qt::X11BypassWindowManagerHint));	// Set the visual ghost window
			view->setSource(QString(NotificationsPath)+Notifier::Notifications[type].filename);
			
			QQuickWindow *subWindow = view->findChild<QQuickWindow *>("__internalWindow");
			QObject::connect(subWindow, &QObject::destroyed, view, &QObject::deleteLater);	// When destroying window, detroy visual root object too
			
			int * screenHeightOffset = &gScreenHeightOffset[screen->name()];	// Access optimization
			QRect availableGeometry = screen->availableGeometry();
			int heightOffset = availableGeometry.y() + (availableGeometry.height() - subWindow->height());//*screen->devicePixelRatio(); when using manual scaler
			if(showAsTool)
				subWindow->setProperty("showAsTool",true);
			subWindow->setX(availableGeometry.x()+ (availableGeometry.width()-subWindow->property("width").toInt()));//*screen->devicePixelRatio()); when using manual scaler
			subWindow->setY(heightOffset-(*screenHeightOffset % heightOffset));
			
			*screenHeightOffset = (subWindow->height() + *screenHeightOffset) + NotificationSpacing;
			if (*screenHeightOffset - heightOffset + availableGeometry.y() >= 0)
				*screenHeightOffset = 0;
			
			//			if(primaryScreen != screen){	//Useful when doing manual scaling jobs. Need to implement scaler in GUI objects
			//				//subwindow->setProperty("xScale", (double)screen->availableVirtualGeometry().width()/availableGeometry.width() );
			//				//subwindow->setProperty("yScale", (double)screen->availableVirtualGeometry().height()/availableGeometry.height());
			//			}
			wrapperItem = view->findChild<QQuickItem *>("__internalWrapper");
			::setProperty(*wrapperItem, NotificationPropertyData,data);
			view->setGeometry(subWindow->geometry());	// Ensure to have sufficient space to both let painter do job without error, and stay behind popup
			
			if(previousWrapper!=nullptr){	// Link objects in order to propagate events without having to store them
				QObject::connect(previousWrapper, SIGNAL(deleteNotification(QVariant)), wrapperItem,SLOT(deleteNotificationSlot()));
				QObject::connect(wrapperItem, SIGNAL(isOpened()), previousWrapper,SLOT(open()));
				QObject::connect(wrapperItem, SIGNAL(isClosed()), previousWrapper,SLOT(close()));
				QObject::connect(wrapperItem, &QObject::destroyed, previousWrapper, &QObject::deleteLater);
			}
			previousWrapper = wrapperItem;	// The last one is used as a point of start when deleting and openning
			
			view->show();
		}
		qInfo() << QStringLiteral("Create notifications:") << wrapperItem;
	}
	return wrapperItem;
}