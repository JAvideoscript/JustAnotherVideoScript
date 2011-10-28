<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
require_once "includes/tablefunction.inc" ;
function mymedia() {
	global $db,$templateimagepath,$sitepath ;	
		$db->query("SELECT * FROM media WHERE poster = '".quote_smart($_SESSION['session_username'])."' AND status = 'true'") ;
		$resTR = $db->fetchAll() ;
		if ($db->numRows()>0) {
			if (isset($_GET['subpage'])) {
				$output = Tableview(13, $resTR, $_GET['subpage'], $sitepath."account/uploadedvideos") ;
			} else {
				$output = Tableview(13, $resTR, 1, $sitepath."account/uploadedvideos") ;
			}
		} else {
			$output .= "<h3>You have not uploaded any videos yet.</h3>";
		}	
	return $output ;
}


if (isset($_POST['deletemediaid'])) { 
	if (getSetting(membervideodelete, $db) == 1) {
		$db->query("SELECT * FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'");
		$res = $db->fetch();
		$history = $res['history'];
		$removeid = quote_smart($_POST['deletemediaid']) ;
		$db->query("DELETE FROM favorite WHERE vidid = ".$removeid);
		$db->query("DELETE FROM `media_comment` WHERE vid_id = ".$removeid);
		$db->query("DELETE FROM `rating` WHERE id = ".$removeid);
		$vidstring = $removeid.':';
		$history = str_replace($vidstring,'',$history);
		$profileid = $res['id'];	
		$db->query("UPDATE member SET history = '".$history."' WHERE id=".$profileid);
		$db->query("SELECT fileid FROM media WHERE id=".$removeid);
		$dres=$db->fetch();

		if (($dres['fileid']!="") && ($dres['mediatype']!='embed')) {
			unlink($rootpath.'uploads/vids/'.$dres['fileid'].'/'.$dres['fileid'].'.flv');
			unlink($rootpath.'uploads/thumbs/'.$dres['fileid'].'.jpg');
			if ($dres['hd']=='1') {
				unlink($rootpath.'uploads/vids/'.$dres['fileid'].'/'.$dres['fileid'].'.mp4');
			}
			if ($dres['mobile']=='1') {
				unlink($rootpath.'uploads/vids/'.$dres['fileid'].'/mob_'.$dres['fileid'].'.mp4');
			}		
		}
		$db->query("DELETE FROM media WHERE id=".$removeid);
	}
}



?>


