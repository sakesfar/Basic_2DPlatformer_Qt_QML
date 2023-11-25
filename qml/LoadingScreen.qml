import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    width: 640
    height: 368


    Image {
        id: backgroundImage
        source: "/images/levels/loadingScreen.png"
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit


    }

    // Loading Bar
    /*
    ProgressBar {
        id: loadingBar
        width: parent.width * 0.8
        height: 20
        anchors.bottom:  parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 64

        value: 0.5 // Example static value for demonstration


    }
    */


}
