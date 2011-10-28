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
	$curemail = $res['email'] ;
	if (isset($_POST['submit'])) { 
			$checkmail = checkmail(quote_smart($_POST['newmail']));
				if ($checkmail == 1) {
					if (quote_smart($_POST['newmail']) == quote_smart($_POST['vermail'])) {
						$db->query("UPDATE `member` SET `email` = '".quote_smart($_POST['newmail'])."' WHERE `username` = '".quote_smart($_SESSION['session_username'])."'") ;
						$msg = "Email Adres has been changed to: ".quote_smart($_POST['newmail']) ;	
					} else {
						$msg = "Email adresses did not matched" ;
					}
				} else {
					$msg = "Email adresses did not meet requirements" ;
				}
	}
}
?>