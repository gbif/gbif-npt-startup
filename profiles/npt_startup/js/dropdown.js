jQuery(document).ready(function() {
  jQuery("#edit-dropdown-first").change(function() {
     jQuery("#edit-dropdown-second").load("profiles/npt_startup/js/textdata/" + jQuery(this).val() + ".txt");
  });  
});

