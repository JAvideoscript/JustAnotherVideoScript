<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
include_once "includes/changepass.inc" ;
?>

<h2>Change Password</h2>


<form action="" method="post" enctype="multipart/form-data">
<div class="box">
	<h3><?=$msg?></h3>

	<label>
		<span>Old password:</span>
		<input type="password" class="input_text" name="oldpass" />
	</label>
	<label>
		<span>New password:</span>
		<input type="password" class="input_text" name="newpass" />
	</label>
	<label>
		<span>Verify password:</span>
		<input type="password" class="input_text" name="newpass2" />
	</label>

	<label>
		<input type="submit" class="button" name="submit" value="Change" />	
	</label>

</div>
</form>
