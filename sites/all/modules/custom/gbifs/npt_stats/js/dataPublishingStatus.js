var node_uuid = Drupal.settings.npt_stats.node_uuid;
var enumName = Drupal.settings.npt_stats.node_country_enum;
var api = Drupal.settings.npt_constants.GBIF_API;
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
        percent = Math.round(countGeo / count * 100, -1);
				
				// now update the content on the page
        $('<p/>', {
          text: count + ' records published. ' + countGeo + ' (' + percent + '%) georeferenced.',
        }).appendTo('#block-npt-stats-data-publishing-status div.content');
      });
    });
  });

})(jQuery);