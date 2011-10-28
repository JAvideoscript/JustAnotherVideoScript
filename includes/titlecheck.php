<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
include_once("../includes/settings.inc");
include_once("../includes/mysql.inc");
include_once("../includes/functions.inc");
include_once("../includes/imagefunctions.inc");
$db = new mysql($db_host, $db_user, $db_password, $db_database) ;
$sitefolder = getsetting("sitefolder", $db) ;
$sitepath = "http://".$_SERVER['SERVER_NAME'].$sitefolder ;
$rootpath =  $_SERVER['DOCUMENT_ROOT'].$sitefolder ;


$valid = 'true' ;
if (isset($_POST['emtitle'])) {
		$emtitle = quote_smart($_POST['emtitle']) ;

		$db->query("SELECT * from `media` WHERE title = '".$emtitle."'") ;
		$resPnum = $db->numRows();

		if ($resPnum > 0) {
			$valid = 'false';
		}
	echo $valid ;
}
if (isset($_POST['title'])) {
		$title = quote_smart($_POST['title']) ;

		$db->query("SELECT * from `media` WHERE title = '".$title."'") ;
		$resPnum = $db->numRows();

		if ($resPnum > 0) {
			$valid = 'false';
		}
	echo $valid ;
}


?>
