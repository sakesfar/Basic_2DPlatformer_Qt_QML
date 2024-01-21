import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id:hBarStatus

    Connections
    {
        target: warG
        onHealthChanged :
        {
            if(warG.health>150 && warG.health<200)
                status.jumpTo("3")
            else if(warG.health>100 && warG.health<150)
                status.jumpTo("2")
            else if(warG.health>50 && warG.health<100)
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
            source:"/images/FancyPants/hbar.png"
            frameX:0
            frameCount: 1
            frameWidth: 32
            frameHeight: 20
            frameDuration:100

            to:{"1":0, "2":0, "3":0 ,"full":1}

        }

        Sprite{
            name:"1"
            source:"/images/FancyPants/hbar.png"
            frameX:96
            frameCount: 1
            frameWidth: 32
            frameHeight: 20
            frameDuration:100

            to:{"1":1, "2":0, "3":0 ,"full":0}

        }
        Sprite{
            name:"2"
            source:"/images/FancyPants/hbar.png"
            frameX:64
            frameCount: 1
            frameWidth: 32
            frameHeight: 20
            frameDuration:100

            to:{"1":0, "2":1, "3":0 ,"full":0}

        }
        Sprite{
            name:"3"
            source:"/images/FancyPants/hbar.png"
            frameX:32
            frameCount: 1
            frameWidth: 32
            frameHeight: 20
            frameDuration:100

            to:{"1":0, "2":0, "3":1 ,"full":0}

        }

        Sprite{
            name:"dead"
            source:"/images/FancyPants/hbar.png"
            frameX:128
            frameCount: 1
            frameWidth: 32
            frameHeight: 20
            frameDuration:100

            to:{"1":0, "2":0, "3":0 ,"full":0, "dead":0}

        }
    }

}
