(function($) {
  Drupal.behaviors.chosen = {
    attach: function(context, settings) {
      var minWidth = settings.chosen.minimum_width;
      var minOptions = settings.chosen.minimum;
      // Define options.
      var options = {};
      options.disable_search = Drupal.settings.chosen.disable_search;
      options.disable_search_threshold = settings.chosen.disable_search_threshold;
      options.search_contains = settings.chosen.search_contains;
      options.placeholder_text_multiple = settings.chosen.placeholder_text_multiple;
      options.placeholder_text_single = settings.chosen.placeholder_text_single;
      options.no_results_text = settings.chosen.no_results_text;
      options.inherit_select_classes = true;

      // Prepare selector and add unwantend selectors.
      var selector = settings.chosen.selector;
      selector = selector + '\n.tabledrag-hide select'

      $(selector, context)
        .not('#field-ui-field-overview-form select, #field-ui-display-overview-form select') //disable chosen on field ui
        .each(function() {
          if ($(this).find('option').size() >= minOptions || minOptions == 'Always Apply') {
            options = $.extend(options, {
              width: (($(this).width() < minWidth) ? minWidth : $(this).width()) + 'px'
            });
            $(this).chosen(options);
          }
      });

      // Enable chosen for widgets.
      $('select.chosen-widget', context).each(function() {
        options = $.extend(options, {
          width: (($(this).width() < minWidth) ? minWidth : $(this).width()) + 'px'
        });
        $(this).chosen(options);
      });
    }
  };
})(jQuery);
