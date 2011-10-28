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
	$output = "<form action=\"".$url."\" method=\"POST\"><input type=\"submit\" class=\"button\" name=\"clearhistory\" value=\"Delete History\"><input type=\"hidden\" name=\"clearhistory\" value=\"".$value['id']."\"></form>\n";
return $output ;
}
function myhistory() {
	global $db,$sitepath ;		
		$db->query("SELECT history FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'");
		$idres = $db->fetch();
		$userhistory = $idres['history'];
		$media = array();
		$count = 0;
		if(strlen($userhistory) != 0) {
			$pastmedia = split(":",$userhistory);
				foreach($pastmedia as $pv) {
					$db->query("SELECT * FROM media WHERE `status`='true' AND id = '$pv'");
					$mres = $db->fetch();
						if(isset($mres['id'])) {
							if ($mres['id']!='') {
								array_push($media,$mres);
								$count++;
							}
						}
				}
				if ($count>0) {
						if (isset($_GET['subpage'])) {
							$output .= Tableview(16, $media, $_GET['subpage'], $sitepath."account/viewinghistory") ;
						} else {
							$output .= Tableview(16, $media, 1, $sitepath."account/viewinghistory") ;
						}
				}	
		} else {
			$output .= "<h3>Your history is empty</h3>";
		}

	
	return $output ;
}

if (isset($_POST['clearhistory'])) { 
	$removeid = quote_smart($_POST['clearhistory']) ;
	$db->query("SELECT * FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'");
	$res = $db->fetch();
	$profileid = $res['id'] ;
	$db->query("UPDATE member SET history=\"\" WHERE id=".$profileid);
}

?>


