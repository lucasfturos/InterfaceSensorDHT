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
            text: qsTr("Rádio")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        Button {
            text: qsTr("Teste")
            Layout.preferredWidth: 155
            Layout.preferredHeight: 70
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }
    }
}
