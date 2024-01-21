.pragma library



function facingDirection(enemyX, enemyWidth, enemyY, playerX, playerWidth, playerY, boundaryX, sameLevelY)
{
    var enemyCenterX = enemyX + enemyWidth / 2;
    var playerCenterX = playerX + playerWidth / 2;
    var isWithinBoundaryX = Math.abs(enemyCenterX - playerCenterX) <= boundaryX;
    var isOnSameLevelY = Math.abs(enemyY - playerY) <= sameLevelY ? true :false;


     return {
            nearby: isWithinBoundaryX && isOnSameLevelY,
            direction:playerCenterX > enemyCenterX
        }


}

function shouldAttack(  enemyX, enemyY, enemyWidth, enemyHeight,
                      playerX, playerY, playerWidth, playerHeight, isPlayerAttacking )
{

    var hoverlap = (playerX+ playerWidth > enemyX) && (enemyX + enemyWidth > playerX);

    var voverlap = (playerY  <= enemyY) && (playerY+playerHeight >=enemyY-enemyHeight);

    var isColliding = hoverlap && voverlap;

    var isNearby = isColliding   

        return {
            isNearby:isNearby,
            shouldAttack: isColliding && !isPlayerAttacking,
            isHit: isColliding && isPlayerAttacking
        };
}

function getData(type)
{
    if (type=="skeleton")
    {
        return {width:35, height:50}
    }

    if(type=="mushroom")
    {
        return {width:20, height:35}
    }

    if(type=="goblin")
    {
        return {width:34, height:35}
    }
}


function moveEnemy(enemy, isPlayerAttacking, stationaryX, xMove, isPlayerNear)

{

    enemy.x = stationaryX + enemy.localX + enemy.xMapOff //- enemy.xoffset;

    if(enemy.type==="mushroom" )
        xMove=30;

    else if(enemy.type==="goblin")
        xMove=25


    if (!isPlayerAttacking && !isPlayerNear )
    {

           enemy.localX += enemy.moveSpeed * enemy.direction;

           if (enemy.localX > xMove)
           {enemy.direction = -1; enemy.facingDir=false }

           if (enemy.localX < -xMove)
           {enemy.direction = 1; enemy.facingDir=true }

           //enemy.x = stationaryX + enemy.localX + enemy.xMapOff-enemy.xoffset;
           enemy.enemyX = stationaryX + enemy.localX+enemy.xMapOff+enemy.xoffset;
           enemy.run()
    }







}

function isNear(enemyX, enemyY, enemyWidth, enemyHeight,
                playerX, playerY, playerWidth, playerHeight)
{
    var hoverlap = (playerX+ playerWidth > enemyX) && (enemyX + enemyWidth > playerX);

    var voverlap = (playerY  <= enemyY) && (playerY+playerHeight >=enemyY-enemyHeight);

    var isColliding = hoverlap && voverlap;

    return isColliding ? true : false;
}




