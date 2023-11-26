#ifndef PLAYER_H
#define PLAYER_H


#include <math.h>
#include "gamedata.h"
#include <set>

class Player :public GameData
{
    struct MouseButtons{
        bool right=false;
        bool left=false;
    };

 Q_OBJECT

public:
    Player(const QString& path , const QPoint& mapPos, int ww, int wh, int mW, int mH, const QPoint& pos, int w, int h, int xsp, int ysp,QObject *parent =nullptr);

    Q_INVOKABLE int getPosX() const;
    Q_INVOKABLE int getPosY() const;
    Q_INVOKABLE void moveRight() ;
    Q_INVOKABLE void moveLeft();
    Q_INVOKABLE void jump() ;
    int collistionVertical();
    Q_INVOKABLE void applyGravity();
    Q_INVOKABLE void setRButton(bool val);
    Q_INVOKABLE void setLButton(bool val);
    Q_INVOKABLE bool playerMovingRight();
    Q_INVOKABLE bool playerMovingLeft();
    Q_INVOKABLE bool collisionWithSkeleton(int idx);
    Q_INVOKABLE bool isRightPressed();
    Q_INVOKABLE bool isLeftPressed();
    Q_INVOKABLE void isAttacking(bool attack);
    Q_INVOKABLE int getHealth() const;

    bool collisionAtPosition(double newX, double newY);


signals:

    void posXChanged() ;
    void posYChanged() ;
    int idxOfSkeletonAttack(int ios, bool attacked);
    int idxOfSkeletonDirection(int ios, bool dir);
    int sendHealth(double health);
    int playerAttacks(bool attack, int ios);



private:
    QPoint m_pos;
    int m_w;
    int m_h;
    int m_xspeed;
    int m_yspeed;
    int m_gravity=3;
    MouseButtons m_mbuttons;
    bool m_isjumping{false};
    bool m_isOnPlatform{false};
    double m_health=300;
    bool m_plAttacks=false;


};

#endif // PLAYER_H
