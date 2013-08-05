<?php
/**
 * @file
 * Define the Export UI plugin for GeoServer Layers.
 */

$plugin = array(
  'schema' => 'geoserver_layers',
  'access' => 'administer geoserver',
  'menu' => array(
    'menu prefix' => 'admin/structure/geoserver',
    'menu item' => 'layers',
    'menu type' => MENU_LOCAL_TASK,
    'menu title' => 'Layers',
    'menu description' => 'Administer GeoServer Layers.',
  ),

  'handler' => array(
    'class' => 'geoserver_layers_ui',
  ),

  'export' => array(
    'admin_title' => 'name',
    'admin_description' => 'description',
  ),

  'title singular' => t('layer'),
  'title plural' => t('layers'),
  'title singular proper' => t('GeoServer Layer'),
  'title plural proper' => t('GeoServer Layers'),

  'strings' => array(
    'confirmation' => array(
      'add' => array(
        'success' => t('Layer added.'),
        'fail' => t('Failed to completely add layer. See the log for details.'),
      ),
      'edit' => array(
        'success' => t('Layer updated.'),
        'fail' => t('Failed to completely update layer. See the log for details.'),
      ),
      'delete' => array(
        'success' => t('Layer was deleted.'),
        'fail' => t('Failed to completely delete layer. See the log for details.'),
      )
    )
  ),

  'form' => array(
    'settings' => 'geoserver_layers_ctools_export_ui_form_settings',
  ),
);

function geoserver_layers_ctools_export_ui_form_settings(&$form, &$form_state) {

  $layer_object = geoserver_get_layer_object($form_state['item']);

  if ($form_state['op'] == 'add'||'edit') {
    $form = array();

    $styles = array('');
    foreach (geoserver_styles() as $style) {
      $styles[$style->name] = $style->title;
    }

    $form['layer']['basics'] = array(
      '#tree' => TRUE,
      '#type' => 'fieldset',
      '#title' => t('Layer Basics'),
      '#description' => t('The following settings are for all layers.'),
      '#tree' => FALSE,
    );
    $form['layer']['basics']['title'] = array(
      '#type' => 'textfield',
      '#title' => t('Layer Title'),
      '#required' => TRUE,
      '#size' => 30,
      '#default_value' => isset($layer_object->title) ? $layer_object->title : '',
      '#description' => t('The friendly name of your layer, which will appear in the administration interface.'),
    );
    $form['layer']['basics']['name'] = array(
      '#type' => 'machine_name',
      '#maxlength' => 32,
      '#machine_name' => array(
        'exists' => 'geoserver_layer_load',
        'source' => array('layer', 'basics', 'title'),
      ),
      '#default_value' => isset($layer_object->name) ? $layer_object->name : '',
      '#description' => t('This is the unique name of the layer. It must contain only alphanumeric characters and underscores.'),
    );
    $form['layer']['basics']['description'] = array(
      '#type' => 'textfield',
      '#title' => t('Layer Description'),
      '#default_value' => isset($layer_object->description) ? $layer_object->description : '',
      '#description' => t('The description of your layer, which will appear in the administration interface.'),
    );

    $layers_options = array();
    $layer_types = geoserver_layer_types();
    $layer_type_options = array('' => t('Select the layer type'));

    foreach ($layer_types as $layer_type) {

      $layer_type_name = $layer_type['name'];
      if (isset($layer_object->data) && $layer_object->data['type'] == $layer_type_name) {
        $layer = $layer_object;
      } else {
        $layer = geoserver_layer_type_load($layer_type_name);
      }

      $layers_option = array(
        '#tree' => TRUE,
        '#type' => 'fieldset',
        '#title' => t('Layer Configuration'),
      );

      $layers_option['type'] = array(
        '#type' => 'hidden',
        '#value' => $layer_type_name,
      );

      $layers_option['style'] = array(
        '#type' => 'select',
        '#title' => t('Style'),
        '#options' => $styles,
        '#default_value' => isset($layer->data['style']) ? $layer->data['style'] : '',
        '#description' => t('Please select a default style for this layer.'),
      );

      $layers_option['source'] = array(
        '#type' => 'select',
        '#title' => t('Source'),
        '#options' => call_user_func($layer_type_name . '::get_sources'),
        '#default_value' => isset($layer->data['source']) ? $layer->data['source'] : '',
        '#description' => t('Please select a source for this layer.'),
        '#ajax' => array(
          'callback' => 'geoserver_layers_ui_type_form',
          'wrapper' => $layer_type_name,
        ),
      );

      $layers_option['attribution'] = array(
        '#type' => 'textfield',
        '#title' => t('Layer Attribution'),
        '#default_value' => isset($layer->data['attribution']) ? $layer->data['attribution'] : '',
        '#description' => t('The attribution of your layer.'),
      );

      if (module_exists('openlayers')) {
        $openlayers = isset($layer->data['openlayers']) ? $layer->data['openlayers'] : array();
        $openlayers_layer = new openlayers_layer_type();

        $wfs_data = isset($openlayers['wfs_data']) ? array('data' => $openlayers['wfs_data']) : array();
        $gwc_data = isset($openlayers['gwc_data']) ? array('data' => $openlayers['gwc_data']) : array();
        $wms_data = isset($openlayers['wms_data']) ? array('data' => $openlayers['wms_data']) : array();

        $layers_option['openlayers'] = array(
          '#type' => 'fieldset',
          '#title' => t('OpenLayers'),
          '#description' => t('Select how you want to have this layer available in maps of the OpenLayers module. Note that raster data is only available for inclusion in the OpenLayers module if the projection chosen here matches the OpenLayers map in question.'),
          'wfs' => array(
            '#type' => 'checkbox',
            '#title' => t('Provide an OpenLayers WFS layer.'),
            '#default_value' => isset($openlayers['wfs']) ? $openlayers['wfs'] : '',
            '#description' => t('This makes your layer\'s content available as vector data.'),
          ),
          'wfs_data' => array(
            '#type' => 'fieldset',
            '#title' => t('WFS layer options'),
            '#prefix' => '<div style="padding-left:20px">',
            '#suffix' => '</div>',
            '#states' => array(
              'visible' => array(
                ':input[name="' . $layer_type_name . '[openlayers][wfs]"]' => array(
                  'checked' => TRUE,
                ),
              ),
            ),
            'strategy' => array(
              '#type' => 'select',
              '#title' => t('Strategy'),
              '#options' => array(
                'bbox' => 'Bounding Box',
                'fixed' => 'Fixed',
              ),
              '#default_value' => isset($wfs_data['data']['strategy']) ? $wfs_data['data']['strategy'] : 'bbox',
              '#description' => t('Define the data loading strategy. "Fixed" will load all data initially, "Bounding Box" only loads data for the current map extent.'),
            ),
          ) + $openlayers_layer->options_form((object)$wfs_data),
          'gwc' => array(
            '#type' => 'checkbox',
            '#title' => t('Provide a cached OpenLayers WMS layer.'),
            '#default_value' => isset($openlayers['gwc']) ? $openlayers['gwc'] : '',
            '#description' => t('Creates a layer that transmits its data using several small adjacent images.'),
          ),
          'gwc_data' => array(
            '#type' => 'fieldset',
            '#title' => t('Cached WMS layer options'),
            '#prefix' => '<div style="padding-left:20px">',
            '#suffix' => '</div>',
            '#states' => array(
              'visible' => array(
                ':input[name="' . $layer_type_name . '[openlayers][gwc]"]' => array(
                  'checked' => TRUE,
                ),
              ),
            ),
          ) + $openlayers_layer->options_form((object)$gwc_data),
          'wms' => array(
            '#type' => 'checkbox',
            '#title' => t('Provide an untiled OpenLayers WMS layer.'),
            '#default_value' => isset($openlayers['wms']) ? $openlayers['wms'] : '',
            '#description' => t('Creates a layer that transmits its data using one image that spans the entire map.'),
          ),
          'wms_data' => array(
            '#type' => 'fieldset',
            '#title' => t('WMS layer options'),
            '#prefix' => '<div style="padding-left:20px">',
            '#suffix' => '</div>',
            '#states' => array(
              'visible' => array(
                ':input[name="' . $layer_type_name . '[openlayers][wms]"]' => array(
                  'checked' => TRUE,
                ),
              ),
            ),
          ) + $openlayers_layer->options_form((object)$wms_data),
        );
      }

      $layers_option['options'] = array(
        '#type' => 'fieldset',
        '#title' => t('Layer Specifics'),
        '#description' => t('The following settings are specific to the layer type.'),
      );

      // Arrays merged in order so that options_form can override defaults.
      //$layers_option['options'] = $layer->options_form() + $layers_option['options'];
      if (method_exists($layer, 'options_form')) {
        $layers_option['options'] += $layer->options_form();
        $layers_option['#states'] = array(
          'visible' => array(
            ':input[name="layer_type"]' => array('value' => $layer_type_name),
          ),
        );
        $layers_options[$layer_type_name] = $layers_option;
      }
      $layer_type_options[$layer_type_name] = $layer_type['title'];
    }

    $form['layer']['layer_type'] = array(
      '#type' => 'select',
      '#title' => t('Layer Type'),
      '#default_value' => isset($layer_object->data['type']) ? $layer_object->data['type'] : '',
      '#description' => t('Select the type of layer.'),
      '#options' => $layer_type_options,
    );

    $form['layer'] += $layers_options;
    
  }
}


