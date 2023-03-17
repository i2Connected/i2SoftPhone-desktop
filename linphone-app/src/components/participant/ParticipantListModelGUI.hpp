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

#ifndef PARTICIPANT_LIST_MODEL_GUI_H_
#define PARTICIPANT_LIST_MODEL_GUI_H_

#include <QSortFilterProxyModel>
#include "components/participant/ParticipantModel.hpp"
#include "app/proxyModel/ProxyListModel.hpp"

#include "utils/CodeHelpersGUI.hpp"

class ConferenceModel;
class ParticipantListModel;

#include "components/chat-room/ChatRoomModelGUI.hpp"


// =============================================================================

class ParticipantListModelGUI : public ProxyListModel {
  Q_OBJECT
public:	
	ParticipantListModelGUI (QSharedPointer<ParticipantListModel> participantListModel, QObject *parent = Q_NULLPTR);
	//ParticipantListModel (ConferenceModel * conferenceModel, QObject *parent = Q_NULLPTR);
	virtual ~ParticipantListModelGUI();
	
	Q_PROPERTY(ChatRoomModelGUI* chatRoomModel READ getChatRoomModelGUI CONSTANT)
	Q_PROPERTY(QString addressesToString READ addressesToString NOTIFY participantsChanged)
	Q_PROPERTY(QString displayNamesToString READ displayNamesToString NOTIFY participantsChanged)
	Q_PROPERTY(QString usernamesToString READ usernamesToString NOTIFY participantsChanged)
    

	Q_INVOKABLE ChatRoomModelGUI* getChatRoomModelGUI() const;
	Q_INVOKABLE ConferenceModel* getConferenceModel() const{
		return nullptr;
	}
	Q_INVOKABLE QString addressesToString()const;	
	Q_INVOKABLE QString displayNamesToString()const;
	Q_INVOKABLE QString usernamesToString()const;
	
	QSharedPointer<ParticipantListModel> getParticipantListModel()const;
	
	QSharedPointer<ParticipantListModel> mParticipantListModel;

signals:	
	Q_INVOKABLE void remove (ParticipantModel *importer);
	
signals:
	void securityLevelChanged();
	void deviceSecurityLevelChanged(std::shared_ptr<const linphone::Address> device);
	void participantsChanged();
	
	DECLARE_SYNC_SIGNAL(ChatRoomModelGUI*, getChatRoomModelGUI)
	DECLARE_SYNC_SIGNAL(ConferenceModel*, getConferenceModel)
	DECLARE_SYNC_SIGNAL(QString, addressesToString)
	DECLARE_SYNC_SIGNAL(QString, displayNamesToString)
	DECLARE_SYNC_SIGNAL(QString, usernamesToString)

};

#endif
