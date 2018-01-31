import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    id: window
    visible: true
    width: 640
    height: 480
    color: "#171717"
    title: qsTr("Hello Android")

    Text {
        id: motd
        color: "#ffffff"
        text: qsTr("Hello Android!")
        anchors.fill: parent
        style: Text.Sunken
        font.pixelSize: 35
        styleColor: "#9e24ff"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

    }


    Connections {
        target: window
        onClicked: changeMessage()
    }
}
