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

#ifndef NOTIFICATIONS_DBUS_H_
#define NOTIFICATIONS_DBUS_H_

#include <QDBusInterface>
#include "components/notifier/Notifier.hpp"

// =============================================================================

class QDBusPendingCallWatcher;


class NotificationsDBus : public QObject {
	Q_OBJECT
	
public:
	NotificationsDBus (Notifier::NotificationType type, QVariantMap data, QDBusMessage message, QObject *parent = Q_NULLPTR);
	~NotificationsDBus ();
	static void init();
	
	static QObject *create(Notifier::NotificationType type, QVariantMap data);
	
	//QObject *createNotification (NotificationType type, QVariantMap data);
	
	
	void closeNotification();
	static QDBusMessage createMessage(const QString& title, const QString& message, QVariantMap hints, QStringList actions);
public slots:
	void open();
	void onActionInvoked(quint32 code ,QString key);
	void onNotificationClosed(quint32 id,quint32 reason);
signals:
	void deleteNotification(QVariant notification);
private:
	//bool mScreenSaverStatus = true;
	Notifier::NotificationType mType;
	QVariantMap mData;
	QDBusMessage mMessage;
	int mId = -1;
	bool mProcessed = false;
};

#endif
