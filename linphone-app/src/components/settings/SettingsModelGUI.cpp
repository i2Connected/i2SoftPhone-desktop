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

#include "SettingsModelGUI.hpp"
#include "components/core/CoreManager.hpp"
#include "SettingsModel.hpp"

// =============================================================================

SettingsModelGUI::SettingsModelGUI(QObject * parent) : QObject(parent){
	auto appModel = CoreManager::getInstance()->getSettingsModel();
	// signals
	CONNECT_CORE_TO_GUI(createAppSipAccountEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(fetchRemoteConfigurationEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(useAppSipAccountEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(useOtherSipAccountEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(assistantSupportsPhoneNumbersChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(assistantRegistrationUrlChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(assistantLoginUrlChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(assistantLogoutUrlChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(cguAcceptedChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(deviceNameChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(captureGraphRunningChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(playbackGainChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(captureGainChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(captureDevicesChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(playbackDevicesChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(captureDeviceChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(playbackDeviceChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(ringerDeviceChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(ringPathChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(echoCancellationStatus, SettingsModel);
	CONNECT_CORE_TO_GUI(showAudioCodecsChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(videoDevicesChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(videoDeviceChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(videoPresetChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(videoFramerateChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(videoDefinitionChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(showVideoCodecsChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(cameraModeChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(gridCameraModeChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(activeSpeakerCameraModeChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(callCameraModeChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(videoConferenceLayoutChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(autoAnswerStatusChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(autoAnswerVideoStatusChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(autoAnswerDelayChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(showTelKeypadAutomaticallyChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(keepCallsWindowInBackgroundChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(outgoingCallsEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(callRecorderEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(autoDownloadMaxSizeChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(callPauseEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(muteMicrophoneEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(standardChatEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(secureChatEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(groupChatEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(hideEmptyChatRoomsChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(waitRegistrationForCallChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(incallScreenshotEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(conferenceEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(videoConferenceEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(chatNotificationsEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(chatNotificationSoundEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(chatNotificationSoundPathChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(fileTransferUrlChanged, SettingsModel);
	CONNECT_CORE_TO_GUI_ENUM(mediaEncryptionChanged, MediaEncryption, SettingsModel);
	CONNECT_CORE_TO_GUI(limeStateChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(contactsEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(showNetworkSettingsChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(dtmfsProtocolChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(ipv6EnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(downloadBandWidthChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(uploadBandWidthChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(adaptiveRateControlEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(tcpPortChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(udpPortChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(audioPortRangeChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(videoPortRangeChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(iceEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(turnEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(stunServerChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(turnUserChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(turnPasswordChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(dscpSipChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(dscpAudioChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(dscpVideoChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(rlsUriEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(textMessageFontChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(textMessageFontSizeChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(emojiFontChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(emojiFontSizeChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(savedScreenshotsFolderChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(savedCallsFolderChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(downloadFolderChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(remoteProvisioningChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(remoteProvisioningNotChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(flexiAPIUrlChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(exitOnCloseChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(mipmapEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(useMinimalTimelineFilterChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(checkForUpdateEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(versionCheckUrlChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(versionCheckTypeChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(logsFolderChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(logsUploadUrlChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(logsEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(logsEmailChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(vfsEncryptedChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(contactImporterChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(developerSettingsEnabledChanged, SettingsModel);
	CONNECT_CORE_TO_GUI(isInCallChanged, SettingsModel);
	
	// Setters/tools
	
	CONNECT_GUI_TO_CORE(onSettingsTabChanged, SettingsModel);
	CONNECT_GUI_TO_CORE(settingsWindowClosing, SettingsModel);
	CONNECT_GUI_TO_CORE(reloadDevices, SettingsModel);
	CONNECT_GUI_TO_CORE(setCreateAppSipAccountEnabled, SettingsModel);
	CONNECT_GUI_TO_CORE(setFetchRemoteConfigurationEnabled, SettingsModel);
	CONNECT_GUI_TO_CORE(setUseAppSipAccountEnabled, SettingsModel);
	CONNECT_GUI_TO_CORE(setUseOtherSipAccountEnabled, SettingsModel);
	CONNECT_GUI_TO_CORE(setAssistantRegistrationUrl, SettingsModel);
	CONNECT_GUI_TO_CORE(setAssistantSupportsPhoneNumbers, SettingsModel);
	CONNECT_GUI_TO_CORE(setAssistantLoginUrl, SettingsModel);
	CONNECT_GUI_TO_CORE(setAssistantLogoutUrl, SettingsModel);
	CONNECT_GUI_TO_CORE(acceptCgu, SettingsModel);
	CONNECT_GUI_TO_CORE(setDeviceName, SettingsModel);
	CONNECT_GUI_TO_CORE(startCaptureGraph, SettingsModel);
	CONNECT_GUI_TO_CORE(stopCaptureGraph, SettingsModel);
	CONNECT_GUI_TO_CORE(resetCaptureGraph, SettingsModel);
	CONNECT_GUI_TO_CORE(setPlaybackGain, SettingsModel);
	CONNECT_GUI_TO_CORE(setCaptureGain, SettingsModel);
	CONNECT_GUI_TO_CORE(setCaptureDevice, SettingsModel);
	CONNECT_GUI_TO_CORE(setPlaybackDevice, SettingsModel);
	CONNECT_GUI_TO_CORE(setRingerDevice, SettingsModel);
	CONNECT_GUI_TO_CORE(setRingPath, SettingsModel);
	CONNECT_GUI_TO_CORE(setEchoCancellationEnabled, SettingsModel);
	CONNECT_GUI_TO_CORE(startEchoCancellerCalibration, SettingsModel);
	CONNECT_GUI_TO_CORE(setShowAudioCodecs, SettingsModel);
	CONNECT_GUI_TO_CORE(accessVideoSettings, SettingsModel);
	CONNECT_GUI_TO_CORE(setVideoDevice, SettingsModel);
	CONNECT_GUI_TO_CORE(setVideoPreset, SettingsModel);
	CONNECT_GUI_TO_CORE(setVideoFramerate, SettingsModel);
	CONNECT_GUI_TO_CORE(setHighMosaicQuality, SettingsModel);
	CONNECT_GUI_TO_CORE(setLimitedMosaicQuality, SettingsModel);
	CONNECT_GUI_TO_CORE(setVideoDefinition, SettingsModel);
	CONNECT_GUI_TO_CORE(setShowVideoCodecs, SettingsModel);
	CONNECT_GUI_TO_CORE_ENUM(setCameraMode, CameraMode, SettingsModel);
	CONNECT_GUI_TO_CORE_ENUM(setGridCameraMode, CameraMode, SettingsModel);
	CONNECT_GUI_TO_CORE_ENUM(setActiveSpeakerCameraMode, CameraMode, SettingsModel);
	CONNECT_GUI_TO_CORE_ENUM(setCallCameraMode, CameraMode, SettingsModel);
	CONNECT_GUI_TO_CORE(setVideoConferenceLayout, SettingsModel);
	CONNECT_GUI_TO_CORE(setAutoAnswerStatus, SettingsModel);
	CONNECT_GUI_TO_CORE(setAutoAnswerVideoStatus, SettingsModel);
	CONNECT_GUI_TO_CORE(setAutoAnswerDelay, SettingsModel);
	CONNECT_GUI_TO_CORE(setShowTelKeypadAutomatically, SettingsModel);
	CONNECT_GUI_TO_CORE(setKeepCallsWindowInBackground, SettingsModel);
	CONNECT_GUI_TO_CORE(setOutgoingCallsEnabled, SettingsModel);
	CONNECT_GUI_TO_CORE(setCallRecorderEnabled, SettingsModel);
	CONNECT_GUI_TO_CORE(setAutomaticallyRecordCalls, SettingsModel);
	CONNECT_GUI_TO_CORE(setAutoDownloadMaxSize, SettingsModel);
	CONNECT_GUI_TO_CORE(setCallPauseEnabled, SettingsModel);
	CONNECT_GUI_TO_CORE(setMuteMicrophoneEnabled, SettingsModel);
	CONNECT_GUI_TO_CORE(setStandardChatEnabled, SettingsModel);
	CONNECT_GUI_TO_CORE(setSecureChatEnabled, SettingsModel);
	CONNECT_GUI_TO_CORE(setHideEmptyChatRooms, SettingsModel);
	CONNECT_GUI_TO_CORE(setWaitRegistrationForCall, SettingsModel);
	CONNECT_GUI_TO_CORE(setIncallScreenshotEnabled, SettingsModel);
	CONNECT_GUI_TO_CORE(setConferenceEnabled, SettingsModel);
	CONNECT_GUI_TO_CORE(setChatNotificationsEnabled, SettingsModel);
	CONNECT_GUI_TO_CORE(setChatNotificationSoundEnabled, SettingsModel);
	CONNECT_GUI_TO_CORE(setChatNotificationSoundPath, SettingsModel);
	CONNECT_GUI_TO_CORE(setFileTransferUrl, SettingsModel);
	CONNECT_GUI_TO_CORE_ENUM(setMediaEncryption, MediaEncryption, SettingsModel);
	CONNECT_GUI_TO_CORE(enableMandatoryMediaEncryption, SettingsModel);
	CONNECT_GUI_TO_CORE(setLimeState, SettingsModel);
	CONNECT_GUI_TO_CORE(setContactsEnabled, SettingsModel);
	CONNECT_GUI_TO_CORE(setShowNetworkSettings, SettingsModel);
	CONNECT_GUI_TO_CORE(setUseSipInfoForDtmfs, SettingsModel);
	CONNECT_GUI_TO_CORE(setUseRfc2833ForDtmfs, SettingsModel);
	CONNECT_GUI_TO_CORE(setIpv6Enabled, SettingsModel);
	CONNECT_GUI_TO_CORE(setDownloadBandwidth, SettingsModel);
	CONNECT_GUI_TO_CORE(setUploadBandwidth, SettingsModel);
	CONNECT_GUI_TO_CORE(setAdaptiveRateControlEnabled, SettingsModel);
	CONNECT_GUI_TO_CORE(setTcpPort, SettingsModel);
	CONNECT_GUI_TO_CORE(setUdpPort, SettingsModel);
	CONNECT_GUI_TO_CORE(setAudioPortRange, SettingsModel);
	CONNECT_GUI_TO_CORE(setVideoPortRange, SettingsModel);
	CONNECT_GUI_TO_CORE(setIceEnabled, SettingsModel);
	CONNECT_GUI_TO_CORE(setTurnEnabled, SettingsModel);
	CONNECT_GUI_TO_CORE(setStunServer, SettingsModel);
	CONNECT_GUI_TO_CORE(setTurnUser, SettingsModel);
	CONNECT_GUI_TO_CORE(setTurnPassword, SettingsModel);
	CONNECT_GUI_TO_CORE(setDscpSip, SettingsModel);
	CONNECT_GUI_TO_CORE(setDscpAudio, SettingsModel);
	CONNECT_GUI_TO_CORE(setDscpVideo, SettingsModel);
	CONNECT_GUI_TO_CORE(setRlsUriEnabled, SettingsModel);
	CONNECT_GUI_TO_CORE(setTextMessageFont, SettingsModel);
	CONNECT_GUI_TO_CORE(setTextMessageFontSize, SettingsModel);
	CONNECT_GUI_TO_CORE(setEmojiFont, SettingsModel);
	CONNECT_GUI_TO_CORE(setEmojiFontSize, SettingsModel);
	CONNECT_GUI_TO_CORE(setSavedScreenshotsFolder, SettingsModel);
	CONNECT_GUI_TO_CORE(setSavedCallsFolder, SettingsModel);
	CONNECT_GUI_TO_CORE(setDownloadFolder, SettingsModel);
	CONNECT_GUI_TO_CORE(setRemoteProvisioning, SettingsModel);
	CONNECT_GUI_TO_CORE(setFlexiAPIUrl, SettingsModel);
	CONNECT_GUI_TO_CORE(setExitOnClose, SettingsModel);
	CONNECT_GUI_TO_CORE(setCheckForUpdateEnabled, SettingsModel);
	CONNECT_GUI_TO_CORE(setVersionCheckUrl, SettingsModel);
	CONNECT_GUI_TO_CORE_ENUM(setVersionCheckType, VersionCheckType, SettingsModel);
	CONNECT_GUI_TO_CORE(setMipmapEnabled, SettingsModel);
	CONNECT_GUI_TO_CORE(setUseMinimalTimelineFilter, SettingsModel);
	CONNECT_GUI_TO_CORE(setLogsFolder, SettingsModel);
	CONNECT_GUI_TO_CORE(setLogsEnabled, SettingsModel);
	CONNECT_GUI_TO_CORE(setLogsEmail, SettingsModel);
	CONNECT_GUI_TO_CORE(setLogsUploadUrl, SettingsModel);
	CONNECT_GUI_TO_CORE(setVfsEncrypted, SettingsModel);
	CONNECT_GUI_TO_CORE(setDeveloperSettingsEnabled, SettingsModel);
	
	
	
	// Getters
	CONNECT_SYNC_TO_SLOT(getCreateAppSipAccountEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getFetchRemoteConfigurationEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getAssistantSupportsPhoneNumbers, SettingsModel);
	CONNECT_SYNC_TO_SLOT(useWebview, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getAssistantRegistrationUrl, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getUseAppSipAccountEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getUseOtherSipAccountEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getAssistantLoginUrl, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getAssistantLogoutUrl, SettingsModel);
	CONNECT_SYNC_TO_SLOT(isCguAccepted, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getDeviceName, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getMicVolume, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getPlaybackGain, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getCaptureGain, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getCaptureDevices, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getPlaybackDevices, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getCaptureDevice, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getPlaybackDevice, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getRingerDevice, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getRingPath, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getEchoCancellationEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getShowAudioCodecs, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getVideoDevices, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getVideoDevice, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getVideoPreset, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getVideoFramerate, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getSupportedVideoDefinitions, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getVideoDefinition, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getCurrentPreviewVideoDefinition, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getVideoSupported, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getShowVideoCodecs, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getGridCameraMode, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getActiveSpeakerCameraMode, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getCallCameraMode, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getVideoConferenceLayout, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getAutoAnswerStatus, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getAutoAnswerVideoStatus, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getAutoAnswerDelay, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getShowTelKeypadAutomatically, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getKeepCallsWindowInBackground, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getOutgoingCallsEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getCallRecorderEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getAutomaticallyRecordCalls, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getAutoDownloadMaxSize, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getCallPauseEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getMuteMicrophoneEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getStandardChatEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getSecureChatEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getHideEmptyChatRooms, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getWaitRegistrationForCall, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getIncallScreenshotEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getGroupChatEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getConferenceEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getVideoConferenceEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getChatNotificationsEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getChatNotificationSoundEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getChatNotificationSoundPath, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getFileTransferUrl, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getLimeIsSupported, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getSupportedMediaEncryptions, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getMediaEncryption, SettingsModel);
	CONNECT_SYNC_TO_SLOT(mandatoryMediaEncryptionEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getPostQuantumAvailable, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getLimeState, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getContactsEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getShowNetworkSettings, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getUseSipInfoForDtmfs, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getUseRfc2833ForDtmfs, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getIpv6Enabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getDownloadBandwidth, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getUploadBandwidth, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getAdaptiveRateControlEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getTcpPort, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getUdpPort, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getAudioPortRange, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getVideoPortRange, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getIceEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getTurnEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getStunServer, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getTurnUser, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getTurnPassword, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getDscpSip, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getDscpAudio, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getDscpVideo, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getRlsUriEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(tunnelAvailable, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getTunnel, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getTextMessageFont, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getTextMessageFontSize, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getEmojiFont, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getEmojiFontSize, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getSavedScreenshotsFolder, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getSavedCallsFolder, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getDownloadFolder, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getRemoteProvisioning, SettingsModel);
	CONNECT_SYNC_TO_SLOT(isQRCodeAvailable, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getFlexiAPIUrl, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getExitOnClose, SettingsModel);
	CONNECT_SYNC_TO_SLOT(isCheckForUpdateEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getVersionCheckUrl, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getVersionCheckType, SettingsModel);
	CONNECT_SYNC_TO_SLOT(haveVersionNightlyUrl, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getShowLocalSipAccount, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getShowStartChatButton, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getShowStartVideoCallButton, SettingsModel);
	CONNECT_SYNC_TO_SLOT(isMipmapEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(useMinimalTimelineFilter, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getLogText, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getLogsFolder, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getLogsUploadUrl, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getLogsEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getLogsEmail, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getVfsEncrypted, SettingsModel);
	CONNECT_SYNC_TO_SLOT(isLdapAvailable, SettingsModel);
	CONNECT_SYNC_TO_SLOT(isOAuth2Available, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getLogsFolder, SettingsModel);
	CONNECT_SYNC_TO_SLOT(isDeveloperSettingsAvailable, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getDeveloperSettingsEnabled, SettingsModel);
	CONNECT_SYNC_TO_SLOT(getIsInCall, SettingsModel);
	
}

SettingsModelGUI::~SettingsModelGUI(){
}

DECLARE_GETTER(bool, getCreateAppSipAccountEnabled, SettingsModel)
DECLARE_GETTER(bool, getFetchRemoteConfigurationEnabled, SettingsModel)
DECLARE_GETTER(bool, getUseAppSipAccountEnabled, SettingsModel)
DECLARE_GETTER(bool, getUseOtherSipAccountEnabled, SettingsModel)
DECLARE_GETTER(bool, getAssistantSupportsPhoneNumbers, SettingsModel)
DECLARE_GETTER(bool, useWebview, SettingsModel)
DECLARE_GETTER(QString, getAssistantRegistrationUrl, SettingsModel)
DECLARE_GETTER(QString, getAssistantLoginUrl, SettingsModel)
DECLARE_GETTER(QString, getAssistantLogoutUrl, SettingsModel)
DECLARE_GETTER(bool, isCguAccepted, SettingsModel)
DECLARE_GETTER(QString, getDeviceName, SettingsModel)
DECLARE_GETTER(float, getMicVolume, SettingsModel)
DECLARE_GETTER(float, getPlaybackGain, SettingsModel)
DECLARE_GETTER(float, getCaptureGain, SettingsModel)
DECLARE_GETTER(bool, getCaptureGraphRunning, SettingsModel)
DECLARE_GETTER(QStringList, getCaptureDevices, SettingsModel)
DECLARE_GETTER(QStringList, getPlaybackDevices, SettingsModel)
DECLARE_GETTER(QString, getCaptureDevice, SettingsModel)
DECLARE_GETTER(QString, getPlaybackDevice, SettingsModel)
DECLARE_GETTER(QString, getRingerDevice, SettingsModel)
DECLARE_GETTER(QString, getRingPath, SettingsModel)
DECLARE_GETTER(bool, getEchoCancellationEnabled, SettingsModel)
DECLARE_GETTER(bool, getShowAudioCodecs, SettingsModel)
DECLARE_GETTER(QStringList, getVideoDevices, SettingsModel)
DECLARE_GETTER(QString, getVideoDevice, SettingsModel)
DECLARE_GETTER(QString, getVideoPreset, SettingsModel)
DECLARE_GETTER(int, getVideoFramerate, SettingsModel)
DECLARE_GETTER(QVariantList, getSupportedVideoDefinitions, SettingsModel)
DECLARE_GETTER(QVariantMap, getVideoDefinition, SettingsModel)
DECLARE_GETTER(QVariantMap, getCurrentPreviewVideoDefinition, SettingsModel)
DECLARE_GETTER(bool, getVideoSupported, SettingsModel)
DECLARE_GETTER(bool, getShowVideoCodecs, SettingsModel)
DECLARE_GETTER_ENUM(CameraMode, getGridCameraMode, SettingsModel)
DECLARE_GETTER_ENUM(CameraMode, getActiveSpeakerCameraMode, SettingsModel)
DECLARE_GETTER_ENUM(CameraMode, getCallCameraMode, SettingsModel)
DECLARE_GETTER(LinphoneEnums::ConferenceLayout, getVideoConferenceLayout, SettingsModel)
DECLARE_GETTER(bool, getAutoAnswerStatus, SettingsModel)
DECLARE_GETTER(bool, getAutoAnswerVideoStatus, SettingsModel)
DECLARE_GETTER(int, getAutoAnswerDelay, SettingsModel)
DECLARE_GETTER(bool, getShowTelKeypadAutomatically, SettingsModel)
DECLARE_GETTER(bool, getKeepCallsWindowInBackground, SettingsModel)
DECLARE_GETTER(bool, getOutgoingCallsEnabled, SettingsModel)
DECLARE_GETTER(bool, getCallRecorderEnabled, SettingsModel)
DECLARE_GETTER(bool, getAutomaticallyRecordCalls, SettingsModel)
DECLARE_GETTER(int, getAutoDownloadMaxSize, SettingsModel)
DECLARE_GETTER(bool, getCallPauseEnabled, SettingsModel)
DECLARE_GETTER(bool, getMuteMicrophoneEnabled, SettingsModel)
DECLARE_GETTER(bool, getStandardChatEnabled, SettingsModel)
DECLARE_GETTER(bool, getSecureChatEnabled, SettingsModel)
DECLARE_GETTER(bool, getHideEmptyChatRooms, SettingsModel)
DECLARE_GETTER(bool, getWaitRegistrationForCall, SettingsModel)
DECLARE_GETTER(bool, getIncallScreenshotEnabled, SettingsModel)
DECLARE_GETTER(bool, getGroupChatEnabled, SettingsModel)
DECLARE_GETTER(bool, getConferenceEnabled, SettingsModel)
DECLARE_GETTER(bool, getVideoConferenceEnabled, SettingsModel)
DECLARE_GETTER(bool, getChatNotificationsEnabled, SettingsModel)
DECLARE_GETTER(bool, getChatNotificationSoundEnabled, SettingsModel)
DECLARE_GETTER(QString, getChatNotificationSoundPath, SettingsModel)
DECLARE_GETTER(QString, getFileTransferUrl, SettingsModel)
DECLARE_GETTER(bool, getLimeIsSupported, SettingsModel)
DECLARE_GETTER(QVariantList, getSupportedMediaEncryptions, SettingsModel)
DECLARE_GETTER_ENUM(MediaEncryption, getMediaEncryption, SettingsModel)
DECLARE_GETTER(bool, mandatoryMediaEncryptionEnabled, SettingsModel)
DECLARE_GETTER(bool, getPostQuantumAvailable, SettingsModel)
DECLARE_GETTER(bool, getLimeState, SettingsModel)
DECLARE_GETTER(bool, getContactsEnabled, SettingsModel)
DECLARE_GETTER(bool, getShowNetworkSettings, SettingsModel)
DECLARE_GETTER(bool, getUseSipInfoForDtmfs, SettingsModel)
DECLARE_GETTER(bool, getUseRfc2833ForDtmfs, SettingsModel)
DECLARE_GETTER(bool, getIpv6Enabled, SettingsModel)
DECLARE_GETTER(int, getDownloadBandwidth, SettingsModel)
DECLARE_GETTER(int, getUploadBandwidth, SettingsModel)
DECLARE_GETTER(bool, getAdaptiveRateControlEnabled, SettingsModel)
DECLARE_GETTER(int, getTcpPort, SettingsModel)
DECLARE_GETTER(int, getUdpPort, SettingsModel)
DECLARE_GETTER(QList<int>, getAudioPortRange, SettingsModel)
DECLARE_GETTER(QList<int>, getVideoPortRange, SettingsModel)
DECLARE_GETTER(bool, getIceEnabled, SettingsModel)
DECLARE_GETTER(bool, getTurnEnabled, SettingsModel)
DECLARE_GETTER(QString, getStunServer, SettingsModel)
DECLARE_GETTER(QString, getTurnUser, SettingsModel)
DECLARE_GETTER(QString, getTurnPassword, SettingsModel)
DECLARE_GETTER(int, getDscpSip, SettingsModel)
DECLARE_GETTER(int, getDscpAudio, SettingsModel)
DECLARE_GETTER(int, getDscpVideo, SettingsModel)
DECLARE_GETTER(bool, getRlsUriEnabled, SettingsModel)
DECLARE_GETTER(bool, tunnelAvailable, SettingsModel)
DECLARE_GETTER(TunnelModel *, getTunnel, SettingsModel)
DECLARE_GETTER(QFont, getTextMessageFont, SettingsModel)
DECLARE_GETTER(int, getTextMessageFontSize, SettingsModel)
DECLARE_GETTER(QFont, getEmojiFont, SettingsModel)
DECLARE_GETTER(int, getEmojiFontSize, SettingsModel)
DECLARE_GETTER(QString, getSavedScreenshotsFolder, SettingsModel)
DECLARE_GETTER(QString, getSavedCallsFolder, SettingsModel)
DECLARE_GETTER(QString, getDownloadFolder, SettingsModel)
DECLARE_GETTER(QString, getRemoteProvisioning, SettingsModel)
DECLARE_GETTER(bool, isQRCodeAvailable, SettingsModel)
DECLARE_GETTER(QString, getFlexiAPIUrl, SettingsModel)
DECLARE_GETTER(bool, getExitOnClose, SettingsModel)
DECLARE_GETTER(bool, isCheckForUpdateEnabled, SettingsModel)
DECLARE_GETTER(QString, getVersionCheckUrl, SettingsModel)
DECLARE_GETTER_ENUM(VersionCheckType, getVersionCheckType, SettingsModel)
DECLARE_GETTER(bool, haveVersionNightlyUrl, SettingsModel)
DECLARE_GETTER(bool, getShowLocalSipAccount, SettingsModel)
DECLARE_GETTER(bool, getShowStartChatButton, SettingsModel)
DECLARE_GETTER(bool, getShowStartVideoCallButton, SettingsModel)
DECLARE_GETTER(bool, isMipmapEnabled, SettingsModel)
DECLARE_GETTER(bool, useMinimalTimelineFilter, SettingsModel)
DECLARE_GETTER(QString, getLogText, SettingsModel)
DECLARE_GETTER(QString, getLogsFolder, SettingsModel)
DECLARE_GETTER(QString, getLogsUploadUrl, SettingsModel)
DECLARE_GETTER(bool, getLogsEnabled, SettingsModel)
DECLARE_GETTER(QString, getLogsEmail, SettingsModel)
DECLARE_GETTER(bool, getVfsEncrypted, SettingsModel)
DECLARE_GETTER(bool, isLdapAvailable, SettingsModel)
DECLARE_GETTER(bool, isOAuth2Available, SettingsModel)
DECLARE_GETTER(bool, isDeveloperSettingsAvailable, SettingsModel)
DECLARE_GETTER(bool, getDeveloperSettingsEnabled, SettingsModel)
DECLARE_GETTER(bool, getIsInCall, SettingsModel)

bool SettingsModelGUI::isCheckForUpdateAvailable(){
	return SettingsModel::isCheckForUpdateAvailable();
}
