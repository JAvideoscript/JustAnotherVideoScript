<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
require_once "includes/tablefunction.inc" ;

$db->query("SELECT * FROM sitead WHERE adname='ad5'") ;
if ($db->numRows() > 0) {
	$ares = $db->fetch() ;
	$ad5 = $ares['adtext'] ;
	if ($ad5 != '') {
		$ad5 = '<div id="adunder728x90">'.$ad5.'</div>' ;
	}
}

function allmedia() {
	global $db,$sitepath ;
		$db->query("SELECT * FROM `media` WHERE `status` ='true' ORDER BY `added` DESC") ;
		$resLV = $db->fetchAll() ;
			if (isset($_GET['page']))
				$output = Tableview(1, $resLV, $_GET['page'], $sitepath."videos") ;
			else
				$output = Tableview(1, $resLV, 1, $sitepath."videos") ;
	return $output ;
}

?>



