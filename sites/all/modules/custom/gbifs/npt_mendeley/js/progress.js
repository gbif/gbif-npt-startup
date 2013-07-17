var progressPath = Drupal.settings.progress_path;
var barContainer = '<div id="progressbar"><div class="progress-label"></div></div>';

function progressUpdate() {
  $("#edit-update-submit").after(barContainer);
}

/*
jQuery(document).ready(function() {
  
  $.("#update-div").append(barContainer);
  
  progressUpdate();
  
});

/*

(function ($) {
Drupal.behaviors.npt_mendeley = {
  attach:function(context, settings) {
    var progressbar = $( "#progressbar" ),
      progressLabel = $( ".progress-label" );

    progressbar.progressbar({
      value: false,
      change: function() {
        progressLabel.text( progressbar.progressbar( "value" ) + "%" );
      },
      complete: function() {
        progressLabel.text( "Complete!" );
      }
    });

    function progressUpdate() {

      $.getJSON(progressPath, function(data) {
        var percentage = Math.round(data.page_retrieved / data.total_pages);
        progressbar.progressbar( "value", percentage );

        if ( percentage < 100 ) {
          setTimeout( progressUpdate, 500 );
        }
      });


    }

    setTimeout( progressUpdate, 3000 );    
  }
};
})(jQuery);


/*
function dgd7progressbarUpdate(){

  var progress;
  progress = $("#progressbar").progressbar("value");
  if (progress < 100) {
    $(".progressbar").progressbar("value", progress + 5);
    setTimeout(dgd7progressbarUpdate, 500);
  }
  Drupal.behaviors.npt_mendeley = {
    attach: function(context, settings) {
      $(".progressbar").progressbar({ value: 1 });
      setTimeout(dgd7progressbarUpdate, 500);
    }
  };
}          
*/