/**
 * @file
 * JS Implementation of OpenLayers behavior.
 */

/**
 * OpenLayers GeoServer ECQL Behavior
 */
Drupal.openlayers.addBehavior('openlayers_behavior_geoserver_ecql', function (data, options) {

  jQuery.each(options, function(name, value) {

    var layer = data.openlayers.getLayersBy('drupalID', name)[0];

    if (typeof layer != 'undefined' && value != '') {
      
      // Listen to change event for all given fields.
      var fields = value.match(/#(\w+)/g);

      for (var i = 0; i < fields.length; i++) {

        var field = fields[i];

        jQuery(field).keyup(function() {

          var cql_filter = {
            'cql_filter': value.replace(new RegExp(field), jQuery(this).val())
          };

          if (layer instanceof OpenLayers.Layer.Vector) {
            layer.protocol.params = OpenLayers.Util.extend(layer.protocol.params, cql_filter);
            delete layer.protocol.params.bbox;
            layer.refresh({force: true});
          }

          else if (layer instanceof OpenLayers.Layer.WMS) {
            layer.mergeNewParams(cql_filter);
          }
        });
      }

      // Filter layer immediately if query doesn't contain fields.
      if (fields.length == 0) {

        var cql_filter = {'cql_filter': value};

        if (layer instanceof OpenLayers.Layer.Vector) {
          layer.protocol.params = OpenLayers.Util.extend(layer.protocol.params, cql_filter);
          delete layer.protocol.params.bbox;
        }

        else if (layer instanceof OpenLayers.Layer.WMS) {
          layer.mergeNewParams(cql_filter);
        }
      }
    }
  });
});
