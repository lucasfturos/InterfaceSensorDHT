import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

Window {
    id: root
    width: 560
    height: 260
    minimumWidth: root.width
    minimumHeight: root.height
    maximumWidth: root.minimumWidth
    maximumHeight: root.minimumHeight
    visible: true
    color: "#3b3b3b"
    title: qsTr("Busca de Dispositivo")

    Material.theme: Material.Dark
    Material.accent: Material.Grey

    property var homeWindow: null
    property string connectionState: "default"

    Timer {
        id: disconnectTimer
        interval: 2000
        repeat: false
        onTriggered: {
            root.connectionState = "default";
        }
    }

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
                    case "desconnected":
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
                if (!root.homeWindow && searchDevice.connected) {
                    var component = Qt.createComponent("Home.qml")
                    root.homeWindow = component.createObject(root)
                    searchDevice.connectDevice(cbPort.currentText, cbBaud.currentText)
                    root.connectionState = "connected";
                }
                if (!searchDevice.connected) {
                    disconnectTimer.start();
                    root.connectionState = "error";
                }
                root.homeWindow.visible = true
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
                if (root.homeWindow && searchDevice.connected) {
                    root.homeWindow.close()
                    root.homeWindow = null
                    disconnectTimer.start();
                    root.connectionState = "desconnected";
                    searchDevice.disconnectDevice(cbPort.currentText)
                }
                if (!searchDevice.connected) {
                    disconnectTimer.start();
                    root.connectionState = "error";
                }
            }
        }

        Button {
            id: btnWifi
            font.pointSize: 14
            text: qsTr("Via rádio")
            Layout.preferredWidth: 155
            Layout.preferredHeight: 70
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight

            onClicked: {
                if (!root.homeWindow) {
                    var component = Qt.createComponent("Home.qml")
                    root.homeWindow = component.createObject(root)
                }
                root.homeWindow.visible = true
                root.connectionState = "radio";
            }
        }
    }
}
