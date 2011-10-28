<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
include_once("adminfunctions.inc");

$db->query("SELECT * FROM sitead WHERE adname = 'ad1'") ;
$ads = $db->fetch() ;
$ad1 = $ads['adtext'] ;
$db->query("SELECT * FROM sitead WHERE adname = 'ad2'") ;
$ads = $db->fetch() ;
$ad2 = $ads['adtext'] ;
$db->query("SELECT * FROM sitead WHERE adname = 'ad3'") ;
$ads = $db->fetch() ;
$ad3 = $ads['adtext'] ;
$db->query("SELECT * FROM sitead WHERE adname = 'ad4'") ;
$ads = $db->fetch() ;
$ad4 = $ads['adtext'] ;
$db->query("SELECT * FROM sitead WHERE adname = 'ad5'") ;
$ads = $db->fetch() ;
$ad5 = $ads['adtext'] ;
$db->query("SELECT * FROM sitead WHERE adname = 'ad6'") ;
$ads = $db->fetch() ;
$ad6 = $ads['adtext'] ;
$db->query("SELECT * FROM sitead WHERE adname = 'ad7'") ;
$ads = $db->fetch() ;
$ad7 = $ads['adtext'] ;
$db->query("SELECT * FROM sitead WHERE adname = 'ad8'") ;
$ads = $db->fetch() ;
$ad8 = $ads['adtext'] ;
$db->query("SELECT * FROM sitead WHERE adname = 'ad9'") ;
$ads = $db->fetch() ;
$ad9 = $ads['adtext'] ;
$db->query("SELECT * FROM sitead WHERE adname = 'ad12'") ;
$ads = $db->fetch() ;
$ad12 = $ads['adtext'] ;
$db->query("SELECT * FROM sitead WHERE adname = 'ad13'") ;
$ads = $db->fetch() ;
$ad13 = $ads['adtext'] ;
$db->query("SELECT * FROM sitead WHERE adname = 'ad14'") ;
$ads = $db->fetch() ;
$ad14 = $ads['adtext'] ;
$db->query("SELECT * FROM sitead WHERE adname = 'ad15'") ;
$ads = $db->fetch() ;
$ad15 = $ads['adtext'] ;
$db->query("SELECT * FROM sitead WHERE adname = 'ad16'") ;
$ads = $db->fetch() ;
$ad16 = $ads['adtext'] ;

if (isset($_POST['submit'])) {
	$ad1 = $_POST['ad1'] ;
	$db->query("UPDATE `sitead` SET `adtext` = '".$ad1."' WHERE `adname` = 'ad1'") ;
	$ad2 = $_POST['ad2'] ;
	$db->query("UPDATE `sitead` SET `adtext` = '".$ad2."' WHERE `adname` = 'ad2'") ;
	$ad3 = $_POST['ad3'] ;
	$db->query("UPDATE `sitead` SET `adtext` = '".$ad3."' WHERE `adname` = 'ad3'") ;
	$ad4 = $_POST['ad4'] ;
	$db->query("UPDATE `sitead` SET `adtext` = '".$ad4."' WHERE `adname` = 'ad4'") ;
	$ad5 = $_POST['ad5'] ;
	$db->query("UPDATE `sitead` SET `adtext` = '".$ad5."' WHERE `adname` = 'ad5'") ;
	$ad6 = $_POST['ad6'] ;
	$db->query("UPDATE `sitead` SET `adtext` = '".$ad6."' WHERE `adname` = 'ad6'") ;
	$ad7 = $_POST['ad7'] ;
	$db->query("UPDATE `sitead` SET `adtext` = '".$ad7."' WHERE `adname` = 'ad7'") ;	
	$ad8 = $_POST['ad8'] ;
	$db->query("UPDATE `sitead` SET `adtext` = '".$ad8."' WHERE `adname` = 'ad8'") ;
	$ad9 = $_POST['ad9'] ;
	$db->query("UPDATE `sitead` SET `adtext` = '".$ad9."' WHERE `adname` = 'ad9'") ;	
	
	$ad12 = $_POST['ad12'] ;
	$db->query("UPDATE `sitead` SET `adtext` = '".$ad12."' WHERE `adname` = 'ad12'") ;
	$ad13 = $_POST['ad13'] ;
	$db->query("UPDATE `sitead` SET `adtext` = '".$ad13."' WHERE `adname` = 'ad13'") ;	
	$ad14 = $_POST['ad14'] ;
	$db->query("UPDATE `sitead` SET `adtext` = '".$ad14."' WHERE `adname` = 'ad14'") ;
	$ad15 = $_POST['ad15'] ;
	$db->query("UPDATE `sitead` SET `adtext` = '".$ad15."' WHERE `adname` = 'ad15'") ;	
	$ad16 = $_POST['ad16'] ;
	$db->query("UPDATE `sitead` SET `adtext` = '".$ad16."' WHERE `adname` = 'ad16'") ;	
}
?>
<fieldset>
	<ol>
	<form action="" method="post" enctype="multipart/form-data">
		<li>
				<h2>&nbsp;&nbsp;Advertising</h2>
		</li>
		<li>
				<label for="ad1">Home page under rotator size = 728x90</label>
				<textarea rows="5" name="ad1"><?=$ad1?></textarea>
		</li>
		<li>
				<label for="ad2">Home page above latest upload size = 728x90</label>
				<textarea rows="5" name="ad2"><?=$ad2?></textarea>
		</li>
		<li>
				<label for="ad3">Member page size = 300x250</label>
				<textarea rows="5" name="ad3"><?=$ad3?></textarea>
		</li>
		<li>
				<label for="ad4">Videos page above videos = 728x90</label>
				<textarea rows="5" name="ad4"><?=$ad4?></textarea>
		</li>
		<li>
				<label for="ad5">Videos page under videos = 728x90</label>
				<textarea rows="5" name="ad5"><?=$ad5?></textarea>
		</li>		
		<li>
				<label for="ad6">toprated page above videos = 728x90</label>
				<textarea rows="5" name="ad6"><?=$ad6?></textarea>
		</li>
		<li>
				<label for="ad7">toprated page under videos = 728x90</label>
				<textarea rows="5" name="ad7"><?=$ad7?></textarea>
		</li>			
		<li>
				<label for="ad8">Populair page above latest upload size = 728x90</label>
				<textarea rows="5" name="ad8"><?=$ad8?></textarea>
		</li>
		<li>
				<label for="ad9">Populair page under latest upload size = 728x90</label>
				<textarea rows="5" name="ad9"><?=$ad9?></textarea>
		</li>						
		<li>
				<label for="ad12">Above video player size = 468x60</label>
				<textarea rows="5" name="ad12"><?=$ad12?></textarea>
		</li>
		<li>
				<label for="ad13">Under video player size = 468x60</label>
				<textarea rows="5" name="ad13"><?=$ad13?></textarea>
		</li>					
		<li>
				<label for="ad14">Video page above related size = 300x250</label>
				<textarea rows="5" name="ad14"><?=$ad14?></textarea>
		</li>					
		<li>
				<label for="ad15">Video page above related 2 player size = 300x250</label>
				<textarea rows="5" name="ad15"><?=$ad15?></textarea>
		</li>			
		<li>
				<label for="ad16">Under the footer size = 728x90</label>
				<textarea rows="5" name="ad16"><?=$ad16?></textarea>
		</li>			
		<li>
				<label for="submit">&nbsp;</label>
				<input class="biggerbutton" type="submit" name="submit" value="Send" />
		</li>
	</form>
	</ol>
</fieldset>