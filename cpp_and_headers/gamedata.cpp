#include "gamedata.h"

GameData::GameData(QObject *parent)
    : QObject{parent}
{



}

GameData::GameData(const QString& path , const QPoint& mapPos, int ww, int wh,int mW, int mH, QObject *parent) : m_mapPos{mapPos},
    m_wndW{ww}, m_wndH{wh}, m_mapW{mW}, m_mapH{mH}
{
    QFile file {path};
    file.open(QIODevice::ReadOnly);
    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    m_mainObject =doc.object();
    m_layers =m_mainObject["layers"].toArray();
    QJsonObject objects = m_layers.at(0).toObject();
    m_objectsData =objects["objects"].toArray();

    timer.start();
}

int GameData::getMapX()
{

    return m_mapPos.rx();

}

const QJsonArray &GameData::getLayers() const
{
    return m_layers;
}

  QJsonArray GameData::getSKeletonPos()
{

     QJsonObject&& tempObj{};

    for (int i =0 ; i<m_layers.size();++i)
    {

         tempObj = m_layers[i].toObject();
        if(tempObj["name"]=="Skeleton")
            break;
    }



   QJsonArray&& arrOfSkel = !tempObj["objects"].isNull() ? tempObj["objects"].toArray() : QJsonArray{};



   return arrOfSkel;


  }

  QJsonArray GameData::getDeadZonePos()
  {
      QJsonObject&& tempObj{};

     for (int i =0 ; i<m_layers.size();++i)
     {

          tempObj = m_layers[i].toObject();
         if(tempObj["name"]=="DeadZone")
             break;
     }



    QJsonArray&& arrOfDeadZone = !tempObj["objects"].isNull() ? tempObj["objects"].toArray() : QJsonArray{};



    return arrOfDeadZone;

  }

double GameData::getCurrentTime()
{
    return timer.elapsed() / 1000.0;

}


