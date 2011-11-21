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

if (isset($_POST['emsubmit'])) { 	
$valid = "yes" ;
	$title = removespechar(trim($_POST["emtitle"])) ;
	$description = quote_smart(trim($_POST["emdescription"])) ;
	$tags = quote_smart(trim($_POST["emtags"])) ;
	$catergory = quote_smart($_POST["emcatergory"]) ;
	$poster = $_SESSION['session_username'];
	$embedcode = addslashes($_POST["emembedcode"]) ;

$encodeset = crc32(rand(100,999).time()) ;
$allowed_filetypes = array('.jpg','.gif','.png');
$max_filesize = "1048576" ;
$upload_path = $rootpath."uploads/thumbs/" ;
$filename_thumb = $_FILES['emthumbe']['name'] ;
$ext = substr($filename_thumb, strpos($filename_thumb,'.'), strlen($filename_thumb)-1);

$db->query("SELECT * from media WHERE title ='".$title."'") ;
if ($db->numRows() >= 1) {
	$title = $encodeset." ".$title ;
}




if(!in_array($ext,$allowed_filetypes)) {
	$valid = "no" ;
	unset ($_POST["emthumbe"]) ;
	$msgb = "<p>Thumb filetype is not allowed, only jpg, gif, png are allowed.</p>" ;
}
if(filesize($_FILES['emthumbe']['tmp_name']) >= $max_filesize) {
	$valid = "no" ;
	unset ($_POST["emthumbe"]) ;
	$msgb = "<p>Thumb filesize is to high, max allowed is 1MB</p>" ;
}	
if ($valid == "yes") {
	if(move_uploaded_file($_FILES['emthumbe']['tmp_name'],$upload_path . $filename_thumb)) {
		createThumb($filename_thumb, getSetting("avatar_w", $db), getSetting("avatar_h", $db), $rootpath."uploads/thumbs/", $encodeset.".jpg");
		if (file_exists($rootpath."uploads/thumbs/".$encodeset.".jpg"))  {
			unlink($upload_path . $filename_thumb) ;
		}
	}
	$added = time() ;
	//maybe in the future add auto accept and approve mail. its better to check embedded shit first for security and spam
	$status = "false" ;
	
$sql = "INSERT INTO `media` (title, category, description, tags, fileid, poster, added, status, embed, mediatype, mainthumb) VALUES ('".$title."', '".$catergory."', '".$description."', '".$tags."', '".$encodeset."', '".$poster."', '".$added."', '".$status."', '".$embedcode."', 'embed', '1')" ;
$db->query($sql) ;
	$msgb = "<p>Thank you for embedding a video.</p>" ;
}
	
	
	
	
}
}
?>