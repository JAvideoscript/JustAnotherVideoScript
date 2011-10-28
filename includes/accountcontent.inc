<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
global $sitepath,$rootpath;
$site_template = getSetting("sitetemplate",$db);
$pageid = quote_smart($_GET['page']) ;
switch ($pageid) {
            case 'changepass':
			$filepath = $rootpath.'templates/'.$site_template.'/loggedin/changepass.tpl' ;
			break ;
            case 'changeavatar':
			$filepath = $rootpath.'templates/'.$site_template.'/loggedin/changeavatar.tpl' ;
			break ;
            case 'changeemail':
			$filepath = $rootpath.'templates/'.$site_template.'/loggedin/changeemail.tpl' ;
			break ;
            case 'personalinformation':
			$filepath = $rootpath.'templates/'.$site_template.'/loggedin/personalinformation.tpl' ;
			break ;
            case 'memberprivacy':
			$filepath = $rootpath.'templates/'.$site_template.'/loggedin/memberprivacy.tpl' ;
			break ;
            case 'uploadedvideos':
			$filepath = $rootpath.'templates/'.$site_template.'/loggedin/uploadedvideos.tpl' ;
			break ;
            case 'favoritevideos':
			$filepath = $rootpath.'templates/'.$site_template.'/loggedin/favoritevideos.tpl' ;
			break ;
            case 'viewinghistory':
			$filepath = $rootpath.'templates/'.$site_template.'/loggedin/viewinghistory.tpl' ;
			break ;
            case 'inbox':
			$filepath = $rootpath.'templates/'.$site_template.'/loggedin/inbox.tpl' ;
			break ;
	    case 'sendmsg':
			$filepath = $rootpath.'templates/'.$site_template.'/loggedin/sendmsg.tpl' ;
			break ;
            case 'outbox':
			$filepath = $rootpath.'templates/'.$site_template.'/loggedin/outbox.tpl' ;
			break ;
            case 'friends':
			$filepath = $rootpath.'templates/'.$site_template.'/loggedin/friends.tpl' ;
			break ;
            case 'receivedrequests':
			$filepath = $rootpath.'templates/'.$site_template.'/loggedin/receivedrequests.tpl' ;
			break ;
            case 'sentrequests':
			$filepath = $rootpath.'templates/'.$site_template.'/loggedin/sentrequests.tpl' ;
			break ;
            case 'profileviews':
			$filepath = $rootpath.'templates/'.$site_template.'/loggedin/profileviews.tpl' ;
			break ;
            case 'blockedmembers':
			$filepath = $rootpath.'templates/'.$site_template.'/loggedin/blockedmembers.tpl' ;
			break ;
            default:
            		$filepath = $rootpath.'templates/'.$site_template.'/loggedin/defaultaccount.tpl' ;
             		break ;                   
}
if (file_exists($filepath)) {
	include($filepath);
}

?>