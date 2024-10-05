import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ItemDelegate {
    id: delegate

    required property string title
    required property string first_sentence
    required property string path

    contentItem: ColumnLayout {
        spacing: 10

        Label {
            text: delegate.title
            background: Rectangle { color: "#dbd6ab" }
            font.pixelSize: 25
            font.bold: true
            wrapMode: Text.Wrap
            elide: Text.ElideRight
            Layout.fillWidth: true
        }
    }
}
