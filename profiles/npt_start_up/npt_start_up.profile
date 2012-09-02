<?php

/**
 * Implements hook_install_tasks()
 */
function npt_start_up_install_tasks() {
  $tasks = array(
    'node_definition_form' => array(
      'display_name' => st('NPT Startup settings'),
      'type' => 'form',
    ),
  );
  return $tasks;
}

function node_definition_form() {
  drupal_set_title(st('NPT Startup settings'));

  // Get the list of GBIF country nodes
  $jsonurl = 'http://npt.gbif.org/gbif/stats/services/membership/world';
  $node = json_decode(file_get_contents($jsonurl));
  $nodelist = array();
  foreach ($node->country as $country => $attr) {
    $iso_a2 = $attr->iso_a2;
    $country_value = $iso_a2 . '-' . $country;
    $nodelist[$country_value] = $country;
  }
  asort($nodelist);
  
  $form = array();
  $form['node_info'] = array(
    '#type' => 'fieldset',
    '#title' => st('Node information'),
    '#description' => st('Please provide necessary information to setup this site as a GBIF node portal.'),
  );
  // Need to get a list of country node here
  $form['node_info']['node_country'] = array(
    '#type' => 'select',
    '#title' => st('GBIF participant:'),
    '#required' => TRUE,
    '#options' => $nodelist,
    '#description' => st('Only GBIF country participants are available at the moment.'),
  );
  $form['node_info']['node_shortname'] = array(
    '#type' => 'textfield',
    '#title' => st('Node short name:'),
    '#required' => FALSE,
    '#description' => st('Some nodes have short names like "NLBIF", "TaiBIF". With this field provided, some menu items will be named accordingly instead of using country names.'),
  );
  $form['node_info']['site_slogan'] = array(
    '#type' => 'textfield',
    '#title' => st('Site slogan:'),
    '#required' => FALSE,
    '#description' => st("Please provide a short text that you'd like to show under the site name."),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => st('Save and continue'),
  );
  return $form;
}

function node_definition_form_validate($form, &$form_state) {
}

function node_definition_form_submit($form, &$form_state) {
    $values = $form_state['values'];
    $country = explode('-', $values['node_country']);
    $country[1] = ($country[1] == 'Chinese Taipei') ? 'Taiwan' : $country[1];
    $shortname = $values['node_shortname'];
    
    // Assigning this site to a GBIF Participant
    variable_set('gbif_participant_node', $values['node_country']);
    // Registering short name
    variable_set('gbif_participant_shortname', $values['node_shortname']);
    
    // Setting site slogan
    if (isset($values['site_slogan'])) variable_set('site_slogan', $values['site_slogan']);
    
    module_enable(array('npt_nodestats', 'npt_feeds'), TRUE);
}

/**
* Implements hook_form_FORM_ID_alter().
*
* Allows the profile to alter the site configuration form.
*/
function npt_start_up_form_install_configure_form_alter(&$form, $form_state){
// Pre-populate the site name with the server name.
$form['update_notifications']['update_status_module']['#default_value'] = array();
}

