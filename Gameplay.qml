import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12

import com.NikolayStepanov.NetetrisModel 1.0

import "./items" as NetetrrisItems

Item {
    id: root
    
    signal newGame
    signal exit

    onNewGame: netetrisModel.newGame();
    onExit: netetrisModel.quitGame();
    
    anchors.fill: parent

    RowLayout
    {
        id:layout
        spacing: 10
        anchors {
            fill: parent
            margins: 20
        }

        Board
        {
            id:areaBoard
            Layout.minimumWidth: 200
            Layout.maximumWidth: 1000
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Item
        {
            Layout.minimumWidth: 100
            Layout.maximumWidth: 450
            Layout.fillWidth: true
            Layout.fillHeight: true

            ColumnLayout
            {
                anchors.fill: parent
                Item
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    NextFigure
                    {
                        anchors.fill: parent
                    }
                }

                Item
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    InformationBlock
                    {
                        anchors.fill: parent
                        lines: netetrisModel.number_lines
                    }
                }
            }
        }
    }
    
    NetetrisModel
    {
        id: netetrisModel
    }

    Connections
    {
        target: netetrisModel
        onGameOver: dialogGameOver.active = true
    }

    Connections
    {
        target: dialogGameOver.item
        onCloseDialogGameOver: dialogGameOver.active = false
        onClickedNewGame: newGame()
        onClickedMainMenu: exit();
    }

    Loader
    {
        id: dialogGameOver

        active: false

        sourceComponent: DialogGameOver
        {
            modelNetetris: netetrisModel
        }

        anchors.fill: parent
    }

    Shortcut
    {
        sequence: "Return";
        onActivated: netetrisModel.fixFigure();
    }
    Shortcut
    {
        sequence: "Space";
        onActivated: netetrisModel.rotate();
    }
    Shortcut
    {
        sequence: "Up"
        onActivated: netetrisModel.moveTop();
    }
    Shortcut
    {
        sequence: "Down"
        onActivated: netetrisModel.moveDown()
    }
    Shortcut
    {
        sequence: "Left"
        onActivated: netetrisModel.moveLeft();
    }
    Shortcut
    {
        sequence: "Right"
        onActivated: netetrisModel.moveRight();
    }

    Shortcut
    {
        sequence: "Escape";
        onActivated: exit();
    }
    Shortcut
    {
        sequence: "Backspace";
        onActivated: exit()
    }
}
