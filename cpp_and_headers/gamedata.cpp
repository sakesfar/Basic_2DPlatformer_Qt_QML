#include "gamedata.h"

GameData::GameData(QObject *parent)
    : QObject{parent}
{

}

GameData::GameData(const QString &path, int mapW, int mapH, QObject *parent) : m_mapW{GameConstants::mapW}, m_mapH{GameConstants::mapH*2}
{
    m_wndW=GameConstants::wndW;
    m_wndH=GameConstants::wndH;

    m_mapPos= {0,0};

    QFile file {path};
    file.open(QIODevice::ReadOnly);
    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    m_jsonDoc =doc.object();
    m_layers =m_jsonDoc["layers"].toArray();

    //it happens objects are always first element in "layers" array from Tiled app json.
    QJsonObject objects = m_layers.at(0).toObject();
    m_objectsData =objects["objects"].toArray();


    m_timer.start();
}

QHash<QString, QJsonArray> GameData::getEnemies()
{

    QHash<QString, QJsonArray> enemyArrays;

    for (const QJsonValue& layer : m_layers)
    {
        QJsonObject layerObj = layer.toObject();
        QString enemyType = layerObj["name"].toString();

        if( enemyType == "Skeleton" || "Mushroom" || "Goblin" || "Flying Eye")
            enemyArrays[enemyType] = layerObj["objects"].toArray();


    }


    return enemyArrays;
}

QVariantMap GameData::getEnemiesForQML()
{

    QHash<QString, QJsonArray> enemyData = getEnemies();
    QVariantMap resultMap;

     for (auto it = enemyData.constBegin(); it != enemyData.constEnd(); ++it)
     {
         resultMap.insert(it.key(), QVariant::fromValue(it.value()));
     }    


     return resultMap;

}


const QPoint &GameData::mapPos() const
{
    return m_mapPos;
}


bool GameData::lbutton() const
{
    return m_mbuttons.left;
}

bool GameData::rbutton() const
{
    return m_mbuttons.right;
}

void GameData::setRbutton(bool val)
{   
    m_mbuttons.right=val;
    emit rbuttonChanged();
}

void GameData::setLbutton(bool val)
{    
    m_mbuttons.left=val;
    emit lbuttonChanged();
}

double GameData::getCurrentTime()
{
    return m_timer.elapsed() / 1000.0;
}

void GameData::setMapPos(QPoint &pos)
{
    if(m_mapPos!=pos)
    {
        m_mapPos=pos;
        emit mapPosChanged();
    }
}


