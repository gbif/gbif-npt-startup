<?php
/**
 * @file
 * Providing administrative functions to update the necessary Node information.
 * @todo Determine the country according to the node UUID.
 * @todo Decide a way to implement dependent mapping centering by default country.
 */

function npt_setup_settings($form, &$form_state) {

  drupal_add_js(libraries_get_path('leaflet') . '/leaflet.js');
  drupal_add_css(libraries_get_path('leaflet') . '/leaflet.css');
  drupal_add_js(drupal_get_path('profile', 'npt_startup') . '/js/nodeSettings.js');
  drupal_add_css(drupal_get_path('profile', 'npt_startup') . '/css/nodeSettings.css');
  
  $form = _npt_startup_settings_get_form($form, $form_state);

  $form['#submit'] = array('npt_setup_settings_submit');

  return system_settings_form($form);
}

function npt_setup_settings_submit($form, &$form_state) {
  $values = $form_state['values'];
  
  $gbif_participant_settings = array();
  
  if (isset($values['participant_type'])) $gbif_participant_settings['participant_type'] = $values['participant_type'];
  if (isset($values['node_uuid'])) $gbif_participant_settings['node_uuid'] = $values['node_uuid'];
  if (isset($values['node_shortname'])) $gbif_participant_settings['node_shortname'] = $values['node_shortname'];
  if (isset($values['node_country'])) {
    $gbif_participant_settings['node_country'] = $values['node_country'];
    $gbif_participant_settings['node_country_enum'] = _npt_startup_get_enum_by_country_code($values['node_country']);
    $gbif_participant_settings['node_title'] = _npt_startup_get_participant_title($values['node_uuid']);
  }

  variable_set('gbif_participant_settings', $gbif_participant_settings);
  

  // Setting centre coordinates
  $centre_crd = array(
      'lat' => (isset($values['node_coordinate_lat'])) ? $values['node_coordinate_lat'] : 0,
      'lng' => (isset($values['node_coordinate_lng'])) ? $values['node_coordinate_lng'] : 0,
  );
  variable_set('centre_crd', $centre_crd);
}