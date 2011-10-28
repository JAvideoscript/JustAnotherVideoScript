<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
include_once "includes/defaultaccount.inc" ;
?>

<h2>Account overview</h2>


	<div class="box">
		<label>
			<span>Account setup:</span>
			<?=$accountsetup?>
		</label>
		<label>
			<span>Avatar:</span>
			<?=$avastats?>
		</label>
		<label>
			<span>About me:</span>
			<?=$aboutstats?>
		</label>		
		<label>
			<span>Favorite Movie:</span>
			<?=$favstats?>
		</label>		
		<label>
			<span>Looking For:</span>
			<?=$lookstats?>
		</label>
		
	</div>
