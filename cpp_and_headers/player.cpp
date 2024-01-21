#include "player.h"



Player::Player() :GameData(GameConstants::path, GameConstants::wndW, GameConstants::wndH)
{

    m_w=GameConstants::playerW;
    m_h=GameConstants::playerH;

    m_pos={10,GameConstants::mapGround};
    m_gravity=3;
    m_xspeed=4;
    m_yspeed=0;
    m_plAttacks=false;
    m_isOnPlatform=false;
    m_isjumping=false;
    m_isOnRope=false;
    m_health=300;
}


const QPoint &Player::pos() const
{
    return m_pos;
}

bool Player::isOnRope() const
{
    return m_isOnRope;

}

bool Player::isJumping() const
{
    return m_isjumping;
}

bool Player::collisionAtPos(double newX, double newY)
{

    for (int i=0; i<m_objectsData.size(); ++i)
        {
            QJsonObject object = m_objectsData[i].toObject();
            double x = object["x"].toDouble()+m_mapPos.x();;
            double y = object["y"].toDouble();
            double w = object["width"].toDouble();
            double h = object["height"].toDouble();
            QString rope =object["name"].toString();



            if ((newX + m_w >= x && newX+(GameConstants::xoffsetLeft+GameConstants::xoffsetRight) < x + w) && (newY + m_h-GameConstants::yoffset >= y && newY < y + h)
                   && rope!="rope")
            {
                return true;
            }

        }

        return false;

}

void Player::moveRight()
{    

    int predictedX = m_pos.rx()+m_xspeed-GameConstants::xoffsetRight;
    //int predictedX=m_pos.rx()+m_xspeed-GameConstants::xoffsetLeft;


    if (!collisionAtPos(predictedX, m_pos.ry()) &&!m_isOnRope)
    {
        if (m_pos.x() < m_wndW / 2 )
        {
            QPoint newPos ={m_pos.rx() + m_xspeed, m_pos.ry()};
            setPos(newPos);

        }

        else if (m_mapPos.x() > -(m_mapW - m_wndW))
        {
            int newMapPosX=m_mapPos.rx() - m_xspeed;
            newMapPosX = std::max(newMapPosX, -(m_mapW - m_wndW));
            QPoint newMapPos = {newMapPosX, m_mapPos.ry()};
            //m_mapPos.rx()=newMapPosX;
            setMapPos(newMapPos);
        }

        else if (m_pos.x() + m_w < m_wndW )
        {
            QPoint newPos = {m_pos.rx() + m_xspeed, m_pos.ry()};
            setPos(newPos);

        }

        return;

    }

    if (m_isOnRope)
    {
        setIsOnRope(false);

        if (m_pos.x() < m_wndW / 2 )
        {
            QPoint newPos ={m_pos.rx() + m_xspeed+14, m_pos.ry()};
            setPos(newPos);

        }

        else if (m_mapPos.x() > -(m_mapW - m_wndW))
        {
            int newMapPosX=m_mapPos.rx() - m_xspeed-14;
            newMapPosX = std::max(newMapPosX, -(m_mapW - m_wndW));
            QPoint newMapPos = {newMapPosX, m_mapPos.ry()};
            //m_mapPos.rx()=newMapPosX;
            setMapPos(newMapPos);
        }

        else if (m_pos.x() + m_w < m_wndW )
        {
            QPoint newPos = {m_pos.rx() + m_xspeed+14, m_pos.ry()};
            setPos(newPos);

        }

        return;

    }
}

void Player::moveLeft()
{
    int predictedX = m_pos.rx()-m_xspeed -GameConstants::xoffsetRight;
    //int predictedX=m_pos.rx()+m_xspeed-GameConstants::xoffsetLeft;


    if (!collisionAtPos(predictedX, m_pos.y())&&!m_isOnRope)
    {

        if (m_pos.x() > m_wndW / 2 - m_w / 2 && m_mapPos.x() < 0 )
        {
            QPoint newPos ={m_pos.rx() - m_xspeed, m_pos.ry()};
            setPos(newPos);

        }

        else if (m_mapPos.x() < 0)
        {

            int newMapPosX=m_mapPos.rx() + m_xspeed;
            newMapPosX = std::min(newMapPosX,0);
            QPoint newMapPos = {newMapPosX, m_mapPos.ry()};
            //m_mapPos.rx()=newMapPosX;
            setMapPos(newMapPos);
        }

        else if (m_pos.x() > 0 )
        {
            QPoint newPos = {m_pos.rx() - m_xspeed, m_pos.ry()};
            setPos(newPos);

        }

        return;
    }

    if (m_isOnRope)
    {
        if (m_pos.x() < m_wndW / 2 )
        {
            QPoint newPos ={m_pos.rx() - m_xspeed-12, m_pos.ry()};
            setPos(newPos);

        }

        else if (m_mapPos.x() > -(m_mapW - m_wndW))
        {
            int newMapPosX=m_mapPos.rx() + m_xspeed+12;
            newMapPosX = std::max(newMapPosX, -(m_mapW - m_wndW));
            QPoint newMapPos = {newMapPosX, m_mapPos.ry()};
            //m_mapPos.rx()=newMapPosX;
            setMapPos(newMapPos);
        }

        else if (m_pos.x() + m_w < m_wndW )
        {
            QPoint newPos = {m_pos.rx() - m_xspeed-12, m_pos.ry()};
            setPos(newPos);

        }

        return;

    }


}

void Player::setPos(const QPoint &pos)
{
    if(m_pos!=pos)
    {
        m_pos=pos;
        emit posChanged();
    }
}

void Player::setIsJumping(bool val)
{
    m_isjumping=val;
    emit isJumpingChanged();
}

void Player::setIsOnRope(bool val)
{
    m_isOnRope=val;
    emit isOnRopeChanged();
}

void Player::jump()
{

    if((m_isOnPlatform || m_pos.y()==GameConstants::mapGround )&&!m_isjumping  )
    { m_yspeed=-30; setIsJumping(true); setIsOnRope(false); }

    if(m_isOnRope &&!m_isjumping  )
    { m_yspeed=-25; setIsJumping(true); setIsOnRope(false); }

    qDebug()<<m_pos.y()-m_wndH/2<<'\n';



}

void Player::crawlUp()
{
    if(m_isOnRope)
    {
        QPoint newPos ={m_pos.rx(), m_pos.ry()-1};
        setPos(newPos);;

    }

}

void Player::crawlDown()
{
    if(m_isOnRope)
    {
        QPoint newPos ={m_pos.rx(), m_pos.ry()+1};
        setPos(newPos);;

    }

}

void Player::adjustY(int newY)
{
    if (newY < m_wndH / 2)
    {

        // If the player is above the middle of the window, move the map instead of the player
        int newMapPosY =  newY-m_mapPos.ry(); //m_mapPos.ry() + m_yspeed;
        //newMapPosY =   //std::min(newMapPosY, 0); // Prevent the map from scrolling down too far
        newMapPosY = std::max(newMapPosY, -(m_mapH*2 - m_wndH)); // Prevent the map from scrolling up too far
        QPoint newMapPos = {m_mapPos.rx(), newMapPosY};
        setMapPos(newMapPos);
    }

    else
    {
        // If the player is below the middle of the window, move the player
        newY = std::min(newY, m_wndH - m_h); // Prevent the player from falling below the window
        QPoint newPos = {m_pos.rx(), newY};
        setPos(newPos);
    }




}

int Player::collisionVertical()
{
    static double lastTimeAbovePlatform = 0;
    double currentTime = getCurrentTime();    
    int landingY = 0;
    m_isOnPlatform=false;
    setIsOnRope(false);
    int lastY=m_pos.y();

   for (int i=0;i<m_objectsData.size();++i)
   {
       QJsonObject object = m_objectsData[i].toObject();
       double x = object["x"].toDouble()+m_mapPos.x();
       double y = object["y"].toDouble();
       double w = object["width"].toDouble();
       double h = object["height"].toDouble();
       QString rope =object["name"].toString();

       bool horOverlap = m_pos.x()-GameConstants::xoffsetRight + m_w >= x && m_pos.x()-GameConstants::xoffsetRight+(GameConstants::xoffsetLeft+GameConstants::xoffsetRight) < x + w;
       bool verOverlap = m_pos.ry() + m_h >= y  && m_pos.ry() + m_h < y + h;


       if (horOverlap && verOverlap &&rope!="rope")
       {
           lastTimeAbovePlatform = currentTime;
           m_isOnPlatform = true;
           landingY = y - m_h -GameConstants::yoffsetForVertColl;
           setIsOnRope(false);
           break;
       }       


   }

   if (!m_isOnPlatform && currentTime - lastTimeAbovePlatform <= GameConstants::GRACE_PERIOD &&!m_isOnRope)
       {               
           m_isOnPlatform = true;
           return landingY;
       }

   return m_isOnPlatform ? landingY : 0;

}

void Player::collisionVertRope()
{

    setIsOnRope(false);
    int lastX;



   for (int i=0;i<m_objectsData.size();++i)
   {
       QJsonObject object = m_objectsData[i].toObject();
       double x = object["x"].toDouble()+m_mapPos.x();
       double y = object["y"].toDouble();
       double w = object["width"].toDouble();
       double h = object["height"].toDouble();
       QString rope =object["name"].toString();

       bool horOverlap = m_pos.x()-GameConstants::xoffsetRight + m_w >= x && m_pos.x()-GameConstants::xoffsetRight+(GameConstants::xoffsetLeft+GameConstants::xoffsetRight) < x + w;
       bool verOverlap = m_pos.ry() + m_h >= y  && m_pos.ry() + m_h < y + h;

       if(m_pos.x()-GameConstants::xoffsetRight+(GameConstants::xoffsetLeft+GameConstants::xoffsetRight)<=x+w)
          lastX=x-GameConstants::xoffseLeftCrawl+w/2;

       if(m_pos.x()-GameConstants::xoffsetRight + m_w>=x)
          lastX=x-GameConstants::xoffseLeftCrawl+w/2-3;


       if (horOverlap && verOverlap &&rope=="rope")
       {
           setPos(QPoint(lastX,m_pos.y()));
           m_yspeed=0;
           setIsOnRope(true);
           setIsJumping(false);
           return;
       }
       else
           setIsOnRope(false);


   }

   setIsOnRope(false);






}

void Player::applyGravity()
{

    int yPlatform = collisionVertical();


    if(yPlatform!=0 &&m_yspeed>0 &&!m_isOnRope)
    {
        m_yspeed=0;
        m_pos.ry()=yPlatform;
        QPoint newY={m_pos.x(),m_pos.ry()};
        setPos(newY);
        m_isOnPlatform=true;
        setIsJumping(false);
        setIsOnRope(false);

    }

      m_yspeed =std::min(m_yspeed +m_gravity, 20);
      int newY=m_pos.ry()+m_yspeed;
      QPoint newPos={m_pos.x(), newY};


        //logic for map.y scrolling
      /*
      {

          if (newY < m_wndH / 2 && m_mapPos.ry()<0 &&!m_isOnPlatformh) {
                 // Scroll map
                 int newMapPosY = m_mapPos.ry() - m_yspeed;
                 newMapPosY = std::min(newMapPosY, 0);
                 //m_mapPos.setY(newMapPosY);
                 QPoint mapP = {m_mapPos.x(),newMapPosY };
                 setMapPos(mapP);
             }

          else if(newY>m_wndH/2 && m_mapPos.y()>-(m_mapH-m_wndH)&&!m_isOnPlatform)
          {

                 int newMapPosY = m_mapPos.ry() - m_yspeed;
                 newMapPosY = std::max(newMapPosY, -(m_mapH-m_wndH));
                 QPoint mapP = {m_mapPos.x(),newMapPosY };
                 setMapPos(mapP);

          }
          else {
                 // Move player
                 //newY = std::min(newY, m_wndH - m_h);
                 newY = std::max(newY, 0);  // Ensure player doesn't go above the map
                 //m_pos.setY(newY);
                 newPos={m_pos.x(), newY};
              setPos(newPos);
             }
      }
          */







      setIsOnRope(false);
      setPos(newPos);





    if (m_mbuttons.right &&!m_isOnPlatform &&m_pos.y()<GameConstants::mapGround)
       moveRight();

    if (m_mbuttons.left&&!m_isOnPlatform&&m_pos.y()<GameConstants::mapGround)
        moveLeft();



    if (m_pos.y() > GameConstants::mapGround)
    {       
        QPoint newY = {m_pos.x(), GameConstants::mapGround};
        setPos(newY);
        setIsOnRope(false);
        m_isOnPlatform=true;

        m_isjumping = false;
        setIsJumping(false);
        m_yspeed = 0;

    }



}

void Player::applyGravityOnRope()
{
    m_yspeed =std::min(m_yspeed +m_gravity-1, 20);
    QPoint newY={m_pos.x(), m_pos.ry()+m_yspeed};    
    setPos(newY);

}
