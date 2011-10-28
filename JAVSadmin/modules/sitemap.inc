<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
include_once("adminfunctions.inc");

if (isset($_POST['submit'])) { 
		$db->query("SELECT id,name FROM category") ;
		$rowCAT = $db->fetchAll() ;
		$numrows = $db->numrows() ;
		echo "There are $numrows sitemaps made <br>" ;
			$siteoutput = '<?xml version="1.0" encoding="UTF-8"?>' ;
			$siteoutput .= '<sitemapindex xmlns="http://www.sitemaps.org/schemas/sitemap/0.9">' ;
			$datelast = gmdate("Y-m-d", time())."T".gmdate("H:i:s", time())."+01:00"  ;
	
			foreach ($rowCAT as $key=>$value) {
				$db->query("SELECT * FROM media WHERE category = '".$value['id']."' AND status = 'true' ORDER BY id DESC") ;
				$rowmedia = $db->fetchAll() ;
				$catname = $value['name'] ;
				if ($rowmedia) {
				$catname = str_replace(" ", "_", trim($catname)) ;
				
					sitemapper($rowmedia, $catname) ;
					$siteoutput .= '<sitemap><loc>'.$sitepath.'sitemap/'.$catname.'.xml</loc><lastmod>'.$datelast.'</lastmod></sitemap>' ;
					echo "Sitemap $catname is made <br>" ;
				} else {
					echo "Sitemap $catname was empty and ignored<br>" ;
				}
	
			 }
			$siteoutput .= '</sitemapindex>' ;
			if ($siteoutput) {
				$file = $rootpath.'sitemap/sitemap.xml' ;
				$fp = fopen($file, "w");
				fwrite($fp, $siteoutput);
				fclose($fp);
				echo "Sitemap is made<br>" ;
			}
}
?>
<fieldset>
	<ol>
	<form action="" method="post" enctype="multipart/form-data">
	<input class="biggerbutton" type="submit" name="submit" value="Create sitemap" />
	</form>
	</ol>
</fieldset>	
	


