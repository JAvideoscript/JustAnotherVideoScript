<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
header("Content-Type: application/xml; ") ;
include_once 'includes/bootstrap.inc' ;
include_once 'includes/common.inc' ;
include_once 'includes/content.inc' ;
global $db,$sitepath ;
$sitename = getSetting("sitename", $db) ;
$email = getSetting("contact_email", $db) ;
$sitetitle = getSetting("sitetitle", $db) ;
echo "<?xml version='1.0' encoding='ISO-8859-1' ?>
<rss version='2.0'>
<channel>
<title>".$sitename."</title>
<link>".$sitepath."</link>
<description>".$sitetitle."</description>
<language>en-us</language>
<pubDate>".date("Y-m-d", time())." GMT</pubDate>
<lastBuildDate>".date("Y-m-d", time())." GMT</lastBuildDate>
<copyright>".$sitename."</copyright>
<author>".$sitetitle."</author>
<image><url>".$sitepath."templates/".$site_template."/images/013.png</url><title>".$row['title']."</title><link>".$sitepath."</link></image>
" ;
if (!quote_smart($_GET['feed'])) {
	$db->query('SELECT * FROM media WHERE status = "true" ORDER BY id DESC') ;
	while ($row = $db->fetch()) {
		echo '<item><title>'.$row['title'].'</title><description><![CDATA[<a href="'.$sitepath.'play/'.$row['url'].'"><img src="'.$sitepath.'uploads/thumbs/'.$row['fileid'].'.jpg"/></a><br/>'.$row['description'].']]></description><tags>'.$row['tags'].'</tags><uploadedby>'.$row['poster'].'</uploadedby><link>'.$sitepath.'play/'.$row['url'].'</link><visits>'.$row['allviews'].'</visits><pubDate>'.date("D, j M Y H:i:s", $row['added']).' EST</pubDate><thumb>'.$sitepath.'uploads/thumbs/'.$row['fileid'].'.jpg</thumb><image><url>'.$sitepath.'uploads/thumbs/'.$row['thumb'].'.large.jpg</url><title>'.$row['title'].'</title><link>'.$sitepath.'</link></image></item>' ;
	}
} else {
	$db->query("SELECT name FROM category WHERE id = '".quote_smart($_GET['feed'])."'") ;
	$res = $db->fetch() ;
	$db->query("SELECT * FROM media WHERE category = '".quote_smart($_GET['feed'])."' ORDER BY id DESC") ;

	while ($row = $db->fetch()) {
		echo '<item><title>'.$row['title'].'</title><description><![CDATA[<a href="'.$sitepath.'play/'.$row['url'].'"><img src="'.$sitepath.'uploads/thumbs/'.$row['fileid'].'.jpg"/></a><br/>'.$row['description'].']]></description><tags>'.$row['tags'].'</tags><uploadedby>'.$row['poster'].'</uploadedby><link>'.$sitepath.'play/'.$row['url'].'</link><visits>'.$row['allviews'].'</visits><pubDate>'.date("D, j M Y H:i:s", $row['added']).' EST</pubDate><thumb>'.$sitepath.'uploads/thumbs/'.$row['fileid'].'.jpg</thumb><image><url>'.$sitepath.'uploads/thumbs/'.$row['thumb'].'.large.jpg</url><title>'.$row['title'].'</title><link>'.$sitepath.'</link></image></item>' ;
	}
}
echo "</channel>" ;
echo "</rss>" ;
?>