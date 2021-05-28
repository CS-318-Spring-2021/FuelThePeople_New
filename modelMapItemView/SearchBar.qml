import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

ToolBar {
    signal goLocation(string location)
    anchors.right: parent.right
    RowLayout {
        id: searchBar
        width: parent.width
        height: parent.height

        TextField {
            id: searchText
            placeholderText: qsTr("Type place...")
            onAccepted: goLocation(searchText.text)
            background: Rectangle {
                        implicitWidth: 200
                        implicitHeight: 40
                        border.color: "#26282a"
                        border.width: 1
                        radius: 4
                        opacity: 0.75
                    }

        }
    }
}
