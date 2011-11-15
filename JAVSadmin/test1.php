<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */


if (isset($_POST['url'])) {
	if ($_POST['url'] == 1) {
		$valid = 'true' ;
	} else {
		$valid = 'false';
	}
} else {
	$valid = 'false';
}

echo $valid ;



?>
