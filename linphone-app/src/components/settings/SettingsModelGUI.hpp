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

#ifndef SETTINGS_MODEL_GUI_H_
#define SETTINGS_MODEL_GUI_H_

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

#include "SettingsModel.hpp"

#include "utils/CodeHelpersGUI.hpp"

// =============================================================================
class TunnelModel;

class SettingsModelGUI : public QObject {
	Q_OBJECT
	
	// ===========================================================================
	// PROPERTIES.
	// ===========================================================================
	
	// Assistant. ----------------------------------------------------------------
	
	Q_PROPERTY(bool createAppSipAccountEnabled READ getCreateAppSipAccountEnabled WRITE setCreateAppSipAccountEnabled NOTIFY createAppSipAccountEnabledChanged)
	Q_PROPERTY(bool fetchRemoteConfigurationEnabled READ getFetchRemoteConfigurationEnabled WRITE setFetchRemoteConfigurationEnabled NOTIFY fetchRemoteConfigurationEnabledChanged)
	Q_PROPERTY(bool useAppSipAccountEnabled READ getUseAppSipAccountEnabled WRITE setUseAppSipAccountEnabled NOTIFY useAppSipAccountEnabledChanged)
	Q_PROPERTY(bool useOtherSipAccountEnabled READ getUseOtherSipAccountEnabled WRITE setUseOtherSipAccountEnabled NOTIFY useOtherSipAccountEnabledChanged)
	
	Q_PROPERTY(bool assistantSupportsPhoneNumbers READ getAssistantSupportsPhoneNumbers WRITE setAssistantSupportsPhoneNumbers NOTIFY assistantSupportsPhoneNumbersChanged)
	// Webviews config
	Q_PROPERTY(QString assistantRegistrationUrl READ getAssistantRegistrationUrl WRITE setAssistantRegistrationUrl NOTIFY assistantRegistrationUrlChanged)
	Q_PROPERTY(QString assistantLoginUrl READ getAssistantLoginUrl WRITE setAssistantLoginUrl NOTIFY assistantLoginUrlChanged)
	Q_PROPERTY(QString assistantLogoutUrl READ getAssistantLogoutUrl WRITE setAssistantLogoutUrl NOTIFY assistantLogoutUrlChanged)
	//----
	Q_PROPERTY(bool cguAccepted READ isCguAccepted WRITE acceptCgu NOTIFY cguAcceptedChanged)
	
	// SIP Accounts. -------------------------------------------------------------
	
	Q_PROPERTY(QString deviceName READ getDeviceName WRITE setDeviceName NOTIFY deviceNameChanged)
	
	// Audio. --------------------------------------------------------------------
	
	Q_PROPERTY(bool captureGraphRunning READ getCaptureGraphRunning NOTIFY captureGraphRunningChanged)
	
	Q_PROPERTY(QStringList captureDevices READ getCaptureDevices NOTIFY captureDevicesChanged)
	Q_PROPERTY(QStringList playbackDevices READ getPlaybackDevices NOTIFY playbackDevicesChanged)
	
	Q_PROPERTY(float playbackGain READ getPlaybackGain WRITE setPlaybackGain NOTIFY playbackGainChanged)
	Q_PROPERTY(float captureGain READ getCaptureGain WRITE setCaptureGain NOTIFY captureGainChanged)
	
	Q_PROPERTY(QString captureDevice READ getCaptureDevice WRITE setCaptureDevice NOTIFY captureDeviceChanged)
	Q_PROPERTY(QString playbackDevice READ getPlaybackDevice WRITE setPlaybackDevice NOTIFY playbackDeviceChanged)
	Q_PROPERTY(QString ringerDevice READ getRingerDevice WRITE setRingerDevice NOTIFY ringerDeviceChanged)
	
	Q_PROPERTY(QString ringPath READ getRingPath WRITE setRingPath NOTIFY ringPathChanged)
	
	Q_PROPERTY(bool echoCancellationEnabled READ getEchoCancellationEnabled WRITE setEchoCancellationEnabled NOTIFY echoCancellationEnabledChanged)
	
	Q_PROPERTY(bool showAudioCodecs READ getShowAudioCodecs WRITE setShowAudioCodecs NOTIFY showAudioCodecsChanged)
	
	// Video. --------------------------------------------------------------------
	
	Q_PROPERTY(QStringList videoDevices READ getVideoDevices NOTIFY videoDevicesChanged)
	
	Q_PROPERTY(QString videoDevice READ getVideoDevice WRITE setVideoDevice NOTIFY videoDeviceChanged)
	
	Q_PROPERTY(QString videoPreset READ getVideoPreset WRITE setVideoPreset NOTIFY videoPresetChanged)
	Q_PROPERTY(int videoFramerate READ getVideoFramerate WRITE setVideoFramerate NOTIFY videoFramerateChanged)
	
	Q_PROPERTY(QVariantList supportedVideoDefinitions READ getSupportedVideoDefinitions CONSTANT)
	
	Q_PROPERTY(QVariantMap videoDefinition READ getVideoDefinition WRITE setVideoDefinition NOTIFY videoDefinitionChanged)
	
	Q_PROPERTY(bool videoSupported READ getVideoSupported CONSTANT)
	
	Q_PROPERTY(bool showVideoCodecs READ getShowVideoCodecs WRITE setShowVideoCodecs NOTIFY showVideoCodecsChanged)
	
	Q_PROPERTY(SettingsModelGUI::CameraMode gridCameraMode READ getGridCameraMode WRITE setGridCameraMode NOTIFY gridCameraModeChanged)
	Q_PROPERTY(SettingsModelGUI::CameraMode activeSpeakerCameraMode READ getActiveSpeakerCameraMode WRITE setActiveSpeakerCameraMode NOTIFY activeSpeakerCameraModeChanged)
	Q_PROPERTY(SettingsModelGUI::CameraMode callCameraMode READ getCallCameraMode WRITE setCallCameraMode NOTIFY callCameraModeChanged)
	Q_PROPERTY(LinphoneEnums::ConferenceLayout videoConferenceLayout READ getVideoConferenceLayout WRITE setVideoConferenceLayout NOTIFY videoConferenceLayoutChanged)
	
	
	// Chat & calls. -------------------------------------------------------------
	
	Q_PROPERTY(bool autoAnswerStatus READ getAutoAnswerStatus WRITE setAutoAnswerStatus NOTIFY autoAnswerStatusChanged)
	Q_PROPERTY(bool autoAnswerVideoStatus READ getAutoAnswerVideoStatus WRITE setAutoAnswerVideoStatus NOTIFY autoAnswerVideoStatusChanged)
	Q_PROPERTY(int autoAnswerDelay READ getAutoAnswerDelay WRITE setAutoAnswerDelay NOTIFY autoAnswerDelayChanged)
	
	Q_PROPERTY(bool showTelKeypadAutomatically READ getShowTelKeypadAutomatically WRITE setShowTelKeypadAutomatically NOTIFY showTelKeypadAutomaticallyChanged)
	
	Q_PROPERTY(bool keepCallsWindowInBackground READ getKeepCallsWindowInBackground WRITE setKeepCallsWindowInBackground NOTIFY keepCallsWindowInBackgroundChanged)
	
	Q_PROPERTY(bool outgoingCallsEnabled READ getOutgoingCallsEnabled WRITE setOutgoingCallsEnabled NOTIFY outgoingCallsEnabledChanged)
	
	Q_PROPERTY(bool callRecorderEnabled READ getCallRecorderEnabled WRITE setCallRecorderEnabled NOTIFY callRecorderEnabledChanged)
	Q_PROPERTY(bool automaticallyRecordCalls READ getAutomaticallyRecordCalls WRITE setAutomaticallyRecordCalls NOTIFY automaticallyRecordCallsChanged)
	Q_PROPERTY(int autoDownloadMaxSize READ getAutoDownloadMaxSize WRITE setAutoDownloadMaxSize NOTIFY autoDownloadMaxSizeChanged)
	
	Q_PROPERTY(bool callPauseEnabled READ getCallPauseEnabled WRITE setCallPauseEnabled NOTIFY callPauseEnabledChanged)
	Q_PROPERTY(bool muteMicrophoneEnabled READ getMuteMicrophoneEnabled WRITE setMuteMicrophoneEnabled NOTIFY muteMicrophoneEnabledChanged)
	
	Q_PROPERTY(bool standardChatEnabled READ getStandardChatEnabled WRITE setStandardChatEnabled NOTIFY standardChatEnabledChanged)
	Q_PROPERTY(bool secureChatEnabled READ getSecureChatEnabled WRITE setSecureChatEnabled NOTIFY secureChatEnabledChanged)
	Q_PROPERTY(bool groupChatEnabled READ getGroupChatEnabled NOTIFY groupChatEnabledChanged)
	Q_PROPERTY(bool hideEmptyChatRooms READ getHideEmptyChatRooms WRITE setHideEmptyChatRooms NOTIFY hideEmptyChatRoomsChanged)
	
	
	Q_PROPERTY(bool waitRegistrationForCall READ getWaitRegistrationForCall WRITE setWaitRegistrationForCall NOTIFY waitRegistrationForCallChanged)// Allow call only if the current proxy has been registered
	Q_PROPERTY(bool incallScreenshotEnabled READ getIncallScreenshotEnabled WRITE setIncallScreenshotEnabled NOTIFY incallScreenshotEnabledChanged)
	
	Q_PROPERTY(bool conferenceEnabled READ getConferenceEnabled WRITE setConferenceEnabled NOTIFY conferenceEnabledChanged)
	Q_PROPERTY(bool videoConferenceEnabled READ getVideoConferenceEnabled NOTIFY videoConferenceEnabledChanged)
	
	Q_PROPERTY(bool chatNotificationsEnabled READ getChatNotificationsEnabled WRITE setChatNotificationsEnabled NOTIFY chatNotificationsEnabledChanged)
	Q_PROPERTY(bool chatNotificationSoundEnabled READ getChatNotificationSoundEnabled WRITE setChatNotificationSoundEnabled NOTIFY chatNotificationSoundEnabledChanged)
	Q_PROPERTY(QString chatNotificationSoundPath READ getChatNotificationSoundPath WRITE setChatNotificationSoundPath NOTIFY chatNotificationSoundPathChanged)
	
	Q_PROPERTY(QString fileTransferUrl READ getFileTransferUrl WRITE setFileTransferUrl NOTIFY fileTransferUrlChanged)
	
	Q_PROPERTY(bool limeIsSupported READ getLimeIsSupported CONSTANT)
	Q_PROPERTY(QVariantList supportedMediaEncryptions READ getSupportedMediaEncryptions CONSTANT)
	
	Q_PROPERTY(SettingsModelGUI::MediaEncryption mediaEncryption READ getMediaEncryption WRITE setMediaEncryption NOTIFY mediaEncryptionChanged)
	Q_PROPERTY(bool mediaEncryptionMandatory READ mandatoryMediaEncryptionEnabled WRITE enableMandatoryMediaEncryption NOTIFY mediaEncryptionChanged)
	Q_PROPERTY(bool isPostQuantumAvailable READ getPostQuantumAvailable CONSTANT)
	
	Q_PROPERTY(bool limeState READ getLimeState WRITE setLimeState NOTIFY limeStateChanged)
	
	Q_PROPERTY(bool contactsEnabled READ getContactsEnabled WRITE setContactsEnabled NOTIFY contactsEnabledChanged)
	
	// Network. ------------------------------------------------------------------
	
	Q_PROPERTY(bool showNetworkSettings READ getShowNetworkSettings WRITE setShowNetworkSettings NOTIFY showNetworkSettingsChanged)
	
	Q_PROPERTY(bool useSipInfoForDtmfs READ getUseSipInfoForDtmfs WRITE setUseSipInfoForDtmfs NOTIFY dtmfsProtocolChanged)
	Q_PROPERTY(bool useRfc2833ForDtmfs READ getUseRfc2833ForDtmfs WRITE setUseRfc2833ForDtmfs NOTIFY dtmfsProtocolChanged)
	
	Q_PROPERTY(bool ipv6Enabled READ getIpv6Enabled WRITE setIpv6Enabled NOTIFY ipv6EnabledChanged)
	
	Q_PROPERTY(int downloadBandwidth READ getDownloadBandwidth WRITE setDownloadBandwidth NOTIFY downloadBandWidthChanged)
	Q_PROPERTY(int uploadBandwidth READ getUploadBandwidth WRITE setUploadBandwidth NOTIFY uploadBandWidthChanged)
	
	Q_PROPERTY(
			bool adaptiveRateControlEnabled
			READ getAdaptiveRateControlEnabled
			WRITE setAdaptiveRateControlEnabled
			NOTIFY adaptiveRateControlEnabledChanged
			)
	
	Q_PROPERTY(int tcpPort READ getTcpPort WRITE setTcpPort NOTIFY tcpPortChanged)
	Q_PROPERTY(int udpPort READ getUdpPort WRITE setUdpPort NOTIFY udpPortChanged)
	
	Q_PROPERTY(QList<int> audioPortRange READ getAudioPortRange WRITE setAudioPortRange NOTIFY audioPortRangeChanged)
	Q_PROPERTY(QList<int> videoPortRange READ getVideoPortRange WRITE setVideoPortRange NOTIFY videoPortRangeChanged)
	
	Q_PROPERTY(bool iceEnabled READ getIceEnabled WRITE setIceEnabled NOTIFY iceEnabledChanged)
	Q_PROPERTY(bool turnEnabled READ getTurnEnabled WRITE setTurnEnabled NOTIFY turnEnabledChanged)
	
	Q_PROPERTY(QString stunServer READ getStunServer WRITE setStunServer NOTIFY stunServerChanged)
	
	Q_PROPERTY(QString turnUser READ getTurnUser WRITE setTurnUser NOTIFY turnUserChanged)
	Q_PROPERTY(QString turnPassword READ getTurnPassword WRITE setTurnPassword NOTIFY turnPasswordChanged)
	
	Q_PROPERTY(int dscpSip READ getDscpSip WRITE setDscpSip NOTIFY dscpSipChanged)
	Q_PROPERTY(int dscpAudio READ getDscpAudio WRITE setDscpAudio NOTIFY dscpAudioChanged)
	Q_PROPERTY(int dscpVideo READ getDscpVideo WRITE setDscpVideo NOTIFY dscpVideoChanged)
	
	Q_PROPERTY(bool rlsUriEnabled READ getRlsUriEnabled WRITE setRlsUriEnabled NOTIFY rlsUriEnabledChanged)
	
	// UI. -----------------------------------------------------------------------
	
	Q_PROPERTY(QFont textMessageFont READ getTextMessageFont WRITE setTextMessageFont NOTIFY textMessageFontChanged)
	Q_PROPERTY(int textMessageFontSize READ getTextMessageFontSize WRITE setTextMessageFontSize NOTIFY textMessageFontSizeChanged)
	Q_PROPERTY(QFont emojiFont READ getEmojiFont WRITE setEmojiFont NOTIFY emojiFontChanged)
	Q_PROPERTY(int emojiFontSize READ getEmojiFontSize WRITE setEmojiFontSize NOTIFY emojiFontSizeChanged)
	
	Q_PROPERTY(QString remoteProvisioning READ getRemoteProvisioning WRITE setRemoteProvisioning NOTIFY remoteProvisioningChanged)
	Q_PROPERTY(QString flexiAPIUrl READ getFlexiAPIUrl WRITE setFlexiAPIUrl NOTIFY flexiAPIUrlChanged)
	
	Q_PROPERTY(QString savedScreenshotsFolder READ getSavedScreenshotsFolder WRITE setSavedScreenshotsFolder NOTIFY savedScreenshotsFolderChanged)
	Q_PROPERTY(QString savedCallsFolder READ getSavedCallsFolder WRITE setSavedCallsFolder NOTIFY savedCallsFolderChanged)
	Q_PROPERTY(QString downloadFolder READ getDownloadFolder WRITE setDownloadFolder NOTIFY downloadFolderChanged)
	
	Q_PROPERTY(bool exitOnClose READ getExitOnClose WRITE setExitOnClose NOTIFY exitOnCloseChanged)
	Q_PROPERTY(bool checkForUpdateEnabled READ isCheckForUpdateEnabled WRITE setCheckForUpdateEnabled NOTIFY checkForUpdateEnabledChanged)
	Q_PROPERTY(QString versionCheckUrl READ getVersionCheckUrl WRITE setVersionCheckUrl NOTIFY versionCheckUrlChanged)
	Q_PROPERTY(SettingsModelGUI::VersionCheckType versionCheckType READ getVersionCheckType WRITE setVersionCheckType NOTIFY versionCheckTypeChanged)
	
	Q_PROPERTY(bool showLocalSipAccount READ getShowLocalSipAccount CONSTANT)
	Q_PROPERTY(bool showStartChatButton READ getShowStartChatButton CONSTANT)
	Q_PROPERTY(bool showStartVideoCallButton READ getShowStartVideoCallButton CONSTANT)
	
	Q_PROPERTY(bool mipmapEnabled READ isMipmapEnabled WRITE setMipmapEnabled NOTIFY mipmapEnabledChanged)
	Q_PROPERTY(bool useMinimalTimelineFilter READ useMinimalTimelineFilter WRITE setUseMinimalTimelineFilter NOTIFY useMinimalTimelineFilterChanged)
	
	// Advanced. -----------------------------------------------------------------
	
	Q_PROPERTY(QString logsFolder READ getLogsFolder WRITE setLogsFolder NOTIFY logsFolderChanged)
	Q_PROPERTY(QString logsUploadUrl READ getLogsUploadUrl WRITE setLogsUploadUrl NOTIFY logsUploadUrlChanged)
	Q_PROPERTY(bool logsEnabled READ getLogsEnabled WRITE setLogsEnabled NOTIFY logsEnabledChanged)
	Q_PROPERTY(QString logsEmail READ getLogsEmail WRITE setLogsEmail NOTIFY logsEmailChanged)
	
	Q_PROPERTY(bool isVfsEncrypted READ getVfsEncrypted NOTIFY vfsEncryptedChanged)
	
	Q_PROPERTY(bool developerSettingsEnabled READ getDeveloperSettingsEnabled WRITE setDeveloperSettingsEnabled NOTIFY developerSettingsEnabledChanged)
	
	Q_PROPERTY(bool isInCall READ getIsInCall NOTIFY isInCallChanged)
	
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
	
	SettingsModelGUI (QObject *parent = Q_NULLPTR);
	virtual ~SettingsModelGUI ();
	
	// ===========================================================================
	// METHODS.
	// ===========================================================================
	// Assistant. ----------------------------------------------------------------
	bool getCreateAppSipAccountEnabled () const;
	bool getFetchRemoteConfigurationEnabled () const;
	bool getUseAppSipAccountEnabled () const;
	bool getUseOtherSipAccountEnabled () const;
	bool getAssistantSupportsPhoneNumbers () const;
	QString getAssistantRegistrationUrl () const;
	Q_INVOKABLE bool useWebview() const;
	QString getAssistantLoginUrl () const;
	QString getAssistantLogoutUrl () const;
	bool isCguAccepted () const;
	// SIP Accounts. -------------------------------------------------------------
	QString getDeviceName() const;
	// Audio. --------------------------------------------------------------------
	bool getCaptureGraphRunning() const;
	Q_INVOKABLE float getMicVolume() const;
	float getPlaybackGain() const;
	float getCaptureGain() const;
	QStringList getCaptureDevices () const;
	QStringList getPlaybackDevices () const;
	QString getCaptureDevice () const;
	QString getPlaybackDevice () const;
	QString getRingerDevice () const;
	QString getRingPath () const;
	bool getEchoCancellationEnabled () const;
	bool getShowAudioCodecs () const;
	// Video. --------------------------------------------------------------------
	QStringList getVideoDevices () const;
	QString getVideoDevice () const;
	QString getVideoPreset () const;
	int getVideoFramerate () const;
	QVariantList getSupportedVideoDefinitions () const;
	QVariantMap getVideoDefinition () const;
	Q_INVOKABLE QVariantMap getCurrentPreviewVideoDefinition () const;
	bool getVideoSupported () const;
	bool getShowVideoCodecs () const;
	SettingsModelGUI::CameraMode getGridCameraMode() const;
	SettingsModelGUI::CameraMode getActiveSpeakerCameraMode() const;
	SettingsModelGUI::CameraMode getCallCameraMode() const;
	LinphoneEnums::ConferenceLayout getVideoConferenceLayout() const;
	
	// Chat & calls. -------------------------------------------------------------
	
	bool getAutoAnswerStatus () const;
	bool getAutoAnswerVideoStatus () const;
	int getAutoAnswerDelay () const;
	bool getShowTelKeypadAutomatically () const;
	bool getKeepCallsWindowInBackground () const;
	bool getOutgoingCallsEnabled () const;
	bool getCallRecorderEnabled () const;
	bool getAutomaticallyRecordCalls () const;
	int getAutoDownloadMaxSize() const;
	bool getCallPauseEnabled () const;
	bool getMuteMicrophoneEnabled () const;
	bool getStandardChatEnabled () const;
	bool getSecureChatEnabled () const;
	bool getHideEmptyChatRooms() const;
	bool getWaitRegistrationForCall() const;
	bool getIncallScreenshotEnabled() const;
	bool getGroupChatEnabled()const;
	bool getConferenceEnabled () const;
	bool getVideoConferenceEnabled()const;
	bool getChatNotificationsEnabled () const;
	bool getChatNotificationSoundEnabled () const;
	QString getChatNotificationSoundPath () const;
	QString getFileTransferUrl () const;
	bool getLimeIsSupported () const;
	QVariantList getSupportedMediaEncryptions () const;
	SettingsModelGUI::MediaEncryption getMediaEncryption () const;
	bool mandatoryMediaEncryptionEnabled () const;
	bool getPostQuantumAvailable() const;
	bool getLimeState () const;
	bool getContactsEnabled () const;
	
	// Network. ------------------------------------------------------------------
	
	bool getShowNetworkSettings () const;
	bool getUseSipInfoForDtmfs () const;
	bool getUseRfc2833ForDtmfs () const;
	bool getIpv6Enabled () const;
	int getDownloadBandwidth () const;
	int getUploadBandwidth () const;
	bool getAdaptiveRateControlEnabled () const;
	int getTcpPort () const;
	int getUdpPort () const;
	QList<int> getAudioPortRange () const;
	QList<int> getVideoPortRange () const;
	bool getIceEnabled () const;
	bool getTurnEnabled () const;
	QString getStunServer () const;
	QString getTurnUser () const;
	QString getTurnPassword () const;
	int getDscpSip () const;
	int getDscpAudio () const;
	int getDscpVideo () const;
	bool getRlsUriEnabled () const;
	Q_INVOKABLE bool tunnelAvailable() const;
	Q_INVOKABLE TunnelModel * getTunnel() const;
	
	// UI. -----------------------------------------------------------------------
	
	QFont getTextMessageFont() const;
	int getTextMessageFontSize() const;
	QFont getEmojiFont() const;
	int getEmojiFontSize() const;
	QString getSavedScreenshotsFolder () const;
	QString getSavedCallsFolder () const;
	QString getDownloadFolder () const;
	QString getRemoteProvisioning () const;
	Q_INVOKABLE bool isQRCodeAvailable() const;
	QString getFlexiAPIUrl() const;
	bool getExitOnClose () const;
	Q_INVOKABLE bool isCheckForUpdateAvailable();
	bool isCheckForUpdateEnabled() const;
	QString getVersionCheckUrl() const;
	SettingsModelGUI::VersionCheckType getVersionCheckType() const;
	Q_INVOKABLE bool haveVersionNightlyUrl()const;
	Q_INVOKABLE bool getShowLocalSipAccount () const;
	Q_INVOKABLE bool getShowStartChatButton () const;
	Q_INVOKABLE bool getShowStartVideoCallButton () const;
	bool isMipmapEnabled() const;
	bool useMinimalTimelineFilter() const;
	
	// Advanced. ---------------------------------------------------------------------------
	
	Q_INVOKABLE QString getLogText()const;
	QString getLogsFolder () const;
	QString getLogsUploadUrl () const;
	bool getLogsEnabled () const;
	QString getLogsEmail () const;
	bool getVfsEncrypted () const;
	Q_INVOKABLE bool isLdapAvailable() const;
	// OAuth 2
	Q_INVOKABLE bool isOAuth2Available() const;
	// ---------------------------------------------------------------------------
	Q_INVOKABLE bool isDeveloperSettingsAvailable() const;
	bool getDeveloperSettingsEnabled () const;
	bool getIsInCall() const;
	
signals:

	Q_INVOKABLE void onSettingsTabChanged(int idx);
	Q_INVOKABLE void settingsWindowClosing(void);
	Q_INVOKABLE void reloadDevices();
	// Assistant. ----------------------------------------------------------------
	void setCreateAppSipAccountEnabled (bool status);
	void setFetchRemoteConfigurationEnabled (bool status);
	void setUseAppSipAccountEnabled (bool status);
	void setUseOtherSipAccountEnabled (bool status);
	void setAssistantSupportsPhoneNumbers (bool status);
	void setAssistantRegistrationUrl (QString url);
	void setAssistantLoginUrl (QString url);
	void setAssistantLogoutUrl (QString url);
	void acceptCgu(const bool accept);
	
	// SIP Accounts. -------------------------------------------------------------
	
	void setDeviceName(const QString& deviceName);
	
	// Audio. --------------------------------------------------------------------
	
	Q_INVOKABLE void startCaptureGraph();
	Q_INVOKABLE void stopCaptureGraph();
	Q_INVOKABLE void resetCaptureGraph();
	void setPlaybackGain(float gain);
	void setCaptureGain(float gain);
	void setCaptureDevice (const QString &device);
	void setPlaybackDevice (const QString &device);
	void setRingerDevice (const QString &device);
	void setRingPath (const QString &path);
	void setEchoCancellationEnabled (bool status);
	Q_INVOKABLE void startEchoCancellerCalibration();
	void setShowAudioCodecs (bool status);
	
	// Video. --------------------------------------------------------------------
	
	//Called from qml when accessing audio settings panel
	Q_INVOKABLE void accessVideoSettings();
	void setVideoDevice (const QString &device);
	void setVideoPreset (const QString &preset);
	void setVideoFramerate (int framerate);
	Q_INVOKABLE void setHighMosaicQuality();
	Q_INVOKABLE void setLimitedMosaicQuality();
	void setVideoDefinition (const QVariantMap &definition);
	void setShowVideoCodecs (bool status);
	Q_INVOKABLE void setCameraMode(CameraMode mode);
	// Custom modes to set default for setCameraMode
	void setGridCameraMode(CameraMode mode);
	void setActiveSpeakerCameraMode(CameraMode mode);
	void setCallCameraMode(CameraMode mode);
	void setVideoConferenceLayout(LinphoneEnums::ConferenceLayout layout);
	
	// Chat & calls. -------------------------------------------------------------
	
	void setAutoAnswerStatus (bool status);
	void setAutoAnswerVideoStatus (bool status);
	void setAutoAnswerDelay (int delay);
	void setShowTelKeypadAutomatically (bool status);
	void setKeepCallsWindowInBackground (bool status);
	void setOutgoingCallsEnabled (bool status);
	void setCallRecorderEnabled (bool status);
	void setAutomaticallyRecordCalls (bool status);
	void setAutoDownloadMaxSize(int maxSize);
	void setCallPauseEnabled (bool status);
	void setMuteMicrophoneEnabled (bool status);
	void setStandardChatEnabled (bool status);
	void setSecureChatEnabled (bool status);
	void setHideEmptyChatRooms(const bool& data);
	void setWaitRegistrationForCall(const bool& status);
	void setIncallScreenshotEnabled(const bool& status);
	void setConferenceEnabled (bool status);
	void setChatNotificationsEnabled (bool status);
	void setChatNotificationSoundEnabled (bool status);
	void setChatNotificationSoundPath (const QString &path);
	void setFileTransferUrl (const QString &url);
	void setMediaEncryption (SettingsModelGUI::MediaEncryption encryption);
	void enableMandatoryMediaEncryption(bool mandatory);
	void setLimeState (const bool& state);
	void setContactsEnabled (bool status);
	
	// Network. ------------------------------------------------------------------
	
	void setShowNetworkSettings (bool status);
	void setUseSipInfoForDtmfs (bool status);
	void setUseRfc2833ForDtmfs (bool status);
	void setIpv6Enabled (bool status);
	void setDownloadBandwidth (int bandwidth);
	void setUploadBandwidth (int bandwidth);
	void setAdaptiveRateControlEnabled (bool status);
	void setTcpPort (int port);
	void setUdpPort (int port);
	void setAudioPortRange (const QList<int> &range);
	void setVideoPortRange (const QList<int> &range);
	void setIceEnabled (bool status);
	void setTurnEnabled (bool status);
	void setStunServer (const QString &stunServer);
	void setTurnUser (const QString &user);
	void setTurnPassword (const QString &password);
	void setDscpSip (int dscp);
	void setDscpAudio (int dscp);
	void setDscpVideo (int dscp);
	void setRlsUriEnabled (bool status);
	
	// UI. -----------------------------------------------------------------------
	
	void setTextMessageFont(const QFont& font);
	void setTextMessageFontSize(const int& size);
	void setEmojiFont(const QFont& font);
	void setEmojiFontSize(const int& size);
	void setSavedScreenshotsFolder (const QString &folder);
	void setSavedCallsFolder (const QString &folder);
	void setDownloadFolder (const QString &folder);
	void setRemoteProvisioning (const QString &remoteProvisioning);
	void setFlexiAPIUrl (const QString &url);
	void setExitOnClose (bool value);
	void setCheckForUpdateEnabled(bool enable);
	void setVersionCheckUrl(const QString& url);
	void setVersionCheckType(const VersionCheckType& type);
	void setMipmapEnabled(const bool& enabled);
	void setUseMinimalTimelineFilter(const bool& useMinimal);
	
	// Advanced. ---------------------------------------------------------------------------
	
	void setLogsFolder (const QString &folder);
	void setLogsUploadUrl (const QString &url);
	void setLogsEnabled (bool status);
	void setLogsEmail (const QString &email);
	Q_INVOKABLE void setVfsEncrypted (bool encrypted, const bool deleteUserData);
	void setDeveloperSettingsEnabled (bool status);
	
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
	
	// SYNC

	DECLARE_SYNC_SIGNAL(bool, getCreateAppSipAccountEnabled)
	DECLARE_SYNC_SIGNAL(bool, getFetchRemoteConfigurationEnabled)
	DECLARE_SYNC_SIGNAL(bool, getUseAppSipAccountEnabled)
	DECLARE_SYNC_SIGNAL(bool, getUseOtherSipAccountEnabled)
	DECLARE_SYNC_SIGNAL(bool, getAssistantSupportsPhoneNumbers)
	DECLARE_SYNC_SIGNAL(bool, useWebview)
	DECLARE_SYNC_SIGNAL(QString, getAssistantRegistrationUrl)
	DECLARE_SYNC_SIGNAL(QString, getAssistantLoginUrl)
	DECLARE_SYNC_SIGNAL(QString, getAssistantLogoutUrl)
	DECLARE_SYNC_SIGNAL(bool, isCguAccepted)
	DECLARE_SYNC_SIGNAL(QString, getDeviceName)
	DECLARE_SYNC_SIGNAL(float, getMicVolume)
	DECLARE_SYNC_SIGNAL(float, getPlaybackGain)
	DECLARE_SYNC_SIGNAL(float, getCaptureGain)
	DECLARE_SYNC_SIGNAL(bool, getCaptureGraphRunning)
	DECLARE_SYNC_SIGNAL(QStringList, getCaptureDevices)
	DECLARE_SYNC_SIGNAL(QStringList, getPlaybackDevices)
	DECLARE_SYNC_SIGNAL(QString, getCaptureDevice)
	DECLARE_SYNC_SIGNAL(QString, getPlaybackDevice)
	DECLARE_SYNC_SIGNAL(QString, getRingerDevice)
	DECLARE_SYNC_SIGNAL(QString, getRingPath)
	DECLARE_SYNC_SIGNAL(bool, getEchoCancellationEnabled)
	DECLARE_SYNC_SIGNAL(bool, getShowAudioCodecs)
	DECLARE_SYNC_SIGNAL(QStringList, getVideoDevices)
	DECLARE_SYNC_SIGNAL(QString, getVideoDevice)
	DECLARE_SYNC_SIGNAL(QString, getVideoPreset)
	DECLARE_SYNC_SIGNAL(int, getVideoFramerate)
	DECLARE_SYNC_SIGNAL(QVariantList, getSupportedVideoDefinitions)
	DECLARE_SYNC_SIGNAL(QVariantMap, getVideoDefinition)
	DECLARE_SYNC_SIGNAL(QVariantMap, getCurrentPreviewVideoDefinition)
	DECLARE_SYNC_SIGNAL(bool, getVideoSupported)
	DECLARE_SYNC_SIGNAL(bool, getShowVideoCodecs)
	DECLARE_SYNC_SIGNAL_ENUM(CameraMode, getGridCameraMode, SettingsModel)
	DECLARE_SYNC_SIGNAL_ENUM(CameraMode, getActiveSpeakerCameraMode, SettingsModel)
	DECLARE_SYNC_SIGNAL_ENUM(CameraMode, getCallCameraMode, SettingsModel)
	DECLARE_SYNC_SIGNAL(LinphoneEnums::ConferenceLayout, getVideoConferenceLayout)
	DECLARE_SYNC_SIGNAL(bool, getAutoAnswerStatus)
	DECLARE_SYNC_SIGNAL(bool, getAutoAnswerVideoStatus)
	DECLARE_SYNC_SIGNAL(int, getAutoAnswerDelay)
	DECLARE_SYNC_SIGNAL(bool, getShowTelKeypadAutomatically)
	DECLARE_SYNC_SIGNAL(bool, getKeepCallsWindowInBackground)
	DECLARE_SYNC_SIGNAL(bool, getOutgoingCallsEnabled)
	DECLARE_SYNC_SIGNAL(bool, getCallRecorderEnabled)
	DECLARE_SYNC_SIGNAL(bool, getAutomaticallyRecordCalls)
	DECLARE_SYNC_SIGNAL(int, getAutoDownloadMaxSize)
	DECLARE_SYNC_SIGNAL(bool, getCallPauseEnabled)
	DECLARE_SYNC_SIGNAL(bool, getMuteMicrophoneEnabled)
	DECLARE_SYNC_SIGNAL(bool, getStandardChatEnabled)
	DECLARE_SYNC_SIGNAL(bool, getSecureChatEnabled)
	DECLARE_SYNC_SIGNAL(bool, getHideEmptyChatRooms)
	DECLARE_SYNC_SIGNAL(bool, getWaitRegistrationForCall)
	DECLARE_SYNC_SIGNAL(bool, getIncallScreenshotEnabled)
	DECLARE_SYNC_SIGNAL(bool, getGroupChatEnabled)
	DECLARE_SYNC_SIGNAL(bool, getConferenceEnabled)
	DECLARE_SYNC_SIGNAL(bool, getVideoConferenceEnabled)
	DECLARE_SYNC_SIGNAL(bool, getChatNotificationsEnabled)
	DECLARE_SYNC_SIGNAL(bool, getChatNotificationSoundEnabled)
	DECLARE_SYNC_SIGNAL(QString, getChatNotificationSoundPath)
	DECLARE_SYNC_SIGNAL(QString, getFileTransferUrl)
	DECLARE_SYNC_SIGNAL(bool, getLimeIsSupported)
	DECLARE_SYNC_SIGNAL(QVariantList, getSupportedMediaEncryptions)
	DECLARE_SYNC_SIGNAL_ENUM(MediaEncryption, getMediaEncryption, SettingsModel)
	DECLARE_SYNC_SIGNAL(bool, mandatoryMediaEncryptionEnabled)
	DECLARE_SYNC_SIGNAL(bool, getPostQuantumAvailable)
	DECLARE_SYNC_SIGNAL(bool, getLimeState)
	DECLARE_SYNC_SIGNAL(bool, getContactsEnabled)
	DECLARE_SYNC_SIGNAL(bool, getShowNetworkSettings)
	DECLARE_SYNC_SIGNAL(bool, getUseSipInfoForDtmfs)
	DECLARE_SYNC_SIGNAL(bool, getUseRfc2833ForDtmfs)
	DECLARE_SYNC_SIGNAL(bool, getIpv6Enabled)
	DECLARE_SYNC_SIGNAL(int, getDownloadBandwidth)
	DECLARE_SYNC_SIGNAL(int, getUploadBandwidth)
	DECLARE_SYNC_SIGNAL(bool, getAdaptiveRateControlEnabled)
	DECLARE_SYNC_SIGNAL(int, getTcpPort)
	DECLARE_SYNC_SIGNAL(int, getUdpPort)
	DECLARE_SYNC_SIGNAL(QList<int>, getAudioPortRange)
	DECLARE_SYNC_SIGNAL(QList<int>, getVideoPortRange)
	DECLARE_SYNC_SIGNAL(bool, getIceEnabled)
	DECLARE_SYNC_SIGNAL(bool, getTurnEnabled)
	DECLARE_SYNC_SIGNAL(QString, getStunServer)
	DECLARE_SYNC_SIGNAL(QString, getTurnUser)
	DECLARE_SYNC_SIGNAL(QString, getTurnPassword)
	DECLARE_SYNC_SIGNAL(int, getDscpSip)
	DECLARE_SYNC_SIGNAL(int, getDscpAudio)
	DECLARE_SYNC_SIGNAL(int, getDscpVideo)
	DECLARE_SYNC_SIGNAL(bool, getRlsUriEnabled)
	DECLARE_SYNC_SIGNAL(bool, tunnelAvailable)
	DECLARE_SYNC_SIGNAL(TunnelModel *, getTunnel)
	DECLARE_SYNC_SIGNAL(QFont, getTextMessageFont)
	DECLARE_SYNC_SIGNAL(int, getTextMessageFontSize)
	DECLARE_SYNC_SIGNAL(QFont, getEmojiFont)
	DECLARE_SYNC_SIGNAL(int, getEmojiFontSize)
	DECLARE_SYNC_SIGNAL(QString, getSavedScreenshotsFolder)
	DECLARE_SYNC_SIGNAL(QString, getSavedCallsFolder)
	DECLARE_SYNC_SIGNAL(QString, getDownloadFolder)
	DECLARE_SYNC_SIGNAL(QString, getRemoteProvisioning)
	DECLARE_SYNC_SIGNAL(bool, isQRCodeAvailable)
	DECLARE_SYNC_SIGNAL(QString, getFlexiAPIUrl)
	DECLARE_SYNC_SIGNAL(bool, getExitOnClose)
	DECLARE_SYNC_SIGNAL(bool, isCheckForUpdateAvailable)
	DECLARE_SYNC_SIGNAL(bool, isCheckForUpdateEnabled)
	DECLARE_SYNC_SIGNAL(QString, getVersionCheckUrl)
	DECLARE_SYNC_SIGNAL_ENUM(VersionCheckType, getVersionCheckType, SettingsModel)
	DECLARE_SYNC_SIGNAL(bool, haveVersionNightlyUrl)
	DECLARE_SYNC_SIGNAL(bool, getShowLocalSipAccount)
	DECLARE_SYNC_SIGNAL(bool, getShowStartChatButton)
	DECLARE_SYNC_SIGNAL(bool, getShowStartVideoCallButton)
	DECLARE_SYNC_SIGNAL(bool, isMipmapEnabled)
	DECLARE_SYNC_SIGNAL(bool, useMinimalTimelineFilter)
	DECLARE_SYNC_SIGNAL(QString, getLogText)
	DECLARE_SYNC_SIGNAL(QString, getLogsFolder)
	DECLARE_SYNC_SIGNAL(QString, getLogsUploadUrl)
	DECLARE_SYNC_SIGNAL(bool, getLogsEnabled)
	DECLARE_SYNC_SIGNAL(QString, getLogsEmail)
	DECLARE_SYNC_SIGNAL(bool, getVfsEncrypted)
	DECLARE_SYNC_SIGNAL(bool, isLdapAvailable)
	DECLARE_SYNC_SIGNAL(bool, isOAuth2Available)
	DECLARE_SYNC_SIGNAL(bool, isDeveloperSettingsAvailable)
	DECLARE_SYNC_SIGNAL(bool, getDeveloperSettingsEnabled)
	DECLARE_SYNC_SIGNAL(bool, getIsInCall)
};

#endif
