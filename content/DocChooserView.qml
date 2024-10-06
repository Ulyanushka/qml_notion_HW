pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls
import notion_v2

ListView {
    id: listView

    model: DocumentsModel {
        id: docsModel
    }

    delegate: ItemDelegate {
        id: delegate
        width: listView.width

        required property string title
        required property string first_sentence
        required property string path

        contentItem: Label {
            text: delegate.title
            font.pixelSize: 60
            font.bold: true

            wrapMode: Text.Wrap
            elide: Text.ElideRight

            background: Rectangle {
                color: "#dbd6ab"
            }
        }
    }
}
