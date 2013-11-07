// http://gis.stackexchange.com/questions/59330/how-to-use-wkt-in-google-map-v3
// http://stackoverflow.com/questions/2956355/highlight-polygon-and-tint-rest-of-map-using-google-maps/2958856#2958856
// http://stackoverflow.com/questions/7494474/google-maps-api-polygon-with-hole-in-center

(function($){
  Drupal.GM3.npt_country_mask = function(map){
    this.GM3 = map;

    if (this.GM3.google_map) {
      
      var ringPaths = [];

      // Drawing the masking polygon.
      var outerRingString = Drupal.settings.npt_maps.settings.outerRingString;
      var outerRing = [];
      AddPoints(outerRingString, outerRing);
      ringPaths.push(outerRing);
      
      // Drawing inner rings with country polygons
      var wkt = Drupal.settings.npt_maps.settings.mask.wkt;

      // Using the regex to get individual rings.
      var regex = /\(([^()]+)\)/g;
      var Rings = [];
      var results;
      while (results = regex.exec(wkt)) {
        Rings.push(results[1]);
      }

      var ptsArray = [];

      // Now we need to draw the polygon for each of inner rings, but reversed.
      // Each ring should be its own array.
      for ( var i = 0; i < Rings.length; i++) {
        AddPoints(Rings[i], ptsArray);
        ringPaths.push(ptsArray);
        // Empty ptsArray for the next ring.
        ptsArray = [];
      }

      var polyMask = new google.maps.Polygon({
          paths: ringPaths,
          strokeColor: '#1E90FF',
          strokeOpacity: 0.8,
          strokeWeight: 0,
          fillColor: '#666',
          fillOpacity: 0.5
        });

      polyMask.setMap(this.GM3.google_map);
      
      // function to add points from individual rings
      function AddPoints(data, array){
        // first spilt the string into individual points
        var pointsData = data.split(",");

        // iterate over each points data and create a latlong
        // & add it to the cords array
        for ( var i = 0; i < pointsData.length; i++) {
          var xy = pointsData[i].split(" ");

          var pt = new google.maps.LatLng(xy[1],xy[0]);
          array.push(pt);
        }
      }
    }

    // Add a toggle button for this mask.
    $('#' + this.GM3.id ).parent().append('<div class="mask-toggle" style="position:relative; top:-40px;left:300px;height:0px;"><form><input id="mask-toggle" type="checkbox" checked="checked"><label class="option" for="mask-toggle">'+Drupal.t('Country mask')+'</label></form></div>');
    $('#mask-toggle').change(function(){
      if ($('#mask-toggle').attr('checked')) {
        polyMask.setMap(map.google_map);        
      } else {
        polyMask.setMap(null);
      }
    });
  }
})(jQuery);