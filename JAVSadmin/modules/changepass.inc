<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
include_once("adminfunctions.inc");

if (is_writable('modules/settings.inc')) {
	$writeablesettings = "<img src='./images/green.png' border=0>" ;
	$showchangeform = '1';
} else {
	$writeablesettings = "<img src='./images/red.png' border=0>" ;
}

	if (isset($_POST['submit'])) { 
		//$_POST['Old_pass']  $_POST['new_pass'] $_POST['new_pass2']
		if (md5($_POST['Old_pass']) == $pass) {
			if ($_POST['new_pass'] == $_POST['new_pass2']) {
				$passc = strlen($_POST['new_pass']) ;
				if ($passc <= '6') {
					echo "Password need to be longer then 6 characters";
				} else {
					$newpass = $_POST['new_pass'] ;
					$settingsadminfile = '<?php
						$db_host = "' . $db_host . '";
						$db_user = "' . $db_user . '";
						$db_password = "' . $db_password. '";
						$db_database = "' . $db_database . '";
						$username = "' . $username . '";
						$pass = "' . md5($newpass) . '";
						?>';
					$fp = fopen('modules/settings.inc', 'r+');
					fwrite($fp, $settingsadminfile);
					fclose($fp);
					echo "Password is changed" ;
				}
			} else {
				echo "New passwords did not match, try again" ;		
			}
		
		} else {
			echo "Old password not correct, please try again." ;
		}

		
	}

?>
<fieldset>
	<ol>
	<form action="" method="post" enctype="multipart/form-data">
		<li>
				<h2>&nbsp;&nbsp;Change admin password</h2>
		</li>
		<li>
				<h4>&nbsp;&nbsp;Make sure to set settings.inc in folder /modules/ to permission 777 and after pass change set it back to 644.</h4>
		</li>
		<li>
			<label>Folder /modules/settings.inc:</label>
			<label><?=$writeablesettings?></label>
		</li>
		
		
		<?php
		if ($showchangeform == '1') {
		?>
		
		<li>
				<label for="Old_pass">Old Password:</label>
				<input type="password" size="25" name="Old_pass">
		</li>
		<li>
				<label for="new_pass">New Password:</label>
				<input type="password" size="25" name="new_pass">
		</li>			
		<li>
				<label for="new_pass2">New Password:</label>
				<input type="password" size="25" name="new_pass2">
		</li>			
		
		<li>
				<label for="submit">&nbsp;</label>
				<input class="biggerbutton" type="submit" name="submit" value="Change" />
		</li>
		<?php } ?>
	</form>
	</ol>
</fieldset>