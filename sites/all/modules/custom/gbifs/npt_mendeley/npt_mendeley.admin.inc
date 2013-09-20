<?php
/**
 * @file
 * Providing administrative functions to update the statistics.
 * @todo throbber is not shown under the scratchpads_admin theme.
 */
 
function npt_mendeley_settings_form() {
  drupal_add_library('npt_mendeley', 'progress', false); 
  $form['npt_mendeley_update'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update documents from Mendeley'),
    '#description' => '<p>' . t('Manually trigger the update of the publication information via Mendeley API and refresh the list of publications that are relevant to the Node.') . '<br/>' . t('Please note that Mendeley API has a rate limit of 150 calls per hour for any given IP. Update with this in mind. This may take longer than expected.') . '</p>',
  );
  $form['npt_mendeley_update']['update_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update now'),
    '#prefix' => '<div id="update-div">',
    '#suffix' => '<div id="status-wrapper"></div></div>',
    '#ajax' => array(
      'callback' => 'npt_mendeley_retrieve',
      'wrapper' => 'status-wrapper',
      'effect' => 'fade',
    ),
  );

  $total_docs = variable_get('npt_mendeley_total');
  $updated_docs = variable_get('npt_mendeley_updated', 0);
  $hours = ceil(($total_docs - $updated_docs) / 499);
  $description = t('Journal names need separate calls to retrieve. @updated_docs of total @total_docs documents updated. ', array(
    '@updated_docs' => $updated_docs,
    '@total_docs' => $total_docs,
  ));
  $description .= format_plural($hours, t('1 cron job left to complete.'), t('@count cron jobs left to complete.'));

  $form['npt_mendeley_detail'] = array(
    '#type' => 'fieldset',
    '#title' => t('Get journal names for documents retrieved from Mendeley'),
    '#description' => '<p>' . $description . '</p>',
  );
  $form['npt_mendeley_detail']['detail_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update journal names'),
    '#prefix' => '<div id="detail-div">',
    '#suffix' => '<div id="detail-status-wrapper"></div></div>',
    '#ajax' => array(
      'callback' => 'npt_mendeley_fill_doc_detail',
      'wrapper' => 'detail-status-wrapper',
      'effect' => 'fade',
    ),
  );
  $form['npt_mendeley_analyse'] = array(
    '#type' => 'fieldset',
    '#title' => t('Analyse retrieved documents from Mendeley'),
    '#description' => '<p>' . t('Group retrieved documents according to prefined sets of tags and produce lists in configurable blocks.') . '</p>',
  );
  $form['npt_mendeley_analyse']['analyse_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Analyse now'),
    '#prefix' => '<div id="analyse-div">',
    '#suffix' => '<div id="analyse-status-wrapper"></div></div>',
    '#ajax' => array(
      'callback' => 'npt_mendeley_analyse',
      'wrapper' => 'analyse-status-wrapper',
      'effect' => 'fade',
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
  $form['#submit'] = array('npt_mendeley_settings_form_submit');
  return system_settings_form($form);
}

function npt_mendeley_settings_form_submit($form, &$form_state) {
  variable_set('npt_mendeley_update_interval', $form_state['values']['update_interval']);
}