import QtQuick 2.15
import QtQuick.Controls 2.15

Item {

    property int playerX: 0
    property int playerY:0
    property int playerW:0
    property int playerH:0
    property int mapY:0

    property bool isAttacking:false

    Connections
    {
        target: warG
        onXchanged:playerX=warG.x
        onYchanged:playerY=warG.y
        onMapYchanged:mapY=warG.mapY
    }



}
