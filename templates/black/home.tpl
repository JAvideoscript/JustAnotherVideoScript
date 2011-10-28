<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
include_once 'includes/home.inc';
?>
<div id="home">
<h2>Latest Videos</h2>
<?=rotator()?>
<?=$ad1?>


<div id="home-left">
	<h2>Latest Uploads</h2>
	<?=latestupload()?>
</div>
<div id="home-right">
	<h2>Top5 Today</h2>
	<?=top5today()?>
	<h2>Newest Members</h2>
	<?=membershome()?>
</div>



<?=$ad2?>
</div>