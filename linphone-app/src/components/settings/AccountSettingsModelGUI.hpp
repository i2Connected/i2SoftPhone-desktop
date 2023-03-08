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

#ifndef ACCOUNT_SETTINGS_MODEL_GUI_H_
#define ACCOUNT_SETTINGS_MODEL_GUI_H_

#include <linphone++/linphone.hh>
#include <QObject>
#include <QString>
#include <QVariantMap>
#include <QVariantList>
#include <QVector>

#include "utils/CodeHelpersGUI.hpp"
#include "AccountSettingsModel.hpp"

// =============================================================================

class AccountSettingsModelGUI : public QObject {
	Q_OBJECT
	
	// Selected account.
	Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY usernameChanged)
	Q_PROPERTY(QString sipAddress READ getUsedSipAddressAsStringUriOnly NOTIFY sipAddressChanged)
	Q_PROPERTY(QString fullSipAddress READ getUsedSipAddressAsString NOTIFY fullSipAddressChanged)
	Q_PROPERTY(RegistrationState registrationState READ getRegistrationState NOTIFY registrationStateChanged)
	
	Q_PROPERTY(QString conferenceUri READ getConferenceUri NOTIFY conferenceUriChanged)
	Q_PROPERTY(QString videoConferenceUri READ getVideoConferenceUri NOTIFY videoConferenceUriChanged)
	Q_PROPERTY(QString limeServerUrl READ getLimeServerUrl NOTIFY limeServerUrlChanged)
	
	// Default info.
	Q_PROPERTY(QString primaryDisplayName READ getPrimaryDisplayName WRITE setPrimaryDisplayName NOTIFY primaryDisplayNameChanged)
	Q_PROPERTY(QString primaryUsername READ getPrimaryUsername WRITE setPrimaryUsername NOTIFY primaryUsernameChanged)
	Q_PROPERTY(QString primarySipAddress READ getPrimarySipAddress NOTIFY primarySipAddressChanged)

	Q_PROPERTY(QString defaultAccountDomain READ getDefaultAccountDomain NOTIFY defaultAccountChanged)
	
	Q_PROPERTY(QVariantList accounts READ getAccounts NOTIFY accountsChanged)
	
public:
	enum RegistrationState {
		RegistrationStateRegistered,
		RegistrationStateNotRegistered,
		RegistrationStateInProgress,
		RegistrationStateNoAccount,
	};
	Q_ENUM(RegistrationState);
	
	AccountSettingsModelGUI (QObject *parent = Q_NULLPTR);
	~AccountSettingsModelGUI();
	
	QString getUsedSipAddressAsStringUriOnly () const;
	QString getUsedSipAddressAsString () const;
	Q_INVOKABLE QVariantMap getAccountDescription (const std::shared_ptr<linphone::Account> &account);
	QString getConferenceUri() const;
	QString getVideoConferenceUri() const;
	QString getLimeServerUrl() const;
	Q_INVOKABLE bool addOrUpdateAccount (const std::shared_ptr<linphone::Account> &account, const QVariantMap &data);
	Q_INVOKABLE bool addOrUpdateAccount (const QVariantMap &data);// Create default account and apply data
	Q_INVOKABLE std::shared_ptr<linphone::Account> createAccount (const QString& assistantFile);
	QString getPrimaryUsername () const;
	QString getPrimaryDisplayName () const;
	QString getPrimarySipAddress () const;
	QString getUsername () const;
	QString getDefaultAccountDomain () const;
	QVariantList getAccounts () const;
	AccountSettingsModelGUI::RegistrationState getRegistrationState () const;
	
signals:
	Q_INVOKABLE void setDefaultAccount (const std::shared_ptr<linphone::Account> &account = nullptr);
	Q_INVOKABLE void setDefaultAccountFromSipAddress (const QString &sipAddress);
	Q_INVOKABLE void removeAccount (const std::shared_ptr<linphone::Account> &account);
	Q_INVOKABLE void addAuthInfo (
			const std::shared_ptr<linphone::AuthInfo> &authInfo,
			const QString &password,
			const QString &userId
			);
	Q_INVOKABLE void eraseAllPasswords ();
	void setUsername (const QString &username);
	void setPrimaryUsername (const QString &username);
	void setPrimaryDisplayName (const QString &displayName);
	
signals:
	
	void usernameChanged();
	void sipAddressChanged();
	void fullSipAddressChanged();
	void registrationStateChanged();
	void conferenceUriChanged();
	void videoConferenceUriChanged();
	void limeServerUrlChanged();
	void primaryDisplayNameChanged();
	void primaryUsernameChanged();
	void primarySipAddressChanged();
	void accountsChanged();
	void accountSettingsUpdated();
	void defaultAccountChanged();
	void publishPresenceChanged();
	void defaultRegistrationChanged();
	
// Sync
	DECLARE_SYNC_SIGNAL(QString, getUsedSipAddressAsStringUriOnly)
	DECLARE_SYNC_SIGNAL(QString, getUsedSipAddressAsString)
	void getAccountDescriptionSync(QVariantMap * result, const std::shared_ptr<linphone::Account> &account);
	DECLARE_SYNC_SIGNAL(QString, getConferenceUri)
	DECLARE_SYNC_SIGNAL(QString, getVideoConferenceUri)
	DECLARE_SYNC_SIGNAL(QString, getLimeServerUrl)
	void addOrUpdateAccountSync (bool * result, const std::shared_ptr<linphone::Account> &account, const QVariantMap &data);
	void addOrUpdateAccountSync (bool * result, const QVariantMap &data);
	void createAccountSync (std::shared_ptr<linphone::Account>* result, const QString& assistantFile);
	DECLARE_SYNC_SIGNAL(QString, getPrimaryUsername)
	DECLARE_SYNC_SIGNAL(QString, getPrimaryDisplayName)
	DECLARE_SYNC_SIGNAL(QString, getPrimarySipAddress)
	DECLARE_SYNC_SIGNAL(QString, getUsername)
	DECLARE_SYNC_SIGNAL(QString, getDefaultAccountDomain)
	DECLARE_SYNC_SIGNAL(QVariantList, getAccounts)
	DECLARE_SYNC_SIGNAL_ENUM(RegistrationState, getRegistrationState, AccountSettingsModel)
	
};

Q_DECLARE_METATYPE(std::shared_ptr<linphone::Account>);

#endif
