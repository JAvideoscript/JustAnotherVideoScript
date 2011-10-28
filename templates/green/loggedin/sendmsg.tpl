<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
include_once "includes/sendmsg.inc" ;
?>
<div class="top-title">Send Message</div>

<?php
if (isset($msgusername )) {
?>


<fieldset>
	<ol>
	<form action="" method="post" enctype="multipart/form-data">
		<li>
				<h2>&nbsp;&nbsp;Send an message to <?=$msgusername?></h2>
				<label for="msgbody"></label>
				<textarea rows=5 cols=35 name="msgbody"></textarea>
		</li>
		<li>
				<label for="submit">&nbsp;</label>
				<input class="biggerbutton" type="submit" name="submit" value="Send Message" />
		</li>
		
		
		</form>
	</ol>
</fieldset>	




<?php
} else {
echo "<h2>not a valid username</h2>" ;
}
?>