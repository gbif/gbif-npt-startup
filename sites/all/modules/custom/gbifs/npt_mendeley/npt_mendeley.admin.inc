<?php
/**
 * @file
 * Providing administrative functions to update the statistics.
 *
 */
 
function npt_mendeley_settings_form() {

  $form['npt_mendeley_update'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update against Mendeley API'),
    '#description' => '<p>' . t('Manually trigger the update of the publication information from Mendeley API and refresh the list of publications that are relevant to the Node.') . '<br/>' . t('This may take longer than expected.') . '</p>',
  );
  $form['npt_mendeley_update']['update_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update now'),
    '#submit' => array('npt_mendeley_retrieve_submit'),
  );
  $form['npt_mendeley_update_interval'] = array(
    '#title' => t('Automatic update interval'),
    '#type' => 'fieldset',
    '#description' => t('You can decide how frequently you want the update to be conducted together with the system cron tasks.'),
  );
  $interval = drupal_map_assoc(array(1800, 3600, 10800, 21600, 32400, 43200, 86400, 259200), 'format_interval');
  $interval[0] = '<' . t('none') . '>';
  $form['npt_mendeley_update_interval']['update_interval'] = array(
    '#type' => 'select',
    '#default_value' => variable_get('npt_mendeley_update_interval', 3600),
    '#options' => $interval,
  );
  return system_settings_form($form);
}

function npt_mendeley_retrieve_submit() {
  $_SESSION['mendeley_page_requested'] = 0; // reset counter for debug information.
  $_SESSION['mendeley_gbif_documents'] = array(); // reset temporary document store.
  $batch = npt_mendeley_retrieve();
  batch_set($batch);
}