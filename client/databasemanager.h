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

    Q_INVOKABLE bool login(QString username, QString password);
    Q_INVOKABLE bool registerUser(QString username, QString password);
    Q_INVOKABLE QVariantList getCars();
    Q_INVOKABLE QVariantList getUserCars(QString author);
    Q_INVOKABLE void addCar(QString b, QString m, QString y, QString mi, QString p, QString author, QString description);

signals:
    void carsChanged();

private:
    QNetworkAccessManager *manager;
    const QString serverUrl = "http://localhost:8080";

    // Спеціальні функції-помічники для відправки запитів
    QByteArray makeSyncPostRequest(const QString& endpoint, const QJsonObject& json);
    QByteArray makeSyncGetRequest(const QString& endpoint);
};

#endif // DATABASEMANAGER_H