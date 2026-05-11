#ifndef CARLISTVIEWMODEL_H
#define CARLISTVIEWMODEL_H

#include <QObject>
#include <QVariantList>
#include "databasemanager.h"

class CarListViewModel : public QObject {
    Q_OBJECT
    // Властивості списків авто, до яких буде прив'язуватися QML
    Q_PROPERTY(QVariantList allCars READ allCars NOTIFY allCarsChanged)
    Q_PROPERTY(QVariantList userCars READ userCars NOTIFY userCarsChanged)

public:
    explicit CarListViewModel(DatabaseManager* dbManager, QObject *parent = nullptr);

    QVariantList allCars() const;
    QVariantList userCars() const;

    // Методи для QML
    Q_INVOKABLE void fetchAllCars();
    Q_INVOKABLE void fetchUserCars(const QString& author);
    Q_INVOKABLE void addCar(const QString& b, const QString& m, const QString& y,
                            const QString& mi, const QString& p,
                            const QString& author, const QString& desc);

signals:
    void allCarsChanged();
    void userCarsChanged();
    void carAddedSuccess();

private:
    DatabaseManager* m_dbManager;
    QVariantList m_allCars;
    QVariantList m_userCars;
};

#endif // CARLISTVIEWMODEL_H