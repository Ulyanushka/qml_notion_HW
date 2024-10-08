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
        //highlighted: ListView.isCurrentItem

        required property string title
        required property string first_sentence
        required property string path

        required property int index

        onClicked: {
            listView.currentIndex = index
            listView.onClicked(index)
        }

        contentItem: Label {
            id: contentItem
            text: delegate.title
            font.pixelSize: 60
            font.bold: true

            wrapMode: Text.Wrap
            elide: Text.ElideRight

            background: Rectangle {
                id: backgroundRectangle
                color: (delegate.ListView.isCurrentItem) ? "#f2a7d5" : "#dbd6ab"
            }
        }
    }
}
