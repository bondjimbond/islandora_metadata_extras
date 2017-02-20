<?php

/**
 * @file
 * Documents the hooks this module defines.
 */

/**
 * Allows other modules to perform a drupal_alter() on Dublin Core values.
 *
 * @param object $dc
 *   An array of Dublin Core elements, each member of which is itself
 *   an array.
 *
 * @param object $object
 *  The current Islandora object.
 */
function mymodule_islandora_metadata_extras_dc_in_head_alter(&$dc, $object) {
  $dc['title'][0] = "Out with the old title, in with the new!";
}
