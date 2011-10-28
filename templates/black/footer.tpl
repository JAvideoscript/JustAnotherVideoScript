<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */

echo $getit.' |' ; 

if (getSetting("showdmca", $db) == '1') {
	echo '<a href="'.$sitepath.'dmca"> DMCA</a> |' ;
}
if (getSetting("show2257", $db) == '1') {
	echo '<a href="'.$sitepath.'2257"> 2257</a> |' ;
}
?>
<a href="<?=$sitepath."rss"?>"> Rss Feed</a>
