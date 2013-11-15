<?php
/**
 * @file
 * GBIF Credit
 */
?>
<div<?php print $attributes; ?>>
  <div<?php print $content_attributes; ?>>
    <?php if (theme_get_setting('toggle_gbif_credit')): ?>
      <p>&copy;2012 <a href="www.gbif.org">Global Biodiversity Information Facility</a>. Data publishers retain all rights to data.</p>
    <?php endif; ?>
    <?php
      print $content;
    ?>
  </div>
</div>