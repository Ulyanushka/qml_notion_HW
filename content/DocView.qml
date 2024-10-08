import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts


Column {
    spacing: 10
    leftPadding: 20
    rightPadding: 20

    function displayDoc(document) {
        docTitle.text = document.title
        docFirstSentence.text = document.first_sentence
    }

    Text {
        id: docTitle
        width: parent.width - parent.leftPadding - parent.rightPadding
        text: "Title"
        font.pixelSize: 60
        font.bold: true
        wrapMode: Text.Wrap
        horizontalAlignment: Text.AlignHCenter
    }

    TextArea {
        id: docFirstSentence
        width: parent.width - parent.leftPadding - parent.rightPadding
        text: "First sentence"
        font.pixelSize: 50
        wrapMode: Text.Wrap
        horizontalAlignment: Text.AlignJustify
        readOnly: true
    }
}
