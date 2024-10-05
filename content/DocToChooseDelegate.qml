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
            //font.pixelSize: 30
            font.bold: true
            elide: Text.ElideRight
            Layout.fillWidth: true
        }
    }
}
