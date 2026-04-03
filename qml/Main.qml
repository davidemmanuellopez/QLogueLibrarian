import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: root
    title: "QLogueLibrarian"
    width: 780
    height: 560
    visible: true

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            anchors.margins: 4

            Label { text: "logue-cli:" }
            TextField {
                id: cliPathField
                Layout.fillWidth: true
                text: App.cliPath
                onTextChanged: App.cliPath = text
            }
            Button {
                text: "..."
                onClicked: App.browseCliPath()
            }
        }
    }

    footer: ToolBar {
        Label {
            anchors.fill: parent
            anchors.margins: 4
            text: App.statusText
            elide: Text.ElideRight
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 8
        spacing: 8

        MidiSection   { Layout.fillWidth: true }
        LoadSection   { Layout.fillWidth: true }
        PluginLibrary { Layout.fillWidth: true; Layout.fillHeight: true }
        LogPanel      { Layout.fillWidth: true; Layout.preferredHeight: 120 }
    }

    // keep cliPath field in sync if changed from C++ (e.g. browseCliPath)
    Connections {
        target: App
        function onCliPathChanged() { cliPathField.text = App.cliPath }
    }
}
