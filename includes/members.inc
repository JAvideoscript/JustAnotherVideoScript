<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
require_once "includes/tablefunction.inc" ;
	$db->query("SELECT * FROM sitead WHERE adname='ad11'") ;
		if ($db->numRows() > 0) {
			$ares = $db->fetch() ;
			$ad11 = $ares['adtext'] ;
			if ($ad11 != '') {
				$ad11 = '<div id="adsecond728x90">'.$ad11.'</div>' ;
			}
		}
function memberList() {
	global $db,$template,$sitepath,$loggedIn ;
	$site_template = getSetting("sitetemplate", $db) ;
	$template_file = "templates/".$site_template."/members_content.php" ;

		$filter = 'all' ;
		if ($_GET['filter'] != "") {
			$filter = $_GET['filter'] ;
		}
		$search = '' ;
		$nsearchvar = '' ;
		$lsearchvar = '' ;
		$searchurl = '' ;
		$sort = " ORDER BY `created` DESC" ;
		$newsel = " SELECTED" ;
		if ($_GET['lsearch'] != "") {
			$lsearchvar = $_GET['lsearch'] ;
		}
		if ($_GET['nsearch'] != "") {
			$nsearchvar = $_GET['nsearch'] ;
		}
		if ($_POST['namesearch'] != "") {
			$nsearchvar = quote_smart($_POST['namesearch']) ;
		}
		if ($_POST['locationsearch'] != "") {
			$lsearchvar = quote_smart($_POST['locationsearch']) ;
		}
		$newsel = "" ;
		$logsel = "" ;
		if (isset($_POST['namesearch'])) {
			$nsearchvar = quote_smart($_POST['namesearch']) ;
		}
		if (isset($_POST['locationsearch'])) {
			$lsearchvar = quote_smart($_POST['locationsearch']) ;
		}
		if ($_POST['membersort'] == 'newest') {
			$sort = " ORDER BY `created` DESC" ;
			$newsel = " SELECTED" ;
		}
		if ($_POST['membersort'] == 'login') {
			$sort = " ORDER BY `lastlogin` DESC" ;
			$logsel = " SELECTED" ;
		}
		$searchurl = $sitepath."members/_".$filter ;
		if ($nsearchvar != '') {
			$search .= " AND (username LIKE '%".$nsearchvar."%')" ;
			$searchurl .= "/__".urlencode($nsearchvar) ;
		}
		if ($lsearchvar != '') {
			$search .= " AND (location LIKE '%".$lsearchvar."%')" ;
			$searchurl .= "/___".urlencode($lsearchvar) ;
		}
		$query = "SELECT * FROM member WHERE (activationkey=0)" ;
		if ($_POST['agefilter'] == "") {
			$agefilter = "all" ;
			$sellall = " SELECTED" ;
		}
		else {
			$agefilter = quote_smart($_POST['agefilter']) ;
		}
		switch ($agefilter) {
			case "u18":
				$query .= " AND (age<18)" ;
				$sel_u18 = " SELECTED" ;
				break ;
			case "1825":
				$query .= " AND (age>=18 AND age<=25)" ;
				$sel_1825 = " SELECTED" ;
				break ;
			case "2635":
				$query .= " AND (age>=26 AND age<=35)" ;
				$sel_2635 = " SELECTED" ;
				break ;
			case "3650":
				$query .= " AND (age>=36 AND age<=50)" ;
				$sel_3650 = " SELECTED" ;
				break ;
			case "5165":
				$query .= " AND (age>=51 AND age<=65)" ;
				$sel_5165 = " SELECTED" ;
				break ;
			case "o65":
				$query .= " AND (age>65)" ;
				$sel_o65 = " SELECTED" ;
				break ;
		}
		if ($_POST['genderfilter'] == "") {
			$genderfilter = "all" ;
			$sel_either = " SELECTED" ;
		}
		else {
			$genderfilter = quote_smart($_POST['genderfilter']) ;
		}
		switch ($genderfilter) {
			case "male":
				$query .= " AND (gender=0)" ;
				$sel_male = " SELECTED" ;
				break ;
			case "female":
				$query .= " AND (gender=1)" ;
				$sel_female = " SELECTED" ;
				break ;
		}
		$query .= $search.$sort ;
		$output = "<form action=\"".$searchurl."\" method=\"post\" name=\"memberform\">
	<div align=left>
	age filter&nbsp;
	<select name=\"agefilter\" onChange='document.forms[\"memberform\"].submit();'>
	<option value=\"all\"".$sel_all.">any age</option>
	<option value=\"u18\"".$sel_u18.">under 18</option>
	<option value=\"1825\"".$sel_1825.">18-25</option>
	<option value=\"2635\"".$sel_2635.">26-35</option>
	<option value=\"3650\"".$sel_3650.">36-50</option>
	<option value=\"5165\"".$sel_5165.">51-65</option>
	<option value=\"o65\"".$sel_o65.">over 65</option>
	</select>
	gender filter&nbsp;
	<select name=\"genderfilter\" onChange='document.forms[\"memberform\"].submit();'>
	<option value=\"either\"".$sel_either.">either gender</option>
	<option value=\"male\"".$sel_male.">male</option>
	<option value=\"female\"".$sel_female.">female</option>
	</select>
	sort by&nbsp;
	<select name=\"membersort\" onChange='document.forms[\"memberform\"].submit();'>
	<option value=\"newest\"".$newsel.">newest members</option>
	<option value=\"login\"".$logsel.">last login</option>
	</select>
	</div><br />search username <input type=\"text\" size=\"30\" name=\"namesearch\" value=\"".$nsearchvar."\" /> search location <input type=\"text\" size=\"30\" name=\"locationsearch\" value=\"".$lsearchvar."\" /><input type=\"submit\" class=\"biggerbutton\" name=\"formsubmit\" value=\"search\" /></form>".$filterlink ;
		$db->query($query) ;
		$resLV = $db->fetchAll() ;
		//Create output for member list results
		if (isset($_GET['page'])) {
			$output .= Tableview(10, $resLV, $_GET['page'], $searchurl) ;
		} else {
			$output .= Tableview(10, $resLV, 1, $searchurl) ;
		}
		return $output ;

}
?>