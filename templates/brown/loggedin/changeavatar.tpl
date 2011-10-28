<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
include_once "includes/changeavatar.inc" ;
?>

<h2>Change avatar</h2>

<form action="" method="post" enctype="multipart/form-data">
<div class="box">
	<h3><?=$msg?></h3>
	<label>
		<span>Current Avatar:</span>
		<?=$curavatar?>	
	</label>

	<label>
		<span>New Avatar:</span>
		<input type="file" class="input_text" name="newavatar" />
	</label>

	<label>
		<input type="submit" class="button" name="submit" value="Change" />	
	</label>


</div>
</form>
