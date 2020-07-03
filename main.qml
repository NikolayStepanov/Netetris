import QtQuick 2.12
import QtQuick.Window 2.12
import com.NikolayStepanov.NetetrisModel 1.0

Window {
    id: window

    visible: true

    width: 1800
    height: 1000
    color: "dodgerblue"
    title: qsTr("Netetris")

    Item
    {
        id: gameStates

        states: [
            State { name: "play";
                PropertyChanges { target: loaderPlay; active: true; }
                PropertyChanges { target: loaderMainMenu; active: false; }
            },
            State { name: "mainMenu";
                PropertyChanges { target: loaderPlay; active: false; }
                PropertyChanges { target: loaderMainMenu; active: true; }
            }
        ]
    }

    Component
    {
        id: gameplay
        Gameplay
        {
            Component.onCompleted: newGame();
        }
    }

    Connections
    {
        target: loaderMainMenu.item

        onClickedNewGame:
        {
            gameStates.state = "play";
        }
        onClickedExit:
        {
            Qt.quit();
        }
    }

    Connections
    {
        target: loaderPlay.item
        onExit: gameStates.state = "mainMenu"
    }

    Loader
    {
        id: loaderMainMenu
        sourceComponent: Component { MainMenu { } }
        active: false
        focus: true
        anchors.fill: parent
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
    }

    Loader
    {
        id: loaderPlay
        active: false
        sourceComponent: gameplay
        anchors.fill: parent
    }

    Component.onCompleted: { gameStates.state = "mainMenu"; }
}
