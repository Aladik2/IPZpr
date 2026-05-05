#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QJsonObject>
#include <QJsonArray>

class HttpServer : public QObject {
    Q_OBJECT
public:
    explicit HttpServer(QObject *parent = nullptr);

private slots:
    void handleConnection();

private:
    void logToFile(const QString& message);

    void loadDatabase();
    void saveDatabase();

    // обробник конкретних дій (маршрутизатор)
    QByteArray processApiRequest(const QString& path, const QByteArray& body);
    QByteArray createHttpResponse(const QJsonObject& jsonResponse);

    QTcpServer *server;
    QJsonObject database;
};

#endif // HTTPSERVER_H