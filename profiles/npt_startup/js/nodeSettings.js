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

      });
    }
  };

})(jQuery);