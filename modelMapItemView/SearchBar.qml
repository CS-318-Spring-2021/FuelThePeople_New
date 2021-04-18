import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

ToolBar {

    signal goLocation(string location)

    RowLayout {
        id: searchBar
        width: parent.width
        height: parent.height

        TextField {
            id: searchText
            placeholderText: qsTr("Type place...")
            onAccepted: goLocation(searchText.text)

        }
    }
}