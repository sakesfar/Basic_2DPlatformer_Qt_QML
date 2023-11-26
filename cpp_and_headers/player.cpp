#include "player.h"


int yground = 324-15*1.3;
const double VERTICAL_TOLERANCE = 10.0;
const double GRACE_PERIOD = 0.01;



Player::Player(const QString& path , const QPoint& mapPos, int ww, int wh, int mW, int mH, const QPoint &pos, int w, int h, int xsp, int ysp, QObject *parent) :
    GameData(path, mapPos, ww, wh , mW, mH), m_pos{pos}, m_w{int(w*1.3)}, m_h{int(h*1.3)}, m_xspeed {xsp}, m_yspeed {ysp} {}

int Player::getPosX() const
{
    return m_pos.x();
}

int Player::getPosY() const
{
    return m_pos.y();
}

void Player::moveRight()
{
    int predictedX = m_pos.rx()+m_xspeed ;

    if (!collisionAtPosition(predictedX, m_pos.y()-2))
    {
        if (m_pos.x() < m_wndW / 2 )
        {
            m_pos.rx() += m_xspeed;

        }

        else if (m_mapPos.x() > -(m_mapW - m_wndW))
        {
            m_mapPos.rx() -= m_xspeed;
            m_mapPos.rx() = std::max(m_mapPos.x(), -(m_mapW - m_wndW));
        }

        else if (m_pos.x() + m_w < m_wndW )
        {
            m_pos.rx() += m_xspeed;

        }

    }

    emit posXChanged();


}

void Player::moveLeft()
{
    int predictedX = m_pos.rx()-m_xspeed ;

    if (!collisionAtPosition(predictedX, m_pos.y()-2))
    {
        if (m_pos.x() > m_wndW / 2 - m_w / 2 && m_mapPos.x() < 0 )
        {
            m_pos.rx() -= m_xspeed;

        }

        else if (m_mapPos.x() < 0)
        {
            m_mapPos.rx() += m_xspeed;
            m_mapPos.rx() = std::min(m_mapPos.x(), 0);
        }

        else if (m_pos.x() > 0 )
        {
            m_pos.rx() -= m_xspeed;

        }
    }

    emit posXChanged();

}

void Player::jump()
{
    //int yground = 337-m_h*1.3;

    if(m_isOnPlatform || m_pos.y()==yground)
        m_yspeed=-30;

}

int Player::collistionVertical()
{

    static double lastTimeAbovePlatform = 0;
    double currentTime = getCurrentTime();

    int landingY = 0;


    m_isOnPlatform=false;

   for (int i=0;i<m_objectsData.size();++i)
   {
       QJsonObject object = m_objectsData[i].toObject();
       double x = object["x"].toDouble()+m_mapPos.x();
       double y = object["y"].toDouble();
       double w = object["width"].toDouble();
       double h = object["height"].toDouble();

       bool horOverlap = m_pos.rx() + m_w >= x && m_pos.rx() < x + w;
       bool verOverlap = m_pos.ry() + m_h >= y-VERTICAL_TOLERANCE  && m_pos.ry() + m_h < y + h;


       if (horOverlap && verOverlap)
       {
           lastTimeAbovePlatform = currentTime;
           m_isOnPlatform = true;
           //return y - m_h-2 ;
           landingY = y - m_h-2 ;

       }

   }

   if (!m_isOnPlatform && currentTime - lastTimeAbovePlatform <= GRACE_PERIOD)
       {
           // If the player is within the grace period and hasn't landed directly
           qDebug()<<currentTime - lastTimeAbovePlatform;
           m_isOnPlatform = true;
           return landingY;
       }




   return m_isOnPlatform ? landingY : 0;
   //return 0;

}

void Player::applyGravity()
{
    int yPlatform = collistionVertical();

    if(yPlatform!=0 &&m_yspeed>0)
    {
        m_yspeed=0;
        m_pos.ry()=yPlatform;
        m_isOnPlatform=true;
        emit posYChanged();


    }


      //m_yspeed += m_gravity; // apply gravity once in air
      m_yspeed =std::min(m_yspeed +m_gravity, 25); // apply gravity once in air
      m_pos.ry() += m_yspeed;




    if (m_mbuttons.right &&!m_isOnPlatform &&m_pos.y()<yground )
        moveRight();

    if (m_mbuttons.left&&!m_isOnPlatform&&m_pos.y()<yground)
        moveLeft();


     emit posYChanged();


    if (m_pos.y() >= yground)
    {
        m_pos.setY(yground);
        emit posYChanged();
        m_isjumping = false;
        m_yspeed = 0;
    }


}

void Player::setRButton(bool val)
{
    m_mbuttons.right=val;
}

void Player::setLButton(bool val)
{
     m_mbuttons.left=val;

}

bool Player::playerMovingRight()
{
    return m_mbuttons.right;

}

bool Player::playerMovingLeft()
{
    return m_mbuttons.left;

}

bool Player::collisionWithSkeleton(int idx)
{

    static std::set<int> deadSkels{};
    deadSkels.insert(idx);


    QJsonArray skelArr = getSKeletonPos();
    int sk_w = 40;
    int sk_h =50;


    for(int i = 0; i <skelArr.size();++i)
    {
        double x = skelArr[i].toObject()["x"].toDouble()+getMapX();
        double y = skelArr[i].toObject()["y"].toDouble();

        bool leftToPlayer = x+sk_w<m_pos.rx()+m_w ? true : false;
        bool horOverlap = m_pos.rx() + m_w >= x-20 && m_pos.rx() < x + sk_w;
        bool verOverlap = m_pos.ry() + m_h >= y-sk_h && m_pos.ry() + m_h < y + sk_h;

        emit idxOfSkeletonDirection(i, leftToPlayer);

        if(deadSkels.find(i)==deadSkels.end())
        {
        if(horOverlap &&verOverlap )
           {
            //emit playerAttacks(m_plAttacks, i);

            if(!m_plAttacks)
                m_health-=0.2;

            emit idxOfSkeletonAttack(i, m_plAttacks);
            emit sendHealth(m_health);
            return true;
        }
        }

    }

    emit idxOfSkeletonAttack(-1, false);




    return false;

}

bool Player::isRightPressed()
{

    return m_mbuttons.right;

}

bool Player::isLeftPressed()
{
     return m_mbuttons.left;

}

void Player::isAttacking(bool attack)
{

    m_plAttacks=attack;
}

int Player::getHealth() const
{
    return m_health;
}

bool Player::collisionAtPosition(double newX, double newY)
{

    for (int i=0; i<m_objectsData.size(); ++i)
        {
            QJsonObject object = m_objectsData[i].toObject();
            double x = object["x"].toDouble()+m_mapPos.x();
            double y = object["y"].toDouble();
            double w = object["width"].toDouble();
            double h = object["height"].toDouble();


            if ((newX + m_w >= x && newX < x + w) && (newY + m_h >= y && newY < y + h))
            {
                //qDebug() << "coll with obj at" << x << "pl.x"<<m_pos.x()<<" "<<m_w<< '\n';
                return true;
            }
        }
        return false;

}



