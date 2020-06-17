import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12

import com.NikolayStepanov.NetetrisModel 1.0

import "./items" as SokobanItem
Item {
    id: root

    signal newGame
    signal updateState
    signal exit

    onNewGame: netetrisModel.newGame();
    onExit: netetrisModel.quitGame();

    Row {
        spacing: 6
        anchors {
            fill: parent
            topMargin: 20;
            bottomMargin: 20;
            leftMargin: 20;
            rightMargin: 20
        }

        Board
        {
            id:areaBoard
            width: parent.width*0.70
            height: parent.height
        }

        NextFigure
        {
            id:nextFigure
            width: parent.width
            height: parent.height
        }
    }

    NetetrisModel
    {
        id: netetrisModel
    }

    Shortcut
    {
        sequence: "Up"
        onActivated: netetrisModel.rotate();
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
