import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Page
{
    id:addNewTableFrom
    anchors.fill: parent
    Rectangle
    {
        anchors.fill: parent
        color:"#222424"
        Column
        {
            Rectangle
            {
                width:100;
                height:50;
                color:"transparent"
                border.color: "grey"
                TextInput
                {
                    anchors.fill: parent
                    id:tableName
                    width:100;
                    color:"white"
                    height:50
                }
            }
            ComboBox {
                id:comboType
                model: ListModel {
                    id: model
                    ListElement { text: "word"}
                    ListElement { text: "verb"}
                    ListElement { text: "single"}
                }
            }


            Button
            {
                text:"create"
                anchors.top: tableType.bottom
                onClicked:
                {
                    var selectedItem = comboType.model.get(comboType.currentIndex);
                    backend.createTable(tableName.text,selectedItem.text)
                }
            }
        }


    }

    Connections
    {
        target: backend
        function onTablesList(word)
        {
            for(let i=0; i<tables.count; i++)
                console.log("received table list:"+tables[i])
            //write code here to notice input to avoid duplicated table name
        }
        function onTableCreationResult(result)
        {
            // console.log("table creation result="+result)
            if (result !== "error")
            {
                mainStackView.pop();
            }
        }
    }
}
