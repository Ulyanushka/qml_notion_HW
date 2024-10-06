import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts


Column {
    spacing: 10
    anchors.fill: parent

    function displayDoc(document) {
        docTitle.text = document.title
        docFirstSentence.text = document.first_sentence
    }

    Label {
        id: docTitle
        text: ""
        font.pixelSize: 60
        font.bold: true
        wrapMode: Text.Wrap
        elide: Text.ElideMiddle
    }

    TextArea {
        id: docFirstSentence
        anchors.topMargin: 100
        text: ""
        font.pixelSize: 60
        font.bold: true
        wrapMode: Text.Wrap
        //elide: Text.ElideMiddle
    }
}
