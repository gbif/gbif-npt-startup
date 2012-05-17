var dest = Drupal.settings.gbif_region.forTable;

function numberFormat( data ) {
	if ( data < 1000 ) {
		// A small optimisation for what is likely to be the majority of use cases
		return data;
	}

	var s=(data+""), a=s.split(""), out="", iLen=s.length;
	
	for ( var i=0 ; i<iLen ; i++ ) {
		if ( i%3 === 0 && i !== 0 ) {
			out = ','+out;
		}
		out = a[iLen-i-1]+out;
	}
	return out;
}

jQuery(document).ready(function() {
  var oTable = jQuery('#dataGrid').dataTable( {
    "iDisplayLength": 15,
    "bFilter": false,
    "bAutoWidth": false,
    "bLengthChange": false,
    "bProcessing": true,
    "sAjaxSource": dest,
    "aoColumnDefs": [
        { "aTargets": [0], "mDataProp": "nodeTitle" },
        { "aTargets": [1], "mDataProp": "GBIFMembership" },
        { "aTargets": [2], "mDataProp": "nodeCount", "sClass": "alignRight" },
        { "aTargets": [3], "mDataProp": "orgCount", "sClass": "alignRight" },
        { "aTargets": [4], "mDataProp": "resourceCount", "sClass": "alignRight" },
        { "aTargets": [5], "mDataProp": "IPTCount", "sClass": "alignRight" },
        { "aTargets": [6], "mDataProp": "providerCount", "sClass": "alignRight" },
        { "aTargets": [7], "mDataProp": "datasetCount", "sClass": "alignRight" },
        { "aTargets": [8], "sClass": "alignRight", "mDataProp": function (source, type, val) {
          if (type === 'set') {
    					// Store the base value
    					source.occurrenceCount = val;

    					// Display is formatted with a dollar sign and number formatting
    					source.occurrenceCount_display = val==="" ? "" : numberFormat(val);

    					// Filtering can occur on the formatted number, or the value alone
    					source.occurrenceCount_filter  = val==="" ? "" : source.occurrenceCount_display+" "+val;
    					return;
    				}
    				else if (type === 'display') {
    					return source.occurrenceCount_display;
    				}
    				else if (type === 'filter') {
    					return source.occurrenceCount_filter;
    				}
    				// 'sort', 'type' and undefined all just use the integer
    				return source.occurrenceCount;
        } },
        { "aTargets": [9], "sClass": "alignRight", "mDataProp": function (source, type, val) {
          if (type === 'set') {
    					// Store the base value
    					source.occurrenceGeoCount = val;

    					// Display is formatted with a dollar sign and number formatting
    					source.occurrenceGeoCount_display = val==="" ? "" : numberFormat(val);

    					// Filtering can occur on the formatted number, or the value alone
    					source.occurrenceGeoCount_filter  = val==="" ? "" : source.occurrenceGeoCount_display+" "+val;
    					return;
    				}
    				else if (type === 'display') {
    					return source.occurrenceGeoCount_display;
    				}
    				else if (type === 'filter') {
    					return source.occurrenceGeoCount_filter;
    				}
    				// 'sort', 'type' and undefined all just use the integer
    				return source.occurrenceGeoCount;
        } }
    ],
    "fnInfoCallback": function(oSettings, iStart, iEnd, iMax, iTotal, sPre){
      var info = "Showing "+iStart +" to "+ iEnd+" of "+iTotal+" entries.<br/>";
      var legend = '<span style="font-size:0.9em;color:#888;">VP: Voting Participant<br/>ACP: Associate Country Participant<br/>OAP: Other Associate Participant</span>';
      return info+legend;
    }
  });
});


