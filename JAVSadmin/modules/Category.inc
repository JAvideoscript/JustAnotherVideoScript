<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
include_once("adminfunctions.inc");
$site_template = getSetting("sitetemplate", $db) ;
$templateimagepath = $sitepath.'templates/'.$site_template.'/images/' ;
if (isset($_POST['catdelete'])) {
	$catdelete = $_POST['catdelete'] ;
	$db->query("DELETE FROM category WHERE id = '".$catdelete."' ") ;
	echo "Category is deleted" ;

}
if (isset($_POST['submit'])) { 
	$halt = "no" ;
	$catname = $_POST['catname'] ;
	if ($catname == '') {
		$halt = "yes" ;
		echo "Enter a Category name" ;
	}
	$db->query("SELECT * FROM category") ;
		$res = $db->fetchAll() ;
		foreach ($res as $key=>$value) {
			if ($value['name'] == $catname) {
				echo "Catname $catname already exist" ;
				$halt = "yes" ;
			}	
		}
		
	if ($halt == "no") {
		echo "Category with name: $catname is now created" ;
		$db->query("INSERT INTO `category` (name) VALUES ('".$catname."')") ;
		unset($catname);
	}

}
if (isset($_POST['catedit'])) {
	$catedit = $_POST['catedit'] ;
	$db->query("SELECT * FROM category WHERE id = '".$catedit."'") ;
	$res = $db->fetch() ;
	$editcatid = $res['id'] ;
	$editcatname = $res['name'] ;
	echo "<fieldset><ol><form action='' method='post' enctype='multipart/form-data'>" ;
	echo "<li><h2>&nbsp;&nbsp;Edit category</h2></li>" ;
	echo "<li><label for='editcatid'>Cat ID:</label><input type='text' size='100' name='editcatid' value='$editcatid'></li>" ;
	echo "<li><label for='editcatname'>Name:</label><input type='text' size='100' name='editcatname' value='$editcatname'></li>" ;
	echo "<li><label for='submit'>&nbsp;</label><input class='biggerbutton' type='submit' name='submit2' value='edit' /></li>" ;
	echo "<input type='hidden' name='oldeditid' value='".$editcatid."'></form></ol></fieldset>" ;
}
if (isset($_POST['submit2'])) { 
	$editid1 = $_POST['editcatid'] ;
	$editcat1 = $_POST['editcatname'] ;
	$oldeditid = $_POST['oldeditid'] ;
	$db->query("UPDATE `category` SET id='".$editid1."',name='".$editcat1."' WHERE `id` = '".$oldeditid."'") ;
	echo "Updated catergoy to ID: $editid1 Name: $editcat1 <br>" ;
}


if (isset($_POST['thumbedit'])) {
	$db->query("SELECT * FROM category WHERE id = '".$_POST['thumbedit']."'") ;
	$res = $db->fetch() ;
	
	$thumbid = $res['id'] ;
	$thumbname = $res['name'] ;

	echo "<fieldset><ol><form action='' method='post' enctype='multipart/form-data'>" ;
	echo "<li><h2>&nbsp;&nbsp;Edit Thumb</h2></li>" ;
	echo "<li><label for='newavatar'>Avatar 160x226px:</label> <input class='filebox' size='60' name='newavatar' type='file' /></li>" ;
	echo "<li><label for='submit'>&nbsp;</label><input class='biggerbutton' type='submit' name='submit3' value='Upload' /></li>" ;
	echo "<input type='hidden' name='thumbid' value='".$thumbid."'><input type='hidden' name='thumbname' value='".$thumbname."'></form></ol></fieldset>" ;
}

if (isset($_POST['submit3'])) { 
	$thumbid = $_POST['thumbid'] ;
	$thumbname = $_POST['thumbname'] ;
	$newavatar = $_FILES['newavatar']['name'] ;
	$allowed_filetypes = array('.jpg','.gif','.png');
	$catname = str_replace(" ", "-", trim($thumbname)) ;
	$upload_path = $rootpath."uploads/category/" ;
	$max_filesize = getsetting("maxsizememberavatar", $db) * 1024;
	$ext = substr($newavatar, strpos($newavatar,'.'), strlen($newavatar)-1);
		if(!in_array($ext,$allowed_filetypes)) {
			echo "Not a valid file extension only .jpg .png .gif";
		} else {
			if(filesize($_FILES['newavatar']['tmp_name']) >= $max_filesize) {
				echo "The avatar file is too big, maxium size: $max_filesize";
			 } else {
			 	if (file_exists($rootpath.'uploads/category/'.$catname.'.jpg')) {
			 		unlink($rootpath.'uploads/category/'.$catname.'.jpg') ;
			 	}
			 	if(move_uploaded_file($_FILES['newavatar']['tmp_name'],$upload_path . $newavatar)) {
					require_once "../includes/imagefunctions.inc" ;
					$avatarfilename = $catname.".jpg" ;

					//crazy fix
					rename($rootpath."uploads/category/".$newavatar, $rootpath."uploads/category/temp".$ext) ;
					//resize the picture
					createThumb("temp.jpg", "226", "160", $rootpath."uploads/category/", $avatarfilename);
					
					//remove temp
					if (file_exists($rootpath.'uploads/category/temp.jpg')) {
						unlink($rootpath.'uploads/category/temp.jpg');
					}
						
					
				}
			}
		
		}



}








?>
<fieldset>
	<ol>
	<form action="" method="post" enctype="multipart/form-data">
		<li>
				<h2>&nbsp;&nbsp;Create category</h2>
		</li>
		<li>
				<label for="catname">Category Name:</label>
				<input type="text" size="100" name="catname" value="<?=$catname?>">
		</li>		
		<li>
				<label for="submit">&nbsp;</label>
				<input class="biggerbutton" type="submit" name="submit" value="Create" />
		</li>
	</form>
	</ol>
</fieldset>

<?php



	echo "<form method='post' action=''>" ;
	echo "<table width='850px' cellspacing='1' cellpadding='3' border='1'><tr>" ;

	echo "<td align='left'><b>Id</b></td>" ;
	echo "<td align='left'><b>Cat Name</b></td>" ;
	echo "<td align='left'><b>Cat Thumb</b></td>" ;
	echo "<td align='left'><b>Actions</b></td>" ;


	$db->query("SELECT * FROM category") ;
	$res2 = $db->fetchAll() ;
		foreach ($res2 as $key=>$value2) {
			
			$action1 = '<form action="" method="POST">' ;
			$action1 .= '<input type="submit" class="biggerbutton" name="catdelete" value="Delete">' ;
			$action1 .= '<input type="hidden" name="catdelete" value="'.$value2['id'].'">' ;
			$action1 .= '</form>' ;
					
			$action2 = '<form action="" method="POST">' ;
			$action2 .= '<input type="submit" class="biggerbutton" name="catedit" value="Edit">' ;
			$action2 .= '<input type="hidden" name="catedit" value="'.$value2['id'].'">' ;
			$action2 .= '</form>' ;
			
			$action3 = '<form action="" method="POST">' ;
			$action3 .= '<input type="submit" class="biggerbutton" name="thumbedit" value="Thumb change">' ;
			$action3 .= '<input type="hidden" name="thumbedit" value="'.$value2['id'].'">' ;
			$action3 .= '</form>' ;			

			echo "<tr><td align='left'><b>".$value2['id']."</b></td>" ;
			echo "<td align='left'>".$value2['name']."</td>" ;
			
			$catname = str_replace(" ", "-", trim($value2['name'])) ;
			
			if (file_exists($rootpath.'uploads/category/'.$catname.'.jpg')) {
				$thumb = "<img src='".$sitepath."uploads/category/".$catname.".jpg' width='160px' height='226px'>" ;	
			} else {
				$thumb = "<img src='".$templateimagepath."defaultcat.jpg' width='160px' height='226px'>" ;
			}

			echo "<td align='left'>".$thumb."</td>" ;
			
			echo "<td align='left'>".$action1.$action2.$action3."</td></tr>" ;
			
		
		
		}
echo "</table></form>" ;
		
?>