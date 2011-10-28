<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
include_once "includes/2257.inc";
if (getSetting("show2257", $db) == '1') {
	echo "$mustbeeightteen <br>" ;
} else {
	echo "2257 is disabled" ;
}
?>