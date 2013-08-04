// $Id

/**
 * @file
 * Main JS file for geofield
 *
 * @ingroup geofield
 */

(function($) {
/**
 * This behaviour moves the map into a new column on the right side.
 * In addition it zooms to the layer "openlayers_drawfeatures_layer".
 */
Drupal.behaviors.openlayers_behavior_ole = {
  'attach': function(context, settings) {

    function openlayers_behavior_ole_control_group(controls, seperator) {
      var arr = [];
      for (var i in controls) {
        if (controls[i]) {
          arr.push(i);
        }
      }
      if (arr.length > 0) {
        arr.push('Separator');
      }
      return arr;
    }

    // Callback function that handles changes of map features.
    function openlayers_behavior_ole_update(event) {

      // limit number of features to field cardinality
      while (event.type == 'featureadded' && behavior.feature_limit &&
        (behavior.feature_limit < event.object.features.length)) {
        event.feature.layer.removeFeatures(event.object.features.shift(), {silent: false});
      }

      // Write features as WKT to form field.
      element.val(wktFormat.write(event.object.features)).trigger('change');
    }

    var data = $(context).data('openlayers'),
        wktFormat = new OpenLayers.Format.WKT(),
        feature_types = [],
        element, behavior, processing_controls, editing_controls, other_controls;
    if (data) {

      behavior = data.map.behaviors['openlayers_behavior_ole'];
      element = $('#' + behavior.element_id);

      // Ensure the ModifyFeature control is present
      if (!('ModifyFeature' in behavior.editing_controls) || 
        behavior.editing_controls.ModifyFeature === 0) {
        behavior.editing_controls.ModifyFeature = 'ModifyFeature';
      }

      // Add select feature if any processing control is configured since they needs a selection to know which geometry to process
      var has_processing_controls = false;
      for(var control in behavior.processing_controls) {
        if (behavior.processing_controls[control]){
          has_processing_controls = true;
          break;
        }
      }
      if (has_processing_controls) {
        behavior.processing_controls.SelectFeature = 'SelectFeature';
      }
      
      processing_controls = openlayers_behavior_ole_control_group(behavior.processing_controls);
      editing_controls = openlayers_behavior_ole_control_group(behavior.editing_controls);
      other_controls = openlayers_behavior_ole_control_group(behavior.other_controls);

      for(var i in data.map.behaviors['openlayers_behavior_ole'].feature_types) {
        feature_types.push(data.map.behaviors['openlayers_behavior_ole'].feature_types[i]);
      }

      // Apply Drupal's styles to form fields in order to make up for the CSS-reset that makes ordinary form fields indistinguishable from text
      OpenLayers.Editor.Control.Dialog.prototype.inputTextClass = "form-text";
      OpenLayers.Editor.Control.Dialog.prototype.buttonClass = "form-submit";
      
      var editor = new OpenLayers.Editor(data.openlayers, {
        showStatus: function(message) {console.log(message);},
        activeControls: other_controls.concat(processing_controls).concat(editing_controls),
        featureTypes: feature_types,
        featureLimit: data.map.behaviors['openlayers_behavior_ole'].feature_limit,
        oleUrl: Drupal.settings.basePath + '?q=admin/structure/openlayers/editor/callbacks/'
      });

      editor.editLayer.events.register('featureadded', this, openlayers_behavior_ole_update);
      editor.editLayer.events.register('featuremodified', this, openlayers_behavior_ole_update);
      editor.editLayer.events.register('afterfeaturemodified', this, openlayers_behavior_ole_update);
      editor.editLayer.events.register('featureremoved', this, openlayers_behavior_ole_update);
      
      var features = wktFormat.read(element.text());
      if (features) {
        if (features.constructor !== Array) {
          features = [features];
        }
        editor.loadFeatures(features);
      }
      editor.startEditMode();

    }
  }
};
})(jQuery);
