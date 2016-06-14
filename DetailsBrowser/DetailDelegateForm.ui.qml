import QtQuick 2.4

Item {
    width: 400
    height: 100
    property alias modelValue: modelValueText.text
    property alias typeText: typeValueText.text

    Row {
        id: row1
        property string alias: "none.none"
        anchors.fill: parent

        Column {
            id: column1
            width: 200
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            anchors.topMargin: 0

            Text {
                id: typeLabelText
                width: 50
                height: 14
                text: qsTr("Type:")
                font.bold: true
            }

            Text {
                id: modelLabelText
                width: 50
                height: 14
                text: qsTr("Model:")
                font.bold: true
            }
        }

        Column {
            id: column2
            width: 200
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            anchors.topMargin: 0

            Text {
                id: typeValueText
                font.pixelSize: 12
            }

            Text {
                id: modelValueText
                text: qsTr("Text")
                font.pixelSize: 12
            }
        }
    }
}
