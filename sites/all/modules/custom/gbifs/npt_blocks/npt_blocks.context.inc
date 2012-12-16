<?php
/**
 * @file
 * Default contexts
 */
/**
 * Implements hook_context_default_contexts()
 */
function npt_blocks_context_default_contexts() {
  $contexts = array();
  
  // NPT Front page context
  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'front_page';
  $context->description = 'Front page for NPT Startup';
  $context->tag = 'NPT';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-news-block_news_front' => array(
          'module' => 'views',
          'delta' => 'news-block_news_front',
          'region' => 'content',
          'weight' => '30',
        ),
        'views-latest_species-block' => array(
          'module' => 'views',
          'delta' => 'latest_species-block',
          'region' => 'content',
          'weight' => '32',
        ),
        'views-eol_images_front-block' => array(
          'module' => 'views',
          'delta' => 'eol_images_front-block',
          'region' => 'sidebar_second',
          'weight' => '30',
        ),
      ),
    ),
    'delta' => array(
      'delta_template' => 'front_page',
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Front page for NPT Startup');
  t('NPT');

  $contexts[$context->name] = $context;

  return $contexts;
}