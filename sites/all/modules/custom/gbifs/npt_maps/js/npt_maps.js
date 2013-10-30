(function($){
  Drupal.GM3.npt_country_mask = function(map){
    this.GM3 = map;

    if (this.GM3.google_map) {
      /* Code snippet for loading KML
      var maskLayer = new google.maps.KmlLayer({
        url: 'http://bkotemp.gbif.org/map/BEN_adm0.kmz'
      });
      maskLayer.setMap(map.google_map);
      */
      
      var elevator;

      var wkt = Drupal.settings.npt_maps.settings.mask.wkt;

      //using regex, we will get the indivudal Rings
      var regex = /\(([^()]+)\)/g;
      var Rings = [];
      var results;
      while( results = regex.exec(wkt) ) {
        Rings.push( results[1] );
      }

      var ptsArray = [];

      var polyLen = Rings.length;

      //now we need to draw the polygon for each of inner rings, but reversed
      for ( var i = 0; i < polyLen ; i++){
        AddPoints(Rings[i]);
      }

      var polyMask = new google.maps.Polygon({
          paths: ptsArray,
          strokeColor: '#1E90FF',
          strokeOpacity: 0.8,
          strokeWeight: 0,
          fillColor: '#666',
          fillOpacity: 0.5
        });

      polyMask.setMap(this.GM3.google_map);

      //function to add points from individual rings
      function AddPoints(data){
        //first spilt the string into individual points
        var pointsData = data.split(",");


        //iterate over each points data and create a latlong
        //& add it to the cords array
        var len = pointsData.length;
        for ( var i = 0; i < len; i++) {
          var xy = pointsData[i].split(" ");

          var pt = new google.maps.LatLng(xy[1],xy[0]);
          ptsArray.push(pt);
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