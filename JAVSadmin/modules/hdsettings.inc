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
		$hdvideo = $_POST['hdvideo'] == 'on' ? 1 : 0 ;
		$db->query("UPDATE `setting` SET `value` = '".$hdvideo."' WHERE `setting` = 'hdvideo'") ;
		$maxresolution_h = $_POST['maxresolution_h'] ;
		$db->query("UPDATE `setting` SET `value` = '".$maxresolution_h."' WHERE `setting` = 'maxresolution_h'") ;
		$maxresolution_w = $_POST['maxresolution_w'] ;
		$db->query("UPDATE `setting` SET `value` = '".$maxresolution_w."' WHERE `setting` = 'maxresolution_w'") ;
		$mp4box = $_POST['mp4box'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mp4box."' WHERE `setting` = 'mp4box'") ;
		$downhdmember = $_POST['downhdmember'] == 'on' ? 1 : 0 ;
		$db->query("UPDATE `setting` SET `value` = '".$downhdmember."' WHERE `setting` = 'downhdmember'") ;	
		$downhdguest = $_POST['downhdguest'] == 'on' ? 1 : 0 ;
		$db->query("UPDATE `setting` SET `value` = '".$downhdguest."' WHERE `setting` = 'downhdguest'") ;	
		echo "Everything has been updated now." ;
		
	}
	
	$hdvideo = getSetting(hdvideo, $db) == 1 ? 'CHECKED' : '' ;
	$maxresolution_h = getSetting(maxresolution_h, $db) ;
	$maxresolution_w = getSetting(maxresolution_w, $db) ;
	$mp4box = getSetting(mp4box, $db) ;
	$downhdmember = getSetting(downhdmember, $db) == 1 ? 'CHECKED' : '' ;
	$downhdguest = getSetting(downhdguest, $db) == 1 ? 'CHECKED' : '' ;
	
?>
<fieldset>
	<ol>
	<form action="" method="post" enctype="multipart/form-data">
		<li>
				<h2>&nbsp;&nbsp;Hd settings</h2>
		</li>
		<li>
				<label for="hdvideo">Enable HD video:</label>
				<input type="checkbox" name="hdvideo" <?=$hdvideo?>>
		</li>
		<li>
				<label for="mp4box">mp4box path:</label>
				<input type="text" size="50" name="mp4box" value="<?=$mp4box?>">
		</li>
		<li>
				<label for="downhdguest">Guest can download HD videos(mp4):</label>
				<input type="checkbox" name="downhdguest" <?=$downhdguest?>>
		</li>	
		<li>
				<label for="downhdmember">Members can download HD videos(flv):</label>
				<input type="checkbox" name="downhdmember" <?=$downhdmember?>>
		</li>			
		
		
		<li>
				<label for="maxresolution_h">Max Resolution height:</label>
				<input type="text" size="10" name="maxresolution_h" value="<?=$maxresolution_h?>">
		</li>	
		<li>
				<label for="maxresolution_w">Max Resolution width:</label>
				<input type="text" size="10" name="maxresolution_w" value="<?=$maxresolution_w?>">
		</li>	
		
		
		
		
		
		<li>
				<label for="submit">&nbsp;</label>
				<input class="biggerbutton" type="submit" name="submit" value="Change" />
		</li>
	</form>
	</ol>
</fieldset>