<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script which is based on vidiscript.
 *    Come to website for support or buying additional plugins/modules.
 */
include_once("adminfunctions.inc");
if (isset($_POST['submit'])) {
	$x = $_POST['filenumber'] ;
	for ($b = 1; $b <= $x; $b++) {
	
		if (!empty($_POST["title$b"]) && !empty($_POST["tags$b"]) && !empty($_POST["desc$b"])) {

			$title = trim($_POST["title$b"]) ;
			$desc = trim($_POST["desc$b"]) ;
			$tags = trim($_POST["tags$b"]) ;
			$cat = $_POST["catergorie$b"] ;
			$filename = $_POST["filename$b"] ;
			$videoad = trim($_POST["videoad$b"]) ;

			if (file_exists($rootpath.'uploads/import/'.$filename)) {
				$encodeset = crc32(rand(100,999).time()) ;
				$ext = strtolower(substr($filename, strrpos($filename, '.') + 1)) ;
				$fileid = $encodeset.".".$ext ;
				rename($rootpath."uploads/import/".$filename, $rootpath."uploads/encode/".$fileid) ;
				$added = time() ;
				$status = "encode" ;
				$poster = "importer";
				$sql = "INSERT INTO `media` (title, category, description, tags, fileid, poster, added, status, mediatype, videoad) VALUES ('".$title."', '".$cat."', '".$desc."', '".$tags."', '".$fileid."', '".$poster."', '".$added."', '".$status."', 'video', '".$videoad."')" ;
				$db->query($sql) ;
				if (getSetting("directencode", $db) == '1') {	
					$cronpass = getSetting("passcron", $db) ;
					$curlpath = getSetting("curlpath", $db) ;
					$cmd = $curlpath. " " .$sitepath. "includes/encode.php?cronpass=" .$cronpass ;
					$curldo = 'true' ;
				}
				echo "File: $filename is now added to the site" ;
			}
			
		} 
	}
	
	if ($curldo == 'true') {
		exec($cmd. ">/dev/null &");
	}
}
?>
<fieldset>		
	<ol>
	<form action="" method="post" enctype="multipart/form-data">
					
	<div class="import">
		
		
		<?php
			$filelist = importlist();
			$countfiles = count($filelist) ;
			if ($countfiles == "0") {  
				echo "No files in dir Import, go upload some" ;
			}
				foreach($filelist as $value) {
					$count++;
					$playvideo = $sitepath."uploads/import/".$value ;
					$filenamehead = $value ;

					echo "<a class='menuitem submenuheader'>".$filenamehead."</a>" ;
					echo "<div class='submenu'><ul>" ;
					echo "Filename: $filenamehead " ;
					
					$title = str_replace(".flv", "", trim($filenamehead)) ;
					$title = str_replace("-", " ", $title) ;
					$title = str_replace("_", " ", $title) ;
					$tags = str_replace(" ", ", ", $title) ;
					
echo "<table>" ;
echo "<tr><td align='left'>Title:</td><td><input size='100' name='title".$count."' type='text' value='".$title."' /></td></tr>" ;
echo "<tr><td align='left'>Description:</td><td><input size='100' name='desc".$count."' type='text' value='".$title."' /></td></tr>" ;
echo "<tr><td align='left'>Tags:</td><td><input size='100' name='tags".$count."' type='text' value='".$tags."' /></td></tr>" ;
echo "<tr><td align='left'>Video Ad:</td><td><textarea rows='5' name='videoad".$count."'>".$videoad."</textarea></td></tr>" ;
echo "<tr><td align='left'>Category:</td><td><select name='catergorie".$count."'>" ;
if (isset($_POST['catergorie']))
	$selected = $_POST['catergorie'] ;
	$sql = "SELECT * FROM `category` ORDER BY name" ;
	$result = mysql_query($sql) or die(mysql_error()) ;
	if ($result) {
		$tmp = '' ;
		while ($row = mysql_fetch_array($result, MYSQL_ASSOC)) {
			$sel = "" ;
			if ($selected == $row['id'])
			$sel = " selected" ;
			echo "<option$sel value=\"".$row['id']."\">".$row['name']."</option>" ;
		}
	}
			
echo "</select></td></tr>" ;
echo "<input type='hidden' name='filename".$count."' value='".$filenamehead."' />" ;
echo "</table>" ;
echo "</ul></div>" ;
						
	}
		
		?>
		
		
				
				
				
	</div>
		
		
		
<?php
	if ($countfiles >= "1") {
		echo "<li><label for='submit'>&nbsp;</label>" ;
		echo "<input type='hidden' name='filenumber' value='".$countfiles."' />" ;
		echo "<input class='biggerbutton' type='submit' name='submit' value='Add video' /></li>" ;
	}		
?>

	</form>
	</ol>
</fieldset>

