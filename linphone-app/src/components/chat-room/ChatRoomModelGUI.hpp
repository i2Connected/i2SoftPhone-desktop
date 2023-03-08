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

#ifndef CHAT_ROOM_MODEL_GUI_H_
#define CHAT_ROOM_MODEL_GUI_H_

#include <linphone++/linphone.hh>
#include "app/proxyModel/ProxyListModel.hpp"
#include <QDateTime>

#include "utils/LinphoneEnums.hpp"

#include "utils/CodeHelpersGUI.hpp"

// =============================================================================
// Fetch all N messages of a ChatRoom.
// =============================================================================

class ParticipantListModel;
class ChatRoomModel;
class ChatMessageModel;

class ChatRoomModelGUI : public ProxyListModel {
	
	Q_OBJECT
	
public:
	enum Roles {
		ChatEntry = Qt::DisplayRole,
		SectionDate
	};
	
	enum EntryType {
		GenericEntry,
		MessageEntry,
		CallEntry,
		NoticeEntry
	};
	Q_ENUM(EntryType)
	
	Q_PROPERTY(QString subject READ getSubject WRITE setSubject NOTIFY subjectChanged)
	Q_PROPERTY(QDateTime lastUpdateTime READ getLastUpdateTime WRITE setLastUpdateTime NOTIFY lastUpdateTimeChanged)
	Q_PROPERTY(int unreadMessagesCount READ getUnreadMessagesCount WRITE setUnreadMessagesCount NOTIFY unreadMessagesCountChanged)
	Q_PROPERTY(int missedCallsCount READ getMissedCallsCount WRITE setMissedCallsCount NOTIFY missedCallsCountChanged)
	
	Q_PROPERTY(int securityLevel READ getSecurityLevel NOTIFY securityLevelChanged)
	Q_PROPERTY(bool groupEnabled READ isGroupEnabled NOTIFY groupEnabledChanged)
	Q_PROPERTY(bool isConference READ isConference CONSTANT)
	Q_PROPERTY(bool isOneToOne READ isOneToOne CONSTANT)
	Q_PROPERTY(bool haveEncryption READ haveEncryption CONSTANT)
	Q_PROPERTY(bool isMeAdmin READ isMeAdmin NOTIFY isMeAdminChanged)
	Q_PROPERTY(bool canHandleParticipants READ canHandleParticipants CONSTANT)
	
	Q_PROPERTY(bool isComposing READ getIsRemoteComposing NOTIFY isRemoteComposingChanged)
	Q_PROPERTY(QList<QString> composers READ getComposers NOTIFY isRemoteComposingChanged)
	Q_PROPERTY(bool isReadOnly READ isReadOnly NOTIFY isReadOnlyChanged)
	Q_PROPERTY(bool updating READ isUpdating NOTIFY updatingChanged)
	
	Q_PROPERTY(QString sipAddress READ getFullPeerAddress NOTIFY fullPeerAddressChanged)
	Q_PROPERTY(QString sipAddressUriOnly READ getPeerAddress NOTIFY fullPeerAddressChanged)
	Q_PROPERTY(QString username READ getUsername NOTIFY usernameChanged)
	Q_PROPERTY(QString avatar READ getAvatar NOTIFY avatarChanged)
	Q_PROPERTY(int presenceStatus READ getPresenceStatus NOTIFY presenceStatusChanged)
	Q_PROPERTY(LinphoneEnums::ChatRoomState state READ getState NOTIFY stateChanged)
	
	Q_PROPERTY(long ephemeralLifetime READ getEphemeralLifetime WRITE setEphemeralLifetime NOTIFY ephemeralLifetimeChanged)
	Q_PROPERTY(bool ephemeralEnabled READ isEphemeralEnabled WRITE setEphemeralEnabled NOTIFY ephemeralEnabledChanged)
	Q_PROPERTY(bool canBeEphemeral READ canBeEphemeral NOTIFY canBeEphemeralChanged)
	Q_PROPERTY(bool markAsReadEnabled READ markAsReadEnabled WRITE enableMarkAsRead NOTIFY markAsReadEnabledChanged)
	Q_PROPERTY(bool notificationsEnabled READ isNotificationsEnabled WRITE enableNotifications NOTIFY notificationsEnabledChanged)
	
	Q_PROPERTY(ParticipantListModel* participants READ getParticipantListModel CONSTANT)
	
	Q_PROPERTY(ChatMessageModel * reply READ getReply WRITE setReply NOTIFY replyChanged)
	
	Q_PROPERTY(bool entriesLoading READ isEntriesLoading WRITE setEntriesLoading NOTIFY entriesLoadingChanged)
	
	ChatRoomModelGUI (ChatRoomModel * chatRoomModel, QObject * parent = nullptr);
	~ChatRoomModelGUI ();
	/*
	QHash<int, QByteArray> roleNames () const override;
	QVariant data (const QModelIndex &index, int role) const override;
	
	bool removeRows (int row, int count, const QModelIndex &parent = QModelIndex()) override;
	void removeAllEntries ();
*/
//---- Getters
	
	Q_INVOKABLE QString getPeerAddress () const;
	Q_INVOKABLE QString getLocalAddress () const;
	Q_INVOKABLE QString getFullPeerAddress () const;
	Q_INVOKABLE QString getFullLocalAddress () const;
	Q_INVOKABLE QString getConferenceAddress () const;
	
	QString getSubject () const;
	QString getUsername () const;
	QString getAvatar () const;
	int getPresenceStatus() const;
	LinphoneEnums::ChatRoomState getState() const;
	bool isReadOnly() const;
	bool isEphemeralEnabled() const;
	long getEphemeralLifetime() const;
	bool canBeEphemeral() const;
	bool haveEncryption() const;
	bool markAsReadEnabled() const;
	Q_INVOKABLE bool isSecure() const;
	int getSecurityLevel() const;
	bool isGroupEnabled() const;
	bool isConference() const;
	bool isOneToOne() const;
	bool isMeAdmin() const;
	bool canHandleParticipants() const;
	bool getIsRemoteComposing () const;
	bool isEntriesLoading() const;
	bool isUpdating() const;
	bool isNotificationsEnabled() const;
	QDateTime getLastUpdateTime() const;
	int getUnreadMessagesCount() const;
	int getMissedCallsCount() const;
	
	ParticipantListModel* getParticipantListModel() const;
	QList<QString> getComposers() const;
	ChatMessageModel * getReply()const;

signals:	
//---- Setters
	void setSubject(QString& subject);
	void setLastUpdateTime(const QDateTime& lastUpdateDate);
	void setEntriesLoading(const bool& loading);
	
	void setUnreadMessagesCount(const int& count);	
	void setMissedCallsCount(const int& count);
	void setEphemeralEnabled(bool enabled);
	void setEphemeralLifetime(long lifetime);
	void enableMarkAsRead(const bool& enable);
	void enableNotifications(const bool& enable);
	
	void setReply(ChatMessageModel * model);

// Tools
	Q_INVOKABLE void deleteChatRoom();
	Q_INVOKABLE void leaveChatRoom ();
	Q_INVOKABLE void updateParticipants(const QVariantList& participants);
	Q_INVOKABLE void forwardMessage(ChatMessageModel * model);
	Q_INVOKABLE void resetMessageCount ();
	Q_INVOKABLE int loadMoreEntries();	// return new entries count
	Q_INVOKABLE int loadTillMessage(ChatMessageModel * message);// Load all entries till message and return its index. -1 if not found.
	
signals:
	bool isRemoteComposingChanged ();
	void entriesLoadingChanged(const bool& loading);
	void allEntriesRemoved (QSharedPointer<ChatRoomModel> model);
	void lastEntryRemoved ();
	void messageSent (const std::shared_ptr<linphone::ChatMessage> &message);
	void messageReceived (const std::shared_ptr<linphone::ChatMessage> &message);
	void messageCountReset ();
	void focused ();
	void fullPeerAddressChanged();
	void participantsChanged();
	void subjectChanged(QString subject);
	void usernameChanged();
	void avatarChanged();
	void presenceStatusChanged();
	void lastUpdateTimeChanged();
	void unreadMessagesCountChanged();
	void missedCallsCountChanged();
	void securityLevelChanged(int securityLevel);
	void groupEnabledChanged(bool groupEnabled);
	void isMeAdminChanged();
	void stateChanged(int state);
	void isReadOnlyChanged();
	void ephemeralEnabledChanged();
	void ephemeralLifetimeChanged();
	void canBeEphemeralChanged();
	void markAsReadEnabledChanged();
	void chatRoomDeleted();// Must be connected with DirectConnection mode
	void replyChanged();
	void updatingChanged();
	void notificationsEnabledChanged();
	
// Chat Room listener callbacks	
	
	void securityEvent(const std::shared_ptr<const linphone::EventLog> & eventLog);
	void participantAdded(const std::shared_ptr<const linphone::EventLog> & eventLog);
	void participantRemoved(const std::shared_ptr<const linphone::EventLog> & eventLog);
	void participantDeviceAdded(const std::shared_ptr<const linphone::EventLog> & eventLog);
	void participantDeviceRemoved(const std::shared_ptr<const linphone::EventLog> & eventLog);
	void participantAdminStatusChanged(const std::shared_ptr<const linphone::EventLog> & eventLog);
	void participantRegistrationSubscriptionRequested(const std::shared_ptr<const linphone::Address> & participantAddress);
	void participantRegistrationUnsubscriptionRequested(const std::shared_ptr<const linphone::Address> & participantAddress);
	void conferenceJoined(const std::shared_ptr<const linphone::EventLog> & eventLog);
	void conferenceLeft(const std::shared_ptr<const linphone::EventLog> & eventLog);
	
		// SYNC

	DECLARE_SYNC_SIGNAL(QString, getPeerAddress)
	DECLARE_SYNC_SIGNAL(QString, getLocalAddress)
	DECLARE_SYNC_SIGNAL(QString, getFullPeerAddress)
	DECLARE_SYNC_SIGNAL(QString, getFullLocalAddress)
	DECLARE_SYNC_SIGNAL(QString, getConferenceAddress)
	DECLARE_SYNC_SIGNAL(QString, getSubject)
	DECLARE_SYNC_SIGNAL(QString, getUsername)
	DECLARE_SYNC_SIGNAL(QString, getAvatar)
	DECLARE_SYNC_SIGNAL(int, getPresenceStatus)
	DECLARE_SYNC_SIGNAL(LinphoneEnums::ChatRoomState , getState)
	DECLARE_SYNC_SIGNAL(bool, isReadOnly)
	DECLARE_SYNC_SIGNAL(bool, isEphemeralEnabled)
	DECLARE_SYNC_SIGNAL(long, getEphemeralLifetime)
	DECLARE_SYNC_SIGNAL(bool, canBeEphemeral)
	DECLARE_SYNC_SIGNAL(bool, haveEncryption)
	DECLARE_SYNC_SIGNAL(bool, markAsReadEnabled)
	DECLARE_SYNC_SIGNAL(bool, isSecure)
	DECLARE_SYNC_SIGNAL(int, getSecurityLevel)
	DECLARE_SYNC_SIGNAL(bool, isGroupEnabled)
	DECLARE_SYNC_SIGNAL(bool, isConference)
	DECLARE_SYNC_SIGNAL(bool, isOneToOne)
	DECLARE_SYNC_SIGNAL(bool, isMeAdmin)
	DECLARE_SYNC_SIGNAL(bool, canHandleParticipants)
	DECLARE_SYNC_SIGNAL(bool, getIsRemoteComposing)
	DECLARE_SYNC_SIGNAL(bool, isEntriesLoading)
	DECLARE_SYNC_SIGNAL(bool, isUpdating)
	DECLARE_SYNC_SIGNAL(bool, isNotificationsEnabled)
	DECLARE_SYNC_SIGNAL(ParticipantListModel*, getParticipantListModel)
	DECLARE_SYNC_SIGNAL(QList<QString>, getComposers)
	DECLARE_SYNC_SIGNAL(ChatMessageModel*, getReply)
	DECLARE_SYNC_SIGNAL(QDateTime, getLastUpdateTime)
	DECLARE_SYNC_SIGNAL(int, getUnreadMessagesCount)
	DECLARE_SYNC_SIGNAL(int, getMissedCallsCount)
	
};

#endif
