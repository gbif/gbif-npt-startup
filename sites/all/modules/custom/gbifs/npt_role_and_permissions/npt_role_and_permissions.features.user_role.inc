<?php
/**
 * @file
 * npt_role_and_permissions.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function npt_role_and_permissions_user_default_roles() {
  $roles = array();

  // Exported role: contributor
  $roles['contributor'] = array(
    'name' => 'contributor',
    'weight' => '2',
  );

  // Exported role: editor
  $roles['editor'] = array(
    'name' => 'editor',
    'weight' => '3',
  );

  // Exported role: maintainer
  $roles['maintainer'] = array(
    'name' => 'maintainer',
    'weight' => '4',
  );

  return $roles;
}
