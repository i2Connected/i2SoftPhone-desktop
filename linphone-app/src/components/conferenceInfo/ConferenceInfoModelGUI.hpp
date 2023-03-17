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

#ifndef CONFERENCE_INFO_MODEL_GUI_H_
#define CONFERENCE_INFO_MODEL_GUI_H_

#include <linphone++/linphone.hh>
#include <QDateTime>
#include <QObject>
#include <QSharedPointer>
#include <QTimeZone>

#include "utils/LinphoneEnums.hpp"
#include "ConferenceInfoModel.hpp"

#include "utils/CodeHelpersGUI.hpp"
#include "components/other/timeZone/TimeZoneModel.hpp" // Note : didn't used by SDK, should be ok to used from GUI

#include "components/participant/ParticipantListModelGUI.hpp"

class ConferenceScheduler;

class ConferenceInfoModelGUI : public QObject {
	Q_OBJECT
	
public:
	Q_PROPERTY(TimeZoneModel * timeZoneModel READ getTimeZoneModel WRITE setTimeZoneModel NOTIFY timeZoneModelChanged)
	Q_PROPERTY(QDateTime dateTime READ getDateTimeSystem WRITE setDateTime NOTIFY dateTimeChanged)
	Q_PROPERTY(QDateTime dateTimeUtc READ getDateTimeUtc NOTIFY dateTimeChanged)
	Q_PROPERTY(int duration READ getDuration WRITE setDuration NOTIFY durationChanged)
	Q_PROPERTY(QDateTime endDateTime READ getEndDateTime NOTIFY dateTimeChanged)
	Q_PROPERTY(QString organizer READ getOrganizer WRITE setOrganizer NOTIFY organizerChanged)
	Q_PROPERTY(QString subject READ getSubject WRITE setSubject NOTIFY subjectChanged)
	Q_PROPERTY(QString description READ getDescription WRITE setDescription NOTIFY descriptionChanged)
	Q_PROPERTY(QString displayNamesToString READ displayNamesToString NOTIFY participantsChanged)
	Q_PROPERTY(QString uri READ getUri NOTIFY uriChanged)
	Q_PROPERTY(bool isScheduled READ isScheduled WRITE setIsScheduled NOTIFY isScheduledChanged)
	Q_PROPERTY(int inviteMode READ getInviteMode WRITE setInviteMode NOTIFY inviteModeChanged)
	Q_PROPERTY(int participantCount READ getParticipantCount NOTIFY participantsChanged)
	Q_PROPERTY(int allParticipantCount READ getAllParticipantCount NOTIFY participantsChanged)
	Q_PROPERTY(LinphoneEnums::ConferenceInfoState state READ getConferenceInfoState NOTIFY conferenceInfoStateChanged)
	Q_PROPERTY(LinphoneEnums::ConferenceSchedulerState conferenceSchedulerState READ getConferenceSchedulerState NOTIFY conferenceSchedulerStateChanged)
	
	ConferenceInfoModelGUI(QObject * parent = nullptr);
	ConferenceInfoModelGUI (ConferenceInfoModel * appModel, QObject * parent = nullptr);
	~ConferenceInfoModelGUI ();
//-------------------------------

	QDateTime getDateTimeUtc() const;
	QDateTime getDateTimeSystem() const;
	int getDuration() const;
	QDateTime getEndDateTime() const;
	QString getOrganizer() const;	
	QString getSubject() const;
	QString getDescription() const;
	Q_INVOKABLE QString displayNamesToString()const;
	QString getUri() const;
	bool isScheduled() const;
	int getInviteMode() const;
	
	Q_INVOKABLE int getParticipantCount()const;
	Q_INVOKABLE int getAllParticipantCount()const;
	Q_INVOKABLE TimeZoneModel* getTimeZoneModel() const;

	Q_INVOKABLE QVariantList getParticipants() const;
	Q_INVOKABLE QVariantList getAllParticipants() const;
	Q_INVOKABLE QString getIcalendarString() const;
	
	LinphoneEnums::ConferenceInfoState getConferenceInfoState() const;
	LinphoneEnums::ConferenceSchedulerState getConferenceSchedulerState() const;

signals:
	
	void setDateTime(const QDateTime& dateTime);
	void setDuration(const int& duration);
	void setSubject(const QString& subject);
	void setOrganizer(const QString& organizerAddress);
	void setDescription(const QString& description);
	void setIsScheduled(const bool& on);
	void setInviteMode(const int& modes);
	
	Q_INVOKABLE void setParticipants(ParticipantListModelGUI * participants);
	Q_INVOKABLE void setTimeZoneModel(TimeZoneModel * model);
	
// Tools
	Q_INVOKABLE void resetConferenceInfo();// Recreate a new conference info from factory
	Q_INVOKABLE void createConference(const int& securityLevel);
	Q_INVOKABLE void cancelConference();
	Q_INVOKABLE void deleteConferenceInfo();// Remove completly this conference info from DB
	

	void timeZoneModelChanged();
	void dateTimeChanged();
	void durationChanged();
	void organizerChanged();
	void subjectChanged();
	void descriptionChanged();
	void participantsChanged();
	void uriChanged();
	void isScheduledChanged();
	void inviteModeChanged();
	void conferenceInfoStateChanged();
	void conferenceSchedulerStateChanged();
	
	void conferenceCreated();
	void conferenceCreationFailed();
	void conferenceInfoChanged();
	void invitationsSent();
	void removed(bool byUser);

// Sync
	DECLARE_SYNC_SIGNAL(QDateTime, getDateTimeUtc)
	DECLARE_SYNC_SIGNAL(QDateTime, getDateTimeSystem)
	DECLARE_SYNC_SIGNAL(int, getDuration)
	DECLARE_SYNC_SIGNAL(QDateTime, getEndDateTime)
	DECLARE_SYNC_SIGNAL(QString, getOrganizer)
	DECLARE_SYNC_SIGNAL(QString, getSubject)
	DECLARE_SYNC_SIGNAL(QString, getDescription)
	DECLARE_SYNC_SIGNAL(QString, displayNamesToString)
	DECLARE_SYNC_SIGNAL(QString, getUri)
	DECLARE_SYNC_SIGNAL(QString, getIcalendarString);
	DECLARE_SYNC_SIGNAL(bool, isScheduled)
	DECLARE_SYNC_SIGNAL(int, getInviteMode)
	DECLARE_SYNC_SIGNAL(QVariantList, getParticipants);
	DECLARE_SYNC_SIGNAL(QVariantList, getAllParticipants);
	DECLARE_SYNC_SIGNAL(LinphoneEnums::ConferenceInfoState, getConferenceInfoState)
	DECLARE_SYNC_SIGNAL(LinphoneEnums::ConferenceSchedulerState, getConferenceSchedulerState)
	DECLARE_SYNC_SIGNAL(int, getParticipantCount)
	DECLARE_SYNC_SIGNAL(int, getAllParticipantCount)
	DECLARE_SYNC_SIGNAL(TimeZoneModel*, getTimeZoneModel)

};

Q_DECLARE_METATYPE(ConferenceInfoModelGUI*)

#endif
