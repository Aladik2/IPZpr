import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: root
    title: "Вхід"

    // відправка сигналу головному вікну при успіху
    signal loginSuccess(string username)

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 15

        Label { text: "AvtoPoshuk"; font.pixelSize: 28; font.bold: true; Layout.alignment: Qt.AlignHCenter }

        Label { id: statusLabel; color: "red"; Layout.alignment: Qt.AlignHCenter }

        TextField { id: userField; placeholderText: "Логін"; Layout.preferredWidth: 300 }
        TextField { id: passField; placeholderText: "Пароль"; echoMode: TextInput.Password; Layout.preferredWidth: 300 }

        Button {
            text: "Увійти"
            Layout.preferredWidth: 300
            onClicked: {
                    if (DB.login(userField.text, passField.text)) {
                        root.loginSuccess(userField.text) // передача введеного логіну
                    } else {
                        statusLabel.text = "Невірний логін або пароль"
                    }
                }
        }

        Button {
            text: "Зареєструватися"
            Layout.preferredWidth: 300
            onClicked: {
                    if (userField.text === "" || passField.text === "") {
                        statusLabel.text = "Поля не можуть бути порожніми"
                        return
                    }
                    if (DB.registerUser(userField.text, passField.text)) {
                        root.loginSuccess(userField.text) // передача логіну
                    } else {
                        statusLabel.text = "Користувач вже існує"
                    }
                }
        }
    }
}