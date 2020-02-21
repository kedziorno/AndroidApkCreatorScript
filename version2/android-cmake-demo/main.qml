// main.qml
import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Window 2.11

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Label {
        text: qsTr("Android CMake Test")
        anchors.centerIn: parent
    }
}

<!-- qml.qrc -->
<RCC>
    <qresource prefix="/">
        <file>main.qml</file>
    </qresource>
</RCC>

