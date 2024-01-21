import QtQuick 2.15
import QtQuick.Controls 2.15

Item {

    id:theGameMap

    Background
    {
        id:backGr
        mapX: warG.mapX
        anchors.fill: parent
    }


    Image {
        id: theMap
        source: "/images/theMap3.png"
        x:warG.mapX
        y:warG.mapY

    }



    WarGirl
    {
        id:warG
        x:0
        y:0

    }

    PlayerSharedData
    {
        id:playerData
        isAttacking: warG.attacking
        playerW: warG.width
        playerH: warG.height
        playerY: warG.y

    }

    Repeater
    {
        model: warG.enemies["Skeleton"]        
        delegate: Enemy{ xMapOff:warG.mapX; yMapOff: warG.mapY;  type:"skeleton"  }

    }

    Repeater
    {
        model: warG.enemies["Mushroom"]
        delegate: Enemy{ xMapOff:warG.mapX ; type:"mushroom" }

    }

    Repeater
    {
        model: warG.enemies["Goblin"]
        delegate: Enemy{ xMapOff:warG.mapX ; type:"goblin" }

    }



    HealthBar
    {
        x:5
        y:20
    }


}
