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

#include "LDateTime.hpp"

#include "LDate.hpp"
#include "LTime.hpp"
#include "app/App.hpp"

#include <QLocale>

// =============================================================================

LDateTime::LDateTime(QObject *parent) : QObject(parent) {
}
LDateTime::LDateTime(const QDateTime& dateTime, QObject *parent) : QObject(parent)
	, mDateTime(dateTime){	
}
LDateTime::LDateTime(LDate * date, LTime * time, QObject *parent) : QObject(parent)
	, mDateTime(date->getDate(), time->getTime(), Qt::UTC ){
		
	QDateTime a(date->getDate(), time->getTime());
	QDateTime b(date->getDate(), time->getTime(), Qt::OffsetFromUTC);
	qWarning() << time->toTimeString("hh:mm") << "/" << mDateTime.time().toString("hh:mm:") << mDateTime.toString("hh:mm") << "/" << mDateTime.toMSecsSinceEpoch()
		<< " == " << a.time().toString("hh:mm") << "/" << a.toString("hh:mm")<< "/" << a.toMSecsSinceEpoch()
		<< " == " << b.time().toString("hh:mm") << "/" << b.toString("hh:mm")<< "/" << b.toMSecsSinceEpoch()
	;
		
}
LDateTime::LDateTime(const int& year, const int& month, const int& day, const int& hour, const int& minute, const int& second, QObject *parent) : QObject(parent)
	, mDateTime(QDate(year, month, day), QTime(hour, minute, second)){
}

LDateTime * LDateTime::create(){
	return new LDateTime(QDateTime::currentDateTime());
}

LDateTime * LDateTime::create(LDate * date, LTime * time){
	return new LDateTime(date, time);
}

LDateTime * LDateTime::create(const int& year, const int& month, const int& day, const int& hour, const int& minute, const int& second){
	return new LDateTime(year, month, day, hour, minute, second);
}

QString LDateTime::toDateTimeString(const QString& format) const{
	if(format == "")
		return QLocale().toString(mDateTime, QLocale::ShortFormat);
	else
		return QLocale().toString(mDateTime,format);
}

bool LDateTime::isToday() const{
	return mDateTime.date() == QDate::currentDate();
}

bool LDateTime::isFuture() const{
	return mDateTime > QDateTime::currentDateTime();
}


int LDateTime::getDay()const{
	return mDateTime.date().day();
}

int LDateTime::getWeekDay()const{
	return mDateTime.date().dayOfWeek();
}

int LDateTime::getMonth()const{
	return mDateTime.date().month();
}

int LDateTime::getYear()const{
	return mDateTime.date().year();
}


int LDateTime::getSecond()const{
	return mDateTime.time().second();
}

int LDateTime::getMinute()const{
	return mDateTime.time().minute();
}

int LDateTime::getHour()const{
	return mDateTime.time().hour();
}

//-----------------------------------------------------------------------

void LDateTime::setDay(const int& data){
	if(getDay() != data){
		mDateTime.setDate(QDate(getYear(), getMonth(), data));
		emit dayChanged();
		emit dateTimeChanged();
	}
}
void LDateTime::setMonth(const int& data){
	if(getMonth() != data){
		mDateTime.setDate(QDate(getYear(), data, getDay()));
		emit monthChanged();
		emit dateTimeChanged();
	}
}
void LDateTime::setYear(const int& data){
	if(getYear() != data){
		mDateTime.setDate(QDate(data, getMonth(), getDay()));
		emit yearChanged();
		emit dateTimeChanged();
	}
}

void LDateTime::setSecond(const int& data){
	if(getSecond() != data){
		mDateTime.setTime(QTime(getHour(), getMinute(), data));
		emit secondChanged();
		emit dateTimeChanged();
	}
}
void LDateTime::setMinute(const int& data){
	if(getMinute() != data){
		mDateTime.setTime(QTime(getHour(), data, getSecond()));
		emit minuteChanged();
		emit dateTimeChanged();
	}
}
void LDateTime::setHour(const int& data){
	if(getHour() != data){
		mDateTime.setTime(QTime(data, getMinute(), getSecond()));
		emit hourChanged();
		emit dateTimeChanged();
	}
}