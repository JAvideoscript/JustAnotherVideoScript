<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
require_once "includes/tablefunction.inc" ;
global $db ;
function searchMedia() {
	global $db,$sitepath ;
	if ($_GET['keywords'] != '') {
		$_POST['keyword'] = urldecode($_GET['keywords']) ;
	}
	//Get dates used for filtering results
	$today = mktime(0, 0, 0, date("m"), date("d"), date("Y")) ;
	$startofyear = mktime(0, 0, 0, 1, 0, date("Y")) ;
	$aweek = 60 * 60 * 24 * 7 ;
	$startofweek = $startofyear + ($aweek * (intval(date("W") - 1))) ;
	$startofmonth = mktime(0, 0, 0, date("m"), 1, date("Y")) ;
	$mostviewed = false ;
	$recent = false ;
	$keywords = quote_smart(alphaNum($_POST['keyword'])) ;
	$keywordsearch = "AND (title LIKE '%".$keywords."%' OR description LIKE '%".$keywords."%' OR tags LIKE '%".$keywords."%')" ;
	if (isset($_POST['mostviewedsubmit'])) {
		$mostviewed = true ;
		if ($_POST['mostviewed'] == "alltime") {
			$mvalltimesel = "SELECTED" ;
			$filterstring = "ORDER BY allviews DESC" ;
			$filter = "all" ;
		}
		if ($_POST['mostviewed'] == "today") {
			$mvtodaysel = "SELECTED" ;
			$filterstring = "ORDER BY dayviews DESC" ;
			$filter = "today" ;
		}
		if ($_POST['mostviewed'] == "thisweek") {
			$mvweeksel = "SELECTED" ;
			$filterstring = "ORDER BY weekviews DESC" ;
			$filter = "week" ;
		}
		if ($_POST['mostviewed'] == "thismonth") {
			$mvmonthsel = "SELECTED" ;
			$filterstring = "ORDER BY monthviews DESC" ;
			$filter = "month" ;
		}
	}
	if (isset($_POST['recentsubmit'])) {
		$recent = true ;
		if ($_POST['recent'] == "today") {
			$rctodaysel = "SELECTED" ;
			$filterstring = "AND (added>".$today.") ORDER BY added DESC" ;
		}
		if ($_POST['recent'] == "thisweek") {
			$rcweeksel = "SELECTED" ;
			$filterstring = "AND (added>".$startofweek.") ORDER BY added DESC" ;
		}
		if ($_POST['recent'] == "thismonth") {
			$rcmonthsel = "SELECTED" ;
			$filterstring = "AND (added>".$startofmonth.") ORDER BY added DESC" ;
		}
	}
	$typestring = "" ;
	if (isset($_POST['typesubmit'])) {
		$recent = true ;
		if ($_POST['type'] == "all") {
			$alltypesel = "SELECTED" ;
			$typestring = "" ;
		}
		if ($_POST['type'] == "video") {
			$videosel = "SELECTED" ;
			$typestring = "AND (mediatype='video') " ;
		}
	}
	$filterlink = "<div class='top-filter'><form action=\"\" method=\"POST\" name=\"orderform\"><input type=\"hidden\" name=\"keyword\" size=\"15\" value=\"".$keywords."\">" ;
	$filterlink .= "&nbsp;most viewed&nbsp;<select name=\"mostviewed\">
	<option value=\"alltime\" ".$mvalltimesel.">all time</option>
	<option value=\"today\" ".$mvtodaysel.">today</option>
	<option value=\"thisweek\" ".$mvweeksel.">this week</option>
	<option value=\"thismonth\" ".$mvmonthsel.">this month</option>
	</select>&nbsp;<input class=\"biggerbutton2\" type=\"submit\" name=\"mostviewedsubmit\" value=\"go\">&nbsp;&nbsp;" ;
	$filterlink .= "&nbsp;recently uploaded&nbsp;<select name=\"recent\" >
	<option value=\"today\" ".$rctodaysel.">today</option>
	<option value=\"thisweek\" ".$rcweeksel.">this week</option>
	<option value=\"thismonth\" ".$rcmonthsel.">this month</option>
	</select>&nbsp;<input class=\"biggerbutton2\" type=\"submit\" name=\"recentsubmit\" value=\"go\"></div>" ;
	if ($_POST['keyword'] != "") {
		$catres = $db->fetch() ;
		$catid = $catres['id'] ;
		$catQuery = "SELECT * FROM `media` WHERE (`status` ='true')  ".$typestring.$keywordsearch." ORDER BY allviews DESC" ;
		if (($mostviewed) || ($recent)) {
			$catQuery = "SELECT * FROM `media` WHERE (`status` ='true')  ".$typestring.$keywordsearch.$filterstring ;
		}
		$db->query($catQuery) ;
		$output = $filterlink ;
		if ($db->numRows() > 0) {
			$resTR = $db->fetchAll() ;
			$sitefolder = getSetting("sitefolder", $db) ;
			$path = 'http://'.$_SERVER['SERVER_NAME'].$sitefolder.'search' ;
			if ($_GET['keywords'] != '') {
				$path .= '/'.$_GET['keywords'] ;
			}
			else if ($_POST['keyword'] != '') {
				$path .= '/'.$_POST['keyword'] ;
			}
			//Create output for search results
			if (isset($_GET['page']))
				$output .= Tableview(12, $resTR, $_GET['page'], $path, $filter) ;
			else
				$output .= Tableview(12, $resTR, 1, $path, $filter) ;
		}
		else {
			$output .= "<h2>No media to display</h2>" ;
		}
	}
	else {
		$output .= "<h3>Please enter something in the search box</h3>" ;
	}
	return $output ;
}

?>