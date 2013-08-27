(function ($) {

  $(document).ready(function() {
    var node_uuid = Drupal.settings.npt_stats.node_uuid;
    var registryNode = Drupal.settings.npt_constants.GBIF_REGISTRY_API_NODE;
    var gbrdsAgent = Drupal.settings.npt_constants.GBRDS_AGENT_URL;
    var url = registryNode + '/' + node_uuid + '/installation';

    $.getJSON(url + '?callback=?', function(data) {

        var results = data.results;
        var techList = $('<ul/>', {
                        id: 'list-tech-installation',
                      }).appendTo('#block-npt-stats-data-publishing-tech div.content');
        $.each(results, function(i,d) {
          var link = $('<a/>', {
            href: gbrdsAgent + results[i].key,
            text: results[i].title,
          });
          
          $('<li/>')
            .append(link)
            .appendTo('#list-tech-installation');
        });

      });

  });

})(jQuery);