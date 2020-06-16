import QtQuick 2.0

Text {
    property color sourceColor: "black"
    property color sourceStyleColor: "white"

    id: text

    font.family: "Helvetica"
    font.bold: true

    color: sourceColor
    elide: Text.ElideRight

    style: Text.Outline
    styleColor: sourceStyleColor
}
