<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
require_once "includes/tablefunction.inc" ;


function mysentfriends() {
	global $db,$sitepath ;	
	$db->query("SELECT * FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'") ;
	$idres = $db->fetch() ;
	$userid = $idres['id'] ;
	$db->query("SELECT * FROM friend WHERE friendid = '".$userid."' AND friend_approved = 0 AND friend_removed = 0") ;
	
	if ($db->numRows() > 0) {
		$resin = $db->fetchAll() ;
		if (isset($_GET['subpage'])) {
			$output = Tableview(7, $resin, $_GET['subpage'], $sitepath."account/sentrequests") ;
		} else {
			$output = Tableview(7, $resin, 1, $sitepath."account/sentrequests") ;
		}	

	
	} else {
		$output .= "<h3>You have no friends requests.</h3>";
	}
	return $output ;
}


if (isset($_POST['cancelfriends'])) { 
		$friendid = $_POST['cancelfriends'] ;
		$db->query("SELECT id FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'") ;
		$idres = $db->fetch() ;
		$userid = $idres['id'] ;
		$db->query("DELETE FROM friend WHERE userid = '".$friendid."' AND friendid = '".$userid."'") ;
}



?>


