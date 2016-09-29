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

  $form['islandora_metadata_extras_object_metadata_display'] = array(
    '#type' => 'fieldset',
    '#title' => t('Object metadata display'),
  );
  $form['islandora_metadata_extras_object_metadata_display']['islandora_metadata_extras_hide_empty_metadata_values'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide empty fields in object metadata displays.'),
    '#default_value' => variable_get('islandora_metadata_extras_hide_empty_metadata_values', FALSE),
  );
  $form['islandora_metadata_extras_object_metadata_display']['islandora_metadata_extras_show_pretty_dates'] = array(
    '#type' => 'checkbox',
    '#title' => t('Replace yyyy-mm-dd and yyyy-mm dates in object metadata displays with  human-readable equivalents.'),
    '#default_value' => variable_get('islandora_metadata_extras_show_pretty_dates', FALSE),
  );

  $form['islandora_metadata_extras_search_results_configuration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Search results'),
  );
  $form['islandora_metadata_extras_search_results_configuration']['islandora_metadata_extras_hide_empty_values_in_search_results'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide empty fields in search results.'),
    '#default_value' => variable_get('islandora_metadata_extras_hide_empty_values_in_search_results', FALSE),
  );
  $form['islandora_metadata_extras_search_results_configuration']['islandora_metadata_extras_show_tooltips_in_search_results'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show preview tooltips in search results. Requires https://www.drupal.org/project/qtip.'),
    '#default_value' => variable_get('islandora_metadata_extras_show_tooltips_in_search_results', FALSE),
  );
  $form['islandora_metadata_extras_search_results_configuration']['islandora_metadata_extras_use_collection_label'] = array(
    '#type' => 'checkbox',
    '#title' => t('Replace collection PID with collection label in search results.'),
    '#default_value' => variable_get('islandora_metadata_extras_use_collection_label', FALSE),
  );

  $form['islandora_metadata_extras_metadata_generation_configuration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Metadata generation'),
  );
  if (strlen(shell_exec('which uuidgen'))) {
    $uuidgen_exists_markup = ' <img src="/misc/watchdog-ok.png" />';
  }
  else {
    $uuidgen_exists_markup = ' <img src="/misc/watchdog-error.png" />';
  }
  $form['islandora_metadata_extras_metadata_generation_configuration']['islandora_metadata_extras_add_uuid_to_mods'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add an &lt;identifer type="uuid"&gt; element to newly ingested MODS datastreams. Requires presence of uuidgen utility. !uuidgen_exists',
      array('!uuidgen_exists' => $uuidgen_exists_markup)),
    '#default_value' => variable_get('islandora_metadata_extras_add_uuid_to_mods', FALSE),
  );

  return system_settings_form($form);
}
