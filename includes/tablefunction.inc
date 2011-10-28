<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
function Tableview($ulget, $res, $page = 1, $url = "", $filter = all) {
	global $db,$sitepath,$loggedIn,$templateimagepath ;
	$vidcount = 0 ;
	foreach ($res as $key=>$value) {
		if ($value['added'] < time()) {
			$visible = true ;
			if ($visible) {
				$vidcount++ ;
			}
		}
	}
		switch ($ulget) {
			case '1':
			//mp_allvideos
				$perpage = getSetting("mp_allvideos", $db) ;
			break ;
			case '2':
			//mp_favoritevideos
				$perpage = getSetting("mp_favoritevideos", $db) ;
			break ;
			case '3':
			//mp_inbox
				$perpage = getSetting("mp_inbox", $db) ;
			break ;	
			case '4':
			//mp_outbox
				$perpage = getSetting("mp_outbox", $db) ;
			break ;	
			case '5':
			//mp_friends
				$perpage = getSetting("mp_friends", $db) ;
			break ;	
			case '6':
			//mp_receivedrequests
				$perpage = getSetting("mp_receivedrequests", $db) ;
			break ;	
			case '7':
			//mp_sentrequests
				$perpage = getSetting("mp_sentrequests", $db) ;
			break ;	
			case '8':
			//mp_profileviews
				$perpage = getSetting("mp_profileviews", $db) ;
			break ;	
			case '9':
			//mp_blockedmembers
				$perpage = getSetting("mp_blockedmembers", $db) ;
			break ;	
			case '10':
			//mp_members
				$perpage = getSetting("mp_members", $db) ;
			break ;	
			
			case '11':
			//mp_category
			$perpage = getSetting("mp_category", $db) ;
			break ;	
			case '12':
			//mp_mediasearch
			$perpage = getSetting("mp_mediasearch", $db) ;
			break ;	
			case '13':
			//mp_uploadedvideos
			$perpage = getSetting("mp_uploadedvideos", $db) ;
			break ;	
			case '14':
			//mp_mostviewed
			$perpage = getSetting("mp_mostviewed", $db) ;
			break ;	
			case '15':
			//mp_toprated
			$perpage = getSetting("mp_toprated", $db) ;
			break ;	
			case '16':
			//mp_viewinghistory
			$perpage = getSetting("mp_viewinghistory", $db) ;
			break ;										
	}
	$pages = ceil($vidcount / $perpage) ;
	$path = getSetting("sitefolder", $db) ;
	$pageLinks = "" ;
	//Page formatting
	if ($pages > 0) {
		$pageLinks = "<ul class=\"paging\">" ;
	}
	else {
		$pageLinks = "<ul>" ;
	}
	$pp = $page - 1 ;
	if ($pp >= 1) {
		$pageLinks .= "<a class=\"prevp\" href='".$url."/".$pp."'>Previous Page</a>" ;
	}
	$p = 1 ;
	$stopat = ($pages <= 10) ? $pages : 10 ;
	if ($pages > 10 && $page > 6) {
		if (!$nomr) {
			$pageLinks .= "<a href='".$url."/1'>1</a> ... " ;
		}
		else {
			$pageLinks .= "<a href='".$url."/1'>1</a> ... " ;
		}
	}
	$p = 1 ;
	$stopat = ($pages <= 10) ? $pages : 10 ;
	if ($pages > 10 && $page > 5) {
		$p = $page - 5 ;
		$stopat = $page + 5 ;
		if ($stopat > $pages)
			$stopat = $pages ;
	}
	for ($p; $p <= $stopat; $p++) {
		if (!$nomr) {
			if ($p == $page)
				$pageLinks .= "<a class=\"selected\" href='".$url."/".$p."'>$p</a> " ;
			else
				$pageLinks .= "<a class=\"normal\" href='".$url."/".$p."'>$p</a> " ;
		}
		else {
			if ($p == $page)
				$pageLinks .= "$p " ;
			else
				$pageLinks .= "<a href='".$url."/".$p."'>$p</a> " ;
		}
	}
	if ($pages > 10) {
		if (!$nomr) {
			$pageLinks .= "... <a href='".$url."/".$pages."'>$pages</a>" ;
		}
		else {
			$pageLinks .= "... <a href='".$url."/".$pages."'>$pages</a>" ;
		}
	}
	$np = $page + 1 ;
	if ($np <= $pages) {
		$pageLinks .= "<a class=\"nextp\" href='".$url."/".$np."'>Next Page</a>" ;
	}
	$pageLinks .= "</ul>" ;
	
	
	$db->query("SELECT * FROM sitead WHERE adname='ad4'") ;
			if ($db->numRows() > 0) {
				$ares = $db->fetch() ;
				$ad4 = $ares['adtext'] ;
				if ($ad4 != '') {
					$ad4 = '<div id="ad728x90">'.$ad4.'</div>' ;
				}
	}
	
	switch ($ulget) {
		case '1':
		case '10':
		case '11':
		case '12':
		case '14':
		case '15':
			$output = '<ul class="thumbvideo">' ;		
		break ;
		case '2':
		case '13':
		case '16':
			$output = '<ul class="mymedia">' ;
		break ;
		case '3':	
			foreach ($res as $key=>$value) {
			$db->query("UPDATE message SET msgread=1 WHERE toid=".$value['toid']) ;
			}
			$output = '<ul class="messages">' ;
		break ;	
		case '4':	
		case '5':	
		case '6':
		case '7':
		case '8':
		case '9':
			$output = '<ul class="messages">' ;
		break ;	
	}
	
	$db->query("SELECT * FROM sitead WHERE adname='ad6'") ;
		if ($db->numRows() > 0) {
			$ares = $db->fetch() ;
			$ad6 = $ares['adtext'] ;
			if ($ad6 != '') {
				$ad6 = '<div id="ad728x90">'.$ad6.'</div>' ;
			}
		}
	$db->query("SELECT * FROM sitead WHERE adname='ad8'") ;
		if ($db->numRows() > 0) {
			$ares = $db->fetch() ;
			$ad8 = $ares['adtext'] ;
			if ($ad8 != '') {
				$ad8 = '<div id="ad728x90">'.$ad8.'</div>' ;
			}
		}
	$db->query("SELECT * FROM sitead WHERE adname='ad10'") ;
		if ($db->numRows() > 0) {
			$ares = $db->fetch() ;
			$ad10 = $ares['adtext'] ;
			if ($ad10 != '') {
				$ad10 = '<div id="ad728x90">'.$ad10.'</div>' ;
			}
		}
	switch ($ulget) {
		case '1':
			$output .= $ad4 ;	
		break ;
		case '15':
			$output .= $ad6 ;	
		break ;
		case '14':
			$output .= $ad8 ;	
		break ;
		case '10':
			$output .= $ad10 ;	
		break ;
	}
	
	$count = 0 ;
	$colcount = 0 ;
	$page-- ;	
	//Clear previous page results
	for ($i = 0; $i < $perpage * $page; $i++)
		unset($res[$i]) ;
	foreach ($res as $key=>$value) {
		if ($value['added'] < time()) {

			$visible = true ;
			if ($visible) {
				$count++ ;
				$colcount++ ;

				
				
				switch ($ulget) {
					case '1':
					case '2':
					case '11':
					case '12':
					case '13':
					case '14':
					case '15':
					case '16':
						$thumbpath = $path.'uploads/thumbs/' ;
						$thumb = $sitepath."uploads/thumbs/".$value['fileid'].".jpg" ;
							if ($thumb == '') {
								$thumb = $templateimagepath."default_video_thumb.jpg" ;
							}
						$thumb = str_replace(" ", "%20", $thumb) ;
						$viewstring = $value['allviews'] ;
						$db->query("SELECT * FROM rating WHERE id = ".$value['id']) ;
						$resR = $db->fetch() ;
						$shortTitle = force_length($value['title'], getSetting("titledisplaylength", $db)) ;
						$title = url_encode($value['title']) ;
			
						if (($filter == "all") || ($filter == "")) {
							$viewstring = $value['allviews'] ;
						}
						else if ($filter == "today") {
							$viewstring = $value['dayviews'] ;
						}
						else if ($filter == "week") {
							$viewstring = $value['weekviews'] ;
						}
						else if ($filter == "month") {
							$viewstring = $value['monthviews'] ;
						}
						else if ($filter == "toprated") {
							$viewstring = $value['allviews'] ;
						}
						if ($viewstring == '') {
							$viewstring = 0 ;
						}
						$output .= "<li>" ;
						$output .= "<br /><a href='".$sitepath."play/".$title."'><img  src='".$thumb."' alt='".$title."' /></a>" ;
						
						$output .= "<div class=\"thumbholder\">" ;
						$output .= "<a href='".$sitepath."play/".$title."'>".str_replace("-", " ", $shortTitle)."</a><br />" ;
						$output .= "Duration: ".$value['duration']."<br />" ;
						$output .= "views: ".$viewstring."<br />" ;
						$output .= basicshow_rating($value['id']) ;
						$mymediatest = substr($url, -14);
						
						if (($mymediatest == "uploadedvideos") && (getSetting(membervideodelete, $db) == 1)) {
							$output .= "<br /><form action=\"".$url."\" method=\"POST\"><input type=\"submit\" class=\"biggerbutton\" name=\"deletemedia\" value=\"Delete Video\"><input type=\"hidden\" name=\"deletemediaid\" value=\"".$value['id']."\"></form>\n";
						}
						if ($mymediatest == "favoritevideos") {
							$output .= "<br /><form action=\"".$url."\" method=\"POST\"><input type=\"submit\" class=\"biggerbutton\" name=\"deletemedia\" value=\"Delete Video\"><input type=\"hidden\" name=\"deletemediaid\" value=\"".$value['id']."\"></form>\n";
						}
						$output .= "</div>" ;
						$output .= "</li>\n" ;
					break ;
					case '3':
						$output .= "<li>" ;
						$foreignid = $value['fromid'] ;
						$db->query("SELECT * FROM member WHERE id = '".$foreignid."'") ;
						$foreign = $db->fetch() ;
						$avatargender = $foreign['gender'] > 0 ? 'female' : 'male' ;
						$avatard = $templateimagepath."default_".$avatargender."_avatar.png" ;
						if (@file_exists("uploads/avatars/".$foreign['avatar']) && ($foreign['avatar'] != "")) {
							$avatard = $sitepath."uploads/avatars/".$foreign['avatar'] ;
						}
						$sentdate = date("Y-m-d H:i", $value['sentdate']) ;
						
						$output .= '<div class="messages-pic"><a href="'.$sitepath.'profile/'.$foreign['username'].'"><img src="'.$avatard.'" width="160" height="120" alt="'.$foreign['username'].'" /></a>' ;
						$output .= 'Message from: <a href="'.$sitepath.'profile/'.$foreign['username'].'"><strong>'.$foreign['username'].'</strong></a><br />Received: <strong><font size="1">'.$sentdate.'</font></strong></div>' ;
						$output .= '<div class="messages-body">Reply to user: <a href="'.$sitepath.'account/sendmsg/'.$foreignid.'"><strong>'.$foreign['username'].'</strong></a><br />Message: '.$value['body'].'</div>' ;
						$output .= '<div class="messages-commands">' ;
						$output .= '<form action="'.$url.'" method="POST">' ;
						$output .= '<input type="submit" class="biggerbutton" name="deletemessage" value="Delete This Message" />' ;
						$output .= '<input type="hidden" name="deletemessage[]" value="d'.$value['messageid'].'" />' ;
						$output .= '<input type="submit" class="biggerbutton" name="deletemessage" value="Delete This Message and block user" />' ;
						$output .= '<input type="hidden" name="deletemessage[]" value="b'.$value['messageid'].'" />' ;
						$output .= '</form></div></li>' ;

					break;
					case '4':
						$output .= "<li>" ;
						$foreignid = $value['toid'] ;
						$db->query("SELECT * FROM member WHERE id = '".$foreignid."'") ;
						$foreign = $db->fetch() ;
						$avatargender = $foreign['gender'] > 0 ? 'female' : 'male' ;
						$avatard = $templateimagepath."default_".$avatargender."_avatar.png" ;
						if (@file_exists("uploads/avatars/".$foreign['avatar']) && ($foreign['avatar'] != "")) {
							$avatard = $sitepath."uploads/avatars/".$foreign['avatar'] ;
						}
						$sentdate = date("Y-m-d H:i", $value['sentdate']) ;
						$output .= '<div class="messages-pic"><a href="'.$sitepath.'profile/'.$foreign['username'].'"><img src="'.$avatard.'" width="160" height="120" alt="'.$foreign['username'].'" /></a>' ;
						$output .= 'Sended to: <a href="'.$sitepath.'profile/'.$foreign['username'].'"><strong>'.$foreign['username'].'</strong></a><br />Date Sent: <strong>'.$sentdate.'</strong></div>' ;
						$output .= '<div class="messages-body">Send another Message to user: <a href="'.$sitepath.'account/sendmsg/'.$foreignid.'"><strong>'.$foreign['username'].'</strong></a><br /><br />Message that was sent:<br /> '.$value['body'].'</div>' ;
						
						$output .= '</li>' ;
					break;
					case '5':
						$output .= "<li>" ;
						$db->query("SELECT * FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'") ;
						$idres3 = $db->fetch() ;
						$usertmp = $idres3['id'] ;
						if ($value['friendid'] == $usertmp) {
							$friendid = $value['userid'] ;
						} else {
							$friendid = $value['friendid'] ;
						}
						$db->query("SELECT * FROM member WHERE id = '".$friendid."'") ;
						$resf = $db->fetch() ;
						$avatargender = $resf['gender'] > 0 ? 'female' : 'male' ;
						$avatard = $templateimagepath."default_".$avatargender."_avatar.png" ;
							if (@file_exists("uploads/avatars/".$resf['avatar']) && ($resf['avatar'] != "")) {
							$avatard = $sitepath."uploads/avatars/".$resf['avatar'] ;
						}
						$output .= '<div class="messages-pic"><a href="'.$sitepath.'profile/'.$resf['username'].'"><img src="'.$avatard.'" width="160" height="120" alt="'.$resf['username'].'" /></a></div>' ;
						$output .= '<div class="messages-body">Send message to: <a href="'.$sitepath.'account/sendmsg/'.$friendid.'"><strong>'.$resf['username'].'</strong></a><br />Gender:'.$avatargender.'<br />About user:<br /> '.$resf['aboutme'].'</div>' ;
						
						$output .= '<div class="messages-commands">' ;
						$output .= '<form action="'.$url.'" method="POST">' ;
						$output .= '<input type="submit" class="biggerbutton" name="removeandblock" value="Remove this friend" />' ;
						$output .= '<input type="hidden" name="removeandblock[]" value="d'.$value['friendid'].'" />' ;	
						$output .= '<input type="submit" class="biggerbutton" name="removeandblock" value="Remove this friend and block friend" />' ;
						$output .= '<input type="hidden" name="removeandblock[]" value="b'.$value['friendid'].'" />' ;
						$output .= '</form></div></li>' ;
					break;
					case '6':
						$output .= "<li>" ;
						$friendid = $value['friendid'] ;
						$db->query("SELECT * FROM member WHERE id = '".$friendid."'") ;
						$resf = $db->fetch() ;
						$avatargender = $resf['gender'] > 0 ? 'female' : 'male' ;
						$avatard = $templateimagepath."default_".$avatargender."_avatar.png" ;
						if (@file_exists("uploads/avatars/".$resf['avatar']) && ($resf['avatar'] != "")) {
							$avatard = $sitepath."uploads/avatars/".$resf['avatar'] ;
						}
						$output .= '<div class="messages-pic"><a href="'.$sitepath.'profile/'.$resf['username'].'"><img src="'.$avatard.'" width="160" height="120" alt="'.$resf['username'].'" /></a></div>' ;
						$output .= '<div class="messages-body">Send message to: <a href="'.$sitepath.'account/sendmsg/'.$friendid.'"><strong>'.$resf['username'].'</strong></a><br />Gender:'.$avatargender.'<br />About user:<br /> '.$resf['aboutme'].'</div>' ;
						$output .= '<div class="messages-commands">' ;
						$output .= '<form action="'.$url.'" method="POST">' ;
						$output .= '<input type="submit" class="biggerbutton" name="becomefriends" value="Become friends" />' ;
						$output .= '<input type="hidden" name="becomefriends[]" value="d'.$value['friendid'].'" />' ;
						$output .= '<input type="submit" class="biggerbutton" name="becomefriends" value="Decline member" />' ;
						$output .= '<input type="hidden" name="becomefriends[]" value="b'.$value['friendid'].'" />' ;
						$output .= '<input type="submit" class="biggerbutton" name="becomefriends" value="Decline and block member" />' ;
						$output .= '<input type="hidden" name="becomefriends[]" value="c'.$value['friendid'].'" />' ;
						$output .= '</form></div></li>' ;
					break;
					case '7':
						$output .= "<li>" ;
						$friendid = $value['userid'] ;
						$db->query("SELECT * FROM member WHERE id = '".$friendid."'") ;
						$resf = $db->fetch() ;
						$avatargender = $resf['gender'] > 0 ? 'female' : 'male' ;
						$avatard = $templateimagepath."default_".$avatargender."_avatar.png" ;
						if (@file_exists("uploads/avatars/".$resf['avatar']) && ($resf['avatar'] != "")) {
							$avatard = $sitepath."uploads/avatars/".$resf['avatar'] ;
						}
						$output .= '<div class="messages-pic"><a href="'.$sitepath.'profile/'.$resf['username'].'"><img src="'.$avatard.'" width="160" height="120" alt="'.$resf['username'].'" /></a></div>' ;
						$output .= '<div class="messages-body">Send message to: <a href="'.$sitepath.'account/sendmsg/'.$friendid.'"><strong>'.$resf['username'].'</strong></a><br />Gender:'.$avatargender.'<br />About user:<br /> '.$resf['aboutme'].'</div>' ;
						
						$output .= '<div class="messages-commands">' ;
						$output .= '<form action="'.$url.'" method="POST">' ;
						$output .= '<input type="submit" class="biggerbutton" name="cancelfriends" value="Cancel the invite" />' ;
						$output .= '<input type="hidden" name="cancelfriends" value="'.$value['userid'].'" />' ;
						$output .= '</form></div></li>' ;
					break;
					case '8':
						
						$friendid = $value['id'] ;
						$db->query("SELECT * FROM member WHERE id = '".$friendid."'") ;
						$resf = $db->fetch() ;
						$avatargender = $resf['gender'] > 0 ? 'female' : 'male' ;
						$avatard = $templateimagepath."default_".$avatargender."_avatar.png" ;
						if (@file_exists("uploads/avatars/".$resf['avatar']) && ($resf['avatar'] != "")) {
							$avatard = $sitepath."uploads/avatars/".$resf['avatar'] ;
						}
						$db->query("SELECT * FROM friend WHERE (userid =".$resf['id']." OR friendid =".$resf['id'].") AND friend_removed=0 AND friend_approved=1") ;
						$friendscount = $db->numRows() ;
	    					$db->query("SELECT * FROM media WHERE poster = '".quote_smart(strtolower($_SESSION['session_username']))."' AND status = 'true'") ;
            					$mediacount = $db->numRows() ;
            					$output .= "<li>" ;
						$output .= '<div class="messages-pic"><a href="'.$sitepath.'profile/'.$resf['username'].'"><img src="'.$avatard.'" width="160" height="120" alt="'.$resf['username'].'" /></a></div>' ;
						$output .= '<div class="messages-body">Send message to: <a href="'.$sitepath.'account/sendmsg/'.$friendid.'"><strong>'.$resf['username'].'</strong></a><br />Gender:'.$avatargender.'<br />Friends:'.$friendscount.'<br />Media: '.$mediacount.'<br />About user:<br /> '.$resf['aboutme'].'</div>' ;				
						$output .= '</li>' ;
					break;	
					
					
					case '9':
						$blockid = $value['blockee_id'] ;
						$db->query("SELECT * FROM member WHERE id = '".$blockid."'") ;
						$resf = $db->fetch() ;
						$avatargender = $resf['gender'] > 0 ? 'female' : 'male' ;
						$avatard = $templateimagepath."default_".$avatargender."_avatar.png" ;
						if (@file_exists("uploads/avatars/".$resf['avatar']) && ($resf['avatar'] != "")) {
							$avatard = $sitepath."uploads/avatars/".$resf['avatar'] ;
						}
						$output .= "<li>" ;
						$output .= '<div class="messages-pic"><a href="'.$sitepath.'profile/'.$resf['username'].'"><img src="'.$avatard.'" width="160" height="120" alt="'.$resf['username'].'" /></a></div>' ;
						$output .= '<div class="messages-body">Send message to: <a href="'.$sitepath.'account/sendmsg/'.$blockid.'"><strong>'.$resf['username'].'</strong></a><br />Gender:'.$avatargender.'<br />About user:<br /> '.$resf['aboutme'].'</div>' ;
						$output .= '<div class="messages-commands">' ;
						$output .= '<form action="'.$url.'" method="POST">' ;
						$output .= '<input type="submit" class="biggerbutton" name="removeblockmem" value="Unblock Member" />' ;
						$output .= '<input type="hidden" name="removeblockmem" value="'.$value['blockee_id'].'" />' ;
						$output .= '</form></div></li>' ;
					break;
					case '10':
					
						$avatargender = $value['gender'] > 0 ? 'female' : 'male' ;
						$avatar = $templateimagepath."default_".$avatargender."_avatar.png" ;
						if (@file_exists("uploads/avatars/".$value['avatar']) && ($value['avatar'] != "")) {
							$avatar = $sitepath."uploads/avatars/".$value['avatar'] ;
						}
						$avatar = str_replace(" ", "%20", $avatar) ;
						$id = $value['id'] ;
						$username = $value['username'] ;
						$db->query("SELECT id FROM media WHERE status='true' AND poster ='".$username."'".$hide." ORDER BY allviews DESC") ;
						$mediacount = $db->numRows() ;
						$rres = $db->fetch() ;
						$db->query("SELECT * FROM member LEFT JOIN friend ON (member.id = friend.friendid OR member.id = friend.userid) WHERE (friend.userid =".$id." OR friend.friendid =".$id.") AND (username!='".$username."') AND friend.friend_removed=0 AND friend.friend_approved=1 GROUP BY member.id") ;
						$friendcount = $db->numRows() ;
						$value['username'] = force_length($value['username'], 25) ;				
					
						$output .= "<li>" ;
						$output .= "<br /><a href='".$sitepath."profile/".$username."'><img  src='".$avatar."' alt='".$username."' /></a>" ;
						$output .= "<div class=\"thumbholder\">" ;
						$output .= "<a href='profile/".$username."'>".$value['username']."</a><br />" ;
						$output .= "friends: ".$friendcount."<br />" ;
						$output .= "videos: ".$mediacount."<br />" ;
						$output .= "profile views: ".$value['profileviews'] ;
						$output .= "</div></li>" ;					
					break;
				}

				
				
				if ($count == $perpage)
					break ;
				}
		}
	}
	$output .= "</ul>" ;
	if ($pages != 1)
		$output .= $pageLinks ;
	return $output ;
}
?>