<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
//ini_set('display_errors', 1);
include_once("../includes/settings.inc");
include_once("../includes/mysql.inc");
include_once("../includes/functions.inc");
include_once("../includes/imagefunctions.inc");
$db = new mysql($db_host, $db_user, $db_password, $db_database) ;
$sitefolder = getsetting("sitefolder", $db) ;
$sitepath = "http://".$_SERVER['SERVER_NAME'].$sitefolder ;
$rootpath =  $_SERVER['DOCUMENT_ROOT'].$sitefolder ;

if (removespechar($_GET["cronpass"]) != getSetting("passcron", $db)) {
	die("Wrong cron password") ;
}


//What are we going to encode
	$db->query("SELECT * from `media` WHERE status = 'encode'") ;
	$res = $db->fetchAll() ;
		foreach ($res as $key=>$value) {
			$db->query("UPDATE `media` SET `status` = 'progressencode' WHERE id = '".$value['id']."'") ;
			if($value['fileid'] == "") {
				$db->query("UPDATE `media` SET `status` = 'fucked' WHERE id = '".$value['id']."'") ;
				die() ;
			}
			$originalname = $value['fileid'] ;
			$fileid = $value['fileid'] ;
			$ext_pos = strrchr($fileid, '.') ;
			if ($ext_pos !== false) {
					$filename_without_ext = substr($fileid, 0, -strlen($ext_pos)) ;
			}
			$ext = strtolower(substr($fileid, strrpos($fileid, '.') + 1)) ;
			$thumbtime = getSetting("default_thumbtime", $db) ;
			$audiofrequency = getSetting("audiofrequency", $db) ;
			$audiobitrate = getSetting("audiobitrate", $db) ;
			$videobitrate = getSetting("videobitrate", $db) ;
			$framerate = getSetting("framerate", $db) ;
			$encodesize = getSetting("encodesize", $db) ;
			$ffmpegpath = getSetting("ffmpegpath", $db) ;
			$flvtool2path = getSetting("flvtool2path", $db) ;
			$videoaspect = getSetting("videoaspect", $db) ;
			$getvinfo = getvidinfo($rootpath."uploads/encode/".$fileid,$ffmpegpath) ;
			if(empty($getvinfo)) {
				$noinfo = "false" ;
			} else {
				$noinfo = "true" ;
			}
			$orirand = mt_rand(5, 5000);

			rename($rootpath."uploads/encode/".$filename_without_ext.".".$ext, $rootpath."uploads/encode/origineel".$orirand.".".$ext) ;
			echo 'start encoding<br>';
			switch($ext){
				case "flv":
						echo 'start flv<br>';
						if ($noinfo == "true") {
							if (($getvinfo['width'] >= "600") || ($getvinfo['height'] >= "480")) {
								echo 'flv 1<br>';
								exec($ffmpegpath." -i ".$rootpath."uploads/encode/origineel".$orirand.".".$ext." -ar ".$audiofrequency." -ab ".$audiobitrate."k -aspect ".$videoaspect." -b ".$videobitrate."k -r ".$framerate." -f flv -y -s ".$encodesize." -acodec libfaac -ac 1 ".$rootpath."uploads/encode/".$filename_without_ext.".flv 2>&1", $res1, $err) ;
							} else {
								rename($rootpath."uploads/encode/origineel".$orirand.".".$ext, $rootpath."uploads/encode/".$filename_without_ext.".flv");
								echo 'flv 2<br>';
							}
						}
						if ($noinfo == "false") {
								echo 'flv 3<br>';
								exec($ffmpegpath." -i ".$rootpath."uploads/encode/origineel".$orirand.".".$ext." -ar ".$audiofrequency." -ab ".$audiobitrate."k -aspect ".$videoaspect." -b ".$videobitrate."k -r ".$framerate." -f flv -y -s ".$encodesize." -acodec libfaac -ac 1 ".$rootpath."uploads/encode/".$filename_without_ext.".flv 2>&1", $res1, $err) ;
						}
				break;
				case "wmv":
				case "mov":
				case "mpg":
				case "avi":
				case "mpeg":
				case "3gp":
				case "mp4":
				case "rm":
				case "asf":
					echo 'start other ext<br>';
					if ($noinfo == "true") {
						if (($getvinfo['width'] <= "600") || ($getvinfo['height'] <= "480") && ($noinfo == "true")) {
							$encodesize = $getvinfo['width']."x".$getvinfo['height'] ;
						}
					}
						exec($ffmpegpath." -y -i ".$rootpath."uploads/encode/origineel".$orirand.".".$ext." -ab ".$audiobitrate."k -b ".$videobitrate."k -f flv -s ".$encodesize." -acodec libfaac -ac 1 ".$rootpath."uploads/encode/".$filename_without_ext.".flv 2>&1", $res4, $err) ;
				break;
			}
			echo 'make dir<br>';
			mkdir($rootpath."uploads/vids/".$filename_without_ext, 0755);
			$newvideopath = $rootpath."uploads/vids/".$filename_without_ext."/".$filename_without_ext.".flv" ;

			echo 'rename file<br><br>';
			rename($rootpath."uploads/encode/".$filename_without_ext.".flv", $newvideopath) ;

			if (file_exists($newvideopath)) {
				//now get duration
					$duration = getduration($newvideopath, 'site') ;
				//now get thumbs
					mkdir($rootpath."uploads/thumbs/".$filename_without_ext, 0755);
					makethumbs($newvideopath, $rootpath."uploads/thumbs/".$filename_without_ext."/");
				//now flvtool2 the video
					exec($flvtool2path." -U ".$newvideopath) ;
			}




			if (getSetting("mobilevideo", $db) == '1') {
				$esizeheight = getSetting("mobile_encodesize_height", $db) ; //default 320
				$esizewidth = getSetting("mobile_encodesize_width", $db) ; //default 480
				$encodesize = $esizeheight."x".$esizewidth ;
				if ($noinfo == "true") {
					if (($getvinfo['width'] <= $esizewidth) || ($getvinfo['height'] <= $esizeheight)) {
						$encodesize = $getvinfo['width']."x".$getvinfo['height'] ;
					}
				}

					exec($ffmpegpath." -i ".$rootpath."uploads/encode/origineel".$orirand.".".$ext." -s ".$encodesize." -vcodec mpeg4 -acodec libfaac -ac 1 -ar 16000 -r 13 -ab 32000 -aspect 3:2 ".$rootpath."uploads/encode/mob_".$filename_without_ext.".mp4 2>&1", $res6, $err) ;

						if (file_exists($rootpath.'uploads/encode/mob_'.$filename_without_ext.'.mp4')) {
							rename($rootpath."uploads/encode/mob_".$filename_without_ext.".mp4", $rootpath."uploads/vids/".$filename_without_ext."/mob_".$filename_without_ext.".mp4") ;
							$db->query("UPDATE `media` SET `mobile` = '1' WHERE id = '".$value['id']."'") ;
						}
			}

			//experimental hd video. It is hard to get it right most sites fucked up.
			if ((getSetting("hdvideo", $db) == '1') && ($noinfo == "true") && ($getvinfo['width'] >= "720") ) {
				if ((($getvinfo['videocodec'] != "h264,") || ($ext != "mp4")) && ($getvinfo['width'] >= "720")) {
					if ((getSetting("maxresolution_w", $db) > $getvinfo['width']) || (getSetting("maxresolution_h", $db) > $getvinfo['height'])) {
						$encodesize = getSetting("maxresolution_w", $db)."x".getSetting("maxresolution_h", $db) ;
						exec($ffmpegpath." -i ".$rootpath."uploads/encode/origineel".$orirand.".".$ext." -y -f mp4 -s ".$encodesize." -vcodec libx264 -crf 28 -threads 0 -flags +loop -cmp +chroma -deblockalpha -1 -deblockbeta -1 -refs 3 -bf 3 -coder 1 -me_method hex -me_range 18 -subq 7 -partitions +parti4x4+parti8x8+partp8x8+partb8x8 -g 320 -keyint_min 25 -level 41 -qmin 10 -qmax 51 -qcomp 0.7 -trellis 1 -sc_threshold 40 -i_qfactor 0.71 -flags2 +mixed_refs+dct8x8+wpred+bpyramid -padcolor 000000 -padtop 0 -padbottom 0 -padleft 0 -padright 0 -acodec libfaac -ab 80kb -ar 48000 -ac 2 ".$rootpath."uploads/encode/".$filename_without_ext.".mp4 2>&1", $res7, $err) ;
					} else {
						exec($ffmpegpath." -i ".$rootpath."uploads/encode/origineel".$orirand.".".$ext." -y -f mp4 -vcodec libx264 -crf 28 -threads 0 -flags +loop -cmp +chroma -deblockalpha -1 -deblockbeta -1 -refs 3 -bf 3 -coder 1 -me_method hex -me_range 18 -subq 7 -partitions +parti4x4+parti8x8+partp8x8+partb8x8 -g 320 -keyint_min 25 -level 41 -qmin 10 -qmax 51 -qcomp 0.7 -trellis 1 -sc_threshold 40 -i_qfactor 0.71 -flags2 +mixed_refs+dct8x8+wpred+bpyramid -padcolor 000000 -padtop 0 -padbottom 0 -padleft 0 -padright 0 -acodec libfaac -ab 80kb -ar 48000 -ac 2 ".$rootpath."uploads/encode/".$filename_without_ext.".mp4 2>&1", $res8, $err) ;
					}
					if (file_exists($rootpath.'uploads/encode/'.$filename_without_ext.'.mp4')) {
						rename($rootpath."uploads/encode/".$filename_without_ext.".mp4", $rootpath."uploads/vids/".$filename_without_ext."/".$filename_without_ext.".mp4") ;
					}

				}
				if (($ext == "mp4") && ($getvinfo['videocodec'] == "h264,")) {
					if ((getSetting("maxresolution_w", $db) > $getvinfo['width']) || (getSetting("maxresolution_h", $db) > $getvinfo['height'])) {
						$encodesize = getSetting("maxresolution_w", $db)."x".getSetting("maxresolution_h", $db) ;
						exec($ffmpegpath." -i ".$rootpath."uploads/encode/origineel".$orirand.".".$ext." -y -f mp4 -s ".$encodesize." -vcodec libx264 -crf 28 -threads 0 -flags +loop -cmp +chroma -deblockalpha -1 -deblockbeta -1 -refs 3 -bf 3 -coder 1 -me_method hex -me_range 18 -subq 7 -partitions +parti4x4+parti8x8+partp8x8+partb8x8 -g 320 -keyint_min 25 -level 41 -qmin 10 -qmax 51 -qcomp 0.7 -trellis 1 -sc_threshold 40 -i_qfactor 0.71 -flags2 +mixed_refs+dct8x8+wpred+bpyramid -padcolor 000000 -padtop 0 -padbottom 0 -padleft 0 -padright 0 -acodec libfaac -ab 80kb -ar 48000 -ac 2 ".$rootpath."uploads/encode/".$filename_without_ext.".mp4 2>&1", $res9, $err) ;
						if (file_exists($rootpath."uploads/encode/".$filename_without_ext.".mp4")) {
							rename($rootpath."uploads/encode/".$filename_without_ext.".mp4", $rootpath."uploads/vids/".$filename_without_ext."/".$filename_without_ext.".mp4") ;
						}
					} else {
						if (file_exists($rootpath."uploads/encode/origineel".$orirand.".".$ext)) {
							rename($rootpath."uploads/encode/origineel".$orirand.".".$ext, $rootpath."uploads/vids/".$filename_without_ext."/".$filename_without_ext.".mp4") ;
						}
					}

				}
				if (file_exists($rootpath."uploads/vids/".$filename_without_ext."/".$filename_without_ext.".mp4")) {
					$mp4box = getSetting("mp4box", $db) ;
					exec($mp4box." -inter 500 ".$rootpath."uploads/vids/".$filename_without_ext."/".$filename_without_ext.".mp4 2>&1", $res10, $err) ;
					$db->query("UPDATE `media` SET `hd` = '1' WHERE id = '".$value['id']."'") ;
				}

			}
			//remove origineel
			if (file_exists($rootpath."uploads/encode/origineel".$orirand.".".$ext)) {
				if (getSetting("removeorifile", $db) == '1') {
					unlink($rootpath."uploads/encode/origineel".$orirand.".".$ext) ;
				} else {
						rename($rootpath."uploads/encode/origineel".$orirand.".".$ext, $rootpath."uploads/encode/".$originalname) ;
				}
			}

			if (getSetting("autoacceptvideo", $db) == '0') {
				$status = "false" ;
				//send mail to admin there is a new video uploaded
					if (getSetting("mail_video_admin", $db) == '1') {
						$msg = getEmailformat("email_approved_admin") ;
						$msg = str_replace(array('[TITLE]', '[POSTER]', '[SITEURL]'), array($value['title'], $value['poster'], $sitepath), $msg);
						sendmail(array(array("email"=>getSetting("contact_email", $db), "name"=>getSetting("default_from", $db))), 'New Video waiting for approvement', $msg) ;
					}
			} else {
				$status = "true" ;
					if (getSetting("mail_video_approved", $db) == '1') {
						$msg = getEmailformat("email_approved") ;
						$msg = str_replace(array('[TITLE]', '[SITENAME]', '[MEDIALINK]', '[SITEURL]', '[USERNAME]'), array($value['title'], getSetting("sitename", $db), $sitepath."play/".url_encode($value['title']), $sitepath, $value['poster']), $msg);


						$db->query("SELECT email, username FROM member WHERE USERNAME = '".$value['poster']."' LIMIT 1") ;
						$member = $db->fetch() ;
						sendmail(array(array("email"=>$member['email'], "name"=>$member['username'])), 'Video Approved', $msg, 'no') ;
					}
				//send mail to subscribed users
					if (getSetting("mail_friend_subscribed", $db) == '1') {
						$db->query("SELECT id FROM member WHERE USERNAME = '".$value['poster']."' LIMIT 1") ;
						$memberid = $db->fetch() ;

						$msg = getEmailformat("email_approved_subscriber") ;
						$msg = str_replace(array('[TITLE]', '[SITENAME]', '[MEDIALINK]', '[SITEURL]', '[POSTER]'), array($value['title'], getSetting("sitename", $db), $sitepath."play/".url_encode($value['title']), $sitepath, $value['poster']), $msg);


						$db->query("SELECT * FROM subscription WHERE subscribedtoid = '".$memberid['id']."'");
						$subscripids = $db->fetchAll() ;
						$subarray = array() ;

						foreach($subscripids as $subvalue) {
							$db->query("SELECT email, username FROM member WHERE id = '".$subvalue['userid']."' LIMIT 1") ;
							$subinfo = $db->fetch() ;
							array_push($subarray, array("email"=>$subinfo['email'], "name"=>$subinfo['username']));
						}
						sendmail($subarray, $value['poster'].' Uploaded a new video', $msg, 'no') ;
					}
				//send mail to friend of users
					if (getSetting("mail_video_friends", $db) == '1') {
						$db->query("SELECT id FROM member WHERE USERNAME = '".$value['poster']."' LIMIT 1") ;
						$memberid = $db->fetch() ;
						$db->query("SELECT * FROM friend WHERE (userid = '".$memberid['id']."' OR friendid = '".$memberid['id']."') AND friend_approved = '1'");
						$friendids = $db->fetchAll() ;

						$msg = getEmailformat("email_approved_friend") ;
						$msg = str_replace(array('[TITLE]', '[SITENAME]', '[MEDIALINK]', '[SITEURL]', '[POSTER]'), array($value['title'], getSetting("sitename", $db), $sitepath."play/".url_encode($value['title']), $sitepath, $value['poster']), $msg);


						$friarray = array() ;
						foreach($friendids as $frivalue) {
							if ($memberid['id'] != $frivalue['userid']) {
								$db->query("SELECT email, username, friendmail_privacy FROM member WHERE id = '".$frivalue['userid']."' LIMIT 1") ;
								$friinfo = $db->fetch() ;
									if ($friinfo['friendmail_privacy'] != '0') {
										array_push($friarray, array("email"=>$friinfo['email'], "name"=>$friinfo['username']));
									}
							}
							if ($memberid['id'] != $frivalue['friendid']) {
								$db->query("SELECT email, username, friendmail_privacy FROM member WHERE id = '".$frivalue['friendid']."' LIMIT 1") ;
								$friinfo = $db->fetch() ;
									if ($friinfo['friendmail_privacy'] != '0') {
										array_push($friarray, array("email"=>$friinfo['email'], "name"=>$friinfo['username']));
									}
							}
						}
						sendmail($friarray, $value['poster'].' Uploaded a new video', $msg, 'no') ;
					}



			}


			$db->query("UPDATE `media` SET `duration` = '".$duration."' WHERE id = '".$value['id']."'") ;
			$db->query("UPDATE `media` SET `status` = '".$status."' WHERE id = '".$value['id']."'") ;
			$db->query("UPDATE `media` SET `fileid` = '".$filename_without_ext."' WHERE id = '".$value['id']."'") ;

//making a log for trouble shooting

		if (getSetting("keepencodelog", $db) == '1') {
			$logbook = '' ;
			$encoderlog .= "<br><h1>res1 - Encodingname: big flv to smaller</h1><br>" ;
			foreach ($res1 as $outputline) {
				$encoderlog .= $outputline."<br>" ;
			}
			$encoderlog .= "<br><h1>res2 - Encodingname: Make flv thumb</h1><br>" ;
			foreach ($res2 as $outputline) {
				$encoderlog .= $outputline."<br>" ;
			}
			$encoderlog .= "<br><h1>res3 - Encodingname: Flvtool2 the flv file</h1><br>" ;
			foreach ($res3 as $outputline) {
				$encoderlog .= $outputline."<br>" ;
			}
			$encoderlog .= "<br><h1>res4 - Encodingname: encoding any file type into flv</h1><br>" ;
			foreach ($res4 as $outputline) {
				$encoderlog .= $outputline."<br>" ;
			}
			$encoderlog .= "<br><h1>res5 - Encodingname: Make thumb of any filetype </h1><br>" ;
			foreach ($res5 as $outputline) {
				$encoderlog .= $outputline."<br>" ;
			}
			$encoderlog .= "<br><h1>res6 - Encodingname: Mobile: Convert original into mobile file</h1><br>" ;
			foreach ($res6 as $outputline) {
				$encoderlog .= $outputline."<br>" ;
			}
			$encoderlog .= "<br><h1>res7 - Encodingname: HD: Make file to xh286 and mp4 and resize because of site settings</h1><br>" ;
			foreach ($res7 as $outputline) {
				$encoderlog .= $outputline."<br>" ;
			}
			$encoderlog .= "<br><h1>res8 - Encodingname: HD: Make file to xh286 and mp4 no resize file is small enough</h1><br>" ;
			foreach ($res8 as $outputline) {
				$encoderlog .= $outputline."<br>" ;
			}
			$encoderlog .= "<br><h1>res9 - Encodingname: HD: File is mp4 but to big for site settings</h1><br>" ;
			foreach ($res9 as $outputline) {
				$encoderlog .= $outputline."<br>" ;
			}
			$encoderlog .= "<br><h1>res10 - Encodingname: HD: MP4box the mp4 file</h1><br>" ;
			foreach ($res11 as $outputline) {
				$encoderlog .= $outputline."<br>" ;
			}
			$outputpath = $rootpath."uploads/encodelogs/".$filename_without_ext.".html" ;

			$file = fopen($outputpath, "w") ;
			fwrite($file, $encoderlog) ;
			fclose($file) ;
		}
}

function makethumbs($basevid,$pathtothumb) {
	global $db, $ffmpegpath;
	$lw = getSetting("thumb_w1", $db) ;
	$lh = getSetting("thumb_h1", $db) ;

//how many thumbs we want
	$thumbsnumber = getSetting("thumbsnumber", $db);
//we dont want an end thumb so we take of 2 precent
	$vid_duration_sec = (getduration($basevid, 'sec') / 100) * 98;

	echo $vid_duration_sec.' total<br>';

//now we make the thumbs
	for ($b = 1; $b <= $thumbsnumber; $b++) {
		$thumbtime = round(($vid_duration_sec / $thumbsnumber) * $b);
		$imagepath = $pathtothumb.$b.".jpg" ;

		echo $thumbtime.' thumbtime<br>';
		echo $basevid.' thumbtime<br>';

		exec($ffmpegpath." -y -i ".$basevid." -f mjpeg -s ".$lw."x".$lh." -vframes 1 -ss ".$thumbtime." -an ".$imagepath." 2>&1", $res2, $err) ;


		if (filesize($imagepath) == "0") {
			unlink($imagepath) ;
		}
		if (file_exists($imagepath)) {
			chmod($imagepath, 0755);
		}
	}

}





//functions
function getvidinfo($file,$ffmpegpath) {
    $command = $ffmpegpath.' -i ' . escapeshellarg($file) . ' 2>&1';
    $dimensions = array();
    exec($command,$output,$status);
    if (!preg_match('/Stream #(?:[0-9\.]+)(?:.*)\: Video: (?P<videocodec>.*) (?P<videocodec2>.*) (?P<width>[0-9]*)x(?P<height>[0-9]*)/',implode('\n',$output),$matches)) {
        preg_match('/Could not find codec parameters \(Video: (?P<videocodec>.*) (?P<videocodec2>.*) (?P<width>[0-9]*)x(?P<height>[0-9]*)\)/',implode('\n',$output),$matches);
    }
    if(!empty($matches['width']) && !empty($matches['height']))
    {
        $dimensions['width'] = $matches['width'];
        $dimensions['height'] = $matches['height'];
        $dimensions['videocodec'] = $matches['videocodec'];
        $dimensions['videocodec2'] = $matches['videocodec2'];
    }
    return $dimensions;
}

function getduration($my_file2, $format) {
	if (file_exists($my_file2)) {
		$handle = fopen($my_file2, "r");
		$contents = fread($handle, filesize($my_file2));
		fclose($handle);$make_hexa = hexdec(bin2hex(substr($contents,strlen($contents)-3)));
			if (strlen($contents) > $make_hexa) {
				$pre_duration = hexdec(bin2hex(substr($contents,strlen($contents)-$make_hexa,3))) ;
				$post_duration = $pre_duration/1000 ;
				$returnsec = round($post_duration);
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
	switch($format) {
		case "sec":
			return $returnsec ;
		break;
		case "site":
			return $duration ;
		break;
	}
}
?>