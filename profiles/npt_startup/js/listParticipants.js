jQuery(document).ready(function() {

  jQuery("#edit-participant-type").change(function() {

    var nodeType = jQuery(this).val();
    var list = Drupal.settings.npt_startup[nodeType];
    var typeLabel = jQuery("#edit-participant-type option:selected").text();
    var nodeSelect = jQuery('#edit-node-uuid');
    
    jQuery("label[for=edit-node-uuid]").text("GBIF " + typeLabel);
    nodeSelect.empty();
    jQuery.each(list, function(uuid, node) {
      nodeSelect.append(jQuery("<option/>", {
        value: uuid,
        text: node
      }));
    });
    nodeSelect.trigger("chosen:updated");
  });

});
