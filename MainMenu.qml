import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import "./items" as NetetrrisItems

Item {
    id:root

    signal clickedListItem(int index)
    signal clickedNewGame
    signal clickedExit


    implicitWidth: 400
    implicitHeight: 400


    Image {
        id: imageMenu
        anchors.fill: parent
        source: "images/menuBackground.png"
    }
    Rectangle
    {
        id: menuRect

        implicitWidth: 400
        implicitHeight: 400

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.margins: 50

        color: "transparent"
        ListView
        {
            id: view
            anchors.fill: parent


            spacing: 10

            model: ListModel
            {
                id: dataModel
                ListElement { text: "New game"; }
                ListElement { text: "Exit"; }
            }
            clip: true

            highlight: Rectangle { color: "blue" }
            highlightFollowsCurrentItem: true

            delegate: NetetrrisItems.MenuButton
            {
                property var view: ListView.view
                property var isCurrent: ListView.isCurrentItem

                id: button
                implicitWidth: root.implicitWidth

                text:
                {
                    return "%1".arg(model.text);
                }
                onClicked:
                {
                    view.currentIndex = model.index;
                    clickedListItem(model.index);
                }
                Connections
                {
                    target: view
                    onCurrentIndexChanged: {  }
                }
            }

            Shortcut
            {
                sequence: "Up"
                onActivated: view.currentIndex ? view.currentIndex-- : print("index invalid");
            }
            Shortcut
            {
                sequence: "Down"
                onActivated: view.currentIndex < view.count - 1 ? view.currentIndex++ : print("index invalid");
            }
            Shortcut
            {
                sequence: "Return"
                onActivated: view.currentItem.clicked()
            }
        }
    }

    onClickedListItem:
    {
        switch (index)
        {
        case 0:
            clickedNewGame();
            break;
        case 1:
            clickedExit();
            break;
        }
    }




}
