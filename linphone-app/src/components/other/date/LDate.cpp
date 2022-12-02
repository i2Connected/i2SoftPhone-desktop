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

#include "LDate.hpp"

#include "app/App.hpp"
#include "utils/Utils.hpp"

#include <QLocale>

// =============================================================================

LDate::LDate(QObject *parent) : QObject(parent) {
}
LDate::LDate(const QDate& date, QObject *parent) : QObject(parent)
	, mDate(date){	
}
LDate::LDate(const int& year, const int& month, const int& day, QObject *parent) : QObject(parent)
	, mDate(year, month, day){	
}

LDate * LDate::create(){
	return new LDate(QDate::currentDate());
}

LDate * LDate::create(const QDateTime& dateTime){
	return new LDate(Utils::getOffsettedUTC(dateTime).date());
}

LDate * LDate::create(const int& year, const int& month, const int& day){
	return new LDate(year, month, day);
}

QString LDate::toDateString(const QString& format) const{
	if(format == "")
		return QLocale().toString(mDate, QLocale::ShortFormat);
	else
		return QLocale().toString(mDate,format);
}

bool LDate::isToday() const{
	return mDate == QDate::currentDate();
}

bool LDate::isFuture() const{
	return mDate > QDate::currentDate();
}

bool LDate::isGreatherThan(LDate* date) const{
	return date && mDate >= date->mDate;
}

bool LDate::isEqual(LDate* date) const{
	return date && mDate == date->mDate;
}

QDate LDate::getDate()const{
	return mDate;
}

int LDate::getDay()const{
	return mDate.day();
}

int LDate::getWeekDay()const{
	return mDate.dayOfWeek();
}

int LDate::getMonth()const{
	return mDate.month();
}

int LDate::getYear()const{
	return mDate.year();
}

void LDate::setDay(const int& data){
	if(getDay() != data){
		mDate = QDate(getYear(), getMonth(), data);
		emit dayChanged();
	}
}
void LDate::setMonth(const int& data){
	if(getMonth() != data){
		mDate = QDate(getYear(), data, getDay());
		emit monthChanged();
	}
}
void LDate::setYear(const int& data){
	if(getYear() != data){
		mDate = QDate(data, getMonth(), getDay());
		emit yearChanged();
	}
}