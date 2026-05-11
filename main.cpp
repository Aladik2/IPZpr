#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "databasemanager.h"
#include "authviewmodel.h"
#include "carlistviewmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Ініціалізуємо сервіс та моделі
    DatabaseManager dbManager;
    AuthViewModel authVM(&dbManager);
    CarListViewModel carListVM(&dbManager);

    QQmlApplicationEngine engine;

    // Реєструємо їх у QML
    QQmlContext* context = engine.rootContext();
    context->setContextProperty("AuthVM", &authVM);
    context->setContextProperty("CarListVM", &carListVM);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [](QObject *obj, const QUrl &objUrl) {
                         if (!obj) QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);

    // Правильний спосіб завантаження для Qt 6: вказуємо URI модуля та початковий файл
    engine.loadFromModule("AvtoPoshuk", "Main");

    return app.exec();
}