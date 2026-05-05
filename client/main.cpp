#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext> // Обов'язково додай цей інклюд
#include "databasemanager.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    DatabaseManager dbManager;
    engine.rootContext()->setContextProperty("DB", &dbManager);

    const QUrl url("qrc:/qt/qml/AvtoPoshuk/Main.qml");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); },
                     Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}