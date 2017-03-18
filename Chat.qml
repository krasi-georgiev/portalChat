import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

import profiles 1.0
import jobs 1.0

Item{
    Text{
        id: loginWarning
        anchors.fill: parent
        text: "Login first"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 40
    }
    anchors.fill: parent




    SplitView{
        id: splitView
        anchors.fill: parent



        Rectangle {
            Layout.minimumWidth: Screen.width/5
            width:Screen.width/3

            color: "silver"

            ListView {
                id: jobs
                header: Text{ text:"JOBS"; font.pixelSize: 18}
                anchors.fill:parent


                highlightMoveDuration: 0
                highlight: Rectangle {
                    color: "lightsteelblue"
                }

                model: JobsModel{
                    id:jobsModel
                    onDataChanged: if(jobsModel.rowCount()===0){
                                       splitView.visible=false;
                                       loginWarning.visible=!splitView.visible;
                                   }
                                   else{
                                       splitView.visible=true ;
                                       loginWarning.visible=!splitView.visible;
                                   }
                }
                delegate: Text {
                    text: title+" - "+company
                    width: parent.width

                    MouseArea {
                        Menu {
                            id: contextMenu
                            MenuItem {
                                text: qsTr('Delete')
                                onTriggered: console.log("Delete clicked")
                            }

                        }
                        acceptedButtons: Qt.RightButton
                        anchors.fill: parent
                        onClicked:contextMenu.open()
                    }
                    MouseArea {
                        hoverEnabled: false
                        anchors.fill: parent
                        onClicked:{
                            jobs.currentIndex = index
                            jobs.forceActiveFocus()
                            profilesModel.reload(root.cookie,"?id_job="+id)
                        }
                    }
               }
            }


        }

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
                header: Text{ text:"Technicians"; font.pixelSize: 18}
                id: profiles
                displayMarginBeginning:4
                anchors.fill: parent
                model: ProfilesModel{
                    id: profilesModel
                }

                highlightMoveDuration: 0
                highlight: Rectangle {
                    color: "lightsteelblue"
                }

                delegate:
                    Item {
                        height: 20
                        width: parent.width
                        Text {
                            text: name + ":"+id
                        }
                        MouseArea {
                            hoverEnabled: false
                            anchors.fill: parent
                            onClicked:{
                                profiles.currentIndex = index
                                profiles.forceActiveFocus()
                            }
                        }
                    }
            }

        }

        Connections {
                target: root
                onCookieChanged: {
                        console.log("modelS reloading");
                        jobsModel.reload(root.cookie)
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
}
