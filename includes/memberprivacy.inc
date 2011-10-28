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
	$db->query("SELECT * FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'") ;
	$res = $db->fetch() ;
	$curshowhide = $res['optoutofviewerlist'] ;
	$curprivacy = $res['profile_privacy'] ;
	
	switch($curshowhide) {
		case '0':
			$curshow = ' CHECKED' ;
		break ;
		case '1':
			$curhide = ' CHECKED' ;
		break ;	
	}
	switch($curprivacy) {
		case '0':
			$prvpublic = ' CHECKED' ;
		break ;
		case '1':
			$prvregis = ' CHECKED' ;
		break ;	
		case '2':
			$prvpriv = ' CHECKED' ;
		break ;	
	}
	
	if (isset($_POST['submit'])) { 		
		$curprivacy = quote_smart($_POST['privacy']) ;
		$curshowhide = quote_smart($_POST['historyview']) ;
		
		switch($curshowhide) {
			case '0':
				$db->query("UPDATE member SET optoutofviewerlist = 0 WHERE `username` = '".quote_smart($_SESSION['session_username'])."'") ;
				$curshow = ' CHECKED' ;
				$curhide = ' ' ;
			break ;	
			case '1':
				$db->query("UPDATE member SET optoutofviewerlist = 1 WHERE `username` = '".quote_smart($_SESSION['session_username'])."'") ;
				$curshow = ' ' ;
				$curhide = ' CHECKED' ;
			break ;	
		}
		switch($curprivacy) {
		case '0':
			$db->query("UPDATE member SET profile_privacy = 0 WHERE `username` = '".quote_smart($_SESSION['session_username'])."'") ;
			$prvpublic = ' CHECKED' ;
			$prvregis = ' ' ;
			$prvpriv = ' ' ;
		break ;
		case '1':
			$db->query("UPDATE member SET profile_privacy = 1 WHERE `username` = '".quote_smart($_SESSION['session_username'])."'") ;
			$prvpublic = ' ' ;
			$prvregis = ' CHECKED' ;
			$prvpriv = ' ' ;
		break ;		
		case '2':
			$db->query("UPDATE member SET profile_privacy = 2 WHERE `username` = '".quote_smart($_SESSION['session_username'])."'") ;
			$prvpublic = ' ' ;
			$prvregis = ' ' ;
			$prvpriv = ' CHECKED' ;
		break ;
		}
		
	
					
	}
}
?>