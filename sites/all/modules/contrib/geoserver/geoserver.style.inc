<?php

/**
 * @file
 * GeoServer style.
 */

/**
 * Get all geoserver styles.
 *
 * @param $reset
 *   Boolean whether to reset cache or not.
 * @return
 *   Array of all available styles.
 */
function geoserver_styles($reset = FALSE) {
  ctools_include('export');
  if ($reset) {
    ctools_export_load_object_reset('geoserver_styles');
  }

  $styles = ctools_export_load_object('geoserver_styles', 'all', array());
  return $styles;
}

/**
 * Load a style object by name.
 *
 * This function can also be used as a
 * menu loader for a style.
 *
 * @param $name
 *   The string identifier of the style.
 * @param $reset
 *   Boolean whether to reset the cache or not.
 * @return
 *   A style object or FALSE if not found.
 */
function geoserver_style_load($name, $reset = FALSE) {
  $styles = geoserver_styles($reset);
  return !empty($styles[$name]) ? $styles[$name] : FALSE;
}

/**
 * Save style.
 *
 * @param $style
 *   The style object to save.
 */
function geoserver_style_save(&$style) {
  $workspace = variable_get('geoserver_workspace', '');
  $update = ($style->export_type & EXPORT_IN_DATABASE) ? array('name') : array();
  $style->export_type = EXPORT_IN_DATABASE;
  $result = drupal_write_record('geoserver_styles', $style, $update);

  if (!$result) {
    return FALSE;
  }

  if (geoserver_style_status($style) == GEOSERVER_STATUS_NOT_FOUND) {
    try {
      geoserver_post("rest/workspaces/$workspace/styles.sld?name={$style->name}", $style->data);
    }
    catch (geoserver_resource_exception $exc) {
      watchdog('geoserver', 'Error when attempting to create style %name: %message', 
        array('%name' => $style->name, '%message' => $exc->getMessage()), WATCHDOG_ERROR);
      return FALSE;
    }
  }
  else {
    try {
      geoserver_put("rest/workspaces/$workspace/styles/{$style->name}.sld", $style->data);
    } catch (geoserver_resource_exception $exc) {
      watchdog('geoserver', 'Error when attempting to update style %name: %message', 
        array('%name' => $style->name, '%message' => $exc->getMessage()), WATCHDOG_ERROR);
      return FALSE;
    }
  }
  return TRUE;
}

function geoserver_style_delete(&$style) {
  $workspace = variable_get('geoserver_workspace', '');
  $result = db_delete('geoserver_styles')
    ->condition('name', is_object($style) ? $style->name : $style)
    ->execute();

  if (!$result) {
    return FALSE;
  }

  try {
    geoserver_delete("rest/workspaces/$workspace/styles/{$style->name}?purge=true");
  } catch (geoserver_resource_exception $exc) {
    watchdog('geoserver', 'Error when attempting to delete style %name: %message',
      array('%name' => $style->name, '%message' => $exc->getMessage()), WATCHDOG_ERROR);
    // Note: ctools doesn't take FALSE return values of delete callbacks into account yet.
    return FALSE;
  }

  // Restore style if exported to code.
  if ($style = geoserver_style_load($style->name, TRUE)) {
    try {
      geoserver_post("rest/workspaces/$workspace/styles.sld?name={$style->name}", $style->data);
    }
    catch (geoserver_resource_exception $exc) {
      watchdog('geoserver', 'Error when attempting to revert style %name: %message', 
        array('%name' => $style->name, '%message' => $exc->getMessage()), WATCHDOG_ERROR);
      return FALSE;
    }
  }
  return TRUE;
}

/**
 * Get style status.
 *
 * @param $style
 *   String identifier of a style or style object with name.
 * @return
 *   Status.
 */
function geoserver_style_status($style) {

  if (is_string($style)) {
    $style = geoserver_style_load($style);
  }

  $workspace = variable_get('geoserver_workspace', '');
  try {
    $result = geoserver_get("rest/workspaces/$workspace/styles/{$style->name}.sld");
  } catch (geoserver_resource_http_exception $exc) {
    return GEOSERVER_STATUS_NOT_FOUND;
  }

  if ($style->data == $result->data) {
    return GEOSERVER_STATUS_FOUND_SAME;
  }
  else {
    return GEOSERVER_STATUS_FOUND_DIFF;
  }
}


function geoserver_styles_features_rebuild($module_name) {

  dvm($module_name);
  //var_dump($module_name);die;
  dvm('geoserver_styles_features_rebuild');

}