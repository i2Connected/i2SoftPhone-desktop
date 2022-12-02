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

#include "LTime.hpp"

#include "app/App.hpp"

#include <QLocale>

// =============================================================================

LTime::LTime(QObject *parent) : QObject(parent) {
}
LTime::LTime(const QTime& time, QObject *parent) : QObject(parent)
	, mTime(time){	
}
LTime::LTime(const int& hour, const int& minute, const int& second, QObject *parent) : QObject(parent)
	, mTime(hour, minute, second){	
}

LTime * LTime::create(){
	return new LTime(QTime::currentTime());
}

LTime * LTime::create(const QDateTime& dateTime){
	return new LTime(dateTime.time());
}

LTime * LTime::create(const int& hour, const int& minute, const int& second){
	return new LTime(hour, minute, second);
}

QString LTime::toTimeString(const QString& format) const{
	if(format == "")
		return QLocale().toString(mTime, QLocale::ShortFormat);
	else
		return QLocale().toString(mTime,format);
}

QTime LTime::getTime() const{
	return mTime;
}

int LTime::getSecond()const{
	return mTime.second();
}

int LTime::getMinute()const{
	return mTime.minute();
}

int LTime::getHour()const{
	return mTime.hour();
}

void LTime::setSecond(const int& data){
	if(getSecond() != data){
		mTime = QTime(getHour(), getMinute(), data);
		emit secondChanged();
	}
}
void LTime::setMinute(const int& data){
	if(getMinute() != data){
		mTime = QTime(getHour(), data, getSecond());
		emit minuteChanged();
	}
}
void LTime::setHour(const int& data){
	if(getHour() != data){
		mTime = QTime(data, getMinute(), getSecond());
		emit hourChanged();
	}
}