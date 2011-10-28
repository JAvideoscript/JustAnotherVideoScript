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
		$halt = "no" ;
		if (($_POST["subject"] == "") || ($_POST["message"] == "")) {
			$halt = "yes" ;
			echo "Subject and/or Message not set" ;
		}
	
		
		if ($halt == "no") {
			switch($_POST["sendto"]) {
				case'activated':
					$db->query("SELECT email FROM member WHERE activationkey = '0'") ;	
				break;
				case'all':
					$db->query("SELECT email FROM member") ;	
				break;		
				case'noneact':
					$db->query("SELECT email FROM member WHERE activationkey <> '0'") ;	
				break;			
			}
			$mailadresses = array() ;	
			while ($res = $db->fetch()) {
				array_push($mailadresses, $res['email']) ;
			}
			$listadres = implode(',', $mailadresses) ;
			$mailheaders = "From:  <".getSetting("contact_email", $db).">\r\nBcc: {$listadres}"."Reply-To: ".getSetting("contact_email", $db)."\r\n"."X-Mailer: PHP/".phpversion() ;
			mail(getSetting("contact_email", $db), $_POST["subject"], $_POST["message"], $mailheaders) ;
			$x = count($mailadresses) ;
			
			echo "Mail Have been sent to $x of people" ;
		}
	}
?> 

<fieldset>
	<ol>
	<form action="" method="post" enctype="multipart/form-data">
		<li>
				<h2>&nbsp;&nbsp;Email every user</h2>
		</li>
		<li>
				<label for="sendto">Send to:</label>
				<select name="sendto" class="select">
					<option value="activated" selected>To all activated users</option>
					<option value="all">To all users</option>
					<option value="noneact" selected>To not activated users</option>
				</select>
		</li>
		<li>
				<label for="subject">Subject:</label>
				<input type="text" size="50" name="subject" value="<?= $_POST["subject"]?>">
		</li>
		<li>
				<label for="message">Message:</label>
				<textarea rows="10" name="message"><?= $_POST["message"]?></textarea>
		</li>
		<li>
				<label for="submit">&nbsp;</label>
				<input class="biggerbutton" type="submit" name="submit" value="Send" />
		</li>
	</form>
	</ol>
</fieldset>