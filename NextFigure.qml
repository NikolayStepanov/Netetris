import QtQuick 2.12
import QtQml.Models 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12

import com.NikolayStepanov.NextFigureModel 1.0
import "./items" as NetetrisItems

Item
{
    anchors.fill: parent

    ColumnLayout
    {
        anchors.fill: parent

        Item
        {
            Layout.fillWidth: true
            Layout.fillHeight: true

            NetetrisItems.Text
            {
                text: "NEXT"
            }
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
                    Layout.minimumWidth: 10
                    Layout.maximumWidth: 100
                }

                TableView
                {
                    id: tableView

                    Layout.minimumWidth: 100
                    Layout.maximumWidth: 200
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    clip: true
                    //model
                    model: NextFigureModel{
                        id: nextFigureModel
                    }

                    delegate: Rectangle
                    {
                        id: cell

                        property int cellSize: Math.min (tableView.width,tableView.height) / 4

                        implicitWidth: cellSize
                        implicitHeight: cellSize

                        border
                        {
                            width: 1
                            color: "#aaa6a6"
                        }
                        color: colorCell
                    }
                    onWidthChanged: tableView.forceLayout();
                    onHeightChanged: tableView.forceLayout();
                }

                Item
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.minimumWidth: 10
                    Layout.maximumWidth: 100
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
