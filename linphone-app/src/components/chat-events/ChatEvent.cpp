﻿/*
 * Copyright (c) 2021 Belledonne Communications SARL.
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

#include <QQmlApplicationEngine>

#include "app/App.hpp"

#include "ChatEvent.hpp"

// =============================================================================

ChatEvent::ChatEvent (ChatRoomModel::EntryType type, QObject * parent) : QObject(parent){
	mType = type;
}
ChatEvent::~ChatEvent(){
}

QDateTime ChatEvent::getTimestamp() const{
	return mTimestamp;
}

QDateTime ChatEvent::getReceivedTimestamp() const{
	return mReceivedTimestamp;
}

void ChatEvent::setTimestamp(const QDateTime& timestamp){
	mTimestamp = timestamp;
}

void ChatEvent::setReceivedTimestamp(const QDateTime& timestamp){
	mReceivedTimestamp = timestamp;
}

void ChatEvent::deleteEvent(){
}