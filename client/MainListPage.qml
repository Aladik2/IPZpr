import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: root
    title: "Всі оголошення"

    signal requestAddCar()
    signal requestProfile()
    signal requestMyAds()

    header: ToolBar {
        RowLayout {
            anchors.fill: parent

            Button { text: "👤"; flat: true; onClicked: root.requestProfile() }
            Button { text: "📋 Мої"; flat: true; onClicked: root.requestMyAds() }

            Label {
                            text: "Каталог авто";
                            Layout.fillWidth: true;
                            horizontalAlignment: Text.AlignHCenter;
                            font.bold: true; font.pixelSize: 18
                        }

            Button {
                text: "+ Додати";
                onClicked: root.requestAddCar()
            }
        }
    }

    ListView {
        id: carList
        anchors.fill: parent
        anchors.margins: 15
        spacing: 15
        model: DB.getCars()

        Connections {
                    target: DB
                    function onCarsChanged() {
                        carList.model = DB.getCars()
                    }
                }

        delegate: ItemDelegate {
            width: ListView.view.width
            contentItem: RowLayout {
                spacing: 15
                // місце під фото (заглушка)
                Rectangle {
                    width: 100; height: 75; color: "#e0e0e0"; radius: 8
                    Text { text: "Фото"; anchors.centerIn: parent; color: "#777" }
                }
                // інформація
                ColumnLayout {
                    Text { text: modelData.brand + " " + modelData.model; font.bold: true; font.pixelSize: 18 }
                    Text { text: modelData.year + " р. | " + modelData.mileage + " км"; color: "#555" }
                }
                Text {
                    text: modelData.description
                    color: "#555"
                    elide: Text.ElideRight
                    Layout.maximumWidth: 200
                }
                Item { Layout.fillWidth: true }
                Text { text: "$" + modelData.price; color: "#2E7D32"; font.bold: true; font.pixelSize: 20 }
            }
        }
    }
}