pragma Singleton
import QtQml 2.2

import ColorsList 1.0

// =============================================================================

QtObject {
	property string sectionName: 'Window'
	property QtObject transientWindow: QtObject {
		property color color: ColorsList.add(sectionName+'_transient', 'l80').color
	}
}
