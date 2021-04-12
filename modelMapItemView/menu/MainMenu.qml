import QtQuick 2.5
import QtQuick.Controls 2.15

MenuBar {
    signal selectTool(string tool)
    // Menu for Geocoding from mapviewer example
    Menu {
        id: geocodeMenu
        title: qsTr("geocode")

        function createMenu(map) {
            clear()
            if (map.plugin.supportsGeocoding()) {
                addItem(qsTr("Geocode")).triggered.connect(function(){selectTool("Geocode")})
            }
        }
    }
}
