#include "authviewmodel.h"

AuthViewModel::AuthViewModel(DatabaseManager* dbManager, QObject *parent)
    : QObject(parent), m_dbManager(dbManager) {}

QString AuthViewModel::errorMessage() const { return m_errorMessage; }
QString AuthViewModel::currentUsername() const { return m_currentUsername; }

void AuthViewModel::setErrorMessage(const QString& msg) {
    if (m_errorMessage != msg) {
        m_errorMessage = msg;
        emit errorMessageChanged(); // Повідомляємо QML, що текст помилки змінився
    }
}

void AuthViewModel::login(const QString& username, const QString& password) {
    if (m_dbManager->login(username, password)) {
        m_currentUsername = username;
        emit currentUsernameChanged();
        setErrorMessage(""); // Очищаємо помилки
        emit loginSuccess(); // Даємо команду QML змінити екран
    } else {
        setErrorMessage("Невірний логін або пароль");
    }
}

void AuthViewModel::registerUser(const QString& username, const QString& password) {
    if (username.isEmpty() || password.isEmpty()) {
        setErrorMessage("Поля не можуть бути порожніми");
        return;
    }

    if (m_dbManager->registerUser(username, password)) {
        m_currentUsername = username;
        emit currentUsernameChanged();
        setErrorMessage("");
        emit loginSuccess();
    } else {
        setErrorMessage("Користувач вже існує");
    }
}

void AuthViewModel::logout() {
    m_currentUsername = "";
    emit currentUsernameChanged();
}