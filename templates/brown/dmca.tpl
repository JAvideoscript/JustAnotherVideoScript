<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
	include_once "includes/dmca.inc";
if (getSetting("showdmca", $db) == '1') {
	echo "$dmca <br>" ;
} else {
	echo "DMCA is disabled" ;
}
?>



