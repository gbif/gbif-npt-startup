<?php
/**
 * @file
 * This file provides a toggle switch for
 *   1) Displaying GBIF links in the footer area;
 *   2) Displaying GBIF credit in the credit area;
 *   3) Enabling banner. 
 * @todo Provide a form to submit a banner image, including validation of the image. 
 */

function gbifwhite_form_system_theme_settings_alter(&$form, &$form_state) {
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
  $form['theme_settings']['toggle_banner'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable banner'),
    '#default_value' => theme_get_setting('toggle_banner'),
  );
}