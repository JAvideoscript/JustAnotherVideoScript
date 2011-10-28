<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
require_once "includes/tablefunction.inc" ;

function myblockeds() {
	global $db,$sitepath ;	
	
	$db->query("SELECT * FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'") ;
	$idres = $db->fetch() ;
	$userid = $idres['id'] ;
	$db->query("SELECT * FROM blocked WHERE blocker_id = '".$userid."'") ;
	if ($db->numRows() > 0) {
		$resin = $db->fetchAll() ;
		if (isset($_GET['subpage'])) {
			$output = Tableview(9, $resin, $_GET['subpage'], $sitepath."account/blockedmembers") ;
		} else {
			$output = Tableview(9, $resin, 1, $sitepath."account/blockedmembers") ;
		}	

	
	} else {
		$output .= "<h3>You have no blocked members</h3>";
	}

	
	return $output ;
}

if (isset($_POST['removeblockmem'])) { 
	$removeid = quote_smart($_POST['removeblockmem']) ;
	$db->query("SELECT * FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'");
	$res = $db->fetch();
	$profileid = $res['id'] ;
	$db->query("DELETE FROM blocked WHERE blocker_id = '".$profileid."' AND blockee_id = '".$removeid."'") ;
}



?>


