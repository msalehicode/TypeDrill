import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Page
{
    anchors.fill: parent
    Item
    {
        id:itemContent
        anchors.fill: parent

        ColumnLayout
        {
            id:columnPractice
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            spacing:50
            Label
            {
                id:w_text
                text:"w_text"
                font.pixelSize: 45
                horizontalAlignment: Text.AlignHCenter  // Center text horizontally
                Layout.fillWidth: true                   // Fill the available width
                wrapMode: Text.WordWrap                  // Enable text wrapping if text is long

            }
            Label
            {
                id:w_meaning
                text:"w_meaning"
                font.pixelSize: 25
                horizontalAlignment: Text.AlignHCenter  // Center text horizontally
                Layout.fillWidth: true                   // Fill the available width
                wrapMode: Text.WordWrap                  // Enable text wrapping if text is long
            }
            Label
            {
                id:w_example
                text:"w_example"
                font.pixelSize: 25
                horizontalAlignment: Text.AlignHCenter  // Center text horizontally
                Layout.fillWidth: true                   // Fill the available width
                wrapMode: Text.WordWrap                  // Enable text wrapping if text is long
            }
            Rectangle
            {
                width: 200;
                height: 50
                Layout.alignment: Qt.AlignHCenter   // Align horizontally center in layout
                TextInput
                {
                    id:text_input
                    text:"type"
                    font.pixelSize: 30
                    anchors.fill: parent
                    focus: true;
                    onAccepted:
                    {
                        backend.getNextWord(text_input.text)
                    }
                }
            }
        }
    }

    Connections
    {
        target: backend
        function onWordReady(word)
        {
            w_text.text = word[0]
            w_meaning.text = word[1]
            w_example.text = word[2]
            text_input.clear()
        }
    }
    Component.onCompleted:
    {
        //to fetch first word
        backend.getNextWord("")
    }
    Component.onDestruction:
    {
        backend.resetPractice();
        console.log("quiting the practice");
    }
}
