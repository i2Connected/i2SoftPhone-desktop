﻿/*
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

#ifndef CALL_LISTENER_H
#define CALL_LISTENER_H

#include "utils/LinphoneEnums.hpp"

#include <QDateTime>

// =============================================================================


class CallModel;

class CallListener : public QObject, public linphone::CallListener {
Q_OBJECT
public:
	CallListener(QObject * parent = nullptr);
	virtual ~CallListener(){}
	
	virtual void onRemoteRecording(const std::shared_ptr<linphone::Call> & call, bool recording) override;
	virtual void onVideoDisplayErrorReceived(const std::shared_ptr<linphone::Call> & call, const int errorCode) override;
	
signals:
	void remoteRecording(const std::shared_ptr<linphone::Call> & call, bool recording);
	void videoDisplayErrorReceived(const std::shared_ptr<linphone::Call> & call, const int errorCode);
};

Q_DECLARE_METATYPE(CallListener*)
#endif
