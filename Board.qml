import QtQuick 2.12
import QtQml.Models 2.12
import QtQuick.Layouts 1.3
import QtQuick.Window 2.12

import com.NikolayStepanov.BoardModel 1.0
import com.NikolayStepanov.CellAction 1.0
import com.NikolayStepanov.CellState 1.0


Item {
    id:board
    TableView {
        id: tableView
        anchors.fill: parent
        anchors.centerIn: parent

        //model
        model: BoardModel {
            id: boardModel
        }

        delegate: Rectangle{
            id: cell

            implicitWidth: 40
            implicitHeight: 40

            opacity: boardModel.isBorder(xCell, yCell) ? 0.5 : 1

            border
            {
                width: 1
                color: "#aaa6a6"
            }

            Cell
            {
                anchors
                {
                    fill: parent
                    margins: 1
                }
                color_cell: colorCell
                state_cell: stateCell
                action_cell: actionCell
                animationActive: actionCell != CellAction.EMPTY
            }
        }
    }


}
