<?php

/**
 * @file
 * Documents the hooks this module defines.
 */

/**
 * Allows modules to alter Dublin Core values that get inserted into HTML meta tags.
 *
 * @param object $dc
 *   An array of Dublin Core elements, each member of which is itself
 *   an array.
 *
 * @param object $object
 *  The current Islandora object.
 */
function mymodule_islandora_metadata_extras_dc_in_head_alter(&$dc, $object) {
  // Override the title that gets inserted into the HTML HEAD meta tags for
  // a specific object.
  if ($object->id == 'islandora:1234' && isset($dc['title'][0])) {
    $dc['title'][0] = "Out with the old title, in with the new!";
  }

  // Show at most 10 DC subject elements.
  if (isset($dc['subject']) && count($dc['subject']) > 10) {
    $dc['subject'] = array_slice($dc['subject'], 0, 10);
  }
}
