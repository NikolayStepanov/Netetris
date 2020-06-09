import QtQuick 2.12
import QtQml.Models 2.12
import QtQuick.Layouts 1.3
import QtQuick.Window 2.12

import com.NikolayStepanov.BoardModel 1.0

Item {
    id:board
    TableView {
        id: tableView
        anchors.fill: parent
        anchors.centerIn: parent

        rowSpacing: 1
        columnSpacing: 1

        //model
        model: BoardModel {
            id: boardModel
        }

        delegate: Rectangle {
            id: cell
            implicitWidth: 50
            implicitHeight: 50

            //color:"#ffffff"
            border.width: 2
            border.color: "#00111010"
            //Cell{}
        }
    }
}
