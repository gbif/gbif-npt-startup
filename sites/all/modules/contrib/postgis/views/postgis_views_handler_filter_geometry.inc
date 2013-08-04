<?php

/**
 * @file
 * Definition of postgis_views_handler_filter_geometry.
 */

/**
 * A handler to provide filter for geospatial data.
 */
class postgis_views_handler_filter_geometry extends views_handler_filter {

  var $no_operator = TRUE;

  var $operations = array('ST_Contains', 'ST_Intersects', 'ST_Disjoint');

  function option_definition() {

    $options = parent::option_definition();
    $options['operation'] = array('default' => 'ST_Contains');
    $options['origin'] = array('default' => 'nid_arg');
    $options['value'] = array(
      'default' => array(
        'nid_arg' => '',
        'nid_postgis_field' => '',
      ),
    );

    return $options;
  }

  function value_form(&$form, &$form_state) {

    $form['operation'] = array(
      '#type' => 'select',
      '#title' => t('Operation'),
      '#options' => array(
        'ST_Contains' => t('Contains'), 
        'ST_Intersects' => t('Intersects'), 
        'ST_Disjoint' => t('Disjoint'),
      ),
      '#description' => t('This will be the way the relationship is determined.'),
      '#default_value' => $this->options['operation'] ? $this->options['operation'] : 'ST_Contains',
    );

    $form['origin'] = array(
      '#type' => 'select',
      '#title' => t('Origin'),
      '#options' => array(
        'nid_arg' => t('Node ID from contextual filter'),
      ),
      '#description' => t('This will be the way the geometry of origin is determined.'),
      '#default_value' => $this->options['origin'] ? $this->options['origin'] : 'nid_arg',
    );

    $nid_arg_options = array();
    $arguments = $this->view->display_handler->get_handlers('argument');
    foreach ($arguments as $id => $handler) {
      if ($handler->field == 'nid') {
        $nid_arg_options[$id] = $handler->ui_name();
      }
    }
    $form['value']['nid_arg'] = array(
      '#type' => 'select',
      '#title' => t('Contextual filter'),
      '#options' => $nid_arg_options,
      '#default_value' => $this->value['nid_arg'],
      '#description' => t('Select which of the contextual filters to use as the node ID.'),
      '#dependency' => array('edit-options-origin' => array('nid_arg')),
      '#weight' => 6,
    );

    $nid_postgis_field_options = array();
    $fields = field_info_fields();
    foreach ($fields as $field) {
      if ($field['module'] == 'postgis') {
        $nid_postgis_field_options[$field['field_name']] = $field['field_name'];
      }
    }
    $form['value']['nid_postgis_field'] = array(
      '#type' => 'select',
      '#title' => t('PostGIS field'),
      '#options' => $nid_postgis_field_options,
      '#default_value' => $this->value['nid_postgis_field'],
      '#description' => t('Select which of the node\'s PostGIS field to use as the origin.'),
      '#dependency' => array('edit-options-origin' => array('nid_arg')),
      '#weight' => 7,
    );
  }

  function query() {

    $nid_arg = $this->view->display_handler->get_handler('argument', $this->options['value']['nid_arg']);
    if (empty($this->value) || empty($nid_arg) || !in_array($this->options['operation'], $this->operations)) {
      return;
    }

    $nid = $nid_arg->get_value();
    if (empty($nid)) {
      return;
    }

    $this->ensure_my_table();

    $operation = $this->options['operation'];
    $field_geometry = db_escape_table($this->definition['field_name'] . '_geometry');
    $field_name = db_escape_table($this->options['value']['nid_postgis_field'] . '_geometry');
    $table_name = db_escape_table('field_data_' . $this->options['value']['nid_postgis_field']);
    $where = "$operation((select $field_name from $table_name where entity_id = :nid), $this->table_alias.$field_geometry)";

    $this->query->add_where_expression($this->options['group'], $where, array(':nid' => $nid));
  }
}
