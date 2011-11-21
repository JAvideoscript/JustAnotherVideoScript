<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
include_once("settings.inc");
include_once("mysql.php");
$db = new mysql($db_host, $db_user, $db_password, $db_database) ;
$sitefolder = getsetting("sitefolder", $db) ;
$sitepath = "http://".$_SERVER['SERVER_NAME'].$sitefolder ;
$rootpath =  $_SERVER['DOCUMENT_ROOT'].$sitefolder ;

function sitemapper($rowmedia, $catname)  {
	global $sitepath, $rootpath ;
	$output = '<urlset xmlns="http://www.sitemaps.org/schemas/sitemap/0.9" xmlns:video="http://www.google.com/schemas/sitemap-video/1.0">';
	$datelast = gmdate("Y-m-d", time())."T".gmdate("H:i:s", time())."+01:00"  ;
		foreach ($rowmedia as $key=>$value) {
			$duration = explode(":", $value['duration']);
			$duration = $duration[0] * 60 + $duration[1] ;
			$tagwords = explode(",", $value['tags']) ;
			$desc = str_replace(array(',', ')', '(', '-', '<', '>', '&', '!', '?', '"', '.'),array(' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '), $value['description']);
			$title = str_replace(array(',', ')', '(', '-', '<', '>', '&', '!', '?', '"', '.'),array(' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '), $value['title']);
			$play = str_replace(' ', '-', $title) ;
			$datelast = str_replace(' ','T', date("Y-m-d H:i:sP", $value['added']));
			$output .= '<url>' ;
			$output .= '<loc>'.$sitepath.'play/'.$play.'</loc>' ;
			$output .= '<video:video>' ;
			$output .= '<video:thumbnail_loc>'.$sitepath.'uploads/thumbs/'.$value['fileid'].'.jpg</video:thumbnail_loc>' ;
			$output .= '<video:title>'.$title.'</video:title>' ;
			$output .= '<video:description>'.$desc.'</video:description>' ;
			if ($value['mediatype'] == 'video') {
				$output .= '<video:content_loc>'.$sitepath.'uploads/vids/'.$value['fileid'].'/'.$value['fileid'].'.flv</video:content_loc>';
			}
			$output .= '<video:duration>'.$duration.'</video:duration>' ;
			$output .= '<video:view_count>'.$value['allviews'].'</video:view_count>' ;
			$output .= '<video:publication_date>'.$datelast.'</video:publication_date>' ;
			
				foreach ($tagwords as $tagword) {
					if ($tagword) {
						$output .= '<video:tag>'.$tagword.'</video:tag>' ;
					}
				}
			$output .= '<video:category>'.$catname.'</video:category>' ;
			$output .= '<video:family_friendly>no</video:family_friendly>' ;
			$output .= '<video:gallery_loc title="'.$catname.'">'.$sitepath.'category/'.$catname.'</video:gallery_loc>' ;
			$output .= '<video:requires_subscription>no</video:requires_subscription>' ;
			$output .= '</video:video>' ;
			$output .= '</url>' ;
		}
	$output .= '</urlset>';
	$file = $rootpath.'sitemap/'.$catname.'.xml' ;
	$fp = fopen($file, "w");
	fwrite($fp, $output);
	fclose($fp);
}
function dirList() {
	global $rootpath ;
	$results = array();
	$handler = opendir($rootpath."templates/");
	while ($file = readdir($handler)) {
		if ($file != ".") {
			if ($file != "..") {
            			array_push($results, $file);
            		}
            	}
	}
	closedir($handler);
	return $results;
}
function homelist() {
	global $rootpath, $db ;
	$results = array();
	array_push($results, home);
	if (getSetting(showallvideos, $db) == '1') {
		array_push($results, videos);
	}
	if (getSetting(showtoprated, $db) == '1') {
		array_push($results, toprated);
	}
	if (getSetting(showmostviewed, $db) == '1') {
		array_push($results, mostviewed);
	}
	if (getSetting(showcategorie, $db) == '1') {
		array_push($results, catlist);
	}
	if (getSetting(showupload, $db) == '1') {
		array_push($results, upload);
	}
	return $results;
}
function updateday() {
	global $rootpath, $db ;
	$results = array();
		array_push($results, saterday);
		array_push($results, sunday);
		array_push($results, monday);
		array_push($results, tuesday);
		array_push($results, wednesday);
		array_push($results, thursday);
		array_push($results, friday);
	return $results;
}

function skinList() {
	global $rootpath ;
	$results = array();
	$handler = opendir($rootpath."player/jwplayer/skin/");
	while ($file = readdir($handler)) {
		$ext = strtolower(substr($file,-3));
		if ($ext == "zip") {
			if ($file != ".") {
				if ($file != "..") {
					array_push($results, $file);
				}
			}
		}
	}
	closedir($handler);
	return $results;
}
function getSetting($setting, $db) {
	$db->query("SELECT `value` FROM `setting` WHERE `setting` = '$setting'") ;
	$res = $db->fetch() ;
	return $res['value'] ;
}
function importlist(){
	global $rootpath ;
	$results = array();
	$vid_exts = array('wmv', 'mov', 'mpg', 'avi', 'flv', 'mpeg', 'mp4', '3gp', 'rm', 'asf') ;
	$handler = opendir($rootpath."uploads/import/");
	while ($file = readdir($handler)){
		$ext = strtolower(substr($file,-3));
		if (array_search($ext, $vid_exts) !== FALSE) {
            		array_push($results, $file);
            	}
	}
	closedir($handler);
	return $results;
}
function getduration($my_file2) {
	if (file_exists($my_file2)) {
		$handle = fopen($my_file2, "r");
		$contents = fread($handle, filesize($my_file2));
		fclose($handle);$make_hexa = hexdec(bin2hex(substr($contents,strlen($contents)-3)));
			if (strlen($contents) > $make_hexa) {
				$pre_duration = hexdec(bin2hex(substr($contents,strlen($contents)-$make_hexa,3))) ;
				$post_duration = $pre_duration/1000 ;
				$timehours = $post_duration/3600 ;
				$timeminutes =($post_duration % 3600)/60 ;
				$timeseconds = ($post_duration % 3600) % 60 ;
				$timehours = explode(".", $timehours) ;
				$timeminutes = explode(".", $timeminutes) ;

					if ($timeseconds <= 9) {
						$timeseconds = explode(".", $timeseconds) ;
						$duration = $timeminutes[0].":0". $timeseconds[0] ;
					}


					else {
						$timeseconds = explode(".", $timeseconds) ;
						$duration = $timeminutes[0].":". $timeseconds[0] ;
					}
		}
	}
return $duration ;
}
function quote_smart($value) {
	if (get_magic_quotes_gpc()) {
		$value = stripslashes($value) ;
	}
	return mysql_real_escape_string($value) ;
}
function removespechar($char) {
	$char = trim(preg_replace('/[^a-z\d ]/i','',$char)) ;
return $char ;
}

function getcontent($url) {
        $options = array(
                CURLOPT_RETURNTRANSFER => true,     // return web page
                CURLOPT_HEADER         => true,    // don't return headers
                CURLOPT_FOLLOWLOCATION => false,     // follow redirects
                CURLOPT_ENCODING       => "",       // handle compressed
                CURLOPT_USERAGENT      => "Googlebot/2.1 (+http://www.google.com/bot.html)", // who am i
                CURLOPT_AUTOREFERER    => true,     // set referer on redirect
                CURLOPT_CONNECTTIMEOUT => 120,      // timeout on connect
                CURLOPT_TIMEOUT        => 120,      // timeout on response
                CURLOPT_MAXREDIRS      => 10,       // stop after 10 redirects
        );

        $ch      = curl_init( $url );
        curl_setopt_array( $ch, $options );

        $content = curl_exec( $ch );
        $err     = curl_errno( $ch );
        $errmsg  = curl_error( $ch );
        $header  = curl_getinfo( $ch );
        curl_close( $ch );

 $header['errno']   = $err;
 $header['errmsg']  = $errmsg;
 $header['content'] = $content;

return $content ;
}
function formatSize( $bytes )	{
        $types = array( 'B', 'KB', 'MB', 'GB', 'TB' );
        for( $i = 0; $bytes >= 1024 && $i < ( count( $types ) -1 ); $bytes /= 1024, $i++ );
	return( round( $bytes, 2 ) . " " . $types[$i] );
}
function sendmail($to, $subject, $message) {
	global $db,$sitepath ;
	$headers = "From: \"".getSetting('default_from', $db)."\" <".getSetting("contact_email", $db).">>\r\n"."Reply-To: ".getSetting("contact_email", $db)."\r\n"."X-Mailer: PHP/".phpversion() ;
	foreach ($to as $mail) {
		echo "<h4>Mailing To: <b>".$mail['name'].", </b>@<b> ".$mail['email']."</b></h4>" ;
		$msg = str_replace('[USERNAME]', $mail['name'], $message) ;
		$msg = str_replace('[EMAIL]', $mail['email'], $msg) ;
		$msg = str_replace('[SITENAME]', getSetting('sitename', $db), $msg) ;
		$sub = str_replace('[USERNAME]', $mail['name'], $subject) ;
		$sub = str_replace('[EMAIL]', $mail['email'], $sub) ;
		$sub = str_replace('[SITENAME]', getSetting('sitename', $db), $sub) ;
		mail($mail['email'], $sub, $msg, $headers) ;
	}
	
}	
function getEmailformat($email) {
	global $db ;
	$db->query("SELECT phrase FROM `email_text` WHERE ident = '$email'") ;
	$res = $db->fetch() ;
	if (isset($res['phrase']))
		return $res['phrase'] ;
	else
		return "" ;
}
function url_encode($url) {
		$url = str_replace(' ', '-', $url) ;
		$url = urlencode($url) ;
		$url = urlencode($url) ;
		return $url ;
}
function url_decode($url, $type = NULL, $pcat = NULL) {
		$url = urldecode($url) ;
		$url = urldecode($url) ;
		$url = str_replace('-', ' ', $url) ;
		return $url ;
}


?>