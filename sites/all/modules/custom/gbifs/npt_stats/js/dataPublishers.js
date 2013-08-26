(function ($) {

  $(document).ready(function() {
    var node_uuid = Drupal.settings.npt_stats.node_uuid;
    var registryWS = Drupal.settings.npt_constants.GBIF_REGISTRY_API_NODE;
    var publisherPrefix = Drupal.settings.npt_constants.GBIF_PORTAL_PUBLISHER;
    var url = registryWS + '/' + node_uuid + '/organization';

    $.ajax({
      type: 'GET',
      url: url,
      async: false,
      jsonpCallback: 'npt_startup',
      contentType: "application/json",
      dataType: 'jsonp',
      success: function(json) {

        var results = json.results;
        var orgList = $('<ul/>', {
                        id: 'list-data-publisher',
                      }).appendTo('#block-npt-stats-data-publishing-orgs');
        for (i = 0; i < results.length; i++) {
          var link = $('<a>', {
            href: publisherPrefix + '/' + results[i].key,
            text: results[i].title,
          });
          $('<li/>')
            .append(link)
            .appendTo('#list-data-publisher');
        }

      },
      error: function(e) {
        console.log(e.message);
      }
    });

  });

})(jQuery);