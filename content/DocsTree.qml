pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls
import notion_v2


TreeView {
    id: treeView

    ScrollBar.vertical: ScrollBar {
        id: vScrollBar
        width: 20
        snapMode: ScrollBar.SnapAlways
    }

    selectionModel: ItemSelectionModel {}

    model: DocumentsTreeModel {
        id: docsModel
    }

    signal sendBlockToView(var content)

    delegate: TreeViewDelegate {
        id: delegate
        width: treeView.width

        required property string title
        required property var content

        TapHandler {
            onSingleTapped: {
                let index = treeView.index(row, 0)

                treeView.selectionModel.setCurrentIndex(index, ItemSelectionModel.NoUpdate)
                treeView.toggleExpanded(row)

                sendBlockToView(delegate.content)
            }
        }

        contentItem: Label {
            id: contentItem
            text: delegate.title
            font.pixelSize: 60
            font.bold: true
            width: treeView.width
            //rightPadding: 10

            wrapMode: Text.Wrap
            elide: Text.ElideRight

            background: Rectangle {
                id: backgroundRectangle
                color: (delegate.current) ? "#f2a7d5" : "#dbd6ab"
            }
        }
    }
}
