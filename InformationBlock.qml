import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12

import "./items" as NetetrrisItems

Item {
    id: root

    property int lines: 0

    ColumnLayout
    {
        NetetrrisItems.Text{
            id: linesText
            text: "Lines"
            font.pointSize: 24
        }
        NetetrrisItems.Text{
            id: numberLines
            text: lines
            font.pointSize: 24
        }
    }
}
