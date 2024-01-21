import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id:goblin
    property Item parentEnemy
    property bool facingDir:parent.facingDir
    x:parent.x
    y:parent.y

    Connections
    {
        target:parentEnemy
        onAttack:sprite.jumpTo("attack")
        onHit:sprite.jumpTo("hit")
        onInitiateDeath:sprite.jumpTo("death")
        onRun:sprite.jumpTo("walking")
    }



    SpriteSequence{
        id:sprite
        width:150
        height:150
        anchors.bottom: parent.bottom
        running: true
        interpolate: true


        Sprite{
            name:"idle"
            source:"/images/enemy/goblin/Idle.png"
            frameX:0
            frameCount: 1
            frameWidth: 150
            frameHeight: 150
            frameDuration:1

            to:{"walking":0, "idle":1,"hit":0 , "attack":0, "death":0}

        }

        Sprite{
            name:"walking"
            source:"/images/enemy/goblin/Run.png"
            frameCount: 4 ; frameRate: 7
            frameWidth: 150
            frameHeight: 150

            to:{"idle":0,"walking":1,"hit":0, "attack":0, "death":0}

        }

        Sprite{
            name:"attack"
            source:"/images/enemy/goblin/attack.png"
            frameCount: 8 ; frameRate: 10
            frameWidth: 150
            frameHeight: 150

            to:{"idle":1,"walking":0,"hit":0, "attack":0, "death":0}

        }

        Sprite{
            name:"hit"
            source:"/images/enemy/goblin/hit.png"
            frameCount: 4 ; frameRate: 8
            frameWidth: 150
            frameHeight: 150

            to:{"idle":1,"walking":0, "hit":0, "attack":0, "death":0}

        }

        Sprite{
            name:"death"
            source:"/images/enemy/goblin/Death.png"
            frameCount: 4 ; frameRate: 4
            frameWidth: 150
            frameHeight: 150

            to:{"idle":0,"walking":0, "hit":0, "attack":0, "death":0}

        }




        transform: Scale {
            origin.x: sprite.width/2
            xScale:  facingDir ?  1 : -1
          }


    }
}


