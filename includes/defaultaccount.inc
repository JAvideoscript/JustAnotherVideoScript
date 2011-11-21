<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
global $db ;
if (!$loggedIn) {
	$haltMessage = "<h2>You must log in</h2>" ;
} else {

$red = "<img src='".$templateimagepath."red.png' border=0>" ;
$green = "<img src='".$templateimagepath."green.png' border=0>" ;


	$db->query("SELECT * FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'") ;
	$res = $db->fetch() ;
	$countpro = "100" ;
	if ($res['avatar'] == '') {
		$avastats = $red ;
		$countpro = $countpro - 25 ;
	} else {
		$avastats = $green ;
	}
	
	if ($res['aboutme'] == '') {
		$aboutstats = $red ;
		$countpro = $countpro - 25 ;
	} else {
		$aboutstats = $green ;
	}

	if ($res['favmovie'] == '') {
		$favstats = $red ;
		$countpro = $countpro - 25 ;
	} else {
		$favstats = $green ;
	}

	if ($countpro == "100") {
		$accountsetup = '<green>'.$countpro.' %</green>' ;
	} else {
		$accountsetup = '<red>'.$countpro.' %</red>' ;
	}
}
?>