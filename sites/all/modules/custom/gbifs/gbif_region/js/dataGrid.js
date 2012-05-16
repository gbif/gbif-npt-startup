var dest = Drupal.settings.gbif_region.forTable;

jQuery(document).ready(function() {
  var oTable = jQuery('#dataGrid').dataTable( {
    "iDisplayLength": 15,
    "bProcessing": true,
    "sAjaxSource": dest,
    "aoColumns": [
        { "mDataProp": "nodeTitle" },
        { "mDataProp": "GBIFMembership" },
        { "mDataProp": "nodeCount" },
        { "mDataProp": "orgCount" },
        { "mDataProp": "resourceCount" },
        { "mDataProp": "IPTCount" },
        { "mDataProp": "providerCount" },
        { "mDataProp": "datasetCount" },
        { "mDataProp": "occurrenceCount" },
        { "mDataProp": "occurrenceGeoCount" }
    ]
  });
});
