<?php

function npt_nodestats_admin_settingsform() {

  $participant_node = variable_get('gbif_participant_node');
  $node_value = explode('-', $participant_node);
  $iso_a2 = $node_value[0];
  $country = $node_value[1];
  
  $form['npt_nodestats_update_stats'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update node statistics'),
  );
  $form['npt_nodestats_update_stats']['update_options'] = array(
    '#title' => t('Available statistics sources: '),
    '#prefix' => t('Please choose statistics to update.'),
    '#type' => 'checkboxes',
    '#options' => drupal_map_assoc(array(
      'membership' => t('Statistics'),
      'geo' => t('Map'),
      'publication' => t('Publication')
    )),
  );
  $form['npt_nodestats_update_stats']['update_stats'] = array(
    '#type' => 'submit',
    '#value' => t('Update now'),
    '#submit' => array('npt_nodestats_update_submit'),
  );
  $form['npt_nodestats_analyse_docs'] = array(
    '#type' => 'fieldset',
    '#title' => t('Analyse documents'),
  );
  $form['npt_nodestats_analyse_docs']['analyse_docs'] = array(
    '#type' => 'submit',
    '#value' => t('Analyse now'),
    '#submit' => array('npt_nodestats_analyse_submit'),
    '#prefix' => '<p>'. t('Analyse professional publications by authors from %country or biodiversity about %country, according to GBIF Public Library maintained on Mendeley.<br/>Please note this may take longer than expected.', array('%country' => $country)).'</p>',
  );
  $form['npt_nodestats_update_interval'] = array(
    '#title' => t('Automatic update interval'),
    '#type' => 'fieldset',
  );
  $interval = drupal_map_assoc(array(1800, 3600, 10800, 21600, 32400, 43200, 86400, 259200), 'format_interval');
  $interval[0] = '<' . t('none') . '>';
  $form['npt_nodestats_update_interval']['npt_nodestats_update_interval'] = array(
    '#title' => t('Please select automatic update interval:'),
    '#prefix' => t('How frequently all statistics will be updated together with system cron tasks.'),
    '#type' => 'select',
    '#default_value' => variable_get('npt_nodestats_update_interval', 3600),
    '#options' => $interval
  );
  
  return system_settings_form($form);
}


function npt_nodestats_update_submit($form, &$form_state) {

  $to_update = $form_state['values']['update_options'];
  $to_update_text = '';
  foreach ($to_update as $k => $v) {
    if (gettype($v) == 'integer') {
      unset($to_update[$k]);
    }
  }
  $length = count($to_update);
  if ($length > 0) {
    $i = 1;
    foreach ($to_update as $text) {
      $to_update_text .= $text;
      $to_update_text .= ($i < $length) ? ', ' : '';
      $i++;
    }
    $tasks = array(
      'Statistics' => 'npt_nodestats_stats_retrieve',
      'Map' => 'geojson_retrieve',
      'Publication' => 'publication_retrieve'
    );
    $tasks_to_run = array_intersect_key($tasks, $to_update);
    
    foreach ($tasks_to_run as $task) {
      switch ($task) {
        case 'npt_nodestats_stats_retrieve':
          npt_nodestats_stats_retrieve();
          break;
        case 'geojson_retrieve':
          geojson_retrieve();
          break;
        case 'publication_retrieve':
          publication_retrieve();
          break;
      }
    }
    
    //drupal_set_message(t('Statistics of @chosen updated.', array('@chosen' => $to_update_text)));  
  } elseif ($length == 0) {
    drupal_set_message(t('No option was chosen.'), 'warning');
  }
}

function npt_nodestats_analyse_submit() {

  $participant_node = variable_get('gbif_participant_node');
  $node_value = explode('-', $participant_node);
  $iso_a2 = $node_value[0];
  $country = $node_value[1];
  
  $tag_authored = $country;
  $tag_about = $country . '_biodiversity';

  $documents = json_decode(file_get_contents(file_create_url(file_build_uri('npt_nodestats/documents.json'))));
  $analysed_docs_authored = array();
  $analysed_docs_about = array();
  $analysed_result = array();
  
  foreach ($documents as $k => $doc) {
    // Only retrieve documents with UUID
    if (isset($doc->uuid)) {
      if (in_array($tag_authored, $doc->tags)) {
        $analysed_docs_authored[] = $doc;
      }
      if (in_array($tag_about, $doc->tags)) {
        $analysed_docs_about[] = $doc;
      }
    }
    unset($documents[$k]);
  }
  
  if (count($documents) == 0) drupal_set_message(t('Analysis finished.'));
  
  $authored_doc_count = count($analysed_docs_authored);
  $analysed_result['authored']['count'] = $authored_doc_count;

  $about_doc_count = count($analysed_docs_about);
  $analysed_result['about']['count'] = $about_doc_count;
  
  if ($authored_doc_count > 0) {
    // Insert publication_outlet from Mendeley detail call
    foreach ($analysed_docs_authored as $adoc) {
      $url = MENDELEY_DOC_DETAIL_URL . $adoc->uuid . '/?consumer_key=' . NPT_MENDELEY_CONSUMER_KEY;
      $detail = json_decode(file_get_contents($url));
      $adoc->publication_outlet = $detail->publication_outlet;
    }
    
    $authored_json = json_encode($analysed_docs_authored);
    $authored_doc = file_save_data($authored_json, file_build_uri('npt_nodestats/authored_doc.json'), FILE_EXISTS_REPLACE);
    
    drupal_set_message(format_plural($authored_doc_count,
      'There is a publication authored by scientists from %country',
      'There are @count publications authored by scientists from %country',
      array('%country' => $country)
    ));
    
    if ($authored_doc == TRUE) {
      drupal_set_message(t('Authored documents saved.'));
      $analysed_result['authored']['file'] = 'authored_doc.json';
    }
  } else {
    drupal_set_message(t('In GBIF Public Library, so far no document found authored by scientists from %country.', array('%country' => $country)));
  }


  if ($about_doc_count > 0) {
    // Insert publication_outlet from Mendeley detail call
    foreach ($analysed_docs_about as $adoc) {
      $url = MENDELEY_DOC_DETAIL_URL . $adoc->uuid . '/?consumer_key=' . NPT_MENDELEY_CONSUMER_KEY;
      $detail = json_decode(file_get_contents($url));
      $adoc->publication_outlet = $detail->publication_outlet;
    }

    $about_json = json_encode($analysed_docs_about);
    $about_doc = file_save_data($about_json, file_build_uri('npt_nodestats/about_doc.json'), FILE_EXISTS_REPLACE);

    drupal_set_message(format_plural($about_doc_count,
      'There is a publication about biodiversity of %country',
      'There are @count publications about biodiversity of %country',
      array('%country' => $country)
    ));
    
    if ($about_doc == TRUE) {
      drupal_set_message(t('About documents saved.'));
      $analysed_result['about']['file'] = 'about_doc.json';      
    }
  } else {
    drupal_set_message(t('In GBIF Public Library, so far no document found about biodiversity of %country.', array('%country' => $country)));    
  }
  
  variable_set('npt_nodestats_publication', $analysed_result);
}