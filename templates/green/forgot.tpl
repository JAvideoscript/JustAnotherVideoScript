<div id="forgotLogin">

<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
include_once 'includes/forgot.inc';
echo '<div id="home"><h2>Recover Password</h2>';


if(isset($haltMessage)) {
	echo $haltMessage;
} else {
	if(isset($message)){
		echo "<h4>$message</h4>";
	}
?>

<h4>Please enter the e-mail address which you registered with below and click send. You will receive an e-mail containing your logon information.</h4>
	<form method="post" action="">
		<div class="box">
			<label>
				<span>Email Adres</span>
				<input type="text" class="input_text" name="email" id="email" />
            		</label>
			<label>
				<input type="submit" name="submit" class="button" value="Submit" />	
		        </label>	
		</div>
	</form>


<?php
}
?>

</div></div>