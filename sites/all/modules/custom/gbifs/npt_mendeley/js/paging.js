(function ($) {

  $(document).ready(function() {
    
    $("div.pagination").hide();
    var recordsPerPage = 20;
    var totalNumRecords = $("#mendeley-citation").children().length;

    if (recordsPerPage < totalNumRecords) {
      pagination(recordsPerPage, totalNumRecords);
    }

    function pagination(recordsPerPage, totalNumRecords){
      //Show the pagination controls
      $(".pagination").show();

      //loop through all of the divs and hide them by default.
      for (var i = 1; i <= totalNumRecords; i++) {
        $("#mendeley-citation").find("#citation-" + i).hide();
      }

      //then only display the number of divs the user dictated
      for (var i = 1; i <= recordsPerPage; i++) {
        $("#mendeley-citation").find("#citation-" + i).show();
      }

      //maxPages is the maximum amount of pages needed for pagination. (round up) 
      var maxPages = Math.ceil(totalNumRecords/recordsPerPage);
      var pathname = window.location.pathname;   

      $('.pagination').jqPagination({
        link_string  : '/?page={page_number}',
        max_page     : maxPages,
        paged        : function(page) { 

                         //loop through all of the divs and hide them all.
                         for (var i = 1; i <= totalNumRecords; i++) {
                           $("#mendeley-citation").find("#citation-" + i).hide();
                         }

                         //Find the range of the records for the page: 
                         var recordsFrom = recordsPerPage * (page-1) + 1;
                         var recordsTo = recordsPerPage * (page);

                         //then display only the records on the specified page
                         for (var i = recordsFrom; i <= recordsTo; i++) {
                           $("#mendeley-citation").find("#citation-" + i).show();
                         }      

                         //scroll to the top of the page if the page is changed
                         $("#mendeley-citation").animate({ scrollTop: 0 }, "slow");

                       }
      });                                                                        
    }    
  	
  });

})(jQuery);