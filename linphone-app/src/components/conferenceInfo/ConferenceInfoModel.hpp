/*
 * Copyright (c) 2022 Belledonne Communications SARL.
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

#ifndef CONFERENCE_INFO_MODEL_H_
#define CONFERENCE_INFO_MODEL_H_

#include <linphone++/linphone.hh>
#include <QDateTime>
#include <QObject>
#include <QSharedPointer>
#include <QTimeZone>

#include "utils/LinphoneEnums.hpp"

class ParticipantListModel;
class ParticipantListModelGUI;
class ConferenceScheduler;
class TimeZoneModel;

#include "utils/CodeHelpersGUI.hpp"

class ConferenceInfoModel : public QObject {
	Q_OBJECT
	
public:
	static QSharedPointer<ConferenceInfoModel> create(std::shared_ptr<linphone::ConferenceInfo> conferenceInfo);
	ConferenceInfoModel (QObject * parent = nullptr);
	ConferenceInfoModel (std::shared_ptr<linphone::ConferenceInfo> conferenceInfo, QObject * parent = nullptr);
	~ConferenceInfoModel ();
	std::shared_ptr<linphone::ConferenceInfo> getConferenceInfo();
	static std::shared_ptr<linphone::ConferenceInfo> findConferenceInfo(const std::shared_ptr<const linphone::ConferenceInfo> & conferenceInfo);
	
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
	QVariantList getParticipants() const;
	QVariantList getAllParticipants() const;
	int getParticipantCount()const;
	int getAllParticipantCount()const;
	TimeZoneModel* getTimeZoneModel() const;
	QString getIcalendarString() const;
	LinphoneEnums::ConferenceInfoState getConferenceInfoState() const;
	LinphoneEnums::ConferenceSchedulerState getConferenceSchedulerState() const;
	
	void setDateTime(const QDateTime& dateTime);
	void setDuration(const int& duration);
	void setSubject(const QString& subject);
	void setOrganizer(const QString& organizerAddress);
	void setDescription(const QString& description);
	void setIsScheduled(const bool& on);
	void setInviteMode(const int& modes);
	
	void setParticipants(ParticipantListModelGUI * participantsGUI);
	void setTimeZoneModel(TimeZoneModel * model);
	void setConferenceInfo(std::shared_ptr<linphone::ConferenceInfo> conferenceInfo);
	
// Tools
	void resetConferenceInfo();// Recreate a new conference info from factory
	void createConference(const int& securityLevel);
	void cancelConference();
	void deleteConferenceInfo();// Remove completly this conference info from DB

// SCHEDULER
	
	virtual void onConferenceSchedulerStateChanged(linphone::ConferenceScheduler::State state);
	virtual void onInvitationsSent(const std::list<std::shared_ptr<linphone::Address>> & failedInvitations);
	
signals:
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
	
private:
	std::shared_ptr<linphone::ConferenceInfo> mConferenceInfo;
	QSharedPointer<ConferenceScheduler> mConferenceScheduler= nullptr;
	QTimeZone mTimeZone;
	
	bool mIsScheduled = true;
	int mInviteMode = 0;
	bool mRemoveRequested = false;// true if user has request its deletion from DB
	linphone::ConferenceScheduler::State  mLastConferenceSchedulerState = linphone::ConferenceScheduler::State::Idle;// Workaround for missing getter in scheduler.

public slots:
	DECLARE_SYNC_SLOT_CONST(QDateTime, getDateTimeUtc);
	DECLARE_SYNC_SLOT_CONST(QDateTime, getDateTimeSystem);
	DECLARE_SYNC_SLOT_CONST(int, getDuration);
	DECLARE_SYNC_SLOT_CONST(QDateTime, getEndDateTime);
	DECLARE_SYNC_SLOT_CONST(QString, getOrganizer);
	DECLARE_SYNC_SLOT_CONST(QString, getSubject);
	DECLARE_SYNC_SLOT_CONST(QString, getDescription);
	DECLARE_SYNC_SLOT_CONST(QString, displayNamesToString);
	DECLARE_SYNC_SLOT_CONST(QString, getUri);
	DECLARE_SYNC_SLOT_CONST(bool, isScheduled);
	DECLARE_SYNC_SLOT_CONST(int, getInviteMode);
	DECLARE_SYNC_SLOT_CONST(int, getParticipantCount);
	DECLARE_SYNC_SLOT_CONST(int, getAllParticipantCount);
	DECLARE_SYNC_SLOT_CONST(TimeZoneModel*, getTimeZoneModel);
	DECLARE_SYNC_SLOT_CONST(QVariantList, getParticipants);
	DECLARE_SYNC_SLOT_CONST(QVariantList, getAllParticipants);
	DECLARE_SYNC_SLOT_CONST(QString, getIcalendarString);
	DECLARE_SYNC_SLOT_CONST(LinphoneEnums::ConferenceInfoState, getConferenceInfoState);
	DECLARE_SYNC_SLOT_CONST(LinphoneEnums::ConferenceSchedulerState, getConferenceSchedulerState);
};

#endif
