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
		$mobilevideo = $_POST['mobilevideo'] == 'on' ? 1 : 0 ;
		$db->query("UPDATE `setting` SET `value` = '".$mobilevideo."' WHERE `setting` = 'mobilevideo'") ;
		$mobile_encodesize_width = $_POST['mobile_encodesize_width'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mobile_encodesize_width."' WHERE `setting` = 'mobile_encodesize_width'") ;
		$mobile_encodesize_height = $_POST['mobile_encodesize_height'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mobile_encodesize_height."' WHERE `setting` = 'mobile_encodesize_height'") ;
		echo "Everything has been updated now." ;
		
	}
	$mobilevideo = getSetting(mobilevideo, $db) == 1 ? 'CHECKED' : '' ;
	$mobile_encodesize_width = getSetting(mobile_encodesize_width, $db) ;
	$mobile_encodesize_height = getSetting(mobile_encodesize_height, $db) ;
?>
<fieldset>
	<ol>
	<form action="" method="post" enctype="multipart/form-data">
		<li>
				<h2>&nbsp;&nbsp;Mobile settings</h2>
		</li>
		<li>
				<label for="mobilevideo">Enable Mobile video:</label>
				<input type="checkbox" name="mobilevideo" <?=$mobilevideo?>>
		</li>
		<li>
				<label for="mobile_encodesize_height">Enconding Height:</label>
				<input type="text" size="5" name="mobile_encodesize_height" value="<?=$mobile_encodesize_height?>">
		</li>	
		<li>
				<label for="mobile_encodesize_width">Enconding Width:</label>
				<input type="text" size="5" name="mobile_encodesize_width" value="<?=$mobile_encodesize_width?>">
		</li>			
		
		
		<li>
				<label for="submit">&nbsp;</label>
				<input class="biggerbutton" type="submit" name="submit" value="Change" />
		</li>
	</form>
	</ol>
</fieldset>