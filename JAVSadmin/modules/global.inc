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
		$sitename = $_POST['sitename'] ;
		$db->query("UPDATE `setting` SET `value` = '".$sitename."' WHERE `setting` = 'sitename'") ;
		$sitetitle = $_POST['sitetitle'] ;
		$db->query("UPDATE `setting` SET `value` = '".$sitetitle."' WHERE `setting` = 'sitetitle'") ;
		$sitefolder = $_POST['sitefolder'] ;
		$db->query("UPDATE `setting` SET `value` = '".$sitefolder."' WHERE `setting` = 'sitefolder'") ;
		$showdesc = $_POST['showdesc'] == 'on' ? 1 : 0 ;
		$db->query("UPDATE `setting` SET `value` = '".$showdesc."' WHERE `setting` = 'showdesc'") ;
		$contact_email = $_POST['contact_email'] ;
		$db->query("UPDATE `setting` SET `value` = '".$contact_email."' WHERE `setting` = 'contact_email'") ;
		$default_from = $_POST['default_from'] ;
		$db->query("UPDATE `setting` SET `value` = '".$default_from."' WHERE `setting` = 'default_from'") ;		
		$accountpageon = $_POST['accountpageon'] == 'on' ? 1 : 0 ;
		$db->query("UPDATE `setting` SET `value` = '".$accountpageon."' WHERE `setting` = 'accountpageon'") ;
		$activation = $_POST['activation'] == 'on' ? 1 : 0 ;
		$db->query("UPDATE `setting` SET `value` = '".$activation."' WHERE `setting` = 'activation'") ;		
		$titledisplaylength = $_POST['titledisplaylength'] ;
		$db->query("UPDATE `setting` SET `value` = '".$titledisplaylength."' WHERE `setting` = 'titledisplaylength'") ;
		$sitetemplate = $_POST['sitetemplate'] ;
		$db->query("UPDATE `setting` SET `value` = '".$sitetemplate."' WHERE `setting` = 'sitetemplate'") ;	
		$showsocial = $_POST['showsocial'] == 'on' ? 1 : 0 ;
		$db->query("UPDATE `setting` SET `value` = '".$showsocial."' WHERE `setting` = 'showsocial'") ;	
		
		$showdmca = $_POST['showdmca'] == 'on' ? 1 : 0 ;
		$db->query("UPDATE `setting` SET `value` = '".$showdmca."' WHERE `setting` = 'showdmca'") ;	
		$show2257 = $_POST['show2257'] == 'on' ? 1 : 0 ;
		$db->query("UPDATE `setting` SET `value` = '".$show2257."' WHERE `setting` = 'show2257'") ;	
		echo "Everything has been updated now." ;

	}
	$sitename = getSetting(sitename, $db) ;
	$sitetitle = getSetting(sitetitle, $db) ;
	$sitefolder = getSetting(sitefolder, $db) ;
	$showdesc = getSetting(showdesc, $db) == 1 ? 'CHECKED' : '' ;
	$accountpageon = getSetting(accountpageon, $db) == 1 ? 'CHECKED' : '' ;
	$activation = getSetting(activation, $db) == 1 ? 'CHECKED' : '' ;
	$contact_email = getSetting(contact_email, $db) ;
	$default_from = getSetting(default_from, $db) ;
	$titledisplaylength = getSetting(titledisplaylength, $db) ;
	$sitetemplate = getSetting(sitetemplate, $db) ;
	$showdmca = getSetting(showdmca, $db) == 1 ? 'CHECKED' : '' ;
	$show2257 = getSetting(show2257, $db) == 1 ? 'CHECKED' : '' ;
	$showsocial = getSetting(showsocial, $db) == 1 ? 'CHECKED' : '' ;
?>
<fieldset>
	<ol>
	<form action="" method="post" enctype="multipart/form-data">
		<li>
				<h2>&nbsp;&nbsp;Global</h2>
		</li>
		<li>
				<label for="sitename">Sitename:</label>
				<input type="text" size="100" name="sitename" value="<?=$sitename?>">
		</li>
		<li>
				<label for="sitetitle">Site title:</label>
				<input type="text" size="100" name="sitetitle" value="<?=$sitetitle?>">
		</li>
		<li>
				<label for="sitefolder">Sitefolder:</label>
				<input type="text" size="100" name="sitefolder" value="<?=$sitefolder?>">
		</li>
		<li>
				<label for="sitetemplate">Template:</label>
				<select name="sitetemplate" class="select">
					<? 
						foreach (dirList() as $template) {
							echo "<option" ;
							if ($template == $sitetemplate)
									echo " selected" ;
							echo ">".$template."</option>" ;
						}
					?>
				</select>
		</li>
		<li>
				<label for="contact_email">Contact email:</label>
				<input type="text" size="50" name="contact_email" value="<?=$contact_email?>">
		</li>
		<li>
				<label for="default_from">From name for email:</label>
				<input type="text" size="50" name="default_from" value="<?=$default_from?>">
		</li>
		<li>
				<label for="titledisplaylength">Max title Length:</label>
				<input type="text" size="5" name="titledisplaylength" value="<?=$titledisplaylength?>">
		</li>	
		<li>
				<label for="accountpageon">Go to account page after login:</label>
				<input type="checkbox" name="accountpageon" <?=$accountpageon?>>
		</li>
		<li>
				<label for="activation">New users need to verify email:</label>
				<input type="checkbox" name="activation" <?=$activation?>>
		</li>
		<li>
				<label for="showdesc">Show description on above video:</label>
				<input type="checkbox" name="showdesc" <?=$showdesc?>>
		</li>
		<li>
				<label for="showsocial">Show social icons under video:</label>
				<input type="checkbox" name="showsocial" <?=$showsocial?>>
		</li>
		<li>
				<label for="showdmca">Show DMCA in footer:</label>
				<input type="checkbox" name="showdmca" <?=$showdmca?>>
		</li>
		<li>
				<label for="show2257">Show 2257 in footer:</label>
				<input type="checkbox" name="show2257" <?=$show2257?>>
		</li>
		<li>
				<label for="submit">&nbsp;</label>
				<input class="biggerbutton" type="submit" name="submit" value="Change" />
		</li>
	</form>
	</ol>
</fieldset>
		