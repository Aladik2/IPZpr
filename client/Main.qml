import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 900
    height: 700
    title: "AvtoPoshuk"

    property string sessionUsername: ""

    Component {
            id: loginComp
            LoginPage {
                onLoginSuccess: function(username) {
                    sessionUsername = username
                    stackView.replace(mainListComp)
                }
            }
        }

    StackView {
            id: stackView
            anchors.fill: parent

            initialItem: loginComp
        }

    Component {
            id: mainListComp
            MainListPage {
                        // при додаванні передаємо логін
                        onRequestAddCar: stackView.push(addCarComp, {"currentUsername": sessionUsername})
                        onRequestProfile: stackView.push(accountComp, {"currentUsername": sessionUsername})
                        // при переході в "Мої оголошення" передаємо логін
                        onRequestMyAds: stackView.push(myAdsComp, {"currentUsername": sessionUsername})
                    }
        }

    Component {
            id: accountComp
            AccountPage {
                onBackRequested: stackView.pop()
                onLogoutRequested: {
                    sessionUsername = "" // очищаємо сесію
                    stackView.replace(loginComp)
                }
            }
        }
    Component {
            id: myAdsComp
            MyAdsPage {
                onBackRequested: stackView.pop()
            }
        }
    Component {
            id: addCarComp
            AddCarPage {
                onCarAdded: stackView.pop()
                onCancelAdd: stackView.pop()
            }
        }
}
