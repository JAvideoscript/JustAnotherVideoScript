<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
require_once "includes/tablefunction.inc" ;
	$db->query("SELECT * FROM sitead WHERE adname='ad9'") ;
	if ($db->numRows() > 0) {
		$ares = $db->fetch() ;
		$ad9 = $ares['adtext'] ;
		if ($ad9 != '') {
			$ad9 = '<div id="adunder728x90">'.$ad9.'</div>' ;
		}
	}


function mostViewedmedia() {
	global $db,$sitepath ;
		//Get dates used for filtering results
		$todaylink = $sitepath.'most-viewed/today' ;
		$weeklink = $sitepath.'most-viewed/week' ;
		$thirtylink = $sitepath.'most-viewed/month' ;
		$alllink = $sitepath.'most-viewed/' ;
		$filter = $_GET['filter'] ;
		$filterstring = "" ;
		$filterlink = "<b>all time</b> | <a href='".$todaylink."'>today</a> | <a href='".$weeklink."'>this week</a> | <a href='".$thirtylink."'>last 30 days</a>" ;
		if (($filter == "all") || ($filter == "")) {
			$filterstring = "ORDER BY allviews DESC" ;
			$filterlink = "<b>all time</b> | <a href='".$todaylink."'>today</a> | <a href='".$weeklink."'>this week</a> | <a href='".$thirtylink."'>this month</a>" ;
		}
		else if ($filter == "today") {
			$filterstring = "ORDER BY dayviews DESC" ;
			$filterlink = "<a href='".$alllink."'>all time</a> | <b>today</b> | <a href='".$weeklink."'>this week</a> | <a href='".$thirtylink."'>this month</a>" ;
		}
		else if ($filter == "week") {
			$filterstring = "ORDER BY weekviews DESC" ;
			$filterlink = "<a href='".$alllink."'>all time</a> | <a href='".$todaylink."'>today</a> | <b>this week</b> | <a href='".$thirtylink."'>this month</a>" ;
		}
		else if ($filter == "month") {
			$filterstring = "ORDER BY monthviews DESC" ;
			$filterlink = "<a href='".$alllink."'>all time</a> | <a href='".$todaylink."'>today</a> | <a href='".$weeklink."'>this week</a> | <b>this month</b>" ;
		}
		$db->query("SELECT * FROM `media` WHERE `status` ='true' ".quote_smart($filterstring)." LIMIT 100") ;
		$resTR = $db->fetchAll() ;
		$sitefolder = getSetting("sitefolder", $db) ;
		$path = 'http://'.$_SERVER['SERVER_NAME'].$sitefolder.'most-viewed' ;
		$output = '<div class="top-filter">'.$filterlink.'</div>' ;
		if ($db->numRows() > 0) {		
				if (isset($_GET['page'])) {
					$output .= Tableview(14, $resTR, quote_smart($_GET['page']), $path, $filter) ;
				} else {
					$output .= Tableview(14, $resTR, 1, $path, quote_smart($filter)) ;
				}
			
		} else {
			$output .= "<h2>There is no media to display</h2>" ;
		}
			
	return $output ;
}

?>
