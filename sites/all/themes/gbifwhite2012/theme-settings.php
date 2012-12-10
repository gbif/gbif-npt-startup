<?php

function gbifwhite2012_form_system_theme_settings_alter(&$form, &$form_state) {
  $form['theme_settings']['toggle_gbif_footer'] = array(
    '#type' => 'checkbox',
    '#title' => t('GBIF links in the footer block'),
    '#default_value' => theme_get_setting('toggle_gbif_footer'),
  );
  $form['theme_settings']['toggle_gbif_credit'] = array(
    '#type' => 'checkbox',
    '#title' => t('GBIF credit in the credit block'),
    '#default_value' => theme_get_setting('toggle_gbif_credit'),
  );
}