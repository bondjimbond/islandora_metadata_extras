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
  $form['islandora_metadata_extras_search_results_configuration']['islandora_metadata_extras_rewrite_namespace'] = array(
    '#type' => 'checkbox',
    '#title' => t('Replace namespaces in search results according to a defined pattern.'),
    '#default_value' => variable_get('islandora_metadata_extras_rewrite_namespace', FALSE),
    '#collapsible' => TRUE,
  );
  $form['islandora_metadata_extras_search_results_configuration']['islandora_metadata_extras_namespace_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Namespace display field'),
    '#states' => array(
      'visible' => array(
        ':input[name="islandora_metadata_extras_rewrite_namespace"]' => array('checked' => TRUE),
      ),
    ),
    '#description' => t('Solr field configured in search settings to display the namespace. Does not need to exist in your Solr configuration, but must be added to your Solr search result display fields (admin/islandora/search/islandora_solr/settings).'),
    '#default_value' => variable_get('islandora_metadata_extras_namespace_field', 'PID_namespace_ss'),
  );
  $default_replacements = "islandora|System\nir|Scholar";
  $form['islandora_metadata_extras_search_results_configuration']['islandora_metadata_extras_namespace_replacements'] = array(
    '#type' => 'textarea',
    '#title' => t('Namespace replacements'),
    '#rows' => 10,
    '#states' => array(
      'visible' => array(
        ':input[name="islandora_metadata_extras_rewrite_namespace"]' => array('checked' => TRUE),
      ),
    ),
    '#default_value' => variable_get('islandora_metadata_extras_namespace_replacements', $default_replacements),
    '#description' => t("Place each namespace and replacement value pair, separated by a |, on its own line."),
  );
  $form['islandora_metadata_extras_search_results_configuration']['islandora_metadata_extras_use_collection_label'] = array(
    '#type' => 'checkbox',
    '#title' => t('Replace collection PID with collection label in search results.'),
    '#default_value' => variable_get('islandora_metadata_extras_use_collection_label', FALSE),
  );

  $form['islandora_metadata_extras_search_results_configuration']['islandora_metadata_extras_rewrite_facets'] = array(
    '#type' => 'checkbox',
    '#title' => t('Replace facet values with configured text.'),
    '#default_value' => variable_get('islandora_metadata_extras_rewrite_facets', FALSE),
    '#collapsible' => TRUE,
  );
  $form['islandora_metadata_extras_search_results_configuration']['islandora_metadata_extras_facet_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Facet display field'),
    '#states' => array(
      'visible' => array(
        ':input[name="islandora_metadata_extras_rewrite_facets"]' => array('checked' => TRUE),
      ),
    ),
    '#description' => t('Solr field used for the target facet.'),
    '#default_value' => variable_get('islandora_metadata_extras_facet_field', 'mods_accessCondition_use_and_reproduction_ms'),
  );
  $default_facet_replacements = "";
  $form['islandora_metadata_extras_search_results_configuration']['islandora_metadata_extras_facet_replacements'] = array(
    '#type' => 'textarea',
    '#title' => t('Facet value replacements'),
    '#rows' => 10,
    '#states' => array(
      'visible' => array(
        ':input[name="islandora_metadata_extras_rewrite_facets"]' => array('checked' => TRUE),
      ),
    ),
    '#default_value' => variable_get('islandora_metadata_extras_facet_replacements', $default_facet_replacements),
    '#description' => t("Place each original value and replacement value pair, separated by a |, on its own line."),
  );

  $form['islandora_metadata_extras_embedded_metadata'] = array(
    '#type' => 'fieldset',
    '#title' => t('Embedded metadata'),
  );
  $form['islandora_metadata_extras_embedded_metadata']['islandora_metadata_extras_embed_dc_in_head'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add &lt;meta&gt; tags containing DC values, for Zotero, etc.'),
    '#default_value' => variable_get('islandora_metadata_extras_embed_dc_in_head', FALSE),
  );

  $form['islandora_metadata_extras_admin_metadata'] = array(
    '#type' => 'fieldset',
    '#title' => t('Administrative metadata'),
  );
  $form['islandora_metadata_extras_admin_metadata']['islandora_metadata_extras_show_solr_doc'] = array(
    '#type' => 'checkbox',
    '#title' => t("Display tab containing an object's Solr document."),
    '#default_value' => variable_get('islandora_metadata_extras_show_solr_doc', FALSE),
  );
  $form['islandora_metadata_extras_admin_metadata']['islandora_metadata_extras_show_edit_metadata_tab'] = array(
    '#type' => 'checkbox',
    '#title' => t("Display tab containing direct link to edit an object's metadata."),
    '#default_value' => variable_get('islandora_metadata_extras_show_edit_metadata_tab', FALSE),
  );
  $form['islandora_metadata_extras_admin_metadata']['islandora_metadata_extras_metadata_dsids'] = array(
    '#type' => 'textfield',
    '#title' => t('Metadata datastream IDs'),
    '#states' => array(
      'visible' => array(
        ':input[name="islandora_metadata_extras_show_edit_metadata_tab"]' => array('checked' => TRUE),
      ),
    ),
    '#description' => t('Comma-separate list of datastream IDs to link to. If an object does not have one of these datastreams, the next one is used.'),
    '#default_value' => variable_get('islandora_metadata_extras_metadata_dsids', 'MODS,MADS'),
  );
  $form['islandora_metadata_extras_admin_metadata']['islandora_metadata_extras_show_datastream_checksums'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display datastream checksums (latest datastream version only).'),
    '#default_value' => variable_get('islandora_metadata_extras_show_datastream_checksums', FALSE),
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
