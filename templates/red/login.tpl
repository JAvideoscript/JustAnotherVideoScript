<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
if (getSetting("enablelogin", $db) == '0') {
	echo '<div id="home"><h2>Login is disabled</h2></div>' ;
} else {
?>


<div id="home"><h2>Login</h2>
<form method="post" action="<?=$sitepath?>includes/login.php">
	 <div class="box">
			<label>
	                	<span>Username</span>
	                	<input type="text" tabindex="1" class="input_text" name="user" id="name"/>
            		</label>
			<label>
	                	<span>Password</span>
	                	<input type="password" tabindex="1" class="input_text" name="pass" id="pass"/>
            		</label>	 

           		<label>
           			<span>Remember me</span>
				<input type="checkbox" name="remember" id="remember"/>
            		</label>
           		<label>
               			<span><a href="<?=$sitepath?>forgot" title="Click here to recover your password">Forgot Password?</a></span>
               			<br>
            		</label>           		

           		<label>
               		<input type="submit" class="button" value="Log in" />	
            		</label>
	</div>
</form>
</div>

<?php
}
?>



