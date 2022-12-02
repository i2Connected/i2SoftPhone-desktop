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
#ifndef DATE_H_
#define DATE_H_

// Used to replace QML Date because of Times bugs (local timezones that changes date)

#include <QObject>
#include <QDate>
// =============================================================================

class LDate : public QObject {
	Q_OBJECT
public:
	Q_PROPERTY(int day READ getDay WRITE setDay NOTIFY dayChanged)
	Q_PROPERTY(int weekday READ getWeekDay NOTIFY dayChanged)
	Q_PROPERTY(int month READ getMonth WRITE setMonth NOTIFY monthChanged)
	Q_PROPERTY(int year READ getYear WRITE setYear NOTIFY yearChanged)

	LDate (QObject *parent = Q_NULLPTR);
	LDate(const QDate& date, QObject *parent = Q_NULLPTR);
	LDate(const int& year, const int& month, const int& day, QObject *parent = Q_NULLPTR);
	
	Q_INVOKABLE static LDate * create();
	Q_INVOKABLE static LDate * create(const QDateTime& dateTime);
	Q_INVOKABLE static LDate * create(const int& year, const int& month, const int& day);
	
	Q_INVOKABLE QString toDateString(const QString& format = "") const;// Do not use toString as it's a conflict with JS toString()
	Q_INVOKABLE bool isToday() const;
	Q_INVOKABLE bool isFuture() const;
	Q_INVOKABLE bool isGreatherThan(LDate* date) const;
	Q_INVOKABLE bool isEqual(LDate* date) const;
	
	QDate getDate()const;
	int getDay()const;
	int getWeekDay()const;
	int getMonth()const;
	int getYear()const;
	
	void setDay(const int& data);
	void setMonth(const int& data);
	void setYear(const int& data);
	
signals:

	void dayChanged();
	void monthChanged();
	void yearChanged();

private:
	QDate mDate;
};
Q_DECLARE_METATYPE(LDate*);

#endif
