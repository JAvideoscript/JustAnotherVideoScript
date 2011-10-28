<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
 if (isset($_POST['submit'])) {
	$db->query("SELECT * FROM member WHERE LOWER(email) = '".quote_smart(strtolower($_POST['email']))."' LIMIT 1") ;
	if ($db->numRows() != 0) {
		$res = $db->fetch() ;
		$newpass = substr(md5(uniqid(rand())), -8) ;
		$db->query("UPDATE member SET password = '".md5($newpass)."' WHERE id = ".$res['id']) ;
		$msg = getEmail("email_forgot") ;
		$msg = str_replace("[USERNAME]", $res['username'], $msg) ;
		$msg = str_replace("[PASSWORD]", $newpass, $msg) ;
		$msg = str_replace("[SITENAME]", getSetting("sitename", $db), $msg) ;
		$headers = "From: \"".getSetting('default_from', $db)."\" <".getSetting("contact_email", $db).">>\r\n"."Reply-To: ".getSetting("contact_email", $db)."\r\n"."X-Mailer: PHP/".phpversion() ;
		mymail(array(array("email"=>$res['email'], "name"=>$res['username'])), 'Password reset', $msg, $headers) ;
		$haltMessage = "Email sent." ;
	}
	else {
		$message = "The email address you entered is not recognised!" ;
	}
}
