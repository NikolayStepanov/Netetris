import QtQuick 2.12
import QtQml.Models 2.12
import QtQuick.Layouts 1.3
import QtQuick.Window 2.12

import com.NikolayStepanov.NextFigureModel 1.0
import "./items" as NetetrrisItems

Item {
    id:nextFigure

    Column{
        spacing:10
        NetetrrisItems.Text{
            text: "NEXT"
            font.pointSize: 24
        }
        Rectangle{
            width: 200
            height: 200

            TableView {
                id: tableView
                anchors.fill: parent
                anchors.centerIn: parent
                //model
                model: NextFigureModel{
                    id: nextFigureModel
                }

                delegate: Rectangle{
                    id: cell
                    implicitWidth: 50
                    implicitHeight: 50
                    border
                    {
                        width: 1
                        color: "#aaa6a6"
                    }
                    color: colorCell
                }
            }
        }
    }
}
