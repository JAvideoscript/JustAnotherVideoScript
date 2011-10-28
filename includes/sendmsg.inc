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
} 
else {
	$msgto = quote_smart($_GET['subpage']) ;
	$db->query("SELECT username FROM member WHERE id = '".$msgto."'") ;
	$res = $db->fetch() ;
	$msgusername = $res['username'] ;
	if (isset($msgusername )) {
		if (isset($_POST['submit'])) { 	
			$msgto = quote_smart($_GET['subpage']) ;
			$msgbody = quote_smart($_POST['msgbody']) ;
			$db->query("SELECT id FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'") ;
			$res2 = $db->fetch() ;
			$msgfrom = $res2['id'] ;
			$db->query("INSERT INTO message (fromid, toid, body, sentdate, msgread) VALUES (".$msgfrom.",".$msgto.",'".$msgbody."',".time().",0)") ;
 			echo "Your Message has been sent." ;
		}
	}

}

?>
