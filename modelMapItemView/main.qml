import QtQuick 2.4
import QtPositioning 5.14
import QtLocation 5.14
import QtQuick.Window 2.2
import QtQuick.Controls 2.15 // or import Qt.labs.controls 1.0
import QtQuick.Controls.Styles 1.4

Map{
    id: map_map
    anchors.centerIn: parent;
    anchors.fill: parent
    plugin: Plugin {
        name: "mapboxgl" // "osm", "esri", ...
        PluginParameter {name: "mapboxgl.access_token"; value: 'pk.eyJ1IjoiYWxhbmRhdXgiLCJhIjoiY2trNGVnenhiMHJsaTJwcXh1a3Y0N2piNyJ9.AanJ6dhSwkSJW3-Ae_Gdzw'}
    }
    center: QtPositioning.coordinate(40.66062, -73.95043)
    zoomLevel: 8

    function changeLocation(text) {
        geocodeModel.query = text
        geocodeModel.update()
    }

    //this mouse area allows users to click on map outside of circles to exit sideBar
    MouseArea {
        anchors.fill: parent
        onClicked: {
            info_bar.expanded = false;
        }
    }

    Rectangle {
        id: zoomSliderLabelRect;
        implicitWidth: 60
        implicitHeight: 25
        border.color: "#26282a"
        border.width: 1
        opacity: 0.75
        radius: 4
        anchors.margins: 10
        anchors.bottomMargin: zoomSlider.height + 16
        anchors.bottom: parent.bottom
        anchors.top: scale.top
        anchors.right: parent.right
        Label {
            id: zoomSliderLabel;
            text: "Zoom";
            font.pixelSize: 14;
            anchors.fill: parent
            horizontalAlignment: Label.AlignHCenter
            verticalAlignment: Label.AlignVCenter
        }
   }

    Slider {
        id: zoomSlider;
        z: map_map.z + 3
        to: map_map.maximumZoomLevel;
        from: map_map.minimumZoomLevel;
        anchors.margins: 18
        anchors.bottom: parent.bottom
        anchors.top: scale.top
        anchors.right: parent.right
        orientation : Qt.Vertical
        value: map_map.zoomLevel
        onValueChanged: {
            map_map.zoomLevel = value
        }
    }

    MapItemView {
        model: bakery_model
        id: bakeryModel
        delegate:  MapQuickItem {
            id: test_map_point

            sourceItem: Rectangle {
                width: 14; height: 14;
                color: {
                    if (model.amenity === "Bakery") return "green";
                    else if (model.amenity === "Restaurant") return "red";
                    else return "blue"
                }
                border.width: 2;
                border.color: "white";
                smooth: true;
                radius: 7;

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: { parent.color = 'purple' }
                    onExited: {parent.color = model.color }
                    onClicked: {
                        info_bar.locationTitle = model.name
                        info_bar.locationWebsite = model.website
                        info_bar.expanded = true
                    }

                }
            }
            coordinate: {
//                if(model.amenity === "Bakery")
                    model.coordinate
            }
            opacity: 1.0
            anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)

        }
    }

    MapItemView {
        model: allPoint_model
        delegate:  MapQuickItem {
            id: allPoint
            sourceItem: Rectangle { width: 14; height: 14; color: model.color; border.width: 2; border.color: "white"; smooth: true; radius: 7;
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: { parent.color = 'purple' }
                    onExited: {parent.color = model.color }
                    onClicked: {
                        info_bar.locationTitle = model.name
                        info_bar.locationWebsite = model.website
                        info_bar.expanded = true
                    }

                }
            }

            coordinate: {
                model.coordinate
            }

            opacity: 1.0
            anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)

        }
    }

    //visualize access through a slider
    MapItemView{
        ComboBox {
            id: visualizeAccess
            currentIndex: 0
            width: 200
            anchors.topMargin: 39
            anchors.top: parent.top;
            anchors.right: parent.right;
            model: ListModel {
                id: amItems
                ListElement { text: "Visualize Access" }
                ListElement { text: "Bakery" }
                ListElement { text: "Restaurant" }

            }
            background: Rectangle {
                        implicitWidth: 100
                        implicitHeight: 40
                        border.color: "#26282a"
                        border.width: 1
                        radius: 4
                        opacity: 0.75
                    }

        }

        Rectangle {
            id: accessSliderLabelRect;
            implicitWidth: 146
            implicitHeight: 25
            border.color: "#26282a"
            border.width: 1
            opacity: 0.75
            radius: 4
            anchors.margins: 53;
            anchors.rightMargin: 72;
            anchors.bottom: parent.bottom;
            anchors.right: parent.right
            Label {
                id: accessSliderLabel;
                text: "Adjust access radius";
                font.pixelSize: 14;
                anchors.fill: parent
                horizontalAlignment: Label.AlignHCenter
                verticalAlignment: Label.AlignVCenter
            }
       }

        Slider {
            id: accessSlider;
            to: 100;
            from: 5;
            anchors.margins: 18
            anchors.rightMargin: 50
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            orientation : Qt.Horizontal
            value: 5

        }

        model: emptyRadii
        delegate:  MapQuickItem {

            zoomLevel: 10
            sourceItem: Rectangle { id: emptyPoints; width: accessSlider.value; height: width;
                color: {
                    if (visualizeAccess.currentIndex === 1 && model.amenity === "Bakery") "purple";
                    else if (visualizeAccess.currentIndex === 2 && model.amenity === "Restaurant") return "purple";
                    else return "green";
                }
                border.width: 2;
                border.color: {
                    if (visualizeAccess.currentIndex === 1 && model.amenity === "Bakery") return "purple";
                    else if (visualizeAccess.currentIndex === 2 && model.amenity === "Restaurant") return "purple";
                    else return "green";
                }
                opacity: {
                    if (visualizeAccess.currentIndex === 1 && model.amenity === "Bakery") return 0.5;
                    else if (visualizeAccess.currentIndex === 2 && model.amenity === "Restaurant") return 0.5;
                    else return 0;
                }
                radius: 0.5*width;
                MouseArea {
                    id : expandingRadii
                    anchors.fill: parent
                    onClicked: {
                        info_bar.locationTitle = model.name
                        info_bar.locationWebsite = model.website
                        info_bar.expanded = true
                    }
                }

            }
            coordinate: {
                model.coordinate
                if (visualizeAccess.currentIndex === 0 && model.amenity === "Bakery") model.coordinate; else if (visualizeAccess.currentIndex === 1 && model.amenity === "Restaurant") model.coordinate;
            }
            opacity: 0.75
            anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)
        }

    }

    SideBar {
        id: info_bar
        expanded: false
        mapSource: map_map
        locationTitle: model.name
        locationWebsite: model.website
        anchors.top: parent.top
    }

    GeocodeModel {
        id: geocodeModel
        plugin: Plugin { name: 'osm' }
        autoUpdate: false
        onLocationsChanged: {
            if (count != 0) {
                map_map.center.latitude = get(0).coordinate.latitude
                map_map.center.longitude = get(0).coordinate.longitude
                map_map.zoomLevel = 14
            }
        }
    }

    SearchBar {
        id: searchBar
        onGoLocation: {
            if (location.length > 0)
                map_map.changeLocation(location);
        }
    }

    //display current location
    PositionSource {
        property variant coord

        id: getLocation
        updateInterval: 10000
        active: true
        onPositionChanged: {
            coord = getLocation.position.coordinate;
        }
    }

    MapQuickItem {
        id: currentMarker
        sourceItem: Rectangle {
            width: 14;
            height: 14;
            color: "blue";
            border.width: 2;
            border.color: "white";
            smooth: true;
            radius: 7;
        }
        coordinate: QtPositioning.coordinate(getLocation.coord.latitude,
                                              getLocation.coord.longitude)
    }


    Button {
        id: locationButton
        text: "Go to current location"
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: map_map.changeLocation(getLocation.position.coordinate)
        background: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 40
                    color: button.down ? "#d6d6d6" : "#f6f6f6"
                    border.color: "#26282a"
                    border.width: 1
                    radius: 4
                    opacity: 0.75
                }
    }

}
