<?php

// Get header
require("ims_header.php");

// Grab setup from general include file
require("ims_include.php");

$nodeID = @$_REQUEST['ID'] . @$_REQUEST['NODE_ID'] ;

// Check for valid Node ID
If ( $nodeID > 0 ) {
	// Node ID ok: Find data
	$myError = 0;
	$Node_find = $IMS->newFindCommand('WNOD_Node');
	$Node_find->addFindCriterion(     '__kp_ID', $nodeID );

	$Node_result = $Node_find->execute(); 
	
	// Handle error (if any)
	if(FileMaker::isError($Node_result)) {
		fmsTrapError($Node_result,"error.php");
		$myError = 1;
	};
} else {
	$myError = 1;
};

?>

<?php

$Node_row = current($Node_result->getRecords());

echo '<a href="javascript:history.back()">back</a>' ;
echo '<table width="500" border="0">';
echo   '<tr>' .
		    '<td class="dingbatsmall" width="130" align="LEFT" valign="TOP">Name</td>' .
  			'<td class="bodystyle" width="413" align="LEFT" valign="TOP">' .
  			'<strong>' . $Node_row->getField('Name_Full') . '</strong>' .
  			'</td>'.
	  '</tr>';
echo	'<tr>'.
   			'<td class="dingbatsmall" align="LEFT" valign="TOP">Node URL</td>' .
		    '<td class="bodystyle" align="LEFT" valign="TOP">' . 
		    '<a href="' . $Node_row->getFIeld('URL') . '"target="_new">' . $Node_row->getField('URL') . '</a>' .
		    '</td>' .
	  '</tr>';
echo   '<tr>' .
		    '<td class="dingbatsmall" width="130" align="LEFT" valign="TOP">Host Institution</td>' .
  			'<td class="bodystyle" width="413" align="LEFT" valign="TOP">' .
  			'<strong>' . $Node_row->getFIeld('WNOD_Node_Participant_Institution::Name_Full__lct') . '</strong>' .
  			'</td>'.
	  '</tr>';
echo	'<tr>'.
   			'<td class="dingbatsmall" align="LEFT" valign="TOP">Host Institution URL</td>' .
		    '<td class="bodystyle" align="LEFT" valign="TOP">' . 
		    '<a href="' . $Node_row->getFIeld('WNOD_Node_Participant_Institution::Website') . '"target="_new">' . $Node_row->getField('WNOD_Node_Participant_Institution::Website') . '</a>' .
		    '</td>' .
	  '</tr>';

echo '</table>';
echo '<p>&nbsp;</p>';

?>

<?php

// Get footer
require("ims_footer.php");

?>
