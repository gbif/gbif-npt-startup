<?php

/**
 * @file
 * GeoServer layer.
 */

/**
 * Get all layer types.
 *
 * @ingroup openlayers_api
 *
 * @param $reset
 *   Boolean whether to reset cache or not.
 * @return
 *   Array of layer type info.
 */
function geoserver_layer_types($reset = FALSE) {
  ctools_include('plugins');
  return ctools_get_plugins('geoserver', 'layer_types');
}

/**
 *  ...
 */
function geoserver_layers_load($reset = FALSE) {

  ctools_include('export');

  if ($reset) {
    ctools_export_load_object_reset('geoserver_layers');
  }

  $layers = ctools_export_load_object('geoserver_layers', 'all', array());

  foreach ($layers as $index => $layer) {
    $layer_object = geoserver_get_layer_object($layer);
    if ($layer_object) {
      $layers[$index] = $layer_object;
    }
    else {
      unset($layers[$index]);
    }
  }

  return $layers;
}

/**
 * Menu loader for layers. (%geoserver_layer)
 * @ingroup geoserver_api
 *
 * @param $name
 *   Layer name
 * @return array
 *   Layer export
 */
function geoserver_layer_load($name, $reset = FALSE) {

  ctools_include('export');

  if ($reset) {
    ctools_export_load_object_reset('geoserver_layers');
  }
  $layers = ctools_export_load_object('geoserver_layers', 'names', array($name));

  if (isset($layers[$name])) {
    return geoserver_get_layer_object($layers[$name]);
  }
  else {
    watchdog('geoserver', 'Layer %layer not found.', array('%layer' => $name), WATCHDOG_ERROR);
    return FALSE;
  }
}

function geoserver_layer_save(&$object) {
  $update = ($object->export_type & EXPORT_IN_DATABASE) ? array('name') : array();
  $object->export_type = EXPORT_IN_DATABASE;
  $result = drupal_write_record('geoserver_layers', $object, $update);

  if ($result) {
    $layer = geoserver_get_layer_object($object);
    return $layer->save();
  }
  else {
    return FALSE;
  }
}

function geoserver_layer_delete(&$object) {
  $layer = geoserver_get_layer_object($object);
  $result = db_delete('geoserver_layers')
    ->condition('name', is_object($object) ? $object->name : $object)
    ->execute();

  if ($result) {
    $layer = geoserver_get_layer_object($object);
    $layer->delete();
  }
  else {
    return FALSE;
  }

  // Restore layer if exported to code.
  if ($layer = geoserver_layer_load($layer->name, TRUE)) {
    return $layer->save();
  }
  return TRUE;
}

/**
 * Get layer object
 *
 * @ingroup openlayers_api
 * @param $reset
 *   Boolean whether to reset cache or not
 * @return array
 *   array of layer info
 */
function geoserver_get_layer_object($layer) {
  // Static cache because this function will possibly be called in big loops.
  static $layer_types;
  if (!isset($layer_types)) {
    $layer_types = geoserver_layer_types();
  }

  $layer->title = t($layer->title);
  $layer->description = t($layer->description);

  if (is_array($layer->data) && isset($layer->data['type']) &&  isset($layer_types[$layer->data['type']])) {
    $layer_class = ctools_plugin_get_class($layer_types[$layer->data['type']], 'layer_type');
    if ($layer_class) {
      return new $layer_class($layer);
    }
  }
  watchdog('geoserver', 'Layer %name is unavailable because its layer type or the module that provides its layer type is missing',
    array('%name' => $layer->name), WATCHDOG_ERROR);
  return FALSE;
}

/**
 * Menu loader for layer types.
 *
 * @ingroup openlayers_api
 *
 * @param $name
 *   String identifier of layer type.
 * @param $reset
 *   Boolean whether to reset cache or not.
 * @return
 *   An instantiated layer type object or FALSE if not found.
 */
function geoserver_layer_type_load($name, $reset = FALSE) {
  ctools_include('plugins');
  $layer_type_class = ctools_plugin_load_class('geoserver', 'layer_types', $name, 'layer_type');

  if ($layer_type_class) {
    $layer_type = new $layer_type_class();
    return $layer_type;
  }
  return FALSE;
}

/**
 * Problem requesting some resource.
 */
class geoserver_resource_exception extends Exception {};
/**
 * Problem requesting external resource using HTTP.
 */
class geoserver_resource_http_exception extends geoserver_resource_exception {
  public function __construct($url, $code, $message){
    $this->message = t("Access to !url returned HTTP status code !code.\n!message", array(
      "!url" => $url,
      "!code" => $code,
      "!message" => $message
    ));
  }
}
/**
 * Problem requesting external resource using curl.
 */
class geoserver_resource_curl_exception extends geoserver_resource_http_exception {
    public function __construct($curlHandle) {
        $error = curl_errno($curlHandle);
        if ($error===0) {
          // No real error but undesired status code
          parent::__construct(
            curl_getinfo($curlHandle, CURLINFO_EFFECTIVE_URL),
            curl_getinfo($curlHandle, CURLINFO_HTTP_CODE),
            ''
          );
        }
        else {
            $this->message = curl_errno($curlHandle) . " " . curl_error($curlHandle);
        }
    }
}

abstract class geoserver_resource {

  /**
   * Constructor.
   */
  function __construct($name, $datastore) {
    $this->name = $name;
    $this->datastore = $datastore;
    $this->workspace = variable_get('geoserver_workspace', '');
  }

  /**
   * Create remote resource.
   */
  abstract function create();

  /**
   * Update remote resource.
   */
  abstract function update();

  /**
   * Delete remote resource.
   */
  abstract function delete();

  /**
   * Read remote resource.
   */
  abstract function read();
}

/**
 * We define base classes in the core module.
 * All other parent classes can be autoloaded through ctools.
 */
abstract class geoserver_layer_type {

  const STATUS_FOUND_SAME = 1;
  const STATUS_FOUND_DIFF = 2;
  const STATUS_NOT_FOUND  = 3;

  public $name;

  /**
   * Constructor.
   */
  function __construct($layer = array()) {

    $this->workspace = variable_get('geoserver_workspace', '');

    foreach (array('name', 'title', 'description', 'data', 'export_type') as $k) {
      if (isset($layer->{$k})) {
        $this->{$k} = $layer->{$k};
      }
    }
  }

  /**
   * Export layer to remote resource definition.
   * @return geoserver_resource
   */
  abstract function to_resource();

  /**
   * Import layer from remote resource definition.
   */
  abstract function from_resource(geoserver_resource $resource);

  /**
   * Return fields of layer settings form.
   */
  function options_form($form = array()) {
    return $form;
  }

  /**
   * Get status of layer.
   */
  function get_status() {

    $resource = new geoserver_resource_feature_type($this->name, $this->datastore);

    try {
      $resource->read();
    } catch (geoserver_resource_exception $exc) {
      return geoserver_layer_type::STATUS_NOT_FOUND;
    }

    $remote = clone $this;
    $remote->from_resource($resource);

    if ($this->to_record() != $remote->to_record()) {
      return geoserver_layer_type::STATUS_FOUND_DIFF;
    }
    else {
      return geoserver_layer_type::STATUS_FOUND_SAME;
    }
  }

  /**
   * @return
   *   A version of this layer_type which can be saved,
   *   when attempting to save a modified layer.
   */
  function to_record() {
    return array(
      'name' => $this->name,
      'title' => $this->title,
      'description' => $this->description,
      'data' => $this->data,
    );
  }

  /**
   * @return
   *   Success value on saving this layer
   */
  function save() {

    $source = explode('.', $this->data['source']);

    if (empty($update) && $source[0] == 'node') {
      // Grant permissions derived from source.
      // Only for new node based layers for now.
      $roles = user_roles();
      $role_permissons = user_role_permissions($roles);
      foreach ($role_permissons as $rid => $permissons) {
        $readable = $editable = $createable = $bypass = FALSE;
        foreach ($permissons as $permission => $status) {
          if ($permission == 'view any ' . $source[1] . ' content') {
            $readable = TRUE;
          }
          elseif ($permission == 'edit any ' . $source[1] . ' content') {
            $editable = TRUE;
          }
          elseif ($permission == 'create ' . $source[1] . ' content') {
            $createable = TRUE;
          }
          elseif ($permission == 'bypass node access') {
            $bypass = TRUE;
          }
        }
        if ($readable) {
          user_role_grant_permissions($rid, array('read layer ' . $this->name));
        }
        if (($editable && $createable) || $bypass) {
          user_role_grant_permissions($rid, array('write layer ' . $this->name));
        }
      }
    }

    if ($this->get_status() == GEOSERVER_STATUS_NOT_FOUND) {
      try {
        $resource = $this->to_resource();
        return $resource->create();
      } catch (geoserver_resource_exception $exc) {
        watchdog('geoserver', 'Error when attempting to create layer %name: %message',
          array('%name' => $this->name, '%message' => $exc->getMessage()), WATCHDOG_ERROR);
        return FALSE;
      }
    }
    else {
      try {
        $resource = $this->to_resource();
        return $resource->update();
      } catch (geoserver_resource_exception $exc) {
        watchdog('geoserver', 'Error when attempting to update layer %name: %message',
          array('%name' => $this->name, '%message' => $exc->getMessage()), WATCHDOG_ERROR);
        return FALSE;
      }
    }
  }

  function delete() {

    $source = explode('.', $this->data['source']);
    if ($source[0] == 'node') {
      $permissions = array('read layer ' . $this->name, 'write layer ' . $this->name);
      db_delete('role_permission')
        ->condition('permission', $permissions, 'IN')
        ->execute();
      // Clear the user access cache.
      drupal_static_reset('user_access');
      drupal_static_reset('user_role_permissions');
    }

    try {
      $resource = $this->to_resource();
      return $resource->delete();
    } catch (geoserver_resource_exception $exc) {
      watchdog('geoserver', 'Error when attempting to delete layer %name: %message',
        array('%name' => $this->name, '%message' => $exc->getMessage()), WATCHDOG_ERROR);
      return FALSE;
    }
  }

  function load_source($source) {
  }
}

class geoserver_resource_feature_type extends geoserver_resource {
  /**
   * @var array
   */
  public $feature_type;

  /**
   * @var array
   */
  public $layer;

  /**
   * Create remote feature type.
   */
  public function create() {

    try {
      $url = "rest/workspaces/{$this->workspace}/datastores/{$this->datastore}/featuretypes.json";
      geoserver_post($url, $this->feature_type);
    } catch (geoserver_resource_exception $exc) {
      watchdog('geoserver', 'Could not create featuretype: %message', array("%message" => $exc->getMessage()), WATCHDOG_ERROR);
      return FALSE;
    }

    try {
      geoserver_put("rest/layers/{$this->workspace}:{$this->name}.json", $this->layer);
    } catch (geoserver_resource_exception $exc) {
      watchdog('geoserver', 'Could not update layer.', array(), WATCHDOG_ERROR);
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Update remote feature type.
   */
  public function update() {

    try {
      $url = "rest/workspaces/{$this->workspace}/datastores/{$this->datastore}/featuretypes/{$this->name}.json";
      geoserver_put($url, $this->feature_type);
    } catch (geoserver_resource_exception $exc) {
      watchdog('geoserver', 'Could not update featuretype.', array(), WATCHDOG_ERROR);
      return FALSE;
    }

    try {
      geoserver_put("rest/layers/{$this->workspace}:{$this->name}.json", $this->layer);
    } catch (geoserver_resource_exception $exc) {
      watchdog('geoserver', 'Could not update layer.', array(), WATCHDOG_ERROR);
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Delete remote feature type.
   */
  public function delete() {
    try {
      $url = "rest/workspaces/{$this->workspace}/datastores/{$this->datastore}/featuretypes/{$this->name}.json?recurse=true";
      geoserver_delete($url);
    } catch (geoserver_resource_exception $exc) {
      watchdog('geoserver', 'Could not delete featuretype.', array(), WATCHDOG_ERROR);
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Read remote feature type.
   */
  public function read() {

    $url = "rest/workspaces/{$this->workspace}/datastores/{$this->datastore}/featuretypes/{$this->name}.json";
    try {
      $result = geoserver_get($url);
      $this->feature_type = $result->data;
    } catch (geoserver_resource_http_exception $exc) {
      throw new geoserver_resource_exception(
        t("Could not read feature types from data store @datastore of workspace @workspace from GeoServer: @exception", array(
          "@datastore" => $this->datastore,
          "@workspace" => $this->workspace,
          "@exception" => $exc->getMessage()
        )));
    }

    try {
      $result = geoserver_get("rest/layers/{$this->workspace}:{$this->name}.json");
      $this->layer = $result->data;
    } catch (geoserver_resource_http_exception $exc) {
      throw new geoserver_resource_exception(t("Could not read layer @layer from GeoServer: @exception", array(
        "@layer" => $this->name,
        "@exception" => $exc->getMessage()
      )));
    }
  }
}

/**
 * Vector based layer.
 */
abstract class geoserver_layer_type_feature_type extends geoserver_layer_type {

  /**
   * Export to remote feature type definition.
   */
  abstract function to_feature_type();

  /**
   * Import from remote feature type definition.
   */
  abstract function from_feature_type($feature_type);

  /**
   * Export to remote layer definition.
   */
  function to_layer() {
    return array(
      'layer' => array(
        'name' => $this->name,
        'type' => 'VECTOR',
        'defaultStyle' => array(
          'workspace' => $this->workspace,
          'name' => $this->data['style'],
        ),
        'resource' => array(
          '@class' => 'featureType',
          'name' => $this->name,
        ),
        'enabled' => TRUE,
        'attribution' => array(
          'title' => isset($this->data['attribution']) ? $this->data['attribution'] : '',
        ),
      ),
    );
  }

  /**
   * Import from remote layer definition.
   */
  function from_layer($layer) {
    $style = isset($layer->layer->defaultStyle->name) ? $layer->layer->defaultStyle->name : '';
    $this->data['style'] = $style;
  }

  /**
   * Export layer to remote resource definition.
   */
  function to_resource() {
    $resource = new geoserver_resource_feature_type($this->name, $this->datastore);
    $resource->feature_type = $this->to_feature_type();
    $resource->layer = $this->to_layer();
    return $resource;
  }

  /**
   * Import layer from remote resource definition.
   */
  function from_resource(geoserver_resource $resource) {
    $this->from_feature_type($resource->feature_type);
    $this->from_layer($resource->layer);
  }

}

/**
 * Raster based layer.
 */
abstract class geoserver_layer_type_coverage extends geoserver_layer_type {

  /**
   * Export layer to remote coverage definition.
   */
  abstract function to_coverage();

  /**
   * Import layer from remote coverage definition.
   */
  abstract function from_coverage($coverage);

  /**
   * Create remote layer.
   */
  public function create_remote() {
  }

  /**
   * Update remote layer.
   */
  public function update_remote() {
  }

  /**
   * Delete remote layer.
   */
  public function delete_remote() {
  }

  /**
   * Read remote layer.
   */
  public function read_remote() {
  }
}
