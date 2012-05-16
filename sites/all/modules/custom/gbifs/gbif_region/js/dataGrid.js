var dest = Drupal.settings.gbif_region.forTable;

jQuery(document).ready(function() {
  var oTable = jQuery('#dataGrid').dataTable( {
    "iDisplayLength": 15,
    "bFilter": false,
    "bAutoWidth": false,
    "bLengthChange": false,
    "bProcessing": true,
    "sAjaxSource": dest,
    "aoColumns": [
        { "mDataProp": "nodeTitle" },
        { "mDataProp": "GBIFMembership" },
        { "mDataProp": "nodeCount", sClass: "alignRight" },
        { "mDataProp": "orgCount", sClass: "alignRight" },
        { "mDataProp": "resourceCount", sClass: "alignRight" },
        { "mDataProp": "IPTCount", sClass: "alignRight" },
        { "mDataProp": "providerCount", sClass: "alignRight" },
        { "mDataProp": "datasetCount", sClass: "alignRight" },
        { "mDataProp": "occurrenceCount", sClass: "alignRight" },
        { "mDataProp": "occurrenceGeoCount", sClass: "alignRight" }
    ]
  });
});
