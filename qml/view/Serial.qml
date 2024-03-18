import QtQuick 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Item {
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        RowLayout {
            spacing: 20

            Text {
                color: "#fff"
                font.pointSize: 14
                text: qsTr("Status")
                Layout.alignment: Qt.AlignLeft
            }

            Text {
                id: textShowStatus
                color: "#fff"
                font.pointSize: 14
                Layout.alignment: Qt.AlignHCenter
            }

            Rectangle {
                id: circleStatus
                width: 55
                height: circleStatus.width
                radius: 180
                Layout.leftMargin: 28
                Layout.alignment: Qt.AlignVCenter | Qt.AlignRight

                color: {
                    switch (root.connectionState) {
                    case "connected":
                        textShowStatus.text = "Conectado";
                        return "green";
                    case "radio":
                        return "purple"
                    case "disconnected":
                        textShowStatus.text = "Desconectado";
                        return "red";
                    case "error":
                        textShowStatus.text = "Erro de Conexão";
                        return "orange";
                    default:
                        textShowStatus.text = "Aguardando Conexão";
                        return "gray";
                    }
                }
            }
        }

        RowLayout {
            spacing: 10

            Text {
                color: "#fff"
                text: qsTr("Porta")
                font.pointSize: 14
                Layout.alignment: Qt.AlignVCenter
            }

            ComboBox {
                id: cbPort
                font.pointSize: 14
                Layout.alignment: Qt.AlignVCenter
                model: ListModel {
                    id: listPort
                    ListElement {
                        text: "---"
                    }
                }
                Component.onCompleted: {
                    for (var i = 1; i < searchDevice.portList.length; ++i) {
                        listPort.append({ "text": searchDevice.portList[i] });
                    }
                }
            }

            Text {
                color: "#fff"
                font.pointSize: 14
                text: qsTr("Baud")
                Layout.alignment: Qt.AlignVCenter
            }

            ComboBox {
                id: cbBaud
                font.pointSize: 14
                Layout.alignment: Qt.AlignVCenter
                model: ListModel {
                    id: listBaud
                    ListElement {
                        text: "---"
                    }
                }
                Component.onCompleted: {
                    for (var i = 1; i < searchDevice.baudList.length; ++i) {
                        listBaud.append({ "text": searchDevice.baudList[i] });
                    }
                }
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        Layout.leftMargin: 10

        Button {
            id: btnConnect
            text: qsTr("Conectar")
            Layout.preferredWidth: 155
            Layout.preferredHeight: 70
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight

            onClicked: {
                if (cbPort.currentIndex !== 0 && cbBaud.currentIndex !== 0) {
                    if (!root.homeWindow && searchDevice.connectionState !== "connected") {
                        var component = Qt.createComponent("Home.qml")
                        root.homeWindow = component.createObject(root)
                        searchDevice.connectDevice(cbPort.currentText, cbBaud.currentText)
                        root.connectionState = "connected";
                        root.homeWindow.visible = true
                    } else {
                        disconnectTimer.start();
                        root.connectionState = "error";
                    }
                } else  {
                    disconnectTimer.start();
                    root.connectionState = "error";
                }
            }
        }

        Button {
            id: btnDisconnect
            font.pointSize: 14
            text: qsTr("Desconectar")
            Layout.preferredWidth: 155
            Layout.preferredHeight: 70
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight

            onClicked: {
                disconnectTimer.start();

                if (root.homeWindow && searchDevice.connected) {
                    root.homeWindow.close()
                    root.homeWindow = null
                    root.connectionState = "disconnected";
                    searchDevice.disconnectDevice(cbPort.currentText)
                } else {
                    root.connectionState = "error"
                }
            }
        }
    }
}
