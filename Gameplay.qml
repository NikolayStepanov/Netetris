import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12

import com.NikolayStepanov.NetetrisModel 1.0

import "./items" as NetetrrisItems

Item {
    id: root

    signal newGame
    signal updateState
    signal exit

    onNewGame: netetrisModel.newGame();
    onExit: netetrisModel.quitGame();

    RowLayout {
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
            width: parent.width*0.7
            height: parent.height
        }
        ColumnLayout
        {
            //width: parent.width*0.3
            //height: parent.height

            NextFigure
            {
                id:nextFigure
                width: 400
                height: 400
            }

            /*InformationBlock
        {
            id:infoBlock
            width: parent.width
            height: parent.height
            lines: netetrisModel.number_lines
        }*/


            NetetrrisItems.Text{
                id: linesText
                text: "Lines"
                font.pointSize: 24
            }
            NetetrrisItems.Text{
                id: numberLines
                text: netetrisModel.number_lines.toString();
                font.pointSize: 24
            }
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
