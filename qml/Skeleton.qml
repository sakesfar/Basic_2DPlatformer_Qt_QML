import QtQuick 2.15
import QtQuick.Controls 2.15
import "EnemyLogic.js" as EnemyLogic


Item {
    id:skeleton
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
            source:"/images/enemy/skeleton/sk_idle.png"
            frameX:0
            frameCount: 1
            frameWidth: 150
            frameHeight: 150
            frameDuration:1

            to:{"walking":0, "idle":1,"hit":0 , "attack":0, "death":0}

        }

        Sprite{
            name:"walking"
            source:"/images/enemy/skeleton/sk_walk.png"
            frameCount: 4 ; frameRate: 7
            frameWidth: 150
            frameHeight: 150

            to:{"idle":0,"walking":1,"hit":0, "attack":0, "death":0}

        }

        Sprite{
            name:"attack"
            source:"/images/enemy/skeleton/sk_at.png"
            frameCount: 8 ; frameRate: 8
            frameWidth: 150
            frameHeight: 150

            to:{"idle":1,"walking":0,"hit":0, "attack":0, "death":0}

        }

        Sprite{
            name:"hit"
            source:"/images/enemy/skeleton/sk_hit.png"
            frameCount: 4 ; frameRate: 8
            frameWidth: 150
            frameHeight: 150

            to:{"idle":1,"walking":0, "hit":0, "attack":0, "death":0}

        }

        Sprite{
            name:"death"
            source:"/images/enemy/skeleton/sk_death.png"
            frameCount: 4 ; frameRate: 4
            frameWidth: 150
            frameHeight: 150

            to:{"idle":0,"walking":0, "hit":0, "attack":0, "death":0}

        }



        transform: Scale {
            origin.x: sprite.width/2
            xScale: facingDir ? 1:-1
          }


    }






}
