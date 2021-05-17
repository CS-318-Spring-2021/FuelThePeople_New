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

    Slider {
        id: zoomSlider;
        z: map_map.z + 3
        to: map_map.maximumZoomLevel;
        from: map_map.minimumZoomLevel;
        anchors.margins: 10
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
            sourceItem: Rectangle { width: 14; height: 14; color: { if (model.amenity === "Bakery") "green"; else if (model.amenity === "Restaurant") "red";} border.width: 2; border.color: "white"; smooth: true; radius: 7;
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
                //if(model.amenity == "Bakery")
                    model.coordinate
            }
            opacity: 1.0
            anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)

        }
    }

//    MapItemView {
//        model: rest_model
//        delegate:  MapQuickItem {
//            id: restModel
//            sourceItem: Rectangle { width: 14; height: 14; color: model.color; border.width: 2; border.color: "white"; smooth: true; radius: 7;
//                MouseArea {
//                    anchors.fill: parent
//                    hoverEnabled: true
//                    onEntered: { parent.color = 'purple' }
//                    onExited: {parent.color = model.color }
//                    onClicked: {
//                        info_bar.locationTitle = model.name
//                        info_bar.locationWebsite = model.website
//                        info_bar.expanded = true
//                    }

//                }
//            }

//            coordinate: {
//                model.coordinate
//            }

//            opacity: 1.0
//            anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)

//        }
//    }
    //visualize access through a slider
    MapItemView{
        ComboBox {
            id: visualizeAccess
            currentIndex: 0

            model: ListModel {
                id: amItems
                ListElement { text: "Bakery" }
                ListElement { text: "Restaurant" }

            }
            width: 200

        }

        Slider {
            id: accessSlider;
            to: 80;
            from: 14;
            anchors.margins: 30
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            orientation : Qt.Horizontal
            value: 14

        }
        model: emptyRadii
        delegate:  MapQuickItem {
            sourceItem: Rectangle { id: emptyPoints; width: accessSlider.value; height: width;
                color: { if (visualizeAccess.currentIndex === 0 && model.amenity === "Bakery") "purple"; else if (visualizeAccess.currentIndex === 1 && model.amenity === "Restaurant") "orange";}
                border.width: 2; border.color: "purple"; opacity: 0.5; radius: 0.5*width; //if (model.amenity === emptyRadii.amenity) 0.5; else 0
                MouseArea {
                    id : expandingRadii
                    anchors.fill: parent
                }

            }
            coordinate: {
                model.coordinate
            }
            opacity: 1.0
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
        onClicked:
            map_map.changeLocation(getLocation.position.coordinate)
    }

}
