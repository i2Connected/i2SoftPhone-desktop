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

#include <QQmlApplicationEngine>

#include "app/App.hpp"

#include "ContactModelGUI.hpp"
#include "ContactModel.hpp"
#include "VcardModel.hpp"

// =============================================================================

using namespace std;

ContactModelGUI::ContactModelGUI (ContactModel * appModel, QObject * parent) : QObject(parent) {
// Signals
	CONNECT_CORE_TO_GUI(contactUpdated, ContactModel);
	CONNECT_CORE_TO_GUI(presenceStatusChanged, ContactModel);
	CONNECT_CORE_TO_GUI(presenceLevelChanged, ContactModel);
	CONNECT_CORE_TO_GUI(sipAddressAdded, ContactModel);
	CONNECT_CORE_TO_GUI(sipAddressRemoved, ContactModel);
	
// Setters/tools
	CONNECT_GUI_TO_CORE(setDefaultAccount, ContactModel);

}


ContactModelGUI::~ContactModelGUI(){
}
