<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
global $hidethumbnails,$hidemedia,$sitepath,$db,$rootpath,$loggedIn ;
$loggedIn = ($loggedIn) && (trim($_SESSION['session_username'] != '')) ;
require_once "includes/imagefunctions.inc" ;
$sitefolder = getSetting("sitefolder", $db) ;
$sitetemplate = getSetting("sitetemplate", $db) ;
$sitepath = "http://".$_SERVER['SERVER_NAME'].$sitefolder ;


function datez_diff($str_start, $str_end) {
	$defdate = $str_start ;
	$str_start = strtotime($str_start) ;
	$str_end = strtotime($str_end) ;
	$nseconds = $str_end - $str_start ;
	$ndays = floor($nseconds / 86400) ;
	$nseconds = $nseconds % 86400 ;
	$nhours = floor($nseconds / 3600) ;
	$nseconds = $nseconds % 3600 ;
	$nminutes = floor($nseconds / 60) ;
	$nseconds = $nseconds % 60 ;
	$retString = "" ;
	if ($ndays > 0) {
		$retString .= $defdate ;
		return "@ ".$retString ;
	}
	if ($nhours > 0) {
		$retString .= " ".$nhours." hour" ;
		if ($nhours > 1)
		$retString .= "s" ;
	}
	if ($nminutes > 0) {
		$retString .= " ".$nminutes." minute" ;
		if ($nminutes > 1)
		$retString .= "s" ;
	}
	if (strcmp($retString, "") == 0)
	$retString = "< 1 minute" ;
	return $retString." ago" ;
}
function checkBan($ip) {
	global $db ;
	$db->query("SELECT * FROM ban WHERE ip='".$ip."'") ;
	if ($db->numRows() > 0) {
		$result = true ;
	}
	else {
		$result = false ;
	}
	return $result ;
}
//Already displayed ad ID to make ad thumbs unique
$prevAdID = '0' ;
function today() {
	$result = mktime(0, 0, 0, date("m"), date("d"), date("Y")) ;
	return $result ;
}
function last7days() {
	$result = mktime(0, 0, 0, date("m"), date("d") - 7, date("Y")) ;
	return $result ;
}
function last30days() {
	$result = mktime(0, 0, 0, date("m"), date("d") - 30, date("Y")) ;
	return $result ;
}
function force_length($string, $length) {
	if (strlen($string) > $length)
		$string = substr($string, 0, $length - 3)."..." ;
	return $string ;
}
function alphaNum($string) {
	$new_string = preg_replace("/[^a-zA-Z0-9s[:space:]*]/", "", $string) ;
	return $new_string ;
}
//make captcha work
require_once 'includes/captcha.jpg' ;
if ($loggedIn) {
	$db->query("SELECT * FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'") ;
	$resUID = $db->fetch() ;
	$username = $resUID['username'] ;
	if (isset($resUID['id'])) {
		$uid = $resUID['id'] ;
		$db->query("SELECT * FROM favorite WHERE userid = $uid") ;
		$numFavorites = $db->numRows() ;
		$db->query("SELECT * FROM friend WHERE (userid =".$uid." OR friendid =".$uid.") AND friend_removed=0 AND friend_approved=1") ;
		$approvedFriends = $db->numRows() ;
		$db->query("SELECT * FROM friend WHERE userid =".$uid." AND friend_approved = 0") ;
		$receivedRequests = $db->numRows() ;
		$db->query("SELECT * FROM friend WHERE friendid =".$uid." AND friend_approved = 0 AND friend_removed = 0") ;
		$sentRequests = $db->numRows() ;
		$db->query("SELECT * FROM blocked WHERE blocker_id = ".$uid) ;
		$numBlocked = $db->numRows() ;
		$db->query("SELECT * FROM subscription WHERE userid = $uid") ;
		$numSubs = $db->numRows() ;
		$db->query("SELECT * FROM media WHERE poster = '".quote_smart($_SESSION['session_username'])."' AND status = 'true'") ;
		$numMedia = $db->numRows() ;
		$db->query("SELECT * FROM media WHERE LOWER(poster) = '".quote_smart(strtolower($_SESSION['session_username']))."' AND status = 'true'") ;
		$numVids = $db->numRows() ;
		$db->query("SELECT * FROM message WHERE toid = $uid") ;
		$allMessages = $db->numRows() ;
		$db->query("SELECT * FROM message WHERE toid = $uid AND msgread = 0") ;
		$newMessages = $db->numRows() ;
		if ($newMessages > 0) {
			$numMessages = $allMessages.'&nbsp;('.$newMessages.' new)' ;
		}
		else {
			$numMessages = $allMessages.'&nbsp;(0 new)' ;
		}
		$db->query("SELECT * FROM message WHERE fromid = $uid AND auto=0") ;
		$allSentMessages = $db->numRows() ;
		$db->query("SELECT * FROM message WHERE fromid = $uid AND auto=0 AND msgread = 0") ;
		$unreadSentMessages = $db->numRows() ;
		if ($unreadSentMessages > 0) {
			$numSentMessages = $allSentMessages.'&nbsp;('.$unreadSentMessages.' unread)' ;
		}
		else {
			$numSentMessages = $allSentMessages.'&nbsp;(0 unread)' ;
		}
	}
	else {
		$numfavorites = 0 ;
		$numFriends = 0 ;
		$numSubs = 0 ;
		$numVids = 0 ;
		$numMessages = 0 ;
	}
}

?>
