import QtQuick 2.12
import QtQuick.Controls 2.12

import com.NikolayStepanov.CellState 1.0
import com.NikolayStepanov.CellAction 1.0

Item {
    id:cell

    property color color_cell : "white"
    property bool animationActive: false
    property int state_cell: CellState.EMPTY
    property int action_cell: CellAction.EMPTY
    property int widthBorder: 2

    Rectangle{
        id: rectangleFirst

        anchors.fill: parent
        color: "transparent"

        border.width: state_cell == CellState.NOT_FIXED ? 3 : 0

        border.color: "#403d3d"

        Rectangle{
            id: rectangleSecond

            anchors
            {
                fill: parent
                margins: state_cell == CellState.NOT_FIXED ? 3 : 0
            }
            color: color_cell
            border.width: widthBorder
            border.color:
            {
                switch(action_cell)
                {
                case CellAction.EMPTY:
                    return "transparent";
                case CellAction.OVERLAP:
                    return "#99092b";	//"#ec1c4c";
                case CellAction.PROMPT:
                    return "green"
                }
            }
        }

        Component
        {
            id: borderAnimation
            SequentialAnimation
            {
                running: true
                loops: Animation.Infinite
                PropertyAnimation
                {
                    target: rectangleSecond;
                    properties: "border.width";
                    to: rectangleSecond.border.width + 2;
                    duration: 400
                }
                PropertyAnimation
                {
                    target: rectangleSecond;
                    properties: "border.width";
                    to: rectangleSecond.border.width;
                    duration: 400
                }
            }
        }
    }
    Loader
    {
        id: borderAnimationLoader

        sourceComponent: borderAnimation
        active: animationActive

        onActiveChanged:
        {
            rectangleSecond.border.width = 2
        }
    }
}
