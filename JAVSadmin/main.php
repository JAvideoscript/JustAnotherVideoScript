<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
session_start();
require_once( "functions.php" );

if (!Beveiliging()){
    echo "Not logged in";
    header ( "location: index.php" );
} else {
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml2/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<head>
<title>JAVS Admin</title>
<script type="text/javascript" src="js/jquery.min.js"></script>
<script type="text/javascript" src="js/ddaccordion.js"></script>
<script type="text/javascript">
ddaccordion.init({
	headerclass: "submenuheader",
	contentclass: "submenu",
	revealtype: "click",
	mouseoverdelay: 200,
	collapseprev: true,
	defaultexpanded: [],
	onemustopen: false,
	animatedefault: false,
	persiststate: true,
	toggleclass: ["", ""],
	togglehtml: ["suffix", "<img src='images/plus.gif' class='statusicon' />", "<img src='images/minus.gif' class='statusicon' />"],
	animatespeed: "normal",
	oninit:function(headers, expandedindices){
		//do nothing
	},
	onopenclose:function(header, index, state, isuseractivated){
		//do nothing
	}
})
</script>
<link rel="stylesheet" type="text/css" href="admin.css" />
</head>
<body>
<div id="wrapper">
<div class="glossymenu">
	<a class="menuitem" href="main.php?do=status" style="border-bottom-width: 0">Site status</a>
	<a class="menuitem submenuheader" href="#" >Site Settings</a>
		<div class="submenu">
			<ul>
				<li><a href="main.php?do=global">Global</a></li>
				<li><a href="main.php?do=mediasettings">Media settings</a></li>
				<li><a href="main.php?do=menusettings">Menu settings</a></li>
				<li><a href="main.php?do=encodingsettings">Encoding settings</a></li>
				<li><a href="main.php?do=pagesettings">Page settings</a></li>
				<li><a href="main.php?do=emailtext">Email Text</a></li>
				<li><a href="main.php?do=mobilesettings">Mobile settings</a></li>
				<li><a href="main.php?do=hdsettings">HD settings</a></li>
			</ul>
		</div>
	<a class="menuitem submenuheader" href="#">Video</a>
		<div class="submenu">
			<ul>
				<li><a href="main.php?do=allvideos">All videos</a></li>
				<li><a href="main.php?do=newuploads">New uploads</a></li>
				<li><a href="main.php?do=dbclean">Database cleaner</a></li>
				<li><a href="main.php?do=memcomments">Comments</a></li>
				<li><a href="main.php?do=flagged">Flagged Videos</a></li>
				<li><a href="main.php?do=Category">Category</a></li>
			</ul>
		</div>
	<a class="menuitem submenuheader" href="#">Members</a>
		<div class="submenu">
			<ul>
				<li><a href="main.php?do=userlist">User List</a></li>
				<li><a href="main.php?do=massemail">Mass email</a></li>
			</ul>
		</div>

	<a class="menuitem submenuheader" href="#">Plugins</a>
		<div class="submenu">
			<ul>
				<li><a href="main.php?do=youtubedown">Youtube Download</a></li>
				<li><a href="main.php?do=youtubeembed">Youtube Embed</a></li>
				<li><a href="main.php?do=s2s">Server2Server</a></li>
				<li><a href="main.php?do=massimport">Mass import</a></li>
				<li><a href="main.php?do=videodownloader">videodownloader</a></li>
			</ul>
		</div>
	<a class="menuitem submenuheader" href="#">SEO</a>
		<div class="submenu">
			<ul>
			<li><a href="main.php?do=seo">Site SEO</a></li>
			<li><a href="main.php?do=sitemap">Sitemap</a></li>
			</ul>
		</div>

<a class="menuitem" href="main.php?do=advertising" style="border-bottom-width: 0">Advertising</a>
<a class="menuitem" href="main.php?do=changepass" style="border-bottom-width: 0">Admin Account</a>
<a class="menuitem" href="../index.php" style="border-bottom-width: 0">Go to Site</a>
<a class="menuitem" href="main.php?do=logout" style="border-bottom-width: 0">Logout</a>
</div>


<div id="content">

<?php include_once ("modules/admincontent.inc") ?>

</div>

</div>
</body>
</html>


<?php
}
?>