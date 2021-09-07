pragma Singleton
import QtQml 2.2

import Units 1.0
import ColorsList 1.0

// =============================================================================
QtObject {
	property QtObject normal : QtObject {
		property QtObject background: QtObject {
		  property int height: 36
		  property int width: 200
	  
		  property int radius: 4
	  
		  property QtObject border: QtObject {
			property QtObject color: QtObject {
			  property color error: ColorsList.add("TextField_normal_background_border_error", "error").color
			  property color normal: ColorsList.add("TextField_normal_background_border_normal", "c").color
			  property color selected: ColorsList.add("TextField_normal_background_border_selected", "i").color
			}
	  
			property int width: 1
		  }
	  
		  property QtObject color: QtObject {
			property color normal: ColorsList.add("TextField_normal_background_normal", "q").color
			property color readOnly: ColorsList.add("TextField_normal_background_readonly", "e").color
		  }
		}
	  
		property QtObject text: QtObject {
		  property color color: ColorsList.add("TextField_normal_text", "d").color
		  property int pointSize: Units.dp * 10
		  property int rightPadding: 10
		}
	}
	property QtObject unbordered : QtObject {
		property QtObject background: QtObject {
		  property int height: 36
		  property int width: 200
	  
		  property int radius: 4
	  
		  property QtObject border: QtObject {
			property QtObject color: QtObject {
			  property color error: "black"
			  property color normal: "black"
			  property color selected: "black"
			}
	  
			property int width: 0
		  }
	  
		  property QtObject color: QtObject {
			property color normal:  ColorsList.add("TextField_unbordered_background_normal", "q").color
			property color readOnly: ColorsList.add("TextField_unbordered_background_readonly", "e").color
		  }
		}
	  
		property QtObject text: QtObject {
		  property color color: ColorsList.add("TextField_unbordered_text", "d").color
		  property int pointSize: Units.dp * 10
		  property int rightPadding: 10
		}
	}
	property QtObject flat : QtObject {
		property QtObject background: QtObject {
		  property int height: 36
		  property int width: 200
	  
		  property int radius: 0
	  
		  property QtObject border: QtObject {
			property QtObject color: QtObject {
			  property color error: "black"
			  property color normal: "black"
			  property color selected: "black"
			}
	  
			property int width: 0
		  }
	  
		  property QtObject color: QtObject {
			property color normal: ColorsList.add("TextField_flat_background_normal", "q").color
			property color readOnly: ColorsList.add("TextField_flat_background_readonly", "e").color
		  }
		}
	  
		property QtObject text: QtObject {
		  property color color: ColorsList.add("TextField_flat_text", "d").color
		  property int pointSize: Units.dp * 10
		  property int rightPadding: 10
		}
	}
}
