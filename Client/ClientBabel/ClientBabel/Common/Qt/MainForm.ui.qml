import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

Item {
    width: 640
    height: 480

    Rectangle {
        id: rectangle1
        x: 8
        y: 8
        width: 307
        height: 464
        color: "#ffffff"
    }

    Rectangle {
        id: rectangle2
        x: 321
        y: 8
        width: 311
        height: 232
        color: "#ffffff"

        TextInput {
            id: textInput1
            x: 8
            y: 8
            width: 173
            height: 20
            text: qsTr("Enter here new nick name")
            font.pixelSize: 12
        }

        Button {
            id: button1
            x: 187
            y: 8
            text: qsTr("Change nickname")
        }

        TextInput {
            id: textInput2
            x: 79
            y: 95
            width: 80
            height: 20
            text: qsTr("Text Input")
            font.pixelSize: 12
        }

        TextEdit {
            id: textEdit1
            x: 101
            y: 134
            width: 80
            height: 20
            text: qsTr("Text Edit")
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: rectangle3
        x: 321
        y: 248
        width: 311
        height: 224
        color: "#ffffff"

        Text {
            id: text1
            x: 8
            y: 8
            width: 295
            height: 208
            text: qsTr("Server info")
            font.pixelSize: 12
        }
    }

}
