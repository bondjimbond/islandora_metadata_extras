<?php

/**
 * @file
 * The admin form for the Islandora Metadata Extras module.
 */

/**
 * Defines the admin settings form.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 *
 * @return array
 *   The Drupal form definition.
 */
function islandora_metadata_extras_admin_form(array $form, array &$form_state) {
  $get_default_value = function($name, $default) use(&$form_state) {
    return isset($form_state['values'][$name]) ? $form_state['values'][$name] : variable_get($name, $default);
  };

  $form['islandora_metadata_extras_search_results_configuration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Search results'),
  );

  $form['islandora_metadata_extras_search_results_configuration']['islandora_metadata_extras_use_collection_label'] = array(
    '#type' => 'checkbox',
    '#title' => t('Replace collection PID with collection label in search results'),
    '#default_value' => variable_get('islandora_metadata_extras_use_collection_label', FALSE),
  );

  return system_settings_form($form);
}
