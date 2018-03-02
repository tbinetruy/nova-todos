import QtQuick 2.6
import QtQuick.Controls 2.3
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import io.qt.examples.backend 1.0

ApplicationWindow {
    id: root
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight
    visible: true

    BackEnd {
        id: backend
    }

    //title of the application
    title: qsTr("Nova Todos")

    //menu containing two menu items
    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    //Content Area

    RowLayout {
        id: layout
        width: parent.width
        height: 50
        spacing: 6
        anchors.bottom: parent.bottom

        //a button in the middle of the content area
        Button {
            Layout.preferredWidth: parent.width/2
            text: 'Get todos for:'
            onClicked: backend.getTodos()
            anchors.bottom: parent.bottom
            anchors.left: parent.left
        }

        TextField {
            id: searchFor
            Layout.preferredWidth: parent.width/2
            text: backend.userName
            placeholderText: qsTr("User name")

            anchors.bottom: parent.bottom
            anchors.right: parent.right
            onTextChanged: backend.userName = text
        }
    }

    TabView {
        anchors.fill: parent
        anchors.bottomMargin: 75
        Tab {
            title: 'Scheduled todos'

            ListView {
                height: parent.height - 100
                anchors.top : parent.top
                anchors.left : parent.left
                anchors.right : parent.right
                anchors.leftMargin: 10
                anchors.rightMargin: 10

                model: backend.scheduledTodoList
                delegate: RowLayout {
                    id: todoLayout
                    width: parent.width
                    spacing: 6
                    height: modelData.dueDate.toLocaleString() == "" ? 60 : 25
                    anchors.bottomMargin: modelData.dueDate.toLocaleString() == "" ? 40 : 0

                    Text {
                        height: parent.height
                        Layout.preferredWidth: parent.width * 5/5
                        text: modelData.headline
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        font.pixelSize: modelData.dueDate.toLocaleString() == "" ? 25 : 15
                        anchors.leftMargin: modelData.dueDate.toLocaleString() == "" ? 40 : 0
                        anchors.bottomMargin: modelData.dueDate.toLocaleString() == "" ? 10 : 0

                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered: parent.color = "green"
                            onExited: parent.color = "black"
                            onClicked: parent.font.strikeout ? parent.font.strikeout = false : parent.font.strikeout = true
                        }
                    }
                }
            }
        }

        Tab {
            title: "Other todos"
            ListView {
                height: parent.height - 100
                anchors.top : parent.top
                anchors.left : parent.left
                anchors.right : parent.right
                anchors.leftMargin: 10
                anchors.rightMargin: 10

                model: backend.todoList
                delegate: Text {
                    height: 25
                    Layout.preferredWidth: parent.width * 4/5
                    text: modelData.headline
                }
            }
        }
    }
}
