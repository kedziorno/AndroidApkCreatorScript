// main.qml
import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Window 2.11

Window {
    visible: true
    width: 320
    height: 240
    title: qsTr("Hello World")

    Label {
        text: qsTr("Android CMake Test")
        anchors.centerIn: parent
    }
}

