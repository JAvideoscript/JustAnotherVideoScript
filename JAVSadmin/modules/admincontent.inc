<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */

switch ($_GET['do']) {
	default: include('modules/status.inc') ;
	break; case"status":include_once('modules/status.inc');
	break; case"global":include_once('modules/global.inc');
	break; case"mediasettings":include_once('modules/mediasettings.inc');
	break; case"menusettings":include_once('modules/menusettings.inc');
	break; case"encodingsettings":include_once('modules/encodingsettings.inc');
	break; case"pagesettings":include_once('modules/pagesettings.inc');
	break; case"mobilesettings":include_once('modules/mobilesettings.inc');
	break; case"hdsettings":include_once('modules/hdsettings.inc');
	break; case"allvideos":include_once('modules/allvideos.inc');
	break; case"youtubedown":include_once('modules/youtubedown.inc');
	break; case"youtubeembed":include_once('modules/youtubeembed.inc');	
	break; case"s2s":include_once('modules/s2s.inc');
	break; case"newuploads":include_once('modules/newuploads.inc');
	break; case"dbclean":include_once('modules/dbclean.inc');
	break; case"massimport":include_once('modules/massimport.inc');
	break; case"Category":include_once('modules/Category.inc');
	break; case"userlist":include_once('modules/userlist.inc');
	break; case"massemail":include_once('modules/massemail.inc');
	break; case"emailtext":include_once('modules/emailtext.inc');
	break; case"seo":include_once('modules/seo.inc');
	break; case"sitemap":include_once('modules/sitemap.inc');
	break; case"advertising":include_once('modules/advertising.inc');
	break; case"memcomments":include_once('modules/memcomments.inc');
	break; case"flagged":include_once('modules/flagged.inc');
	break; case"frontvideo":include_once('modules/frontvideo.inc');
	break; case"logout":session_start(); session_destroy(); header("Location: index.php");
	break; case"changepass":include_once('modules/changepass.inc');
	break; case"videodownloader":include_once('modules/videodownloader.inc');
	
}


?>