#include "Core.hpp"

#include <QDebug>
#include <QTimer>

#include "utils/Constants.hpp"

Core::Core(QObject * parent) : LinphoneObject<std::shared_ptr<linphone::Core>>(parent){

}

void Core::startIterate(){
	mCbsTimer = new QTimer((QThread*)this);
	mCbsTimer->setInterval(Constants::CbsCallInterval);
	QObject::connect(mCbsTimer, &QTimer::timeout, this, &Core::iterate);
	qInfo() << QStringLiteral("Start iterate");

	mCbsTimer->start();
	start();
}

void Core::stopIterate(){
	qInfo() << QStringLiteral("Stop iterate");
	mCbsTimer->stop();
	mCbsTimer->deleteLater();// allow the timer to continue its stuff
	mCbsTimer = nullptr;
}

void Core::iterate ()
	if(mLinphoneObject)
		mLinphoneObject->iterate();
}
