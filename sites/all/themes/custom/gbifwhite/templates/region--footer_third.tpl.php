<?php
/**
 * @file
 * GBIF Links
 */
?>
<aside<?php print $attributes; ?>>
  <div<?php print $content_attributes; ?>>
  <?php if (theme_get_setting('toggle_gbif_footer')): ?>
  	<label><a target="_blank" href="http://data.gbif.org/ws/">Webservices</a></label>
  	<ul>
  		<li><a target="_blank" href="http://ecat-dev.gbif.org/api/clb">Checklist Bank API</a></li>
  		<li><a target="_blank" href="http://tools.gbif.org/namefinder/api.do">Name Finder API</a></li>
  		<li><a target="_blank" href="http://tools.gbif.org/nameparser/api.do">Name Parser API</a></li>
  		<li><a target="_blank" href="http://data.gbif.org/ws/rest/occurrence">Occurrence API</a></li>
  		<li><a target="_blank" href="http://data.gbif.org/ws/rest/density">Occurrence Density API</a></li>
  		<li><a target="_blank" href="http://code.google.com/p/gbif-registry/wiki/ResourceAPI">Registry API</a></li>
  	</ul>
  <?php endif; ?>
    <?php
      print $content;
    ?>
  </div>
</aside>