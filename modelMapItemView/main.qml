import QtQuick 2.14
import QtPositioning 5.14
import QtLocation 5.14
import QtQuick.Window 2.2
import QtQuick.Controls 2.15 // or import Qt.labs.controls 1.0
import "menu"

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
        console.info("location update")
    }

    Slider {
            id: zoomSlider;
            z: map_map.z + 3
            to: map_map.maximumZoomLevel;
            from: map_map.minimumZoomLevel;
            anchors.margins: 10
            anchors.bottom: scale.top
            anchors.top: parent.top
            anchors.right: parent.right
            orientation : Qt.Vertical
            value: map_map.zoomLevel
            onValueChanged: {
                map_map.zoomLevel = value
            }
    }

    MapItemView{
        model: circle_model
        delegate:  MapQuickItem {
            id: test_map_point
            sourceItem: Rectangle { width: 14; height: 14; color: "#e41e25"; border.width: 2; border.color: "white"; smooth: true; radius: 7;
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: { parent.color = 'purple' }
                    onExited: {parent.color = 'red' }
                    onClicked: { popup.open() }

                }}
            coordinate: {
                model.coordinate
            }
            opacity: 1.0
            anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)

        }
    }

    Popup {
        id: popup
        parent: test_map_point
        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        width: 200
        height: 300
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
    }

    GeocodeModel {
        id: geocodeModel
        plugin: Plugin {
            name: 'osm'}
        autoUpdate: false

        onLocationsChanged: {
            if (count != 0) {
                console.info("location changed")
                console.info(count)
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
}
