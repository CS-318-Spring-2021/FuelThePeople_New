import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.0 as C2

Row {
    id: containerRow

    property var mapSource
    property real fontSize : 14
    property color labelBackground : "transparent"
    property int edge: Qt.RightEdge
    property alias expanded: sliderToggler.checked

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
        id: sliderToggler
        width: 32
        height: 96
        checkable: true
        checked: true
        anchors.verticalCenter: parent.verticalCenter

        transform:  Scale {
            origin.x: rightEdge() ? 0 : sliderToggler.width / 2
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
            opacity: sliderToggler.buttonOpacity
            anchors.top: parent.top
            anchors.left: sliderToggler.checked ?  parent.left : parent.horizontalCenter
            transform: Matrix4x4 {
                property real d : sliderToggler.checked ? 1.0 : -1.0
                matrix:    Qt.matrix4x4(1.0,  d * sliderToggler.shear,    0.0,    0.0,
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
            opacity: sliderToggler.buttonOpacity
            anchors.top: parent.verticalCenter
            anchors.right: sliderToggler.checked ?  parent.right : parent.horizontalCenter
            transform: Matrix4x4 {
                property real d : sliderToggler.checked ? -1.0 : 1.0
                matrix:    Qt.matrix4x4(1.0,  d * sliderToggler.shear,    0.0,    0.0,
                                        0.0,    1.0,    0.0,    0.0,
                                        0.0,    0.0,    1.0,    0.0,
                                        0.0,    0.0,    0.0,    1.0)
            }
        }
    }




    // These are the labels for each slider
    Rectangle {
        id: info_container
        height: parent.height
//        width: sliderRow.width + 100
//        eventually we will want to scale the width to what it is containing
        width: 200
        visible: sliderToggler.checked
        // color: Qt.rgba( 0, 191 / 255.0, 255 / 255.0, 0.07)
        // the above color is if we want slightly transparent, green background
        color: "white"

        property var labelBorderColor: "transparent"
        property var slidersHeight : sliderContainer.height
                                     - rowSliderValues.height
                                     - rowSliderLabels.height
                                     - sliderColumn.spacing * 2
                                     - sliderColumn.topPadding
                                     - sliderColumn.bottomPadding
        Column {
            id: textColumn
            spacing: 10
            topPadding: 16
            bottomPadding: 48
            anchors.centerIn: parents
            Text {
                id: random_text
                text: qsTr("This is random text")
            }
        }
    }
} // overall containerRow

