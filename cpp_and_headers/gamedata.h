#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QPoint>
#include <QElapsedTimer>


class GameData : public QObject
{
    Q_OBJECT
public:


    explicit GameData(QObject *parent = nullptr);
    GameData (const QString& path , const QPoint& mapPos, int ww, int wh, int mW, int mH,  QObject *parent=nullptr);


    Q_INVOKABLE int getMapX();
    const QJsonArray& getLayers() const;
    Q_INVOKABLE   QJsonArray getSKeletonPos();
    Q_INVOKABLE   QJsonArray getDeadZonePos();
    double getCurrentTime();






signals:


protected:
    QJsonObject m_mainObject;
    QJsonArray m_layers;
    QJsonArray m_objectsData;
    int m_wndW;
    int m_wndH;
    int m_mapW;
    int m_mapH;
    QPoint m_mapPos;
    QElapsedTimer timer;



};

#endif // GAMEDATA_H
