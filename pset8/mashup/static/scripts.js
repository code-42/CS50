// Google Map
let map;

// Markers for map
let markers = [];

// Info window
let info = new google.maps.InfoWindow(); // see line 91 and 187


// Execute when the DOM is fully loaded
$(document).ready(function() {

    // Styles for map
    // https://developers.google.com/maps/documentation/javascript/styling
    let styles = [

        // Hide Google's labels
        {
            featureType: "all",
            elementType: "labels",
            stylers: [
                {visibility: "off"}
            ]
        },

        // Hide roads
        {
            featureType: "road",
            elementType: "geometry",
            stylers: [
                {visibility: "off"}
            ]
        }

    ];

    // Options for map
    // https://developers.google.com/maps/documentation/javascript/reference#MapOptions
    let options = {
        // center: {lat: 37.4236, lng: -122.1619}, // Stanford, California
        center: {lat: 42.3770, lng: -71.1256},
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        maxZoom: 14,
        panControl: true,
        styles: styles,
        zoom: 13,
        zoomControl: true
    };

    // Get DOM node in which map will be instantiated
    let canvas = $("#map-canvas").get(0);

    // Instantiate map
    map = new google.maps.Map(canvas, options);

    // Configure UI once Google Map is idle (i.e., loaded)
    google.maps.event.addListenerOnce(map, "idle", configure);

});


// Add marker for place to map
function addMarker(place)
{
    // TODO
    // https://developers.google.com/maps/documentation/javascript/markers

    var myLatLng = new google.maps.LatLng(place.latitude, place.longitude);

    var marker = new google.maps.Marker({
      position: myLatLng,
      map: map
    });
    marker.addListener('click', function() {
        info.open(map, marker);
    });


    console.log("80. marker: ", marker);
    // console.log(marker);
    markers.push(marker);

}


// Configure application
function configure()
{
    // Update UI after map has been dragged
    google.maps.event.addListener(map, "dragend", function() {

        // If info window isn't open
        // http://stackoverflow.com/a/12410385
        if (!info.getMap || !info.getMap())
        {
            update();
        }
    });

    // Update UI after zoom level changes
    google.maps.event.addListener(map, "zoom_changed", function() {
        update();
    });

    // Configure typeahead
    $("#q").typeahead({
        highlight: false,
        minLength: 1
    },
    {
        display: function(suggestion) { return null; },
        limit: 5000,
        source: search,
        templates: {
            suggestion: Handlebars.compile(
                "<div>" +
                "{{place_name}}, {{admin_name1}}, {{postal_code}}" +
                "</div>"
            )
        }
    });

    // Re-center map after place is selected from drop-down
    $("#q").on("typeahead:selected", function(eventObject, suggestion, name) {

        // Set map's center
        map.setCenter({lat: parseFloat(suggestion.latitude), lng: parseFloat(suggestion.longitude)});

        // Update UI
        update();
    });

    // Hide info window when text box has focus
    $("#q").focus(function(eventData) {
        info.close();
    });

    // Re-enable ctrl- and right-clicking (and thus Inspect Element) on Google Map
    // https://chrome.google.com/webstore/detail/allow-right-click/hompjdfbfmmmgflfjdlnkohcplmboaeo?hl=en
    document.addEventListener("contextmenu", function(event) {
        event.returnValue = true;
        event.stopPropagation && event.stopPropagation();
        event.cancelBubble && event.cancelBubble();
    }, true);

    // Update UI
    console.log("\n134. about to call update()...");
    update();

    // Give focus to text box
    $("#q").focus();
}


// Remove markers from map
function removeMarkers()
{
    // TODO
    // https://developers.google.com/maps/documentation/javascript/examples/marker-remove

    for (var i = 0; i < markers.length; i++) {
      markers[i].setMap(null);
    }

    markers = [];

}


// Search database for typeahead's suggestions
function search(query, syncResults, asyncResults)
{
    // Get places matching query (asynchronously)
    let parameters = {
        q: query
    };
    $.getJSON("/search", parameters, function(data, textStatus, jqXHR) {
        console.log("158. data == ", data); // data[] is empty hmmm
        console.log("159. textStatus == " + textStatus);
        console.log("160. jqXHR == ", jqXHR);

        // Call typeahead's callback with search results (i.e., places)
        asyncResults(data);
    });
}


// Show info window at marker with content
function showInfo(marker, content)
{
    // Start div
    let div = "<div id='info'>";
    if (typeof(content) == "undefined")
    {
        // http://www.ajaxload.info/
        div += "<img alt='loading' src='/static/ajax-loader.gif'/>";
    }
    else
    {
        div += content;
    }

    // End div
    div += "</div>";

    // Set info window's content
    info.setContent(div);

    // Open info window (if not already open)
    info.open(map, marker);
}


// Update UI's markers
function update()
{
    console.log("\n194. inside update()");

    // Get map's bounds
    let bounds = map.getBounds();
    let ne = bounds.getNorthEast();
    let sw = bounds.getSouthWest();
    console.log("\n200. inside update().bounds" + bounds);

    // Get places within bounds (asynchronously)
    let parameters = {
        ne: `${ne.lat()},${ne.lng()}`,
        q: $("#q").val(),
        sw: `${sw.lat()},${sw.lng()}`
    };
    console.log(parameters);
    $.getJSON("/update", parameters, function(data, textStatus, jqXHR) {

       // Remove old markers from map
        removeMarkers();
        console.log("223. parameters == ", parameters);
        console.log("224. data == ", data.length); // data[] is empty hmmm
        console.log("225. textStatus == " + textStatus);
        console.log("226. jqXHR == ", jqXHR);


       // Add new markers to map
       for (let i = 0; i < data.length; i++)
       {
           console.log("212. inside update()", data[i]);
           addMarker(data[i]);
       }

        console.log("245. markers.length == " +  markers.length);
        for (let i = 0; i < markers.length; i++)
        {
           console.log("248. inside markers[]", markers[i]);
        }
    });

}
