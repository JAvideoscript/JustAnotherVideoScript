<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
function catlist() {
	global $db,$sitepath,$templateimagepath ;
	$db->query("SELECT * FROM `category` ORDER BY name") ;
	$res = $db->fetchAll() ;
	
	$output = '<ul class="catelist">' ;
	foreach($res as $value) {
		$db->query("SELECT * FROM `media` WHERE category = '".$value['id']."'") ;
		$number = $db->numRows() ;
		$catname = str_replace(" ", "-", trim($value['name'])) ;
		if (file_exists($rootpath.'uploads/category/'.$catname.'.jpg')) {
			$thumb = $sitepath."uploads/category/".$catname.".jpg" ;
		} else {
			$thumb = $templateimagepath."defaultcat.jpg" ;
		}

		$output .= '<li><a href="'.$sitepath.'category/'.$catname.'"><img src="'.$thumb .'" width="160" height="226" alt="'.$value['name'].'" /></a><br/><a href="'.$sitepath.'category/'.$catname.'"><h3>'.$catname.'<span> ('.$number.')</span></h3></a></li>' ;
		
	}
	$output .= '</ul>' ;
return $output ;
}

?>
