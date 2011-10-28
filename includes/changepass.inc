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
	if (isset($_POST['submit'])) { 
		$db->query("SELECT * FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'") ;
		$res = $db->fetch() ;

			if (quote_smart($_POST['newpass']) == quote_smart($_POST['newpass2'])) {

				if (md5(quote_smart($_POST['oldpass'])) == $res['password']) {
					$db->query("UPDATE `member` SET `password` = '".md5(quote_smart($_POST['newpass']))."' WHERE `username` = '".quote_smart($_SESSION['session_username'])."'") ;
					$msg = "Password has been changed" ;
				} else {
				$msg = "Old password not valid" ;
				}

			} else {
				$msg = "New Passwords did not matched" ;
			}
	}
}
?>