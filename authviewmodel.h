#ifndef AUTHVIEWMODEL_H
#define AUTHVIEWMODEL_H

#include <QObject>
#include "databasemanager.h" // Твій старий менеджер, який тепер буде просто сервісом

class AuthViewModel : public QObject {
    Q_OBJECT
    // Властивості, які будуть доступні в QML
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY errorMessageChanged)
    Q_PROPERTY(QString currentUsername READ currentUsername NOTIFY currentUsernameChanged)

public:
    explicit AuthViewModel(DatabaseManager* dbManager, QObject *parent = nullptr);

    QString errorMessage() const;
    QString currentUsername() const;

    // Функції, які QML зможе викликати (кліки по кнопках)
    Q_INVOKABLE void login(const QString& username, const QString& password);
    Q_INVOKABLE void registerUser(const QString& username, const QString& password);
    Q_INVOKABLE void logout();

signals:
    void errorMessageChanged();
    void currentUsernameChanged();
    void loginSuccess(); // Сигнал для QML, що час перемикати екран

private:
    DatabaseManager* m_dbManager;
    QString m_errorMessage;
    QString m_currentUsername;

    void setErrorMessage(const QString& msg);
};

#endif // AUTHVIEWMODEL_H