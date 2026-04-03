import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Pane {
    padding: 0

    ScrollView {
        anchors.fill: parent

        TextArea {
            readOnly: true
            wrapMode: TextArea.Wrap
            text: App.logText
            font.family: "monospace"
            font.pointSize: 9
        }
    }
}
