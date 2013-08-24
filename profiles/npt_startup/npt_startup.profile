<?php

/**
 * @file
 * Internal functions for assiting installation
 */

function _npt_startup_settings_get_form($form, &$form_state) {

  // Prepare form.
  $t = get_t();
  $form = array();
  $form['node_info'] = array(
    '#type' => 'fieldset',
    '#title' => $t('Node information'),
  );
  $form['node_info']['intro'] = array(
    '#type' => 'item',
    '#markup' => $t('Please indicate the GBIF Node with which this site associates. In case your country or organisation is not yet a member of GBIF, you can still set up NPT Startup without providing information here. This will however disable specific features.'),
  );

  // Provide a drop-down list of GBIF Participant Nodes.
  $participant_type_options = _npt_startup_participant_type_options();

  // Populate default values if settings exist.
  $gbif_participant_settings = variable_get('gbif_participant_settings', NULL);
  if (isset($form_state['values']['participant_type'])) {
    $default_type = $form_state['values']['participant_type'];
  }
  elseif (isset($gbif_participant_settings)) {
    $default_type = $gbif_participant_settings['participant_type'];
  }
  elseif ($gbif_participant_settings == NULL) {
    $default_type = key($participant_type_options);
  }

  $form['node_info']['participant_type'] = array(
    '#type' => 'select',
    '#title' => $t('Participant type'),
    '#options' => $participant_type_options,
    '#default_value' => $default_type,
  );
  $form['node_info']['node_uuid'] = array(
    '#type' => 'select',
    '#title' => $t('GBIF Participants'),
    '#options' => _npt_startup_get_participant_list($default_type),
    '#default_value' => isset($gbif_participant_settings['node_uuid']) ? $gbif_participant_settings['node_uuid'] : NULL,
    '#description' => $t('Not a GBIF Participant? Please leave it unselected.'),
    '#required' => FALSE,
  );

  $form['node_info']['node_shortname'] = array(
    '#type' => 'textfield',
    '#title' => $t('Node short name:'),
    '#required' => FALSE,
    '#description' => $t('Some nodes have short names like "NLBIF", "TaiBIF". With this field provided, some menu items will use the short name.'),
    '#default_value' => isset($gbif_participant_settings['node_shortname']) ? $gbif_participant_settings['node_shortname'] : NULL,
  );

  $form['node_location'] = array(
    '#type' => 'fieldset',
    '#title' => $t('Node location'),
  );

  $countries = country_get_list();
  array_unshift($countries, '');
  // Determine default country
  if ($gbif_participant_settings['participant_type'] == 'VOTING' || $gbif_participant_settings['participant_type'] == 'ASSOCIATE') {
    $node_info = _npt_startup_get_participant_info($gbif_participant_settings['node_uuid']);
    $default_country = _npt_setup_get_country_code_by_enum($node_info->country);
  } else {
    $default_country = isset($gbif_participant_settings['node_country']) ? $gbif_participant_settings['node_country'] : variable_get('site_default_country');
  }

  $form['node_location']['node_country'] = array(
    '#type' => 'select',
    '#title' => $t('Country'),
    '#description' => t('By default NPT will determine your country by, first, the type of GBIF membership, and then second, where the server location is (set in the previous page). Please choose if neither of the above applies.'),
    '#options' => $countries,
    '#default_value' => $default_country,
    '#attributes' => array(
      'data-placeholder' => $t('Choose a country...'),
    ),
    '#required' => FALSE,
  );

  // Determine the centre coordinate of the country for map positioning.
  $centre_crd = variable_get("centre_crd", NULL);
  if ($centre_crd == NULL) {
    $centre_crd = _npt_startup_get_country_coordinate($default_country, $countries[$default_country]);
  }
  _npt_startup_set_map_centre($centre_crd['lat'], $centre_crd['lng']);

  $form['node_location']['node_coordinate'] = array(
    '#type' => 'item',
    '#markup' => '<p>' . t('For mapping features in NPT Startup, by default NPT Startup will centre the map according to where your node is located. Please confirm the coordinate that NPT Startup has determined by the default country you chose from the last page. You can of course provide your own to fit your situation better.') . '</p>',
    '#suffix' => '<div id="node_map"></div>',
  );
  $form['node_location']['node_coordinate_lat'] = array(
    '#type' => 'textfield',
    '#title' => $t('Latitude:'),
    '#required' => FALSE,
    '#description' => $t('Please provide the latitude.'),
    '#default_value' => (isset($centre_crd['lat'])) ? $centre_crd['lat'] : 0,
  );
  $form['node_location']['node_coordinate_lng'] = array(
    '#type' => 'textfield',
    '#title' => $t('Longitude:'),
    '#required' => FALSE,
    '#description' => $t('Please provide the longitude.'),
    '#default_value' => (isset($centre_crd['lng'])) ? $centre_crd['lng'] : 0,
  );
  
  return $form; 
}

function _npt_startup_participant_type_options() {
  $t = get_t();
  return array(
    'VOTING' => $t('Voting Participants'),
    'ASSOCIATE' => $t('Associate Country Participants'),
    'OTHER' => $t('Other Associate Participants'),
  );
}

function _npt_startup_get_participant_list() {

  $node_types = array('voting', 'associate', 'other');
  foreach ($node_types as $node) {
    $$node = array();
  }
  $iso2 = array();

  // Get the list of GBIF Participant Nodes from GBIF API.
  $json_url = GBIF_REGISTRY_API_NODE . "?limit=200"; // To get all nodes at once.
  $gbif_registry_node_api_response = json_decode(file_get_contents($json_url));
  $gbif_registry_node_api_results = $gbif_registry_node_api_response->results;
  unset($gbif_registry_node_api_response);

  // Only to keep the title, type and UUID
  foreach ($gbif_registry_node_api_results as $result) {

    switch ($result->type) {
      case 'COUNTRY':
        if ($result->participationStatus == 'VOTING') {
          $voting[$result->key] = $result->title;
          asort($voting);
        } elseif ($result->participationStatus == 'ASSOCIATE') {
          $associate[$result->key] = $result->title;
          asort($associate);
        }
        $iso2[$result->key] = $result->country;
        break;
      case 'OTHER':
        if ($result->participationStatus <> 'FORMER') {
          $other[$result->key] = $result->title;
          asort($other);
        }
        break;
    }

  }
  $initial_list = array_merge($voting, $associate, $other);

  foreach ($node_types as $node) {
    $$node = json_decode(json_encode($$node));
  }
  
  // Convert enumName into ISO2. To be deleted when GBIF API updated.
  $countries = json_decode(file_get_contents(GBIF_COUNTRY_ENUM));
  foreach ($iso2 as $uuid => $enum) {
    foreach ($countries as $country) {
      if ($country->enumName == $enum) {
        $iso2[$uuid] = $country->iso2;
      }
    }
  }
  
  drupal_add_js(array(
    'npt_startup' => array(
      'VOTING' => $voting,
      'ASSOCIATE' => $associate,
      'OTHER' => $other,
      'ISO2' => $iso2,
    ),
  ), 'setting');

  return $initial_list;
}

function _npt_startup_get_participant_info($uuid) {
  $url = GBIF_REGISTRY_API_NODE . '/' . $uuid;
  $result = json_decode(file_get_contents($url));
  return $result;
}

function _npt_startup_get_country_coordinate($iso, $enum) {
  $url = "http://api.geonames.org/searchJSON?country=" . $iso . "&name=" . $enum . "&maxRows=1&username=nptstartup";
  $coordinate_json = json_decode(file_get_contents($url));
  if ($coordinate_json->geonames) {
    $lat = $coordinate_json->geonames[0]->lat;
    $lng = $coordinate_json->geonames[0]->lng;
    return $centre_crd = array(
      'lat' => $lat,
      'lng' => $lng,
    );
  }
}

function _npt_startup_set_map_centre($lat, $lng) {
  drupal_add_js(array(
    'npt_startup' => array(
      'lat' => $lat,
      'lng' => $lng,
    ),
  ), 'setting');
}