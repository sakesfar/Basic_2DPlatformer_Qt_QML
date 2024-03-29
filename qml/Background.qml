import QtQuick 2.15
import QtQuick.Controls 2.15

Item {

    id:backMain
    //anchors.fill:parent
    property int mapX:0

    function calculateXPosition(pF, mapX)
    {
        return mapX*(1-pF)
    }


    Image{
        id:back1
        source:"images/levels/day1.png"
        anchors.bottom:parent.bottom
        x: calculateXPosition(parallaxFactor,mapX) //Woo.getMapX() * (1 - parallaxFactor)
        property real parallaxFactor:0.9

        Image{
            id:back1B
            source:"images/levels/day1.png"
            anchors.bottom:parent.bottom
            x:back1.width

        }

    }


    Image{
        id:back2
        source:"images/levels/day2.png"
        anchors.bottom:parent.bottom
        width:640
        height:368
        x:calculateXPosition(parallaxFactor,mapX) //Woo.getMapX() * (1 - parallaxFactor)
        property real parallaxFactor:0.9

        Image{
            id:back2B
            source:"images/levels/day2.png"
            anchors.bottom:parent.bottom
            x:back2.width

        }


    }


    Image{
        id:back3
        source:"images/levels/day3.png"
        anchors.bottom:parent.bottom
        x:calculateXPosition(parallaxFactor,mapX)//Woo.getMapX() * (1 - parallaxFactor)
        property real parallaxFactor:0.8

        Image{
            id:back3B
            source:"images/levels/day3.png"
            anchors.bottom:parent.bottom
            x: back3.width

        }
    }


    Image{
        id:back4
        source:"images/levels/trees2.png"
        anchors.bottom:parent.bottom
        x:calculateXPosition(parallaxFactor,mapX)//Woo.getMapX()
        property real parallaxFactor:0.7

        Image{
            id:back4B
            source:"images/levels/trees2.png"
            anchors.bottom:parent.bottom
            //anchors.left: 640+parent.right
            x:back4.width

        }

        Image{
            id:back4C
            source:"images/levels/trees2.png"
            anchors.bottom:parent.bottom
            x: back4.width*2

        }

    }

    Timer{
        running: true
        interval: 28
        repeat: true
        onTriggered:
        {

            back1.x = calculateXPosition(back1.parallaxFactor,mapX);
            back2.x = calculateXPosition(back2.parallaxFactor,mapX);
            back3.x = calculateXPosition(back3.parallaxFactor,mapX);
            back4.x = calculateXPosition(back4.parallaxFactor,mapX);

        }
    }

}
