<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
require_once "includes/tablefunction.inc" ;

function myfriendssubs() {
	global $db,$sitepath ;	
	$db->query("SELECT * FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'") ;
	$idres = $db->fetch() ;
	$userid = $idres['id'] ;
	$db->query("SELECT * FROM friend WHERE userid = '".$userid."' AND friend_approved = 0 AND friend_removed = 0") ;
	if ($db->numRows() > 0) {
		$resin = $db->fetchAll() ;
		if (isset($_GET['subpage'])) {
			$output = Tableview(6, $resin, $_GET['subpage'], $sitepath."account/receivedrequests") ;
		} else {
			$output = Tableview(6, $resin, 1, $sitepath."account/receivedrequests") ;
		}	

	
	} else {
		$output .= "<h3>No Friends requests are pending for approval.</h3>";
	}
	return $output ;
}


if (isset($_POST['becomefriends'])) { 
	$tmpid = $_POST['becomefriends'] ;
	switch($tmpid[0][0]) {
		case'd':
		//Become friends
			$newfriend = quote_smart(str_replace(d, '', $tmpid[0])) ;
			$db->query("SELECT id FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'") ;
			$idres = $db->fetch() ;
			$userid = $idres['id'] ;
			$db->query("UPDATE friend SET friend_removed = 0 WHERE userid = '".$userid."' AND friendid = '".$newfriend."'") ;
			$db->query("UPDATE friend SET friend_approved = 1 WHERE userid = '".$userid."' AND friendid = '".$newfriend."'") ;		
		break;
		case'b':
		//Decline member
			$newfriend = quote_smart(str_replace(b, '', $tmpid[0])) ;
			$db->query("SELECT id FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'") ;
			$idres = $db->fetch() ;
			$userid = $idres['id'] ;
			
			$db->query("UPDATE friend SET friend_removed = 1 WHERE userid = '".$userid."' AND friendid = '".$newfriend."'") ;
			$db->query("UPDATE friend SET friend_approved = 0 WHERE userid = '".$userid."' AND friendid = '".$newfriend."'") ;	
		break;
		case'c':
		//Decline and block member
			$newfriend = quote_smart(str_replace(c, '', $tmpid[0])) ;
			$db->query("SELECT id FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'") ;
			$idres = $db->fetch() ;
			$userid = $idres['id'] ;		
			$db->query("SELECT blocker_id FROM blocked WHERE blocker_id=".$userid." AND blockee_id=".$newfriend) ;
			if ($db->numRows() < 1) {
			 	$db->query("INSERT INTO blocked (blocker_id,blockee_id) VALUES (".$userid.",".$newfriend.")") ;
			}
			$db->query("UPDATE friend SET friend_removed = 1 WHERE userid = '".$userid."' AND friendid = '".$newfriend."'") ;
			$db->query("UPDATE friend SET friend_approved = 0 WHERE userid = '".$userid."' AND friendid = '".$newfriend."'") ;
		break;
	}


}



?>


