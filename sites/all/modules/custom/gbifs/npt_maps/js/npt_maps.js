(function($){
  Drupal.GM3.npt_country_mask = function(map){

    if (map.google_map) {

      var maskLayer = new google.maps.KmlLayer({
        url: 'http://bkotemp.gbif.org/map/BEN_adm1.kmz'
      });
      maskLayer.setMap(map.google_map);

    }
    

    /* Add a toggle button.
    $('#'+this.GM3.id).parent().append('<div class="gbif-toggle" style="position:relative; top:-20px;left:200px;height:0px;"><form><input id="gbif-toggle" type="checkbox" checked="checked"><label class="option" for="gbif-toggle">'+Drupal.t('GBIF data')+'</label></form></div>');
    var self = this;
    $('#gbif-toggle').change(function(){
      if($('#gbif-toggle').attr('checked')){
        self.GM3.google_map.overlayMapTypes.insertAt(0, self.overlay);        
      } else {
        self.GM3.google_map.overlayMapTypes.removeAt(0);  
      }
    });
    */
  }
})(jQuery);