
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {

    width:16
    height:16


    Image{

        width: 16
        height: 16
        source: "images/levels/mainlevbuild.png"
        sourceSize.width: 1024
        sourceSize.height: 1024
        property int tileX: (modelData-1)%64
        property int tileY: Math.floor((modelData-1)/64)
        sourceClipRect: Qt.rect(tileX*16, tileY*16, 16, 16)


    }

}
