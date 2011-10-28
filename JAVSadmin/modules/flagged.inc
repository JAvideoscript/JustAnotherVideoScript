<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
include_once("adminfunctions.inc");

if ($_POST['massfunc'] !== "") {
	if ($_POST['massfunc'] == "deleteall") {
		$db->query("SELECT * FROM media")  ;
		$resv = $db->fetchAll() ;
			foreach ($resv as $resCheck) {
				if (isset($_POST['check_all_user'.$resCheck['id']])) {
					$fileid = $resCheck['fileid'] ;
					if ($resCheck['hd'] == "1") {
						unlink($rootpath."uploads/vids/".$fileid."/".$fileid.".mp4") ;
					}
					if ($resCheck['mobile'] == "1") {
						unlink($rootpath."uploads/vids/".$fileid."/mob_".$fileid.".mp4") ;
					}
					unlink($rootpath."uploads/vids/".$fileid."/".$fileid.".flv") ;
					unlink($rootpath."uploads/thumbs/".$fileid.".jpg") ;
					rmdir($rootpath."uploads/vids/".$fileid."/") ;
					$deleteid = $resCheck['id'] ;
					$db->query("DELETE FROM `media` WHERE id = '".$deleteid."'") ;
					echo "Deleted Video with id: $deleteid <br>" ;	
				}
			}
	}
	if ($_POST['massfunc'] == "unflag") {
		$db->query("SELECT * FROM media")  ;
		$resv = $db->fetchAll() ;
		foreach ($resv as $resCheck) {
			if (isset($_POST['check_all_user'.$resCheck['id']])) {
				$unflagid = $resCheck['id'] ;
				$db->query("UPDATE `media` SET `flagged` = '0' WHERE id = '".$unflagid."'") ;
				echo "Unflagged Video with id: $unflagid <br>" ;
			}
		}
	}
}
?>
<script language="javascript">
		function checkUncheckAll(theElement){
		    var theForm = theElement.form, z = 0;
		    for (z = 0; z < theForm.length; z++) {
		        if (theForm[z].type == 'checkbox' && theForm[z].name != 'checkall') {
		            theForm[z].checked = theElement.checked;
		        }
		    }
		}
</script>
<h2>Flagged Videos</h2>
<?php
$db->query("SELECT * FROM media WHERE flagged = '1'") ;
$row = $db->fetchAll() ;

	echo "<form method='post' action=''>" ;
	echo "<table><tr><td align='right'>Mass function:</td>" ;
	echo "<td><select name='massfunc'>" ;
	echo "<option value='deleteall'>Delete all selected</option>" ;
	echo "<option value='unflag' selected>Unflag all selected</option>" ;	
	echo "</select></td><td><input class='biggerbutton' type='submit' value='Go'></td></tr></table>" ;
	echo "<table width='850px' cellspacing='1' cellpadding='3' border='1'><tr>" ;
	echo "<td align='left' width='10px'><b><input type='checkbox' name='checkall' onclick='checkUncheckAll(this);'/></b></td>" ;
	echo "<td align='left' width='25px'><b>Id</b></td>" ;
	echo "<td align='left' width='165px'><b>Thumb</b></td>" ;
	echo "<td align='left' width='150px'><b>Media info</b></td>" ;
	echo "<td align='left' width='40px'><b>Category</b></td>" ;
	echo "<td align='left' width='100px'><b>Video info</b></td>" ;
	echo "<td align='left' width='100px'><b>Addon info</b></td>" ;



	foreach ($row as $key=>$value) {
		$added =  date("m/d/Y h:i:s a", $value['added']);
		if ($value['hd'] == "1") {
			$hdcheck = "yes" ;
		} else {
			$hdcheck = "no" ;
		}
		if ($value['mobile'] == "1") {
			$mobilecheck = "yes" ;
		} else {
			$mobilecheck = "no" ;
		}
		$thumb = "<img src='".$sitepath."uploads/thumbs/".$value['fileid'].".jpg' width='160px' height='120px'>" ;
			
		
		echo "<tr><td align='left'><b><input name='check_all_user".$value['id']."' type='checkbox'></b></td>" ;
		echo "<td align='left'><b>".$value['id']."</b></td>" ;
		echo "<td align='left'>".$thumb."</td>" ;
		echo "<td align='left'>Title: ".$value['title']."<br>Desc: ".$value['description']."<br>Tags: ".$value['tags']."</td>" ;
		echo "<td align='left'>".$value['category']."</td>" ;
		echo "<td align='left'>Poster: ".$value['poster']."<br>Duration: ".$value['duration']."<br>Added: ".$added."</td>" ;
		echo "<td align='left'>Mobile: ".$mobilecheck."<br>HD: ".$hdcheck."</td>" ;
	}
echo "</table></form>" ;

?>