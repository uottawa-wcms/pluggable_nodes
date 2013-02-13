<?php

$plugin = array(
  'title' => t('Pluggable Node'),
  'description' => t('Insert any node'),
  'category' => t('Content'),
  'single' => TRUE,
  'defaults' => array(
    'display_nid' => NULL,
    'nid' => NULL,
    'view_mode' => 'full',
  ),
  'js' => 'misc/autocomplete.js',
);

function pluggable_nodes_pluggable_node_content_type_render($subtype, $conf) {
  $block = new stdClass();
  $block->title = NULL;
  if (!empty($conf['nid'])) {
    $block->content = node_view(
      node_load($conf['nid']),
      $conf['view_mode']
    );
  } else {
    $block->content = '<p>' . t('Example') . '</p>';
  }
  return $block;
}

function pluggable_nodes_pluggable_node_content_type_edit_form($form, &$form_state) {

  /* TODO: autocomplete
   * drupal_add_js('misc/autocomplete.js');
  $form['csid'] = array(
    '#title' => t('Snippet'),
    '#type' => 'textfield',
    '#autocomplete_path' => 'content_snippets/autocomplee',
    '#default_value' => $form_state['conf']['csid'],
  );
   *
   */
  $form['nid'] = array(
    '#title' => t('Content'),
    '#type' => 'textfield',
    '#autocomplete_path' => 'system/autocomplete/node',
    '#default_value' => $form_state['conf']['display_nid'],
  );
  $info = entity_get_info('node');
  $options = array();
  foreach ($info['view modes'] as $key => $opts) {
    $options[$key] = $opts['label'];
  }
  $form['view_mode'] = array(
    '#title' => t('View Mode'),
    '#type' => 'select',
    '#default_value' => $form_state['conf']['view_mode'],
    '#options' => $options,
    '#required' => TRUE,
  );
  return $form;
}

function pluggable_nodes_pluggable_node_content_type_edit_form_submit($form, &$form_state) {
  preg_match('`\[(\d{1,})\]$`i', $form_state['values']['nid'], $matches);
  $conf = array(
    'display_nid' => $form_state['values']['nid'],
    'nid' => $matches[1],
    'view_mode' => $form_state['values']['view_mode'],
  );
  $form_state['conf'] = $conf;
}

function pluggable_nodes_pluggable_node_content_type_admin_title($subtype, $conf) {
  $snippet = node_load($conf['nid']);
  return $snippet->title;
}

