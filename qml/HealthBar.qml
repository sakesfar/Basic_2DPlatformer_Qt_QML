import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id:hBarStatus


    Connections{
        target:Woo
        onSendHealth:
        {
            if(health<270 &&health >225)
                status.jumpTo("3")

            if(health<225 &&health >150)
                status.jumpTo("2")

            if(health<150 &&health >75)
                status.jumpTo("1")

        }
    }

    SpriteSequence{
        id:status
        width:32 //framW
        height:20 //frameH
        x:15
        y:10
        running: true
        interpolate: true
        scale:2.3


        Sprite{
            name:"full"
            source:"/images/woo/hbar.png"
            frameX:0
            frameCount: 1
            frameWidth: 32
            frameHeight: 20
            frameDuration:100

            to:{"1":0, "2":0, "3":0 ,"full":1}

        }

        Sprite{
            name:"1"
            source:"/images/woo/hbar.png"
            frameX:96
            frameCount: 1
            frameWidth: 32
            frameHeight: 20
            frameDuration:100

            to:{"1":1, "2":0, "3":0 ,"full":0}

        }
        Sprite{
            name:"2"
            source:"/images/woo/hbar.png"
            frameX:64
            frameCount: 1
            frameWidth: 32
            frameHeight: 20
            frameDuration:100

            to:{"1":0, "2":1, "3":0 ,"full":0}

        }
        Sprite{
            name:"3"
            source:"/images/woo/hbar.png"
            frameX:32
            frameCount: 1
            frameWidth: 32
            frameHeight: 20
            frameDuration:100

            to:{"1":0, "2":0, "3":1 ,"full":0}

        }
    }

}
