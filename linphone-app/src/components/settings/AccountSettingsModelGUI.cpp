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

#include "config.h"

#include "AccountSettingsModelGUI.hpp"
#include "components/core/CoreManager.hpp"

// =============================================================================

AccountSettingsModelGUI::AccountSettingsModelGUI(QObject * parent) : QObject(parent){
	auto appModel = CoreManager::getInstance()->getAccountSettingsModel();
	// signals
	CONNECT_CORE_TO_GUI(usernameChanged, AccountSettingsModel);
	CONNECT_CORE_TO_GUI(sipAddressChanged, AccountSettingsModel);
	CONNECT_CORE_TO_GUI(fullSipAddressChanged, AccountSettingsModel);
	CONNECT_CORE_TO_GUI(registrationStateChanged, AccountSettingsModel);
	CONNECT_CORE_TO_GUI(conferenceUriChanged, AccountSettingsModel);
	CONNECT_CORE_TO_GUI(videoConferenceUriChanged, AccountSettingsModel);
	CONNECT_CORE_TO_GUI(limeServerUrlChanged, AccountSettingsModel);
	CONNECT_CORE_TO_GUI(primaryDisplayNameChanged, AccountSettingsModel);
	CONNECT_CORE_TO_GUI(primaryUsernameChanged, AccountSettingsModel);
	CONNECT_CORE_TO_GUI(primarySipAddressChanged, AccountSettingsModel);
	CONNECT_CORE_TO_GUI(accountsChanged, AccountSettingsModel);
	CONNECT_CORE_TO_GUI(accountSettingsUpdated, AccountSettingsModel);
	CONNECT_CORE_TO_GUI(defaultAccountChanged, AccountSettingsModel);
	CONNECT_CORE_TO_GUI(publishPresenceChanged, AccountSettingsModel);
	CONNECT_CORE_TO_GUI(defaultRegistrationChanged, AccountSettingsModel);
	
	// Setters/tools
	
	CONNECT_GUI_TO_CORE(setDefaultAccount, AccountSettingsModel);
	CONNECT_GUI_TO_CORE(setDefaultAccountFromSipAddress, AccountSettingsModel);
	CONNECT_GUI_TO_CORE(removeAccount, AccountSettingsModel);
	CONNECT_GUI_TO_CORE(addAuthInfo, AccountSettingsModel);
	CONNECT_GUI_TO_CORE(eraseAllPasswords, AccountSettingsModel);
	CONNECT_GUI_TO_CORE(setUsername, AccountSettingsModel);
	CONNECT_GUI_TO_CORE(setPrimaryUsername, AccountSettingsModel);
	CONNECT_GUI_TO_CORE(setPrimaryDisplayName, AccountSettingsModel);
	
	// Getters
	CONNECT_SYNC_TO_SLOT(getUsedSipAddressAsStringUriOnly, AccountSettingsModel);
	CONNECT_SYNC_TO_SLOT(getUsedSipAddressAsString, AccountSettingsModel);
	CONNECT_SYNC_TO_SLOT(getAccountDescription, AccountSettingsModel);
	CONNECT_SYNC_TO_SLOT(getConferenceUri, AccountSettingsModel);
	CONNECT_SYNC_TO_SLOT(getVideoConferenceUri, AccountSettingsModel);
	CONNECT_SYNC_TO_SLOT(getLimeServerUrl, AccountSettingsModel);
	connect(this, qOverload<bool *, const std::shared_ptr<linphone::Account> &, const QVariantMap &>(&AccountSettingsModelGUI::addOrUpdateAccountSync), appModel, qOverload<bool *, const std::shared_ptr<linphone::Account> &, const QVariantMap &>(&AccountSettingsModel::addOrUpdateAccountSlot), Qt::BlockingQueuedConnection);
	connect(this, qOverload<bool *, const QVariantMap &>(&AccountSettingsModelGUI::addOrUpdateAccountSync), appModel, qOverload<bool *, const QVariantMap &>(&AccountSettingsModel::addOrUpdateAccountSlot), Qt::BlockingQueuedConnection);
		
	CONNECT_SYNC_TO_SLOT(createAccount, AccountSettingsModel);
	CONNECT_SYNC_TO_SLOT(getPrimaryUsername, AccountSettingsModel);
	CONNECT_SYNC_TO_SLOT(getPrimaryDisplayName, AccountSettingsModel);
	CONNECT_SYNC_TO_SLOT(getPrimarySipAddress, AccountSettingsModel);
	CONNECT_SYNC_TO_SLOT(getUsername, AccountSettingsModel);
	CONNECT_SYNC_TO_SLOT(getDefaultAccountDomain, AccountSettingsModel);
	CONNECT_SYNC_TO_SLOT(getAccounts, AccountSettingsModel);
	CONNECT_SYNC_TO_SLOT(getRegistrationState, AccountSettingsModel);
	
}

AccountSettingsModelGUI::~AccountSettingsModelGUI(){
}

DECLARE_GETTER(QString, getUsedSipAddressAsStringUriOnly, AccountSettingsModel)
DECLARE_GETTER(QString, getUsedSipAddressAsString, AccountSettingsModel)
QVariantMap AccountSettingsModelGUI::getAccountDescription(const std::shared_ptr<linphone::Account> &account){
	QVariantMap result;
	emit getAccountDescriptionSync(&result, account);
	return result;
}
DECLARE_GETTER(QString, getConferenceUri, AccountSettingsModel)
DECLARE_GETTER(QString, getVideoConferenceUri, AccountSettingsModel)
DECLARE_GETTER(QString, getLimeServerUrl, AccountSettingsModel)
bool AccountSettingsModelGUI::addOrUpdateAccount(const std::shared_ptr<linphone::Account> &account, const QVariantMap &data){
	bool result;
	emit addOrUpdateAccountSync(&result, account, data);
	return result;
}
bool AccountSettingsModelGUI::addOrUpdateAccount(const QVariantMap &data) {
	bool result;
	emit addOrUpdateAccountSync(&result, data);
	return result;
}
std::shared_ptr<linphone::Account> AccountSettingsModelGUI::createAccount(const QString& assistantFile){
	std::shared_ptr<linphone::Account> result;
	emit createAccountSync(&result, assistantFile);
	return result;
}
DECLARE_GETTER(QString, getPrimaryUsername, AccountSettingsModel)
DECLARE_GETTER(QString, getPrimaryDisplayName, AccountSettingsModel)
DECLARE_GETTER(QString, getPrimarySipAddress, AccountSettingsModel)
DECLARE_GETTER(QString, getUsername, AccountSettingsModel)
DECLARE_GETTER(QString, getDefaultAccountDomain, AccountSettingsModel)
DECLARE_GETTER(QVariantList, getAccounts, AccountSettingsModel)
DECLARE_GETTER_ENUM(RegistrationState, getRegistrationState, AccountSettingsModel)

/*
bool SettingsModelGUI::isCheckForUpdateAvailable(){
	return SettingsModel::isCheckForUpdateAvailable();
}
*/