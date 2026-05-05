import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: root
    title: "Менеджмент акаунту"

    property string currentUsername: "Невідомо"
    signal logoutRequested()
    signal backRequested()

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            Button { text: "← Назад"; onClicked: root.backRequested() }
            Label { text: "Мій профіль"; Layout.fillWidth: true; horizontalAlignment: Text.AlignHCenter }
            Item { width: 40 } // порожня розпірка для симетрії
        }
    }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 20

        // Іконка або аватар
        Rectangle {
            width: 100; height: 100
            color: "#eeeeee"; radius: 50
            Layout.alignment: Qt.AlignHCenter
            Text { text: "👤"; font.pixelSize: 50; anchors.centerIn: parent }
        }

        Label {
            text: "Ви увійшли як:"
            font.pixelSize: 14; color: "#777"
            Layout.alignment: Qt.AlignHCenter
        }

        Label {
            text: root.currentUsername // Тепер тут змінна!
            font.pixelSize: 22; font.bold: true
            Layout.alignment: Qt.AlignHCenter
        }

        Button {
            text: "Вийти з акаунту"
            highlighted: true
            palette.button: "red"
            Layout.preferredWidth: 200
            onClicked: root.logoutRequested()
        }
    }
}