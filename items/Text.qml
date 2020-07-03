import QtQuick 2.0

Text {
    property color colorText: "black"
    property color colorOutlineText: "white"

    id: text

    anchors.centerIn: parent

    width: parent.width / 2
    height: parent.height / 2

    fontSizeMode: Text.Fit
    minimumPointSize:  10
    font.pointSize: 200

    font.family: "Helvetica"
    font.bold: true

    color: colorText
    elide: Text.ElideMiddle

    style: Text.Outline
    styleColor: colorOutlineText
}
