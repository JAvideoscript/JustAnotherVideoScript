<?php
session_start();
include_once("./modules/adminfunctions.inc");

	$url = trim(quote_smart($_GET['url'])) ;
	$title = trim(removespechar($_GET['title'])) ;
	$desc = quote_smart($_GET['desc']) ;
	$encodeset2 = str_replace("-", "", crc32(rand(100,999).time())) ;
	$tags = removespechar(str_replace(",", $encodeset2, $_GET['tags'])) ;
	$tags = str_replace($encodeset2, ",", $tags) ;
	$cater = quote_smart($_GET['cater']) ;


$db->query("SELECT * FROM media WHERE title = '".$title."'") ;
if ($db->numRows() >= 1) {
	echo 'dubtitle' ;
	$error = 'true' ;
}
if ($url == '') {
	echo 'nourl' ;
	$error = 'true' ;
}
if (($title == '') && ($error != 'true')) {
	echo 'notitle' ;
	$error = 'true' ;
}
if (($desc == '') && ($error != 'true')) {
	echo 'nodesc' ;
	$error = 'true' ;
}
if (($tags == '') && ($error != 'true')) {
	echo 'notags' ;
	$error = 'true' ;
}
if (($cater == '-----') && ($error != 'true')) {
	echo 'nocater' ;
	$error = 'true' ;
}

if ($error != 'true') {
	//check url valid and get id
		$youtubeid = explode("youtube.com/watch?v=", $url);
		$yid = $youtubeid[1] ;

	//download video with wget requires some weird coding but it works

	$execute = '/usr/bin/youtube-dl -o '.$rootpath.'uploads/newuploads/'.$yid.'.ext -w --no-part http://www.youtube.com/watch?v='.$yid ;
	exec($execute);




	if (file_exists($rootpath.'uploads/newuploads/'.$yid.'.ext')) {
			$ffmpegpath = getSetting("ffmpegpath", $db) ;
			$getvinfo = getvidinfo($rootpath."uploads/newuploads/".$yid.".ext",$ffmpegpath) ;
			$videoext = $getvinfo['ext'] ;

			if ($videoext == "flv,") {
				$ext = 'flv' ;
			} else {
				$ext = 'mp4' ;
			}
	} else {
			echo 'filenot';
	}



		$encodeset = str_replace("-", "", crc32(rand(100,999).time())) ;
		$fileid = $encodeset.".".$ext ;
		$path2file = $rootpath.'uploads/newuploads/'.$yid.'.ext' ;
		$newpath = $rootpath."uploads/encode/".$fileid ;

	//standard vars
		$added = time() ;
		$status = "encode" ;
		$poster = "importer" ;
	//move to encode folder
		rename($path2file, $newpath) ;
	//put in DB
		if (file_exists($newpath)) {
			$sql = "INSERT INTO `media` (title, category, description, tags, fileid, poster, added, status, mediatype) VALUES ('".$title."', '".$cater."', '".$desc."', '".$tags."', '".$fileid."', '".$poster."', '".$added."', '".$status."', 'video')" ;
			$db->query($sql) ;
			if (getSetting("directencode", $db) == '1') {
					$cronpass = getSetting("passcron", $db) ;
					$curlpath = getSetting("curlpath", $db) ;
					$cmd = $curlpath. " " .$sitepath. "includes/encode.php?cronpass=" .$cronpass ;
					exec($cmd. ">/dev/null &");
			}


		echo "File added to encoding progress..." ;

		}


}

function getvidinfo($file,$ffmpegpath) {
    $command = $ffmpegpath.' -i ' . escapeshellarg($file) . ' 2>&1';
    $dimensions = array();
    exec($command,$output,$status);

    if (!preg_match('/Input #0, (?P<ext>.*) from/',implode('\n',$output),$matches)) {
    	preg_match('/Input #0, (?P<ext>.*) from/',implode('\n',$output),$matches) ;
    }

    if(!empty($matches['ext'])) {
        $dimensions['ext'] = $matches['ext'];
    }
    return $dimensions;
}
?>
