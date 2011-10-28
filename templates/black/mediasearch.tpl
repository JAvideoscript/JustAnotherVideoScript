<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
include_once 'includes/mediasearch.inc';







echo '<div id="main-left"><h2>Media search</h2>' ;
echo catplainlist() ;
echo '</div>' ;
echo '<div id="main-right"><h2>Videos</h2>' ;
echo searchMedia() ;
echo '</div>' ;
?>