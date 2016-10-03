<?php

/**
 * Implements hook_qtip_default_qtips().
 */
function islandora_metadata_extras_qtip_default_qtips() {
  $qtips = array();

  $qtip = new stdClass();
  $qtip->disabled = FALSE;
  $qtip->api_version = 1;
  $qtip->machine_name = 'islandora_metadata_extras_preview';
  $qtip->name = 'Islandora Metadata Extras Preview';
  $qtip->settings = array(
    'style' => array(
      'classes'         => 'qtip-bootstrap',
      'classes_custom'  => '',
      'shadow'          => 0,
      'rounded_corners' => 0,
      'tip'             => 0,
    ),
    'position' => array(
      'at' => 'top right',
      'my' => '',
    ),
    'show' => array(
      'event' => array(
        'mouseenter' => 'mouseenter',
        'focus'      => 0,
        'click'      => 0,
      ),
      'solo'  => 0,
      'ready' => 0,
    ),
    'hide' => array(
      'event' => array(
        'mouseleave' => 'mouseleave',
        'unfocus'    => 0,
        'click'      => 0,
      ),
      'fixed' => 0,
    ),
  );
  $qtips['islandora_metadata_extras_preview'] = $qtip;

  return $qtips;
}
