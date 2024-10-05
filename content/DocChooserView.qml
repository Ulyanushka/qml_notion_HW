pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls
import notion_v2

ListView {
    id: listView

    focus: true
    boundsBehavior: Flickable.StopAtBounds

    delegate: DocToChooseDelegate {
        id: delegate
        width: listView.width
        height: 20

        Component.onCompleted: {
            console.log("pizda s delegatom")
        }
    }

    model: DocumentsModel {
        id: docsModel
    }

//    model: ListModel {
//        ListElement {
//           title: "PIZDA"
//           first_sentence: "PIZDA"
//           path: "PIZDA"
//        }

//        ListElement {
//           title: "PIZDA2"
//           first_sentence: "PIZDA2"
//           path: "PIZDA2"
//        }
//    }

//    Rectangle {
//        color:"red"
//        width: 320
//        height: 480
//    }

    ScrollBar.vertical: ScrollBar { }
}
