(function ($) {
  $(document).ready(function() {
    $("dl.solr-thumb > dt > a").each(function() {
      $(this).after(Drupal.settings.islandora_metadata_extras.tooltip_markup);
      $(this).qtip({
        content: {
          text: $(this).next('.qtipcontent')
        }
      });
    }
 )});
})(jQuery);



