import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: root
    title: "Нове оголошення"

    property string currentUsername: "" // сюди прийде логін

    signal carAdded()
    signal cancelAdd()

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 10
        width: 300

        Label { text: "Параметри авто"; font.pixelSize: 20; Layout.alignment: Qt.AlignHCenter }

        TextField { id: bField; placeholderText: "Марка (напр. BMW)"; Layout.fillWidth: true }
        TextField { id: mField; placeholderText: "Модель"; Layout.fillWidth: true }
        TextField { id: yField; placeholderText: "Рік випуску"; Layout.fillWidth: true }
        TextField { id: miField; placeholderText: "Пробіг (км)"; Layout.fillWidth: true }
        TextField { id: pField; placeholderText: "Ціна ($)"; Layout.fillWidth: true }

        ScrollView {
            Layout.fillWidth: true
            Layout.preferredHeight: 80
            TextArea {
                id: descField
                placeholderText: "Опис авто (стан, комплектація...)"
                wrapMode: TextArea.Wrap
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Button { text: "Скасувати"; Layout.fillWidth: true; onClicked: root.cancelAdd() }
            Button {
                text: "Зберегти"
                Layout.fillWidth: true
                onClicked: {
                    // Змінюємо DB на CarListVM
                        CarListVM.addCar(bField.text, mField.text, yField.text, miField.text, pField.text, root.currentUsername, descField.text)
                        root.carAdded()
                }
            }
        }
    }
}