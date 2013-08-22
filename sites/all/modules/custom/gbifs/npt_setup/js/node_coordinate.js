(function($) {
  Drupal.behaviors.npt_setup = {
    attach: function(context, settings) {

      var map = new OpenLayers.Map('node_map');
      var wms = new OpenLayers.Layer.WMS(
        "OpenLayers WMS",
        "http://vmap0.tiles.osgeo.org/wms/vmap0",
        {'layers':'basic'} );
      map.addLayer(wms);
      map.zoomToMaxExtent();
    }
  };
})(jQuery);