<?php

/**
 * @file
 * Basic Feeds API implementation.
 */

/**
 * Implements hook_feeds_processor_targets_alter().
 */
function postgis_feeds_processor_targets_alter(&$targets, $entity_type, $bundle_name) {
  foreach (field_info_instances($entity_type, $bundle_name) as $name => $instance) {
    $info = field_info_field($name);
    if ($info['type'] == 'postgis') {
      $targets[$info['field_name'] . ':gml'] = array(
        'name' => t('@label from GML', array('@label' => $instance['label'])),
        'callback' => 'postgis_feeds_set_target_gml',
        'real_target' => $info['field_name'],
      );
      $targets[$info['field_name'] . ':kml'] = array(
        'name' => t('@label from KML', array('@label' => $instance['label'])),
        'callback' => 'postgis_feeds_set_target_kml',
        'real_target' => $info['field_name'],
      );
      $targets[$info['field_name'] . ':wkt'] = array(
        'name' => t('@label from WKT', array('@label' => $instance['label'])),
        'callback' => 'postgis_feeds_set_target',
        'real_target' => $info['field_name'],
      );
      if (version_compare(postgis_version(), '2.0.0', '>=')) {
        $targets[$info['field_name'] . ':geojson'] = array(
          'name' => t('@label from GeoJSON', array('@label' => $instance['label'])),
          'callback' => 'postgis_feeds_set_target_geojson',
          'real_target' => $info['field_name'],
        );
      }
    }
  }
}

/**
 * Callback function for Feeds processor to convert GML geometries to WKT.
 */
function postgis_feeds_set_target_gml($source, $entity, $target, $value) {

  $value = db_query("SELECT ST_AsText(ST_GeomFromGML(:gml));",
          array(':gml' => $value))->fetchField();

  postgis_feeds_set_target($source, $entity, $target, $value);
}

/**
 * Callback function for Feeds processor to convert KML geometries to WKT.
 */
function postgis_feeds_set_target_kml($source, $entity, $target, $value) {

  $value = db_query("SELECT ST_AsText(ST_GeomFromKML(:kml));",
          array(':kml' => $value))->fetchField();

  postgis_feeds_set_target($source, $entity, $target, $value);
}


/**
 * Callback function for Feeds processor to convert GeoJSON geometries to WKT.
 */
function postgis_feeds_set_target_geojson($source, $entity, $target, $value) {

  $value = db_query("SELECT ST_AsText(ST_GeomFromGeoJSON(:geojson));",
          array(':geojson' => $value))->fetchField();

  postgis_feeds_set_target($source, $entity, $target, $value);
}

/**
 * Callback function for Feeds processor to import WKT.
 */
function postgis_feeds_set_target($source, $entity, $target, $value) {

  $field = isset($entity->$target) ? $entity->$target : array();
  $field[$entity->language][0]['wkt'] = $value;
  $field[$entity->language][0]['feeds'] = TRUE;

  $target = substr($target, 0, strpos($target, ':'));
  $entity->{$target} = $field;
}
