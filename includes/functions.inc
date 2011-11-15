<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
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
function checkmail($mail) {
     $email_host = explode("@", $mail);
     $email_host = $email_host['1'];
     $email_resolved = gethostbyname($email_host);
     if ($email_resolved != $email_host && eregi("^[0-9a-z]([-_.~]?[0-9a-z])*@[0-9a-z]([-.]?[0-9a-z])*\\.[a-z]{2,4}$",$mail)) {
         $valid = 1;
     }
     return $valid;
}
function basicshow_rating($id) {
	global $db,$templateimagepath,$sitepath ;
	$db->query("SELECT `total_votes`,`total_value`,`used_ips` FROM rating WHERE id='$id'") ;
	if ($db->numRows() > 0) {
		$numres = $db->fetch() ;
		$votes = $numres['total_votes'] ;
		$value = $numres['total_value'] ;
		if ($votes > 0) {
			$rating = $value / $votes ;
		}
		else {
			$rating = 0 ;
		}
		$ratingexists = true ;
	}
	if ($ratingexists) {
		$rating = round_up($rating, 2) ;
		$ratingbar = "Rating: ".$rating." out of 5" ;
	} else {
		$ratingbar = "Not rated yet" ;
	}
	
	return $ratingbar ;
}
function catplainlist() {
	global $db,$sitepath ;
	$db->query("SELECT * FROM `category` ORDER BY name") ;
	$res = $db->fetchAll() ;
	$output = '<ul class="catplainlist">' ;
		foreach($res as $value) {
			$catname = str_replace(" ", "-", trim($value['name'])) ;
			$output .= '<li><a href="'.$sitepath.'category/'.$catname.'">'.$catname.'</a></li>' ;
		}
	$output .= '</ul>' ;
return $output ;
}
function round_up($value, $places=0) {
  if ($places < 0) { $places = 0; }
  $mult = pow(10, $places);
  return ceil($value * $mult) / $mult;
 }
function quote_smart($value) {
	if (get_magic_quotes_gpc()) {
		$value = stripslashes($value) ;
	}
	return mysql_real_escape_string(htmlspecialchars($value)) ;
}
function removespechar($char) {
	$char = trim(preg_replace('/[^a-z\d ]/i','',$char)) ;
return $char ;
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
function getSetting($setting, $db) {
	$db->query("SELECT `value` FROM `setting` WHERE `setting` = '$setting'") ;
	$res = $db->fetch() ;
	return $res['value'] ;
}
function show_rating($id) {
	global $db,$templateimagepath,$sitepath ;
	// Check for a rating record for this media
	$db->query("SELECT `total_votes`,`total_value`,`used_ips` FROM rating WHERE id='$id'") ;
	if ($db->numRows() > 0) {
		$numres = $db->fetch() ;
		$votes = $numres['total_votes'] ;
		$value = $numres['total_value'] ;
		if ($votes > 0) {
			$rating = $value / $votes ;
		}
		else {
			$rating = 0 ;
		}
		$ratingexists = true ;
	}
	else {
		$ratingexists = false ;
	}
	$full = "<img src='".$templateimagepath."star_full.png' border=0>" ;
	$half = "<img src='".$templateimagepath."star_half.png' border=0'>" ;
	$empty = "<img src='".$templateimagepath."star_empty.png' border=0'>" ;
	if ($ratingexists) {
		$ratingbar = "" ;
		if ($rating > 4.5) {
			$ratingbar .= $full.$full.$full.$full.$full ;
		}
		else if ($rating > 4.0) {
			$ratingbar .= $full.$full.$full.$full.$half ;
		}
		else if ($rating > 3.5) {
			$ratingbar .= $full.$full.$full.$full.$empty ;
		}
		else if ($rating > 3.0) {
			$ratingbar .= $full.$full.$full.$half.$empty ;
		}
		else if ($rating > 2.5) {
			$ratingbar .= $full.$full.$full.$empty.$empty ;
		}
		else if ($rating > 2.0) {
			$ratingbar .= $full.$full.$half.$empty.$empty ;
		}
		else if ($rating > 1.5) {
			$ratingbar .= $full.$full.$empty.$empty.$empty ;
		}
		else if ($rating > 1.0) {
			$ratingbar .= $full.$half.$empty.$empty.$empty ;
		}
		else if ($rating > 0.5) {
			$ratingbar .= $full.$empty.$empty.$empty.$empty ;
		}
		else if ($rating > 0.0) {
			$ratingbar .= $half.$empty.$empty.$empty.$empty ;
		}
		else {
			$ratingbar .= $empty.$empty.$empty.$empty.$empty ;
		}
		$ratingbar .= "" ;
	}
	else {
		$ratingbar = "Not rated yet" ;
	}
	return $ratingbar ;
}
function rating_bar($id, $passedip, $url) {
	global $db_host,$db_user,$db_password,$db_database,$db,$templateimagepath,$sitepath ;
	$output = "" ;
	// this is to get the current rating(s) and display it
	$conn = mysql_connect($db_host, $db_user, $db_password) or die('Error connecting to mysql') ;
	mysql_select_db($db_database) ;
	$ip = $_SERVER['REMOTE_ADDR'] ;
	$id = quote_smart($_GET['vidid']) ;
	$query = mysql_query("SELECT total_votes, total_value, used_ips FROM rating WHERE id='$id' ") or die(" Error: ".mysql_error()) ;
	$numbers = mysql_fetch_assoc($query) ;
	$count = $numbers['total_votes'] ;//how many votes total
	$current_rating = $numbers['total_value'] ;//total number of rating added together and stored
	$tense = ($count == 1) ? "vote" : "votes" ;
	if ($count > 0) {
		$average_rating = $current_rating / $count ;
	}
	else {
		$average_rating = -1 ;
	}
	$db->query("SELECT id FROM rating WHERE used_ips LIKE '%".$ip."%' AND id='$id' ") ;
	$voted = $db->numRows() > 0 ;
	$full = "<img src='".$templateimagepath."star_full.png' border=0>" ;
	$half = "<img src='".$templateimagepath."star_half.png' border=0'>" ;
	$empty = "<img src='".$templateimagepath."star_empty.png' border=0'>" ;
	if ($voted) {
		$ratingbar = "<div class=\"ratings\">member rating<br>" ;
		if ($average_rating > 4.5) {
			$ratingbar .= $full.$full.$full.$full.$full ;
		}
		else if ($average_rating > 4.0) {
			$ratingbar .= $full.$full.$full.$full.$half ;
		}
		else if ($average_rating > 3.5) {
			$ratingbar .= $full.$full.$full.$full.$empty ;
		}
		else if ($average_rating > 3.0) {
			$ratingbar .= $full.$full.$full.$half.$empty ;
		}
		else if ($average_rating > 2.5) {
			$ratingbar .= $full.$full.$full.$empty.$empty ;
		}
		else if ($average_rating > 2.0) {
			$ratingbar .= $full.$full.$half.$empty.$empty ;
		}
		else if ($average_rating > 1.5) {
			$ratingbar .= $full.$full.$empty.$empty.$empty ;
		}
		else if ($average_rating > 1.0) {
			$ratingbar .= $full.$half.$empty.$empty.$empty ;
		}
		else if ($average_rating > 0.5) {
			$ratingbar .= $full.$empty.$empty.$empty.$empty ;
		}
		else if ($average_rating > 0.0) {
			$ratingbar .= $half.$empty.$empty.$empty.$empty ;
		}
		else {
			$ratingbar .= $empty.$empty.$empty.$empty.$empty ;
		}
		$ratingbar .= "</div>" ;
	}
	else {
		//voting
		$ratingbar = "<div class=\"ratings\">Rate this out of 5 <br>" ;
		$ratingbar .= '1<img src="'.$templateimagepath.'star_full.png" border=0 alt="1 Rate" onClick="doRate(1,\''.quote_smart($_GET['vidid']).'\');" style="cursor: hand; cursor: pointer;"/>' ;
		$ratingbar .= '2<img src="'.$templateimagepath.'star_full.png" border=0 alt="1 Rate" onClick="doRate(2,\''.quote_smart($_GET['vidid']).'\');" style="cursor: hand; cursor: pointer;"/>' ;
		$ratingbar .= '3<img src="'.$templateimagepath.'star_full.png" border=0 alt="1 Rate" onClick="doRate(3,\''.quote_smart($_GET['vidid']).'\');" style="cursor: hand; cursor: pointer;"/>' ;
		$ratingbar .= '4<img src="'.$templateimagepath.'star_full.png" border=0 alt="1 Rate" onClick="doRate(4,\''.quote_smart($_GET['vidid']).'\');" style="cursor: hand; cursor: pointer;"/>' ;
		$ratingbar .= '5<img src="'.$templateimagepath.'star_full.png" border=0 alt="1 Rate" onClick="doRate(5,\''.quote_smart($_GET['vidid']).'\');" style="cursor: hand; cursor: pointer;"/>' ;
		$ratingbar .= "</div>" ;
	}
	return $ratingbar ;
}
?>
