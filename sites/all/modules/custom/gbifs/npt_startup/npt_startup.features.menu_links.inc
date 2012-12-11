<?php
/**
 * @file
 * Provide a link back to NPT group page.
 *
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function npt_startup_menu_default_menu_links() {
  $menu_links = array();
  // Exported menu link: management:http://help.scratchpads.eu/
  $menu_links['management:http://community.gbif.org/pg/groups/3507/nodes-portal-toolkit-npt/'] = array(
    'menu_name' => 'management',
    'link_path' => 'http://community.gbif.org/pg/groups/3507/nodes-portal-toolkit-npt/',
    'router_path' => '',
    'link_title' => 'Help',
    'options' => array(
      'attributes' => array(
        'title' => ''
      )
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '1',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '50',
    'parent_path' => 'admin'
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Help');
  return $menu_links;
}
