<?php
/**
 * @file
 * GeoServer layer type for PostGIS fields.
 */

/**
 * Define the Ctools plugin options.
 */
$plugin = array(
  'title' => t('PostGIS Field'),
  'description' => t('An entity containing a PostGIS field.'),
  'layer_type' => array(
    'file' => 'geoserver_layer_type_postgis_field.inc',
    'class' => 'geoserver_layer_type_postgis_field',
    'parent' => 'geoserver_layer_type',
  ),
);

/**
 * GeoServer PostGIS layer class.
 */
class geoserver_layer_type_postgis_field extends geoserver_layer_type_feature_type {

  /**
   * Constructor.
   */
  function __construct($layer = array()) {
    parent::__construct($layer);
    $this->datastore = variable_get('geoserver_postgis_datastore', '');
  }

  function save() {
    $this->create_view();
    return parent::save();
  }

  function create_view() {

    db_query($this->data['options']['sql']);
    $primary_keys = array('table_schema', 'table_name', 'pk_column');
    $sql_name = $this->data['options']['sql_name'];
    $schema = $this->get_schema($sql_name);

    // Insert/Update rercords in geoserver_pk_metadata_table.
    foreach (array('id', 'delta') as $idx => $column) {
      $record = array(
        'table_schema' => $schema,
        'table_name' => $sql_name,
        'pk_column' => $column,
        'pk_column_idx' => $idx
      );
      db_select('geoserver_pk_metadata_table', 'gs_pk')
          ->fields('gs_pk')
          ->condition('table_schema', $record['table_schema'])
          ->condition('table_name', $record['table_name'])
          ->condition('pk_column', $record['pk_column'])
          ->execute()
          ->fetchAll() ?
        drupal_write_record('geoserver_pk_metadata_table', $record, $primary_keys) :
        drupal_write_record('geoserver_pk_metadata_table', $record);
    }
  }

  function delete() {

    $sql_name = $this->data['options']['sql_name'];
    $schema = $this->get_schema($sql_name);
    $name = $schema . '.' . $sql_name;

    db_delete('geoserver_pk_metadata_table')
      ->condition('table_schema', $schema)
      ->condition('table_name', $sql_name)
      ->execute();

    db_query('DROP VIEW IF EXISTS ' . db_escape_table($name));
    return parent::delete();
  }

  private function get_schema(&$name) {
    if ($pos = strpos($name, '.')) {
      $name = substr($name, $pos) . $name;
      $schema = substr($name, 0, $pos);
    } else {
      $prefix = Database::getConnection()->tablePrefix();
      if ($pos = strpos($prefix, '.')) {
        $name = substr($prefix, $pos) . $name;
        $schema = substr($prefix, 0, $pos);
      } else {
        $name = $prefix . $name;
        $schema = 'public';
      }
    }
    return $schema;
  }

  /**
   * Import from remote feature type definition.
   */
  function from_feature_type($data) {

    $feature_type = isset($data->featureType) ? $data->featureType : new stdClass();
    $bbox = isset($feature_type->nativeBoundingBox) ? $feature_type->nativeBoundingBox : new stdClass();

    $this->name = isset($feature_type->name) ? $feature_type->name : '';
    $this->title = isset($feature_type->title) ? $feature_type->title : '';
    $this->data['options']['srid'] = isset($feature_type->srs) ? drupal_substr($feature_type->srs, 5) : '';
    $this->data['options']['bounding_box'] = array(
      'minx' => isset($bbox->minx) ? $bbox->minx : '',
      'miny' => isset($bbox->miny) ? $bbox->miny : '',
      'maxx' => isset($bbox->maxx) ? $bbox->maxx : '',
      'maxy' => isset($bbox->maxy) ? $bbox->maxy : '',
    );
  }

  /**
   * Export to remote feature type definition.
   */
  function to_feature_type() {

    $options = isset($this->data['options']) ? $this->data['options'] : array();
    $bbox = isset($options['bounding_box']) ? $options['bounding_box'] : array();

    return array(
      'featureType' => array(
        'name'       => $this->name,
        'nativeName' => isset($options['sql_name']) ? $options['sql_name'] : '',
        'namespace'  => array('name' => $this->workspace),
        'title'      => $this->title,
        'abstract'   => $this->description,
        'nativeCRS'  => isset($options['srid']) ? 'EPSG:' . $options['srid'] : '',
        'srs'        => isset($options['srid']) ? 'EPSG:' . $options['srid'] : '',
        'nativeBoundingBox' => array(
          'minx' => isset($bbox['minx']) ? $bbox['minx'] : '',
          'miny' => isset($bbox['miny']) ? $bbox['miny'] : '',
          'maxx' => isset($bbox['maxx']) ? $bbox['maxx'] : '',
          'maxy' => isset($bbox['maxy']) ? $bbox['maxy'] : '',
        ),
        'latLonBoundingBox' => array(
          'minx' => isset($bbox['minx']) ? $bbox['minx'] : '',
          'miny' => isset($bbox['miny']) ? $bbox['miny'] : '',
          'maxx' => isset($bbox['maxx']) ? $bbox['maxx'] : '',
          'maxy' => isset($bbox['maxy']) ? $bbox['maxy'] : '',
        ),
        'projectionPolicy' => 'FORCE_DECLARED',
        'enabled' => TRUE,
        'store' => array(
          '@class' => 'dataStore',
          'name' => $this->datastore,
        ),
        'maxFeatures' => 0,
        'numDecimals' => 0,
        'attributes' => array(),
      ),
    );
  }

  /**
   * Load field configuration.
   */
  function load_source($source) {

    $prefix       = Database::getConnection()->tablePrefix();
    $source_array = explode('.', $source);
    $entity_type  = $source_array[0];
    $bundle_name  = $source_array[1];
    $field_name   = $source_array[2];
    $sql_name     = $prefix . 'geoserver_' . $this->name . '_view';
    $sql          = $this->get_sql($entity_type, $bundle_name, $field_name, $sql_name);
    $field        = field_info_field($field_name);

    if ($field['settings']['srid'] == '4326') {
      $bbox = array('-180', '-90', '180', '90');
    }
    elseif ($field['settings']['srid'] == '900913') {
      $bbox = array('-20037508', '-20037508', '20037508', '20037508');
    }
    else {
      // Try to calculate maximum bounding box for defined projection.
      try {
        $extent = db_query("select st_extent(st_transform(st_setsrid(st_geomfromtext('polygon((-180 -90,-180 90, 180 90, -180 -90))'), 4326), :srid::int))",
          array(':srid' => $field['settings']['srid']))->fetchField();
        $bbox = preg_split('/[\, ]/', drupal_substr($extent, 4, -1));
      } catch (PDOException $exc) {
        $bbox = array('', '', '', '');
      }
    }

    $this->data['options']['srid'] = $field['settings']['srid'];
    $this->data['options']['sql_name'] = $sql_name;
    $this->data['options']['sql'] = $sql;
    $this->data['options']['bounding_box']['minx'] = $bbox[0];
    $this->data['options']['bounding_box']['miny'] = $bbox[1];
    $this->data['options']['bounding_box']['maxx'] = $bbox[2];
    $this->data['options']['bounding_box']['maxy'] = $bbox[3];
  }

  /**
   * Get layer SQL definition.
   */
  protected function get_sql($entity_type, $bundle_name, $field_name, $name) {
    $prefix = Database::getConnection()->tablePrefix();
    $rule_name = str_replace('.', '_', $name);
    $sql = array(
      'select' => array("DROP VIEW IF EXISTS $name;
CREATE VIEW $name AS SELECT $entity_type.nid AS id, $entity_type.nid, $entity_type.title AS name, field_data_$field_name.delta, field_data_$field_name.{$field_name}_geometry"),
      'from' => array("FROM $prefix$entity_type LEFT JOIN {$prefix}field_data_$field_name ON node.nid = field_data_$field_name.entity_id"),
      'where' => array("WHERE $entity_type.type = '$bundle_name' and $entity_type.status = 1 and field_data_$field_name.deleted = 0"),
      'rules' => array(
        "CREATE OR REPLACE RULE ${rule_name}_update AS ON UPDATE TO $name DO INSTEAD
  UPDATE {$prefix}field_data_$field_name SET ${field_name}_geometry = NEW.${field_name}_geometry WHERE entity_id = NEW.id;",
        "CREATE OR REPLACE RULE ${rule_name}_insert AS ON INSERT TO ${name} DO INSTEAD (
    INSERT INTO {$prefix}field_data_$field_name VALUES ('node', '$bundle_name', 0, nextval('{$prefix}node_nid_seq'), currval('{$prefix}node_nid_seq'), 'und', 0, NEW.${field_name}_geometry);
    INSERT INTO {$prefix}node VALUES (currval('{$prefix}node_nid_seq'), currval('{$prefix}node_nid_seq'), '$bundle_name', 'und', '', 0, 1, extract(epoch from now())::int, extract(epoch from now())::int, 0, 0, 0, 0, 0);
    INSERT INTO {$prefix}node_revision VALUES (currval('{$prefix}node_nid_seq'), currval('{$prefix}node_nid_seq'), 0, '', '', extract(epoch from now())::int, 1, 0, 0, 0);
  );",
        "CREATE OR REPLACE RULE ${rule_name}_delete AS ON DELETE TO ${name} DO INSTEAD
  DELETE FROM {$prefix}field_data_$field_name  WHERE entity_id = OLD.id and delta = OLD.delta;",
      ),
    );

    // Join additional fields with a 1:1 mapping to this bundle.
    $fields = field_info_instances($entity_type, $bundle_name);
    foreach ($fields as $name => $field) {
      $field = field_info_field($name);
      if ($name != $field_name && $field['cardinality'] === '1') {
        foreach ($field['storage']['details']['sql']['FIELD_LOAD_CURRENT'] as $table => $table_fields) {
          foreach ($table_fields as $table_field) {
            if ($table_field === 'body_value') {
              $table_field .= ' AS description';
            }
            $sql['select'][] = $table_field;
          }
          $sql['from'][] = "LEFT JOIN $prefix$table ON $entity_type.nid = $table.entity_id";
        }
      }
    }
    return implode(', ', $sql['select']) . "\n" . implode("\n", $sql['from']) . "\n" . implode("\n", $sql['where']) . ";\n" . implode("\n", $sql['rules']);
  }

  /**
   * Options form which generates layers
   */
  function options_form($form = array()) {

    if (empty($form)) {

      return array(
        'srid' => array(
          '#type' => 'hidden',
          '#title' => t('Projection'),
          '#prefix' => '<div id="geoserver_layer_type_postgis_field">',
          '#default_value' => isset($this->data['options']['srid']) ?
                  $this->data['options']['srid'] : '',
        ),
        'sql_name' => array(
          '#type' => 'textfield',
          '#title' => t('SQL View Name'),
          '#default_value' => isset($this->data['options']['sql_name']) ?
                  $this->data['options']['sql_name'] : '',
        ),
        'sql' => array(
          '#type' => 'textarea',
          '#title' => t('SQL'),
          '#default_value' => isset($this->data['options']['sql']) ?
                  $this->data['options']['sql'] : '',
        ),
        'bounding_box' => array(
          '#type' => 'fieldset',
          '#title' => t('Bounding Box'),
          '#collapsible' => TRUE,
          '#collapsed' => TRUE,
          '#suffix' => '</div>',
          'minx' => array(
            '#type' => 'textfield',
            '#title' => t('Min X'),
            '#default_value' => isset($this->data['options']['bounding_box']['minx']) ?
                    $this->data['options']['bounding_box']['minx'] : '',
          ),
          'miny' => array(
            '#type' => 'textfield',
            '#title' => t('Min Y'),
            '#default_value' => isset($this->data['options']['bounding_box']['miny']) ?
                    $this->data['options']['bounding_box']['miny'] : '',
          ),
          'maxx' => array(
            '#type' => 'textfield',
            '#title' => t('Max X'),
            '#default_value' => isset($this->data['options']['bounding_box']['maxx']) ?
                    $this->data['options']['bounding_box']['maxx'] : '',
          ),
          'maxy' => array(
            '#type' => 'textfield',
            '#title' => t('Max Y'),
            '#default_value' => isset($this->data['options']['bounding_box']['maxy']) ?
                    $this->data['options']['bounding_box']['maxy'] : '',
          ),
        ),
      );

    } else {

      $form['srid']['#value'] = $this->data['options']['srid'];
      $form['sql_name']['#value'] = $this->data['options']['sql_name'];
      $form['sql']['#value'] = $this->data['options']['sql'];
      $form['bounding_box']['minx']['#value'] = $this->data['options']['bounding_box']['minx'];
      $form['bounding_box']['miny']['#value'] = $this->data['options']['bounding_box']['miny'];
      $form['bounding_box']['maxx']['#value'] = $this->data['options']['bounding_box']['maxx'];
      $form['bounding_box']['maxy']['#value'] = $this->data['options']['bounding_box']['maxy'];

      return array($form['srid'], $form['sql_name'], $form['sql'], $form['bounding_box']);
    }
  }

  /**
   * @return array Mapping with all fields that are provided by the postgis module (fields that contain spatial data).
   */
  static function get_sources() {
    $sources = array('');

    $entityTypes = entity_get_info();
    foreach(field_info_fields() as $fieldName => $field){
      // Offer all fields of the postgis module
      if ($field['type'] === 'postgis') {
        foreach($field['bundles'] as $entityType => $contentTypes){
          foreach($contentTypes as $contentType) {
            $key = $entityType.'.'.$contentType.'.'.$field['field_name'];
            $value = $entityTypes[$entityType]['bundles'][$contentType]['label'].' ('.$field['field_name'].')';
            $sources[$entityTypes[$entityType]['label']][$key] = $value;
          }
        }
      }
    }
    return $sources;
  }

  /**
   * Layer type settings form.
   */
  function settings_form() {

    $datastores = array('');
    $workspace  = variable_get('geoserver_workspace', '');

    $result = geoserver_get('rest/workspaces/' . $workspace . '/datastores.json');
    if ($result->code == 200 && isset($result->data->dataStores)) {
      foreach ($result->data->dataStores->dataStore as $datastore) {
        $datastores[$datastore->name] = $datastore->name;
      }
    }

    return array(
      'geoserver_postgis_datastore' => array(
        '#type' => 'select',
        '#title' => t('Datastore'),
        '#options' => $datastores,
        '#description' => t('Select the PostGIS datastore where Drupal stores its data. This one needs to be created manually for now.'),
        '#default_value' => variable_get('geoserver_postgis_datastore', ''),
        '#suffix' => '</div>',
      ),
    );
  }
}
