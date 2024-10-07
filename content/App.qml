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
            id: btn
            height: 200
            text: "Docs List"
            font.pixelSize: 50
            onClicked: popup.open()
        }

        DocView {
            id: docView
            width: window.width
            height: window.height - btn.height - parent.spacing
        }
    }

    Popup {
        id: popup
        parent: Overlay.overlay
        width: window.width * 1/2
        height: window.height - btn.height
        y: btn.height

        DocChooserView {
            id: docsChooserView
            anchors.fill: parent
            clip: true
            onClicked: function(index) {
                console.log("doc title clicked")
                docView.displayDoc(docsChooserView.model.get(index))
            }
        }
    }
}
