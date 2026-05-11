import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: root
    title: "Вхід"

    signal loginSuccess(string username)

    // З'єднуємо сигнал успішного входу з ViewModel із сигналом сторінки
    Connections {
        target: AuthVM
        function onLoginSuccess() {
            root.loginSuccess(AuthVM.currentUsername)
        }
    }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 15

        Label {
            text: "AvtoPoshuk"
            font.pixelSize: 28; font.bold: true
            Layout.alignment: Qt.AlignHCenter
        }

        // Тепер текст помилки автоматично підтягується з ViewModel
        Label {
            id: statusLabel
            text: AuthVM.errorMessage
            color: "red"
            visible: text !== ""
            Layout.alignment: Qt.AlignHCenter
        }

        TextField {
            id: userField
            placeholderText: "Логін"
            Layout.preferredWidth: 300
        }

        TextField {
            id: passField
            placeholderText: "Пароль"
            echoMode: TextInput.Password
            Layout.preferredWidth: 300
        }

        Button {
            text: "Увійти"
            Layout.preferredWidth: 300
            onClicked: {
                // Викликаємо метод ViewModel замість прямого звернення до БД
                AuthVM.login(userField.text, passField.text)
            }
        }

        Button {
            text: "Зареєструватися"
            Layout.preferredWidth: 300
            onClicked: {
                AuthVM.registerUser(userField.text, passField.text)
            }
        }
    }
}