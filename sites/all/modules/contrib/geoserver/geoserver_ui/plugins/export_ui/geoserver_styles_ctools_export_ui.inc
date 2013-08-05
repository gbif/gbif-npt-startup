<?php
/**
 * @file
 * Define the Export UI plugin for GeoServer Styles.
 */

$plugin = array(
  'schema' => 'geoserver_styles',
  'access' => 'administer geoserver',
  'menu' => array(
    'menu prefix' => 'admin/structure/geoserver',
    'menu item' => 'styles',
    'menu type' => MENU_LOCAL_TASK,
    'menu title' => 'Styles',
    'menu description' => 'Administer GeoServer Styles presets.',
  ),

  'handler' => array(
    'class' => 'geoserver_styles_ui',
  ),

  'export' => array(
    'admin_title' => 'name',
    'admin_description' => 'description',
  ),

  'title singular' => t('style'),
  'title plural' => t('styles'),
  'title singular proper' => t('GeoServer Style preset'),
  'title plural proper' => t('GeoServer Styles presets'),

  'strings' => array(
    'confirmation' => array(
      'add' => array(
        'success' => t('Style added.'),
        'fail' => t('Failed to completely add style. See the log for details.'),
      ),
      'edit' => array(
        'success' => t('Style updated.'),
        'fail' => t('Failed to completely update style. See the log for details.'),
       ),
      'delete' => array(
        'success' => t('Style was deleted.'),
        'fail' => t('Failed to completely delete style. See the log for details.'),
      )
    )
  ),

  'form' => array(
    'settings' => 'geoserver_styles_ctools_export_ui_form_settings',
  ),
);

function geoserver_styles_ctools_export_ui_form_settings(&$form, &$form_state) {

  $style = $form_state['item'];
  if (empty($style->name)) {
    $style = NULL;
  }

  if ($form_state['op'] == 'add'||'edit') {
    $form = array();
    $form['title'] = array(
      '#type' => 'textfield',
      '#title' => t('Style Title'),
      '#required' => TRUE,
      '#size' => 30,
      '#default_value' => isset($style->title) ? $style->title : '',
      '#description' => t('The friendly name of your style, which will appear in the administration interface.'),
    );
    $form['name'] = array(
      '#type' => 'machine_name',
      '#maxlength' => 32,
      '#machine_name' => array(
        'exists' => 'geoserver_style_load',
        'source' => array('title'),
      ),
      '#default_value' => isset($style->name) ? $style->name : '',
      '#description' => t('This is the unique name of the style. It must contain only alphanumeric characters and underscores.'),
    );
    $form['description'] = array(
      '#type' => 'textfield',
      '#title' => t('Style Description'),
      '#default_value' => isset($style->description) ? $style->description : '',
      '#description' => t('The description of your style, which will appear in the administration interface.'),
    );
    $form['data'] = array(
      '#type' => 'textarea',
      '#title' => t('SLD'),
      '#description' => t('Styled Layer Descriptor (SLD)'),
      '#default_value' => isset($style->data) ? $style->data : '',
    );
  }
}
