import QtQuick 2.7
//import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2



ApplicationWindow {
    id:root
    visible: true
    width: Screen.width
    height: Screen.height

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Item {
            Portal{

            }
        }
        Item {
            Chat {

            }
        }
    }

    header: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Portal")
        }
        TabButton {
            text: qsTr("Chat")
        }
    }
}
