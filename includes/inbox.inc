<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
require_once "includes/tablefunction.inc" ;

function clearbutton() {
	global $db,$sitepath ;
	$url = $sitepath."account/viewinghistory" ;
	$db->query("SELECT id FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'");
	$value = $db->fetch();
	$output = "<form action=\"".$url."\" method=\"POST\"><input type=\"submit\" class=\"button\" name=\"clearinbox\" value=\"Delete All\"><input type=\"hidden\" name=\"clearinbox\" value=\"".$value['id']."\"></form>\n";
return $output ;
}
function myinbox() {
	global $db,$sitepath ;		
	$db->query("SELECT * FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'") ;
	$idres = $db->fetch() ;
	$userid = $idres['id'] ;
	$db->query("SELECT * FROM message LEFT JOIN member ON message.fromid = member.id WHERE message.toid = ".$userid." ORDER BY sentdate DESC") ;
	
	
	if ($db->numRows() > 0) {
		$resin = $db->fetchAll() ;	
		if (isset($_GET['subpage'])) {
			$output = Tableview(3, $resin, $_GET['subpage'], $sitepath."account/inbox") ;
		} else {
			$output = Tableview(3, $resin, 1, $sitepath."account/inbox") ;
		}	

	
	} else {
		$output .= "<h3>You have no messages in your inbox</h3>";
	}

	
	return $output ;
}

if (isset($_POST['clearinbox'])) { 
	$removeid = quote_smart($_POST['clearinbox']) ;
	$db->query("SELECT * FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'");
	$res = $db->fetch();
	$profileid = $res['id'] ;
	$db->query("DELETE FROM message WHERE toid = ".$profileid) ;
}

if (isset($_POST['deletemessage'])) { 
	$tmpid = $_POST['deletemessage'] ;
	switch($tmpid[0][0]) {
		case'b':
		//delete and block msg
			$removeid = quote_smart(str_replace(b, '', $tmpid[0])) ;
			$db->query("SELECT * FROM message WHERE messageid = '".$removeid."'");
			$resblock = $db->fetch();
			$blocker = $resblock['toid'] ;
			$blockee = $resblock['fromid'] ;
			$db->query("SELECT blocker_id FROM blocked WHERE blocker_id=".$blocker." AND blockee_id=".$blockee) ;
			if ($db->numRows() < 1) {
			 	$db->query("INSERT INTO blocked (blocker_id,blockee_id) VALUES (".$blocker.",".$blockee.")") ;
			}		
			$db->query("UPDATE friend SET friend_removed = 1 WHERE userid = '".$blocker."' AND friendid = '".$blockee."'") ;
			$db->query("UPDATE friend SET friend_approved = 0 WHERE userid = '".$blocker."' AND friendid = '".$blockee."'") ;
			$db->query("DELETE FROM message WHERE messageid = ".$removeid) ;
		break;
		case'd':
		//delete msg only
			$removeid = quote_smart(str_replace(d, '', $tmpid[0])) ;
			$db->query("DELETE FROM message WHERE messageid = ".$removeid) ;
		break;
	
	}


}



?>


