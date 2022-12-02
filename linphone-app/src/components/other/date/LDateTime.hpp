/*
 * Copyright (c) 2010-2022 Belledonne Communications SARL.
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
#ifndef DATE_TIME_H_
#define DATE_TIME_H_

// Used to replace QML Date because of Times bugs (local timezones that changes date)

#include <QObject>
#include <QDate>
// =============================================================================

class LDate;
class LTime;

// Note: we don't inherit because we are using a QDateTime and not : QDate and QTime
class LDateTime : public QObject {
	Q_OBJECT
public:
	Q_PROPERTY(int day READ getDay WRITE setDay NOTIFY dayChanged)
	Q_PROPERTY(int weekday READ getWeekDay NOTIFY dayChanged)
	Q_PROPERTY(int month READ getMonth WRITE setMonth NOTIFY monthChanged)
	Q_PROPERTY(int year READ getYear WRITE setYear NOTIFY yearChanged)
	Q_PROPERTY(int second READ getSecond WRITE setSecond NOTIFY secondChanged)
	Q_PROPERTY(int minute READ getMinute WRITE setMinute NOTIFY minuteChanged)
	Q_PROPERTY(int hour READ getHour WRITE setHour NOTIFY hourChanged)
	Q_PROPERTY(QDateTime dateTime MEMBER mDateTime NOTIFY dateTimeChanged)

	LDateTime (QObject *parent = Q_NULLPTR);
	LDateTime(const QDateTime& date, QObject *parent = Q_NULLPTR);
	LDateTime(LDate * date, LTime * time, QObject *parent = Q_NULLPTR);
	LDateTime(const int& year, const int& month, const int& day, const int& hour, const int& minute, const int& second, QObject *parent = Q_NULLPTR);
	
	Q_INVOKABLE static LDateTime * create();
	Q_INVOKABLE static LDateTime * create(LDate * date, LTime * time);
	Q_INVOKABLE static LDateTime * create(const int& year, const int& month, const int& day, const int& hout, const int& minute, const int& second);
	
	Q_INVOKABLE QString toDateTimeString(const QString& format = "") const;// Do not use toString as it's a conflict with JS toString()
	Q_INVOKABLE bool isToday() const;
	Q_INVOKABLE bool isFuture() const;
	
	int getDay()const;
	int getWeekDay()const;
	int getMonth()const;
	int getYear()const;
	
	int getSecond()const;
	int getMinute()const;
	int getHour()const;
//-------------------------------------
	void setDay(const int& data);
	void setMonth(const int& data);
	void setYear(const int& data);
	
	void setSecond(const int& data);
	void setMinute(const int& data);
	void setHour(const int& data);
	
signals:

	void dayChanged();
	void monthChanged();
	void yearChanged();
	
	void secondChanged();
	void minuteChanged();
	void hourChanged();
	
	void dateTimeChanged();

private:
	QDateTime mDateTime;
};
Q_DECLARE_METATYPE(LDateTime*);

#endif
