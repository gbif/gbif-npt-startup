var destMembership = Drupal.settings.gbif_region.membership;
var destGeo = Drupal.settings.gbif_region.geo;
var region = Drupal.settings.gbif_region.region;

jQuery("#zone-content-wrapper").ready(function() {
  jQuery("#zone-content-wrapper").before('<div id="zone-preface-wrapper" class="zone-wrapper zone-preface-wrapper clearfix"><div id="zone-preface" class="zone zone-preface clearfix container-24"><div class="gallery" id="map"></div></div></div>');
  jQuery("#zone-preface-wrapper").hide();
  createMap();
});

jQuery(document).ready(function() {
  jQuery(".menu").append('<li><input id="open-map" type="button" value="open map" /></li><li><input id="close-map" type="button" value="close map" /></li>');

  jQuery("#open-map").click(function() {
    if (jQuery("#zone-preface-wrapper").is(':hidden')) {

      jQuery("#page-title").addClass("map-title-fixed").animate({"top": "120px"}, 1000, function() {
        jQuery(this).appendTo("#zone-preface").removeClass("map-title-fixed").addClass("map-title-relative").css("top", "80px");
      });

      jQuery("ul.tabs").addClass("map-tabs-fixed").animate({
        'top': '538px',
        'margin-left': '-10px'
        }, 1000, function() {
          jQuery(this).appendTo("#zone-preface").removeClass("map-tabs-fixed").addClass("map-tabs-relative").css({
            'top': '522px',
            'margin': '0px'
          });
      });
      jQuery("#zone-preface-wrapper").slideDown(1000);
    }
  });

  jQuery("#close-map").click(function() {
    if (jQuery("#zone-preface-wrapper").is(':visible')) {
      
      jQuery("#page-title").animate({"top": "105px"}, 1000, function() {
        jQuery(this).removeClass("map-title-relative").removeAttr("style");
        jQuery("#main-content").after(this);
      });

      jQuery("ul.tabs").animate({
        'top': '200px',
        'margen-left': '0px'
      }, 1000, function() {
        jQuery(this).appendTo("div.tabs").removeClass("map-tabs-relative").removeAttr("style");
      });
      
      jQuery("#zone-preface-wrapper").slideUp(1000);
    }
  });  
});


function createMap() {
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
        "scale": 600,
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
      .attr("class", "Blues")
      .attr("width", 1160)
      .attr("height", 480);

    var counties = svg.append("svg:g")
      .attr("id", "counties");

  d3.json(destMembership, function(data) {
    var pad = d3.format("02,"), quantize = d3.scale.quantile().domain([0, 36215834]).range(d3.range(9));

    d3.json(destGeo, function(json) {
    
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
                     + count.agents.Organisation + " organisation(s).<br />"
                     + count.agents.Resource + " resource(s).<br />"
                     + count.stats.provider_count + " provider(s).<br />"
                     + count.stats.dataset_count + " dataset(s).<br />"
                     + pad(count.stats.occurrence_count) + " records.<br />"
                     + pad(count.stats.occurrence_georeferenced_count) + " georeferended.<br />";
                 }
             } 
          });
    });
  });
};


d3.select("select").on("change", function() {
  d3.selectAll("svg").attr("class", this.value);
});

