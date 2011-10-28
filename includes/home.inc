<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
include_once ("includes/common.inc") ;
global $db,$sitepath,$rootpath,$template,$templateimagepath ;

$db->query("SELECT * FROM sitead WHERE adname='ad1'") ;
if ($db->numRows() > 0) {
	$ares = $db->fetch() ;
	$ad1 = $ares['adtext'] ;
	if ($ad1 != '') {
		$ad1 = '<div id="adfront728x90">'.$ad1.'</div>' ;
	}
}
$db->query("SELECT * FROM sitead WHERE adname='ad2'") ;
if ($db->numRows() > 0) {
	$ares = $db->fetch() ;
	$ad2 = $ares['adtext'] ;
	if ($ad2 != '') {
		$ad2 = '<div id="adfront728x90">'.$ad2.'</div>' ;
	}
}
function rotator() {
	global $db,$sitepath ;

	$db->query("SELECT * FROM `media` WHERE `status` ='true' ORDER BY lastviewed DESC LIMIT 0,20") ;
	$res = $db->fetchALL() ;
	$output = '' ;
	$output .= '<ul id="mycarousel" class="jcarousel-skin-tango">' ;
		foreach ($res as $key=>$value) {	
			$title = url_encode($value['title']) ;
			$url = $sitepath.'play/'.$title ;
			$img = $sitepath."uploads/thumbs/".$value['fileid'].".jpg" ;
			$output .= '<li><a href="'.$url.'"><img src="'.$img.'" width="160" height="120" alt="'.$value['title'].'" /></a></li>' ;

		}
	$output .= '</ul>' ;

return $output ;

}

function cyclemap() {
	global $db,$sitepath ;
	$output = '' ;
	$output .= '<div id="cycleMap-buttons"><button id="cycleLeft">Left</button><button id="cycleRight">Right</button></div>';
	$output .= '<div id="cycleMap">';
	
	$db->query("SELECT * FROM `media` WHERE `status` ='true' ORDER BY lastviewed DESC LIMIT 0,14") ;
	$res = $db->fetchALL() ;
		foreach ($res as $key=>$value) {
			$title = url_encode($value['title']) ;
			$url = $sitepath.'play/'.$title ;
			$img = $sitepath."uploads/thumbs/".$value['fileid'].".jpg" ;
	
			$output .= '<img src="'.$img.'" href="'.$url.'" title="'.$value['title'].'" alt="'.$value['title'].'" />';
	
	
		}
	$output .= '</div>';

return $output ;

}

function top5today() {
	global $db,$sitepath ;
	$db->query("SELECT * FROM media WHERE status = 'true' Order by dayviews DESC LIMIT 5") ;
	$res = $db->fetchALL() ;
	$output = '' ;
	$i = '' ;
	$output .= '<div class="home-top5">' ;
		foreach ($res as $key=>$value) {
			$i++;
			$title = url_encode($value['title']) ;
			$url = $sitepath.'play/'.$title ;
			$img = $sitepath."uploads/thumbs/".$value['fileid'].".jpg" ;
			$viewstoday = $value['dayviews'] ;
			if ($viewstoday == '') {
					$viewstoday = 0 ;
			}

			$output .= '<div class="home-brick">' ;
				$output .= '<div class="home-top5-num">'.$i.'</div>' ;
				$output .= '<div class="home-top5-pic"><a href="'.$url.'"><img src="'.$img.'" width="30" height="30" alt="'.$value['title'].'" /></a></div>' ;
				$output .= '<div class="home-top5-title"><a href="'.$url.'">'.force_length($value['title'], 32).'</a></div>' ;
			$output .= '<div class="clearfix"></div>' ;
			$output .= '</div>' ;
		}

$output .= '</div>' ;

return $output ;
}

function membershome() {
	global $db,$sitepath,$templateimagepath ;
	$db->query("SELECT * FROM member WHERE activationkey = '0' ORDER BY id DESC LIMIT 5") ;
	$res = $db->fetchALL() ;
	$output = '' ;
	$output .= '<div class="home-mem">' ;
	$i = '' ;
			foreach ($res as $key=>$value) {
			$i++;
			$url = $sitepath."profile/".$value['username'] ;
			$avatargender = $value['gender'] > 0 ? 'female' : 'male' ;
			$avatar = $templateimagepath."default_".$avatargender."_avatar.png" ;
			if (@file_exists("uploads/avatars/".$value['avatar']) && ($value['avatar'] != "")) {
				$avatar = $sitepath."uploads/avatars/".$value['avatar'] ;
			}
			$img = str_replace(" ", "%20", $avatar) ;
			$output .= '<div class="home-brick">' ;

			$output .= '<div class="home-mem-pic"><a href="'.$url.'"><img src="'.$img.'" width="30" height="30" alt="'.$value['username'].'" /></a></div>' ;
			$output .= '<div class="home-mem-title"><a href="'.$url.'">'.$value['username'].'</a><br />Location: '.$value['location'].' Age: '.$value['age'].'</div>' ;

			$output .= '<div class="clearfix"></div>' ;
			$output .= '</div>' ;
		}

$output .= '</div>' ;
return $output ;
}


function latestupload() {
	global $db,$sitepath,$templateimagepath ;
	$db->query("SELECT * FROM `media` WHERE `status` ='true' ORDER BY id DESC LIMIT 12") ;
	$res = $db->fetchALL() ;
	$sitefolder = getSetting("sitefolder", $db) ;
	$path = "http://".$_SERVER['SERVER_NAME'].$sitefolder ;
	$output = '<ul class="horiz-thumbs-list">' ;
	
	
	foreach ($res as $value) {
		$thumbpath = $path.'uploads/thumbs/' ;
		$thumb = $sitepath."uploads/thumbs/".$value['fileid'].".jpg" ;
			if ($thumb == '') {
				$thumb = $templateimagepath."default_video_thumb.jpg" ;
			}
		$thumb = str_replace(" ", "%20", $thumb) ;
		$db->query("SELECT * FROM rating WHERE id = ".$value['id']) ;
		$resR = $db->fetch() ;
				$title = url_encode($value['title']) ;
				$added = datez_diff(date("Y-m-d H:i:s", $value["added"]), date("Y-m-d H:i:s")) ;
				$short_title = force_length($value['title'], 29) ;
				$viewstring = $value['allviews'] ;

				$output .= "<li>" ;
				$output .= '<div class="related-col-pic"><a href="'.$path.'play/'.$title.'"><img class="thumb" src="'.$thumb.'" /></a></div>' ;
				$output .= '<div class="related-col-body"><a href="'.$path.'play/'.$title.'">'.$short_title.'</a><br />'.$added.'<br />Views: '.$viewstring.'<br />'.show_rating($value['id']).'</div>' ;
				$output .= "</li>" ;
	}
	$output .= "</ul>" ;
	return $output ;
}


?>