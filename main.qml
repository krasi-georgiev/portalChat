import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.0
import QtQuick.Window 2.0

//TODO features
//    show user presence from facebook
//    support hastags
//    file uploads ?


Rectangle {
    id:"window"
    visible: true
    width: 640
    height: 480
//    title: qsTr("Chat")



    RowLayout{
        spacing: 2

        Rectangle {
            color: "grey"
            Layout.preferredWidth: window.width/3
            Layout.preferredHeight: window.height
            Label{
                font.pixelSize: 18
                text:"PEOPLE"
            }

//            Text {
//                   id: myText
//                   text: "Hello"
//                   color: "#dd44ee"
//               }


//            ListView {

//                anchors.fill: parent
//                model: myText
//                delegate: Label {
//                    text: text
//                }

//            }

            TreeView {
                anchors.fill: parent

                model: modelC
//                delegate: Rectangle {
//                    height: 25
//                    width: 100
////                    Text { text: modelData }
//                }
            }
        }

        Rectangle {
            color: "silver"
            Layout.preferredWidth: window.width/3
            Layout.preferredHeight: window.height

            Label{
                font.pixelSize: 18
                text:"JOBS"
            }
        }

        Rectangle {
            Layout.preferredWidth: window.width/3
            Layout.preferredHeight: window.height

            Label{
                font.pixelSize: 18
                text:"MESSAGES"
            }
        }
    }
}
