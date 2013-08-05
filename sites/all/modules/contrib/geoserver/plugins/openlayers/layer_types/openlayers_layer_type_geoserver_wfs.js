
/**
 * @file
 * Layer handler for GeoServer WFS layers
 */

/**
 * Openlayer layer handler for GeoServer WFS layer
 */
Drupal.openlayers.layer.openlayers_layer_type_geoserver_wfs = function(title, map, options) {

  var sld, layer, strategy, renderIntent, 
      intents = ['default', 'select', 'temporary', 'delete'];

  if (options.strategy == 'fixed') {
    strategy = new OpenLayers.Strategy.Fixed();
  } else {
    strategy = new OpenLayers.Strategy.BBOX();
  }

  layer = new OpenLayers.Layer.Vector(title, {
    drupalID: options.drupalID,
    attribution: options.attribution,
    strategies: [strategy],
    projection: map.projection,
    buffer: 0,
    styleMap: new OpenLayers.StyleMap(),
    protocol: new OpenLayers.Protocol.Script({
      url: options.url,
      callbackKey: 'format_options',
      callbackPrefix: 'callback:',
      params: {
        service: 'WFS',
        version: '1.0.0',
        request: 'GetFeature',
        // typeName equals layer name
        typeName: options.typeName,
        outputFormat: 'text/javascript',
        srsName: map.projection
      },
      filterToParams: function(filter, params) {
        if (filter.type === OpenLayers.Filter.Spatial.BBOX && !params.cql_filter) {
          params.bbox = filter.value.toArray();
          if (filter.projection) {
            params.bbox.push(filter.projection.getCode());
          }
        }
        return params;
      }
    })
  });

  // Apply GeoServer SLD.
  sld = new OpenLayers.Format.SLD().read(options.sld);
  jQuery.each(sld.namedLayers, function(index, namedLayer) {

    if (typeof namedLayer != 'object') {
      return;
    }

    jQuery.each(namedLayer.userStyles, function(index, style) {

      // Set cursor to pointer.
      style.defaultsPerSymbolizer = false;
      style.defaultStyle.cursor = 'pointer';

      // Prepend path of external graphics with geoserver_url if path is relative.
      // This way OpenLayers can find graphics that are stored and used inside GeoServer.
      jQuery.each(style.rules, function(index, rule) {
        if (rule.symbolizer.Point &&
            rule.symbolizer.Point.externalGraphic &&
            rule.symbolizer.Point.externalGraphic.substr(0, 4) != 'http' &&
            rule.symbolizer.Point.externalGraphic.substr(0, 1) != '/') {
          rule.symbolizer.Point.externalGraphic = options.geoserver_url+
            'styles/'+rule.symbolizer.Point.externalGraphic;
        }
      });

      // Use style name if it matches a render intent.
      renderIntent = 'default';
      if (jQuery.inArray(style.name, intents) > -1) {
        renderIntent = style.name;
      }

      // Apply style to layer if the specific render intent is not already set.
      if (jQuery.inArray(renderIntent, layer.styleMap.styles) === -1) {
        layer.styleMap.styles[renderIntent] = style;
      }
    });
  });
  layer.redraw();

  return layer;
};

