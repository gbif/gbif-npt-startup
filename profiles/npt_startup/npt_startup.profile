<?php

/**
 * @file
 * Instructing the installation and configuration so the Drupal site
 * is an instance of the NPT Startup
 */

/**
 * Implements hook_library().
 */
function npt_startup_library() {
  $libraries['list_participants'] = array(
    'title' => 'List Participants',
    'js' => array(
      drupal_get_path('profile', 'npt_startup') . '/js/listParticipants.js' => array(
        'type' => 'file',
        'scope' => 'footer',
        'weight' => 20,
      ),
    ),
  );
  $libraries['node_coordinate'] = array(
    'title' => 'Node Coordinate',
    'js' => array(
      drupal_get_path('module', 'npt_setup') . '/js/node_coordinate.js' => array(
        'type' => 'file',
        'scope' => 'footer',
        'weight' => 20,
      ),
    ),
    'css' => array(
      drupal_get_path('module', 'npt_setup') . '/css/node_coordinate.css' => array(
        'type' => 'file',
        'media' => 'all',
      ),
    ),
  );
  $libraries['leaflet'] = array(
    'title' => 'leaflet',
    'js' => array(
      libraries_get_path('leaflet') . '/leaflet.js' => array(
        'type' => 'file',
        'scope' => 'footer',
        'weight' => 20,
      ),
    ),
    'css' => array(
      libraries_get_path('leaflet') . '/leaflet.css' => array(
        'type' => 'file',
        'media' => 'all',
      ),
    ),
  );
  return $libraries;
}