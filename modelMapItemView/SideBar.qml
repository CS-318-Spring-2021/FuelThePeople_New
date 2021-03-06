import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.0 as C2


Row {
    id: containerRow

    property var mapSource
    property real fontSize : 14
    property int edge: Qt.LeftEdge
    property alias expanded: sideBarToggler.checked

    property string locationTitle: "title"
    property string locationWebsite: "website"

    function rightEdge() {
        return (containerRow.edge === Qt.RightEdge);
    }

    layoutDirection: rightEdge() ? Qt.LeftToRight : Qt.RightToLeft
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.right: rightEdge() ? parent.right : undefined
    anchors.left: rightEdge() ? undefined : parent.left





    // This is the arrow to close and open window
    Button {
        id: sideBarToggler
        width: 32
        height: 96
        checkable: (locationTitle!=='title')
        anchors.verticalCenter: parent.verticalCenter

        transform:  Scale {
            origin.x: rightEdge() ? 0 : sideBarToggler.width / 2
            xScale: rightEdge() ? 1 : -1
        }
        // @disable-check M16
        style:  ButtonStyle {
            background: Rectangle {
                color: "transparent"
            }
        }

        property real shear: 0.333
        property real buttonOpacity: 0.5
        property real mirror : rightEdge() ? 1.0 : -1.0
        Rectangle {
            width: 16
            height: 48
            color: "seagreen"
            antialiasing: true
            opacity: sideBarToggler.buttonOpacity
            anchors.top: parent.top
            anchors.left: sideBarToggler.checked ?  parent.left : parent.horizontalCenter
            transform: Matrix4x4 {
                property real d : sideBarToggler.checked ? 1.0 : -1.0
                matrix:    Qt.matrix4x4(1.0,  d * sideBarToggler.shear,    0.0,    0.0,
                                        0.0,    1.0,    0.0,    0.0,
                                        0.0,    0.0,    1.0,    0.0,
                                        0.0,    0.0,    0.0,    1.0)
            }
        }
        Rectangle {
            width: 16
            height: 48
            color: "seagreen"
            antialiasing: true
            opacity: sideBarToggler.buttonOpacity
            anchors.top: parent.verticalCenter
            anchors.right: sideBarToggler.checked ?  parent.right : parent.horizontalCenter
            transform: Matrix4x4 {
                property real d : sideBarToggler.checked ? -1.0 : 1.0
                matrix:    Qt.matrix4x4(1.0,  d * sideBarToggler.shear,    0.0,    0.0,
                                        0.0,    1.0,    0.0,    0.0,
                                        0.0,    0.0,    1.0,    0.0,
                                        0.0,    0.0,    0.0,    1.0)
            }
        }
    }



    Rectangle {
        id: info_container
        height: parent.height
        width: parent.parent.width * 0.3
        radius: 3
        visible: sideBarToggler.checked
        // color: Qt.rgba( 0, 191 / 255.0, 255 / 255.0, 0.07)
        // the above color is if we want slightly transparent, green background
        color: "white"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                expanded = true;
                console.log("sidebar was clicked on")
            }
        }
        Column {
            id: informationColumn
            height: parent.height
            width: parent.width

            Row {
                id: imageRow
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.left: parent.left
                Image {
                    width: parent.parent.width; height: 2/3*parent.parent.width
                    fillMode: Image.PreserveAspectFit
                    verticalAlignment: Image.AlignTop
                    horizontalAlignment: Image.AlignTop
                    source: "http://images.citysearch.net/assets/imgdb2/reinvent/profile/2012/7/27/0/tfKQnpBn.jpg"
                }
            }




            Row {
                id: titleRow
                spacing: 10
                leftPadding: 20
                topPadding: 10
                anchors.left: parent.left
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    id: title
                    font.pointSize: fontSize
                    text: qsTr(locationTitle)
                }
            }


            Row {
                id: descriptionRow
                spacing: 10
                leftPadding: 20
                topPadding: 10
                anchors.left: parent.left
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    id: description
                    font.pointSize: fontSize
                    text: qsTr("Description: ")
                }
            }

            Row {
                id: addressRow
                spacing: 10
                leftPadding: 20
                topPadding: 10
                anchors.left: parent.left
                Image {
                    width: 20; height: 20
                    fillMode: Image.PreserveAspectFit
                    source: "location_icon.png"
                }
                Text {
                    id: address
                    font.pointSize: fontSize
                    text: qsTr("this is the address")
                }
            }

            Row {
                id: websiteRow
                spacing: 10
                leftPadding: 20
                topPadding: 10
                anchors.left: parent.left
                Text {
                    id: website
                    font.pointSize: fontSize
                    text: "To order online, <a href='" + locationWebsite + "'>click here</a>"
                    onLinkActivated: Qt.openUrlExternally(link)
                    MouseArea {
                        anchors.fill: parent
                        acceptedButtons: Qt.NoButton // we don't want to eat clicks on the Text
                        cursorShape: parent.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor
                    }
                }
            }

        }
    }
}
