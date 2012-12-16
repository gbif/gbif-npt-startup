<?php
/**
 * @file
 * Default views with npt_blocks.
 *
 */

/**
 * Implementation of hook_views_default_views()
 */
function npt_blocks_views_default_views() {
  
  // EOL Images for the front page.
  
  $view = new view;
  $view->name = 'eol_images_front';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'eolapi';
  $view->human_name = 'EOL Images front';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '18';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'eolapi';
  $handler->display->display_options['row_plugin'] = 'entity';
  $handler->display->display_options['row_options']['view_mode'] = 'teaser';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'This block is designed to show cached images from EOL. This site retrieves EOL contents according to species information that has been imported. All cached images will come with IPR statements attached.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
  /* Field: Encyclopaedia of Life data: Encyclopaedia of life data ID */
  $handler->display->display_options['fields']['eid']['id'] = 'eid';
  $handler->display->display_options['fields']['eid']['table'] = 'eolapi';
  $handler->display->display_options['fields']['eid']['field'] = 'eid';
  /* Sort criterion: Global: Random */
  $handler->display->display_options['sorts']['random']['id'] = 'random';
  $handler->display->display_options['sorts']['random']['table'] = 'views';
  $handler->display->display_options['sorts']['random']['field'] = 'random';
  /* Contextual filter: Encyclopaedia of Life data: Taxonomy field (eolapi_taxonomy) */
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['id'] = 'eolapi_taxonomy_tid';
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['table'] = 'field_data_eolapi_taxonomy';
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['field'] = 'eolapi_taxonomy_tid';
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['not'] = 0;
  /* Filter criterion: Encyclopaedia of Life data: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'eolapi';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'stillimage' => 'stillimage',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['block_description'] = 'EOL images for the front page.';

  $views[$view->name] = $view;
  
  // Latest species list
  
  $view = new view;
  $view->name = 'latest_species';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Latest Species';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Latest Taxa';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = 1;
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'species_info' => 'species_info',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['block_description'] = 'Latest taxa for front page';

  $views[$view->name] = $view;
    
  return $views;
}

/**
 * Implementation of hook_views_default_views_alter(&$views)
 */
function npt_blocks_views_default_views_alter(&$views) {
  // Alter species_overview_map by scratchpads_species  
  unset($views['species_overview_map']->display['default']->handler->display->display_options['arguments']);
  unset($views['species_overview_map']->display['default']->handler->display->display_options['filters']['status']);
  unset($views['species_overview_map']->display['default']->handler->display->display_options['filters']['type']);
  
  // Add no results behaviour for species biblio
  $species_biblio_display_default = $views['species_biblio']->display['default'];
  $species_biblio_display_default->handler->display->display_options['empty']['area']['id'] = 'area';
  $species_biblio_display_default->handler->display->display_options['empty']['area']['table'] = 'views';
  $species_biblio_display_default->handler->display->display_options['empty']['area']['field'] = 'area';
  $species_biblio_display_default->handler->display->display_options['empty']['area']['empty'] = FALSE;
  $species_biblio_display_default->handler->display->display_options['empty']['area']['content'] = 'Currently no local literature data hosted for this taxon.';
  $species_biblio_display_default->handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $species_biblio_display_default->handler->display->display_options['empty']['area']['tokenize'] = 0;
  
  // Add no results behaviour for species map
  $species_map_display_default = $views['species_map']->display['default'];
  $species_map_display_default->handler->display->display_options['empty']['area']['id'] = 'area';
  $species_map_display_default->handler->display->display_options['empty']['area']['table'] = 'views';
  $species_map_display_default->handler->display->display_options['empty']['area']['field'] = 'area';
  $species_map_display_default->handler->display->display_options['empty']['area']['empty'] = FALSE;
  $species_map_display_default->handler->display->display_options['empty']['area']['content'] = 'Currently no local map data hosted for this taxon.';
  $species_map_display_default->handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $species_map_display_default->handler->display->display_options['empty']['area']['tokenize'] = 0;
  
  // Add no results behavious for species specimen observation
  $species_speciemen_display_default = $views['species_specimen']->display['default'];
  $species_speciemen_display_default->handler->display->display_options['empty']['area']['id'] = 'area';
  $species_speciemen_display_default->handler->display->display_options['empty']['area']['table'] = 'views';
  $species_speciemen_display_default->handler->display->display_options['empty']['area']['field'] = 'area';
  $species_speciemen_display_default->handler->display->display_options['empty']['area']['empty'] = FALSE;
  $species_speciemen_display_default->handler->display->display_options['empty']['area']['content'] = 'Currently no local specimen data hosted for this taxon.';
  $species_speciemen_display_default->handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $species_speciemen_display_default->handler->display->display_options['empty']['area']['tokenize'] = 0;
}