import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

GroupBox {
    title: "MIDI Ports"

    ColumnLayout {
        anchors.fill: parent
        spacing: 4

        Button {
            text: "Probe"
            onClicked: App.probe()
        }

        RowLayout {
            spacing: 8
            Label { text: "In:" }
            ComboBox {
                id: inCombo
                Layout.fillWidth: true
                model: App.inPorts
                currentIndex: App.inPortIndex
                onCurrentIndexChanged: App.inPortIndex = currentIndex
            }
            Label { text: "Out:" }
            ComboBox {
                id: outCombo
                Layout.fillWidth: true
                model: App.outPorts
                currentIndex: App.outPortIndex
                onCurrentIndexChanged: App.outPortIndex = currentIndex
            }
        }
    }

    Connections {
        target: App
        function onInPortIndexChanged()  { inCombo.currentIndex  = App.inPortIndex  }
        function onOutPortIndexChanged() { outCombo.currentIndex = App.outPortIndex }
    }
}
