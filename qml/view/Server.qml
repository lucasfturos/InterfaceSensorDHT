import QtQuick 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Item {
    ColumnLayout {
        spacing: 20
        anchors.margins: 10
        anchors.fill: parent

        Text {
            color: "#fff"
            font.pointSize: 16
            text: qsTr("Server HTTP")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        Text {
            color: "#fff"
            font.pointSize: 14
            text: qsTr("Inicie o serviço antes de entrar!")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        Button {
            id: btnEntrar
            text: qsTr("Entrar")
            enabled: sensor.isConnectedServer
            Layout.preferredWidth: 155
            Layout.preferredHeight: 70
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            onClicked: {
                var component = Qt.createComponent("qrc:/qml/Home.qml")
                root.homeWindow = component.createObject(root)
                root.homeWindow.visible = true
            }
        }
    }
}
