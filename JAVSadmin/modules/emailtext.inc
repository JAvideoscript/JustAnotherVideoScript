<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
include_once("adminfunctions.inc");

$db->query("SELECT * FROM email_text WHERE ident = 'email_forgot'") ;
$mail = $db->fetch() ;
$emailforgot = $mail['phrase'] ;
$db->query("SELECT * FROM email_text WHERE ident = 'email_newmedia'") ;
$mail = $db->fetch() ;
$emailnew = $mail['phrase'] ;
$db->query("SELECT * FROM email_text WHERE ident = 'email_activate'") ;
$mail = $db->fetch() ;
$emailactivate = $mail['phrase'] ;
$db->query("SELECT * FROM email_text WHERE ident = 'email_upload'") ;
$mail = $db->fetch() ;
$emailupload = $mail['phrase'] ;
$db->query("SELECT * FROM email_text WHERE ident = 'admin_acc_act'") ;
$mail = $db->fetch() ;
$emailact = $mail['phrase'] ;

if (isset($_POST['submit'])) {
	$emailforgot = $_POST['emailforgot'] ;
	$db->query("UPDATE `email_text` SET `phrase` = '".$emailforgot."' WHERE `ident` = 'email_forgot'") ;
	$emailnew = $_POST['emailnew'] ;
	$db->query("UPDATE `email_text` SET `phrase` = '".$emailnew."' WHERE `ident` = 'email_newmedia'") ;
	$emailactivate = $_POST['emailactivate'] ;
	$db->query("UPDATE `email_text` SET `phrase` = '".$emailactivate."' WHERE `ident` = 'email_activate'") ;
	$emailupload = $_POST['emailupload'] ;
	$db->query("UPDATE `email_text` SET `phrase` = '".$emailupload."' WHERE `ident` = 'email_upload'") ;
	$emailact = $_POST['emailact'] ;
	$db->query("UPDATE `email_text` SET `phrase` = '".$emailact."' WHERE `ident` = 'admin_acc_act'") ;

}
?>
<fieldset>
	<ol>
	<form action="" method="post" enctype="multipart/form-data">
		<li>
				<h2>&nbsp;&nbsp;Advertising</h2>
		</li>
		<li>
				<label for="emailforgot">Forgot password email: [USERNAME], [PASSWORD], [SITENAME]</label>
				<textarea rows="5" name="emailforgot"><?=$emailforgot?></textarea>
		</li>
		<li>
				<label for="emailnew">New Media email: [POSTER], [MEDIALINK], [SITENAME]</label>
				<textarea rows="5" name="emailnew"><?=$emailnew?></textarea>
		</li>			
		<li>
				<label for="emailactivate">Activate email: [ACTLINK], [SITENAME]</label>
				<textarea rows="5" name="emailactivate"><?=$emailactivate?></textarea>
		</li>			
		<li>
				<label for="emailupload">Upload email: [MEDIALINK], [FILELINK], [MANAGELINK]</label>
				<textarea rows="5" name="emailupload"><?=$emailupload?></textarea>
		</li>			
		<li>
				<label for="emailact">Admin acc act email: [SITENAME], [USERNAME]</label>
				<textarea rows="5" name="emailact"><?=$emailact?></textarea>
		</li>							
		
		<li>
				<label for="submit">&nbsp;</label>
				<input class="biggerbutton" type="submit" name="submit" value="Send" />
		</li>
	</form>
	</ol>
</fieldset>