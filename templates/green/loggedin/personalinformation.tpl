<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
include_once "includes/personalinformation.inc" ;
?>

<h2>Personal information</h2>




<form action="" method="post" enctype="multipart/form-data">
<div class="box">
	<h3><?=$msg?></h3>
	<label>
		<span>About Me:</span>
		<textarea class="input_text" rows=5 name="aboutme"><?=$curabout?></textarea>
	</label>
	<label>
		<span>Favorite Movie:</span>
		<input type="text" class="input_text" name="favmovie" value="<?=$curmovie?>" />
	</label>
	<label>
		<span>My age:</span>
		<input type="text" class="input_text" name="age" value="<?=$curage?>" />
	</label>
	<label>
		<span>Gender:</span>
		<input type="radio" name="gender" VALUE="0" <?=$curmale?>> Male <input type="radio" name="gender" VALUE="1" <?=$curfemale?>> Female 
	</label>

	<label>
		<span>Location:</span>
		<select class="input_text" name="location" value="<?=$curlocation?>">
			<?php echo alllands($curlocation)?>
		</select>
	</label>

	<label>
		<input type="submit" class="button" name="submit" value="Update" />	
	</label>

</div>
</form>



