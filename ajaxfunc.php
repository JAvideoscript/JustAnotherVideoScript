<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
include_once 'includes/ajaxfunctions.inc' ;
include_once 'includes/common.inc' ;
session_start() ;
$site_template = getSetting("sitetemplate", $db) ;
$templateimagepath = $sitepath.'templates/'.$site_template.'/images/' ;

function displayRUser($res) {
	global $db,$sitepath,$templateimagepath ;
	$max = getSetting("relateduserpage", $db) ;
	$thumbcount = max(sizeof($res), $max) ;
	$sitefolder = getSetting("sitefolder", $db) ;
	$path = "http://".$_SERVER['SERVER_NAME'].$sitefolder ;
	if ($thumbcount > 0) {
		$output = "" ;
		$count = 0 ;
		$page-- ;
		foreach ($res as $key=>$value) {
			if ($value['added'] < time()) {
				$count++ ;
				$thumbpath = $path.'uploads/thumbs/' ;
				$thumb = $sitepath."uploads/thumbs/".$value['fileid']."/".$value['mainthumb'].".jpg" ;

					if ($thumb == '') {
						$thumb = $templateimagepath."default_video_thumb.png" ;
					}
					$thumb = str_replace(" ", "%20", $thumb) ;
				$db->query("SELECT * FROM rating WHERE id = ".$value['id']) ;
				$resR = $db->fetch() ;
				$title = url_encode($value['title']) ;
				$added = datez_diff(date("Y-m-d H:i:s", $value["added"]), date("Y-m-d H:i:s")) ;
				$short_title = force_length($value['title'], 30) ;
				$viewstring = $value['allviews'] ;
				$output .= "<li>" ;
				$output .= '<div class="related-col-pic"><a href="'.$path.'play/'.$title.'"><img class="thumb" src="'.$thumb.'" /></a></div>' ;
				$output .= '<div class="related-col-body"><a href="'.$path.'play/'.$title.'">'.$short_title.'</a><br />'.$added.'<br />Views: '.$viewstring.'<br />'.show_rating($value['id']).'</div>' ;

				$output .= "</li>" ;
				if ($count >= $max) {
					break ;
				}
			}
		}
	}
	return $output ;
}
global $sitepath,$templateimagepath ;
if (($_GET['id'] == 1) && ($_GET['tags'] != '') && ($_GET['poster'] != '')) {
	$tags = quote_smart($_GET['tags']) ;
	$poster = quote_smart($_GET['poster']) ;
	$db->query("SELECT * FROM media WHERE `status`='true' AND MATCH (tags) AGAINST ('".quote_smart(trim($_GET['tags']))."' IN BOOLEAN MODE) LIMIT 18") ;
	$res = $db->fetchALL() ;
	echo '
	<ul class="c-tabs">
		<li class="crt">
			<span>
				<a class="rel" style="cursor: hand; cursor: pointer;" onClick="doRelated(\''.$tags.'\',\''.$poster.'\');">Suggestions </a>
			</span>
		</li>
		<li>
			<span>
				<a class="rel" style="cursor: hand; cursor: pointer;" onClick="doUser(\''.$tags.'\',\''.$poster.'\');"> User video\'s   </a>
			</span>
		</li>
	</ul>' ;
	echo '<div class="tab-cont"><ul class="horiz-thumbs-list">' ;
	echo displayRUser($res) ;
	echo '</ul></div>' ;
}
if (($_GET['id'] == 2) && ($_GET['tags'] != '') && ($_GET['poster'] != '')) {
	$tags = quote_smart($_GET['tags']) ;
	$poster = quote_smart($_GET['poster']) ;
	$db->query("SELECT * FROM media WHERE `status`='true' AND poster = '".quote_smart(trim($_GET['poster']))."' ORDER BY id DESC LIMIT 18") ;
	$res = $db->fetchALL() ;
	echo '
	<ul class="no-format c-tabs">
		<li>
			<span>
				<a class="rel" style="cursor: hand; cursor: pointer;" onClick="doRelated(\''.$tags.'\',\''.$poster.'\');">Suggestions </a>
			</span>
		</li>
		<li class="crt">
			<span>
				<a class="rel" style="cursor: hand; cursor: pointer;" onClick="doUser(\''.$tags.'\',\''.$poster.'\');"> User video\'s   </a>
			</span>
		</li>
	</ul>' ;
	echo '<div class="tab-cont"><ul class="horiz-thumbs-list">';
	echo displayRUser($res);
	echo '</ul></div>' ;
}
if (($_GET['id'] == 3) && ($_GET['comment'] != '')) {
	$scode2 = quote_smart($_GET['scode2']) ;
	$vidid = quote_smart($_GET['vidid']) ;
	$_SESSION['session_vidid']  = $vidid;
	$name = quote_smart($_GET['name']) ;
	$comment = quote_smart($_GET['comment']) ;
	$visitor = quote_smart($_GET['visitor']) ;
	$loggedIn = quote_smart($_GET['loggedIn']) ;
	if ((($_SESSION['session_security_code'] == $scode2) && (! empty($_SESSION['session_security_code']))) || ((getSetting("captchaformembers", $db) == 0) && ($loggedIn))) {
		if (! empty($name)) {
			$doComment = true ;
			if (!$loggedIn) {
				$db->query("SELECT id FROM member WHERE LOWER(username) = '".strtolower(quote_smart($name))."'") ;
				if ($db->numRows() != 0) {
					echo 'The name you entered matches the name of a user already registered!' ;
					$doComment = false ;
				}
			}
			if (! empty($comment)) {
				if ($doComment) {
					if (strlen($comment) <= getSetting('comment_length', $db)) {
						$commenttext = quote_smart($comment) ;
						if ($visitor == 'visitorposting') {
							$db->query("INSERT INTO `media_comment` (`vid_id`, `leftbyname`, `date`, `text`,`regdposter`) VALUES ('".$vidid."', '".$name."', '".date("Y-m-d H:i:s")."', '".$commenttext."',0);") ;
						}
						else {
							$db->query("INSERT INTO `media_comment` (`vid_id`, `leftbyname`, `date`, `text`,`regdposter`) VALUES ('".$vidid."', '".$_SESSION['session_username']."', '".date("Y-m-d H:i:s")."', '".$commenttext."',1);") ;
						}
						echo '<b>Your comment was added successfully. Thank you.</b>' ;
						unset($_SESSION['session_security_code']) ;

						?>
<input
	type="hidden" name="ajax" id="ajax" value="<?=$sitepath?>">
<script type="text/javascript" src="<?=$sitepath?>js/play.js">
</script>
<script type="text/javascript">
    RefreshComments();
</script>
						<?
					}
					else {
						echo '<h3>Your comment is to long, please make it less then '.getSetting('comment_length', $db).' characters.</h3>' ;
					}
				}
			}
			else {
				echo '<h3>You have to fill in something in the text box.</h3>' ;
			}
		}
		else {
			echo '<h3>You have to fill in your name.</h3>' ;
		}
	}
	else {
		echo '<h3>Please enter the security code on the form</h3>' ;
	}
}
if (($_GET['id'] == 4) && ($_GET['vidid'] != '')) {
	$pagelink = quote_smart($_SESSION['session_pagelink']) ;
	$vidid = quote_smart($_GET['vidid']) ;

	if ($_SESSION['session_username'] != "") {
		$loggedIn = 1 ;
	}
	else {
		$loggedIn = "" ;
	}
	$sql = "SELECT * FROM `media_comment` WHERE `vid_id` = '".$vidid."' ORDER BY id DESC" ;
	$result = mysql_query($sql) or die('Fehler: '.mysql_error()) ;
	$comments = $message ;
	if ($result) {
		$count = 0 ;
		while ($row = mysql_fetch_array($result, MYSQL_ASSOC)) {
			$db->query("SELECT * FROM `member` WHERE `username` = '".quote_smart($row['name'])."'") ;
			$user = $db->fetch() ;
				$del = '' ;
			$postername = $row['leftbyname'] ;
			if ($row['regdposter'] == 1) {
				$posterString = '<a href="'.$sitepath.'profile/'.htmlentities($row['leftbyname']).'">'.htmlentities($row['leftbyname']).'</a>' ;
				$db->query("SELECT * FROM `member` WHERE `username` = '".quote_smart($row['leftbyname'])."'") ;
				$user = $db->fetch() ;
				if (($user['avatar'] == '') || ($db->numRows() < 1)) {
					$avatargender = $value['gender'] > 0 ? 'female' : 'male' ;
					$avatar_tag = '<img width=80px height=60px class="thumb" src="'.$templateimagepath.'default_'.$avatargender.'_avatar.png" alt="" />' ;
				}
				else {
					$avatar_tag = '<img width=80px height=60px class="thumb" src="'.$sitepath.'uploads/avatars/'.$user['avatar'].'" alt="" />' ;
				}
			}
			else {
				$posterString = htmlentities($row['leftbyname'])." (visitor)" ;
				$avatar_tag = '<img width=80px height=60px class="thumb" src="'.$templateimagepath.'default_male_avatar.png" alt="" />' ;
			}
			$comments .= '<dl class="full-com2"><dt><b>'.$posterString.' '.$row["date"].' </b> </dt>' ;
			$comments .= '<dp>'.$avatar_tag.'</dp><dd>'.nl2br(($row['text'])).$del.'</dd></dl>' ;
		}
	}
	$comments .= '<div>' ;
	if (getSetting("restrictpc", $db) == "1" && !$loggedIn) {
		$comments .= '<a href="'.$sitepath.'register">Please login to comment<a/>' ;
	}
	else {
		$comments .= '<h2>Add comment</h2>' ;
		if ($loggedIn == 1) {
			$comments .= '<div id="inputcomment"><input type="hidden" id="name" name="name" value="'.$_SESSION['session_username'].'"/><input type="hidden" id="visitor" name="visitor" value="notguest">' ;
		}
		else {
			$comments .= '<div id="inputcomment"><li>
					Name
						<input type="hidden" id="visitor" name="visitor" value="visitorposting">
					<input id="name" name="name"  />
					</li>' ;
		}
		$comments .= '<h4>Your Comment:</h4><div id="message"><textarea id="text" name="text" size"6"></textarea></div>' ;
		if ((!$loggedIn) || (getSetting("captchaformembers", $db) == 1)) {
			$comments .= '<li><img src="'.$sitepath.'includes/CaptchaSecurityImages.php" /><br>Enter code above<br>
			<input id="security_code" name="security_code" type="text" size="6"/></li>' ;
		}
		else {
			$comments .= '<input type="hidden" id="security_code" name="security_code" value="" />' ;
		}
		$comments .= '<p><input class="button" type="button" onClick="Mcomment(\''.$vidid.'\',\''.$loggedIn.'\');" name="submit" value="Post comment" style="margin-right: 30px;"/></p></form>' ;
	}
	$comments .= '</div></div>' ;
	echo $comments ;
}
?>