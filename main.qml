import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
//import vipconsult.portal.chat 1.0



//ApplicationWindow {
//    id:root
//    visible: true
//    width: 640
//    height: 480



    SplitView{
        anchors.fill: parent
        Rectangle {
            id:first
            Layout.minimumWidth: 200
            color: "grey"
            ColumnLayout{
                Label {
                    Label{
                        font.pixelSize: 14
                        text:"Search name/company:"
                    }
                    TextInput{
                        leftPadding: 100
                        maximumLength: 14
                        focus: true
                    }
                }

                TreeView {
                    model: ContactsModel
                    headerVisible: false
                    itemDelegate: Rectangle {
                        color: ( styleData.hasChildren ) ? "lightgreen" : "lightblue"
                        Text {
                            font.pixelSize: 18
                            text: styleData.value // this points to the role we defined in the TableViewColumn below; which one depends on which column this delegate is instantiated for.
                        }
                    }
                    TableViewColumn {
                        role: "display"
                        title: "Name"
                    }
                }               
            }
        }

        Rectangle {
            Layout.minimumWidth: 200
            color: "silver"

            Label  {
                text:"MESSAGES"
            }
        }
    }
//}
