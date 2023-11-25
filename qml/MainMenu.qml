import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
 signal startGame

    Rectangle {
        id: mainMenu
        width: 640
        height: 368
        color: "#333" // Background color for the menu


        Button {
            id: startButton
            text: "Start"
            anchors.centerIn: parent
            onClicked: {
                startGame() // Emit the startGame signal
            }
        }

        // Other buttons like Settings and Exit can be added here
    }

}
