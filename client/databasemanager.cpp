#include "databasemanager.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include <QDebug>

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent) {
    // створнення менеджера, який буде відправляти наші листи на сервер
    manager = new QNetworkAccessManager(this);
}

// ДОПОМІЖНІ ФУНКЦІЇ ДЛЯ МЕРЕЖІ
QByteArray DatabaseManager::makeSyncPostRequest(const QString& endpoint, const QJsonObject& json) {
    QNetworkRequest request(QUrl(serverUrl + endpoint));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, QJsonDocument(json).toJson(QJsonDocument::Compact));

    // очікуваня відповіді серверу
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QByteArray response = reply->readAll();
    reply->deleteLater();
    return response;
}

QByteArray DatabaseManager::makeSyncGetRequest(const QString& endpoint) {
    QNetworkRequest request(QUrl(serverUrl + endpoint));
    QNetworkReply *reply = manager->get(request);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QByteArray response = reply->readAll();
    reply->deleteLater();
    return response;
}

// БІЗНЕС-ЛОГІКА

bool DatabaseManager::login(QString username, QString password) {
    QJsonObject req;
    req["user"] = username;
    req["pass"] = password;

    QByteArray respStr = makeSyncPostRequest("/login", req);
    QJsonObject respJson = QJsonDocument::fromJson(respStr).object();

    return respJson["status"].toString() == "success";
}

bool DatabaseManager::registerUser(QString username, QString password) {
    QJsonObject req;
    req["user"] = username;
    req["pass"] = password;

    QByteArray respStr = makeSyncPostRequest("/register", req);
    QJsonObject respJson = QJsonDocument::fromJson(respStr).object();

    return respJson["status"].toString() == "success";
}

QVariantList DatabaseManager::getCars() {
    QByteArray respStr = makeSyncGetRequest("/get_cars");
    QJsonObject respJson = QJsonDocument::fromJson(respStr).object();

    // Перетворення JSON від сервера назад у список для QML
    return respJson["data"].toArray().toVariantList();
}

QVariantList DatabaseManager::getUserCars(QString author) {
    QVariantList allCars = getCars();
    QVariantList userCars;

    // фільтрація на стороні клієнта
    for (const QVariant& carVar : allCars) {
        if (carVar.toMap()["author"].toString() == author) {
            userCars.append(carVar);
        }
    }
    return userCars;
}

void DatabaseManager::addCar(QString b, QString m, QString y, QString mi, QString p, QString author, QString description) {
    QJsonObject req;
    req["brand"] = b;
    req["model"] = m;
    req["year"] = y;
    req["mileage"] = mi;
    req["price"] = p;
    req["author"] = author;
    req["description"] = description;

    // Відправка нову машину на сервер
    makeSyncPostRequest("/add_car", req);

    // повідомлення про оновлення даних для qml
    emit carsChanged();
}