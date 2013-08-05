<?php
/**
 * @file
 * WFS Layer Type
 */

/**
 * Define the Ctools plugin options.
 */
$plugin = array(
  'title' => t('GeoServer WFS'),
  'description' => t('GeoServer specific Web Feature Service'),
  'layer_type' => array(
    'file' => 'openlayers_layer_type_geoserver_wfs.inc',
    'class' => 'openlayers_layer_type_geoserver_wfs',
    'parent' => 'openlayers_layer_type',
  ),
);

/**
 * OpenLayers WFS Layer Type class
 */
class openlayers_layer_type_geoserver_wfs extends openlayers_layer_type {

  /**
   * Constructor.
   */
  function __construct($layer = array(), $map = array()) {
    parent::__construct($layer, $map);
    if (isset($this->data)) {
      $this->data += $this->options_init();
    }
    else {
      $this->data = $this->options_init();
    }
  }

  /**
   * Provide initial values for options.
   */
  function options_init() {

    $url = variable_get('geoserver_url', '');
    $workspace = variable_get('geoserver_workspace', '');

    return array(
      'layer_type' => 'openlayers_layer_type_geoserver_wfs',
      'layer_handler' => 'openlayers_layer_type_geoserver_wfs',
      'url' => $url . $workspace . '/ows',
      'projection' => array('EPSG:4326', 'EPSG:3857'),
      'isBaseLayer' => FALSE,
      'typeName' => '', 
      'strategy' => 'bbox',
      'vector' => TRUE,
      'formatOptions' => array(
        'extractStyles' => TRUE,
        'extractAttributes' => TRUE,
      ),
    );
  }

  /**
   * Options form which generates layers
   */
  function options_form($defaults = array()) {
    return array(
      'url' => array(
        '#type' => 'textfield',
        '#title' => t('URL'),
        '#description' => t('The URL of the WFS server. For example: http://your_hostname/geoserver/your_workspace_name/ows'),
        '#maxlength' => 1024,
        '#default_value' => isset($this->data['url']) ? $this->data['url'] : ''
      ),
      'typeName' => array(
        '#type' => 'textfield',
        '#title' => t('Type Name'),
        '#description' => t('The typename of the features requested. Equals the layer name in GeoServer.'),
        '#maxlength' => 100,
        '#default_value' => isset($this->data['typeName']) ? $this->data['typeName'] : ''
      ),
      'strategy' => array(
        '#type' => 'select',
        '#title' => t('Strategy'),
        '#description' => t('Define the data loading strategy. "Fixed" will load all data initially, "Bounding Box" only loads data for the current map extent.'),
        '#options' => array(
          'bbox' => t('Bounding Box'),
          'fixed' => t('Fixed'),
        ),
        '#default_value' => isset($this->data['strategy']) ? $this->data['strategy'] : 'bbox',
      ),
      'attribution' => array(
        '#type' => 'textfield',
        '#title' => t('Attribution'),
        '#description' => t('Attribution is displayed when the Attribution behavior has been added to the map.'),
        '#maxlength' => 100,
        '#default_value' => isset($this->data['attribution']) ? $this->data['attribution'] : ''
      ),
      'sld' => array(
        '#type' => 'textarea',
        '#title' => t('SLD'),
        '#description' => t('Styled Layer Descriptor (SLD). Can be left empty to use default styling.'),
        '#default_value' => isset($this->data['sld']) ? $this->data['sld'] : ''
      ),
      'layer_type' => array(
        '#type' => 'hidden',
        '#value' => 'openlayers_layer_type_geoserver_wfs'
      ),
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'geoserver') .
      '/plugins/openlayers/layer_types/openlayers_layer_type_geoserver_wfs.js');
  }
}
