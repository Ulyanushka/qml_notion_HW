// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.2
import QtQuick.Controls 6.2
import notion_v2

ApplicationWindow {
    id: window
    width: 1920
    height: 1080

    visible: true
    title: "notion_simulaton"

    DocChooserView {
        id: docsChooserView
        height: window.height / 2
        width: window.width / 2

        Component.onCompleted: {
            console.log("pizda s chooserom")
        }
    }
}

