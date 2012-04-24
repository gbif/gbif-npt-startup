<aside<?php print $attributes; ?>>
  <div<?php print $content_attributes; ?>>
	<label><a target="_blank" href="http://www.gbif.org/">Data Publishing Manuals</a></label>
	<ul>
		<li><a target="_blank" href="http://www.gbif.org/informatics/discoverymetadata/publishing/">Metadata</a></li>
		<li><a target="_blank" href="http://www.gbif.org/informatics/primary-data/publishing/">Occurrence Data</a></li>
		<li><a target="_blank" href="http://www.gbif.org/informatics/name-services/sharing-taxonomic-data/">Taxonomic Data</a></li>
	</ul>
	<label><a href="http://www.gbif.org/communications/contact-us/">Contact</a></label>
	<ul>
		<li><a target="_blank" href="http://www.gbif.org/communications/contact-us/help-desk/">Help Desk</a></li>
		<li><a target="_blank" href="http://www.gbif.org/communications/directory-of-contacts/gbif-secretariat/">Secretariat Staff</a></li>
	</ul>
    <?php
      print $content;
    ?>
  </div>
</aside>