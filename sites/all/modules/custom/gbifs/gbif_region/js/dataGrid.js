var dest = Drupal.settings.gbif_region;

jQuery(document).ready(function() {
  jQuery('#dataGrid').dataTable( {
    "bProcessing" : true,
    "sAjaxSource" : dest
  });
});