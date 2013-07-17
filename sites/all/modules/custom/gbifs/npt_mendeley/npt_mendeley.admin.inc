<?php
/**
 * @file
 * Providing administrative functions to update the statistics.
 *
 */
 
function npt_mendeley_settings_form() {
  drupal_add_library('system', 'ui.progressbar');
  drupal_add_library('npt_mendeley', 'progress', FALSE);
  $progress_path = $base_url . '/npt_mendeley/retrieval_progress';
  drupal_add_js(array('progress_path' => $progress_path), 'setting');
  variable_del('npt_mendeley_retrieval_progress');
  
  $form['npt_mendeley_update'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update against Mendeley API'),
    '#description' => '<p>' . t('Manually trigger the update of the publication information from Mendeley API and refresh the list of publications that are relevant to the Node.') . '<br/>' . t('Please note that Mendeley API has a rate limit of 150 calls per hour for any given IP. Update with this in mind. This may take longer than expected.') . '</p>',
  );
  $form['npt_mendeley_update']['update_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update now'),
    '#prefix' => '<div id="update-div">',
    '#suffix' => '</div>',
    '#attributes' => array(
      'onclick' => 'progressUpdate()',
    ),
    //'#submit' => array('npt_mendeley_retrieve'),
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