#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "player.h"



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

    qmlRegisterType<Player> ("WarGirlImport", 1,0, "MainCharachter");
    //const QString path {"C:/Users/User/source/repos/cpptest/theMap3.tmj"};
    //Player* player = new Player {path,10,10, 20,20};





    engine.load(url);




    return app.exec();
}
