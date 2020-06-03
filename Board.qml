import QtQuick 2.12
import QtQuick.Controls 1.4
import QtQml.Models 2.12

Item {
    id:board
    TableView {
        id: tableView
        anchors.fill: parent
        anchors.centerIn: parent

        //rowSpacing: 1
        //columnSpacing: 1
       /*delegate: Rectangle {
            id: cell
            implicitWidth: 100
            implicitHeight: 100

            color:"#a6d3fb"
        }*/

    }
}
