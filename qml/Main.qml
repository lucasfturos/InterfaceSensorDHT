import QtQuick 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Window {
    id: root
    width: 560
    height: 300
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
        id: stateTimer
        interval: 1000
        repeat: false
        onTriggered: {
            root.connectionState = "default";
        }
    }

    TabBar {
        id: bar
        width: parent.width
        background: Rectangle {
            color: "#3b3b3b"
        }

        TabButton {
            text: "Serial"
        }

        TabButton {
            text: "Server"
        }

        TabButton {
            text: "Rádio"
        }
    }

    StackLayout {
        width: parent.width
        height: parent.height - bar.height
        currentIndex: bar.currentIndex
        anchors {
            top: bar.bottom
            left: root.left
            right: root.right
            bottom: root.bottom
        }

        Loader {
            source: "view/Serial.qml"
        }

        Loader {
            source: "view/Server.qml"
        }

        Loader {
            source: "view/Radio.qml"
        }
    }
}
