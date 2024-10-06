pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls
import notion_v2


ListView {
    id: listView

    ScrollBar.vertical: ScrollBar {
        id: vScrollBar
        width: 20
        snapMode: ScrollBar.SnapAlways
    }

    model: DocumentsModel {
        id: docsModel
    }

    signal clicked(int index)

    delegate: ItemDelegate {
        id: delegate
        width: listView.width

        required property string title
        required property string first_sentence
        required property string path

        required property int index

        MouseArea {
            anchors.fill: parent
            onClicked: listView.onClicked(index)
        }

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
