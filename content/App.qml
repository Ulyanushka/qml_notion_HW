// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts
import notion_v2


Window {
    id: window
    //width: 1920
    //height: 1080
    visible: true
    title: "notion_simulaton"

    Column {
        spacing: 10
        anchors.fill: parent

        Button { //opens DocChooserView
            id: btn_list
            height: 200
            text: "Docs List"
            font.pixelSize: 50
            onClicked: popup_list.open()
        }

        Button { //opens DocsTree
            id: btn_tree
            height: 200
            text: "Docs Tree"
            font.pixelSize: 50
            onClicked: popup_tree.open()
        }

        DocView {
            id: docView
            width: window.width
            height: { window.height
                      - btn_list.height - btn_tree.height
                      - parent.spacing
            }
        }
    }

    Popup { //TREE
        id: popup_tree
        parent: Overlay.overlay
        width: window.width * 1/2
        height: window.height - btn_list.height - btn_tree.height
        y: btn_list.height + btn_tree.height

        DocsTree {
            id: docsTree
            anchors.fill: parent
            clip: true
        }
    }

    Popup { //LIST
        id: popup_list
        parent: Overlay.overlay
        width: window.width * 1/2
        height: window.height - btn_list.height - btn_tree.height
        y: btn_list.height + btn_tree.height

        DocChooserView{
            id: docsChooser
            anchors.fill: parent
            clip: true
            onClicked: function(index) {
                docView.displayDoc(docsChooser.model.get(index))
            }
        }
    }
}
