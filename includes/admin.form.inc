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
  $form['islandora_metadata_extras_search_results_configuration']['islandora_metadata_extras_use_collection_label'] = array(
    '#type' => 'checkbox',
    '#title' => t('Replace collection PID with collection label in search results.'),
    '#default_value' => variable_get('islandora_metadata_extras_use_collection_label', FALSE),
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

  $form['islandora_metadata_extras_metadata_generation_configuration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Metadata generation'),
  );

  if (user_access('administer site configuration')) {
    $xsl_extensions = array('xsl', 'xslt');
    $form['islandora_metadata_extras_metadata_generation_configuration']['islandora_metadata_extras_use_dc_xslt'] = array(
      '#type' => 'checkbox',
      '#title' => t("Use a custom XSLT stylesheet to create DC datastreams from MODS."),
      '#default_value' => variable_get('islandora_metadata_extras_use_dc_xslt', FALSE),
    );
    $current_dc_xslt_filepath = variable_get('islandora_metadata_extras_dc_xslt_path', '');
    if (!strlen($current_dc_xslt_filepath)) {
      $current_dc_xslt_filepath = '[none]';
    }
    $form['islandora_metadata_extras_metadata_generation_configuration']['dc_xslt_stylesheet'] = array(
      '#title' => t('MODS to DC XSLT stylesheet'),
      '#type' => 'managed_file',
      '#required' => FALSE,
      '#description' => t('Select a file to upload. Existing files will be overwritten.<br/>Allowed file types: <strong>@ext.</strong><br />Current stylesheet is at !xslt_path.',
        array(
          '@ext' => implode(', ', $xsl_extensions),
          '!xslt_path' => $current_dc_xslt_filepath)
      ),
      '#default_value' => isset($form_state['values']['files']) ? $form_state['values']['files'] : NULL,
      '#upload_location' => 'temporary://',
      '#upload_validators' => array(
        'file_validate_extensions' => $xsl_extensions,
      ),
      '#states' => array(
        'visible' => array(
          ':input[name="islandora_metadata_extras_use_dc_xslt"]' => array('checked' => TRUE),
        ),
      ),
    );
  }

  if (strlen(shell_exec('which uuidgen'))) {
    $uuidgen_exists_markup = ' <img src="/misc/watchdog-ok.png" />';
  }
  else {
    $uuidgen_exists_markup = ' <img src="/misc/watchdog-error.png" />';
  }
  $form['islandora_metadata_extras_metadata_generation_configuration']['islandora_metadata_extras_add_uuid_to_mods'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add an &lt;identifer type="uuid"&gt; element to newly ingested MODS datastreams. Requires presence of the "uuidgen" utility. !uuidgen_exists',
      array('!uuidgen_exists' => $uuidgen_exists_markup)),
    '#default_value' => variable_get('islandora_metadata_extras_add_uuid_to_mods', FALSE),
  );

  $form['#submit'][] = "islandora_metadata_extras_save_dc_xslt";

  return system_settings_form($form);
}

/**
 * Form submit handler.
 *
 * Copies the uploaded file into the public 'files' directory.
 *
 * @param array $form
 *   The drupal form.
 * @param array $form_state
 *   The drupal form state.
 */
function islandora_metadata_extras_save_dc_xslt(array $form, array &$form_state) {
  if (isset($form_state['values']['dc_xslt_stylesheet']) && ($form_state['values']['dc_xslt_stylesheet'] > 0)) {
    $stylesheet_file = file_load($form_state['values']['dc_xslt_stylesheet']);
    $stylesheet_tmp_path = drupal_realpath($stylesheet_file->uri);
    $stylesheet_filename = drupal_realpath($stylesheet_file->filename);
    $destination = "public://" . $stylesheet_filename;
    $permanent_file = file_move($stylesheet_file, $destination, FILE_EXISTS_REPLACE);
    $permanent_file->status = 1;
    file_save($permanent_file);
    $permanent_file_realpath = drupal_realpath($permanent_file->uri);
    drupal_set_message(t('Stylesheet for generating DC datastreams uploaded to !dest',
      array('!dest' => $permanent_file_realpath)));
    variable_set('islandora_metadata_extras_dc_xslt_path', $permanent_file_realpath);

  }
}
