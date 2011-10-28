<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
require_once "includes/tablefunction.inc" ;


function myoutbox() {
	global $db,$sitepath ;		
	$db->query("SELECT * FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'") ;
	$idres = $db->fetch() ;
	$userid = $idres['id'] ;
	
	$db->query("SELECT * FROM message LEFT JOIN member ON message.toid = member.id WHERE message.fromid = ".$userid." ORDER BY sentdate DESC") ;

	
	if ($db->numRows() > 0) {
		$resin = $db->fetchAll() ;	
		if (isset($_GET['subpage'])) {
			$output = Tableview(4, $resin, $_GET['subpage'], $sitepath."account/outbox") ;
		} else {
			$output = Tableview(4, $resin, 1, $sitepath."account/outbox") ;
		}	

	
	} else {
		$output .= "<h3>You have no messages in your inbox</h3>";
	}

	
	return $output ;
}




?>


