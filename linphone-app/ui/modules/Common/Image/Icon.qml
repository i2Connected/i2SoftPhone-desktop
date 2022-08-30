import QtQuick 2.7
import QtGraphicalEffects 1.12

import Common 1.0
import Linphone 1.0
import Utils 1.0

// =============================================================================
// An icon image properly resized.
// =============================================================================

Item {
	id: mainItem
	property var iconSize // Required.
	property int iconHeight: 0	// Or this
	property int iconWidth: 0	//	<-- too
	
	property string icon
	property color overwriteColor
	property alias horizontalAlignment: image.horizontalAlignment
	property alias verticalAlignment: image.verticalAlignment
	property alias fillMode: image.fillMode
	
	
// Use this slot because of testing overwriteColor in layer doesn't seem to work
	onOverwriteColorChanged: if(overwriteColor) 
								image.colorOverwriteEnabled = true
							else
								image.colorOverwriteEnabled = false
	height: iconHeight > 0 ? iconHeight : iconSize
	width: iconWidth > 0 ? iconWidth : iconSize
	
	Image {
		id:image
		anchors.fill: parent
		
		property bool colorOverwriteEnabled : false
		mipmap: SettingsModel.mipmapEnabled
		cache: Images.areReadOnlyImages	
		asynchronous: true
		smooth: true
		antialiasing: false
		
		fillMode: Image.PreserveAspectFit
		source: Utils.resolveImageUri(icon)
				
		//Test if we need to preserve aspect fit to avoid loss quality. This is the point of having svg in square format.
		sourceSize.width: width == height ? parent.width : 0
		sourceSize.height: width == height ? parent.height : 0
		
		layer {
			enabled: image.colorOverwriteEnabled
			effect: ColorOverlay {
				color: mainItem.overwriteColor
			}
		}
	}
}
