<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
global $sitepath ;
if (file_exists('./loginfunctions.inc')) {
	require_once './loginfunctions.inc' ;
}
elseif (@file_exists('../includes/loginfunctions.inc')) {
	@ require_once '../includes/loginfunctions.inc' ;
}
elseif (file_exists('includes/loginfunctions.inc')) {
	require_once 'includes/loginfunctions.inc' ;
}
else {
	die("Include Error") ;
}
$date = gmdate("'Y-m-d'") ;
$db = db_connect() ;
$user = new User($db) ;
$loggedIn = false ;
$sitefolder = getSetting("sitefolder", $db) ;
$template = getSetting("sitetemplate", $db) ;
$path = "http://".$_SERVER['SERVER_NAME'] ;
$ssitepath = "http://".$_SERVER['SERVER_NAME'].$sitefolder ;
$rootpath = $_SERVER['DOCUMENT_ROOT'].$sitefolder ;
$templateimagepath = $ssitepath.'templates/'.$template.'/images/' ;

if (isset($_GET['logout']))
	if ($_GET['logout'] == 1) {
	$_SESSION['session_logged'] = false ;
	$_SESSION['session_uid'] = 0 ;
	$_SESSION['session_username'] = '' ;
	$_SESSION['session_cookie'] = 0 ;
	$_SESSION['session_remember'] = false ;
	setcookie('vidlogin', $cookie, time() - 31104000, '/') ;
		if (isset($_SESSION['session_url'])) {
			$referrer = $_SESSION['session_url'] ;
			$referURL = !strpos($referrer, $sitepath) ? $referrer : $sitepath ;
			header('Location: '.$path.$referURL) ;
		}
		else if (isset($_SERVER['HTTP_REFERER'])) {
			$referrer = $_SERVER['HTTP_REFERER'] ;
			$referURL = !strpos($referrer, $sitepath) ? $referrer : $sitepath ;
			header('Location: '.$path.$referURL) ;
		}
	}
	
	
if (isset($_SESSION['session_logged'])) {
	if ($_SESSION['session_logged']) {
		$loggedIn = true ;
	}
}
$skipRefSet = false ;
if (isset($_GET['action'])) {
	if ($_GET['action'] == 'login') {
		$skipRefSet = true ;
		$_SESSION['session_url'] = $referrer ;
	}
}
if (!$skipRefSet)
	$_SESSION['session_url'] = $_SERVER['REQUEST_URI'] ;

?>
