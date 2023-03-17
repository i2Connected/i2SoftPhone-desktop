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

#ifndef CONTACT_MODEL_GUI_H_
#define CONTACT_MODEL_GUI_H_

#include "components/presence/Presence.hpp"
#include "utils/LinphoneEnums.hpp"

#include <QSharedPointer>

#include "utils/CodeHelpersGUI.hpp"
// =============================================================================

class ContactModel;
class VcardModelGUI;

class ContactModelGUI : public QObject {
	Q_OBJECT
	
	Q_PROPERTY(Presence::PresenceStatus presenceStatus READ getPresenceStatus NOTIFY presenceStatusChanged)
	Q_PROPERTY(Presence::PresenceLevel presenceLevel READ getPresenceLevel NOTIFY presenceLevelChanged)
	Q_PROPERTY(VcardModelGUI * vcard READ getVcardModel WRITE setVcardModel NOTIFY contactUpdated)
	
public:
	ContactModelGUI (ContactModel * appModel, QObject * parent = nullptr);
	virtual ~ContactModelGUI();
	
	VcardModelGUI *getVcardModel () const;
	void setVcardModel (VcardModelGUI *vcardModel);
	
	Q_INVOKABLE VcardModelGUI *cloneVcardModel () const;
	Presence::PresenceLevel getPresenceLevel () const;
	Q_INVOKABLE bool hasCapability(const LinphoneEnums::FriendCapability& capability);
	
signals:
	void contactUpdated ();
	void presenceStatusChanged (Presence::PresenceStatus status);
	void presenceLevelChanged (Presence::PresenceLevel level);
	void sipAddressAdded (const QString &sipAddress);
	void sipAddressRemoved (const QString &sipAddress);
	
// Sync
	DECLARE_SYNC_SIGNAL(Presence::PresenceLevel, getPresenceLevel)
	
private:
	Presence::PresenceStatus getPresenceStatus () const;
	
};

Q_DECLARE_METATYPE(ContactModelGUI *);

#endif // CONTACT_MODEL_GUI_H_
