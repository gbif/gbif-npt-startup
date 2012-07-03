<?php 

// We are NOT in debug...
// error_reporting(E_ALL);
// ini_set('display_errors', '1');

// Setup path
$path = preg_replace("#^(.*[/\\\\])[^/\\\\]*[/\\\\][^/\\\\]*$#",'\1',__FILE__);
set_include_path(get_include_path() . PATH_SEPARATOR . $path);

// Setup FileMaker specific details
require_once('FileMaker.php');
$hostname_IMS = "filemaker.gbif.org";
$database_IMS = "IMS_NG";
$username_IMS = "web_ims";
$password_IMS = "GBIFims";
$IMS = new FileMaker($database_IMS, $hostname_IMS, $username_IMS, $password_IMS); 

// Define site name
$sitename = 'http://www.gbif.org/';

// Setup defaults
$nodemanager_grouproleID = 14; // Was 105;

$participant_associate = 'Associate Country Participant';
$participant_other = 'Other Associate Participant';
$participant_voting = 'Voting Participant';

$grouprole_sort_cutoff = 99 ; // Group roles with sort key higher than this value will be omitted

// Super Container path
$supercontainer_base = 'http://fms.gbif.org:8020/SuperContainer/RawData/' ;
$supercontainer_people = 'PEOP/';
$supercontainer_thumbnails = 'THMB/';
$supercontainer_access = '?username=zordesign&password=GBIF2010';

// Error trapping (wrapper)
function fmstraperror($error, $file){
   // echo 'Error should be handled by >' . $file . '<' ;
};

// Convert document types by name to filepath by ID
function get_filepathID( $pathtype ) {
	if ( $pathtype == 'booklets' ) {
		return 176;
	} elseif ( $pathtype === 'pamphlets' ) { 
		return 172 ;
	} elseif ( $pathtype === 'annualreport' ) {
		return 157 ;
	} elseif ( $pathtype === 'otherreports' ) {
		return 1100 ;
	} elseif ( $pathtype === 'newsletters' ) {
		return 156 ;
	} elseif ( $pathtype === 'posters' ) {
		return 251 ;
	} else {
		return -1;
	};
};

// Convert deprecated GrouproleIDs to current GrouproleIDs 
function grouprole_convert( $role_old ) {
	if ( $role_old == 1 ) {
		// Science Committee
		return 1;
	} elseif ( $role_old == 2 ) {
		// Rules Committee
		return 2;
	} elseif ( $role_old == 4 ) {
		// Executive Committee
		return 4;
	} elseif ( $role_old == 5 ) {
		// Budget Committee
		return 5;
	} elseif ( $role_old == 7 ) {
		// Governing Board
		return 7;
	} elseif ( $role_old == 17 ) {
		// Global Strategy and Action Plan for Mobilisation of Natural...
		return 17;
	} elseif ( $role_old == 18 ) {
		// Data Publishing Framework Task Group
		return 18;
	} elseif ( $role_old == 19 ) {
		// Content Needs Assesment Task Group
		return 19;
	} elseif ( $role_old == 20 ) {
		// Multimedia Resources Task Group
		return 20;
	} elseif ( $role_old == 21 ) {
		// Observational Data Task Group
		return 21;
	} elseif ( $role_old == 22 ) {
		// Ex officio representatives
		return 22;
	} elseif ( $role_old == 23 ) {
		// Pro Bono Legal Advisory Group
		return 23;
	} elseif ( $role_old == 25 ) {
		// Review Team
		return 25;
	} elseif ( $role_old == 26 ) {
		// Forward Look Team
		return 26;
	} else {
		return $role_old;
	};
};

?>