<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
global $db ;
if (!$loggedIn) {
	$haltMessage = "<h2>You must log in</h2>" ;
} else {
	$db->query("SELECT * FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'") ;
	$res = $db->fetch() ;
	$curavatar = $res['avatar'] ;

if (file_exists($rootpath."uploads/avatars/".$curavatar) && (trim($curavatar) != "")) {
	$avatarpath = $sitepath."uploads/avatars/".$curavatar ;
	$curavatar = '<img src="'.$avatarpath.'" width="160" height="120" alt="'.$res['username'].'" />';
} else {
	$curavatar = "Upload a new Avatar" ;
}
	
	if (isset($_POST['submit'])) { 	
			$allowed_filetypes = array('.jpg','.gif','.png');
			$max_filesize = getsetting("maxsizememberavatar", $db) * 1024;
			$upload_path = $rootpath."uploads/avatars/" ;
			$filename_thumb = $_FILES['newavatar']['name'] ;
			$ext = substr($filename_thumb, strpos($filename_thumb,'.'), strlen($filename_thumb)-1);
				if(!in_array($ext,$allowed_filetypes)) {
					$msg = "Not a valid file extension only .jpg .png .gif";
				} else {
					 if(filesize($_FILES['newavatar']['tmp_name']) >= $max_filesize) {
					 	$msg = "The avatar file is too big, maxium size: $max_filesize";
					 } else {
					 	if(move_uploaded_file($_FILES['newavatar']['tmp_name'],$upload_path . $filename_thumb)) {
					 		require_once "includes/imagefunctions.inc" ;
					 		$avatarfilename = crc32(rand(100,999).time()).".jpg" ;
					 		createThumb($filename_thumb, getSetting("avatar_h", $db), getSetting("avatar_w", $db), $rootpath."uploads/avatars/", $avatarfilename);
					 		if(filesize($upload_path . $filename_thumb)) {
					 			unlink($upload_path . $filename_thumb) ;
					 		}
					 		if(filesize($upload_path . $res['avatar']) && (trim($res['avatar']) != "")) {
								unlink($upload_path . $res['avatar']) ;
							}
					 		$db->query("UPDATE `member` SET `avatar` = '".$avatarfilename."' WHERE `username` = '".quote_smart($_SESSION['session_username'])."'") ;
							$imglink = $sitepath."uploads/avatars/".$avatarfilename ; 		
					 		$curavatar = '<img src="'.$imglink.'" width="160" height="120" alt="'.$res['username'].'" />';
					 	}
					 }
				}
			
	}
	
}
?>