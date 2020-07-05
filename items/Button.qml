import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

import "./" as NetetrisItems

Button{
    id: root

    property color colorBut: "#7247d7";
    property string textBut: ""
    property color textColor : "black";

    background: Rectangle
    {
        anchors.fill: parent
        color: colorBut
        border.width: 3
        border.color: "white"
        radius: 5
    }

    Item
    {
        anchors.fill: parent
        anchors.margins: 20
        NetetrisItems.Text
        {
            anchors.fill: parent
            text: textBut
            colorText: textColor
            minimumPointSize: 5
        }
    }

    DropShadow {
        anchors.fill: root
        cached: true
        horizontalOffset: 3
        verticalOffset: 3
        radius: 8.0
        samples: 16
        color: "#80000000"
        source:  root
    }
}
