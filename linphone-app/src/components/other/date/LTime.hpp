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
#ifndef TIME_H_
#define TIME_H_

// Used to replace QML Date because of Times bugs (local timezones that changes date)

#include <QObject>
#include <QTime>
// =============================================================================

class LTime : public QObject {
	Q_OBJECT
public:
	Q_PROPERTY(int second READ getSecond WRITE setSecond NOTIFY secondChanged)
	Q_PROPERTY(int minute READ getMinute WRITE setMinute NOTIFY minuteChanged)
	Q_PROPERTY(int hour READ getHour WRITE setHour NOTIFY hourChanged)
	
	LTime (QObject *parent = Q_NULLPTR);
	LTime(const QTime& date, QObject *parent = Q_NULLPTR);
	LTime(const int& hour, const int& minute, const int& second, QObject *parent = Q_NULLPTR);
	
	Q_INVOKABLE static LTime* create();
	Q_INVOKABLE static LTime* create(const QDateTime& dateTime);
	Q_INVOKABLE static LTime* create(const int& hour, const int& minute, const int& second);
	
	Q_INVOKABLE QString toTimeString(const QString& format = "") const;// Do not use toString as it's a conflict with JS toString()
	
	QTime getTime() const;
	int getSecond()const;
	int getMinute()const;
	int getHour()const;
	
	void setSecond(const int& data);
	void setMinute(const int& data);
	void setHour(const int& data);
	
signals:

	void secondChanged();
	void minuteChanged();
	void hourChanged();

private:
	QTime mTime;
};
Q_DECLARE_METATYPE(LTime*);

#endif
