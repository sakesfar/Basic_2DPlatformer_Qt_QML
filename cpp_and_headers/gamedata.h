#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <QObject>
#include <QPoint>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QElapsedTimer>
#include <algorithm>
#include <QHash>

namespace GameConstants
{

 constexpr int wndW =640;
 constexpr int wndH=368;
 inline const  QString path {"C:/Users/User/source/repos/cpptest/theMap3.tmj"};

 constexpr int mapW=1920;
 constexpr int mapH=368;

 constexpr int playerW=64; //64
 constexpr int playerH=44;//was 44


 constexpr int mapGround = 288 ;// OR 332-playerH

 constexpr double VERTICAL_TOLERANCE = 10.0;
 constexpr double GRACE_PERIOD = 0.01;

 //the following are for sprite frame's offsets
 constexpr int xoffsetRight=29;
 constexpr int xoffsetLeft =16;
 constexpr int xoffseLeftCrawl=23;
 constexpr int yoffset=9;
 constexpr int yoffsetForVertColl=2;




}

class GameData : public QObject
{
    Q_OBJECT
    struct KeyButtons{
        bool right;
        bool left;
    };
protected:
    Q_PROPERTY(QPoint mapPos READ mapPos WRITE setMapPos NOTIFY mapPosChanged);
    Q_PROPERTY(bool lbutton READ lbutton WRITE setLbutton NOTIFY lbuttonChanged);
    Q_PROPERTY(bool rbutton READ rbutton WRITE setRbutton NOTIFY rbuttonChanged);

public:
    explicit GameData(QObject *parent = nullptr);
    GameData (const QString& path, int mapW, int mapH, QObject *parent=nullptr);

    QHash<QString, QJsonArray> getEnemies();
    Q_INVOKABLE QVariantMap  getEnemiesForQML();

    const QPoint& mapPos() const;
    const KeyButtons& mbuttons() const;
    bool lbutton() const;
    bool rbutton() const;
    double getCurrentTime();

public slots:
    void setMapPos(QPoint& pos);
    void setRbutton(bool val);
    void setLbutton(bool val);



signals:
    void mapPosChanged();
    void lbuttonChanged();
    void rbuttonChanged();




protected:
    QJsonObject m_jsonDoc;
    QJsonArray m_layers;
    QJsonArray m_objectsData;
    int m_wndW;
    int m_wndH;
    int m_mapW;
    int m_mapH;
    QPoint m_mapPos;
    QElapsedTimer m_timer;
    KeyButtons m_mbuttons;

};

#endif // GAMEDATA_H
