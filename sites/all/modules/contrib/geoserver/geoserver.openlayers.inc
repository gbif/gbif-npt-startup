<?php

/**
 * @file
 * Provides OpenLayers layers.
 */

/**
 * Implements hook_openlayers_layers().
 */
function geoserver_openlayers_layers() {

  $ol_layers = array();
  $gs_layers = geoserver_layers_load();
  $gs_styles = geoserver_styles();
  $url = geoserver_url();
  $workspace = variable_get('geoserver_workspace', '');

  foreach (array_values($gs_layers) as $gs_layer) {

    if (!isset($gs_layer->data['openlayers'])) {
      // Layer has no OpenLayers configuration --> skip the layer
      continue;
    }
    $openlayers = $gs_layer->data['openlayers'];

    if ($openlayers['gwc']) {
      $data = isset($openlayers['gwc_data']) ? $openlayers['gwc_data'] : array();
      $ol_layer = new stdClass();
      $ol_layer->api_version = 1;
      $ol_layer->name = $gs_layer->name . '_gwc';
      $ol_layer->title = $gs_layer->title;
      $ol_layer->description = t('Cached WMS layer of GeoServer layer !name',
          array('!name' => $gs_layer->name));
      $ol_layer->data = array(
        'layer_type' => 'openlayers_layer_type_wms',
        'base_url' => $url . 'gwc/service/wms',
        'isBaseLayer' => isset($data['isBaseLayer']) ? $data['isBaseLayer'] : FALSE,
        'projection' => isset($data['projection']) ? $data['projection'] : array('EPSG:900913', 'EPSG:3857'),
        'params' => array(
          'isBaseLayer' => isset($data['isBaseLayer']) ? $data['isBaseLayer'] : FALSE,
          'buffer' => '2',
          'ratio' => '1.5',
          'singleTile' => 0,
        ),
        'options' => array(
          'TRANSPARENT' => 'true',
          'exceptions' => 'application/vnd.ogc.se_inimage',
          'format' => 'image/png',
          'layers' => array($workspace . ':' . $gs_layer->name),
          'styles' => '',
        ),
      );
      $ol_layers[$ol_layer->name] = $ol_layer;
    }

    if ($openlayers['wfs']) {
      $style = $gs_layer->data['style'];
      $sld = isset($gs_styles[$style]) ? $gs_styles[$style]->data : '';
      $data = isset($openlayers['wfs_data']) ? $openlayers['wfs_data'] : array();
      $ol_layer = new stdClass();
      $ol_layer->api_version = 1;
      $ol_layer->name = $gs_layer->name . '_wfs';
      $ol_layer->title = $gs_layer->title;
      $ol_layer->description = t('WFS layer of GeoServer layer !name',
          array('!name' => $gs_layer->name));
      $ol_layer->data = array(
        'attribution' =>  isset($gs_layer->data['attribution']) ? $gs_layer->data['attribution'] : NULL,
        'layer_type' => 'openlayers_layer_type_geoserver_wfs',
        'sld' => $sld,
        'url' => $url . $workspace . '/ows',
        'typeName' => $workspace . ':' . $gs_layer->name,
        'strategy' => isset($data['strategy']) ? $data['strategy'] : 'bbox',
        'isBaseLayer' => isset($data['isBaseLayer']) ? $data['isBaseLayer'] : FALSE,
        'projection' => isset($data['projection']) ? $data['projection'] : array('EPSG:900913', 'EPSG:3857'),
      );
      $ol_layers[$ol_layer->name] = $ol_layer;
    }

    if ($openlayers['wms']) {
      $data = isset($openlayers['wms_data']) ? $openlayers['wms_data'] : array();
      $ol_layer = new stdClass();
      $ol_layer->api_version = 1;
      $ol_layer->name = $gs_layer->name . '_wms';
      $ol_layer->title = $gs_layer->title;
      $ol_layer->description = t('Untiled WMS layer of GeoServer layer !name',
          array('!name' => $gs_layer->name));
      $ol_layer->data = array(
        'layer_type' => 'openlayers_layer_type_wms',
        'geoserver_wms' => TRUE,
        'base_url' => $url . 'wms',
        'isBaseLayer' => isset($data['isBaseLayer']) ? $data['isBaseLayer'] : FALSE,
        'projection' => isset($data['projection']) ? $data['projection'] : array('EPSG:900913', 'EPSG:3857'),
        'params' => array(
          'isBaseLayer' => isset($data['isBaseLayer']) ? $data['isBaseLayer'] : FALSE,
          'buffer' => '2',
          'ratio' => '1.5',
          'singleTile' => 1,
        ),
        'options' => array(
          'TRANSPARENT' => 'true',
          'exceptions' => 'application/vnd.ogc.se_inimage',
          'format' => 'image/png',
          'layers' => array($workspace . ':' . $gs_layer->name),
          'styles' => '',
        ),
      );
      $ol_layers[$ol_layer->name] = $ol_layer;
    }
  }

  return $ol_layers;
}
