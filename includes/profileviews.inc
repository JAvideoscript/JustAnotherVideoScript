<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
require_once "includes/tablefunction.inc" ;
function myprofileviews() {
	global $db,$sitepath ;		
	$db->query("SELECT viewerhistory FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'") ;
	$idres = $db->fetch() ;
	$viewerhistory = $idres['viewerhistory'] ;
	$members = array() ;
	$count = 0 ;
	if (strlen($viewerhistory) != 0) {
		$pastviewers = split(":", $viewerhistory) ;
		foreach ($pastviewers as $pv) {
			$db->query("SELECT * FROM member WHERE `activationkey`=0 AND id = '$pv'".$hide) ;
			$mres = $db->fetch() ;
			if (isset($mres['id'])) {
				if ($mres['id'] != '') {
					if ($mres['optoutofviewerlist'] < 1) {
						array_push($members, $mres) ;
						$count++ ;
					}
				}
			}
		}
	}
	if ($count > 0) {	
		if (isset($_GET['subpage'])) {
			$output = Tableview(8, $members, $_GET['subpage'], $sitepath."account/profileviews") ;
		} else {
			$output = Tableview(8, $members, 1, $sitepath."account/profileviews") ;
		}	

	
	} else {
		$output .= "<h3>Nobody has watched your profile</h3>";
	}

	
	return $output ;
}

function clearbutton() {
	global $db,$sitepath ;
	$url = $sitepath."account/profileviews" ;
	$db->query("SELECT id FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'");
	$value = $db->fetch();
	$output = "<form action=\"".$url."\" method=\"POST\"><input type=\"submit\" class=\"button\" name=\"clearprofileviews\" value=\"Delete All\"><input type=\"hidden\" name=\"clearprofileviews\" value=\"".$value['id']."\"></form>\n";
return $output ;
}


if (isset($_POST['clearprofileviews'])) { 
	$removeid = quote_smart($_POST['clearprofileviews']) ;
	$db->query("UPDATE member SET viewerhistory = '' WHERE id = '".$removeid."'") ;
}



?>


