(function ($) {

  Drupal.behaviors.npt_setup = {
    attach: function (context, settings) {

      var lat = Drupal.settings.npt_setup.lat;
      var lng = Drupal.settings.npt_setup.lng;
      var map = L.map('node_map').setView([lat, lng], 6);

      L.tileLayer('http://{s}.tile.cloudmade.com/BC9A493B41014CAABB98F0471D759707/997/256/{z}/{x}/{y}.png', {
      	maxZoom: 18,
      	attribution: 'Map data &copy; <a href="http://openstreetmap.org">OpenStreetMap</a> contributors, <a href="http://creativecommons.org/licenses/by-sa/2.0/">CC-BY-SA</a>, Imagery © <a href="http://cloudmade.com">CloudMade</a>'
      }).addTo(map);

      L.marker([lat, lng])
        .addTo(map).bindPopup("Current map centre.")
        .openPopup();

      var popup = L.popup();

      function onMapClick(e) {
      	popup
      		.setLatLng(e.latlng)
      		.setContent("Assigned new map centre at " + e.latlng.toString())
      		.openOn(map);
      		
      	$("#edit-node-coordinate-lat").val(e.latlng.lat);
      	$("#edit-node-coordinate-lng").val(e.latlng.lng);
      }

      map.on('click', onMapClick);

    }
  };

})(jQuery);