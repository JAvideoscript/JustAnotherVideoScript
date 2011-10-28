<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
require_once "includes/tablefunction.inc" ;


function myfriends() {
	global $db,$sitepath ;	
	$db->query("SELECT * FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'") ;
	$idres = $db->fetch() ;
	$userid = $idres['id'] ;
	$db->query("SELECT * FROM friend WHERE userid = '".$userid."' OR friendid = '".$userid."' AND friend_approved = 1 AND friend_removed = 0") ;
	if ($db->numRows() > 0) {
		$resin = $db->fetchAll() ;
		if (isset($_GET['subpage'])) {
			$output = Tableview(5, $resin, $_GET['subpage'], $sitepath."account/friends") ;
		} else {
			$output = Tableview(5, $resin, 1, $sitepath."account/friends") ;
		}	

	
	} else {
		$output .= "<h3>You have no friends, YET.</h3>";
	}
	return $output ;
}


if (isset($_POST['removeandblock'])) { 
	$tmpid = $_POST['removeandblock'] ;
	switch($tmpid[0][0]) {
		case'b':
		//delete and block msg
			$blockee = quote_smart(str_replace(b, '', $tmpid[0])) ;
			$db->query("SELECT id FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'") ;
			$idres = $db->fetch() ;
			$blocker = $idres['id'] ;
			$db->query("SELECT blocker_id FROM blocked WHERE blocker_id=".$blocker." AND blockee_id=".$blockee) ;
			if ($db->numRows() < 1) {
			 	$db->query("INSERT INTO blocked (blocker_id,blockee_id) VALUES (".$blocker.",".$blockee.")") ;
			}
			$db->query("UPDATE friend SET friend_removed = 1 WHERE userid = '".$blocker."' AND friendid = '".$blockee."'") ;
			$db->query("UPDATE friend SET friend_approved = 0 WHERE userid = '".$blocker."' AND friendid = '".$blockee."'") ;
		break;
		case'd':
		//delete msg only
			$removeid = quote_smart(str_replace(d, '', $tmpid[0])) ;
			$db->query("SELECT id FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'") ;
			$idres = $db->fetch() ;
			$userid = $idres['id'] ;
			$db->query("UPDATE friend SET friend_removed = 1 WHERE userid = '".$userid."' AND friendid = '".$removeid."'") ;
			$db->query("UPDATE friend SET friend_approved = 0 WHERE userid = '".$userid."' AND friendid = '".$removeid."'") ;
			
		break;
	
	}


}



?>


