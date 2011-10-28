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
		$showallvideos = $_POST['showallvideos'] == 'on' ? 1 : 0 ;
		$db->query("UPDATE `setting` SET `value` = '".$showallvideos."' WHERE `setting` = 'showallvideos'") ;
		$showtoprated = $_POST['showtoprated'] == 'on' ? 1 : 0 ;
		$db->query("UPDATE `setting` SET `value` = '".$showtoprated."' WHERE `setting` = 'showtoprated'") ;		
		$showmostviewed = $_POST['showmostviewed'] == 'on' ? 1 : 0 ;
		$db->query("UPDATE `setting` SET `value` = '".$showmostviewed."' WHERE `setting` = 'showmostviewed'") ;
		$showcategorie = $_POST['showcategorie'] == 'on' ? 1 : 0 ;
		$db->query("UPDATE `setting` SET `value` = '".$showcategorie."' WHERE `setting` = 'showcategorie'") ;			
		$showmembers = $_POST['showmembers'] == 'on' ? 1 : 0 ;
		$db->query("UPDATE `setting` SET `value` = '".$showupload."' WHERE `setting` = 'showupload'") ;		
		$showfrontpage = $_POST['showfrontpage'] ;
		$db->query("UPDATE `setting` SET `value` = '".$showfrontpage."' WHERE `setting` = 'showfrontpage'") ;	
		$showupload = $_POST['showupload'] == 'on' ? 1 : 0 ;
		$db->query("UPDATE `setting` SET `value` = '".$showupload."' WHERE `setting` = 'showupload'") ;
		$showembed = $_POST['showembed'] == 'on' ? 1 : 0 ;
		$db->query("UPDATE `setting` SET `value` = '".$showembed."' WHERE `setting` = 'showembed'") ;	

		$enablelogin = $_POST['enablelogin'] == 'on' ? 1 : 0 ;
		$db->query("UPDATE `setting` SET `value` = '".$enablelogin."' WHERE `setting` = 'enablelogin'") ;
		
		if (getSetting(enablelogin, $db) == '0') {
			$db->query("UPDATE `setting` SET `value` = '0' WHERE `setting` = 'showembed'") ;	
			$db->query("UPDATE `setting` SET `value` = '0' WHERE `setting` = 'showupload'") ;
		
		}
		
		if ((getSetting(showallvideos, $db) == '0') && (getSetting(showfrontpage, $db) == 'allvideos')) {
			$db->query("UPDATE `setting` SET `value` = 'home' WHERE `setting` = 'showfrontpage'") ;	
		}
		if ((getSetting(showtoprated, $db) == '0') && (getSetting(showfrontpage, $db) == 'toprated')) {
			$db->query("UPDATE `setting` SET `value` = 'home' WHERE `setting` = 'showfrontpage'") ;	
		}		
		if ((getSetting(showmostviewed, $db) == '0') && (getSetting(showfrontpage, $db) == 'mostviewed')) {
			$db->query("UPDATE `setting` SET `value` = 'home' WHERE `setting` = 'showfrontpage'") ;	
		}			
		if ((getSetting(showcategorie, $db) == '0') && (getSetting(showfrontpage, $db) == 'catlist')) {
			$db->query("UPDATE `setting` SET `value` = 'home' WHERE `setting` = 'showfrontpage'") ;	
		}
		if ((getSetting(showupload, $db) == '0') && (getSetting(showfrontpage, $db) == 'upload')) {
			$db->query("UPDATE `setting` SET `value` = 'home' WHERE `setting` = 'showfrontpage'") ;	
		}
		echo "Everything has been updated now." ;

	}

	$showfrontpage = getSetting(showfrontpage, $db) ;
	$showallvideos = getSetting(showallvideos, $db) == 1 ? 'CHECKED' : '' ;
	$showtoprated = getSetting(showtoprated, $db) == 1 ? 'CHECKED' : '' ;
	$showmostviewed = getSetting(showmostviewed, $db) == 1 ? 'CHECKED' : '' ;
	$showcategorie = getSetting(showcategorie, $db) == 1 ? 'CHECKED' : '' ;
	$showupload = getSetting(showupload, $db) == 1 ? 'CHECKED' : '' ;
	$showembed = getSetting(showembed, $db) == 1 ? 'CHECKED' : '' ;
	$enablelogin = getSetting(enablelogin, $db) == 1 ? 'CHECKED' : '' ;
?>




<fieldset>
	<ol>
	<form action="" method="post" enctype="multipart/form-data">
		<li>
				<h2>&nbsp;&nbsp;Menu Settings</h2>
		</li>
		<li>
				<h4>You can turn pages off in menu and on the actual page. Turning off members turns off upload.</h4>
		</li>
		<li>
				<label for="showfrontpage">Front page:</label>
				<select name="showfrontpage" class="select">
					<? 
						foreach (homelist() as $frontlist) {
							echo "<option" ;
							if ($frontlist == $showfrontpage)
									echo " selected" ;
							echo ">".$frontlist."</option>" ;
						}
					?>
				</select>
		</li>
		<li>
				<label for="showallvideos">Show videos:</label>
				<input type="checkbox" name="showallvideos" <?=$showallvideos?>>
		</li>
		<li>
				<label for="showtoprated">Show Top Rated:</label>
				<input type="checkbox" name="showtoprated" <?=$showtoprated?>>
		</li>		
		<li>
				<label for="showmostviewed">Show Most viewed:</label>
				<input type="checkbox" name="showmostviewed" <?=$showmostviewed?>>
		</li>		
		<li>
				<label for="showcategorie">Show Categories:</label>
				<input type="checkbox" name="showcategorie" <?=$showcategorie?>>
		</li>		
		<li>
				<label for="showupload">Show Uploads:</label>
				<input type="checkbox" name="showupload" <?=$showupload?>>
		</li>		
		<li>
				<label for="showembed">Show Embed:</label>
				<input type="checkbox" name="showembed" <?=$showembed?>>
		</li>	
		<li>
				<label for="enablelogin ">enable all login options:</label>
				<input type="checkbox" name="enablelogin" <?=$enablelogin?>>
		</li>	
		<li>
				<label for="submit">&nbsp;</label>
				<input class="biggerbutton" type="submit" name="submit" value="Change" />
		</li>
	</form>
	</ol>
</fieldset>
