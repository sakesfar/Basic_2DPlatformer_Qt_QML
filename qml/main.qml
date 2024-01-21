import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 640
    height: 368
    visible: true
    title: qsTr("FancyPants")
    color:"grey"



    GameMainMap
    {
        anchors.fill: parent
    }




}
