<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
 global $sitepath;
$accountManagementPage = false ;

//ad under player
$db->query("SELECT * FROM sitead WHERE adname='ad16'") ;
if ($db->numRows() > 0) {
	$ares = $db->fetch() ;
	$ad16 = $ares['adtext'] ;
	if ($ad16 != '') {
		$ad16 = '<div id="adfooter728x90">'.$ad16.'</div>' ;
	}
}
if (($_GET['id'] == '56') && (getSetting("accountpageon", $db) == 0)) {
      $_GET['id'] = '1' ;
}
      switch ($_GET['id']) {
            //Accessible to all
            case '1':
            	  $frontpage = getSetting("showfrontpage", $db) ;
                  $c_file = '/'.$frontpage.'.tpl' ;
                  $c_header = getSetting('meta_'.$frontpage.'_header', $db) ;
                  $mediaKeywords = getSetting('meta_'.$frontpage.'_key', $db) ;
		  $mediaDescription =  getSetting('meta_'.$frontpage.'_desc', $db) ;
                  break ;
            case '2':
                  $c_file = '/toprated.tpl' ;
                  $c_header = getSetting(meta_toprated_header, $db) ;
                  $mediaKeywords = getSetting(meta_toprated_key, $db) ;
		  $mediaDescription = getSetting(meta_toprated_desc, $db) ;
                  break ;
            case '3':
                  $c_file = '/mostviewed.tpl' ;
                  $c_header = getSetting(meta_mostviewed_header, $db) ;
                  $mediaKeywords = getSetting(meta_mostviewed_key, $db) ;
		  $mediaDescription = getSetting(meta_mostviewed_desc, $db) ;
                  break ;
            case '4':
                  $c_file = '/forgot.tpl' ;
                  $c_header = 'Forgotten Login' ;
                  $mediaKeywords = "Forgot," ;
		  $mediaDescription = "Forgot" ;
                  break ;
            case '5':
                  $c_file = '/upload.tpl' ;
                  $c_header = 'Upload Media' ;
                  $mediaKeywords = "Upload, video" ;
		  $mediaDescription = "Upload Video" ;                  
                  break ;
            case '6':
                  $c_file = '/signup.tpl' ;
                  $c_header = 'Signup' ;
                  $mediaKeywords = "User, signup," ;
		  $mediaDescription = "User signup" ;
                  break ;
            case '7':
                  $c_file = '/videos.tpl' ;
                  $c_header = getSetting(meta_allvideos_header, $db) ;
                  $mediaKeywords = getSetting(meta_allvideos_key, $db) ;
		  $mediaDescription = getSetting(meta_allvideos_desc, $db) ;
                  break ;
            case '8':
                  $c_file = '/play.tpl' ;
                  $c_header = dec_VID ;
                  break ;
            case '9':
                  $c_file = '/embed.tpl' ;
                  $c_header = 'Embed Media' ;
                  $mediaKeywords = "Embed, video" ;
		  $mediaDescription = "Embed Video" ;                  
                  break ;
            case '10':
                  $c_file = '/activate.tpl' ;
                  $c_header = 'Activate Your Account' ;
                  $mediaKeywords = "Activate, Your Account" ;
		  $mediaDescription = "Activate Your Account" ;
                  break ;
            case '11':
                  $c_file = '/upload2.tpl' ;
                  $c_header = 'Name your upload' ;
                  $mediaKeywords = "Upload2, video" ;
		  $mediaDescription = "Upload2 Video" ;  
                  break ;
            case '12':
                  $c_file = '/login.tpl' ;
                  $c_header = 'Login' ;
                  $mediaKeywords = "Login, video" ;
		  $mediaDescription = "Login to site" ;  
                  break ;   
            case '88':
                  $c_file = '/members.tpl' ;
                  $c_header = getSetting(meta_members_header, $db) ;
                  $mediaKeywords = getSetting(meta_members_key, $db) ;
		  $mediaDescription = getSetting(meta_members_desc, $db) ;
                  break ;
            case '16':
                  $c_file = '/terms.tpl' ;
                  $c_header = 'Terms of Service' ;
              	  $mediaKeywords = "Terms, Service" ;
		  $mediaDescription = "Terms of Service" ;
                  break ;
            case '33':
		  $c_file = '/dmca.tpl' ;
		  $c_header = 'DMCA' ;
		  $mediaKeywords = "DMCA," ;
		  $mediaDescription = "DMCA notice" ; 
                  break ;
            case '34':
		  $c_file = '/2257.tpl' ;
		  $c_header = '2257' ;
		  $mediaKeywords = "2257," ;
		  $mediaDescription = "2257 notice" ; 
                  break ;
            case '18':
                  $c_file = '/profile.tpl' ;
                  $c_header = getSetting(meta_profile_header, $db) ;
                  $mediaKeywords = getSetting(meta_profile_key, $db) ;
                  $mediaDescription = getSetting(meta_profile_desc, $db) ;
                  break ;
            case '21':
                  $c_file = '/category.tpl' ;
                  $c_header = getSetting(meta_category_header, $db) ;
                  $mediaKeywords = getSetting(meta_category_key, $db) ;
		  $mediaDescription = getSetting(meta_category_desc, $db) ;
                  break ;
            case '22':
                  $c_file = '/mediasearch.tpl' ;
                  $c_header = getSetting(meta_search_header, $db) ;
                  $mediaKeywords = getSetting(meta_search_key, $db) ;
		  $mediaDescription = getSetting(meta_search_desc, $db) ;
                  break ;
            case '29':
                  $c_file = '/rss.tpl' ;
                  $c_header = 'Rss Feeds' ;
                  $mediaKeywords = "RSS," ;
		  $mediaDescription = "RSS" ; 
                  break ;
            case '56':
                  $c_file = '/account.tpl' ;
                  $c_header = 'Account Management' ;
                  $mediaKeywords = "Account, Management," ;
		  $mediaDescription = "Account Management" ; 
                  $accountManagementPage = true ;
                  break ;
            case '14':
                  $c_file = '/catlist.tpl' ;
                  $c_header = getSetting(meta_catlist_header, $db) ;
		  $mediaKeywords = getSetting(meta_catlist_key, $db) ;
		  $mediaDescription = getSetting(meta_catlist_desc, $db) ;
                  break ;
            default:
                  $c_file = '/error.php' ;
                  $c_header = 'Error 404' ;
                  $mediaKeywords = "Error 404," ;
		  $mediaDescription = "Error 404" ; 
                  break ;
      }

?>
