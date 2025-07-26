import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
Item
{
    id:toolbar
    width:parent.width;
    height:40;
    Rectangle
    {
        anchors.fill: parent
        color :"red"
        Row
        {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            Button
            {
                id:addNewWord
                text:"add word"
                onClicked:
                {
                    mainStackView.push("AddNewWordForm.qml", { myMessage: "Hello from Page1!" })
                }
            }

            Button
            {
                id:newTable
                text:"new table"
                onClicked:
                {
                    mainStackView.push("AddNewTableForm.qml", { myMessage: "Hello from Page1!" })
                }
            }
        }
    }

}
