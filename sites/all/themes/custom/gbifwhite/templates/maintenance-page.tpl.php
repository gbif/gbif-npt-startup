<?php
/**
 * @file
 * Implementation to display a single Drupal page while offline.
 *
 * All the available variables are mirrored in page.tpl.php.
 *
 * @see template_preprocess()
 * @see template_preprocess_maintenance_page()
 * @see bartik_process_maintenance_page()
 */
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML+RDFa 1.1//EN">
<html lang="en" dir="ltr" version="HTML+RDFa 1.1"
  xmlns:content="http://purl.org/rss/1.0/modules/content/"
  xmlns:dc="http://purl.org/dc/terms/"
  xmlns:foaf="http://xmlns.com/foaf/0.1/"
  xmlns:og="http://ogp.me/ns#"
  xmlns:rdfs="http://www.w3.org/2000/01/rdf-schema#"
  xmlns:sioc="http://rdfs.org/sioc/ns#"
  xmlns:sioct="http://rdfs.org/sioc/types#"
  xmlns:skos="http://www.w3.org/2004/02/skos/core#"
  xmlns:xsd="http://www.w3.org/2001/XMLSchema#">
<head profile="http://www.w3.org/1999/xhtml/vocab">
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<link rel="shortcut icon" href="http://npt.bkolocal:10088/sites/all/themes/gbifwhite/favicon.ico" type="image/vnd.microsoft.icon" />
<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, minimum-scale=1, user-scalable=no" />
<meta about="/node/2" property="sioc:num_replies" content="0" datatype="xsd:integer" />
<link rel="shortlink" href="/node/2" />
<meta name="Generator" content="Drupal 7 (http://drupal.org)" />
<link rel="canonical" href="/node/2" />
<meta content="Welcome to GBIF Benin!" about="/node/2" property="dc:title" />
  <title>Under maintenance</title>  
  <style type="text/css" media="all">@import url("http://npt.bkolocal:10088/modules/system/system.base.css?mfc8nk");
@import url("http://npt.bkolocal:10088/modules/system/system.menus.css?mfc8nk");
@import url("http://npt.bkolocal:10088/modules/system/system.messages.css?mfc8nk");
@import url("http://npt.bkolocal:10088/modules/system/system.theme.css?mfc8nk");</style>
<style type="text/css" media="all">@import url("http://npt.bkolocal:10088/sites/all/libraries/mediaelement/build/mediaelementplayer.min.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/modules/contrib/jquery_update/replace/ui/themes/base/minified/jquery.ui.core.min.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/modules/contrib/jquery_update/replace/ui/themes/base/minified/jquery.ui.theme.min.css?mfc8nk");
@import url("http://npt.bkolocal:10088/modules/overlay/overlay-parent.css?mfc8nk");</style>
<style type="text/css" media="all">@import url("http://npt.bkolocal:10088/sites/all/modules/contrib/comment_notify/comment_notify.css?mfc8nk");
@import url("http://npt.bkolocal:10088/modules/aggregator/aggregator.css?mfc8nk");
@import url("http://npt.bkolocal:10088/modules/comment/comment.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/modules/contrib/date/date_api/date.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/modules/custom/field_quick_delete/theme/field.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/modules/contrib/mollom/mollom.css?mfc8nk");
@import url("http://npt.bkolocal:10088/modules/node/node.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/modules/custom/gbifs/npt_setup/css/npt-setup.css?mfc8nk");
@import url("http://npt.bkolocal:10088/modules/search/search.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/modules/custom/twitterscript/css/twitterscript.css?mfc8nk");
@import url("http://npt.bkolocal:10088/modules/user/user.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/modules/contrib/views/css/views.css?mfc8nk");</style>
<style type="text/css" media="all">@import url("http://npt.bkolocal:10088/sites/all/modules/contrib/ckeditor/ckeditor.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/modules/contrib/colorbox/styles/default/colorbox_default_style.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/modules/contrib/ctools/css/ctools.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/modules/contrib/hide_submit/hide_submit.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/modules/contrib/ctools/css/modal.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/modules/contrib/modal_forms/css/modal_forms_popup.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/modules/contrib/biblio/biblio.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/modules/custom/twitter_pull/twitter-pull-listing.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/modules/custom/eolapi/css/eolapi.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/modules/custom/scratchpads/scratchpads_search_block/css/scratchpads_search_block.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/modules/custom/creative_commons/css/creative_commons.css?mfc8nk");</style>
<style type="text/css" media="all">@import url("http://npt.bkolocal:10088/sites/all/themes/omega/alpha/css/alpha-reset.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/themes/omega/alpha/css/alpha-mobile.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/themes/omega/alpha/css/alpha-alpha.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/themes/omega/omega/css/formalize.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/themes/omega/omega/css/omega-text.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/themes/omega/omega/css/omega-branding.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/themes/omega/omega/css/omega-menu.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/themes/omega/omega/css/omega-forms.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/themes/omega/omega/css/omega-visuals.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/themes/gbifwhite/css/global.css?mfc8nk");</style>

<!--[if (lt IE 9)&(!IEMobile)]>
<style type="text/css" media="all">@import url("http://npt.bkolocal:10088/sites/all/themes/gbifwhite/css/gbifwhite-alpha-default.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/themes/gbifwhite/css/gbifwhite-alpha-default-normal.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/themes/omega/alpha/css/grid/alpha_default/normal/alpha-default-normal-24.css?mfc8nk");</style>
<![endif]-->

<!--[if gte IE 9]><!-->
<style type="text/css" media="all and (min-width: 980px) and (min-device-width: 980px), all and (max-device-width: 1024px) and (min-width: 1024px) and (orientation:landscape)">@import url("http://npt.bkolocal:10088/sites/all/themes/gbifwhite/css/gbifwhite-alpha-default.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/themes/gbifwhite/css/gbifwhite-alpha-default-normal.css?mfc8nk");
@import url("http://npt.bkolocal:10088/sites/all/themes/omega/alpha/css/grid/alpha_default/normal/alpha-default-normal-24.css?mfc8nk");</style>
<!--<![endif]-->
</head>
<body class="html front not-logged-in page-node page-node- page-node-2 node-type-page">
  <div id="skip-link">
    <a href="#main-content" class="element-invisible element-focusable">Skip to main content</a>
  </div>
  <div class="region region-page-top" id="region-page-top">
  <div class="region-inner region-page-top-inner">
      </div>
</div>  <div class="page clearfix" id="page">
      <header id="section-header" class="section section-header">
  <div id="zone-user-wrapper" class="zone-wrapper zone-user-wrapper clearfix">  
  <div id="zone-user" class="zone zone-user clearfix container-24">
    <aside class="grid-5 region region-user-second account" id="region-user-second">
  <div class="region-inner region-user-second-inner">&nbsp;</div>
</aside>  </div>
</div><div id="zone-branding-wrapper" class="zone-wrapper zone-branding-wrapper clearfix">  
  <div id="zone-branding" class="zone zone-branding clearfix container-24">
    <div class="grid-19 region region-branding" id="region-branding">
  <div class="region-inner region-branding-inner">
        <div class="branding-data clearfix">
            <div class="logo-img">
        <a href="/" rel="home" title="GBIF Benin" class="active"><img src="http://npt.bkolocal:10088/sites/all/themes/custom/gbifwhite/logo.svg" alt="GBIF Benin" id="logo" /></a>      </div>
                        <hgroup class="site-name-slogan">        
                                
        <h1 class="site-name"><a href="/" rel="home" title="Home" class="active">GBIF Benin</a></h1>
                                        <h6 class="site-slogan">NPT Startup demonstration</h6>
              </hgroup>
          </div>
          </div>
</div>
<div class="grid-5 region region-search" id="region-search">
  <div class="region-inner region-search-inner">
    <div class="block block-search contextual-links-region block-form block-search-form odd block-without-title" id="block-search-form">
      <div class="block-inner clearfix">
        <div class="content clearfix">
        </div>
      </div>
    </div>
  </div>
</div>
</div><div id="zone-menu-wrapper" class="zone-wrapper zone-menu-wrapper clearfix">  
  <div id="zone-menu" class="zone zone-menu clearfix container-24">
    <div class="grid-19 suffix-5 region region-menu" id="region-menu">
  <div class="region-inner region-menu-inner">
        <div class="block block-system contextual-links-region block-menu block-main-menu block-system-main-menu odd block-without-title" id="block-system-main-menu">
  <div class="block-inner clearfix">
                
    <div class="content clearfix">
      <ul class="menu"><li class="first leaf"><a href="/"></a></li>
<li class="leaf"><a href="/news"></a></li>
<li class="leaf"><a href="/node/4" title="Biodiversity in Benin"></a></li>
<li class="leaf"><a href="/classification/5"></a></li>
<li class="leaf"><a href="/npt/nodestats" title="Statistics about GBIF Network"></a></li>
<li class="last leaf"><a href="/node/3" title="About GBIF Benin"></a></li>
</ul>    </div>
  </div>
</div>  </div>
</div>
  </div>
</div><div id="zone-header-wrapper" class="zone-wrapper zone-header-wrapper clearfix">  
  <div id="zone-header" class="zone zone-header clearfix container-24">
      </div>
</div></header>    
      <section id="section-content" class="section section-content">
  <div id="zone-content-wrapper" class="zone-wrapper zone-content-wrapper clearfix">  
  <div id="zone-content" class="zone zone-content clearfix container-24">    
        
        <div class="grid-16 region region-content" id="region-content">
  <div class="region-inner region-content-inner">
    <a id="main-content"></a>
                <h1 class="title" id="page-title">Under maintenance</h1>
                <div class="tabs clearfix"></div>        <div class="block block-system block-main block-system-main odd block-without-title" id="block-system-main">
  <div class="block-inner clearfix">
                
    <div class="content clearfix">
      <article about="/node/2" typeof="foaf:Document" class="node node-page node-published node-not-promoted node-not-sticky author-bko odd clearfix" id="node-page-2">
    <p>We are updating content for this demonstration site. Please come and visit later. Sorry for inconvenience and thank  you for your patience.</p>
    
    
  
  <div class="content clearfix">
    <div class="field field-name-body field-type-text-with-summary field-label-hidden"><div class="field-items">
    </div></div>
  </div>
  
  <div class="clearfix">
          <nav class="links node-links clearfix"></nav>
    
      </div>
</article>    </div>
  </div>
</div>      </div>
</div><aside class="grid-8 region region-sidebar-second" id="region-sidebar-second">
  <div class="region-inner region-sidebar-second-inner">
    <div class="block block-npt-blocks contextual-links-region block-how-to-publish block-npt-blocks-how-to-publish odd block-without-title" id="block-npt-blocks-how-to-publish">
  <div class="block-inner clearfix">
                
    <div class="content clearfix">
      <div class="item-list"><ul><li class="first"><a href="/node/1">How to publish data through the GBIF network?</a></li></ul></div>    </div>
  </div>
</div><div class="block block-views contextual-links-region block-eol-images-front-block block-views-eol-images-front-block even block-without-title" id="block-views-eol-images-front-block">
  <div class="block-inner clearfix">
                
    <div class="content clearfix">
      <div class="view view-eol-images-front view-id-eol_images_front view-display-id-block view-dom-id-d2d16e208b72834cf4b8d75535cc7012">
        
  
  
      <div class="view-content">
      
<noscript>
	<p class="error">Please enable Javascript, or reload the page.</p>
</noscript>
	    </div>
  
  
  
  
  
  
</div>    </div>
  </div>
</div>  </div>
</aside>  </div>
</div></section>    
  
      <footer id="section-footer" class="section section-footer">
  <div id="zone-postscript-wrapper" class="zone-wrapper zone-postscript-wrapper clearfix">  
  <div id="zone-postscript" class="zone zone-postscript clearfix container-24">
    <div class="grid-8 region region-postscript-first" id="region-postscript-first">
  <div class="region-inner region-postscript-first-inner">
    <section class="block block-aggregator contextual-links-region block-feed-1 block-aggregator-feed-1 odd" id="block-aggregator-feed-1">
  <div class="block-inner clearfix">
              <h2 class="block-title">GBIF News</h2>
            
    <div class="content clearfix">
      <div class="item-list"><ul><li class="first"><a href="http://www.gbif.org/communications/news-and-events/showsingle/article/call-for-proposals-for-the-2013-young-researchers-award">Call for proposals for the 2013 Young Researchers Award</a>
</li><li><a href="http://www.gbif.org/communications/news-and-events/showsingle/article/call-for-nominations-for-the-2013-ebbe-nielsen-prize">Call for nominations for the 2013 Ebbe Nielsen Prize</a>
</li><li><a href="http://www.gbif.org/communications/news-and-events/showsingle/article/peer-review-option-proposed-for-biodiversity-data">Peer review option proposed for biodiversity data</a>
</li><li><a href="http://www.gbif.org/communications/news-and-events/showsingle/article/brazil-joins-global-initiative-for-biodiversity-data-access">Brazil joins global initiative for biodiversity data access</a>
</li><li><a href="http://www.gbif.org/communications/news-and-events/showsingle/article/new-guide-for-compiling-national-species-checklists">New guide for compiling national species checklists</a>
</li><li><a href="http://www.gbif.org/communications/news-and-events/showsingle/article/national-biodiversity-information-grid-proposed-for-india">National biodiversity information ‘grid’ proposed for India</a>
</li><li><a href="http://www.gbif.org/communications/news-and-events/showsingle/article/gbif-signs-invasive-species-information-partnership">GBIF signs invasive species information partnership</a>
</li><li class="last"><a href="http://www.gbif.org/communications/news-and-events/showsingle/article/gbif-committed-to-provide-cbd-data-foundations-hobern">GBIF committed to provide CBD data foundations – Hobern</a>
</li></ul></div><div class="more-link"><a href="/aggregator/sources/1" title="View this feed&#039;s recent news.">More</a></div>    </div>
  </div>
</section>  </div>
</div><div class="grid-8 region region-postscript-second" id="region-postscript-second">
  <div class="region-inner region-postscript-second-inner">
    <section class="block block-aggregator contextual-links-region block-feed-2 block-aggregator-feed-2 odd" id="block-aggregator-feed-2">
  <div class="block-inner clearfix">
              <h2 class="block-title">GBIF Latest Online Resources</h2>
            
    <div class="content clearfix">
      <div class="item-list"><ul><li class="first"><a href="http://www.gbif.org/orc/?doc_id=3657">VERNON CMS (Collection Management System)</a>
</li><li><a href="http://www.gbif.org/orc/?doc_id=3447">Mandala</a>
</li><li><a href="http://www.gbif.org/orc/?doc_id=3676">Birder&#039;s Diary</a>
</li><li><a href="http://www.gbif.org/orc/?doc_id=3674">AviSys, Birding Database Software  </a>
</li><li><a href="http://www.gbif.org/orc/?doc_id=3673">AditSite, Wildlife Recording System</a>
</li><li><a href="http://www.gbif.org/orc/?doc_id=5049">B-VegAna, Anàlisis de Vegetació i Biodiversitat</a>
</li><li><a href="http://www.gbif.org/orc/?doc_id=5048">B-VegAna, Análisis de la Vegetación y la Biodiversidad</a>
</li><li class="last"><a href="http://www.gbif.org/orc/?doc_id=5047">B-VegAna, Biodiversity and Vegetation Analysis</a>
</li></ul></div><div class="more-link"><a href="/aggregator/sources/2" title="View this feed&#039;s recent news.">More</a></div>    </div>
  </div>
</section>  </div>
</div><div class="grid-8 region region-postscript-third" id="region-postscript-third">
  <div class="region-inner region-postscript-third-inner">
    <div class="block block-twitter-pull contextual-links-region block-0 block-twitter-pull-0 odd block-without-title" id="block-twitter-pull-0">
  <div class="block-inner clearfix">
                
    <div class="content clearfix">
      
<div class="tweets-pulled-listing">

      <h2>GBIF on Twitter</h2>
  
          
    <ul class="tweets-pulled-listing">
          <li>
        <div class="tweet-authorphoto"><img src="http://a0.twimg.com/profile_images/366073545/logo_normal.gif" alt="GBIF" /></div>
        <span class="tweet-author"><a href="http://twitter.com/GBIF">GBIF</a></span>
        <span class="tweet-text"><a href="http://twitter.com/brembs" rel="nofollow" title="@brembs">@brembs</a> Perhaps more to the point, <a href="http://twitter.com/eol" rel="nofollow" title="@eol">@eol</a> species pages include maps showing occurrences served via GBIF e.g. <a href="http://t.co/RiBDeiwk" rel="nofollow" title="http://t.co/RiBDeiwk">t.co/RiBDeiwk</a></span>
        <div class="tweet-time"><a href="http://twitter.com/GBIF/status/279186576188272640">1 week 5 hours ago.</a></div>

                  <div class="tweet-divider"></div>
                
      </li>
          <li>
        <div class="tweet-authorphoto"><img src="http://a0.twimg.com/profile_images/366073545/logo_normal.gif" alt="GBIF" /></div>
        <span class="tweet-author"><a href="http://twitter.com/GBIF">GBIF</a></span>
        <span class="tweet-text">Call for nominations for 2013 <a href="http://twitter.com/#!/search?q=%23gbif" title="#gbif" rel="nofollow">#gbif</a> Young Researchers Award <a href="http://t.co/UCuRf2si" rel="nofollow" title="http://t.co/UCuRf2si">t.co/UCuRf2si</a>  to foster innovative research in <a href="http://twitter.com/#!/search?q=%23biodiversity" title="#biodiversity" rel="nofollow">#biodiversity</a> informatics</span>
        <div class="tweet-time"><a href="http://twitter.com/GBIF/status/278509875976368128">1 week 2 days ago.</a></div>

                  <div class="tweet-divider"></div>
                
      </li>
          <li>
        <div class="tweet-authorphoto"><img src="http://a0.twimg.com/profile_images/366073545/logo_normal.gif" alt="GBIF" /></div>
        <span class="tweet-author"><a href="http://twitter.com/GBIF">GBIF</a></span>
        <span class="tweet-text">"I noticed that the <a href="http://twitter.com/#!/search?q=%23GBIF" title="#GBIF" rel="nofollow">#GBIF</a> data portal has fewer records than it used to – what happened?" <a href="http://t.co/eZtU2ypd" rel="nofollow" title="http://t.co/eZtU2ypd">t.co/eZtU2ypd</a>  blog on removing duplicates</span>
        <div class="tweet-time"><a href="http://twitter.com/GBIF/status/278186005788504064">1 week 2 days ago.</a></div>

                
      </li>
        </ul>
  </div>

    </div>
  </div>
</div>  </div>
</div>  </div>
</div><div id="zone-footer-wrapper" class="zone-wrapper zone-footer-wrapper clearfix">  
  <div id="zone-footer" class="zone zone-footer clearfix container-24">
    <aside class="grid-6 region region-footer-first" id="region-footer-first">
  <div class="region-inner region-footer-first-inner">
        </div>
</aside><aside class="grid-6 region region-footer-second" id="region-footer-second">
  <div class="region-inner region-footer-second-inner">
        </div>
</aside><aside class="grid-6 region region-footer-third" id="region-footer-third">
  <div class="region-inner region-footer-third-inner">
        </div>
</aside><aside class="grid-6 region region-footer-fourth" id="region-footer-fourth">
  <div class="region-inner region-footer-fourth-inner">
        </div>
</aside>  </div>
</div><div id="zone-credit-wrapper" class="zone-wrapper zone-credit-wrapper clearfix">  
  <div id="zone-credit" class="zone zone-credit clearfix container-24">
    <div class="grid-20 region region-credit-first" id="region-credit-first">
  <div class="region-inner region-credit-first-inner">
        <div class="block block-creative-commons contextual-links-region block-creative-commons block-creative-commons-creative-commons odd block-without-title" id="block-creative-commons-creative-commons">
  <div class="block-inner clearfix">
                
    <div class="content clearfix">
      <a href="http://creativecommons.org/licences/by/3.0/" class="cc-small"><img typeof="foaf:Image" src="http://i.creativecommons.org/l/by/3.0/80x15.png" width="80px" height="15px" alt="Creative Commons Licence" /></a>
<p>Except where otherwise noted, content on this site is licensed under a Creative Commons Attribution CC BY Licence. Usages of GBIF contents are subjected to <a href="http://data.gbif.org/tutorial/datasharingagreement">GBIF Data Sharing Agreement</a>.</p>    </div>
  </div>
</div>  </div>
</div><div class="grid-4 region region-credit-second" id="region-credit-second">
  <div class="region-inner region-credit-second-inner">
    <div class="block block-npt-blocks contextual-links-region block-credit-npt block-npt-blocks-credit-npt odd block-without-title" id="block-npt-blocks-credit-npt">
  <div class="block-inner clearfix">
                
    <div class="content clearfix">
      <span class="nptcredit"><p><a href="http://community.gbif.org/pg/groups/3507/nodes-portal-toolkit-npt/">The NPT Project</a></p></span>    </div>
  </div>
</div>  </div>
</div>  </div>
</div><div id="zone-credit-stretch-wrapper" class="zone-wrapper zone-credit-stretch-wrapper clearfix">  
  <div id="zone-credit-stretch" class="zone zone-credit-stretch clearfix container-24">
    <div class="grid-24 region region-credit-stretch" id="region-credit-stretch">
  <div class="region-inner region-credit-stretch-inner">
    <div class="block block-npt-blocks contextual-links-region block-credit-orgs block-npt-blocks-credit-orgs odd block-without-title" id="block-npt-blocks-credit-orgs">
  <div class="block-inner clearfix">
                
    <div class="content clearfix">
      <div class="item-list"><ul><li class="first"><a href="http://vbrant.eu/"><img typeof="foaf:Image" src="http://npt.bkolocal:10088/sites/all/modules/custom/gbifs/npt_blocks/images/vibrant_44.png" width="102" height="44" alt="ViBRANT logo" title="ViBRANT" /></a></li><li class="last"><a href="http://www.gbif.org/"><img typeof="foaf:Image" src="http://npt.bkolocal:10088/sites/all/modules/custom/gbifs/npt_blocks/images/gbif_48.png" width="49" height="48" alt="GBIF logo" title="GBIF" /></a></li></ul></div>    </div>
  </div>
</div>  </div>
</div>  </div>
</div></footer>  </div>  </body>
</html>