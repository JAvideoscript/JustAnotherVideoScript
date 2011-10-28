<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
include_once 'includes/mysql.inc' ;
include_once 'includes/functions.inc' ;
include_once 'includes/logged.inc' ;
$country = '' ;
global $db;
$sitefolder = getSetting("sitefolder", $db) ;
$sitepath = "http://".$_SERVER['SERVER_NAME'].$sitefolder ;
if (class_exists("mysql")) {
      $db = db_connect() ;
}

//Handle query string
if (isset($_GET['crw'])) {
      define('enc_CAT', url_encode(quote_smart($_GET['crw']))) ;
      define('dec_CAT', url_decode(quote_smart($_GET['crw']), "cat")) ;
}
if (isset($_GET['vrw'])) {
      define('enc_VID', url_encode(quote_smart($_GET['vrw']))) ;
      define('dec_VID', url_decode(quote_smart($_GET['vrw']), "vid")) ;
}
if (isset($_GET['id'])) {
      $_this['id'] = quote_smart($_GET['id']) ;
}
if (!isset($_GET['id'])) {
      $_GET['id'] = 1 ;
}
if (defined("dec_VID")) {
      $db->query("SELECT category,title,tags FROM `media` WHERE title = '".quote_smart(dec_VID)."'") ;
      $res = $db->fetch() ;
      $db->query("SELECT name FROM `category` WHERE `id` = '".$res['category']."'") ;
      $catres = $db->fetch() ;
      $mediaKeywords = $catres['name'].", ".$res['tags'] ;
      $mediaDescription = $res['title'] ;
}
?>