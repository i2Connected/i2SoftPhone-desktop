/*
 * Copyright (c) 2010-2020 Belledonne Communications SARL.
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

#ifndef CORE_H_
#define CORE_H_

#include <linphone++/linphone.hh>
#include <QObject>
#include <QString>
#include <QHash>
#include <QMutex>
#include <QSharedPointer>

// =============================================================================

class QTimer;

class AbstractEventCountNotifier;
class AccountSettingsModel;
class CallsListModel;
class ChatModel;
class ChatRoomModel;
class ContactsListModel;
class ContactsImporterListModel;
class CoreHandlers;
class CoreManagerGUI;
class EventCountNotifier;
class HistoryModel;
class LdapListModel;
class RecorderManager;
class SettingsModel;
class SipAddressesModel;
class VcardModel;
class TimelineListModel;

class LinphoneThread;


class CoreManager : public QObject {
	Q_OBJECT
public:
	
	std::shared_ptr<linphone::Core> getCore () {
		return mCore;
	}
	

	QString getVersion () const;
	int getEventCount () const;
	static QString getDownloadUrl ();
	
	// ---------------------------------------------------------------------------
	// Initialization.
	// ---------------------------------------------------------------------------
	
	static void init (QObject *parent, const QString &configPath);
	static void uninit ();
	
	// ---------------------------------------------------------------------------
	
	// Must be used in a qml scene.
	// Warning: The ownership of `VcardModel` is `QQmlEngine::JavaScriptOwnership` by default.
	Q_INVOKABLE VcardModel *createDetachedVcardModel () const;
	
	Q_INVOKABLE void forceRefreshRegisters ();
	void updateUnreadMessageCount();
	void stateChanged(Qt::ApplicationState pState);
	
	Q_INVOKABLE void sendLogs () const;
	Q_INVOKABLE void cleanLogs () const;
	
	int getCallLogsCount() const;
	int getMissedCallCount(const QString &peerAddress, const QString &localAddress) const;// Get missed call count from a chat (useful for showing bubbles on Timelines)
	int getMissedCallCountFromLocal(const QString &localAddress) const;// Get missed call count from a chat (useful for showing bubbles on Timelines)
	
	std::list<std::shared_ptr<linphone::Account>> getAccountList()const;
	
	static bool isInstanciated(){return mInstance!=nullptr;}
	
	Q_INVOKABLE bool isLastRemoteProvisioningGood();
	Q_INVOKABLE QString getUserAgent()const;
	void updateUserAgent();
	
public slots:
	void initCoreManager();
	void startIterate();
	void stopIterate();
	void setLastRemoteProvisioningState(const linphone::ConfiguringState& state);
	void createLinphoneCore (const QString &configPath);// In order to delay creation
	void handleChatRoomCreated(const QSharedPointer<ChatRoomModel> &chatRoomModel);
	
signals:
	void coreManagerInitialized ();
	
	void chatRoomModelCreated (const QSharedPointer<ChatRoomModel> &chatRoomModel);
	void historyModelCreated (HistoryModel *historyModel);
	void recorderManagerCreated(RecorderManager *recorderModel);
	
	void logsUploaded (const QString &url);
	
	void eventCountChanged ();
	void callLogsCountChanged();
	
private:
	CoreManager (QObject *parent, const QString &configPath);
	~CoreManager ();
	
	void setDatabasesPaths ();
	void setOtherPaths ();
	void setResourcesPaths ();
	
	void migrate ();
	

	
	void iterate ();
	
	void handleLogsUploadStateChanged (linphone::Core::LogCollectionUploadState state, const std::string &info);
	
	void connectTo(CoreListener * listener);
	std::shared_ptr<linphone::Core> mCore;
	std::shared_ptr<CoreListener> mListener;
	
	bool mStarted = false;
};

#endif // CORE_MANAGER_H_
