import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import "./items" as NetetrisItems


Item
{
    id: dialogGameOver

    signal clickedNewGame
    signal clickedMainMenu
    signal closeDialogGameOver

    property var modelNetetris

    Rectangle
    {
        anchors.fill: parent
        opacity: 0.6
        color: "#9aaaca"
    }

    Rectangle
    {
        id: dialog

        width: parent.width / 2
        height: parent.height / 2

        color: "#2a72ee"

        anchors.centerIn: parent

        radius: 20
        border
        {
            width: 3
            color: "#1a10aa"
        }

        ColumnLayout
        {
            anchors.fill: parent

            Item
            {
                Layout.fillWidth: true
                Layout.fillHeight: true

                NetetrisItems.Text
                {
                    text: "GAME OVER"
                    color: "#3914af"
                }
            }

            Item
            {
                Layout.fillWidth: true
                Layout.fillHeight: true

                NetetrisItems.Text
                {
                    text: "Lines: " + modelNetetris.number_lines
                }
            }

            Item
            {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }


            Item
            {
                Layout.fillWidth: true
                Layout.fillHeight: true

                RowLayout
                {
                    anchors.fill: parent
                    Item
                    {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                    Item
                    {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        NetetrisItems.Button
                        {
                            textBut:"New Game"
                            height: parent.height
                            width: parent.width
                            onClicked:{
                                clickedNewGame()
                                closeDialogGameOver()
                            }
                        }
                    }

                    Item
                    {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }

                    Item
                    {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        NetetrisItems.Button
                        {
                            textBut:"Main Menu"
                            height: parent.height
                            width: parent.width

                            onClicked:{
                                clickedMainMenu()
                                closeDialogGameOver()
                            }
                        }
                    }

                    Item
                    {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }

                }
            }

            Item
            {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }

    }
}
