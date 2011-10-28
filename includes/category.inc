<? 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
global $db,$categoryName ;
require_once "includes/tablefunction.inc" ;
$maincategory = str_replace("-", " ", $_GET['crw']) ;
if ($maincategory != '') {
      $db->query("SELECT id from category WHERE name='".quote_smart($maincategory)."'") ;
      $cres = $db->fetch() ;
      $catid = $cres['id'] ;
      $categoryName = $maincategory ;
      $catnameh2 = $categoryName;
}

if (isset($_POST['mostviewed'])) {
	    if ($_POST['mostviewed'] == "alltime") {
                  $mvalltimesel = "SELECTED" ;
                  $filter = "all" ;
		$reply = categoryMedia($filter);	
            }
            if ($_POST['mostviewed'] == "today") {
                  $mvtodaysel = "SELECTED" ;
                  $filter = "today" ;
                  $reply = categoryMedia($filter);
            }
            if ($_POST['mostviewed'] == "thisweek") {
                  $mvweeksel = "SELECTED" ;
                  $filter = "week" ;
                  $reply = categoryMedia($filter);
            }
            if ($_POST['mostviewed'] == "thismonth") {
                  $mvmonthsel = "SELECTED" ;
                  $filter = "month" ;
                  $reply = categoryMedia($filter);
            }
} else {
	$mvalltimesel = "SELECTED" ;
	$filter = "all" ;
	$reply = categoryMedia($filter);
}


function categoryMedia($querytest) {
      global $db,$sitepath ;

	switch($querytest) {
		case 'all':
			$filterstring = "ORDER BY allviews DESC" ;
		break ;
		case 'today':
			 $filterstring = "ORDER BY dayviews DESC" ;
		break ;
		case 'week':
			 $filterstring = "ORDER BY weekviews DESC" ;
		break ;
		case 'month':
			 $filterstring = "ORDER BY monthviews DESC" ;
		break ;
	}
	
	
	$category = str_replace("-", " ", $_GET['crw']) ;
	if ($category != '') {
		$db->query("SELECT id from category WHERE name='".quote_smart($category)."'") ;
		$cres = $db->fetch() ;
		$catid = $cres['id'] ;
	}


		$db->query("SELECT * FROM `media` WHERE (`status` = 'true') AND (`category` = '".$catid."') ".$filterstring) ;
		$resLV = $db->fetchAll() ;

			$path = $sitepath."category/$category" ;
			if (isset($_GET['page'])) {
				$output = Tableview(11, $resLV, $_GET['page'], $path,$querytest) ;
			} else {
				$output = Tableview(11, $resLV, 1, $path,$querytest) ;
			}

      return $output ;
}
?>
