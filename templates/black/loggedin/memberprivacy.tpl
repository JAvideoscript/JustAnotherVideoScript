<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
include_once "includes/memberprivacy.inc" ;
?>

<h2>Change Privacy settings</h2>

<form action="" method="post" enctype="multipart/form-data">
<div class="box">
	<h3><?=$msg?></h3>
	<label>
			Who can send you messages and leave comments:<br>
			<input type="radio" name="privacy" VALUE="0" <?=$prvpublic?>>&nbsp;Public - All visitors to the site <br>
			<input type="radio" name="privacy" VALUE="1" <?=$prvregis?>>&nbsp;Registered - Only registered, logged in members <br>
			<input type="radio" name="privacy" VALUE="2" <?=$prvpriv?>>&nbsp;Private - Only approved friends
	</label>	
	
	
	<label>
		Show other members you watched there profile:<br>
		<input type="radio" name="historyview" VALUE="0" <?=$curshow?>> show <br> <input type="radio" name="historyview" VALUE="1" <?=$curhide?>> hide <br>
	</label>	

	<label>
		Get email from friends when they uploaded email:<br>
		<input type="radio" name="friendmail" VALUE="0" <?=$fmailshow?>> Yes <br> <input type="radio" name="friendmail" VALUE="1" <?=$fmailhide?>> No <br>
	</label>

	<label>
		<input type="submit" class="button" name="submit" value="Change" />	
	</label>

</div>
</form>

