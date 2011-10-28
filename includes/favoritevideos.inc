<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
require_once "includes/tablefunction.inc" ;
function myfavmedia() {
	global $db,$templateimagepath,$sitepath ;		
		$db->query("SELECT * FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'");
		$idres = $db->fetch();
		$userid = $idres['id'];
		$db->query("SELECT * FROM media LEFT JOIN favorite ON media.id = favorite.vidid WHERE favorite.userid =".$userid);
		if ($db->numRows()>0) {
			$resTR = $db->fetchAll() ;
			if (isset($_GET['subpage'])) {
				$output = Tableview(2, $resTR, $_GET['subpage'], $sitepath."account/favoritevideos") ;
			} else {
				$output = Tableview(2, $resTR, 1, $sitepath."account/favoritevideos") ;
			}
		} else {
			$output .= "<h3>Your favorites list is empty</h3>";
		}	
	return $output ;
}

if (isset($_POST['deletemediaid'])) { 
	$removeid = quote_smart($_POST['deletemediaid']) ;
	$db->query("SELECT * FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'");
	$res = $db->fetch();
	$profileid = $res['id'] ;
	$db->query("DELETE FROM favorite WHERE userid=".$profileid." AND vidid=".$removeid);
}

?>


