#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QQmlContext>

#include "player.h"

#include <string>



int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    const QString path {"C:/Users/User/source/repos/cpptest/theMap3.tmj"};
    Player player {path, {0,0}, 640,368 , 640*3, 368, {10,320}, 15,28,3,0 };
    QJsonArray tiles{};

    for(int i=0;i<player.getLayers().size();++i)
    {
        QJsonObject inLayerTile = player.getLayers().at(i).toObject();
        QString search = "Foreground";
        QString str = inLayerTile["name"].toString();


        if (str.contains(search))
            tiles.push_back(inLayerTile);
    }




    engine.rootContext()->setContextProperty("tilesData", tiles);
    engine.rootContext()->setContextProperty("Woo", &player);



    return app.exec();
}
