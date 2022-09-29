pragma Singleton
import QtQuick 2.15
import QtQml 2.2
import ColorsList 1.0
// =============================================================================

QtObject {
	property string sectionName: 'Busy'
	property color color: ColorsList.add(sectionName+'_indicator', 'q').color
	property int duration: 1250
	property int nSpheres: 8
}
