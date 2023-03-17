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

#include "ParticipantListModelGUI.hpp"
#include "components/core/CoreManager.hpp"
#include "components/chat-events/ChatMessageModel.hpp"
#include "ParticipantListModel.hpp"

// =============================================================================

ParticipantListModelGUI::ParticipantListModelGUI(QSharedPointer<ParticipantListModel> participantListModel, QObject * parent) : ProxyListModel(parent){
	mParticipantListModel = participantListModel;
	auto appModel = mParticipantListModel.get();
	// signals
	CONNECT_CORE_TO_GUI(securityLevelChanged, ParticipantListModel);
	CONNECT_CORE_TO_GUI(deviceSecurityLevelChanged, ParticipantListModel);
	CONNECT_CORE_TO_GUI(participantsChanged, ParticipantListModel);
	
	// Setters/tools
	CONNECT_GUI_TO_CORE(remove, ParticipantListModel);
	
	// Getters
	CONNECT_SYNC_TO_SLOT(getChatRoomModelGUI, ParticipantListModel);
	CONNECT_SYNC_TO_SLOT(addressesToString, ParticipantListModel);
	CONNECT_SYNC_TO_SLOT(displayNamesToString, ParticipantListModel);
	CONNECT_SYNC_TO_SLOT(usernamesToString, ParticipantListModel);
}

ParticipantListModelGUI::~ParticipantListModelGUI(){
}

QSharedPointer<ParticipantListModel> ParticipantListModelGUI::getParticipantListModel()const{
	return mParticipantListModel;
}

DEFINE_GETTER(ChatRoomModelGUI*, getChatRoomModelGUI, ParticipantListModel)
DEFINE_GETTER(QString, addressesToString, ParticipantListModel)
DEFINE_GETTER(QString, displayNamesToString, ParticipantListModel)
DEFINE_GETTER(QString, usernamesToString, ParticipantListModel)

