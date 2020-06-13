import QtQuick 2.12
import QtQuick.Window 2.12
import com.NikolayStepanov.NetetrisModel 1.0

Window {
    visible: true
    width: 1800
    height: 1000
    color: "dodgerblue"
    title: qsTr("Netetris")
    Item{
        id: main
        anchors.fill: parent
        Column {
            spacing: 6
            anchors {
                fill: parent
                topMargin: 20;
                bottomMargin: 20;
                leftMargin: 20;
                rightMargin: 20
            }

            Board
            {
                id:areaBoard
                width: parent.width*0.70
                height: parent.height
            }
        }
        NetetrisModel
        {
            id: netetrisModel
        }

        Shortcut
        {
            sequence: "Up"
            onActivated: netetrisModel.rotate();
        }
        Shortcut
        {
            sequence: "Down"
            onActivated: netetrisModel.moveDown()
        }
        Shortcut
        {
            sequence: "Left"
            onActivated: netetrisModel.moveLeft();
        }
        Shortcut
        {
            sequence: "Right"
            onActivated: netetrisModel.moveRight();
        }
    }


}
