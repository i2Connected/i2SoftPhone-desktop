import QtQuick 2.7

import Common.Styles 1.0
// =============================================================================

Loader {
  id: loader

  // ---------------------------------------------------------------------------

  property string label
  readonly property int orientation: parent.orientation

  default property var _content: null
  property int maxWidth:  orientation === Qt.Horizontal ? FormHGroupStyle.content.maxWidth : FormVGroupStyle.content.maxWidth
  
  // ---------------------------------------------------------------------------

  sourceComponent: orientation === Qt.Horizontal ? hGroup : vGroup
  width: parent.maxItemWidth

  // ---------------------------------------------------------------------------

  Component {
    id: hGroup
    FormHGroup {
      _content: loader._content
      label: loader.label
      maxWidth: loader.maxWidth
    }
  }

  Component {
    id: vGroup
    FormVGroup {
      _content: loader._content
      label: loader.label
      maxWidth: loader.maxWidth
    }
  }
}
