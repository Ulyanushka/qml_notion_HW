pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls
import notion_v2

ListView {
    id: listView

    focus: true
    boundsBehavior: Flickable.VerticalFlick

    delegate: DocToChooseDelegate {
        id: delegate
        width: listView.width
        //height: 100

        Component.onCompleted: {
            console.log("pizda s delegatom")
        }
    }

    model: DocumentsModel {
        id: docsModel
    }

    ScrollBar.vertical: ScrollBar { }
}
