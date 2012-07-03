var regionsURL = Drupal.settings.gbif_region;
var dataTable = '<table cellpadding="0" cellspacing="0" border="0" class="display" id="dataGrid"><thead><tr><th>Node</th><th>Status</th><th>Node</th><th>Org Nr.</th><th>Res.</th><th>IPT</th><th>chk dst</th><th>chk usg</th><th>Provider</th><th>Occu dst</th><th>Occu</th><th>Geo Occu</th></tr></thead><tbody><tr><th></th><th></th><th></th><th></th><th></th><th></th><th></th><th></th><th></th><th></th><th></th><th></th></tr></tbody></table>';
var jsonLocation = Drupal.settings.json_location;
var destForTable = Drupal.settings.json_location.forTable;
var destForChart = Drupal.settings.json_location.forChart;
var destForMembership = Drupal.settings.json_location.membership;
var destForGeo = Drupal.settings.json_location.geo;

jQuery(document).ready(function() {
  var region = window.location.hash.substring(1);
  
  jQuery(".menu").append('<li><input id="toggle-map" type="button" value="hide map" /></li>');
  jQuery("#zone-content-wrapper").before('<div id="zone-preface-wrapper" class="zone-wrapper zone-preface-wrapper clearfix"><div id="zone-preface" class="zone zone-preface clearfix container-24"><div id="map"></div></div></div>');
  jQuery("#zone-preface-wrapper").hide().delay(800).slideDown();
  jQuery("#zone-preface").append('<h1 id="map-title">GBIF Membership</h1>');
  jQuery("#zone-preface").append('<div id="regional-map-menu-wrapper"></div>');

  jQuery('<ul/>').attr('id', 'map-region-menu').appendTo("#regional-map-menu-wrapper");
  
  jQuery("#page-title").remove();
  jQuery("#breadcrumb").remove();

  jQuery.each(regionsURL, function(index, value) {
    jQuery('<li/>').addClass(index).append(value).appendTo("#map-region-menu");
  });
  
  jQuery("#map-region-menu").appendTo("#regional-map-menu-wrapper");

  jQuery("#toggle-map").click(function() {
    jQuery("#zone-preface-wrapper").slideToggle('normal', function() {
      if (jQuery(this).is(':hidden')) {
        jQuery("#toggle-map").attr("value", "show map");
      } else {
        jQuery("#toggle-map").attr("value", "hide map");
      }
    });
  });

  // If a anchor variable is available in the url, attach the data table.

  if (region) {
    jQuery("#region-content").append(dataTable);
    chart(destForChart[region]);
    dataGrid(destForTable[region]);
    createMap(region);
  }
  
  
  jQuery("li").click(function() {
    if (jQuery("#dataGrid").length == 0 ) {
      jQuery("#region-content").append(dataTable);      
    } else if (jQuery("#dataGrid").length > 0 ) {
      jQuery("#dataGrid_wrapper").remove();
      jQuery("#region-content").append(dataTable);
      jQuery("svg.chart").remove();
      jQuery("svg.mapvector").remove();
    }
    
    region = jQuery(this).attr("class");
    chart(destForChart[region]);
    dataGrid(destForTable[region]);
    createMap(region);
  });    
  
});

function chart(dest) {
  d3.json(dest, function(data) {
    var width = 895;
    var canvasWidth = 940;
    var height = 420;
    var canvasHeight = 450;
    var padding = 20;
    var barWidth = (width / data.length) - 10;

    var x = d3.scale.linear().
      domain([0, data.length]).
      range([0, width]);
    var y = d3.scale.linear().
      domain([0, d3.max(data, function(d) { return d.occurrenceCount + 200000; })]).
      rangeRound([0, height - 100]);

    var published = d3.select("#chart").
      append("svg:svg").
      attr("class", "chart").
      attr("width", canvasWidth).
      attr("height", canvasHeight);

    var barGroup = published.append("svg:g").attr("transform", "translate("+padding+", "+padding+")");

    barGroup.selectAll("rect").
      data(data).
      enter().
      append("svg:rect").
      attr("x", function(d, i) { return x(i); }).
      attr("y", height - 100).
      attr("width", barWidth).
      attr("height", 0).
      attr("fill", "#679ED2").
      transition().
        delay(100).
        duration(750).
        attr("height", function(d) { return y(d.occurrenceCount); }).
        attr("y", function(d) { return height - 100 - y(d.occurrenceCount); });

    barGroup.selectAll("text").
      data(data).
      enter().
      append("svg:text").
      attr("x", function(d, i) { return x(i); }).
      attr("y", function(d) { return height - 100 - y(d.occurrenceCount); }).
      attr("dx", barWidth/2).
      attr("dy", "-0.4em").
      attr("text-anchor", "middle").
      text(function(d) { return d.occurrenceCount;}).
      attr("style", "font-size: 12; font-family: Helvetica, sans-serif;").
      attr("fill", "grey");

    var yAxis = published.append("svg:g");
      yAxis.selectAll("yAxis").
        data(data).
        enter().append("svg:text").
        attr("x", 0).
        attr("y", 0).
        attr("text-anchor", "end").
        attr("transform", function(d, i){ return "translate("+(x(i)+padding+(barWidth/2))+" "+ (height - 60) +") rotate(-40)";}).
        attr("style", "font-size: 12; font-family: Helvetica, sans-serif;").
        text(function(d) { return d.nodeTitle;}).
        attr("class", "yAxis");

    var rules = published.append("g").attr("transform", "translate("+padding+", "+padding+")");
      rules = rules.selectAll(".rule").
        data(y.ticks(10)).
        enter().append("g").
        attr("class", "rule").
        attr("transform", function(d) { return "translate(0, " + (height -100 - y(d)) + ")"; });
      rules.
        append("line").
        attr("x2", width - 10).
        attr("stroke", "lightgray");
      rules.
        append("text").
        attr("x", width+25).
        attr("dy", ".35em").
        attr("style", "font-size: 12; font-family: Helvetica, sans-serif;").
        attr("text-anchor", "end").
        text(function(d) { return (Math.round(d / 1e5)/10).toFixed(1) + "M"; });
  });
  
}

function numberFormat(data) {
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

function dataGrid(dest) {
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
        { "aTargets": [6], "mDataProp": "ChecklistDataset", "sClass": "alignRight" },
        { "aTargets": [7], "sClass": "alignRight", "mDataProp": function (source, type, val) {
          if (type === 'set') {
    					// Store the base value
    					source.ChecklistRecord = val;

    					// Display is formatted with a dollar sign and number formatting
    					source.ChecklistRecord_display = val==="" ? "" : numberFormat(val);

    					// Filtering can occur on the formatted number, or the value alone
    					source.ChecklistRecord_filter  = val==="" ? "" : source.occurrenceCount_display+" "+val;
    					return;
    				}
    				else if (type === 'display') {
    					return source.ChecklistRecord_display;
    				}
    				else if (type === 'filter') {
    					return source.ChecklistRecord_filter;
    				}
    				// 'sort', 'type' and undefined all just use the integer
    				return source.ChecklistRecord;
        } },
        { "aTargets": [8], "mDataProp": "providerCount", "sClass": "alignRight" },
        { "aTargets": [9], "mDataProp": "datasetCount", "sClass": "alignRight" },
        { "aTargets": [10], "sClass": "alignRight", "mDataProp": function (source, type, val) {
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
        { "aTargets": [11], "sClass": "alignRight", "mDataProp": function (source, type, val) {
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
}




function createMap(region) {
    var geoLayoutParams = {
      africa: {
        "origin": [20, 5],
        "scale": 500,
        "translate": [680, 360]
      },
      asia: {
        "origin": [120, 10],
        "scale": 500,
        "translate": [680, 360]
      },
      europe: {
        "origin": [22, 45],
        "scale": 800,
        "translate": [680, 360]
      },
      lamerica: {
        "origin": [-65, -10],
        "scale": 300,
        "translate": [680, 360]
      },
      namerica: {
        "origin": [-100, 35],
        "scale": 600,
        "translate": [680, 360]
      },
      oceania: {
        "origin": [160, -30],
        "scale": 500,
        "translate": [680, 360]
      }
    };
    
    var path = d3.geo.path()
      .projection(d3.geo.albers()
          .origin(geoLayoutParams[region].origin)
          .scale(geoLayoutParams[region].scale)
          .translate(geoLayoutParams[region].translate));

    var svg = d3.select("#map").append("svg:svg")
      .attr("class", "Blues mapvector")
      .attr("width", 1160)
      .attr("height", 480);

    var counties = svg.append("svg:g")
      .attr("id", "counties");

  d3.json(destForMembership[region], function(data) {
    var pad = d3.format("02,"), quantize = d3.scale.quantile().domain([0, 36215834]).range(d3.range(9));

    d3.json(destForGeo[region], function(json) {
    
      counties.selectAll("path")
          .data(json.features)
        .enter().append("svg:path")
          .attr("class", function(d) { 
            var count = data.country[d.name];
            if (typeof(count) === "undefined") {
              return "non-member";
            } else {
              return "q" + quantize(count.stats.occurrence_count) + "-9"; 
            }
          })
          .attr("d", path)

        .append("svg:title")
          .text(function(d) { return d.name + ": " + d.iso_a2; });

          jQuery('svg path').tipsy({
             gravity: 'w',
             html: true,
             title: function(d) {
                 var d = this.__data__;
                 var count = data.country[d.name];
                 if (typeof(count) === "undefined") {
                     return d.name + ": non member";
                 } else {
                     return d.name + ": <br />" + count.GBIFMembership + "<br />"
                     + count.agents.Node + " node(s).<br />"
                     + count.agents.Org + " organisation(s).<br />"
                     + count.agents.Resource + " resource(s).<br />"
                     + count.stats.provider_count + " provider(s).<br />"
                     + count.agents.ChecklistDataset + " checklist(s). <br />"
                     + count.agents.ChecklistRecord + " name(s). <br />"
                     + count.stats.dataset_count + " dataset(s).<br />"
                     + pad(count.stats.occurrence_count) + " records.<br />"
                     + pad(count.stats.occurrence_georeferenced_count) + " georeferended.<br />";
                 }
             } 
          });
    });
  });
};
