<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
include_once 'includes/ajaxfunctions.inc' ;
include_once 'includes/common.inc' ;
include 'includes/profile.inc' ;
session_start() ;
global $sitepath,$templateimagepath,$db,$loggedIn ;
$site_template = getSetting("sitetemplate", $db) ;
$templateimagepath = $sitepath.'templates/'.$site_template.'/images/' ;

if (($_GET['id'] == 2) && ($_GET['page'] != '')) {
	$content = getMedia(quote_smart($_GET['page'])) ;
	echo $content ;
}
if (($_GET['id'] == 1) && ($_GET['page'] != '')) {
	$content = getFriends(quote_smart($_GET['page'])) ;
	echo $content ;
}
if (($_GET['id'] == 3) && ($_GET['page'] != '')) {
	$content = getSubscriptions(quote_smart($_GET['page'])) ;
	echo $content ;
}
if (($_GET['id'] == 4) && ($_GET['page'] != '')) {
	$content = getFavorites(quote_smart($_GET['page'])) ;
	echo $content ;
}
?>