<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
include_once 'includes/mostviewed.inc';

if (getSetting("showmostviewed", $db) == '1') {
	echo '<div id="main-left"><h2>Categories</h2>' ;
	echo catplainlist() ;
	echo '</div>' ;

	echo '<div id="main-right"><h2>Most Viewed</h2>' ;
	echo $ad8 ;
	echo mostViewedmedia() ;
	echo '</div>' ;	
	
	
} else {
	echo "<h2>Most Viewed videos are disabled</h2>" ;
}

?>
<?=$ad9?>