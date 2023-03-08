/*
 * Copyright (c) 2010-2023 Belledonne Communications SARL.
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

#ifndef CODE_HELPERS_GUI_H_
#define CODE_HELPERS_GUI_H_

// Use them in .hpp
#define DECLARE_SYNC_SLOT_CONST(RETURN_TYPE, FUNCTION_NAME) void FUNCTION_NAME ## Slot(RETURN_TYPE* result) const;
#define DECLARE_SYNC_SLOT(RETURN_TYPE, FUNCTION_NAME) void FUNCTION_NAME ## Slot(RETURN_TYPE* result);

// Use them in .cpp
#define DECLARE_SYNC_BODY_SLOT_CONST(RETURN_TYPE, FUNCTION_NAME, ROOT_CLASS) \
	void ROOT_CLASS::FUNCTION_NAME ## Slot(RETURN_TYPE * result) const{\
	*result = FUNCTION_NAME();\
	}
#define DECLARE_SYNC_BODY_SLOT(RETURN_TYPE, FUNCTION_NAME, ROOT_CLASS) \
	void ROOT_CLASS::FUNCTION_NAME ## Slot(RETURN_TYPE * result){\
	*result = FUNCTION_NAME();\
	}

// Use them in GUI.hpp
#define DECLARE_SYNC_SIGNAL(RETURN_TYPE, FUNCTION_NAME) RETURN_TYPE FUNCTION_NAME ## Sync(RETURN_TYPE* result) const;
#define DECLARE_SYNC_SIGNAL_ENUM(RETURN_TYPE, FUNCTION_NAME, ROOT_CLASS) ROOT_CLASS ## GUI::RETURN_TYPE FUNCTION_NAME ## Sync(ROOT_CLASS::RETURN_TYPE* result) const;

// Use them in GUI constructor
#define CONNECT_CORE_TO_GUI(FUNCTION_NAME, ROOT_CLASS) \
	connect(appModel, &ROOT_CLASS::FUNCTION_NAME, this, &ROOT_CLASS ## GUI::FUNCTION_NAME)
	
#define CONNECT_GUI_TO_CORE(FUNCTION_NAME, ROOT_CLASS) \
	connect(this, &ROOT_CLASS ## GUI::FUNCTION_NAME, appModel, &ROOT_CLASS::FUNCTION_NAME)

#define CONNECT_CORE_TO_GUI_ENUM(FUNCTION_NAME, ENUM_TYPE, ROOT_CLASS) \
	connect(appModel,&SettingsModel::FUNCTION_NAME, this, [&](ROOT_CLASS::ENUM_TYPE enumParam){emit FUNCTION_NAME((ROOT_CLASS ## GUI::ENUM_TYPE)enumParam);})

#define CONNECT_GUI_TO_CORE_ENUM(FUNCTION_NAME, ENUM_TYPE, ROOT_CLASS) \
	connect(this, &ROOT_CLASS ## GUI::FUNCTION_NAME, appModel, [appModel](ROOT_CLASS ## GUI::ENUM_TYPE enumParam){emit appModel->FUNCTION_NAME((ROOT_CLASS::ENUM_TYPE)enumParam);})

#define CONNECT_SYNC_TO_SLOT(FUNCTION_NAME, ROOT_CLASS) \
	connect(this, &ROOT_CLASS ## GUI::FUNCTION_NAME ## Sync, appModel, &ROOT_CLASS::FUNCTION_NAME ## Slot, Qt::BlockingQueuedConnection)

// Use them in GUI.cpp
#define DECLARE_GETTER(RETURN_TYPE, FUNCTION_NAME, ROOT_CLASS) \
	RETURN_TYPE ROOT_CLASS ## GUI::FUNCTION_NAME() const{\
	RETURN_TYPE result;\
	emit FUNCTION_NAME ## Sync(&result);\
	return result;\
	}
#define DECLARE_GETTER_ENUM(RETURN_TYPE, FUNCTION_NAME, ROOT_CLASS) \
	ROOT_CLASS ## GUI::RETURN_TYPE ROOT_CLASS ## GUI::FUNCTION_NAME() const{\
	ROOT_CLASS::RETURN_TYPE result;\
	emit FUNCTION_NAME ## Sync(&result);\
	return (ROOT_CLASS ## GUI::RETURN_TYPE) result;\
	}

#endif 
