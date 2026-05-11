#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QVariantList>
#include <QVariantMap>
#include <QNetworkAccessManager>

class DatabaseManager : public QObject {
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);

    bool login(QString username, QString password);
    bool registerUser(QString username, QString password);
    QVariantList getCars();
    QVariantList getUserCars(QString author);
    void addCar(QString b, QString m, QString y, QString mi, QString p, QString author, QString description);

private:
    QNetworkAccessManager *manager;
    const QString serverUrl = "http://localhost:8080";

    // Спеціальні функції-помічники для відправки запитів
    QByteArray makeSyncPostRequest(const QString& endpoint, const QJsonObject& json);
    QByteArray makeSyncGetRequest(const QString& endpoint);
};

#endif // DATABASEMANAGER_H