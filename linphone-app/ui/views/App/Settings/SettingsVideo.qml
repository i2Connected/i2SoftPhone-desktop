import QtQuick 2.7
import QtQuick.Layouts 1.3

import Common 1.0
import Linphone 1.0
import LinphoneEnums 1.0
import Utils 1.0

import App.Styles 1.0

import 'SettingsVideo.js' as Logic

// =============================================================================

TabContainer {
	Column {
		spacing: SettingsWindowStyle.forms.spacing
		width: parent.width
		
		// -------------------------------------------------------------------------
		// Video parameters.
		// -------------------------------------------------------------------------
		
		Form {
			title: qsTr('videoCaptureTitle')
			width: parent.width
			
			//Warning if in call
			FormLine {
				visible: SettingsModel.isInCall
				FormGroup {
					RowLayout {
						spacing: SettingsWindowStyle.video.warningMessage.iconSize
						Icon {
							icon: 'warning'
							iconSize: SettingsWindowStyle.video.warningMessage.iconSize
							anchors {
								rightMargin: SettingsWindowStyle.video.warningMessage.iconSize
								leftMargin: SettingsWindowStyle.video.warningMessage.iconSize
							}
						}
						Text {
							text: qsTr('videoSettingsInCallWarning')
						}
					}
				}
			}
			
			FormLine {
				FormGroup {
					label: qsTr('videoInputDeviceLabel')
					
					ComboBox {
						currentIndex: Number(Utils.findIndex(model, function (device) {
							return device === SettingsModel.videoDevice
						})) // Number cast => Index is null if app does not support video.
						model: SettingsModel.videoDevices
						
						onActivated: SettingsModel.videoDevice = model[index]
					}
				}
			}
			
			FormLine {
				FormGroup {
					label: qsTr('videoPresetLabel')
					
					ComboBox {
						currentIndex: {
							var preset = SettingsModel.videoPreset
							
							return Number(Utils.findIndex(model, function (value) {
								return preset === value.value
							}))
						}
						
						model: [{
								key: qsTr('presetDefault'),
								value: 'default'
							}, {
								key: qsTr('presetHighFps'),
								value: 'high-fps'
							}, {
								key: qsTr('presetCustom'),
								value: 'custom'
							}]
						
						textRole: 'key'
						
						onActivated: SettingsModel.videoPreset = model[index].value
					}
				}
			}
			
			FormLine {
				FormGroup {
					label: qsTr('videoSizeLabel')
					
					ComboBox {
						currentIndex: Number(Utils.findIndex(model, function (definition) {
							return definition.value.name === SettingsModel.videoDefinition.name
						})) // Number cast => Index is null if app does not support video.
						model: SettingsModel.supportedVideoDefinitions.map(function (definition) {
							return {
								key: definition.name + ' (' + definition.width + 'x' + definition.height + ')',
								value: definition
							}
						})
						
						textRole: 'key'
						
						onActivated: SettingsModel.videoDefinition = model[index].value
					}
				}
				
				FormGroup {
					label: qsTr('videoFramerateLabel')
					visible: SettingsModel.videoPreset === 'custom'
					
					NumericField {
						maxValue: 60
						minValue: 1
						text: SettingsModel.videoFramerate
						
						onEditingFinished: SettingsModel.videoFramerate = text
					}
				}
			}
			
			FormEmptyLine {}
		}
		
		TextButtonB {
			id: showCameraPreview
			
			anchors.right: parent.right
			enabled: CallsListModel.rowCount() === 0
			
			text: qsTr('showCameraPreview')
			
			onClicked: Logic.showVideoPreview()
			
			Connections {
				target: CallsListModel
				
				onRowsInserted: Logic.updateVideoPreview()
				onRowsRemoved: Logic.updateVideoPreview()
			}
			
			Connections {
				target: window
				
				onClosing: Logic.hideVideoPreview()
			}
		}
		
		// -------------------------------------------------------------------------
		// Video Codecs.
		// -------------------------------------------------------------------------
		
		Form {
			title: qsTr('videoCodecsTitle')
			visible: SettingsModel.showVideoCodecs || SettingsModel.developerSettingsEnabled
			width: parent.width
			
			FormLine {
				visible: SettingsModel.developerSettingsEnabled
				
				FormGroup {
					label: qsTr('showVideoCodecsLabel')
					
					Switch {
						checked: SettingsModel.showVideoCodecs
						
						onClicked: SettingsModel.showVideoCodecs = !checked
					}
				}
			}
			
			CodecsViewer {
				model: VideoCodecsModel
				width: parent.width
				
				onDownloadRequested: Logic.handleCodecDownloadRequested(codecInfo)
			}
		}
		
		// -------------------------------------------------------------------------
		// Diplay Video.
		// -------------------------------------------------------------------------
		
		Form {
			//: 'Video display' : Title for display parameters
			title: qsTr('videoDisplayTitle')
			width: parent.width
			
			FormLine {
				FormGroup {
					//: 'Camera mode' : Label to choose a camera mode.
					label: qsTr('videoModeLabel')
					
					ComboBox {
					//: 'Hybrid' : Hybrid mode for camera.
						model:[{text:qsTr('videoHybrid'), value: SettingsModel.CameraMode_Hybrid}
						//: 'Occupy all space' : Camera mode for a centered cropping view.
								, {text:qsTr('videoOccupyAllSpace'), value:SettingsModel.CameraMode_OccupyAllSpace}
						//: 'Black bars' : Camera mode for a fit view with black bars to keep ratio.
								,{text:qsTr('videoBlackBars'), value:SettingsModel.CameraMode_BlackBars}
						]
						textRole: 'text'
						currentIndex: SettingsModel.cameraMode == SettingsModel.CameraMode_Hybrid 
										? 0 
										: SettingsModel.cameraMode == SettingsModel.CameraMode_OccupyAllSpace 
											? 1
											: 2
						onActivated: SettingsModel.cameraMode = model[index].value
					}
				}
			}
			FormLine {
				FormGroup {
					//: 'Default video layout' : Label to choose the default layout in video conference.
					label: qsTr('videoLayout')
					
					ComboBox {
					//: 'Mosaic' : Mosaic layout invideo conference.
						model:[{text:qsTr('videoMosaicLayout'), value:LinphoneEnums.ConferenceLayoutGrid}
						//: 'Active speaker' : Active speaker layout for video conference.
								, {text:qsTr('videoActiveSpeakerLayout'), value:LinphoneEnums.ConferenceLayoutActiveSpeaker}
						]
						textRole: 'text'
						currentIndex: SettingsModel.videoConferenceLayout == LinphoneEnums.ConferenceLayoutGrid ? 0 : 1
						onActivated: SettingsModel.videoConferenceLayout = model[index].value
					}
				}
			}
		}
	}
}
