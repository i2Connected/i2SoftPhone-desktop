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

#include <QCoreApplication>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QDBusMetaType>
#include <QDBusConnectionInterface>
#include <QDebug>
#include <QTimer>
#include <QImage>
#include <QBuffer>
#include <QDesktopServices>

#include "NotificationsDBus.hpp"

#include "app/App.hpp"
#include "app/providers/ImageProvider.hpp"
#include "components/call/CallModel.hpp"
#include "components/chat-room/ChatRoomModel.hpp"
#include "components/settings/AccountSettingsModel.hpp"
#include "components/timeline/TimelineModel.hpp"
#include "qquickwindow.h"
#include "utils/Utils.hpp"

// =============================================================================

namespace {
  constexpr char ServiceName[] = "org.freedesktop.Notifications";
  constexpr char ServicePath[] = "/org/freedesktop/Notifications";
}

QDBusArgument &operator<<(QDBusArgument &arg, const QImage &image) {
    QImage scaledImage;
    if (!image.isNull()) {
        scaledImage = image.scaled(200, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        if (scaledImage.format() != QImage::Format_ARGB32)
            scaledImage = scaledImage.convertToFormat(QImage::Format_ARGB32);
        scaledImage = scaledImage.rgbSwapped();
    }

    const int channels = 4; // ARGB32 has 4 channels

    arg.beginStructure();
    arg << scaledImage.width();
    arg << scaledImage.height();
    arg << scaledImage.bytesPerLine();
    arg << true; // ARGB32 has alpha
    arg << scaledImage.depth() / channels;
    arg << channels;
    arg << QByteArray::fromRawData((const char *)scaledImage.constBits(), scaledImage.height() * scaledImage.bytesPerLine());
    arg.endStructure();

    return arg;
}
const QDBusArgument &operator >>(const QDBusArgument &arg, QImage &image) {
    Q_UNUSED(image)
    return arg;
}

NotificationsDBus::NotificationsDBus (Notifier::NotificationType type, QVariantMap data, QDBusMessage message, QObject *parent) : QObject(parent), mType(type), mData(data), mMessage(message) {
	QDBusConnection::sessionBus().connect(QString(), QString(), "org.freedesktop.Notifications", "ActionInvoked", this, SLOT(onActionInvoked(quint32,QString)));
	QDBusConnection::sessionBus().connect(QString(), QString(), "org.freedesktop.Notifications", "NotificationClosed", this, SLOT(onNotificationClosed(quint32,quint32)));
}

NotificationsDBus::~NotificationsDBus () {
	closeNotification();
}

void NotificationsDBus::init(){
	qDBusRegisterMetaType<QImage>();
}

static void openUrl(QFileInfo info){
	bool showDirectory = showDirectory || !info.exists();
	if(!QDesktopServices::openUrl(
			QUrl(QStringLiteral("file:///%1").arg(showDirectory ? info.absolutePath() : info.absoluteFilePath()))
		) && !showDirectory){
		QDesktopServices::openUrl(QUrl(QStringLiteral("file:///%1").arg(info.absolutePath())));
	}
}

void NotificationsDBus::onActionInvoked(quint32 code ,QString key){
	qWarning() << code << key;
	if(code == mId && !mProcessed){
		switch(mType){
		case Notifier::ReceivedCall :{
			if(key == "call-start"){
				mData["call"].value<CallModel*>()->accept();
			}else if(key == "call-stop"){
				mData["call"].value<CallModel*>()->terminate();
			}else
				emit deleteNotification(QVariant::fromValue(this));
		}
		break;
		case Notifier::ReceivedFileMessage:{
			if(key == "document-open"){
				openUrl(QFileInfo( mData["fileUri"].toString()));
			}
		}
		break;
		case Notifier::ReceivedMessage: {
			if(key == "document-open"){
				CoreManager::getInstance()->getAccountSettingsModel()->setDefaultAccountFromSipAddress(mData["localAddress"].toString());
				auto timelineModel = mData["timelineModel"].value<TimelineModel*>();
				timelineModel->setSelected(true);
				App::getInstance()->smartShowWindow(App::getInstance()->getMainWindow());
			}
			/*
			notification.notificationData.window.setView('Conversation', {
															 chatRoomModel:notification.timelineModel.getChatRoomModel()
														 })
			*/
			
		}break;
		case Notifier::NewVersionAvailable:{
			if(key == "software-update-available")
				QDesktopServices::openUrl(QUrl(mData["url"].toString()));
		}
		break;
		case Notifier::SnapshotWasTaken:{
			if(key == "document-open"){
				openUrl(QFileInfo( mData["filePath"].toString()));
			}
		}
		break;
		case Notifier::RecordingCompleted:{
			if(key == "document-open"){
				openUrl(QFileInfo( mData["filePath"].toString()));
			}
		}
		break;
		default:{
		}
		}
		mProcessed = true;
	}
}

void NotificationsDBus::onNotificationClosed(quint32 id,quint32 reason){
	if( !mProcessed ){// Is was closed from system.
		if(reason != 2)
			qWarning() << "Notification has been closed by system. If this is an issue, please deactivate native notifications [" << id << reason << "]";
		//open();// Not a workaround because of infinite openning loop.
	}
}

QObject *NotificationsDBus::create(Notifier::NotificationType type, QVariantMap data) {
	QString title;
	QString message;
	QSize size, requestedSize(200,200);
	ImageProvider imageProvider;
	QVariantMap hints;
	QStringList actions;
	QString iconName = "linphone_logo";
	actions << "default" << "Close";
	//Check https://specifications.freedesktop.org/icon-naming-spec/icon-naming-spec-latest.html
	switch(type){
		case Notifier::ReceivedCall :
			//iconName = "call_sign_incoming";
			title = "Incoming call";
			message = Utils::getDisplayName(data["call"].value<CallModel*>()->getFullPeerAddress())+"\n"+data["call"].value<CallModel*>()->getPeerAddress();
			actions << "call-start" << "Accept";
			actions << "call-stop" << "Decline";
		break;
		case Notifier::ReceivedFileMessage :{
			auto timelineModel = data["timelineModel"].value<TimelineModel*>();
			title = "File received from " + timelineModel->getChatRoomModel()->getUsername();
			actions << "document-open" << "View";
			//message = timelineModel->getChatRoomModel()->getUsername();
		break;
		}
		case Notifier::ReceivedMessage: {
			auto timelineModel = data["timelineModel"].value<TimelineModel*>();
			title = "Message received from "+ timelineModel->getChatRoomModel()->getUsername();
			message = data["message"].toString();
			actions << "document-open" << "View";
		}
		break;
		case Notifier::NewVersionAvailable:{
			title = data["message"].toString();
			message = data["url"].toString();
			actions << "software-update-available" << "Download";
		}
		break;
		case Notifier::SnapshotWasTaken:{
			//iconName = "snapshot_sign";
			title = "Snapshot taken";
			actions << "document-open" << "View";
		}
		break;
		case Notifier::RecordingCompleted:{
			title = "Recording completed";
			actions << "document-open" << "View";
		}break;
		default:{
			return nullptr;
		}
	}
	
	hints["image_data"] = imageProvider.requestImage(iconName, &size, requestedSize);
	
	return new NotificationsDBus(type, data, createMessage(title, message, hints, actions));
}

QDBusMessage NotificationsDBus::createMessage(const QString& title, const QString& message, QVariantMap hints, QStringList actions){
	
	QDBusMessage msg = QDBusMessage::createMethodCall("org.freedesktop.Notifications", "/org/freedesktop/Notifications", "org.freedesktop.Notifications", "Notify");
	hints["urgency"] = 2;// if not 2, it can be timeout without taking account of custom timeout
	hints["category"] = "im";
	//hints["resident"] = true;
	hints["transient"] = true;
	//hints["desktop-entry"] = "com.belledonnecommunications.linphone";
	hints["suppress-sound"] = true;
	
	msg << APPLICATION_NAME; // Application name
	msg << quint32(0);	// ID
	msg << ""; // Icon to display
	msg << APPLICATION_NAME +QString(": ") + title; // Summary / Header of the message to display
	msg << message; // Body of the message to display
	msg << actions; // Actions from which the user may choose
	msg << hints; // Hints to the server displaying the message
	msg << qint32(0); // Timeout in milliseconds
	
	return msg;
}

void NotificationsDBus::open(){
	QDBusPendingReply<quint32> asyncReply(QDBusConnection::sessionBus().asyncCall(mMessage)); // Would return a message containing the id of this notification
	asyncReply.waitForFinished();
	if(asyncReply.isValid())
		mId = asyncReply.argumentAt(0).toInt();
	else
		qWarning() << asyncReply.error();
}

void NotificationsDBus::closeNotification(){
	QDBusMessage msg = QDBusMessage::createMethodCall("org.freedesktop.Notifications", "/org/freedesktop/Notifications", "org.freedesktop.Notifications", "CloseNotification");
	msg << quint32(mId);
	QDBusConnection::sessionBus().call(msg);
}