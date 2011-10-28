<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
include_once "includes/changeemail.inc" ;
?>

<h2>Change Email</h2>

<form action="" method="post" enctype="multipart/form-data">
<div class="box">
	<h3><?=$msg?></h3>
	<label>
		<span>New email:</span>
		<input type="text" class="input_text" name="newmail" />
	</label>
	<label>
		<span>Verify email:</span>
		<input type="text" class="input_text" name="vermail" />
	</label>	
	
	<label>
		<input type="submit" class="button" name="submit" value="Change" />	
	</label>

</div>
</form>
