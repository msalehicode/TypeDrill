import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

Page
{
    id:addNewTableFrom
    anchors.fill: parent
    Rectangle
    {
        width:400;
        height:200;
        anchors.centerIn: parent
        color:"blue"
        Column
        {
            Rectangle
            {
                width:100;
                height:50;
                color:"grey"
                TextInput
                {
                    anchors.fill: parent
                    id:tableName
                    width:100;
                    height:50
                }
            }
            Rectangle
            {
                width:100;
                height:50;
                color:"pink"
                anchors.top:tableName.bottom
                TextInput
                {
                    id:tableType
                    anchors.fill: parent
                    width:100;
                    height:50
                }
            }



            Button
            {
                text:"create"
                anchors.top: tableType.bottom
                onClicked:
                {
                    backend.createTable(tableName.text,tableType.text)
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
        }
        function onTableCreationResult(result)
        {
            console.log("table creation result="+result)
        }
    }
}
