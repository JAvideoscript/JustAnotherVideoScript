<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
ob_start("ob_gzhandler");
header("Content-Type: application/xml; ") ;
include_once 'includes/bootstrap.inc' ;
include_once 'includes/common.inc' ;
include_once 'includes/content.inc' ;
global $db,$sitepath ;
$sitename = getSetting("sitename", $db) ;
$email = getSetting("contact_email", $db) ;
$sitetitle = getSetting("sitetitle", $db) ;
echo "<?xml version='1.0' encoding='ISO-8859-1' ?>
<rss version='2.0'  xmlns:media='http://search.yahoo.com/mrss/'>>
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
		echo '
<item>
	<title>'.$row['title'].'</title>
	<link>'.$sitepath.'play/'.$row['url'].'</link>
	<description><![CDATA['.$row['description'].']]></description>
	<guid isPermaLink="false">'.$sitepath.'play/'.$row['url'].'</guid>
	<media:content url="'.$row['fileid'].'.flv" type="video/x-msvideo" height="240" width="320" medium="video" isDefault="true">
	<media:title>'.$row['title'].'</media:title>
	<media:description><![CDATA['.$row['description'].']]></media:description>
	<media:keywords>'.$row['tags'].'</media:keywords>
	<media:thumbnail url="" height="96" width="96"/>
	</media:content>
	<tags>'.$row['tags'].'</tags>
	<uploadedby>'.$row['poster'].'</uploadedby>
	<visits>'.$row['allviews'].'</visits>
	<pubDate>'.date("D, j M Y H:i:s", $row['added']).' EST</pubDate>
	<thumb>'.$sitepath.'uploads/thumbs/'.$row['fileid'].'.jpg</thumb>
	<image><url>'.$sitepath.'uploads/thumbs/'.$row['fileid'].'.jpg</url><title>'.$row['title'].'</title><link>'.$sitepath.'</link></image>
</item>' ;
	}
}
else {
	$db->query("SELECT name FROM category WHERE id = '".quote_smart($_GET['feed'])."'") ;
	$res = $db->fetch() ;
	$db->query("SELECT * FROM media WHERE category = '".quote_smart($_GET['feed'])."' AND status = 'true' ORDER BY id DESC") ;
	while ($row = $db->fetch()) {
		echo '
<item>
	<title>'.$row['title'].'</title>
	<link>'.$sitepath.'play/'.$row['url'].'</link>
	<description><![CDATA['.$row['description'].']]></description>
	<guid isPermaLink="false">'.$sitepath.'play/'.$row['url'].'</guid>
	<media:content url="" type="video/x-msvideo" height="240" width="320" medium="video" isDefault="true">
	<media:title>'.$row['title'].'</media:title>
	<media:description><![CDATA['.$row['description'].']]></media:description>
	<media:keywords>'.$row['tags'].'</media:keywords>
	<media:thumbnail url="" height="96" width="96"/>
	</media:content>
	<tags>'.$row['tags'].'</tags>
	<uploadedby>'.$row['poster'].'</uploadedby>
	<visits>'.$row['allviews'].'</visits>
	<pubDate>'.date("D, j M Y H:i:s", $row['added']).' EST</pubDate>
	<thumb>'.$sitepath.'uploads/thumbs/'.$row['fileid'].'.jpg</thumb>
	<image><url>'.$sitepath.'uploads/thumbs/'.$row['fileid'].'.jpg</url><title>'.$row['title'].'</title><link>'.$sitepath.'</link></image>
</item>' ;
		}
}
echo "</channel>" ;
echo "</rss>" ;
?>