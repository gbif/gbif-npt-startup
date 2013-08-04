<?php

/**
 * @file
 * Hooks for Views integration.
 */

/**
 * Implements hook_field_views_data().
 *
 * Set custom filter handler for PostGIS fields.
 *
 */
function postgis_field_views_data($field) {
  $data = field_views_field_default_views_data($field);
  $field_name = $field['field_name'] . '_geometry';

  foreach ($data as $table_name => $table_data) {
    if (isset($table_data[$field_name])) {
      $data[$table_name][$field_name]['filter']['handler'] = 'postgis_views_handler_filter_geometry';
    }
  }
  return $data;
}