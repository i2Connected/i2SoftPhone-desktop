/*
 * Copyright (c) 2010-2020 Belledonne Communications SARL.
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

#ifndef SETTINGS_MODEL_H_
#define SETTINGS_MODEL_H_

#include <linphone++/linphone.hh>
#include <utils/MediastreamerUtils.hpp>
#include <QObject>
#include <QVariantMap>
#include <QFont>

#include "components/core/CoreHandlers.hpp"
#include "components/contacts/ContactsImporterModel.hpp"
#include "utils/LinphoneEnums.hpp"

#ifdef ENABLE_QT_KEYCHAIN
#include "components/vfs/VfsUtils.hpp"
#endif

#include "utils/CodeHelpersGUI.hpp"

// =============================================================================
class TunnelModel;

class SettingsModel : public QObject {
	Q_OBJECT
public:
	enum MediaEncryption {
		MediaEncryptionNone = int(linphone::MediaEncryption::None),
		MediaEncryptionDtls = int(linphone::MediaEncryption::DTLS),
		MediaEncryptionSrtp = int(linphone::MediaEncryption::SRTP),
		MediaEncryptionZrtp = int(linphone::MediaEncryption::ZRTP)
	};
	Q_ENUM(MediaEncryption)
	
	enum VersionCheckType {
		VersionCheckType_Release,
		VersionCheckType_Nightly,
		VersionCheckType_Custom
	};
	Q_ENUM(VersionCheckType);
	
	enum CameraMode{
		CameraMode_Hybrid = 0,
		CameraMode_OccupyAllSpace = 1, 
		CameraMode_BlackBars = 2
	};
	Q_ENUM(CameraMode);
	static SettingsModel::CameraMode cameraModefromString(const std::string& mode);
	static std::string toString(const CameraMode& mode);
	
	
	SettingsModel (QObject *parent = Q_NULLPTR);
	virtual ~SettingsModel ();
	
	// ===========================================================================
	// METHODS.
	// ===========================================================================
	
	void onSettingsTabChanged(int idx);
	void settingsWindowClosing(void);
	void reloadDevices();
	
	// Assistant. ----------------------------------------------------------------
	
	bool getCreateAppSipAccountEnabled () const;
	void setCreateAppSipAccountEnabled (bool status);
	
	bool getFetchRemoteConfigurationEnabled () const;
	void setFetchRemoteConfigurationEnabled (bool status);
	
	bool getUseAppSipAccountEnabled () const;
	void setUseAppSipAccountEnabled (bool status);
	
	bool getUseOtherSipAccountEnabled () const;
	void setUseOtherSipAccountEnabled (bool status);
	
	bool getAssistantSupportsPhoneNumbers () const;
	void setAssistantSupportsPhoneNumbers (bool status);
	
	bool useWebview() const;

	QString getAssistantRegistrationUrl () const;
	void setAssistantRegistrationUrl (QString url);

	QString getAssistantLoginUrl () const;
	void setAssistantLoginUrl (QString url);
	
	QString getAssistantLogoutUrl () const;
	void setAssistantLogoutUrl (QString url);
	
	bool isCguAccepted () const;
	void acceptCgu(const bool accept);
	
	// SIP Accounts. -------------------------------------------------------------
	
	static QString getDeviceName(const std::shared_ptr<linphone::Config>& config);
	QString getDeviceName() const;
	void setDeviceName(const QString& deviceName);

	// Audio. --------------------------------------------------------------------

	void startCaptureGraph();
	void stopCaptureGraph();
	void resetCaptureGraph();
	void createCaptureGraph();
	void deleteCaptureGraph();
	bool getCaptureGraphRunning() const;
	void accessAudioSettings();
	void closeAudioSettings();
	
	float getMicVolume() const;
	
	float getPlaybackGain() const;
	void setPlaybackGain(float gain);
	
	float getCaptureGain() const;
	void setCaptureGain(float gain);
	
	QStringList getCaptureDevices () const;
	QStringList getPlaybackDevices () const;
	
	QString getCaptureDevice () const;
	void setCaptureDevice (const QString &device);
	
	QString getPlaybackDevice () const;
	void setPlaybackDevice (const QString &device);
	
	QString getRingerDevice () const;
	void setRingerDevice (const QString &device);
	
	QString getRingPath () const;
	void setRingPath (const QString &path);
	
	bool getEchoCancellationEnabled () const;
	void setEchoCancellationEnabled (bool status);
	
	void startEchoCancellerCalibration();
	
	bool getShowAudioCodecs () const;
	void setShowAudioCodecs (bool status);
	
	// Video. --------------------------------------------------------------------
	
	//Called from qml when accessing audio settings panel
	void accessVideoSettings();
	
	QStringList getVideoDevices () const;
	
	QString getVideoDevice () const;
	void setVideoDevice (const QString &device);
	
	QString getVideoPreset () const;
	void setVideoPreset (const QString &preset);
	
	int getVideoFramerate () const;
	void setVideoFramerate (int framerate);
	
	QVariantList getSupportedVideoDefinitions () const;
	
	void setHighMosaicQuality();
	void setLimitedMosaicQuality();
	
	QVariantMap getVideoDefinition () const;
	QVariantMap getCurrentPreviewVideoDefinition () const;
	void setVideoDefinition (const QVariantMap &definition);
	
	bool getVideoSupported () const;
	
	bool getShowVideoCodecs () const;
	void setShowVideoCodecs (bool status);
	
	void updateCameraMode();
	CameraMode getCameraMode() const;
	void setCameraMode(CameraMode mode);
	// Custom modes to set default for setCameraMode
	CameraMode getGridCameraMode() const;
	void setGridCameraMode(CameraMode mode);
	CameraMode getActiveSpeakerCameraMode() const;
	void setActiveSpeakerCameraMode(CameraMode mode);
	CameraMode getCallCameraMode() const;
	void setCallCameraMode(CameraMode mode);
	
	LinphoneEnums::ConferenceLayout getVideoConferenceLayout() const;
	void setVideoConferenceLayout(LinphoneEnums::ConferenceLayout layout);
	
	
	// Chat & calls. -------------------------------------------------------------
	
	bool getAutoAnswerStatus () const;
	void setAutoAnswerStatus (bool status);
	
	bool getAutoAnswerVideoStatus () const;
	void setAutoAnswerVideoStatus (bool status);
	
	int getAutoAnswerDelay () const;
	void setAutoAnswerDelay (int delay);
	
	bool getShowTelKeypadAutomatically () const;
	void setShowTelKeypadAutomatically (bool status);
	
	bool getKeepCallsWindowInBackground () const;
	void setKeepCallsWindowInBackground (bool status);
	
	bool getOutgoingCallsEnabled () const;
	void setOutgoingCallsEnabled (bool status);
	
	bool getCallRecorderEnabled () const;
	void setCallRecorderEnabled (bool status);
	
	bool getAutomaticallyRecordCalls () const;
	void setAutomaticallyRecordCalls (bool status);
	
	int getAutoDownloadMaxSize() const;
	void setAutoDownloadMaxSize(int maxSize);
	
	bool getCallPauseEnabled () const;
	void setCallPauseEnabled (bool status);
	
	bool getMuteMicrophoneEnabled () const;
	void setMuteMicrophoneEnabled (bool status);
	
	bool getStandardChatEnabled () const;
	void setStandardChatEnabled (bool status);
	
	bool getSecureChatEnabled () const;
	void setSecureChatEnabled (bool status);
	
	bool getHideEmptyChatRooms() const;
	void setHideEmptyChatRooms(const bool& data);
	
	bool getWaitRegistrationForCall() const;
	void setWaitRegistrationForCall(const bool& status);
	
	bool getIncallScreenshotEnabled() const;
	void setIncallScreenshotEnabled(const bool& status);
	
	bool getGroupChatEnabled()const;
	
	bool getConferenceEnabled () const;
	void setConferenceEnabled (bool status);
	bool getVideoConferenceEnabled()const;
	
	bool getChatNotificationsEnabled () const;
	void setChatNotificationsEnabled (bool status);
	
	bool getChatNotificationSoundEnabled () const;
	void setChatNotificationSoundEnabled (bool status);
	
	QString getChatNotificationSoundPath () const;
	void setChatNotificationSoundPath (const QString &path);
	
	QString getFileTransferUrl () const;
	void setFileTransferUrl (const QString &url);
	
	bool getLimeIsSupported () const;
	QVariantList getSupportedMediaEncryptions () const;
	
	MediaEncryption getMediaEncryption () const;
	void setMediaEncryption (MediaEncryption encryption);
	
	bool mandatoryMediaEncryptionEnabled () const;
	void enableMandatoryMediaEncryption(bool mandatory);
	
	bool getPostQuantumAvailable() const;
	
	bool getLimeState () const;
	void setLimeState (const bool& state);
	
	bool getContactsEnabled () const;
	void setContactsEnabled (bool status);
	
	int getIncomingCallTimeout() const;
	
	// Network. ------------------------------------------------------------------
	
	bool getShowNetworkSettings () const;
	void setShowNetworkSettings (bool status);
	
	bool getUseSipInfoForDtmfs () const;
	void setUseSipInfoForDtmfs (bool status);
	
	bool getUseRfc2833ForDtmfs () const;
	void setUseRfc2833ForDtmfs (bool status);
	
	bool getIpv6Enabled () const;
	void setIpv6Enabled (bool status);
	
	int getDownloadBandwidth () const;
	void setDownloadBandwidth (int bandwidth);
	
	int getUploadBandwidth () const;
	void setUploadBandwidth (int bandwidth);
	
	bool getAdaptiveRateControlEnabled () const;
	void setAdaptiveRateControlEnabled (bool status);
	
	int getTcpPort () const;
	void setTcpPort (int port);
	
	int getUdpPort () const;
	void setUdpPort (int port);
	
	QList<int> getAudioPortRange () const;
	void setAudioPortRange (const QList<int> &range);
	
	QList<int> getVideoPortRange () const;
	void setVideoPortRange (const QList<int> &range);
	
	bool getIceEnabled () const;
	void setIceEnabled (bool status);
	
	bool getTurnEnabled () const;
	void setTurnEnabled (bool status);
	
	QString getStunServer () const;
	void setStunServer (const QString &stunServer);
	
	QString getTurnUser () const;
	void setTurnUser (const QString &user);
	
	QString getTurnPassword () const;
	void setTurnPassword (const QString &password);
	
	int getDscpSip () const;
	void setDscpSip (int dscp);
	
	int getDscpAudio () const;
	void setDscpAudio (int dscp);
	
	int getDscpVideo () const;
	void setDscpVideo (int dscp);
	
	bool getRlsUriEnabled () const;
	void setRlsUriEnabled (bool status);
	
	void configureRlsUri ();
	void configureRlsUri (const std::string& domain);
	void configureRlsUri (const std::shared_ptr<const linphone::Account> &account);
	
	bool tunnelAvailable() const;
	TunnelModel * getTunnel() const;
	
	// UI. -----------------------------------------------------------------------
	
	QFont getTextMessageFont() const;
	void setTextMessageFont(const QFont& font);
	
	int getTextMessageFontSize() const;
	void setTextMessageFontSize(const int& size);
	
	QFont getEmojiFont() const;
	void setEmojiFont(const QFont& font);
	
	int getEmojiFontSize() const;
	void setEmojiFontSize(const int& size);
	
	QString getSavedScreenshotsFolder () const;
	void setSavedScreenshotsFolder (const QString &folder);
	
	QString getSavedCallsFolder () const;
	void setSavedCallsFolder (const QString &folder);
	
	QString getDownloadFolder () const;
	void setDownloadFolder (const QString &folder);
	
	QString getRemoteProvisioningRootUrl() const;
	QString getRemoteProvisioning () const;
	void setRemoteProvisioning (const QString &remoteProvisioning);
	
	bool isQRCodeAvailable() const;
	QString getFlexiAPIUrl() const;
	void setFlexiAPIUrl (const QString &url);
	
	bool getExitOnClose () const;
	void setExitOnClose (bool value);
	
	Q_INVOKABLE static bool isCheckForUpdateAvailable();
	bool isCheckForUpdateEnabled() const;
	void setCheckForUpdateEnabled(bool enable);
	
	QString getVersionCheckUrl();
	void setVersionCheckUrl(const QString& url);
	
	VersionCheckType getVersionCheckType() const;
	void setVersionCheckType(const VersionCheckType& type);
	bool haveVersionNightlyUrl()const;
	
	
	bool getShowLocalSipAccount () const;
	bool getShowStartChatButton () const;
	bool getShowStartVideoCallButton () const;
	
	bool isMipmapEnabled() const;
	void setMipmapEnabled(const bool& enabled);
	
	bool useMinimalTimelineFilter() const;
	void setUseMinimalTimelineFilter(const bool& useMinimal);
	
	// Advanced. ---------------------------------------------------------------------------
	
	
	void accessAdvancedSettings();
	
	QString getLogText()const;
	
	QString getLogsFolder () const;
	void setLogsFolder (const QString &folder);
	
	QString getLogsUploadUrl () const;
	void setLogsUploadUrl (const QString &url);
	
	bool getLogsEnabled () const;
	void setLogsEnabled (bool status);
	
	QString getLogsEmail () const;
	void setLogsEmail (const QString &email);
	
	bool getVfsEncrypted () const;
	Q_INVOKABLE void setVfsEncrypted (bool encrypted, const bool deleteUserData);
	
	Q_INVOKABLE bool isLdapAvailable() const;
	
// OAuth 2
	bool isOAuth2Available() const;
	QString getOAuth2AuthorizationUrl()const;
	QString getOAuth2AccessTokenUrl()const;
	QString getOAuth2RedirectUri()const;
	QString getOAuth2Identifier()const;
	QString getOAuth2Password()const;
	QString getOAuth2Scope()const;
	QString getOAuth2RemoteProvisioningBasicAuth()const;
	QString getOAuth2RemoteProvisioningHeader()const;
	
	// ---------------------------------------------------------------------------
	
	static QString getLogsFolder (const std::shared_ptr<linphone::Config> &config);
	static bool getLogsEnabled (const std::shared_ptr<linphone::Config> &config);
	
	// ---------------------------------------------------------------------------
	bool isDeveloperSettingsAvailable() const;
	bool getDeveloperSettingsEnabled () const;
	void setDeveloperSettingsEnabled (bool status);
	
	void handleCallCreated(const std::shared_ptr<linphone::Call> &call);
	void handleCallStateChanged(const std::shared_ptr<linphone::Call> &call, linphone::Call::State state);
	void handleEcCalibrationResult(linphone::EcCalibratorStatus status, int delayMs);
	
	bool getIsInCall() const;
	
	bool isReadOnly(const std::string& section, const std::string& name) const;
	std::string getEntryFullName(const std::string& section, const std::string& name) const;	// Return the full name of the entry : 'name/readonly' or 'name'
	
	static const std::string UiSection;
	static const std::string ContactsSection;
	
	// ===========================================================================
	// SIGNALS.
	// ===========================================================================
	
signals:
	// Assistant. ----------------------------------------------------------------
	
	void createAppSipAccountEnabledChanged (bool status);
	void fetchRemoteConfigurationEnabledChanged (bool status);
	void useAppSipAccountEnabledChanged (bool status);
	void useOtherSipAccountEnabledChanged (bool status);
	
	void assistantSupportsPhoneNumbersChanged (bool status);

	void assistantRegistrationUrlChanged (QString url);
	void assistantLoginUrlChanged (QString url);
	void assistantLogoutUrlChanged (QString url);
	
	void cguAcceptedChanged(bool accepted);
	
	// SIP Accounts. -------------------------------------------------------------
	
	void deviceNameChanged();

	// Audio. --------------------------------------------------------------------
	
	void captureGraphRunningChanged(bool running);
	
	void playbackGainChanged(float gain);
	void captureGainChanged(float gain);
	
	void captureDevicesChanged (const QStringList &devices);
	void playbackDevicesChanged (const QStringList &devices);
	
	void captureDeviceChanged (const QString &device);
	void playbackDeviceChanged (const QString &device);
	void ringerDeviceChanged (const QString &device);
	
	void ringPathChanged (const QString &path);
	
	void echoCancellationEnabledChanged (bool status);
	void echoCancellationStatus(int status, int msDelay);
	
	void showAudioCodecsChanged (bool status);
	
	// Video. --------------------------------------------------------------------
	
	void videoDevicesChanged (const QStringList &devices);
	void videoDeviceChanged (const QString &device);
	
	void videoPresetChanged (const QString &preset);
	void videoFramerateChanged (int framerate);
	
	void videoDefinitionChanged (const QVariantMap &definition);
	
	void showVideoCodecsChanged (bool status);
	
	void cameraModeChanged();
	void gridCameraModeChanged();
	void activeSpeakerCameraModeChanged();
	void callCameraModeChanged();
	void videoConferenceLayoutChanged();
	
	// Chat & calls. -------------------------------------------------------------
	
	void autoAnswerStatusChanged (bool status);
	void autoAnswerVideoStatusChanged (bool status);
	void autoAnswerDelayChanged (int delay);
	
	void showTelKeypadAutomaticallyChanged (bool status);
	
	void keepCallsWindowInBackgroundChanged (bool status);
	
	void outgoingCallsEnabledChanged (bool status);
	
	void callRecorderEnabledChanged (bool status);
	void automaticallyRecordCallsChanged (bool status);
	void autoDownloadMaxSizeChanged (int maxSize);
	
	void callPauseEnabledChanged (bool status);
	void muteMicrophoneEnabledChanged (bool status);
	
	void standardChatEnabledChanged (bool status);
	void secureChatEnabledChanged ();
	void groupChatEnabledChanged();
	void hideEmptyChatRoomsChanged (bool status);
	void waitRegistrationForCallChanged (bool status);
	void incallScreenshotEnabledChanged(bool status);
	
	void conferenceEnabledChanged (bool status);
	void videoConferenceEnabledChanged ();
	
	void chatNotificationsEnabledChanged (bool status);
	void chatNotificationSoundEnabledChanged (bool status);
	void chatNotificationSoundPathChanged (const QString &path);
	
	void fileTransferUrlChanged (const QString &url);
	
	void mediaEncryptionChanged (MediaEncryption encryption);
	void limeStateChanged (bool state);
	
	void contactsEnabledChanged (bool status);
	
	// Network. ------------------------------------------------------------------
	
	void showNetworkSettingsChanged (bool status);
	
	void dtmfsProtocolChanged ();
	
	void ipv6EnabledChanged (bool status);
	
	void downloadBandWidthChanged (int bandwidth);
	void uploadBandWidthChanged (int bandwidth);
	
	bool adaptiveRateControlEnabledChanged (bool status);
	
	void tcpPortChanged (int port);
	void udpPortChanged (int port);
	
	void audioPortRangeChanged (int a, int b);
	void videoPortRangeChanged (int a, int b);
	
	void iceEnabledChanged (bool status);
	void turnEnabledChanged (bool status);
	
	void stunServerChanged (const QString &server);
	
	void turnUserChanged (const QString &user);
	void turnPasswordChanged (const QString &password);
	
	void dscpSipChanged (int dscp);
	void dscpAudioChanged (int dscp);
	void dscpVideoChanged (int dscp);
	
	void rlsUriEnabledChanged (bool status);
		
	// UI. -----------------------------------------------------------------------
	
	void textMessageFontChanged(const QFont& font);
	void textMessageFontSizeChanged(const int& size);
	
	void emojiFontChanged(const QFont& font);
	void emojiFontSizeChanged(const int& size);
	
	void savedScreenshotsFolderChanged (const QString &folder);
	void savedCallsFolderChanged (const QString &folder);
	void downloadFolderChanged (const QString &folder);
	
	void remoteProvisioningChanged (const QString &remoteProvisioning);
	void remoteProvisioningNotChanged (const QString &remoteProvisioning);
	void flexiAPIUrlChanged (const QString &url);
	
	void exitOnCloseChanged (bool value);
	void mipmapEnabledChanged();
	void useMinimalTimelineFilterChanged();
	
	void checkForUpdateEnabledChanged();
	void versionCheckUrlChanged();
	void versionCheckTypeChanged();
	
	// Advanced. -----------------------------------------------------------------
	
	void logsFolderChanged (const QString &folder);
	void logsUploadUrlChanged (const QString &url);
	void logsEnabledChanged (bool status);
	void logsEmailChanged (const QString &email);
	void vfsEncryptedChanged();
	
	void contactImporterChanged();
	
	bool developerSettingsEnabledChanged (bool status);
	
	bool isInCallChanged(bool);
	
private:
	int mCurrentSettingsTab = 0;
	MediastreamerUtils::SimpleCaptureGraph *mSimpleCaptureGraph = nullptr;
	int mCaptureGraphListenerCount = 0;
#ifdef ENABLE_QT_KEYCHAIN
	VfsUtils mVfsUtils;
#endif
	
	std::shared_ptr<linphone::Config> mConfig;
public slots:

	DECLARE_SYNC_SLOT_CONST(bool, getCreateAppSipAccountEnabled)
	DECLARE_SYNC_SLOT_CONST(bool, getFetchRemoteConfigurationEnabled)
	DECLARE_SYNC_SLOT_CONST(bool, getUseAppSipAccountEnabled)
	DECLARE_SYNC_SLOT_CONST(bool, getUseOtherSipAccountEnabled)
	DECLARE_SYNC_SLOT_CONST(bool, getAssistantSupportsPhoneNumbers)
	DECLARE_SYNC_SLOT_CONST(bool, useWebview)
	DECLARE_SYNC_SLOT_CONST(QString, getAssistantRegistrationUrl)
	DECLARE_SYNC_SLOT_CONST(QString, getAssistantLoginUrl)
	DECLARE_SYNC_SLOT_CONST(QString, getAssistantLogoutUrl)
	DECLARE_SYNC_SLOT_CONST(bool, isCguAccepted)
	DECLARE_SYNC_SLOT_CONST(QString, getDeviceName)
	DECLARE_SYNC_SLOT_CONST(float, getMicVolume)
	DECLARE_SYNC_SLOT_CONST(float, getPlaybackGain)
	DECLARE_SYNC_SLOT_CONST(float, getCaptureGain)
	DECLARE_SYNC_SLOT_CONST(bool, getCaptureGraphRunning)
	DECLARE_SYNC_SLOT_CONST(QStringList, getCaptureDevices)
	DECLARE_SYNC_SLOT_CONST(QStringList, getPlaybackDevices)
	DECLARE_SYNC_SLOT_CONST(QString, getCaptureDevice)
	DECLARE_SYNC_SLOT_CONST(QString, getPlaybackDevice)
	DECLARE_SYNC_SLOT_CONST(QString, getRingerDevice)
	DECLARE_SYNC_SLOT_CONST(QString, getRingPath)
	DECLARE_SYNC_SLOT_CONST(bool, getEchoCancellationEnabled)
	DECLARE_SYNC_SLOT_CONST(bool, getShowAudioCodecs)
	DECLARE_SYNC_SLOT_CONST(QStringList, getVideoDevices)
	DECLARE_SYNC_SLOT_CONST(QString, getVideoDevice)
	DECLARE_SYNC_SLOT_CONST(QString, getVideoPreset)
	DECLARE_SYNC_SLOT_CONST(int, getVideoFramerate)
	DECLARE_SYNC_SLOT_CONST(QVariantList, getSupportedVideoDefinitions)
	DECLARE_SYNC_SLOT_CONST(QVariantMap, getVideoDefinition)
	DECLARE_SYNC_SLOT_CONST(QVariantMap, getCurrentPreviewVideoDefinition)
	DECLARE_SYNC_SLOT_CONST(bool, getVideoSupported)
	DECLARE_SYNC_SLOT_CONST(bool, getShowVideoCodecs)
	DECLARE_SYNC_SLOT_CONST(CameraMode, getGridCameraMode)
	DECLARE_SYNC_SLOT_CONST(CameraMode, getActiveSpeakerCameraMode)
	DECLARE_SYNC_SLOT_CONST(CameraMode, getCallCameraMode)
	DECLARE_SYNC_SLOT_CONST(LinphoneEnums::ConferenceLayout, getVideoConferenceLayout)
	DECLARE_SYNC_SLOT_CONST(bool, getAutoAnswerStatus)
	DECLARE_SYNC_SLOT_CONST(bool, getAutoAnswerVideoStatus)
	DECLARE_SYNC_SLOT_CONST(int, getAutoAnswerDelay)
	DECLARE_SYNC_SLOT_CONST(bool, getShowTelKeypadAutomatically)
	DECLARE_SYNC_SLOT_CONST(bool, getKeepCallsWindowInBackground)
	DECLARE_SYNC_SLOT_CONST(bool, getOutgoingCallsEnabled)
	DECLARE_SYNC_SLOT_CONST(bool, getCallRecorderEnabled)
	DECLARE_SYNC_SLOT_CONST(bool, getAutomaticallyRecordCalls)
	DECLARE_SYNC_SLOT_CONST(int, getAutoDownloadMaxSize)
	DECLARE_SYNC_SLOT_CONST(bool, getCallPauseEnabled)
	DECLARE_SYNC_SLOT_CONST(bool, getMuteMicrophoneEnabled)
	DECLARE_SYNC_SLOT_CONST(bool, getStandardChatEnabled)
	DECLARE_SYNC_SLOT_CONST(bool, getSecureChatEnabled)
	DECLARE_SYNC_SLOT_CONST(bool, getHideEmptyChatRooms)
	DECLARE_SYNC_SLOT_CONST(bool, getWaitRegistrationForCall)
	DECLARE_SYNC_SLOT_CONST(bool, getIncallScreenshotEnabled)
	DECLARE_SYNC_SLOT_CONST(bool, getGroupChatEnabled)
	DECLARE_SYNC_SLOT_CONST(bool, getConferenceEnabled)
	DECLARE_SYNC_SLOT_CONST(bool, getVideoConferenceEnabled)
	DECLARE_SYNC_SLOT_CONST(bool, getChatNotificationsEnabled)
	DECLARE_SYNC_SLOT_CONST(bool, getChatNotificationSoundEnabled)
	DECLARE_SYNC_SLOT_CONST(QString, getChatNotificationSoundPath)
	DECLARE_SYNC_SLOT_CONST(QString, getFileTransferUrl)
	DECLARE_SYNC_SLOT_CONST(bool, getLimeIsSupported)
	DECLARE_SYNC_SLOT_CONST(QVariantList, getSupportedMediaEncryptions)
	DECLARE_SYNC_SLOT_CONST(MediaEncryption, getMediaEncryption)
	DECLARE_SYNC_SLOT_CONST(bool, mandatoryMediaEncryptionEnabled)
	DECLARE_SYNC_SLOT_CONST(bool, getPostQuantumAvailable)
	DECLARE_SYNC_SLOT_CONST(bool, getLimeState)
	DECLARE_SYNC_SLOT_CONST(bool, getContactsEnabled)
	DECLARE_SYNC_SLOT_CONST(bool, getShowNetworkSettings)
	DECLARE_SYNC_SLOT_CONST(bool, getUseSipInfoForDtmfs)
	DECLARE_SYNC_SLOT_CONST(bool, getUseRfc2833ForDtmfs)
	DECLARE_SYNC_SLOT_CONST(bool, getIpv6Enabled)
	DECLARE_SYNC_SLOT_CONST(int, getDownloadBandwidth)
	DECLARE_SYNC_SLOT_CONST(int, getUploadBandwidth)
	DECLARE_SYNC_SLOT_CONST(bool, getAdaptiveRateControlEnabled)
	DECLARE_SYNC_SLOT_CONST(int, getTcpPort)
	DECLARE_SYNC_SLOT_CONST(int, getUdpPort)
	DECLARE_SYNC_SLOT_CONST(QList<int>, getAudioPortRange)
	DECLARE_SYNC_SLOT_CONST(QList<int>, getVideoPortRange)
	DECLARE_SYNC_SLOT_CONST(bool, getIceEnabled)
	DECLARE_SYNC_SLOT_CONST(bool, getTurnEnabled)
	DECLARE_SYNC_SLOT_CONST(QString, getStunServer)
	DECLARE_SYNC_SLOT_CONST(QString, getTurnUser)
	DECLARE_SYNC_SLOT_CONST(QString, getTurnPassword)
	DECLARE_SYNC_SLOT_CONST(int, getDscpSip)
	DECLARE_SYNC_SLOT_CONST(int, getDscpAudio)
	DECLARE_SYNC_SLOT_CONST(int, getDscpVideo)
	DECLARE_SYNC_SLOT_CONST(bool, getRlsUriEnabled)
	DECLARE_SYNC_SLOT_CONST(bool, tunnelAvailable)
	DECLARE_SYNC_SLOT_CONST(TunnelModel *, getTunnel)
	DECLARE_SYNC_SLOT_CONST(QFont, getTextMessageFont)
	DECLARE_SYNC_SLOT_CONST(int, getTextMessageFontSize)
	DECLARE_SYNC_SLOT_CONST(QFont, getEmojiFont)
	DECLARE_SYNC_SLOT_CONST(int, getEmojiFontSize)
	DECLARE_SYNC_SLOT_CONST(QString, getSavedScreenshotsFolder)
	DECLARE_SYNC_SLOT_CONST(QString, getSavedCallsFolder)
	DECLARE_SYNC_SLOT_CONST(QString, getDownloadFolder)
	DECLARE_SYNC_SLOT_CONST(QString, getRemoteProvisioning)
	DECLARE_SYNC_SLOT_CONST(bool, isQRCodeAvailable)
	DECLARE_SYNC_SLOT_CONST(QString, getFlexiAPIUrl)
	DECLARE_SYNC_SLOT_CONST(bool, getExitOnClose)
	DECLARE_SYNC_SLOT_CONST(bool, isCheckForUpdateEnabled)
	DECLARE_SYNC_SLOT(QString, getVersionCheckUrl)
	DECLARE_SYNC_SLOT_CONST(VersionCheckType, getVersionCheckType)
	DECLARE_SYNC_SLOT_CONST(bool, haveVersionNightlyUrl)
	DECLARE_SYNC_SLOT_CONST(bool, getShowLocalSipAccount)
	DECLARE_SYNC_SLOT_CONST(bool, getShowStartChatButton)
	DECLARE_SYNC_SLOT_CONST(bool, getShowStartVideoCallButton)
	DECLARE_SYNC_SLOT_CONST(bool, isMipmapEnabled)
	DECLARE_SYNC_SLOT_CONST(bool, useMinimalTimelineFilter)
	DECLARE_SYNC_SLOT_CONST(QString, getLogText)
	DECLARE_SYNC_SLOT_CONST(QString, getLogsFolder)
	DECLARE_SYNC_SLOT_CONST(QString, getLogsUploadUrl)
	DECLARE_SYNC_SLOT_CONST(bool, getLogsEnabled)
	DECLARE_SYNC_SLOT_CONST(QString, getLogsEmail)
	DECLARE_SYNC_SLOT_CONST(bool, getVfsEncrypted)
	DECLARE_SYNC_SLOT_CONST(bool, isLdapAvailable)
	DECLARE_SYNC_SLOT_CONST(bool, isOAuth2Available)
	DECLARE_SYNC_SLOT_CONST(bool, isDeveloperSettingsAvailable)
	DECLARE_SYNC_SLOT_CONST(bool, getDeveloperSettingsEnabled)
	DECLARE_SYNC_SLOT_CONST(bool, getIsInCall)
};

Q_DECLARE_METATYPE(std::shared_ptr<const linphone::VideoDefinition>);

#endif // SETTINGS_MODEL_H_
