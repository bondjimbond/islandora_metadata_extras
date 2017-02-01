<?php

/**
 * @file
 * Utility functions.
 */

/**
 * Given a PID, looks up the object's label in Solr.
 *
 * @param string $pid
 *   The PID to look up in Solr.
 *
 * @return string
 *   The object's label, or an empty string.
 */
function islandora_metadata_extras_pid_to_label($pid) {
  $query_processor = new IslandoraSolrQueryProcessor();
  $label = '';
  $pid = str_replace('info:fedora/', '', $pid);
  if (islandora_is_valid_pid($pid)) {
    $query_processor->buildQuery("PID:\"$pid\"");
    $query_processor->solrParams['fl'] = 'PID, ' . variable_get('islandora_solr_object_label_field', 'fgs_label_s');
    $query_processor->executeQuery();
    if (!empty($query_processor->islandoraSolrResult) && !empty($query_processor->islandoraSolrResult['response']['objects'])) {
      $label = (!empty($query_processor->islandoraSolrResult['response']['objects'][0]['object_label']) ?
        $query_processor->islandoraSolrResult['response']['objects'][0]['object_label'] : '');
    }
  }
  return $label;
}

/**
 * Adds an identifier element containing a UUID to a MODS datastream.
 *
 * @param string $pid
 *   The PID of the object that the MODS is part of.
 * @param string $mods_xml
 *   The XML content of the MODS datastream.
 *
 * @return string|bool
 *   The modified XML, or FALSE if the XML was not modified.
 */
function islandora_metadata_extras_add_uuid_to_mods($pid, $mods_xml) {
  $dom = new DOMDocument();
  $dom->loadXML($mods_xml);

  $xpath = new \DOMXPath($dom);
  $xpath->registerNamespace('mods', 'http://www.loc.gov/mods/v3');
  $existing_uuid_identifiers = $xpath->query("//mods:identifier[@type='uuid']");
  if ($existing_uuid_identifiers->length > 0) {
    return FALSE;
  }

  // If there were none, continue.
  $uuid = islandora_metadata_extras_get_uuid();
  if (!strlen($uuid)) {
    watchdog('islandora_metadata_extras', 'UUID not added to MODS for !object.',
      array('!object' => $pid));
    return FALSE;
  }

  // Build the <identifier> element we are adding.
  $type = $dom->createAttribute('type');
  $type->value = 'uuid';
  $uuid_identifier = $dom->createElement('identifier', trim($uuid));
  $uuid_identifier->appendChild($type);

  // Figure out where to add it. If one ore more <identifier> elements
  // exist in the document, add the new one before the first existing one.
  $identifiers = $dom->getElementsByTagName('identifier');
  if ($identifiers->length) {
    $dom->documentElement->insertBefore($uuid_identifier, $identifiers->item(0));
  }
  else {
    // If none exist, append it to the end of the document.
    $dom->documentElement->appendChild($uuid_identifier);
  }

  return $dom->saveXML();
}

/**
 * Parses the DC datastream into an array.
 *
 * @param string $xml
 *   The XML content of the DC datastream.
 *
 * @return array
 *   An associative array containing element name => element values.
 */
function islandora_metadata_extras_get_dc_values($xml) {
  $dc_values = array();
  $dom = new DOMDocument;
  $dom->loadXML($xml);
  $elements = $dom->getElementsByTagNameNS('http://purl.org/dc/elements/1.1/', '*');
  foreach ($elements as $e) {
    if (!array_key_exists($e->localName, $dc_values)) {
      $dc_values[$e->localName] = array();
      $dc_values[$e->localName][] = $e->nodeValue;
    }
    else {
      $dc_values[$e->localName][] = $e->nodeValue;
    }
  }
  return $dc_values;
}

/**
 * Lazy generation of a UUID.
 *
 * @return string
 *   A UUID.
 */
function islandora_metadata_extras_get_uuid() {
  return shell_exec('uuidgen');
}
