#include "carlistviewmodel.h"

CarListViewModel::CarListViewModel(DatabaseManager* dbManager, QObject *parent)
    : QObject(parent), m_dbManager(dbManager) {}

QVariantList CarListViewModel::allCars() const { return m_allCars; }
QVariantList CarListViewModel::userCars() const { return m_userCars; }

void CarListViewModel::fetchAllCars() {
    m_allCars = m_dbManager->getCars();
    emit allCarsChanged();
}

void CarListViewModel::fetchUserCars(const QString& author) {
    m_userCars = m_dbManager->getUserCars(author);
    emit userCarsChanged();
}

void CarListViewModel::addCar(const QString& b, const QString& m, const QString& y,
                              const QString& mi, const QString& p,
                              const QString& author, const QString& desc) {

    m_dbManager->addCar(b, m, y, mi, p, author, desc);
    emit carAddedSuccess();

    // Оновлюємо локальні списки після додавання
    fetchAllCars();
    fetchUserCars(author);
}