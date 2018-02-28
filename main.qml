import QtQuick 2.6
import QtQuick.Controls 2.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import io.qt.examples.backend 1.0

ApplicationWindow {
    id: root
    width: 300
    height: 480
    visible: true

    BackEnd {
        id: backend
    }

    //title of the application
    title: qsTr("Hello World")

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
    anchors.fill: parent
    spacing: 6

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

    ListView {
        height: parent.height - 100
        anchors.top : parent.top
        anchors.left : parent.left
        anchors.right : parent.right

        model: backend.todoList
        delegate: Rectangle {
            height: 25
            width: 100
            Text { text: modelData.headline }
        }
    }
}
