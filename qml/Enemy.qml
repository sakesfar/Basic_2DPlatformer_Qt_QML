import QtQuick 2.15
import QtQuick.Controls 2.15

import "EnemyLogic.js" as EnemyLogic

Item {

    id:enemy
    property string type:parent.type
    property string action:modelData["name"]
    property var enemyData: EnemyLogic.getData(type)
    property int enemyW: enemyData.width
    property int enemyH:enemyData.width
    property int xMapOff:0
    property int yMapOff:0
    property int enemyX: modelData["x"]+xMapOff
    property int enemyY: modelData["y"]
    property int spriteW:150
    property int spriteH:150

    property bool canChangeState: true
    property int stationaryX:0
    property int localX: 0
    property int direction :1
    property real moveSpeed:1
    property int incrementX:0

    Component.onCompleted: {stationaryX=x ; localX=0; console.log("mapY:", warG.mapY)}



    property int xoffset:60
    property int yoffset: 50
    property bool facingDir:true
    property bool attackingPlayer:false
    property int health: 50
    property int attackPower:2
    property bool isActive:true
    property bool plNear:false
    onPlNearChanged:  console.log("player is near:", plNear)



    x:modelData["x"]-xoffset+xMapOff//where to draw an Enemy with offset
    y:modelData["y"]+yoffset


    signal attack();
    signal hit();
    signal initiateDeath();
    signal run();







    Timer
    {
        id:playerProximityTimer
        interval:30
        running: true
        repeat: true
        onTriggered:         if(enemy.enabled==true)
                   plNear=EnemyLogic.isNear(enemy.enemyX, enemy.enemyY, enemy.enemyW, enemy.enemyH,
                playerData.playerX, playerData.playerY,playerData.playerW, playerData.playerH)
    }





    Timer
    {
        id:timerMove
        interval: 15  // Adjust as needed for smoother movement
        repeat: true
        running: true
        onTriggered: {

            if(canChangeState && enemy.action=="a")
             EnemyLogic.moveEnemy(enemy,  false, stationaryX,80, plNear);
        }
    }




    Timer
    {
        id:facingTimer
        running: true
        repeat: true
        interval: 100
        onTriggered:
        {
            if(plNear)
            {
            var condition =EnemyLogic.facingDirection(enemy.x,enemy.spriteW, enemyY ,
                  playerData.playerX, playerData.playerW,playerData.playerY+playerData.playerH,100,30)
            if(condition.nearby)
                facingDir=condition.direction
            }

        }


    }


    Timer
    {
        id: hitReactionTimer
        interval: 300
        onTriggered: canChangeState = true;
    }


    Timer
    {
        id:attackTimer
        running: true
        repeat: true
        interval: 80
        onTriggered: {


            if (canChangeState)
            {

                var action =EnemyLogic.shouldAttack(enemy.enemyX, enemy.enemyY, enemy.enemyW, enemy.enemyH,
                                     playerData.playerX, playerData.playerY,playerData.playerW,
                                     playerData.playerH, playerData.isAttacking )


                if(action.shouldAttack &&action.isNearby)
                    {attack(); warG.health-=1;  }

                if(action.isHit&&action.isNearby)
                { canChangeState = false;  hitReactionTimer.restart(); health-=25;  hit(); }


            }
        }
    }

    Timer
    {
        id:monitorLife
        running: true
        repeat: true
        interval: 100
        onTriggered:
        {
            if(enemy.health<=0)
            {

                //sprite.jumpTo("death")
                initiateDeath();
                attackTimer.stop();
                hitReactionTimer.stop()
                deathTimer.start();
            }
        }
    }

    Timer
    {
        id:deathTimer
        running: false
        interval: 650
        onTriggered: {
            enemy.enabled=false
            enemy.visible=false
            monitorLife.stop()
        }
    }


    Loader{
        id:dynamicEnemyLoader
        active:type!=""
        source: getEnemyComponent(enemy.type)
        property alias facingDir:enemy.facingDir        
        onLoaded:{
            item.parentEnemy = enemy

        }



    }

    function getEnemyComponent(type)
    {
        switch(type)
        {
            case "skeleton":
                return "Skeleton.qml";
            case "mushroom":
                return "Mushroom.qml";
            case "goblin":
                return "Goblin.qml";
            case "flying eye":
                return "FlyingEye.qml";

        }

    }

}







