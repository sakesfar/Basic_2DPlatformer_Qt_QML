import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id:skeleton
    property bool directionRight:true
    property bool playerSpotted:false
    property bool attackingPlayer:false
    property int health: 50
    property int attackPower:2    
    property bool isActive:true
    enabled: isActive
    opacity: isActive ? 1 : 0



    x:modelData["x"]-55
    y:modelData["y"] +50


    function adjustPosX()
    {

        return modelData["x"]-63+Woo.getMapX();

    }




    Connections{
        target:Woo
        onIdxOfSkeletonAttack:{
            if(health>0)
            {
            if(ios==index &&!dir)
            {
                //directionRight=dir;

                sprite.jumpTo("attack");

            }

            if(ios==index &&dir)
            {
                sprite.jumpTo("hit");
                health-=0.05;

            }
            }

            else
            {
                if(ios==index)
                {
                    sprite.jumpTo("death");
                    isActive=false;


                }
            }




        }

        onIdxOfSkeletonDirection : {
          if(ios==index) directionRight=dir;


        }

        onPlayerAttacks:
        {



        }
    }





    SpriteSequence{
        id:sprite
        width:150
        height:150
        anchors.bottom: parent.bottom
        //anchors.horizontalCenter: parent.horizontalCenter
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
            frameCount: 8 ; frameRate: 10
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

        Sprite{
            name:"bug"
            source:"/images/enemy/skeleton/sk_death.png"
            frameCount: 4 ; frameRate: 4
            frameWidth: 150
            frameHeight: 150

            to:{"idle":0,"walking":0, "hit":0, "attack":0, "death":0}

        }


        transform: Scale {
            origin.x: sprite.width/2
            xScale:  directionRight ?  1 : -1
          }


    }

    Timer{
        id:updateSkPos
        running:true
        repeat:true
        interval:10
        onTriggered: {
            skeleton.x=adjustPosX() ;

            if(!isActive)
            Woo.collisionWithSkeleton(index);
            else
                Woo.collisionWithSkeleton(-1);

        }
    }


}
