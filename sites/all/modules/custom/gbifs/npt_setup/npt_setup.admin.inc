<?php
/**
 * @file
 * Providing administrative functions to update the necessary Node information.
 * @todo Determine the country according to the node UUID.
 */

function npt_setup_settings() {
  $gbif_participant_node_uuid = variable_get('gbif_participant_node_uuid');
  $gbif_participant_shortname = variable_get('gbif_participant_shortname');
  $site_slogan = variable_get('site_slogan', $values['site_slogan']);

  // Get the list of GBIF Participant Nodes from GBIF API.
  $json_url = GBIF_REGISTRY_API_NODE . "?limit=200"; // To get all nodes at once.
  $gbif_registry_node_api_response = json_decode(file_get_contents($json_url));
  $gbif_registry_node_api_results = $gbif_registry_node_api_response->results;
  unset($gbif_registry_node_api_response);
  $node_list = array();
  $node_country_voting = array();
  $node_country_associate = array();
  $node_other = array();

  // Only to keep the title, type and UUID
  foreach ($gbif_registry_node_api_results as $result) {

    switch ($result->type) {
      case 'COUNTRY':
        if ($result->participationStatus == 'VOTING') {
          $node_country_voting[$result->key] = $result->title;
          asort($node_country_voting);
        } elseif ($result->participationStatus == 'ASSOCIATE') {
          $node_country_associate[$result->key] = $result->title;
          asort($node_country_associate);
        }
        break;
      case 'OTHER':
        if ($result->participationStatus <> 'FORMER') {
          $node_other[$result->key] = $result->title;
          asort($node_other);
        }
        break;
    }

  }
  
  // Assemble the option list
  $node_list['country-voting'] = '= ' . t('VOTING COUNTRY PARTICIPANT') . ' =';
  $node_list = array_merge($node_list, $node_country_voting);
  $node_list['country-associate'] = '= ' . t('ASSOCIATE COUNTRY PARTICIPANT') . ' =';
  $node_list = array_merge($node_list, $node_country_associate);
  $node_list['other-associate'] = '= ' . t('OTHER ASSOCIATE PARTICIPANT') . ' =';
  $node_list = array_merge($node_list, $node_other);
  unset($node_country_voting, $node_country_associate, $node_other);
  
  // Get the centre coordinate of the country.
  if ($centre_crd = variable_get('centre_crd')) {
    $lat = $centre_crd['lat'];
    $lng = $centre_crd['lng'];
  } else {
    // Use Geonames.org API
    $countries = country_get_list();
    $site_default_country_code = variable_get('site_default_country');
    $site_default_country_name = $countries[$site_default_country_code];

    $url = "http://api.geonames.org/searchJSON?country=" . $site_default_country_code . "&name=" . $site_default_country_name . "&maxRows=1&username=nptstartup";

    $coordinate_json = json_decode(file_get_contents($url));

    $lat = $coordinate_json->geonames[0]->lat;
    $lng = $coordinate_json->geonames[0]->lng;
  }
  
  // Prepare form.
  $form = array();
  $form['node_info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Node information'),
    '#description' => t('Please provide information to indicate the GBIF node with which this site will associate. The information can be changed later in the system configuration.'),
  );
  // Providing a drop-down list of GBIF Participant Nodes.
  $form['node_info']['node_uuid'] = array(
    '#type' => 'select',
    '#title' => t('GBIF Participant:'),
    '#required' => FALSE,
    '#options' => $node_list,
    '#description' => t('The list is sorted by the membership status of GBIF Participant. If you cannot find your node on the list, it may be that you are not yet a GBIF member. In this case, please leave it unselected.'),
    '#default_value' => $gbif_participant_node_uuid,
  );
  $form['node_info']['node_shortname'] = array(
    '#type' => 'textfield',
    '#title' => t('Node short name:'),
    '#required' => FALSE,
    '#description' => t('Some nodes have short names like "NLBIF", "TaiBIF". With this field provided, some menu items will use the short name.'),
    '#default_value' => $gbif_participant_shortname,
  );
  $form['node_info']['site_slogan'] = array(
    '#type' => 'textfield',
    '#title' => t('Site slogan:'),
    '#required' => FALSE,
    '#description' => t('Please provide a short text that you would like to show under the site name.'),
    '#default_value' => $site_slogan,
  );
  $form['node_location'] = array(
    '#type' => 'fieldset',
    '#title' => t('Node location'),
    '#description' => t('For mapping features in NPT Startup, by default NPT Startup will centre the map according to where your node is located. Please confirm the coordinate that NPT Startup has determined by the default country you chose from the last page. You can of course provide your own to fit your situation better.'),
  );
  $form['node_location']['node_coordinate_lat'] = array(
    '#type' => 'textfield',
    '#title' => t('Latitude:'),
    '#required' => FALSE,
    '#description' => t('Please provide the latitude.'),
    '#default_value' => (isset($lat)) ? $lat : 0,
  );
  $form['node_location']['node_coordinate_lng'] = array(
    '#type' => 'textfield',
    '#title' => t('Longitude:'),
    '#required' => FALSE,
    '#description' => t('Please provide the longitude.'),
    '#default_value' => (isset($lng)) ? $lng : 0,
  );
  $form['#submit'] = array('npt_setup_settings_submit');
  return system_settings_form($form);
}

function npt_setup_settings_submit($form, &$form_state) {
  $values = $form_state['values'];
  
  // Assigning this site to a GBIF Participant
  if ($values['node_uuid'] == 'country-voting' || $values['node_uuid'] == 'country-associate' || $values['node_uuid'] == 'other-associate' ) {
    // If no node is selected, then use 'none' to indicate.
    variable_set('gbif_participant_node_uuid', 'none');
  } else {
    variable_set('gbif_participant_node_uuid', $values['node_uuid']);
  }

  // Registering short name
  variable_set('gbif_participant_shortname', $values['node_shortname']);

  // Setting site slogan
  if (isset($values['site_slogan'])) variable_set('site_slogan', $values['site_slogan']);

  // Setting centre coordinates
  $centre_crd = array(
      'lat' => (isset($values['node_coordinate_lat'])) ? $values['node_coordinate_lat'] : 0,
      'lng' => (isset($values['node_coordinate_lng'])) ? $values['node_coordinate_lng'] : 0,
  );
  variable_set('centre_crd', $centre_crd);
}