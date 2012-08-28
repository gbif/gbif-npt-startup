<?php
/**
 * @file
 * npt_role_and_permissions.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function npt_role_and_permissions_user_default_permissions() {
  $permissions = array();

  // Exported permission: access administration pages
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      0 => 'maintainer',
    ),
    'module' => 'system',
  );

  // Exported permission: access all views
  $permissions['access all views'] = array(
    'name' => 'access all views',
    'roles' => array(
      0 => 'maintainer',
    ),
    'module' => 'views',
  );

  // Exported permission: access biblio content
  $permissions['access biblio content'] = array(
    'name' => 'access biblio content',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
      2 => 'contributor',
      3 => 'editor',
      4 => 'maintainer',
    ),
    'module' => 'biblio',
  );

  // Exported permission: access comments
  $permissions['access comments'] = array(
    'name' => 'access comments',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
      2 => 'contributor',
      3 => 'editor',
      4 => 'maintainer',
    ),
    'module' => 'comment',
  );

  // Exported permission: access content
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
      2 => 'contributor',
      3 => 'editor',
      4 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: access content overview
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: access contextual links
  $permissions['access contextual links'] = array(
    'name' => 'access contextual links',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
      2 => 'contributor',
      3 => 'editor',
      4 => 'maintainer',
    ),
    'module' => 'contextual',
  );

  // Exported permission: access dashboard
  $permissions['access dashboard'] = array(
    'name' => 'access dashboard',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'dashboard',
  );

  // Exported permission: access form flows
  $permissions['access form flows'] = array(
    'name' => 'access form flows',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
      2 => 'contributor',
      3 => 'editor',
      4 => 'maintainer',
    ),
    'module' => 'formflow',
  );

  // Exported permission: access lexicon
  $permissions['access lexicon'] = array(
    'name' => 'access lexicon',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
      2 => 'contributor',
      3 => 'editor',
      4 => 'maintainer',
    ),
    'module' => 'lexicon',
  );

  // Exported permission: access news feeds
  $permissions['access news feeds'] = array(
    'name' => 'access news feeds',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
    ),
    'module' => 'aggregator',
  );

  // Exported permission: access overlay
  $permissions['access overlay'] = array(
    'name' => 'access overlay',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
      2 => 'contributor',
      3 => 'editor',
      4 => 'maintainer',
    ),
    'module' => 'overlay',
  );

  // Exported permission: access site in maintenance mode
  $permissions['access site in maintenance mode'] = array(
    'name' => 'access site in maintenance mode',
    'roles' => array(
      0 => 'maintainer',
    ),
    'module' => 'system',
  );

  // Exported permission: access site reports
  $permissions['access site reports'] = array(
    'name' => 'access site reports',
    'roles' => array(),
  );

  // Exported permission: access subpermission form
  $permissions['access subpermission form'] = array(
    'name' => 'access subpermission form',
    'roles' => array(
      0 => 'maintainer',
    ),
    'module' => 'subpermissions',
  );

  // Exported permission: access toolbar
  $permissions['access toolbar'] = array(
    'name' => 'access toolbar',
    'roles' => array(
      0 => 'authenticated user',
      1 => 'contributor',
      2 => 'editor',
      3 => 'maintainer',
    ),
    'module' => 'toolbar',
  );

  // Exported permission: access tools
  $permissions['access tools'] = array(
    'name' => 'access tools',
    'roles' => array(
      0 => 'maintainer',
    ),
    'module' => 'tools',
  );

  // Exported permission: access user profiles
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
      2 => 'contributor',
      3 => 'editor',
      4 => 'maintainer',
    ),
    'module' => 'user',
  );

  // Exported permission: administer actions
  $permissions['administer actions'] = array(
    'name' => 'administer actions',
    'roles' => array(),
  );

  // Exported permission: administer biblio
  $permissions['administer biblio'] = array(
    'name' => 'administer biblio',
    'roles' => array(),
  );

  // Exported permission: administer blocks
  $permissions['administer blocks'] = array(
    'name' => 'administer blocks',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'block',
  );

  // Exported permission: administer ckeditor
  $permissions['administer ckeditor'] = array(
    'name' => 'administer ckeditor',
    'roles' => array(),
  );

  // Exported permission: administer comments
  $permissions['administer comments'] = array(
    'name' => 'administer comments',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'comment',
  );

  // Exported permission: administer content types
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(
      0 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: administer facets
  $permissions['administer facets'] = array(
    'name' => 'administer facets',
    'roles' => array(),
  );

  // Exported permission: administer features
  $permissions['administer features'] = array(
    'name' => 'administer features',
    'roles' => array(),
  );

  // Exported permission: administer feeds
  $permissions['administer feeds'] = array(
    'name' => 'administer feeds',
    'roles' => array(
      0 => 'maintainer',
    ),
    'module' => 'feeds',
  );

  // Exported permission: administer feeds_tamper
  $permissions['administer feeds_tamper'] = array(
    'name' => 'administer feeds_tamper',
    'roles' => array(),
  );

  // Exported permission: administer fieldgroups
  $permissions['administer fieldgroups'] = array(
    'name' => 'administer fieldgroups',
    'roles' => array(
      0 => 'maintainer',
    ),
    'module' => 'field_group',
  );

  // Exported permission: administer files
  $permissions['administer files'] = array(
    'name' => 'administer files',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: administer filters
  $permissions['administer filters'] = array(
    'name' => 'administer filters',
    'roles' => array(),
  );

  // Exported permission: administer form flows
  $permissions['administer form flows'] = array(
    'name' => 'administer form flows',
    'roles' => array(
      0 => 'maintainer',
    ),
    'module' => 'formflow',
  );

  // Exported permission: administer hashcash
  $permissions['administer hashcash'] = array(
    'name' => 'administer hashcash',
    'roles' => array(),
  );

  // Exported permission: administer image styles
  $permissions['administer image styles'] = array(
    'name' => 'administer image styles',
    'roles' => array(),
  );

  // Exported permission: administer lexicon
  $permissions['administer lexicon'] = array(
    'name' => 'administer lexicon',
    'roles' => array(
      0 => 'maintainer',
    ),
    'module' => 'lexicon',
  );

  // Exported permission: administer linkit
  $permissions['administer linkit'] = array(
    'name' => 'administer linkit',
    'roles' => array(),
  );

  // Exported permission: administer menu
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(
      0 => 'maintainer',
    ),
    'module' => 'menu',
  );

  // Exported permission: administer modules
  $permissions['administer modules'] = array(
    'name' => 'administer modules',
    'roles' => array(),
  );

  // Exported permission: administer news feeds
  $permissions['administer news feeds'] = array(
    'name' => 'administer news feeds',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'aggregator',
  );

  // Exported permission: administer nodes
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      0 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: administer permissions
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(),
  );

  // Exported permission: administer search
  $permissions['administer search'] = array(
    'name' => 'administer search',
    'roles' => array(),
  );

  // Exported permission: administer shortcuts
  $permissions['administer shortcuts'] = array(
    'name' => 'administer shortcuts',
    'roles' => array(
      0 => 'maintainer',
    ),
    'module' => 'shortcut',
  );

  // Exported permission: administer site configuration
  $permissions['administer site configuration'] = array(
    'name' => 'administer site configuration',
    'roles' => array(
      0 => 'maintainer',
    ),
    'module' => 'system',
  );

  // Exported permission: administer software updates
  $permissions['administer software updates'] = array(
    'name' => 'administer software updates',
    'roles' => array(),
  );

  // Exported permission: administer subpermission
  $permissions['administer subpermission'] = array(
    'name' => 'administer subpermission',
    'roles' => array(),
  );

  // Exported permission: administer taxonomy
  $permissions['administer taxonomy'] = array(
    'name' => 'administer taxonomy',
    'roles' => array(
      0 => 'maintainer',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: administer themes
  $permissions['administer themes'] = array(
    'name' => 'administer themes',
    'roles' => array(
      0 => 'maintainer',
    ),
    'module' => 'system',
  );

  // Exported permission: administer users
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      0 => 'maintainer',
    ),
    'module' => 'user',
  );

  // Exported permission: administer uuid
  $permissions['administer uuid'] = array(
    'name' => 'administer uuid',
    'roles' => array(),
  );

  // Exported permission: administer views
  $permissions['administer views'] = array(
    'name' => 'administer views',
    'roles' => array(
      0 => 'maintainer',
    ),
    'module' => 'views',
  );

  // Exported permission: allow CKFinder file uploads
  $permissions['allow CKFinder file uploads'] = array(
    'name' => 'allow CKFinder file uploads',
    'roles' => array(),
  );

  // Exported permission: assign all roles
  $permissions['assign all roles'] = array(
    'name' => 'assign all roles',
    'roles' => array(
      0 => 'maintainer',
    ),
    'module' => 'role_delegation',
  );

  // Exported permission: assign contributor role
  $permissions['assign contributor role'] = array(
    'name' => 'assign contributor role',
    'roles' => array(),
  );

  // Exported permission: assign editor role
  $permissions['assign editor role'] = array(
    'name' => 'assign editor role',
    'roles' => array(),
  );

  // Exported permission: assign maintainer role
  $permissions['assign maintainer role'] = array(
    'name' => 'assign maintainer role',
    'roles' => array(),
  );

  // Exported permission: block IP addresses
  $permissions['block IP addresses'] = array(
    'name' => 'block IP addresses',
    'roles' => array(),
  );

  // Exported permission: bypass node access
  $permissions['bypass node access'] = array(
    'name' => 'bypass node access',
    'roles' => array(
      0 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: cancel account
  $permissions['cancel account'] = array(
    'name' => 'cancel account',
    'roles' => array(
      0 => 'authenticated user',
      1 => 'contributor',
      2 => 'editor',
      3 => 'maintainer',
    ),
    'module' => 'user',
  );

  // Exported permission: change own username
  $permissions['change own username'] = array(
    'name' => 'change own username',
    'roles' => array(
      0 => 'authenticated user',
      1 => 'contributor',
      2 => 'editor',
      3 => 'maintainer',
    ),
    'module' => 'user',
  );

  // Exported permission: clear biblio_oai_pmh feeds
  $permissions['clear biblio_oai_pmh feeds'] = array(
    'name' => 'clear biblio_oai_pmh feeds',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'feeds',
  );

  // Exported permission: clear node feeds
  $permissions['clear node feeds'] = array(
    'name' => 'clear node feeds',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'feeds',
  );

  // Exported permission: clear node_importer_biblio feeds
  $permissions['clear node_importer_biblio feeds'] = array(
    'name' => 'clear node_importer_biblio feeds',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'feeds',
  );

  // Exported permission: clear node_importer_media_gallery feeds
  $permissions['clear node_importer_media_gallery feeds'] = array(
    'name' => 'clear node_importer_media_gallery feeds',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'feeds',
  );

  // Exported permission: clear node_importer_page feeds
  $permissions['clear node_importer_page feeds'] = array(
    'name' => 'clear node_importer_page feeds',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'feeds',
  );

  // Exported permission: clear node_importer_spm feeds
  $permissions['clear node_importer_spm feeds'] = array(
    'name' => 'clear node_importer_spm feeds',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'feeds',
  );

  // Exported permission: clear taxonomy_importer_image_keywords feeds
  $permissions['clear taxonomy_importer_image_keywords feeds'] = array(
    'name' => 'clear taxonomy_importer_image_keywords feeds',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'feeds',
  );

  // Exported permission: clear taxonomy_importer_imaging_technique feeds
  $permissions['clear taxonomy_importer_imaging_technique feeds'] = array(
    'name' => 'clear taxonomy_importer_imaging_technique feeds',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'feeds',
  );

  // Exported permission: clear taxonomy_importer_preparation_technique feeds
  $permissions['clear taxonomy_importer_preparation_technique feeds'] = array(
    'name' => 'clear taxonomy_importer_preparation_technique feeds',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'feeds',
  );

  // Exported permission: clear user feeds
  $permissions['clear user feeds'] = array(
    'name' => 'clear user feeds',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'feeds',
  );

  // Exported permission: clone node
  $permissions['clone node'] = array(
    'name' => 'clone node',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'clone',
  );

  // Exported permission: clone own nodes
  $permissions['clone own nodes'] = array(
    'name' => 'clone own nodes',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'clone',
  );

  // Exported permission: create biblio content
  $permissions['create biblio content'] = array(
    'name' => 'create biblio content',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: create form flows
  $permissions['create form flows'] = array(
    'name' => 'create form flows',
    'roles' => array(
      0 => 'maintainer',
    ),
    'module' => 'formflow',
  );

  // Exported permission: create media_gallery content
  $permissions['create media_gallery content'] = array(
    'name' => 'create media_gallery content',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: create page content
  $permissions['create page content'] = array(
    'name' => 'create page content',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: create spm content
  $permissions['create spm content'] = array(
    'name' => 'create spm content',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: customize ckeditor
  $permissions['customize ckeditor'] = array(
    'name' => 'customize ckeditor',
    'roles' => array(),
  );

  // Exported permission: customize shortcut links
  $permissions['customize shortcut links'] = array(
    'name' => 'customize shortcut links',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'shortcut',
  );

  // Exported permission: delete any biblio content
  $permissions['delete any biblio content'] = array(
    'name' => 'delete any biblio content',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any media_gallery content
  $permissions['delete any media_gallery content'] = array(
    'name' => 'delete any media_gallery content',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any page content
  $permissions['delete any page content'] = array(
    'name' => 'delete any page content',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any spm content
  $permissions['delete any spm content'] = array(
    'name' => 'delete any spm content',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own biblio content
  $permissions['delete own biblio content'] = array(
    'name' => 'delete own biblio content',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own media_gallery content
  $permissions['delete own media_gallery content'] = array(
    'name' => 'delete own media_gallery content',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own page content
  $permissions['delete own page content'] = array(
    'name' => 'delete own page content',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own spm content
  $permissions['delete own spm content'] = array(
    'name' => 'delete own spm content',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: delete revisions
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: delete terms in 1
  $permissions['delete terms in 1'] = array(
    'name' => 'delete terms in 1',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: delete terms in 2
  $permissions['delete terms in 2'] = array(
    'name' => 'delete terms in 2',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: delete terms in 3
  $permissions['delete terms in 3'] = array(
    'name' => 'delete terms in 3',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: edit any biblio content
  $permissions['edit any biblio content'] = array(
    'name' => 'edit any biblio content',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any media_gallery content
  $permissions['edit any media_gallery content'] = array(
    'name' => 'edit any media_gallery content',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any page content
  $permissions['edit any page content'] = array(
    'name' => 'edit any page content',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any spm content
  $permissions['edit any spm content'] = array(
    'name' => 'edit any spm content',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: edit biblio authors
  $permissions['edit biblio authors'] = array(
    'name' => 'edit biblio authors',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'biblio',
  );

  // Exported permission: edit by all biblio authors
  $permissions['edit by all biblio authors'] = array(
    'name' => 'edit by all biblio authors',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'biblio',
  );

  // Exported permission: edit file
  $permissions['edit file'] = array(
    'name' => 'edit file',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: edit form flows
  $permissions['edit form flows'] = array(
    'name' => 'edit form flows',
    'roles' => array(
      0 => 'maintainer',
    ),
    'module' => 'formflow',
  );

  // Exported permission: edit own biblio content
  $permissions['edit own biblio content'] = array(
    'name' => 'edit own biblio content',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own comments
  $permissions['edit own comments'] = array(
    'name' => 'edit own comments',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'comment',
  );

  // Exported permission: edit own media_gallery content
  $permissions['edit own media_gallery content'] = array(
    'name' => 'edit own media_gallery content',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own page content
  $permissions['edit own page content'] = array(
    'name' => 'edit own page content',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own spm content
  $permissions['edit own spm content'] = array(
    'name' => 'edit own spm content',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: edit terms in 1
  $permissions['edit terms in 1'] = array(
    'name' => 'edit terms in 1',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: edit terms in 2
  $permissions['edit terms in 2'] = array(
    'name' => 'edit terms in 2',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: edit terms in 3
  $permissions['edit terms in 3'] = array(
    'name' => 'edit terms in 3',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: import biblio_oai_pmh feeds
  $permissions['import biblio_oai_pmh feeds'] = array(
    'name' => 'import biblio_oai_pmh feeds',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'feeds',
  );

  // Exported permission: import from file
  $permissions['import from file'] = array(
    'name' => 'import from file',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'biblio',
  );

  // Exported permission: import media
  $permissions['import media'] = array(
    'name' => 'import media',
    'roles' => array(),
  );

  // Exported permission: import node feeds
  $permissions['import node feeds'] = array(
    'name' => 'import node feeds',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'feeds',
  );

  // Exported permission: import node_importer_biblio feeds
  $permissions['import node_importer_biblio feeds'] = array(
    'name' => 'import node_importer_biblio feeds',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'feeds',
  );

  // Exported permission: import node_importer_media_gallery feeds
  $permissions['import node_importer_media_gallery feeds'] = array(
    'name' => 'import node_importer_media_gallery feeds',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'feeds',
  );

  // Exported permission: import node_importer_page feeds
  $permissions['import node_importer_page feeds'] = array(
    'name' => 'import node_importer_page feeds',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'feeds',
  );

  // Exported permission: import node_importer_spm feeds
  $permissions['import node_importer_spm feeds'] = array(
    'name' => 'import node_importer_spm feeds',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'feeds',
  );

  // Exported permission: import taxonomy_importer_image_keywords feeds
  $permissions['import taxonomy_importer_image_keywords feeds'] = array(
    'name' => 'import taxonomy_importer_image_keywords feeds',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'feeds',
  );

  // Exported permission: import taxonomy_importer_imaging_technique feeds
  $permissions['import taxonomy_importer_imaging_technique feeds'] = array(
    'name' => 'import taxonomy_importer_imaging_technique feeds',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'feeds',
  );

  // Exported permission: import taxonomy_importer_preparation_technique feeds
  $permissions['import taxonomy_importer_preparation_technique feeds'] = array(
    'name' => 'import taxonomy_importer_preparation_technique feeds',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'feeds',
  );

  // Exported permission: import user feeds
  $permissions['import user feeds'] = array(
    'name' => 'import user feeds',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'feeds',
  );

  // Exported permission: manage features
  $permissions['manage features'] = array(
    'name' => 'manage features',
    'roles' => array(),
  );

  // Exported permission: post comments
  $permissions['post comments'] = array(
    'name' => 'post comments',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
      2 => 'contributor',
      3 => 'editor',
      4 => 'maintainer',
    ),
    'module' => 'comment',
  );

  // Exported permission: revert revisions
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      0 => 'editor',
      1 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: search content
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
      2 => 'contributor',
      3 => 'editor',
      4 => 'maintainer',
    ),
    'module' => 'search',
  );

  // Exported permission: select account cancellation method
  $permissions['select account cancellation method'] = array(
    'name' => 'select account cancellation method',
    'roles' => array(),
  );

  // Exported permission: show download links
  $permissions['show download links'] = array(
    'name' => 'show download links',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
      2 => 'contributor',
      3 => 'editor',
      4 => 'maintainer',
    ),
    'module' => 'biblio',
  );

  // Exported permission: show export links
  $permissions['show export links'] = array(
    'name' => 'show export links',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
      2 => 'contributor',
      3 => 'editor',
      4 => 'maintainer',
    ),
    'module' => 'biblio',
  );

  // Exported permission: show filter tab
  $permissions['show filter tab'] = array(
    'name' => 'show filter tab',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
      2 => 'contributor',
      3 => 'editor',
      4 => 'maintainer',
    ),
    'module' => 'biblio',
  );

  // Exported permission: show own download links
  $permissions['show own download links'] = array(
    'name' => 'show own download links',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
      2 => 'contributor',
      3 => 'editor',
      4 => 'maintainer',
    ),
    'module' => 'biblio',
  );

  // Exported permission: show sort links
  $permissions['show sort links'] = array(
    'name' => 'show sort links',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
      2 => 'contributor',
      3 => 'editor',
      4 => 'maintainer',
    ),
    'module' => 'biblio',
  );

  // Exported permission: skip comment approval
  $permissions['skip comment approval'] = array(
    'name' => 'skip comment approval',
    'roles' => array(
      0 => 'authenticated user',
      1 => 'contributor',
      2 => 'editor',
      3 => 'maintainer',
    ),
    'module' => 'comment',
  );

  // Exported permission: submit form without hashcash
  $permissions['submit form without hashcash'] = array(
    'name' => 'submit form without hashcash',
    'roles' => array(
      0 => 'authenticated user',
      1 => 'contributor',
      2 => 'editor',
      3 => 'maintainer',
    ),
    'module' => 'hashcash',
  );

  // Exported permission: switch shortcut sets
  $permissions['switch shortcut sets'] = array(
    'name' => 'switch shortcut sets',
    'roles' => array(),
  );

  // Exported permission: tamper biblio_oai_pmh
  $permissions['tamper biblio_oai_pmh'] = array(
    'name' => 'tamper biblio_oai_pmh',
    'roles' => array(),
  );

  // Exported permission: tamper node
  $permissions['tamper node'] = array(
    'name' => 'tamper node',
    'roles' => array(),
  );

  // Exported permission: tamper node_importer_biblio
  $permissions['tamper node_importer_biblio'] = array(
    'name' => 'tamper node_importer_biblio',
    'roles' => array(),
  );

  // Exported permission: tamper node_importer_media_gallery
  $permissions['tamper node_importer_media_gallery'] = array(
    'name' => 'tamper node_importer_media_gallery',
    'roles' => array(),
  );

  // Exported permission: tamper node_importer_page
  $permissions['tamper node_importer_page'] = array(
    'name' => 'tamper node_importer_page',
    'roles' => array(),
  );

  // Exported permission: tamper node_importer_spm
  $permissions['tamper node_importer_spm'] = array(
    'name' => 'tamper node_importer_spm',
    'roles' => array(),
  );

  // Exported permission: tamper taxonomy_importer_image_keywords
  $permissions['tamper taxonomy_importer_image_keywords'] = array(
    'name' => 'tamper taxonomy_importer_image_keywords',
    'roles' => array(),
  );

  // Exported permission: tamper taxonomy_importer_imaging_technique
  $permissions['tamper taxonomy_importer_imaging_technique'] = array(
    'name' => 'tamper taxonomy_importer_imaging_technique',
    'roles' => array(),
  );

  // Exported permission: tamper taxonomy_importer_preparation_technique
  $permissions['tamper taxonomy_importer_preparation_technique'] = array(
    'name' => 'tamper taxonomy_importer_preparation_technique',
    'roles' => array(),
  );

  // Exported permission: tamper user
  $permissions['tamper user'] = array(
    'name' => 'tamper user',
    'roles' => array(),
  );

  // Exported permission: toggle placeholder blocks
  $permissions['toggle placeholder blocks'] = array(
    'name' => 'toggle placeholder blocks',
    'roles' => array(
      0 => 'contributor',
      1 => 'editor',
      2 => 'maintainer',
    ),
    'module' => 'scratchpads_blocks',
  );

  // Exported permission: use PHP for title patterns
  $permissions['use PHP for title patterns'] = array(
    'name' => 'use PHP for title patterns',
    'roles' => array(),
  );

  // Exported permission: use advanced search
  $permissions['use advanced search'] = array(
    'name' => 'use advanced search',
    'roles' => array(),
  );

  // Exported permission: use text format comment_filtered_html
  $permissions['use text format comment_filtered_html'] = array(
    'name' => 'use text format comment_filtered_html',
    'roles' => array(
      0 => 'authenticated user',
      1 => 'contributor',
      2 => 'editor',
      3 => 'maintainer',
    ),
    'module' => 'filter',
  );

  // Exported permission: use text format filtered_html
  $permissions['use text format filtered_html'] = array(
    'name' => 'use text format filtered_html',
    'roles' => array(
      0 => 'authenticated user',
      1 => 'contributor',
      2 => 'editor',
      3 => 'maintainer',
    ),
    'module' => 'filter',
  );

  // Exported permission: view advanced help index
  $permissions['view advanced help index'] = array(
    'name' => 'view advanced help index',
    'roles' => array(
      0 => 'authenticated user',
    ),
    'module' => 'advanced_help',
  );

  // Exported permission: view advanced help popup
  $permissions['view advanced help popup'] = array(
    'name' => 'view advanced help popup',
    'roles' => array(
      0 => 'authenticated user',
    ),
    'module' => 'advanced_help',
  );

  // Exported permission: view advanced help topic
  $permissions['view advanced help topic'] = array(
    'name' => 'view advanced help topic',
    'roles' => array(
      0 => 'authenticated user',
    ),
    'module' => 'advanced_help',
  );

  // Exported permission: view file
  $permissions['view file'] = array(
    'name' => 'view file',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
      2 => 'contributor',
      3 => 'editor',
      4 => 'maintainer',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: view full text
  $permissions['view full text'] = array(
    'name' => 'view full text',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
      2 => 'contributor',
      3 => 'editor',
      4 => 'maintainer',
    ),
    'module' => 'biblio',
  );

  // Exported permission: view own unpublished content
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      0 => 'authenticated user',
      1 => 'contributor',
      2 => 'editor',
      3 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: view revisions
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
      2 => 'contributor',
      3 => 'editor',
      4 => 'maintainer',
    ),
    'module' => 'node',
  );

  // Exported permission: view the administration theme
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
      2 => 'contributor',
      3 => 'editor',
      4 => 'maintainer',
    ),
    'module' => 'system',
  );

  return $permissions;
}
