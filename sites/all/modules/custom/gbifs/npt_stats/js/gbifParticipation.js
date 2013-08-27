(function ($) {

  $(document).ready(function() {

    var node_uuid = Drupal.settings.npt_stats.node_uuid;
    var registryWS = Drupal.settings.npt_constants.GBIF_REGISTRY_API_NODE;
    var url = registryWS + '/' + node_uuid + '?callback=npt_startup';
    $.ajax({
      type: 'GET',
      url: url,
      async: false,
      jsonpCallback: 'npt_startup',
      contentType: "application/json",
      dataType: 'jsonp',
      success: function(json) {
        
        $("#block-npt-stats-gbif-participation").html(json.title);
        
      },
      error: function(e) {
        console.log(e.message);
      }
    });

  });

})(jQuery);