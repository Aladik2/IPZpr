#include "httpserver.h"
#include <QTcpSocket>
#include <QFile>
#include <QDateTime>
#include <QJsonDocument>
#include <QStringList>
#include <QDebug>

HttpServer::HttpServer(QObject *parent) : QObject(parent) {
    loadDatabase();

    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &HttpServer::handleConnection);

    if (server->listen(QHostAddress::Any, 8080)) {
        qDebug() << "=== Сервер AvtoPoshuk API ЗАПУЩЕНО ===";
        qDebug() << "Порт: 8080. Чекаємо на запити...";
    }
}

void HttpServer::handleConnection() {
    QTcpSocket *socket = server->nextPendingConnection();

    connect(socket, &QTcpSocket::readyRead, this, [this, socket]() {
        QByteArray requestData = socket->readAll();
        QString requestStr = QString::fromUtf8(requestData);

        // 1. Парсинг HTTP запиту (пошук роздільника між заголовками і тілом)
        int bodyStartIndex = requestData.indexOf("\r\n\r\n");
        QByteArray body = "";
        if (bodyStartIndex != -1) {
            body = requestData.mid(bodyStartIndex + 4); // отримання JSON тіло
        }

        // 2. отримання першої лінії (наприклад: "POST /login HTTP/1.1")
        QString firstLine = requestStr.section("\r\n", 0, 0);
        QStringList parts = firstLine.split(" ");
        QString path = parts.length() > 1 ? parts[1] : "/";

        qDebug() << "[ЗАПИТ]:" << firstLine;
        logToFile("Отримано запит: " + firstLine + "\nТіло: " + QString::fromUtf8(body));

        // 3. передача шляху і тіла в маршрутизатор
        QByteArray responseData = processApiRequest(path, body);

        // 4. відправка відповідь клієнту
        socket->write(responseData);
        socket->disconnectFromHost();
    });

    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
}

// МАРШРУТИЗАТОР ТА БІЗНЕС-ЛОГІКА
QByteArray HttpServer::processApiRequest(const QString& path, const QByteArray& body) {
    QJsonObject response;

    if (path == "/get_cars") {
        response["status"] = "success";
        response["data"] = database["cars"];
    }
    else if (path == "/login") {
        QJsonObject req = QJsonDocument::fromJson(body).object();
        QString user = req["user"].toString();
        QString pass = req["pass"].toString();

        QJsonObject users = database["users"].toObject();
        if (users.contains(user) && users[user].toString() == pass) {
            response["status"] = "success";
        } else {
            response["status"] = "error";
            response["message"] = "Невірний логін або пароль";
        }
    }
    else if (path == "/register") {
        // ДЕСЕРІАЛІЗАЦІЯ JSON
        QJsonObject req = QJsonDocument::fromJson(body).object();
        QString user = req["user"].toString();
        QString pass = req["pass"].toString();
        QJsonObject users = database["users"].toObject();

        // ВАЛІДАЦІЯ: перевірка на порожній логін і чи немає дублікатів
        if (user.isEmpty() || users.contains(user)) {
            response["status"] = "error";
            response["message"] = "Користувач вже існує або логін порожній";
        } else {
            users[user] = pass; // +юзер
            database["users"] = users;
            saveDatabase();
            response["status"] = "success";
        }
    }
    else if (path == "/add_car") {
        QJsonObject req = QJsonDocument::fromJson(body).object();

        // ВАЛІДАЦІЯ: не даємо додати машину без марки
        if (req["brand"].toString().isEmpty()) {
            response["status"] = "error";
            response["message"] = "Помилка валідації: Марка авто обов'язкова!";
        } else {
            QJsonArray cars = database["cars"].toArray();
            cars.append(req); // + нове авто
            database["cars"] = cars;
            saveDatabase();
            response["status"] = "success";
        }
    }
    else {
        response["status"] = "error";
        response["message"] = "Невідомий маршрут";
    }

    return createHttpResponse(response); // СЕРІАЛІЗАЦІЯ назад у текст
}

// ФОРМУВАННЯ ПРАВИЛЬНОЇ HTTP ВІДПОВІДІ
QByteArray HttpServer::createHttpResponse(const QJsonObject& jsonResponse) {
    QByteArray jsonBody = QJsonDocument(jsonResponse).toJson(QJsonDocument::Compact);
    QByteArray header = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: application/json; charset=utf-8\r\n"
                        "Connection: close\r\n\r\n";
    return header + jsonBody;
}

// РОБОТА З БАЗОЮ ДАНИХ (ЛОКАЛЬНИЙ ФАЙЛ СЕРВЕРА)
void HttpServer::loadDatabase() {
    QFile file("server_db.json");
    if (file.open(QIODevice::ReadOnly)) {
        database = QJsonDocument::fromJson(file.readAll()).object();
        file.close();
    } else {
        // якщо файлу ще немає, створюємо порожню структуру
        database["users"] = QJsonObject();
        database["cars"] = QJsonArray();
    }
}

void HttpServer::saveDatabase() {
    QFile file("server_db.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(database).toJson());
        file.close();
    }
}

void HttpServer::logToFile(const QString& message) {
    QFile file("server.log");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << "] " << message << "\n";
        file.close();
    }
}