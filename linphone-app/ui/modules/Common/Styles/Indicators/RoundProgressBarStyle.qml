pragma Singleton
import QtQuick 2.15
import QtQml 2.2

import ColorsList 1.0
import Units 1.0

// =============================================================================

QtObject {
	property string sectionName: 'RoundProgressBar'
	
	property color backgroundColor:  ColorsList.add(sectionName+'_bg', 'progress_bg').color
	property color progressRemainColor:  ColorsList.add(sectionName+'_remaining_fg', 'progress_remaining_fg').color
	property color progressColor:  ColorsList.add(sectionName+'_fg', 'i').color
	property int progressionWidth : 3
	property int borderWidth: 2
	property int pointSize:  Units.dp * 7
}
