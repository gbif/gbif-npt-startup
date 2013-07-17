Drupal.behaviors.nptMendeleyProgressbar = {
  attach: function(context, settings) {

    jQuery("#update-div").append('<div id="progressbar"><div class="progressbar-label"></div></div></div>')


    var progressPath = Drupal.settings.progress_path;

    var progressbar = jQuery( "#progressbar" ),
      progressLabel = jQuery( ".progressbar-label" );

    progressbar.progressbar({
      value: false,
      change: function() {
      },
      complete: function() {
        progressLabel.text( "Complete!" );
      }
    });

    function progress() {
      jQuery.getJSON(progressPath, function(data) {
        var percentage = Math.round((data.page_retrieved / data.total_pages) * 100);
        progressbar.progressbar({ value: percentage });
        progressLabel.text( data.documents_retrieved + " of " + data.total_documents + " documents retrieved (" + percentage + "%)");

        if ( percentage < 99 ) {
          setTimeout( progress, 100 );
        }
      });
    }

    setTimeout( progress, 3000 );

  }
};