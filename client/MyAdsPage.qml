import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: root
    title: "Мої оголошення"

    property string currentUsername: ""

    signal backRequested()

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            Button { text: "← Назад"; onClicked: root.backRequested() }
            Label { text: "Мої оголошення"; Layout.fillWidth: true; horizontalAlignment: Text.AlignHCenter; font.bold: true }
            Item { width: 60 }
        }
    }

    ListView {
        id: myAdsList
        anchors.fill: parent
        anchors.margins: 15
        spacing: 15
        model: DB.getUserCars(root.currentUsername)

        Connections {
                    target: DB
                    function onCarsChanged() {
                        myAdsList.model = DB.getUserCars(root.currentUsername)
                    }
                }

        delegate: ItemDelegate {
            width: ListView.view.width
            contentItem: RowLayout {
                spacing: 15
                Rectangle { width: 80; height: 60; color: "#e0e0e0"; radius: 5 }

                ColumnLayout {
                    Text { text: modelData.brand + " " + modelData.model; font.bold: true; font.pixelSize: 16 }
                    Text { text: "$" + modelData.price + " | " + modelData.year + " р. | " + modelData.mileage + " км"; color: "#2E7D32" }
                    Text {
                        text: modelData.description
                        color: "#555"
                        elide: Text.ElideRight
                        Layout.maximumWidth: 200
                    }
                }
            }
        }
        Label {
            text: "У вас ще немає оголошень"
            anchors.centerIn: parent
            visible: myAdsList.count === 0
            color: "#999"
        }
    }
}