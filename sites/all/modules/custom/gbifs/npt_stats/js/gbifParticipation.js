(function ($) {

  Drupal.behaviors.npt_stats = {
    attach: function (context, settings) {
      
      $(document).ready(function() {

        var node_uuid = Drupal.settings.npt_stats.node_uuid;
        var url = 'http://api.gbif.org/node/' + node_uuid + '?callback=npt_startup';
        $.ajax({
          type: 'GET',
          url: url,
          async: false,
          jsonpCallback: 'npt_startup',
          contentType: "application/json",
          dataType: 'jsonp',
          success: function(json) {
            
            /*
            if (typeof json.participationStatus != 'undefined') {
              switch (json.participationStatus) {
                case 'VOTING':
                  var pageTitle = json.title + ' ' + Drupal.t('as a GBIF Voting Country Participant'); 
                  $("#page-title").text(pageTitle);
                  break;
                case 'ASSOCIATE':
                  var pageTitle = json.title + ' ' + Drupal.t('as a GBIF Associate Countrt Participant'); 
                  $("#page-title").text(pageTitle);
                  break;
                case 'Other':
                  var pageTitle = json.title + ' ' + Drupal.t('as a GBIF Associate Participant'); 
                  $("#page-title").text(pageTitle);
                  break;
              }
            }
            */
              $("#block-npt-stats-gbif-participation").html(json.title);
            
          },
          error: function(e) {
            console.log(e.message);
          }
        });

      });
      

    }
  };

})(jQuery);