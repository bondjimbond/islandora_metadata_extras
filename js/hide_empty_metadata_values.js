(function ($) {
  $(document).ready(function() {
    $("dl.islandora-metadata-fields > dd").each(function() {
      // Value of the <dd> cannot be emtpy or contain only puncutation.
      if ($.trim($(this).text()) == '' || $.trim($(this).text()).match(/^[.,;:\-]$/)) {
        // Hide the <dd>.
        $(this).hide();
        // And hide the corresponding <dt>.
        $(this).prev().hide();
      }
    }
 )});
})(jQuery);
