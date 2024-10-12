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

    function displayBlock(block_data) {
        console.log("!!!", block_data);
        if(block_data.length === 1) {
            docTitle.text = block_data[0].title
            docFirstSentence.text = block_data[0].content
        }
        if(block_data.length > 1) {
            docTitle.text = block_data[0].title
            docFirstSentence.text = ""
            for(var data of block_data) {
                docFirstSentence.text += data.content
                docFirstSentence.text += "\n"
            }
        }
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
