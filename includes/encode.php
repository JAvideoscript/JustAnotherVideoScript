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
			$lw = getSetting("thumb_w1", $db) ;
			$lh = getSetting("thumb_h1", $db) ;
			$videoaspect = getSetting("videoaspect", $db) ;
			$getvinfo = getvidinfo($rootpath."uploads/encode/".$fileid,$ffmpegpath) ;
			if(empty($getvinfo)) {
				$noinfo = "false" ;
			} else {
				$noinfo = "true" ;
			}
			$orirand = mt_rand(5, 5000);

			rename($rootpath."uploads/encode/".$filename_without_ext.".".$ext, $rootpath."uploads/encode/origineel".$orirand.".".$ext) ;

			switch($ext){
				case "flv":
						if ($noinfo == "true") {
							if (($getvinfo['width'] >= "600") || ($getvinfo['height'] >= "480")) {
								exec($ffmpegpath." -i ".$rootpath."uploads/encode/origineel".$orirand.".".$ext." -ar ".$audiofrequency." -ab ".$audiobitrate."k -aspect ".$videoaspect." -b ".$videobitrate."k -r ".$framerate." -f flv -y -s ".$encodesize." -acodec libfaac -ac 1 ".$rootpath."uploads/encode/".$filename_without_ext.".flv 2>&1", $res1, $err) ;
							}
						}
						if (file_exists($rootpath.'uploads/encode/'.$filename_without_ext.'.flv')) {
							exec($ffmpegpath." -y -i ".$rootpath."uploads/encode/".$filename_without_ext.".flv -f mjpeg -s ".$lw."x".$lh." -vframes 1 -ss ".$thumbtime." -an ".$rootpath."uploads/thumbs/".$filename_without_ext.".jpg 2>&1", $res2, $err) ;
							chmod($rootpath."uploads/thumbs/".$filename_without_ext.".jpg", 0755) ;
							$duration = getduration($rootpath."uploads/encode/".$filename_without_ext.".".$ext) ;
							exec($flvtool2path." -U ".$rootpath."uploads/encode/".$filename_without_ext.".".$ext." 2>&1", $res3, $err) ;
						}
						if (file_exists($rootpath.'uploads/encode/origineel'.$orirand.'.flv')) {
							exec($ffmpegpath." -y -i ".$rootpath."uploads/encode/origineel".$orirand.".flv -f mjpeg -s ".$lw."x".$lh." -vframes 1 -ss ".$thumbtime." -an ".$rootpath."uploads/thumbs/".$filename_without_ext.".jpg 2>&1", $res2, $err) ;
							chmod($rootpath."uploads/thumbs/".$filename_without_ext.".jpg", 0755) ;
							$duration = getduration($rootpath."uploads/encode/origineel".$orirand.".".$ext) ;
							exec($flvtool2path." -U ".$rootpath."uploads/encode/origineel".$orirand.".".$ext." 2>&1", $res3, $err) ;
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
					if ($noinfo == "true") {
						if (($getvinfo['width'] <= "600") || ($getvinfo['height'] <= "480") && ($noinfo == "true")) {
							$encodesize = $getvinfo['width']."x".$getvinfo['height'] ;
						}
					}
						exec($ffmpegpath." -y -i ".$rootpath."uploads/encode/origineel".$orirand.".".$ext." -ab ".$audiobitrate."k -b ".$videobitrate."k -f flv -s ".$encodesize." -acodec libfaac -ac 1 ".$rootpath."uploads/encode/".$filename_without_ext.".flv 2>&1", $res4, $err) ;
						exec($ffmpegpath." -y -i ".$rootpath."uploads/encode/origineel".$orirand.".".$ext." -f mjpeg -s ".$lw."x".$lh." -vframes 1 -ss ".$thumbtime." -an ".$rootpath."uploads/thumbs/".$filename_without_ext.".jpg 2>&1", $res5, $err) ;

							if (filesize($rootpath.'uploads/thumbs/'.$filename_without_ext.'.jpg') == "0") {
								unlink($rootpath.'uploads/thumbs/'.$filename_without_ext.'.jpg') ;
							}
							if (file_exists($rootpath.'uploads/thumbs/'.$filename_without_ext.'.jpg')) {
								chmod($rootpath."uploads/thumbs/".$filename_without_ext.".jpg", 0755) ;
							}
					if (file_exists($rootpath.'uploads/encode/'.$filename_without_ext.'.flv')) {
						$duration = getduration($rootpath."uploads/encode/".$filename_without_ext.".flv") ;
						exec($flvtool2path." -U ".$rootpath."uploads/encode/".$filename_without_ext.".flv") ;
					}

				break;
			}
			mkdir($rootpath."uploads/vids/".$filename_without_ext, 0755);
			rename($rootpath."uploads/encode/".$filename_without_ext.".flv", $rootpath."uploads/vids/".$filename_without_ext."/".$filename_without_ext.".flv") ;

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
						rename($rootpath."uploads/encode/".$filename_without_ext.".mp4", $rootpath."uploads/vids/".$filename_without_ext."/".$filename_without_ext.".mp4") ;
					} else {
						rename($rootpath."uploads/encode/origineel".$orirand.".".$ext, $rootpath."uploads/vids/".$filename_without_ext."/".$filename_without_ext.".mp4") ;
					}

				}
				if (file_exists($rootpath."uploads/vids/".$filename_without_ext."/".$filename_without_ext.".mp4")) {
					$mp4box = getSetting("mp4box", $db) ;
					exec($mp4box." -inter 500 ".$rootpath."uploads/vids/".$filename_without_ext."/".$filename_without_ext.".mp4 2>&1", $res10, $err) ;
					$db->query("UPDATE `media` SET `hd` = '1' WHERE id = '".$value['id']."'") ;
				}

			}
			//remove origineel
			if (getSetting("removeorifile", $db) == '1') {
				unlink($rootpath."uploads/encode/origineel".$orirand.".".$ext) ;
			} else {
				rename($rootpath."uploads/encode/origineel".$orirand.".".$ext, $rootpath."uploads/encode/".$originalname) ;
			}

			if (getSetting("autoacceptvideo", $db) == '0') {
				$status = "false" ;
			} else {
				$status = "true" ;
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
?>