pragma Singleton
import QtQml 2.2
import QtQuick 2.15

import Units 1.0
import ColorsList 1.0

// =============================================================================

QtObject {
	property string sectionName: 'NotificationBasic'
	property int leftMargin: 30
	property int rightMargin: 15
	property int overrodeHeight: 55
	
	property QtObject message: QtObject {
		property color color: ColorsList.add(sectionName+'_message', 'h').color
		property int pointSize: Units.dp * 10
	}
}
