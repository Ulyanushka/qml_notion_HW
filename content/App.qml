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

    DocView {
        id: docView
        width: window.width * 4/5
        height: window.height
        anchors.topMargin: 300
    }

    Column { //choosing a doc to see
        spacing: 10

        Button { //opens DocChooserView
            id: btn
            height: 200
            text: "Docs List"
            font.pixelSize: 50
            onClicked: {
                docsChooserView.visible = !docsChooserView.visible
            }
        }

        DocChooserView {
            id: docsChooserView
            width: window.width * 2/3
            height: window.height * 2/3
            clip: true
            visible: true
            onClicked: function(index) {
                console.log("doc title clicked")
                docView.displayDoc(docsChooserView.model.get(index))
            }
        }
    }
}
