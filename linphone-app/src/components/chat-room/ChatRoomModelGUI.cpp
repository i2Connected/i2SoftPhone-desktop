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

#include "config.h"

#include "ChatRoomModelGUI.hpp"
#include "components/core/CoreManager.hpp"
#include "components/chat-events/ChatMessageModel.hpp"
#include "ChatRoomModel.hpp"

// =============================================================================

ChatRoomModelGUI::ChatRoomModelGUI(ChatRoomModel * appModel, QObject * parent) : ProxyListModel(parent){
	
	// signals
	CONNECT_CORE_TO_GUI(isRemoteComposingChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(entriesLoadingChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(allEntriesRemoved, ChatRoomModel);
	CONNECT_CORE_TO_GUI(lastEntryRemoved, ChatRoomModel);
	CONNECT_CORE_TO_GUI(messageSent, ChatRoomModel);
	CONNECT_CORE_TO_GUI(messageReceived, ChatRoomModel);
	CONNECT_CORE_TO_GUI(messageCountReset, ChatRoomModel);
	CONNECT_CORE_TO_GUI(focused, ChatRoomModel);
	CONNECT_CORE_TO_GUI(fullPeerAddressChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(participantsChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(subjectChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(usernameChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(avatarChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(presenceStatusChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(lastUpdateTimeChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(unreadMessagesCountChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(missedCallsCountChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(securityLevelChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(groupEnabledChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(isMeAdminChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(stateChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(isReadOnlyChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(ephemeralEnabledChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(ephemeralLifetimeChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(canBeEphemeralChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(markAsReadEnabledChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(chatRoomDeleted, ChatRoomModel);
	CONNECT_CORE_TO_GUI(replyChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(updatingChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(notificationsEnabledChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(securityEvent, ChatRoomModel);
	CONNECT_CORE_TO_GUI(participantAdded, ChatRoomModel);
	CONNECT_CORE_TO_GUI(participantRemoved, ChatRoomModel);
	CONNECT_CORE_TO_GUI(participantDeviceAdded, ChatRoomModel);
	CONNECT_CORE_TO_GUI(participantDeviceRemoved, ChatRoomModel);
	CONNECT_CORE_TO_GUI(participantAdminStatusChanged, ChatRoomModel);
	CONNECT_CORE_TO_GUI(participantRegistrationSubscriptionRequested, ChatRoomModel);
	CONNECT_CORE_TO_GUI(participantRegistrationUnsubscriptionRequested, ChatRoomModel);
	CONNECT_CORE_TO_GUI(conferenceJoined, ChatRoomModel);
	CONNECT_CORE_TO_GUI(conferenceLeft, ChatRoomModel);
		
	// Setters/tools
	
	CONNECT_GUI_TO_CORE(setSubject, ChatRoomModel);
	CONNECT_GUI_TO_CORE(setLastUpdateTime, ChatRoomModel);
	CONNECT_GUI_TO_CORE(setEntriesLoading, ChatRoomModel);
	CONNECT_GUI_TO_CORE(setUnreadMessagesCount, ChatRoomModel);
	CONNECT_GUI_TO_CORE(setMissedCallsCount, ChatRoomModel);
	CONNECT_GUI_TO_CORE(setEphemeralEnabled, ChatRoomModel);
	CONNECT_GUI_TO_CORE(setEphemeralLifetime, ChatRoomModel);
	CONNECT_GUI_TO_CORE(enableMarkAsRead, ChatRoomModel);
	CONNECT_GUI_TO_CORE(enableNotifications, ChatRoomModel);
	CONNECT_GUI_TO_CORE(setReply, ChatRoomModel);
	CONNECT_GUI_TO_CORE(deleteChatRoom, ChatRoomModel);
	CONNECT_GUI_TO_CORE(leaveChatRoom, ChatRoomModel);
	CONNECT_GUI_TO_CORE(updateParticipants, ChatRoomModel);
	CONNECT_GUI_TO_CORE(forwardMessage, ChatRoomModel);
	CONNECT_GUI_TO_CORE(resetMessageCount, ChatRoomModel);
	CONNECT_GUI_TO_CORE(loadMoreEntries, ChatRoomModel);
	CONNECT_GUI_TO_CORE(loadTillMessage, ChatRoomModel);
	
	// Getters
	
	CONNECT_SYNC_TO_SLOT(getPeerAddress, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(getLocalAddress, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(getFullPeerAddress, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(getFullLocalAddress, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(getConferenceAddress, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(getSubject, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(getUsername, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(getAvatar, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(getPresenceStatus, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(getState, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(isReadOnly, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(isEphemeralEnabled, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(getEphemeralLifetime, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(canBeEphemeral, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(haveEncryption, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(markAsReadEnabled, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(isSecure, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(getSecurityLevel, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(isGroupEnabled, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(isConference, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(isOneToOne, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(isMeAdmin, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(canHandleParticipants, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(getIsRemoteComposing, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(isEntriesLoading, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(isUpdating, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(isNotificationsEnabled, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(getParticipantListModel, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(getComposers, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(getReply, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(getLastUpdateTime, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(getUnreadMessagesCount, ChatRoomModel);
	CONNECT_SYNC_TO_SLOT(getMissedCallsCount, ChatRoomModel);
	
}

ChatRoomModelGUI::~ChatRoomModelGUI(){
}


DEFINE_GETTER(QString, getPeerAddress, ChatRoomModel)
DEFINE_GETTER(QString, getLocalAddress, ChatRoomModel)
DEFINE_GETTER(QString, getFullPeerAddress, ChatRoomModel)
DEFINE_GETTER(QString, getFullLocalAddress, ChatRoomModel)
DEFINE_GETTER(QString, getConferenceAddress, ChatRoomModel)
DEFINE_GETTER(QString, getSubject, ChatRoomModel)
DEFINE_GETTER(QString, getUsername, ChatRoomModel)
DEFINE_GETTER(QString, getAvatar, ChatRoomModel)
DEFINE_GETTER(int, getPresenceStatus, ChatRoomModel)
DEFINE_GETTER(LinphoneEnums::ChatRoomState , getState, ChatRoomModel)
DEFINE_GETTER(bool, isReadOnly, ChatRoomModel)
DEFINE_GETTER(bool, isEphemeralEnabled, ChatRoomModel)
DEFINE_GETTER(long, getEphemeralLifetime, ChatRoomModel)
DEFINE_GETTER(bool, canBeEphemeral, ChatRoomModel)
DEFINE_GETTER(bool, haveEncryption, ChatRoomModel)
DEFINE_GETTER(bool, markAsReadEnabled, ChatRoomModel)
DEFINE_GETTER(bool, isSecure, ChatRoomModel)
DEFINE_GETTER(int, getSecurityLevel, ChatRoomModel)
DEFINE_GETTER(bool, isGroupEnabled, ChatRoomModel)
DEFINE_GETTER(bool, isConference, ChatRoomModel)
DEFINE_GETTER(bool, isOneToOne, ChatRoomModel)
DEFINE_GETTER(bool, isMeAdmin, ChatRoomModel)
DEFINE_GETTER(bool, canHandleParticipants, ChatRoomModel)
DEFINE_GETTER(bool, getIsRemoteComposing, ChatRoomModel)
DEFINE_GETTER(bool, isEntriesLoading, ChatRoomModel)
DEFINE_GETTER(bool, isUpdating, ChatRoomModel)
DEFINE_GETTER(bool, isNotificationsEnabled, ChatRoomModel)
DEFINE_GETTER(ParticipantListModelGUI*, getParticipantListModel, ChatRoomModel)
DEFINE_GETTER(QList<QString>, getComposers, ChatRoomModel)
DEFINE_GETTER(ChatMessageModel*, getReply, ChatRoomModel)
DEFINE_GETTER(QDateTime, getLastUpdateTime, ChatRoomModel)
DEFINE_GETTER(int, getUnreadMessagesCount, ChatRoomModel)
DEFINE_GETTER(int, getMissedCallsCount, ChatRoomModel)

