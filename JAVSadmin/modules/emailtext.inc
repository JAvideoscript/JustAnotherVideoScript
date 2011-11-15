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
$db->query("SELECT * FROM email_text WHERE ident = 'email_activate'") ;
$mail = $db->fetch() ;
$emailactivate = $mail['phrase'] ;
$db->query("SELECT * FROM email_text WHERE ident = 'email_approved'") ;
$mail = $db->fetch() ;
$emailapproved = $mail['phrase'] ;

$db->query("SELECT * FROM email_text WHERE ident = 'email_approved_subscriber'") ;
$mail = $db->fetch() ;
$emailapprovedsub = $mail['phrase'] ;
$db->query("SELECT * FROM email_text WHERE ident = 'email_approved_friend'") ;
$mail = $db->fetch() ;
$emailapprovedfriend = $mail['phrase'] ;

$db->query("SELECT * FROM email_text WHERE ident = 'email_approved_admin'") ;
$mail = $db->fetch() ;
$emailapproveadmin = $mail['phrase'] ;


if (isset($_POST['submit'])) {
	//email settings
	$mail_video_admin = $_POST['mail_video_admin'] == 'on' ? 1 : 0 ;
	$db->query("UPDATE `setting` SET `value` = '".$mail_video_admin."' WHERE `setting` = 'mail_video_admin'") ;
	
	$mail_video_approved = $_POST['mail_video_approved'] == 'on' ? 1 : 0 ;
	$db->query("UPDATE `setting` SET `value` = '".$mail_video_approved."' WHERE `setting` = 'mail_video_approved'") ;
	$mail_video_rejected = $_POST['mail_video_rejected'] == 'on' ? 1 : 0 ;
	$db->query("UPDATE `setting` SET `value` = '".$mail_video_rejected."' WHERE `setting` = 'mail_video_rejected'") ;
	$mail_video_friends = $_POST['mail_video_friends'] == 'on' ? 1 : 0 ;
	$db->query("UPDATE `setting` SET `value` = '".$mail_video_friends."' WHERE `setting` = 'mail_video_friends'") ;
	$mail_friend_request = $_POST['mail_friend_request'] == 'on' ? 1 : 0 ;
	$db->query("UPDATE `setting` SET `value` = '".$mail_friend_request."' WHERE `setting` = 'mail_friend_request'") ;
	$mail_friend_pm = $_POST['mail_friend_pm'] == 'on' ? 1 : 0 ;
	$db->query("UPDATE `setting` SET `value` = '".$mail_friend_pm."' WHERE `setting` = 'mail_friend_pm'") ;
	$mail_friend_subscribed = $_POST['mail_friend_subscribed'] == 'on' ? 1 : 0 ;
	$db->query("UPDATE `setting` SET `value` = '".$mail_friend_subscribed."' WHERE `setting` = 'mail_friend_subscribed'") ;
	
	//email text
	$emailforgot = addslashes($_POST['emailforgot']) ;
	$db->query("UPDATE `email_text` SET `phrase` = '".$emailforgot."' WHERE `ident` = 'email_forgot'") ;
	$emailactivate = addslashes($_POST['emailactivate']) ;
	$db->query("UPDATE `email_text` SET `phrase` = '".$emailactivate."' WHERE `ident` = 'email_activate'") ;
	
	$emailapproveadmin = addslashes($_POST['emailapproveadmin']) ;
	$db->query("UPDATE `email_text` SET `phrase` = '".$emailapproveadmin."' WHERE `ident` = 'email_approved_admin'") ;
	
	$emailapproved = addslashes($_POST['emailapproved']) ;
	$db->query("UPDATE `email_text` SET `phrase` = '".$emailapproved."' WHERE `ident` = 'email_approved'") ;	
	
	$emailapprovedsub = addslashes($_POST['emailapprovedsub']) ;
	$db->query("UPDATE `email_text` SET `phrase` = '".$emailapprovedsub."' WHERE `ident` = 'email_approved_subscriber'") ;
	
	$emailapprovedfriend = addslashes($_POST['emailapprovedfriend']) ;
	$db->query("UPDATE `email_text` SET `phrase` = '".$emailapprovedfriend."' WHERE `ident` = 'email_approved_friend'") ;
	
	
}

$mail_video_admin = getSetting(mail_video_admin, $db) == 1 ? 'CHECKED' : '' ;
$mail_video_approved = getSetting(mail_video_approved, $db) == 1 ? 'CHECKED' : '' ;
$mail_video_rejected = getSetting(mail_video_rejected, $db) == 1 ? 'CHECKED' : '' ;
$mail_video_friends = getSetting(mail_video_friends, $db) == 1 ? 'CHECKED' : '' ;

$mail_friend_request = getSetting(mail_friend_request, $db) == 1 ? 'CHECKED' : '' ;
$mail_friend_pm = getSetting(mail_friend_pm, $db) == 1 ? 'CHECKED' : '' ;
$mail_friend_subscribed = getSetting(mail_friend_subscribed, $db) == 1 ? 'CHECKED' : '' ;



?>
<fieldset>
	<ol>
	<form action="" method="post" enctype="multipart/form-data">
	
		<li>
				<h2>&nbsp;&nbsp;Email Settings, when to send mail?</h2>
		</li>	
		<li>
				<label for="mail_video_admin">Admin gets mail when video is uploaded and needs approval:</label>
				<input type="checkbox" name="mail_video_admin" <?=$mail_video_admin?>>
		</li>
		<li>
				<label for="mail_video_approved">When user video is approved:</label>
				<input type="checkbox" name="mail_video_approved" <?=$mail_video_approved?>>
		</li>
		<li>
				<label for="mail_video_rejected">When user video is rejected:</label>
				<input type="checkbox" name="mail_video_rejected" <?=$mail_video_rejected?>>
		</li>
		<li>
				<label for="mail_video_friends">Send mail to all friends of uploader:</label>
				<input type="checkbox" name="mail_video_friends" <?=$mail_video_friends?>>
		</li>
		<li>
				<label for="mail_friend_subscribed">Send mail to subscribed users of the uploader</label>
				<input type="checkbox" name="mail_friend_subscribed" <?=$mail_friend_subscribed ?>>
		</li>			
		
		<li>
				<label for="mail_friend_request">When user gets friend request:</label>
				<input type="checkbox" name="mail_friend_request" <?=$mail_friend_request?>>
		</li>	
		<li>
				<label for="mail_friend_pm">When user gets private message:</label>
				<input type="checkbox" name="mail_friend_pm" <?=$mail_friend_pm?>>
		</li>		
	
	
	
	
	
		<li>
				<h2>&nbsp;&nbsp;Email Text</h2>
		</li>
		<li>
				<label>This words can be used and will be replaced when a mail is send</label>
				<label>[USERNAME], [PASSWORD], [POSTER], [MEDIALINK], [SITENAME], [SITEURL], [ACTLINK], [TITLE]</label>
		</li>	
		<li>
		
				<label for="emailapproveadmin">Admin new video email:</label>
				<textarea rows="5" name="emailapproveadmin"><?=$emailapproveadmin?></textarea>
		</li>	
		<li>
				<label for="emailapproved">Video approved email:</label>
				<textarea rows="5" name="emailapproved"><?=$emailapproved?></textarea>
		</li>		
		<li>
				<label for="emailapprovedsub">Video approved email to subscribers of uploader:</label>
				<textarea rows="5" name="emailapprovedsub"><?=$emailapprovedsub?></textarea>
		</li>	
		<li>
				<label for="emailapprovedfriend">Video approved email to friends of uploader:</label>
				<textarea rows="5" name="emailapprovedfriend"><?=$emailapprovedfriend?></textarea>
		</li>	


		
		<li>
				<label for="emailactivate">Activate email:</label>
				<textarea rows="5" name="emailactivate"><?=$emailactivate?></textarea>
		</li>
		<li>
				<label for="emailforgot">Forgot password email:</label>
				<textarea rows="5" name="emailforgot"><?=$emailforgot?></textarea>
		</li>
		<li>
				<label for="submit">&nbsp;</label>
				<input class="biggerbutton" type="submit" name="submit" value="Send" />
		</li>
	</form>
	</ol>
</fieldset>