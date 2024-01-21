#ifndef PLAYER_H
#define PLAYER_H

#include <gamedata.h>

class Player : public GameData
{
    Q_OBJECT

    Q_PROPERTY(QPoint pos READ pos WRITE setPos NOTIFY posChanged)
    Q_PROPERTY(bool isJumping READ isJumping WRITE setIsJumping NOTIFY isJumpingChanged)
    Q_PROPERTY(bool isOnRope READ isOnRope WRITE setIsOnRope NOTIFY isOnRopeChanged)



public:  
    Player();
    const QPoint& pos() const;
    bool isOnRope() const;
    bool isJumping() const;
    bool collisionAtPos(double newX, double newY);
    Q_INVOKABLE void moveRight();
    Q_INVOKABLE void moveLeft();
    Q_INVOKABLE void jump();
    Q_INVOKABLE void crawlUp();
    Q_INVOKABLE void crawlDown();
    Q_INVOKABLE void adjustY(int yShift);
    int collisionVertical();
    Q_INVOKABLE void collisionVertRope();
    Q_INVOKABLE void applyGravity();
    Q_INVOKABLE void applyGravityOnRope();


public slots:
    void setPos(const QPoint& pos);
    void setIsJumping(bool val);
    void setIsOnRope (bool val);

private:
    QPoint m_pos;
    int m_w;
    int m_h;
    int m_xspeed;
    int m_yspeed;
    int m_gravity;
    bool m_isjumping;
    bool m_isOnPlatform;
    double m_health;
    bool m_plAttacks;
    bool m_isOnRope;


signals:
    void posChanged();
    void isJumpingChanged();
    void isOnRopeChanged();

};

#endif // PLAYER_H
