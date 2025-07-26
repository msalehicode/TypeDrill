import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window
{
    id:root
    width: 800
    height: 800
    visible: true
    title: qsTr("TypeDrill")
    color:"#222424"
    onClosing:
    {
        console.log("source : main.qml -> user is trying to close app, mainStackView Dep = "+ mainStackView.depth);
        if(mainStackView.depth===1)
        {
            console.log("source : main.qml -> SAFE EXIT.");
        }
        else
        {
            mainStackView.pop();
            close.accepted = false;
        }

    }

    StackView
    {
        id:mainStackView;
        initialItem: "./HomePage.qml";
        anchors.fill:parent;
    }
    AppToolbar
    {

    }
}
