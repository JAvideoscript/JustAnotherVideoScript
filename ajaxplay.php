<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
include 'includes/ajaxfunctions.inc' ;
include 'includes/common.inc' ;
$site_template = getSetting("sitetemplate", $db) ;
global $sitepath,$templateimagepath,$db ;
$templateimagepath = $sitepath.'templates/'.$site_template.'/images/' ;


if (($_GET['id'] == 1) && ($_GET['vidid'] != '')) {
	global $db ;
	$vidid = trim(quote_smart($_GET['vidid'])) ;
	$num = trim(quote_smart($_GET['num'])) ;
	$db->query("SELECT `total_votes`,`total_value`,`used_ips` FROM rating WHERE id='.quote_smart($vidid).'") ;
	if ($db->numRows() > 0) {
		$numres = $db->fetch() ;
		$votes = $numres['total_votes'] ;
		$value = $numres['total_value'] ;
		$ratingexists = true ;
	}
	else {
		$ratingexists = false ;
	}
	$ip = $_SERVER['REMOTE_ADDR'] ;
	if ($ratingexists) {
		$db->query("SELECT id FROM rating WHERE used_ips LIKE '%".quote_smart($ip)."%' AND id='.quote_smart($vidid).' ") ;
		$voted = $db->numRows() > 0 ;
		$voted = $db->numRows() > 0 ;
		if (!$voted) {
			$vres = $db->fetch() ;
			$updateips = $vres['used_ips'].$ip.':' ;
			$votes = $votes + 1 ;
			$value = $value + $num ;
			$db->query("UPDATE rating SET `used_ips` = '".quote_smart($updateips)."',`total_votes`=".quote_smart($votes).",`total_value`=".quote_smart($value)." WHERE id='.quote_smart($vidid).'") ;
		}
	}
	else {
		$votes = 1 ;
		$value = $num ;
		$db->query("INSERT INTO rating (`id`,`total_votes`,`total_value`,`used_ips`) VALUES (".quote_smart($vidid).",".quote_smart($votes).",".quote_smart($value).",'".quote_smart($ip).":')") ;
	}
	return "Ran Function" ;
	echo "Ran Function" ;
}
if ($_GET['id'] == 2) {
	$result = rating_bar(quote_smart($vidid), $_SERVER['REMOTE_ADDR'], quote_smart($pagelink)) ;
	echo $result ;
}
?>