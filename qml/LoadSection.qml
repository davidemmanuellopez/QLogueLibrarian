import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

GroupBox {
    title: "Load Unit"

    RowLayout {
        anchors.fill: parent
        spacing: 6

        TextField {
            id: unitField
            Layout.fillWidth: true
            placeholderText: "Select a .xxxunit file…"
            text: App.unitPath
            onTextChanged: App.unitPath = text
        }

        Button {
            text: "Browse…"
            onClicked: App.browseUnitFile()
        }

        Label { text: "Slot:" }
        SpinBox {
            id: slotSpin
            from: 0
            to: 16
            value: App.slot
            onValueChanged: App.slot = value
            textFromValue: function(value) {
                return value === 0 ? "Auto" : value.toString()
            }
        }

        Button {
            text: "Upload"
            enabled: App.canLoad
            onClicked: App.loadUnit()
        }
    }

    Connections {
        target: App
        function onUnitPathChanged() { unitField.text = App.unitPath }
    }
}
