/**
  * @desc Dependent dropdown for NPT Startup settings
  *
*/
(function ($) {

  Drupal.behaviors.npt_starup = {
    attach: function (context, settings) {

      $(document).ready(function() {

        $("#edit-participant-type").change(function() {

          var nodeType = $(this).val();
          var list = Drupal.settings.npt_startup[nodeType];
          var typeLabel = $("#edit-participant-type option:selected").text();
          var nodeSelect = $('#edit-node-uuid');
          
          // Update the Participant list according to the chosen type.
          $("label[for=edit-node-uuid]").text("GBIF " + typeLabel);
          nodeSelect.empty();
          $.each(list, function(uuid, node) {
            nodeSelect.append($("<option/>", {
              value: uuid,
              text: node
            }));
          });
          nodeSelect.trigger("chosen:updated");
          nodeSelect.trigger('change');
          
        });
        
        $("#edit-node-uuid").change(function() {
          var iso2 = Drupal.settings.npt_startup.ISO2;
          var currentUUID = $("#edit-node-uuid").val();
          var currentISO = iso2[currentUUID];
          $("#edit-node-country").val(currentISO).trigger("chosen:updated");
        });

        var lat = Drupal.settings.npt_startup.lat;
        var lng = Drupal.settings.npt_startup.lng;

        var map = new L.Map('node_map');
        
        /*
        var cloudmadeAPI = '7c6b0bdb3ff7468f949e6bb44ca1b569';
        var cloudmadeUrl = 'http://{s}.tile.cloudmade.com/' + cloudmadeAPI + '/997/256/{z}/{x}/{y}.png';
        var cloudmadeAttrib = 'Map data &copy; 2011 OpenStreetMap contributors, Imagery &copy; 2011 CloudMade';
        var cloudmade = new L.TileLayer(cloudmadeUrl, {minZoom: 1, maxZoom: 18, attribution: cloudmadeAttrib});
        */
        var mapquestUrl = 'http://{s}.mqcdn.com/tiles/1.0.0/osm/{z}/{x}/{y}.png';
        var subDomains = ['otile1','otile2','otile3','otile4'];
        var mapquestAttrib = 'Data, imagery and map information provided by <a href="http://open.mapquest.co.uk" target="_blank">MapQuest</a>, <a href="http://www.openstreetmap.org/" target="_blank">OpenStreetMap</a> and contributors.';
        var mapquest = new L.TileLayer(mapquestUrl, {maxZoom: 18, attribution: mapquestAttrib, subdomains: subDomains});        

        map.setView(new L.LatLng(lat, lng), 6);
        map.addLayer(mapquest);
        
        /*
        L.tileLayer('http://{s}.tile.cloudmade.com/BC9A493B41014CAABB98F0471D759707/997/256/{z}/{x}/{y}.png', {
        	maxZoom: 18,
        	attribution: 'Map data &copy; <a href="http://openstreetmap.org">OpenStreetMap</a> contributors, <a href="http://creativecommons.org/licenses/by-sa/2.0/">CC-BY-SA</a>, Imagery © <a href="http://cloudmade.com">CloudMade</a>'
        }).addTo(map);
        */
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

      });
    }
  };

})(jQuery);