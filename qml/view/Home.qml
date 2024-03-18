import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

Window {
    id: home
    width: 860
    height: 640
    minimumWidth: 610
    minimumHeight: 640
    visible: false
    color: "#3b3b3b"
    title: qsTr("Sensor de Umidade e Temperatura")

    Material.theme: Material.Dark
    Material.accent: Material.Grey

    GridLayout {
        anchors.fill: parent
        anchors.margins: 10

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            GridLayout {
                anchors.fill: parent
                rows: 2
                columns: 2
                rowSpacing: 10
                columnSpacing: 10

                Rectangle {
                    id: rectTemp
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    width: 300

                    color: "#222222"
                    radius: 10

                    GridLayout {
                        anchors.fill: parent
                        rows: 3
                        columns: 1

                        Text {
                            id: textNumTemp
                            color: "#636363"
                            font.pointSize: 72
                            text: sensor.temperature.toFixed(2)
                            Layout.row: 1
                            Layout.alignment: Qt.AlignLeft
                        }
                        Text {
                            text: qsTr("ºC")
                            color: "#636363"
                            font.pointSize: 72
                            Layout.row: 2
                            Layout.alignment: Qt.AlignHCenter
                        }
                        Text {
                            text: qsTr("Temperatura")
                            color: "#636363"
                            font.pointSize: 40
                            Layout.row: 3
                            Layout.alignment: Qt.AlignLeft
                        }
                        anchors.leftMargin: 10
                        anchors.topMargin: -10
                        anchors.bottomMargin: 10
                    }
                }

                Rectangle {
                    id: rectConfig
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.rowSpan: 2
                    width: 60
                    color: "#222222"
                    radius: 10
                }

                Rectangle {
                    id: rectUmi
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    width: 300
                    color: "#222222"
                    radius: 10

                    GridLayout {
                        anchors.fill: parent
                        rows: 3
                        columns: 1

                        Text {
                            id: textNumHum
                            color: "#636363"
                            font.pointSize: 72
                            text: sensor.humidity.toFixed(2)
                            Layout.row: 1
                            Layout.alignment: Qt.AlignLeft
                        }
                        Text {
                            text: qsTr("% rH")
                            color: "#636363"
                            font.pointSize: 72
                            Layout.row: 2
                            Layout.alignment: Qt.AlignHCenter
                        }
                        Text {
                            text: qsTr("Umidade Relativa")
                            color: "#636363"
                            font.pointSize: 40
                            Layout.row: 3
                            Layout.alignment: Qt.AlignLeft
                        }
                        anchors.leftMargin: 10
                        anchors.topMargin: -10
                        anchors.bottomMargin: 10
                    }
                }
            }
        }
    }
}
