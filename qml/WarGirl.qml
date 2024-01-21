import QtQuick 2.15
import QtQuick.Controls 2.15
import WarGirlImport 1.0
import QtMultimedia 5.15

Item {
    id:warGirl
    focus:true
    //x:warGirlReg.pos.x
    //y:warGirlReg.pos.y
    width:girlSprite.width
    height: girlSprite.height

    property bool facingRight:true
    property bool jumping:warGirlReg.isJumping
    property bool attacking: false
    property bool onRopeGravity:false
    property var enemies: warGirlReg.getEnemiesForQML()
    property int mapX: warGirlReg.mapPos.x
    property int mapY:warGirlReg.mapPos.y
    property int mapH:368 //proper way -->need to send from C++
    property int mapW:640*3 // proper way -->need to send from C++
    property int health: 200

    property bool moving: false
    property bool onRope:warGirlReg.isOnRope
    property bool crawling:false


    Keys.onRightPressed: { warGirlReg.moveRight() ; moving=true; girlSprite.goalSprite="run"; facingRight=true; warGirlReg.setRbutton(true) }
    Keys.onLeftPressed: {warGirlReg.moveLeft(); girlSprite.goalSprite="run";facingRight=false; warGirlReg.setLbutton(true) }
    Keys.onDigit1Pressed: {girlSprite.jumpTo("attack") ; attacking=true }
    Keys.onUpPressed : {warGirlReg.crawlUp();  if(onRope) girlSprite.jumpTo("crawl") ; crawling=true   }
    Keys.onDownPressed: {warGirlReg.crawlDown() ;if(onRope) girlSprite.jumpTo("crawl");crawling=true  }
    Keys.onSpacePressed:  {girlSprite.jumpTo("jump"); warGirlReg.jump(); onRopeGravity=true; gravityOnRopeDelay.start() ;onRopeTimer.stop()   }


    onOnRopeChanged: {
        if(onRope &&!crawling ) girlSprite.jumpTo("crawlIdle");
        if(!onRope &&!crawling) girlSprite.jumpTo("idle");
    }


    MainCharachter{
        id:warGirlReg
    }


    Keys.onReleased:
       {
           if (event.key === Qt.Key_Right)
           {

               girlSprite.goalSprite="idle"
               warGirlReg.setRbutton(false)
               moving=false;
           }

           if (event.key === Qt.Key_Left)
           {
               girlSprite.goalSprite="idle"
               warGirlReg.setLbutton(false)

           }

           if (event.key === Qt.Key_1)
            {
                girlSprite.goalSprite="idle"
                attacking=false;
            }

           if(event.key===Qt.Key_Down ||  event.key===Qt.key_Up )
               girlSprite.goalSprite="idle" ;crawling=false

           //if(event.key==Qt.Key_Space)
               //onRopeGravity=false;






       }



    SpriteSequence
    {
        id:girlSprite
        width:69 //framW
        height:44 //frameH
        running: true
        interpolate: false
        scale:1.3
        x:warGirlReg.pos.x
        y:warGirlReg.pos.y
        onXChanged: playerData.playerX=warGirlReg.pos.x
        onYChanged: playerData.playerY=warGirlReg.pos.y


        Sprite{
            name:"idle"
            source:"/images/FancyPants/girl.png"
            frameCount: 6; frameRate: 10
            frameWidth: 69
            frameHeight: 44


            to:{"idle":1, "jump":0, "run":0, "attack":0  }
        }

        Sprite{
            name:"run"
            source:"/images/FancyPants/girl.png"
            frameY:frameHeight
            frameCount: 6; frameRate: 10
            frameWidth: 69
            frameHeight: 44

            to:{"idle":0, "jump":0, "run":1 , "attack":0  }
        }

        Sprite{
            name:"attack"
            source:"/images/FancyPants/girl.png"
            frameY: frameHeight*3
            frameCount: 6; frameRate: 12
            frameWidth: 69
            frameHeight: 44

            to:{"idle":1, "run0":0, "attack":0 , "jump":0 }
        }


        Sprite{
            name:"jump"
            source:"/images/FancyPants/girl.png"
            frameY: frameHeight*7
            frameCount: 6; frameRate: 12
            frameWidth: 69
            frameHeight: 44

            to:{"idle":1, "run0":0, "attack":0 , "jump":0 }
        }

        Sprite{

            name:"crawl"
            source:"/images/FancyPants/girl.png"
            frameY: frameHeight*15
            frameX:frameWidth
            frameCount: 5; frameRate: 8
            frameWidth: 69
            frameHeight: 44

            to:{"crawlIdle":1, "run0":0, "attack":0 , "jump":0 }

        }

        Sprite{

            name:"crawlIdle"
            source:"/images/FancyPants/girl.png"
            frameY: frameHeight*15
            frameX:frameWidth
            frameCount: 1; frameRate: 10
            frameWidth: 69
            frameHeight: 44

            to:{"idle":1, "run0":0, "attack":0 , "jump":0 }

        }

        transform: Scale {
            origin.x: 26
            xScale:facingRight ? 1:-1
          }

    }



    Timer {
        id:gravityTimer
        running:true
        repeat:true
        interval:27
        onTriggered: if(!onRope) warGirlReg.applyGravity()

    }

    Timer
    {
        id:gravityOnRopeTimer
        interval: 150
        running:true
        repeat:true
        onTriggered: if(onRope && onRopeGravity)warGirlReg.applyGravityOnRope()
    }

    Timer
    {
        id:gravityOnRopeDelay
        running:false
        interval:300
        onTriggered: {onRopeGravity=false; onRopeTimer.restart() }

    }


    Timer
    {
        id:onRopeTimer
        running: true
        repeat:true
        interval:50
        onTriggered:  {warGirlReg.collisionVertRope(); }

    }


}
