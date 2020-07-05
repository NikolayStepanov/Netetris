import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12

import "./items" as NetetrrisItems

Item
{
    property int lines: 0

    ColumnLayout
    {
        anchors.fill: parent

        Item
        {
            Layout.fillWidth: true
            Layout.fillHeight: true
            NetetrrisItems.Text
            {
                text: "Lines:"
            }
        }

        Item
        {
            Layout.fillWidth: true
            Layout.fillHeight: true

            NetetrrisItems.Text
            {
                text: lines
            }
        }
    }
}
