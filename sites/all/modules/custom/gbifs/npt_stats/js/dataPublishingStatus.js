var node_uuid = Drupal.settings.npt_stats.node_uuid;
var nodeShortname = Drupal.settings.npt_stats.node_shortname + ' ';
var enumName = Drupal.settings.npt_stats.node_country_enum;
var iso2 = Drupal.settings.npt_stats.node_country;
var api = Drupal.settings.npt_constants.GBIF_API;
var portal = Drupal.settings.npt_constants.GBIF_PORTAL;
var gbrdsAgent = Drupal.settings.npt_constants.GBRDS_AGENT_URL;
var url = api + '/occurrence/count?hostCountry=' + enumName;
var count, countGeo, percent;

(function ($) {

  $(document).ready(function() {
    
    // chain our requests, in the callback
    $.getJSON(url + '&callback=?', function(data) {
      count = data; 
      
      // call the second method
      $.getJSON(url + '&georeferenced=true&callback=?', function(data) {
        countGeo = data; 
        percent = (countGeo / count * 100).toFixed(2);
				
				// prepare the link to the portal
				var href = portal + '/country/' + iso2 + '/publishing';
				var link = '<a href="' + href + '">More</a>';
				var text = '<p>' + count + ' records published. ' + countGeo + ' (' + percent + '%) georeferenced. ' + link + ' on ' + nodeShortname + 'data publishing on the GBIF Portal.</p>';
				
				$('#block-npt-stats-data-publishing-status div.content').html(text);
      });
    });
  });

})(jQuery);