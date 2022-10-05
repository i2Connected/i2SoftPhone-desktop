pragma Singleton
import QtQuick 2.15
import QtQml 2.2

import Units 1.0
import ColorsList 1.0

// =============================================================================

QtObject {
	property string sectionName: 'FormHGroup'
	property int spacing: 20
	
	property QtObject content: QtObject {
		property int maxWidth: 400
	}
	
	property QtObject legend: QtObject {
		property color color: ColorsList.add(sectionName+'_legend', 'j').color
		property int pointSize: Units.dp * 10
		property int height: 36
		property int width: 200
	}
}
