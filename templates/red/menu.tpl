<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
?>
<div id="menu">
	<ul>
			<li class="left">&nbsp;</li>
			<li><em></em><a href="<?php echo $path;?>">Home</a></li>
		<?php if (getSetting("showallvideos", $db) == '1') { ?>
			<li><em></em><a href="<?php echo $path;?>videos">Videos</a></li>
		<?php } if (getSetting("showtoprated", $db) == '1') { ?>
			<li><em></em><a href="<?php echo $path;?>top-rated">Top rated</a></li>
		<?php } if (getSetting("showmostviewed", $db) == '1') { ?>
			<li><em></em><a href="<?php echo $path;?>most-viewed">Most viewed</a></li>
		<?php } if (getSetting("showcategorie", $db) == '1') { ?>
			<li><em></em><a href="<?php echo $path;?>categories">Categories</a></li>
		<?php } ?>	
		<?php if ((getSetting("showupload", $db) == '1') || (getSetting("showembed", $db) == '1')) { ?>
			<li><em></em><a href="<?php echo $path;?>upload">Upload</a></li>
		<?php } ?>
			<li class="sep">&nbsp;</li>
			<li class="right">&nbsp;</li>

	

<form method="post" action="<?=$sitepath?>search">
<fieldset class="search">
<input type="text" name="keyword" class="box" />
<button class="btn" type="submit" name="submit" title="Submit Search">Search</button>
</fieldset>
</form>

		</ul>
	
	
	
	
	
	
</div>





         	  