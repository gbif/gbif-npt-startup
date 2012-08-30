var regionsURL = Drupal.settings.npt_nodestats;
var dataTableTitle = '<div id="dataTableTitle"><p>Membership status, registry information, and data moblised per GBIF Participants:</p></div>';
var dataTable = '<table cellpadding="0" cellspacing="0" border="0" class="display" id="dataGrid"><thead><tr><th>Node</th><th>Status</th><th>Node</th><th>Org Nr.</th><th>Res.</th><th>IPT</th><th>Chk dst</th><th>Chk usg</th><th>Publisher</th><th>Occu dst</th><th>Occu</th><th>Geo Occu</th></tr></thead><tbody><tr><th></th><th></th><th></th><th></th><th></th><th></th><th></th><th></th><th></th><th></th><th></th><th></th></tr></tbody></table>';
var publicationTable = '<div id="paper-publication" class="grid-16"><h3>Professional Publication</h3><p>Professional publications regarding GBIF mediated data.</p><div id="publicationChart"></div><table cellpadding="0" cellspacing="0" border="0" class="display" id="publicationTable"><thead><tr><th>Year</th><th>GBIF Used</th><th>GBIF Discussed</th><th>GBIF Mentioned</th><th>Other</th><th>Total</th></tr></thead><tbody><tr><th></th><th></th><th></th><th></th><th></th><th></th></tr></tbody><tfoot><tr><th></th><th></th><th></th><th></th><th></th><th></th></tr></tfoot></table></div>';
var jsonLocation = Drupal.settings.json_location;
var destForTable = Drupal.settings.json_location.forTable;
var destForMembership = Drupal.settings.json_location.membership;
var destForGeo = Drupal.settings.json_location.geo;
var destForPublication = Drupal.settings.json_location.publication_stats;
// var destForMembershiptype = Drupal.settings.json_location.membershiptype;
var membershipType = '{"type":[{"name":"Voting Participants","color":"green"},{"name":"Associate Country Participants","color":"yellow"},{"name":"Participants as of end-2011 yet to sign new MOU","color":"gray"}]}'

jQuery(document).ready(function() {
  var region = window.location.hash.substring(1);
  
  //jQuery(".menu").append('<li><input id="toggle-map" type="button" value="hide map" /></li>');
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

  /*
  jQuery("#toggle-map").click(function() {
    jQuery("#zone-preface-wrapper").slideToggle('normal', function() {
      if (jQuery(this).is(':hidden')) {
        jQuery("#toggle-map").attr("value", "show map");
      } else {
        jQuery("#toggle-map").attr("value", "hide map");
      }
    });
  });
  */
  // If a anchor variable is available in the url, attach the data table.

  if (region) {
    jQuery("#participant-list").hide();
    createMap(region);
    chart(destForTable[region]);
    jQuery("#region-content").append(dataTableTitle).append(dataTable);
    dataGrid(destForTable[region]);
  } else {
    createMembershipMap();
    jQuery("#zone-content").append(publicationTable);
    createPublicationChart(destForPublication.world);
    publicationGrid(destForPublication.world);
    
  }
  
  jQuery("#map-region-menu li").click(function() {
    if (jQuery("#dataGrid").length == 0 ) {
      jQuery("svg.mapvector").remove();  
    } else if (jQuery("#dataGrid").length > 0 ) {
      jQuery("#dataGrid_wrapper").remove();
      jQuery("svg.chart").remove();
      jQuery("svg.mapvector").remove();
      jQuery("#dataTableTitle").remove();
    }
    jQuery("#region-content").append(dataTableTitle).append(dataTable);
    jQuery("svg#legend").remove();
    jQuery("#publicationChart").remove();
    jQuery("#paper-publication").remove();
    
    region = jQuery(this).attr("class");
    jQuery("#participant-list").hide();
    chart(destForTable[region]);
    dataGrid(destForTable[region]);
    createMap(region);
  });    
  
});

function chart(dest) {
  
  jQuery("#chart").html("<p>Simple bar chart according to mobilised occurrence data per participant. (To be enriched.)</p>");
  d3.json(dest, function(json) {
    var data = json.aaData;
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

function createPublicationChart(dest) {
  d3.json(dest, function(data) {
    var width = 895;
    var canvasWidth = 940;
    var height = 420;
    var canvasHeight = 380;
    var padding = 20;
    var barWidth = 20;
    var data = data.aaData;
    var cate = ['GBIF_used', 'GBIF_discussed', 'GBIF_mentioned', 'other']
    var cateName = {'GBIF_used': 'GBIF Used', 'GBIF_discussed': 'GBIF Discussed', 'GBIF_mentioned': 'GBIF Mentioned', 'other': 'Other'}
    var columnWidth = ( width / cate.length ) - 30;
    
    var x = d3.scale.linear().
      domain([0, data.length]).
      range([0, width]);
    var y = d3.scale.linear().
      domain([0, d3.max(data, function(d) { return d.GBIF_used ; })]).
      rangeRound([0, height - 100]);

    var published = d3.select("#publicationChart").
      append("svg:svg").
      attr("class", "publication-chart").
      attr("width", canvasWidth).
      attr("height", canvasHeight);

    var yAxis = published.append("svg:g");
      yAxis.selectAll("yAxis").
        data(data).
        enter().append("svg:text").
        attr("x", 0).
        attr("y", 0).
        attr("text-anchor", "end").
        attr("transform", function(d, i){ return "translate("+(x(i)+padding+((columnWidth/2)-35))+" "+ (height - 60) +")";}).
        attr("style", "font-size: 12; font-family: Helvetica, sans-serif;").
        text(function(d) { return d.year;}).
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
        text(function(d) { return d; });
    
    
    cate.forEach(function(v, k) {
      var barGroup = published.append("svg:g").attr("transform", "translate("+padding+", "+padding+")").attr("class", v);
      barGroup.selectAll("rect").
        data(data).
        enter().
        append("svg:rect").
        attr("x", function(d, i) { return x(i) + (25 * k); }).
        attr("y", height - 100).
        attr("width", barWidth).
        attr("height", 0).
        attr("class", v).
        transition().
          delay(100).
          duration(750).
          attr("height", function(d) { return y(d[v]); }).
          attr("y", function(d) { return height - 101 - y(d[v]); });      

      barGroup.selectAll("text").
        data(data).
        enter().
        append("svg:text").
        attr("x", function(d, i) { return x(i) + (25 * k); }).
        attr("y", function(d) { return height - 100 - y(d[v]); }).
        attr("dx", barWidth/2).
        attr("dy", "-0.4em").
        attr("text-anchor", "middle").
        text(function(d) { return d[v];}).
        attr("style", "font-size: 12; font-family: Helvetica, sans-serif;").
        attr("fill", "grey");

    });
    var yLegend = d3.scale.linear().domain([0, cate.length]).range([0, 80]);
    var legendPublish = d3.select("#publicationChart").append("svg:svg").attr("id", "publicationChartLegend").attr("width", 300).attr("height", 100).append("svg:g");


      legendPublish.selectAll("rect")
          .data(cate)
        .enter()
          .append("svg:rect")
          .attr("x", 10)
          .attr("y",  function (d, i) { return yLegend(i) + 10 ; })
          .attr("width", 15)
          .attr("height", 15)
          .attr("class", function (d, i) { return d; });

      legendPublish.selectAll("text")
          .data(cate)
        .enter()
          .append("svg:text")
          .attr("x", 30)
          .attr("y", function (d, i) { return yLegend(i) + 22; })
          .text(function(d) { return cateName[d]; })
          .attr("style", "font-size: 12; font-family: Helvetica, sans-serif;");      
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
        "origin": [25, -20],
        "scale": 400,
        "translate": [680, 360],
        "fullname": "Africa"
      },
      asia: {
        "origin": [110, 2],
        "scale": 500,
        "translate": [680, 360],
        "fullname": "Asia"
      },
      europe: {
        "origin": [22, 45],
        "scale": 800,
        "translate": [680, 360],
        "fullname": "Europe"
      },
      lamerica: {
        "origin": [-65, -40],
        "scale": 400,
        "translate": [680, 360],
        "fullname": "Latin America"
      },
      namerica: {
        "origin": [-100, 35],
        "scale": 500,
        "translate": [680, 360],
        "fullname": "North America"
      },
      oceania: {
        "origin": [170, -40],
        "scale": 500,
        "translate": [780, 360],
        "fullname": "Oceania"
      }
    };
    
    jQuery("#map-title").html("GBIF "+geoLayoutParams[region].fullname);
    
    var projection = d3.geo.azimuthal()
        .mode("orthographic")
        .scale(geoLayoutParams[region].scale)
        .origin(geoLayoutParams[region].origin)
        .translate(geoLayoutParams[region].translate);
    
    var path = d3.geo.path()
        .projection(projection);
        
    var circle = d3.geo.circle()
        .origin(projection.origin());

    var svg = d3.select("#map").append("svg:svg")
      .attr("class", "Blues mapvector")
      .attr("width", 1160)
      .attr("height", 480);

    var counties = svg.append("svg:g")
      .attr("id", "counties");


  d3.json(destForMembership.world, function(data) {
    var pad = d3.format("02,"), quantize = d3.scale.quantile().domain([0, 36215834]).range(d3.range(9));

    d3.json(destForGeo.world, function(json) {
    
      counties.selectAll("path")
          .data(json.features)
        .enter().append("svg:path")
          .attr("class", function(d) { 
            var count = data.country[d.name];
            if (typeof(count) === "undefined") {
              return "non-publishing";
            } else {
              return "q" + quantize(count.stats.occurrence_count) + "-9"; 
            }
          })
          .attr("d", function(d) {
            return path(circle.clip(d))
          })

        .append("svg:title")
          .text(function(d) { return d.name + ": " + d.iso_a2; });

          jQuery('svg path').mouseover(function(d) {
            var d = this.__data__;
            var count = data.country[d.name];
            if (typeof(count) === "undefined") {
              var membership = d.name + ": non member";              
            } else {
              var membership = d.name + ": <br />" + count.GBIFMembership + "<br />"
                   + count.agents.Node + " node(s).<br />"
                   + count.agents.Org + " organisation(s).<br />"
                   + count.agents.Resource + " resource(s).<br />"
                   + count.stats.provider_count + " publisher(s).<br />"
                   + count.agents.ChecklistDataset + " checklist(s). <br />"
                   + count.agents.ChecklistRecord + " name(s). <br />"
                   + count.stats.dataset_count + " dataset(s).<br />"
                   + pad(count.stats.occurrence_count) + " records.<br />"
                   + pad(count.stats.occurrence_georeferenced_count) + " georeferended.<br />";
            }
            jQuery("#zone-preface").append('<div id="dashBox"></div>');
            jQuery("#dashBox").append(membership).css({
              display: 'block'
            }).animate({
              opacity: 1
            });
            
          }).mouseout(function() {
            jQuery("#dashBox").remove();
          });
    });
  });
};

function publicationGrid(dest) {
  var oTable = jQuery('#publicationTable').dataTable( {
    "iDisplayLength": 15,
    "bFilter": false,
    "bAutoWidth": false,
    "bLengthChange": false,
    "bInfo": false,
    "bPaginate": false,
    "bProcessing": true,
    "sAjaxSource": dest,
    "aoColumnDefs": [
        { "aTargets": [0], "mDataProp": "year" },
        { "aTargets": [1], "mDataProp": "GBIF_used", "sClass": "alignRight" },
        { "aTargets": [2], "mDataProp": "GBIF_discussed", "sClass": "alignRight" },
        { "aTargets": [3], "mDataProp": "GBIF_mentioned", "sClass": "alignRight" },
        { "aTargets": [4], "mDataProp": "other", "sClass": "alignRight" },
        { "aTargets": [5], "mDataProp": "total", "sClass": "alignRight" }
    ],
    "fnFooterCallback": function ( nRow, aaData, iStart, iEnd, aiDisplay ) {
      var totalGBIF_used = 0;
      var totalGBIF_discussed = 0;
      var totalGBIF_mentioned = 0;
      var totalOther = 0;
      var totalTotal = 0;
      for ( var i = 0; i < aaData.length; i++) {
        totalGBIF_used += aaData[i]['GBIF_used'];
        totalGBIF_discussed += aaData[i]['GBIF_discussed'];
        totalGBIF_mentioned += aaData[i]['GBIF_mentioned'];
        totalOther += aaData[i]['other'];
        totalTotal += aaData[i]['total'];
      }
      var nCells = nRow.getElementsByTagName('th');
      nCells[0].innerHTML = 'Total';
      nCells[1].innerHTML = totalGBIF_used;
      nCells[2].innerHTML = totalGBIF_discussed;
      nCells[3].innerHTML = totalGBIF_mentioned;
      nCells[4].innerHTML = totalOther;
      nCells[5].innerHTML = totalTotal;
    }    
  });
}

function createMembershipMap() {

    var path = d3.geo.path()
      .projection(
        d3.geo.mercator()
          .scale(1000)
          .translate([450, 300])
      );

    var svg = d3.select("#map").append("svg:svg")
      .attr("class", "Blues mapvector")
      .attr("width", 1160)
      .attr("height", 480);

    var counties = svg.append("svg:g")
      .attr("id", "counties");
    
    legend();

  d3.json(destForMembership.world, function(data) {
    var pad = d3.format("02,"), quantize = d3.scale.quantile().domain([0, 36215834]).range(d3.range(9));

    d3.json(destForGeo.world, function(json) {
    
      counties.selectAll("path")
          .data(json.features)
        .enter().append("svg:path")
          .attr("class", function(d) { 
            var count = data.country[d.name];
            if (typeof(count) === "undefined") {
              return "non-member";
            } else {
              if (count.GBIFMembership == "Voting Participant" && count.MOU2012 == "signed") return "voting";
              if (count.GBIFMembership == "Associate Country Participant" && count.MOU2012 == 'signed') return "associate";
              if (count.MOU2007 == 'signed' && count.MOU2012 == 'unsigned') return "unsigned";
            }
          })
          .attr("d", path)

        .append("svg:title")
          .text(function(d) { return d.name + ": " + d.iso_a2; });

          jQuery('svg path').mouseover(function(d) {
            var d = this.__data__;
            var count = data.country[d.name];
            if (typeof(count) === "undefined") {
              var membership = d.name + ": non member";              
            } else {
              var membership = d.name + ": " + count.GBIFMembership;
              if (count.MOU2012 == 'unsigned') membership = membership + ' (~2011)';
            }
            jQuery("#zone-preface").append('<div id="memberBox"></div>');
            jQuery("#memberBox").append(membership).css({
              display: 'block'
            }).animate({
              opacity: 1
            });
            
          }).mouseout(function() {
            jQuery("#memberBox").remove();
          });
    });
  });
}

function legend() {
    
    data = JSON.parse(membershipType);
    
    var y = d3.scale.linear().domain([0, data.type.length]).range([15, 60]);
    var legend = d3.select("#zone-preface").append("svg:svg").attr("id", "legend").attr("width", 300).attr("height", 50).append("svg:g");
    
    legend.selectAll("rect")
        .data(data.type)
      .enter()
        .append("svg:rect")
        .attr("x", 10)
        .attr("y",  function (d, i) { return y(i) - 8 ; })
        .attr("width", 8)
        .attr("height", 8)
        .attr("fill", function (d) { return d.color; });
        
    legend.selectAll("text")
        .data(data.type)
      .enter()
        .append("svg:text")
        .attr("x", 25)
        .attr("y", function (d, i) { return y(i); })
        .text(function(d) { return d.name; })
        .attr("style", "font-size: 12; font-family: Helvetica, sans-serif;");
}