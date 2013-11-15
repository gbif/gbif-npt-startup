<?php

/**
 * @file
 * This file is empty by default because the base theme chain (Alpha & Omega) provides
 * all the basic functionality. However, in case you wish to customize the output that Drupal
 * generates through Alpha & Omega this file is a good place to do so.
 * 
 * Alpha comes with a neat solution for keeping this file as clean as possible while the code
 * for your subtheme grows. Please read the README.txt in the /preprocess and /process subfolders
 * for more information on this topic.
 */

function gbifwhite_preprocess_html(&$vars) {
  // Bringing in styles for banner.
  if (theme_get_setting('toggle_banner') == 1 ) {
    drupal_add_css(drupal_get_path('theme', 'gbifwhite') . '/css/banner.css', array('group' => CSS_THEME));
  }
  if (theme_get_setting('toggle_banner') == 1 ) {
    db_update('block')
      ->fields(array(
        'status' => 1,
        'region' => 'branding',
      ))
      ->condition('delta', 'eol_images_front-block_banner', '=')
      ->condition('theme', 'gbifwhite', '=')
      ->execute();
  }
  elseif (theme_get_setting('toggle_banner') == 0 ) {
    db_update('block')
      ->fields(array(
        'status' => 0,
        'region' => -1,
      ))
      ->condition('delta', 'eol_images_front-block_banner', '=')
      ->condition('theme', 'gbifwhite', '=')
      ->execute();
  }  
}