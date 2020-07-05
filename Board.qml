import QtQuick 2.12
import QtQml.Models 2.12
import QtQuick.Layouts 1.3

import com.NikolayStepanov.BoardModel 1.0
import com.NikolayStepanov.CellAction 1.0
import com.NikolayStepanov.CellState 1.0


Item {

    ColumnLayout
    {
        anchors.fill: parent

        TableView
        {
            id: tableView

            Layout.fillWidth: true
            Layout.fillHeight: true

            clip: true
            //model
            model: BoardModel {
                id: boardModel
            }

            delegate: Rectangle
            {
                id: cell

                property int sizeCell: Math.min(tableView.width / tableView.columns,
                                                tableView.height / tableView.rows)
                implicitWidth: sizeCell
                implicitHeight: sizeCell

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
                    widthBorder: 2
                    color_cell: colorCell
                    state_cell: stateCell
                    action_cell: actionCell
                    animationActive: actionCell != CellAction.EMPTY
                }
            }

            onWidthChanged: tableView.forceLayout();
            onHeightChanged: tableView.forceLayout();
        }

    }
}

