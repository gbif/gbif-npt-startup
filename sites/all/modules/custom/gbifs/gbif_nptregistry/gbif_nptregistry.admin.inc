<?php
/**
 * @file
 * Administration page callbacks for the GBIF Registry module.
 */

/**
 * Form builder. Configure GBIF Registry Forms.
 *
 * @ingroup forms
 * @see system_settings_form().
 */

function gbif_nptregistry_admin_settings() {
  // Get an array of node types with internal names as keys and
  // "friendly names" as values. E.g.,
  // array('page' => 'Basic Page', 'article' => 'Articles')
  $jsonurl = "http://gbrds.gbif.org/registry/node.json";
  $json = file_get_contents($jsonurl,0,null,null);
  $json_output = json_decode($json);
  foreach ($json_output as $node) {
    $nodes[$node->key] = $node->name;
  }

  asort($nodes);

//$nodes = ksort($options);
/*  $types = node_type_get_types();
  foreach($types as $node_type) {
    $options[$node_type->type] = $node_type->name;
  }
*/

  $form['gbif_nptregistry_org_list'] = array(
    '#type' => 'select',
    '#title' => t('Endorsed GBIF Nodes worldwide:'),
    '#options' => $nodes,
    '#default_value' => variable_get('gbif_registry_org_registered', array('page')),
    '#description' => t('Select the node against which this NPT/Drupal website will register.'),
  );

  $form['gbif_nptregistry_org_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Node Password:'),
    '#description' => t("Node password for verifying that you have rights to set up and manage this NPT/Drupal instance for a GBIF Node. If you don't know this, please contact the node manager to get it."),
  );
  
  $form['gbif_nptregistry_org_publishpermitted'] = array(
    '#type' => 'checkbox',
    '#title' => t('Can publish resources'),
  );

  $form['gbif_nptregistry_org_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title for this NPT/Drupal Installation:'),
    '#description' => t("The title will be used for identifying this NPT/Drupal instance in the GBIF Registry"),
  );
  
  $form['gbif_nptregistry_org_description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description for this NPT/Drupal installation:'),
  );
  
  $form['gbif_nptregistry_org_contact_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Contact Name:'),
  );  

  $form['gbif_nptregistry_org_contact_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Contact Email:'),
  );  
  
/*  $form['gbif_registry_deletion'] = array(
    '#type' => 'radios',
    '#title' => t('The organisation will be deleted'),
    '#description' => t('Select a method for deleting organisation.'),
    '#options' => array(
      t('Never'),
      t('Randomly'),
      t('After 30 days')
    ),
  '#default_value' => variable_get('gbif_registry_deletion', 0) // Default to Never
  );
  $form['gbif_registry_limit_per_node'] = array(
    '#type' => 'textfield',
    '#title' => t('Annotations per node'),
    '#description' => t('Enter the maximum number of annotations allowed per node (0 for no limit).'),
    '#default_value' => variable_get('annotate_limit_per_node', 1),
    '#size' => 3
  );
*/  

  $form['#submit'][] = 'gbif_nptregistry_admin_settings_submit';
  return system_settings_form($form, TRUE);

}

/**
 * Process gbif_nptregistry settings submission.
 * WARNING: Test function drafted from a book example. To be worked.
 */
function gbif_nptregistry_admin_settings_submit($form, $form_state) {
  // Loop through each of the content type checkboxes shown on the form.
  foreach ($form_state['values']['gbif_nptregistry_node_types'] as $key => $value) {
    // If the check box for a content type is unchecked, look to see whether
    // this content type has the annotation field attached to it using the
    // field_info_instance function. If it does then we need to remove the
    // annotation field as the administrator has unchecked the box.
    if (!$value) {
      $instance = field_info_instance('node', 'annotation', $key);
      if (!empty($instance)) {
        field_delete_instance($instance, false);
        watchdog("GBIF NPT Registry", 'Deleted annotation field from content type:
          %key', array('%key' => $key));
      }
    } else {
      // If the check box for a content type  is checked, look to see whether
      // the field is associated with that content type. If not then add the
      // annotation field to the content type.
      $instance = field_info_instance('node', 'annotation', $key);
      if (empty($instance)) {
        $instance = array(
          'field_name' => 'organisation',
          'entity_type' => 'node',
          'bundle' => $key,
          'label' => t('Organisation'),
          'widget_type' => 'text_textarea_with_summary',
          'settings' => array('display_summary' => TRUE),
          'display' => array(
            'default' => array(
              'type' => 'text_default',
            ),
            'teaser' => array(
              'type' => 'text_summary_or_trimmed',
            ),
        ),
      );
      $instance = field_create_instance($instance);
      watchdog('Annotation', 'Added annotation field to content type: %key',
        array('%key' => $key));
      }
    }
  } // End foreach loop.
}