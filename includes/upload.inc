<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
global $db, $sitepath, $rootpath ;
if ($loggedIn) {
	if (isset($_POST['txtFileName'])) {
		$title = quote_smart($_POST['title']) ;
		$description = quote_smart($_POST['description']) ;
		$tags = quote_smart($_POST['tags']) ;
		$catergorie = quote_smart($_POST['category']) ;
		$filename = quote_smart($_POST['txtFileName']) ;
		
		//test if extension is still good, hacker don;t like these
		$allowed_filetypes = array('wmv','mov','flv','mpg','avi','mpeg','mp4','3gp','rm','asf');
		$ext = strtolower(substr($filename, strrpos($filename, '.') + 1)) ;
		
		if(in_array($ext,$allowed_filetypes)) {
			if (file_exists($rootpath.'uploads/newuploads/'.$filename)) {
				$title = removespechar($title) ;
				$encodeset = str_replace('-', '', crc32(rand(100,999).time())) ;
				$tags = removespechar(str_replace(",", $encodeset, $tags)) ;
				$tags = str_replace($encodeset, ",", $tags) ;
				$fileid = $encodeset.".".$ext ;
				rename($rootpath."uploads/newuploads/".$filename, $rootpath."uploads/encode/".$fileid) ;
				$added = time() ;
				$status = "encode" ;
				$poster = $_SESSION['session_username'];
				//make title good if exists
				$db->query("SELECT * from media WHERE title ='".$title."'") ;
				if ($db->numRows() >= 1) {
					$title = $encodeset." ".$title ;
				}
				$sql = "INSERT INTO `media` (title, category, description, tags, fileid, poster, added, status, mediatype, mainthumb) VALUES ('".$title."', '".$catergorie."', '".$description."', '".$tags."', '".$fileid."', '".$poster."', '".$added."', '".$status."', 'video', '1')" ;
				$db->query($sql) ;
				if (getSetting("directencode", $db) == '1') {
					$cronpass = getSetting("passcron", $db) ;
					$curlpath = getSetting("curlpath", $db) ;
					$cmd = $curlpath. " " .$sitepath. "includes/encode.php?cronpass=" .$cronpass ;
					exec($cmd. ">/dev/null &");
				}
				$msgu = "<p>Thank you for sending a video, it will be waiting for approval.</p>" ;
			} else {
				$msgu = "<p>Filename is not correct, please start the upload again.</p>" ;
			}
		} else {
			$msgu = "<p>File extension is not allowed...probaly hacking me</p>" ;
		}
	}

}
?>