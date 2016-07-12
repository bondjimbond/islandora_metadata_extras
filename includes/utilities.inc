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
