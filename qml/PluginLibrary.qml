import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

GroupBox {
    title: "Plugin Library"

    ColumnLayout {
        anchors.fill: parent
        spacing: 4

        // directory picker
        RowLayout {
            spacing: 6
            Label { text: "Directory:" }
            TextField {
                id: dirField
                Layout.fillWidth: true
                placeholderText: "Select plugin directory…"
                text: App.pluginDir
                onTextChanged: App.pluginDir = text
            }
            Button {
                text: "Browse…"
                onClicked: App.browsePluginDir()
            }
        }

        // splitter: list (left) + meta panel (right)
        SplitView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            orientation: Qt.Horizontal

            ListView {
                id: pluginList
                SplitView.preferredWidth: 200
                SplitView.minimumWidth: 140
                clip: true
                model: App.pluginListModel
                currentIndex: -1

                delegate: ItemDelegate {
                    width: pluginList.width
                    text: model.name
                    highlighted: ListView.isCurrentItem
                    opacity: model.isValid ? 1.0 : 0.5
                    onClicked: {
                        pluginList.currentIndex = index
                        App.selectPlugin(index)
                    }
                }

                ScrollBar.vertical: ScrollBar {}
            }

            MetaPanel {
                SplitView.fillWidth: true
            }
        }
    }

    Connections {
        target: App
        function onPluginDirChanged() { dirField.text = App.pluginDir }
    }
}
