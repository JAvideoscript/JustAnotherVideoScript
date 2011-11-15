<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
include_once "includes/common.inc" ;
global $db,$sitepath,$rootpath,$template,$templateimagepath,$loggedIn;

//moet blijven
$vrw = quote_smart($_GET['vrw']) ; //title of video with -
$tabfav = strpos($vrw, '/addfav');
$tabflag = strpos($vrw, '/flagmedia');

if ($tabfav !== false) {
	$addfav = 1 ;
	$vrw = str_replace("/addfav", "", $vrw);
}
if ($tabflag !== false) {
	$addflag = 1 ;
	$vrw = str_replace("/flagmedia", "", $vrw);
}

$videotitle = str_replace("-", " ", $vrw); //video title without the - 


$pagelink = $sitepath."play/" ; 
if ($vrw != "") {
	$pagelink .= str_replace(" ", "-", $vrw) ; //important for rating or comment i forgot lol
	$_SESSION['session_pagelink'] = $pagelink ; //maybe I use this
}
//get advertising

	$db->query("SELECT * FROM sitead WHERE adname='ad12'") ;
	if ($db->numRows() > 0) {
		$ares = $db->fetch() ;
		$ad12 = $ares['adtext'] ;
		if ($ad12 != '') {
			$ad12 = '<div id="adsecond468x60">'.$ad12.'</div>' ;
		}
	}
	$db->query("SELECT * FROM sitead WHERE adname='ad13'") ;
	if ($db->numRows() > 0) {
		$ares = $db->fetch() ;
		$ad13 = $ares['adtext'] ;
		if ($ad13 != '') {
			$ad13 = '<div id="adsecond468x60">'.$ad13.'</div>' ;
		}
	}
	$db->query("SELECT * FROM sitead WHERE adname='ad14'") ;
	if ($db->numRows() > 0) {
		$ares = $db->fetch() ;
		$ad14 = $ares['adtext'] ;
		if ($ad14 != '') {
			$ad14 = '<div id="adsecond300x250">'.$ad14.'</div>' ;
		}
	}
	$db->query("SELECT * FROM sitead WHERE adname='ad15'") ;
	if ($db->numRows() > 0) {
		$ares = $db->fetch() ;
		$ad15 = $ares['adtext'] ;
		if ($ad15 != '') {
			$ad15 = '<div id="adsecond300x250">'.$ad15.'</div>' ;
		}
	}

//now get the right video from database
	$db->query("SELECT * FROM media WHERE title = '".$videotitle."'") ;
	$videores = $db->fetch() ;
	
	$poster = $videores['poster']; //poster of the video
	$vidid = $videores['id']; //related colum for user vids
	$tags = $videores['tags']; //related colum for suggestions
	$title = $videores['title']; //title above the video
	
	//personal ad creating
	if ($videores['vidad'] != '') {
		$personalvideoad = '<div id="adsecond468x60">'.$videores['vidad'].'</div>' ;
	}
	
	// update views
	$db->query("SELECT checkday,checkweek,checkmonth FROM media WHERE id=".$vidid) ;
	$dres = $db->fetch() ;
	$last_day = $dres['checkday'] ;
	$todays_day = mktime(0, 0, 0, date("m"), date("d"), date("Y")) ;
	if ($todays_day != $last_day) {
		$db->query("UPDATE media SET checkday='".$todays_day."',dayviews=0 WHERE id=".$vidid) ;
	}
	$last_week = intval($dres['checkweek']) ;
	$todays_week = intval(date("W")) ;
	if ($todays_week != $last_week) {
		$db->query("UPDATE media SET checkweek='".$todays_week."',weekviews=0 WHERE id=".$vidid) ;
	}
	$last_month = intval($dres['checkmonth']) ;
	$todays_month = intval(date("m")) ;
	if ($todays_month != $last_month) {
		$db->query("UPDATE media SET checkmonth='".$todays_month."',monthviews=0 WHERE id=".$vidid) ;
	}
	$db->query("UPDATE `media` SET allviews=allviews+1,monthviews=monthviews+1,weekviews=weekviews+1,dayviews=dayviews+1 WHERE `id` = '".$vidid."'") ;


	//get category under the video
	$db->query("SELECT name FROM category WHERE id = ".$videores['category']) ;
	$catres = $db->fetch() ;
	$fullcategorypath = url_encode($catres['name']) ;	
	$category = '<a href="'.$sitepath.'category/'.$fullcategorypath.'">'.str_replace("-", " ", $fullcategorypath).'</a> ' ;
	
	//get tags under the video
	
	$videotags = strtolower($videores['tags']) ;
	
	if (str_replace(" ", "", $tags) != '') {
		$tagwords = explode(",", $tags) ;
		$taglinks = '' ;
			foreach ($tagwords as $tagword) {
				if (trim($tagword) != '') {
					$taglinks .= "<a href='".$sitepath."search/".urlencode(trim($tagword))."'>$tagword</a>," ;
				}
			}
	} else {
		$taglinks = '' ;
	}
	
	
	
	
	
	
	if (getSetting("showdesc", $db) == '1') {
		$description = $videores['description']; //description above the video if set in admin panel
	}
	//get number of votes made on this video
	$db->query("SELECT total_votes FROM rating WHERE id = '".$vidid."' LIMIT 1");
	$numV = $db->fetch();
	if ($numV['total_votes'] != "") {
		$numVotes = $numV['total_votes'] ;
	} else {
		$numVotes = "0" ;
	}
	
	//addthis is easy to use and people can share your stuff easy
	if (getSetting("showsocial", $db) == '1') {
		$showsocial = '<div class="addthis_toolbox addthis_32x32_style addthis_default_style">   
			<a class="addthis_button_facebook"></a>    
			<a class="addthis_button_twitter"></a>   
			<a class="addthis_button_email"></a>    
			<a class="addthis_button_google"></a>    
			<a class="addthis_button_myspace"></a>
			<a class="addthis_button_digg"></a>
			<a class="addthis_button_delicious"></a>
			<a class="addthis_button_reddit"></a>
			<a class="addthis_button_stumpleupon"></a>
			<a class="addthis_button_live"></a>
			<a class="addthis_button_favorites"></a>
			<a class="addthis_button_email"></a>
			<a class="addthis_button_google_plusone"></a>  
			<a class="addthis_button_compact"></a>
			</div>' ;	
	}


	//now get the video or embed code in flowplayer of jwplayer for now

	$mediaPlayer = "" ;
	if ($videores['mediatype'] == "video") {
			if (getSetting("player", $db) == 'flow') { 
			
				$mediaPlayer = '<div id="player" style="height:480px;">
						<a href="'.$sitepath.'uploads/vids/'.$videores['fileid'].'/'.$videores['fileid'].'.flv" style="display:block;width:600px;height:480px;" id="flowplayer"></a> 
						 <script type="text/javascript">
						var options = {          
						    // use the first frame of the video as a "splash image" 
						    clip: { 
						        autoPlay: true, 
						        autoBuffering: true,
						    }, 
						     
						    // controlbar settings 
						    plugins:  { 
						        controls: {             
						             all:false, 
						            scrubber:true, 
						            play:true, 
						            mute:true,
						            fullscreen:true, 
						            autoHide: "always",             
						            width: "98%",  
						            bottom: 5, 
						            left: "50%", 
						            borderRadius: 15, 
						         } 
						    } 
						};
						options.plugins.controls.bufferColor=buffcol;
						options.plugins.controls.progressColor=progcol;
						options.plugins.controls.buttonColor=butcol;
						options.plugins.controls.buttonOverColor=butovercol;
						options.plugins.controls.tooltipColor=tooltipcol;
						$f("flowplayer", "'.$sitepath.'player/flow/flowplayer-3.2.7.swf",  	options);					
						</script>
						</div>											
						';
				$medialink = $pagelink;		
			} 
			else if (getSetting("player", $db) == 'jwplayer') {
				$skinname = getSetting("skinjw", $db) ;
				if ($videores['hd'] == "1") {
					$hd = '&plugins=hd-1&hd.file='.$sitepath.'uploads/vids/'.$videores['fileid'].'/'.$videores['fileid'].'.mp4' ;
				} else {
					$hd = '' ;
				}
				$mediaPlayer = '
				<div id="player">This will be replaced with video</div>

				<script type="text/javascript">
				var so = new SWFObject("'.$sitepath.'player/jwplayer/player.swf","mpl","600","480","9");
				so.addParam("allowscriptacces","always");
				so.addParam("allowfullscreen","true");
				so.addParam("wmode","opaque");			
				so.addParam("flashvars","file='.$sitepath.'uploads/vids/'.$videores['fileid'].'/'.$videores['fileid'].'.flv'.$hd.'&amp;skin='.$sitepath.'player/jwplayer/skin/'.$skinname.'&amp;autostart=true&amp;dock=false&amp;provider=http&amp;stretching=false&amp;plugins=viral-3");
				so.write("player");
				</script>'; 

				$medialink = $pagelink;	 
			} 

	}
	else if ($videores['mediatype'] == "embed") {
		$mediaPlayer = stripslashes($videores['embed']) ;
	}	


	//now get the vars that only show or changed when user is loggedin
	
	//flag
	if ($loggedIn) {
		if ($videores['flagged'] == '0') {
			$flagvidlink = '<a href="'.$pagelink.'/flagmedia">Flag Video</a>' ;
		}
		if ($videores['flagged'] == '1') {
			$flagvidlink = '<h4><b>Flagged </b></h4>' ;
		}		
		if (($addflag == '1') && ($videores['flagged'] == '0')) {
			$db->query("UPDATE media SET flagged=1 WHERE id=".$vidid) ;
			$flagvidlink = 'Flagged ' ;
		}
		$db->query("SELECT id FROM member WHERE username = '".$_SESSION['session_username']."'") ;
		$userres = $db->fetch() ;
		$userid = $userres['id'] ;	
		$db->query("SELECT * FROM favorite WHERE userid=".$userid." AND vidid=".$vidid) ;
		if ($db->numRows() == 1) {
			$addfavlink = '<h4><b>(Added to Favorites)</b></h4>' ;
		} else {
			$addfavlink = '<a href="'.$pagelink.'/addfav">Add To<br> Favorites</a>' ;
		}
		
		if ($addfav == '1') {
			$db->query("SELECT id FROM member WHERE username = '".$_SESSION['session_username']."'") ;
			$userres = $db->fetch() ;
			$userid = $userres['id'] ;	
			$db->query("SELECT * FROM favorite WHERE userid=".$userid." AND vidid=".$vidid) ;
				if ($db->numRows() == 1) {
					$addfavlink = '<h4><b>(Added to Favorites)</b></h4>' ;
				} else {
					$db->query("INSERT INTO favorite (userid,vidid) VALUES (".$userid.",".$vidid.")") ;
					$addfavlink = '<h4><b>(Added to Favorites)</b></h4>' ;
				}
		}
		if ((getSetting("downnormalmembers", $db) == 1) && ($videores['mediatype'] == "video")) {
			$downloadnormal = '<a href="'.$sitepath.'uploads/vids/'.$videores['fileid'].'/'.$videores['fileid'].'.flv">Download</a>' ;
		}
		if (($videores['hd'] == 1) && (getSetting("downhdmember", $db) == 1) && ($videores['mediatype'] == "video")) { 
			$downloadhd = '<a href="'.$sitepath.'uploads/vids/'.$videores['fileid'].'/'.$videores['fileid'].'.mp4">Download HD</a>' ;
		}
		if (($videores['mobile'] == 1) && (getSetting("downmobilemember", $db) == 1) && ($videores['mediatype'] == "video")) { 
			$downloadmobile = '<a href="'.$sitepath.'uploads/vids/'.$videores['fileid'].'/mob_'.$videores['fileid'].'.mp4">Download Mobile</a>' ;
		}
	} 
	if (!$loggedIn) {
		if ($videores['flagged'] == '0') {
			$flagvidlink = '<a href="'.$sitepath.'login">Login to Flag</a>' ;
		}
		if ($videores['flagged'] == '1') {
			$flagvidlink = '<h4><b>Flagged </b></h4>' ;
		}
		$addfavlink = '<a href="'.$sitepath.'login">Login to add favorite</a>' ;
		if ((getSetting("downGuest", $db) == 1) && ($videores['mediatype'] == "video")) {
			$downloadnormal = '<a href="'.$sitepath.'uploads/vids/'.$videores['fileid'].'/'.$videores['fileid'].'.flv">Download</a>' ;
		}
		if (($videores['hd'] == 1) && (getSetting("downhdguest", $db) == 1) && ($videores['mediatype'] == "video")) { 
			$downloadhd = '<a href="'.$sitepath.'uploads/vids/'.$videores['fileid'].'/'.$videores['fileid'].'.mp4">Download HD</a>' ;
		}
		if (($videores['mobile'] == 1) && (getSetting("downmobileguest", $db) == 1) && ($videores['mediatype'] == "video")) { 
			$downloadmobile = '<a href="'.$sitepath.'uploads/vids/'.$videores['fileid'].'/mob_'.$videores['fileid'].'.mp4">Download Mobile</a>' ;
		}
		if ((getSetting("downGuest", $db) == 0) && (getSetting("downnormalmembers", $db) == 1) && ($videores['mediatype'] == "video")) {
			$downloadnormal = '<a href="'.$sitepath.'login">Login to Download</a>' ;
		}
	}
	




?>