<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
session_start() ;
require_once '../includes/loginfunctions.inc' ;
function leavePage($logged) {
	global $db ;
	$sitefolder = getSetting("sitefolder", $db) ;
	$sitepath = "http://".$_SERVER['SERVER_NAME'].$sitefolder ;
	$path = "http://".$_SERVER['SERVER_NAME'] ;
	if (isset($_POST['refer']))
		$_SESSION['session_url'] = $_POST['refer'] ;
	if ($logged == 0) {
		if (getSetting("accountpageon", $db) == 1) {
			header('Location: '.$sitepath.'account') ;
		}
		else {
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
	}
	else {
		if ($logged == 2)
			$_SESSION['session_loginerr'] = "You have not activated your account yet, please check your e-mail and activate your account." ;
		elseif ($logged == 1)
			$_SESSION['session_loginerr'] = "Wrong User name and/or password." ;
		header("Location: ".$sitepath."index.php?loginFailed=$logged") ;
	}
}
$date = gmdate("'Y-m-d'") ;
$db = db_connect() ;
$user = new User($db) ;
$logout1 = quote_smart($_GET['logout']) ;
if (isset($logout1)) {
	if ($logout1 == 1) {
		$user->_logout() ;
		leavePage(0) ;
	}
}
$username = quote_smart($_POST['user']) ;
$password = quote_smart($_POST['pass']) ;
$remember = true ;
if (isset($_POST['remember']))
	$remember = $_POST['remember'] ;
$isLogged = -1 ;
$isLogged = $user->_checkLogin($username, $password, $remember) ;
leavePage($isLogged) ;
?>