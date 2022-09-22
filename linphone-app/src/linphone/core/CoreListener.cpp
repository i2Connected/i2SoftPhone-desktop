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

#include <QMutex>
#include <QtDebug>
#include <QThread>
#include <QTimer>

#include "app/App.hpp"
#include "components/call/CallModel.hpp"
#include "components/contact/ContactModel.hpp"
#include "components/notifier/Notifier.hpp"
#include "components/settings/AccountSettingsModel.hpp"
#include "components/settings/SettingsModel.hpp"
#include "components/timeline/TimelineListModel.hpp"
#include "utils/Utils.hpp"

#include "CoreListener.hpp"

// =============================================================================

using namespace std;

// -----------------------------------------------------------------------------

CoreListener::CoreListener(QObject * parent): QObject(parent){
}
CoreListener::~CoreListener(){
	qDebug() << "Destroying CoreListener " << this;
}

// -----------------------------------------------------------------------------
void CoreListener::onAccountRegistrationStateChanged(const std::shared_ptr<linphone::Core> & core, const std::shared_ptr<linphone::Account> & account, linphone::RegistrationState state, const std::string & message){
	emit accountRegistrationStateChanged(account, state, message);
}
void CoreListener::onAuthenticationRequested(const std::shared_ptr<linphone::Core> &core, const std::shared_ptr<linphone::AuthInfo> &authInfo, linphone::AuthMethod method){
	emit authenticationRequested(authInfo, method);
}
void CoreListener::onCallEncryptionChanged(const std::shared_ptr<linphone::Core> &core, const std::shared_ptr<linphone::Call> &call, bool on, const std::string &authenticationToken){
	emit callEncryptionChanged(call, on, authenticationToken);
}
void CoreListener::onCallLogUpdated(const std::shared_ptr<linphone::Core> & core, const std::shared_ptr<linphone::CallLog> & callLog){
	emit onCallLogUpdated(callLog);
}
void CoreListener::onCallStateChanged (const std::shared_ptr<linphone::Core> &core, const std::shared_ptr<linphone::Call> &call, linphone::Call::State state, const std::string &message){
	emit onCallStateChanged(call, state, message);
}
void CoreListener::onCallStatsUpdated (const std::shared_ptr<linphone::Core> &core, const std::shared_ptr<linphone::Call> &call, const std::shared_ptr<const linphone::CallStats> &stats){
	emit onCallStatsUpdated(call, stats);
}
void CoreListener::onCallCreated(const std::shared_ptr<linphone::Core> & lc, const std::shared_ptr<linphone::Call> & call){
	emit onCallCreated(call);
}
void CoreListener::onChatRoomStateChanged(const std::shared_ptr<linphone::Core> & core, const std::shared_ptr<linphone::ChatRoom> & chatRoom, linphone::ChatRoom::State state){
	emit onChatRoomStateChanged(chatRoom, state);
}
void CoreListener::onConfiguringStatus(const std::shared_ptr<linphone::Core> & core, linphone::ConfiguringState status, const std::string & message){
	emit onConfiguringStatus(status, message);
}
void CoreListener::onDtmfReceived(const std::shared_ptr<linphone::Core> & lc, const std::shared_ptr<linphone::Call> & call, int dtmf){
	emit onDtmfReceived(call dtmf);
}
void CoreListener::onGlobalStateChanged (const std::shared_ptr<linphone::Core> &core, linphone::GlobalState gstate, const std::string &message){
	emit onGlobalStateChanged(gstate, message);
}
void CoreListener::onIsComposingReceived (const std::shared_ptr<linphone::Core> &core, const std::shared_ptr<linphone::ChatRoom> &room){
	emit onIsComposingReceived(room);
}
void CoreListener::onLogCollectionUploadStateChanged (const std::shared_ptr<linphone::Core> &core, linphone::Core::LogCollectionUploadState state, const std::string &info){
	emit onLogCollectionUploadStateChanged(state, info);
}
void CoreListener::onLogCollectionUploadProgressIndication (const std::shared_ptr<linphone::Core> &lc, size_t offset, size_t total){
	emit onLogCollectionUploadProgressIndication(offset, total);
}
void CoreListener::onMessageReceived (const std::shared_ptr<linphone::Core> &core, const std::shared_ptr<linphone::ChatRoom> &room, const std::shared_ptr<linphone::ChatMessage> &message){
	emit onMessageReceived(room, message);
}
void CoreListener::onMessagesReceived (const std::shared_ptr<linphone::Core> &core, const std::shared_ptr<linphone::ChatRoom> &room, const std::list<std::shared_ptr<linphone::ChatMessage>> &messages){
	emit onMessagesReceived(room, messages);
}
void CoreListener::onNotifyPresenceReceivedForUriOrTel (const std::shared_ptr<linphone::Core> &core, const std::shared_ptr<linphone::Friend> &linphoneFriend, const std::string &uriOrTel, const std::shared_ptr<const linphone::PresenceModel> &presenceModel){
	emit onNotifyPresenceReceivedForUriOrTel(linphoneFriend, uriOrTel, presenceModel);
}
void CoreListener::onNotifyPresenceReceived (const std::shared_ptr<linphone::Core> &core, const std::shared_ptr<linphone::Friend> &linphoneFriend){
	emit onNotifyPresenceReceived(linphoneFriend);
}
void CoreListener::onQrcodeFound(const std::shared_ptr<linphone::Core> & core, const std::string & result){
	emit onQrcodeFound(result);
}
void CoreListener::onTransferStateChanged (const std::shared_ptr<linphone::Core> &core, const std::shared_ptr<linphone::Call> &call, linphone::Call::State state){
	emit onTransferStateChanged(call, state);
}
void CoreListener::onVersionUpdateCheckResultReceived (const std::shared_ptr<linphone::Core> & core, linphone::VersionUpdateCheckResult result, const std::string &version, const std::string &url){
	emit onVersionUpdateCheckResultReceived(result, version, url);
}
void CoreListener::onEcCalibrationResult(const std::shared_ptr<linphone::Core> & core, linphone::EcCalibratorStatus status, int delayMs){
	emit onEcCalibrationResult(delayMs);
}
void CoreListener::onConferenceInfoReceived(const std::shared_ptr<linphone::Core> & core, const std::shared_ptr<const linphone::ConferenceInfo> & conferenceInfo){
	emit onConferenceInfoReceived(conferenceInfo);
}
