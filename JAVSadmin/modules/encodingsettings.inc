<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
include_once("adminfunctions.inc");

	if (isset($_POST['submit'])) { 
		$audiobitrate = $_POST['audiobitrate'] ;
		$db->query("UPDATE `setting` SET `value` = '".$audiobitrate."' WHERE `setting` = 'audiobitrate'") ;
		$audiofrequency = $_POST['audiofrequency'] ;
		$db->query("UPDATE `setting` SET `value` = '".$audiofrequency."' WHERE `setting` = 'audiofrequency'") ;
		$thumb_h1 = $_POST['thumb_h1'] ;
		$db->query("UPDATE `setting` SET `value` = '".$thumb_h1."' WHERE `setting` = 'thumb_h1'") ;		
		$thumb_w1 = $_POST['thumb_w1'] ;
		$db->query("UPDATE `setting` SET `value` = '".$thumb_w1."' WHERE `setting` = 'thumb_w1'") ;
		$curlpath = $_POST['curlpath'] ;
		$db->query("UPDATE `setting` SET `value` = '".$curlpath."' WHERE `setting` = 'curlpath'") ;
		$ffmpegpath = $_POST['ffmpegpath'] ;
		$db->query("UPDATE `setting` SET `value` = '".$ffmpegpath."' WHERE `setting` = 'ffmpegpath'") ;
		$flvtool2path = $_POST['flvtool2path'] ;
		$db->query("UPDATE `setting` SET `value` = '".$flvtool2path."' WHERE `setting` = 'flvtool2path'") ;
		$framerate = $_POST['framerate'] ;
		$db->query("UPDATE `setting` SET `value` = '".$framerate."' WHERE `setting` = 'framerate'") ;
		$default_thumbtime = $_POST['default_thumbtime'] ;
		$db->query("UPDATE `setting` SET `value` = '".$default_thumbtime."' WHERE `setting` = 'default_thumbtime'") ;		
		$directencode = $_POST['directencode'] == 'on' ? 1 : 0 ;
		$db->query("UPDATE `setting` SET `value` = '".$directencode."' WHERE `setting` = 'directencode'") ;	
		$encodesize = $_POST['encodesize'] ;	
		$db->query("UPDATE `setting` SET `value` = '".$encodesize."' WHERE `setting` = 'encodesize'") ;			
		$passcron = $_POST['passcron'] ;
		$db->query("UPDATE `setting` SET `value` = '".$passcron."' WHERE `setting` = 'passcron'") ;	
		$removeorifile = $_POST['removeorifile'] == 'on' ? 1 : 0 ;
		$db->query("UPDATE `setting` SET `value` = '".$removeorifile."' WHERE `setting` = 'removeorifile'") ;
		
		$keepencodelog = $_POST['keepencodelog'] == 'on' ? 1 : 0 ;
		$db->query("UPDATE `setting` SET `value` = '".$keepencodelog."' WHERE `setting` = 'keepencodelog'") ;
		
		$videoaspect = $_POST['videoaspect'] ;
		$db->query("UPDATE `setting` SET `value` = '".$videoaspect."' WHERE `setting` = 'videoaspect'") ;
		$videobitrate = $_POST['videobitrate'] ;
		$db->query("UPDATE `setting` SET `value` = '".$videobitrate."' WHERE `setting` = 'videobitrate'") ;	
		echo "Everything has been updated now." ;

	}
	$audiobitrate = getSetting(audiobitrate, $db) ;
	$audiofrequency = getSetting(audiofrequency, $db) ;
	$thumb_h1 = getSetting(thumb_h1, $db) ;
	$thumb_w1 = getSetting(thumb_w1, $db) ;
	$curlpath = getSetting(curlpath, $db) ;
	$ffmpegpath = getSetting(ffmpegpath, $db) ;
	$flvtool2path = getSetting(flvtool2path, $db) ;
	$default_thumbtime = getSetting(default_thumbtime, $db) ;
	$directencode = getSetting(directencode, $db) == 1 ? 'CHECKED' : '' ;
	$removeorifile = getSetting(removeorifile, $db) == 1 ? 'CHECKED' : '' ;
	$keepencodelog = getSetting(keepencodelog, $db) == 1 ? 'CHECKED' : '' ;
	$encodesize = getSetting(encodesize, $db) ;
	$framerate = getSetting(framerate, $db) ;
	$passcron = getSetting(passcron, $db) ;
	$sitefolder = getsetting("sitefolder", $db) ;
	$sitepath = "http://".$_SERVER['SERVER_NAME'].$sitefolder ;
	$croncommand = $curlpath. ' ' .$sitepath.'includes/encode.php?cronpass='.$passcron ;
	$videoaspect = getSetting(videoaspect, $db) ;
	$videobitrate = getSetting(videobitrate, $db) ;
?>
<fieldset>
	<ol>
	<form action="" method="post" enctype="multipart/form-data">
		<li>
				<h2>&nbsp;&nbsp;Encoding Settings</h2>
		</li>
		<li>
				<label for="directencode">Direct encode after upload:</label>
				<input type="checkbox" name="directencode" <?=$directencode?>>
		</li>
		<li>
				<label for="removeorifile">Remove original uploaded file after encoding:</label>
				<input type="checkbox" name="removeorifile" <?=$removeorifile?>>
		</li>
		<li>
				<label for="keepencodelog">Make encoding logs:</label>
				<input type="checkbox" name="keepencodelog" <?=$keepencodelog?>>
		</li>
		<li>
				<label for="encodesize">Encoding size:</label>
				<input type="text" size="10" name="encodesize" value="<?=$encodesize?>">
		</li>
		<li>
				<label for="framerate">Frame rate:</label>
				<input type="text" size="10" name="framerate" value="<?=$framerate?>">
		</li>
		<li>
				<label for="videoaspect">Video aspect:</label>
				<input type="text" size="10" name="videoaspect" value="<?=$videoaspect?>">
		</li>
		<li>
				<label for="videobitrate">Video bitrate:</label>
				<input type="text" size="10" name="videobitrate" value="<?=$videobitrate?>">
		</li>
		<li>
				<label for="audiobitrate">Audiobitrate:</label>
				<input type="text" size="10" name="audiobitrate" value="<?=$audiobitrate?>">
		</li>
		<li>
				<label for="audiofrequency">Audiofrequency:</label>
				<input type="text" size="10" name="audiofrequency" value="<?=$audiofrequency?>">
		</li>
		<li>
				<label for="default_thumbtime">Time in seconds when thumb is made:</label>
				<input type="text" size="10" name="default_thumbtime" value="<?=$default_thumbtime?>">
		</li>
		<li>
				<label for="thumb_h1">Thumb height:</label>
				<input type="text" size="10" name="thumb_h1" value="<?=$thumb_h1?>">
		</li>
		<li>
				<label for="thumb_w1">Thumb width:</label>
				<input type="text" size="10" name="thumb_w1" value="<?=$thumb_w1?>">
		</li>				
		<li>
				<label for="curlpath">Curl path:</label>
				<input type="text" size="50" name="curlpath" value="<?=$curlpath?>">
		</li>	
		<li>
				<label for="ffmpegpath">FFmpeg path:</label>
				<input type="text" size="50" name="ffmpegpath" value="<?=$ffmpegpath?>">
		</li>	
		<li>
				<label for="flvtool2path">FLVtools2 path:</label>
				<input type="text" size="50" name="flvtool2path" value="<?=$flvtool2path?>">
		</li>			
		<li>
				<label for="passcron">Cron password:</label>
				<input type="text" size="50" name="passcron" value="<?=$passcron?>">
		</li>	
		<li>
				<label for="croncommand">Cronjob command for encoding</label>
				<input size=100 value="<?= $croncommand?>" onClick="this.select()" />
		</li>
		
		
		
		
		
		<li>
				<label for="submit">&nbsp;</label>
				<input class="biggerbutton" type="submit" name="submit" value="Change" />
		</li>
	</form>
	</ol>
</fieldset>
