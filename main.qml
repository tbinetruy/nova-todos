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
                    height: 25
                    width: parent.width
                    spacing: 6

                    Text {
                        height: 25
                        Layout.preferredWidth: parent.width * 4/5
                        text: modelData.headline
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                    }

                    Text {
                        height: 25
                        Layout.preferredWidth: parent.width * 1/5
                        text: modelData.dueDate
                        anchors.bottom: parent.bottom
                        anchors.right: parent.right
                        horizontalAlignment: Text.AlignRight
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
                delegate: RowLayout {
                    id: todoLayout
                    height: 25
                    width: parent.width
                    spacing: 6

                    Text {
                        height: 25
                        Layout.preferredWidth: parent.width * 4/5
                        text: modelData.headline
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                    }

                    Text {
                        height: 25
                        Layout.preferredWidth: parent.width * 1/5
                        text: modelData.dueDate
                        anchors.bottom: parent.bottom
                        anchors.right: parent.right
                        horizontalAlignment: Text.AlignRight
                    }
                }
            }
        }
    }
}
