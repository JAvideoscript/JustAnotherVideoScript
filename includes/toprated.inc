<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
require_once "includes/tablefunction.inc" ;
	$db->query("SELECT * FROM sitead WHERE adname='ad7'") ;
	if ($db->numRows() > 0) {
		$ares = $db->fetch() ;
		$ad7 = $ares['adtext'] ;
		if ($ad7 != '') {
			$ad7 = '<div id="adunder728x90">'.$ad7.'</div>' ;
		}
	}

function topRatedmedia() {
	global $db,$templateimagepath,$sitepath ;
		$db->query("SELECT v.*, (r.total_value/r.total_votes) as rating FROM media v LEFT JOIN rating r ON r.id = v.id WHERE v.status = 'true' ORDER BY (r.total_value/r.total_votes) DESC LIMIT 100") ;
		$resTR = $db->fetchAll() ;
			if (isset($_GET['page'])) {
				$output = Tableview(15, $resTR, $_GET['page'], $sitepath."top-rated") ;
			} else {
				$output = Tableview(15, $resTR, 1, $sitepath."top-rated") ;
			}
	return $output ;
}

?>