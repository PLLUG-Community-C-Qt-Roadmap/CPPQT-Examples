import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3

Item {
    width: 640
    height: 480
    property alias detailsView: detailsView

    ListView {
        id: detailsView
        width: 644
        anchors.fill: parent
    }
}
