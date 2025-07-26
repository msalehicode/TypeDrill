import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

Page
{
    id:addNewWordForm
    anchors.fill: parent
    property string formType: "none"

    onFormTypeChanged:
    {
        if(formType=="word")
        {
            //text, meaning, example, translate, source, status
           // firstInput.placeholderText="word text";
           //  secondInput.placeholderText="word meaning";
           //  thirdInput.placeholderText="word example";
           //  forthInput.placeholderText="word translate";
           //  fifthInput.placeholderText="word source";
           //  sixthInput.placeholderText="word status";
        }
        else if(formType=="verb")
        {
            //verb, past, past perfect, status
            // firstInput.placeholderText="verb";
            //  secondInput.placeholderText="past";
            //  thirdInput.placeholderText="past perfect";
            //  forthInput.placeholderText="status";
            fifthInput.enabled=false;
            fifthInput.visible=false;
            sixthInput.visible=false;
            sixthInput.enabled=false;
        }
    }

    Item
        {
            id:baseNewWordFrom
            width:400;
            height:200;
            anchors.centerIn: parent
            // color:"purple"
            Column
            {
                anchors.fill: parent
                Rectangle { width:100; height:50; color:"black"; TextInput { id:firstInput; anchors.fill: parent;}}
                Rectangle { width:100; height:50; color:"red"; TextInput { id:secondInput; anchors.fill: parent;}}
                Rectangle { width:100; height:50; color:"grey"; TextInput { id:thirdInput; anchors.fill: parent;}}
                Rectangle { width:100; height:50; color:"green"; TextInput { id:forthInput; anchors.fill: parent;}}
                Rectangle { width:100; height:50; color:"black"; TextInput { id:fifthInput; anchors.fill: parent;}}
                Rectangle { width:100; height:50; color:"red"; TextInput { id:sixthInput; anchors.fill: parent;}}
            }
        }
    Button
    {
        text:"save"
        anchors.top: baseNewWordFrom.bottom
        onClicked:
        {
            console.log("values are:"+
                        firstInput.text,
                        secondInput.text,
                        thirdInput.text,
                        forthInput.text,
                        fifthInput.text,
                        sixthInput.text)
            var data
            if(formType=="word")
            {
                //text, meaning, example, translate, source, status
                data = [
                                firstInput.text,
                                secondInput.text,
                                thirdInput.text,
                                forthInput.text,
                                fifthInput.text,
                                sixthInput.text
                            ];
                for(var i=0; i<data.length; i++) {
                    console.log(typeof data[i], data[i]);
                }
                backend.addWordToTable(data);
            }
            else if(formType=="verb")
            {
                //verb, past, past perfect, status
                data = [
                                firstInput.text,
                                secondInput.text,
                                thirdInput.text,
                                forthInput.text
                            ];
                for(var i=0; i<data.length; i++) {
                    console.log(typeof data[i], data[i]);
                }
                backend.addWordToTable(data);
            }
            else
            {
                console.log("formtype undefined..");
            }


        }
    }

    Connections
    {
        target: backend
        function onTableTypeIs(currentTableType)
        {
            formType=currentTableType
        }
        function onAddItemtoTableResult(res)
        {
            console.log("result submit/add item to the table: "+res)
        }
    }
    Component.onCompleted:
    {
        console.log("add new word page component loaded")
        backend.whatIsCurrentTableType();
    }

}

