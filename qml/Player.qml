import QtQuick 2.15
import QtQuick.Controls 2.15

Item {

    Keys.onRightPressed: {Woo.moveRight(); spriteDir=true; Woo.setRButton(true);player.goalSprite="walking"}
    Keys.onLeftPressed: {Woo.moveLeft(); spriteDir=false; Woo.setLButton(true);player.goalSprite="walking"}
    Keys.onUpPressed: {Woo.jump() ; player.goalSprite="jumping"}
    Keys.onDigit1Pressed: {player.jumpTo("fight"); Woo.isAttacking(true) }

    property bool spriteDir:true


    Keys.onReleased:
       {
           if (event.key === Qt.Key_Right)
           {
               Woo.setRButton(false)
               player.goalSprite ="idle"
           }

           if (event.key === Qt.Key_Left)
           {
               player.goalSprite ="idle"
               Woo.setLButton(false)
           }

           if (event.key === Qt.Key_1)
           {
              Woo.isAttacking(false);
           }


       }

    Connections{
        target: Woo
        onPosXChanged : {player.x=Woo.getPosX() ; }
        onPosYChanged : player.y =Woo.getPosY()
        onIdxOfSkeletonAttack:
        {
            if(ios>=0)
            player.jumpTo("hit")
        }

    }


    SpriteSequence{
        id:player
        width:32 //framW
        height:32 //frameH
        x:10
        y:336-player.height
        running: true
        interpolate: true
        scale:1.3


        Sprite{
            name:"idle"
            source:"/images/woo/woo.png"
            frameX:5
            frameCount: 1
            frameWidth: 32
            frameHeight: 32
            frameDuration:100

            to:{"idle":1, "jumping":0, "walking":0 ,"fight":0, "hit": 0, "death":0, "bug":0 }
        }

        Sprite{
            name:"walking"
            source:"/images/woo/woo.png"
            frameY: 96
            frameX:5
            frameCount: 8 ; frameRate: 10
            frameWidth: 32
            frameHeight: 32

            to:{"idle":0, "jumping":0, "walking":1,"fight":0, "hit": 0, "death":0, "bug":0}

        }

        Sprite{
            name:"jumping"
            source:"/images/woo/woo.png"
            frameY: 160
            frameX:5
            frameCount: 8 ; frameRate: 15
            frameWidth: 32
            frameHeight: 32

            to:{"idle":1, "jumping":0, "walking":0,"fight":0, "hit": 0, "death":0, "bug":0}

        }

        Sprite{
            name:"fight"
            source:"/images/woo/woo.png"
            frameY: 256
            frameX:5
            frameCount: 8 ; frameRate: 15
            frameWidth: 32
            frameHeight: 32

            to:{"idle":1, "jumping":0, "walking":0,"fight":0, "hit": 0, "death":0, "bug":0}

        }

        Sprite{
            name:"hit"
            source:"/images/woo/woo.png"
            frameY: 192
            frameX:5
            frameCount: 3 ; frameRate: 5
            frameWidth: 32
            frameHeight: 32

            to:{"idle":1, "jumping":0, "walking":0,"fight":0, "hit": 0, "death":0, "bug":0}

        }


        Sprite{
            name:"death"
            source:"/images/woo/woo.png"
            frameY: 224
            frameX:5
            frameCount: 8 ; frameRate: 8
            frameWidth: 32
            frameHeight: 32

            to:{"idle":0, "jumping":0, "walking":0,"fight":0, "hit": 0, "death":0, "bug":0}
        }



        Sprite{
            name:"bug"
            source:"/images/woo/woo.png"
            frameY: 224
            frameX:5
            frameCount: 8 ; frameRate: 8
            frameWidth: 32
            frameHeight: 32

            to:{"idle":0, "jumping":0, "walking":0,"fight":0, "hit": 0, "death":0, "bug":1}

        }

        Sprite{
            name:"bug2"
            source:"/images/woo/woo.png"
            frameY: 224
            frameX:5
            frameCount: 8 ; frameRate: 8
            frameWidth: 32
            frameHeight: 32

            to:{"idle":0, "jumping":0, "walking":0,"fight":0, "hit": 0, "death":0, "bug":1}

        }

        transform: Scale{
            origin.x:10
            xScale:  spriteDir ? 1 : -1

        }

    }

    focus:true

    HealthBar{
        id:hbar
        anchors.fill: parent
    }


    Timer {
        id:gravityTimer
        running:true
        repeat:true
        interval:25
        onTriggered: Woo.applyGravity()
    }



}
