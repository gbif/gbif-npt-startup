<?php
/**
 * @file
 * GBIF links
 */
?>
<aside<?php print $attributes; ?>>
  <div<?php print $content_attributes; ?>>
  <?php if (theme_get_setting('toggle_gbif_footer')): ?>
  	<label><a target="_blank" href="http://tools.gbif.org/">TOOLS</a></label>
  	<ul>
  		<li><a target="_blank" href="http://tools.gbif.org/namefinder">Name Finder</a></li>
  		<li><a target="_blank" href="http://tools.gbif.org/nameparser">Name Parser</a></li>
  		<li><a target="_blank" href="http://tools.gbif.org/dwca-assistant">DwC Archive Assistant</a></li>
  		<li><a target="_blank" href="http://tools.gbif.org/spreadsheet-processor">Spreadsheet Processor</a></li>
  		<li><a target="_blank" href="http://tools.gbif.org/dwca-validator">DwC Archive Validator</a></li>
  		<li><a target="_blank" href="http://tools.gbif.org/dwca-register/">Dataset Registration</a></li>
  	</ul>
  <?php endif; ?>
    <?php
      print $content;
    ?>
  </div>
</aside>