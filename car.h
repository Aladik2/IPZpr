// car.h
#ifndef CAR_H
#define CAR_H

#include <QString>
#include <QJsonObject>

class Car {
public:
    QString brand;
    QString model;
    int year;
    int mileage;
    double price;
    QString author;
    QString description;

    // Зручний метод для перетворення з JSON (те, що приходить від сервера)
    static Car fromJson(const QJsonObject &json) {
        return {
            json["brand"].toString(),
            json["model"].toString(),
            json["year"].toString().toInt(),
            json["mileage"].toString().toInt(),
            json["price"].toString().toDouble(),
            json["author"].toString(),
            json["description"].toString()
        };
    }
};
#endif