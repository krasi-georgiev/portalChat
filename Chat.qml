import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

import profiles 1.0



SplitView{
    anchors.fill: parent

    Rectangle {
        id:first
        Layout.minimumWidth: Screen.width/3
        width: Layout.minimumWidth
        color: "grey"
//            Rectangle {
//                id:"profileSearch"
//                height:30
//                TextInput{
//                    placeholderText: "Search"
//                    Layout.fillWidth: true
//                    leftPadding: 100
//                    maximumLength: 14
//                    focus: true
//                }
//            }



        ListView {
            id:"technicians"
            displayMarginBeginning:4
            height: parent.height
            width:parent.width
            model: ProfilesModel{
                id: model
            }


            highlight: Rectangle {
                width:technicians.width
                color: "lightsteelblue" }
            focus: true
            header: Text{ text:"Technicians"; font.pixelSize: 18}
            delegate:
                Item {
                    height: 20
                    width: parent.width
                    Text {
                        text: name + ":"+id
                    }
                    MouseArea {
                        z: 1
                        hoverEnabled: false
                        anchors.fill: parent
                        onClicked:{
                            technicians.currentIndex = index
                            technicians.forceActiveFocus()
                        }
                    }
                }
        }
        Connections {
                target: root
                onCookieChanged: {
                        console.log("model reloading");
                        model.reload(root.cookie)
                    }
        }


    }



    Rectangle {
        Layout.minimumWidth: Screen.width/3
        color: "silver"

        ListModel {
            id: "jobsModel"

            ListElement {
                name: "UNASSIGNED"
                id_job: "0"
            }
            ListElement {
                name: "Proactive Office move"
               id_job: "555"
            }
            ListElement {
                name: "Make research for a good windows and linux monitoring tool"
                id_job: "123"
            }
            ListElement {
                name: "HA and LB for PAI"
                id_job: "456"
            }
        }

        ListView {
            height: parent.height
            width:parent.width
            model: jobsModel
            header: Text{ text:"JOBS"; font.pixelSize: 18}
            delegate: Text {
                text: name + ": " + id_job
            }
        }

    }


    Rectangle {
        Layout.minimumWidth: Screen.width/3
        color: "silver"

        Label  {
            text:"MESSAGES"
            font.pixelSize:20
        }


    }
}
