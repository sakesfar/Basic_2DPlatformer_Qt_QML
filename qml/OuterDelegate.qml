import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: outerDelegate
    y:0
    width:foregroundDisplay.width
    height:foregroundDisplay.height
    property var tileData: modelData.data
    property int offsetX: modelData.offsetx
    x:offsetX

    Connections{
        target: Woo
        onPosXChanged : {outerDelegate.x=Woo.getMapX()+ offsetX ; }
    }


    GridView {
        anchors.fill: parent
        cellHeight: 16
        cellWidth: 16
        property real parallaxFactor:0.6
        model: tileData
        delegate: Foreground {}


    }








}
