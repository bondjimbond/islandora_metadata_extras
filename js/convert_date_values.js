(function ($) {
  $(document).ready(function() {
    $("dl.islandora-metadata-fields > dd").each(function() {
      var fieldValue = $(this).text();
      fieldValue = $.trim(fieldValue);

      // If a field's value matches dddd-dd-dd, convert it to its
      // textual equivalent, respecting locale-specific month names.
      var datePattern = /^\d\d\d\d\-\d\d\-\d\d$/;
      if (datePattern.test(fieldValue)) {
        dateParts = fieldValue.split("-");
        var year = dateParts[0];
        var month = dateParts[1] - 1;
        var day = dateParts[2];
        var date = new Date(year, month, day);
        month = date.toLocaleString(Drupal.settings.islandora_metadata_extras.locale, { month: "long" });
        day = day.replace(/^0+/, '');
        var textDate = month + ' ' + day + ', ' + year;
        $(this).text(textDate);
      }

      // If a field's value matches dddd-dd, convert it to its
      // textual equivalent, respecting locale-specific month names.
      datePattern = /^\d\d\d\d\-\d\d$/;
      if (datePattern.test(fieldValue)) {
        dateParts = fieldValue.split("-");
        var year = dateParts[0];
        var month = dateParts[1] - 1;
        var date = new Date(year, month);
        month = date.toLocaleString(Drupal.settings.islandora_metadata_extras.locale, { month: "long" });
        var textDate = month + ' ' + year;
        $(this).text(textDate);
      }

    }
 )});
})(jQuery);
