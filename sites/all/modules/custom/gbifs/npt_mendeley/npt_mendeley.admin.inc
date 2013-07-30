<?php
/**
 * @file
 * Providing administrative functions to update the statistics.
 *
 */
 
function npt_mendeley_settings_form() {
  global $base_url;
  
  $form['npt_mendeley_update'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update documents from Mendeley'),
    '#description' => '<p>' . t('Manually trigger the update of the publication information via Mendeley API and refresh the list of publications that are relevant to the Node.') . '<br/>' . t('Please note that Mendeley API has a rate limit of 150 calls per hour for any given IP. Update with this in mind. This may take longer than expected.') . '</p>',
  );
  $form['npt_mendeley_update']['update_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update now'),
    '#prefix' => '<div id="update-div">',
    '#suffix' => '<span id="status-message"></span></div>',
    '#ajax' => array(
      'callback' => 'npt_mendeley_retrieve',
      'wrapper' => 'status-message',
      'effect' => 'fade',
      'progress' => array(
        'type' => 'bar',
        'message' => t('Loading...'),
        'url' => '/npt_mendeley/retrieval_progress',
        'interval' => '100',
      ),
    ),
  );
  $form['npt_mendeley_update_interval'] = array(
    '#title' => t('Automatic update interval'),
    '#type' => 'fieldset',
    '#description' => t('You can decide how frequently you want to run the update together with the system cron tasks.'),
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

function npt_mendeley_settings_form_submit($form, &$form_state) {
  variable_set('npt_mendeley_update_interval');
}