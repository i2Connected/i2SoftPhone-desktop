/*
 * Copyright (c) 2023 Belledonne Communications SARL.
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

#include "ConferenceInfoModelGUI.hpp"
// =============================================================================
ConferenceInfoModelGUI::ConferenceInfoModelGUI(QObject * parent) : QObject(parent){

}
ConferenceInfoModelGUI::ConferenceInfoModelGUI (ConferenceInfoModel * appModel, QObject * parent) : QObject(parent){
// Signals
	CONNECT_CORE_TO_GUI(timeZoneModelChanged, ConferenceInfoModel);
	CONNECT_CORE_TO_GUI(dateTimeChanged, ConferenceInfoModel);
	CONNECT_CORE_TO_GUI(durationChanged, ConferenceInfoModel);
	CONNECT_CORE_TO_GUI(organizerChanged, ConferenceInfoModel);
	CONNECT_CORE_TO_GUI(subjectChanged, ConferenceInfoModel);
	CONNECT_CORE_TO_GUI(descriptionChanged, ConferenceInfoModel);
	CONNECT_CORE_TO_GUI(participantsChanged, ConferenceInfoModel);
	CONNECT_CORE_TO_GUI(uriChanged, ConferenceInfoModel);
	CONNECT_CORE_TO_GUI(isScheduledChanged, ConferenceInfoModel);
	CONNECT_CORE_TO_GUI(inviteModeChanged, ConferenceInfoModel);
	CONNECT_CORE_TO_GUI(conferenceInfoStateChanged, ConferenceInfoModel);
	CONNECT_CORE_TO_GUI(conferenceSchedulerStateChanged, ConferenceInfoModel);
	CONNECT_CORE_TO_GUI(conferenceCreated, ConferenceInfoModel);
	CONNECT_CORE_TO_GUI(conferenceCreationFailed, ConferenceInfoModel);
	CONNECT_CORE_TO_GUI(conferenceInfoChanged, ConferenceInfoModel);
	CONNECT_CORE_TO_GUI(invitationsSent, ConferenceInfoModel);
	CONNECT_CORE_TO_GUI(removed, ConferenceInfoModel);
	
// Setters/tools
	CONNECT_GUI_TO_CORE(setDateTime, ConferenceInfoModel);
	CONNECT_GUI_TO_CORE(setDuration, ConferenceInfoModel);
	CONNECT_GUI_TO_CORE(setSubject, ConferenceInfoModel);
	CONNECT_GUI_TO_CORE(setOrganizer, ConferenceInfoModel);
	CONNECT_GUI_TO_CORE(setDescription, ConferenceInfoModel);
	CONNECT_GUI_TO_CORE(setIsScheduled, ConferenceInfoModel);
	CONNECT_GUI_TO_CORE(setInviteMode, ConferenceInfoModel);
	CONNECT_GUI_TO_CORE(setParticipants, ConferenceInfoModel);
	CONNECT_GUI_TO_CORE(setTimeZoneModel, ConferenceInfoModel);
	CONNECT_GUI_TO_CORE(resetConferenceInfo, ConferenceInfoModel);
	CONNECT_GUI_TO_CORE(createConference, ConferenceInfoModel);
	CONNECT_GUI_TO_CORE(cancelConference, ConferenceInfoModel);
	CONNECT_GUI_TO_CORE(deleteConferenceInfo, ConferenceInfoModel);
	
	// Getters
	CONNECT_SYNC_TO_SLOT(getDateTimeUtc, ConferenceInfoModel);
	CONNECT_SYNC_TO_SLOT(getDateTimeSystem, ConferenceInfoModel);
	CONNECT_SYNC_TO_SLOT(getDuration, ConferenceInfoModel);
	CONNECT_SYNC_TO_SLOT(getEndDateTime, ConferenceInfoModel);
	CONNECT_SYNC_TO_SLOT(getOrganizer, ConferenceInfoModel);
	CONNECT_SYNC_TO_SLOT(getSubject, ConferenceInfoModel);
	CONNECT_SYNC_TO_SLOT(getDescription, ConferenceInfoModel);
	CONNECT_SYNC_TO_SLOT(displayNamesToString, ConferenceInfoModel);
	CONNECT_SYNC_TO_SLOT(getUri, ConferenceInfoModel);
	CONNECT_SYNC_TO_SLOT(isScheduled, ConferenceInfoModel);
	CONNECT_SYNC_TO_SLOT(getInviteMode, ConferenceInfoModel);
	CONNECT_SYNC_TO_SLOT(getParticipantCount, ConferenceInfoModel);
	CONNECT_SYNC_TO_SLOT(getAllParticipantCount, ConferenceInfoModel);
	CONNECT_SYNC_TO_SLOT(getTimeZoneModel, ConferenceInfoModel);
	CONNECT_SYNC_TO_SLOT(getParticipants, ConferenceInfoModel);
	CONNECT_SYNC_TO_SLOT(getAllParticipants, ConferenceInfoModel);
	CONNECT_SYNC_TO_SLOT(getIcalendarString, ConferenceInfoModel);
	CONNECT_SYNC_TO_SLOT(getConferenceInfoState, ConferenceInfoModel);
	CONNECT_SYNC_TO_SLOT(getConferenceSchedulerState, ConferenceInfoModel);
}

ConferenceInfoModelGUI::~ConferenceInfoModelGUI () {
}


DEFINE_GETTER(QDateTime, getDateTimeUtc, ConferenceInfoModel);
DEFINE_GETTER(QDateTime, getDateTimeSystem, ConferenceInfoModel);
DEFINE_GETTER(int, getDuration, ConferenceInfoModel);
DEFINE_GETTER(QDateTime, getEndDateTime, ConferenceInfoModel);
DEFINE_GETTER(QString, getOrganizer, ConferenceInfoModel);
DEFINE_GETTER(QString, getSubject, ConferenceInfoModel);
DEFINE_GETTER(QString, getDescription, ConferenceInfoModel);
DEFINE_GETTER(QString, displayNamesToString, ConferenceInfoModel);
DEFINE_GETTER(QString, getUri, ConferenceInfoModel);
DEFINE_GETTER(bool, isScheduled, ConferenceInfoModel);
DEFINE_GETTER(int, getInviteMode, ConferenceInfoModel);
DEFINE_GETTER(int, getParticipantCount, ConferenceInfoModel);
DEFINE_GETTER(int, getAllParticipantCount, ConferenceInfoModel);
DEFINE_GETTER(TimeZoneModel*, getTimeZoneModel, ConferenceInfoModel);
DEFINE_GETTER(QVariantList, getParticipants, ConferenceInfoModel);
DEFINE_GETTER(QVariantList, getAllParticipants, ConferenceInfoModel);
DEFINE_GETTER(QString, getIcalendarString, ConferenceInfoModel);
DEFINE_GETTER(LinphoneEnums::ConferenceInfoState, getConferenceInfoState, ConferenceInfoModel);
DEFINE_GETTER(LinphoneEnums::ConferenceSchedulerState, getConferenceSchedulerState, ConferenceInfoModel);

