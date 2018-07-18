<?php
/**
 * @file
 * Theme functions for the islandora_solr_metadata module.
 */

/**
 * Prepares variables for islandora_solr_metadata_display templates.
 *
 * Default template: islandora-solr-metadata-display.tpl.php
 *
 * @param array $variables
 *   An associative array containing:
 *   - islandora_object: The AbstractObject for which we are generating a
 *     metadata display.
 *   - print: A boolean indicating to disable some functionality, to facilitate
 *     printing. When TRUE, avoids adding the "collapsible" and "collapsed"
 *     classes to fieldsets.
 */
function islandora_metadata_extras_templated_metadata_display(array &$variables) {
  module_load_include('inc', 'islandora_solr_metadata', 'includes/db');
  module_load_include('inc', 'islandora', 'includes/utilities');
  drupal_add_js('misc/form.js');
  drupal_add_js('misc/collapse.js');

  $object = $variables['islandora_object'];
  $db_fields = array();
  $solr_fields =& $variables['solr_fields'];
  $associations = $variables['associations'];

  foreach ($associations as $configuration_id) {
    $field = islandora_solr_metadata_get_fields($configuration_id['configuration_id']);
    $db_fields = array_merge($db_fields, $field);
  }
  foreach ($db_fields as $solr_field => $value) {
    if (isset($solr_fields[$solr_field])) {
      continue;
    }
    // Make an array for use later on.
    $solr_fields[$solr_field] = $value + array(
      'value' => array(),
    );
  }

  require_once '/var/www/drupal/sites/all/libraries/twig/lib/Twig/Autoloader.php';
  Twig_Autoloader::register();
  $loader = new Twig_Loader_Array(array(
    'index' => 'I am the output of a template, {{ name }}!',
  ));
  $twig = new Twig_Environment($loader);
  $variables['twig_content'] = $twig->render('index', array('name' => 'friend'));

  $separator = variable_get('islandora_solr_metadata_field_value_separator', "\n");

  if (empty($separator)) {
    $separator = "\n";
  }
  $variables['separator'] = $separator;
  $variables['parent_collections'] = islandora_get_parents_from_rels_ext($object);
}