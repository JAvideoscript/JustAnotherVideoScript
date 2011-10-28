<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
session_start();
include_once("adminfunctions.inc");
if (!Beveiliging()){
    echo "Not logged in";
} else {
if (isset($_POST['reset_search'])) {
	unset($_POST, $orderby, $order, $sort) ;
	$query = "SELECT * FROM media WHERE status = 'true'" ;
}
if (isset($_POST['edit'])) {
	if ($_POST['massfunc'] == "") {
		$videoedit = $_POST['editid'] ;
		$db->query("SELECT * FROM media WHERE id = '".$videoedit."'") ;
		$res = $db->fetch() ;
		$editid = $res['id'] ;
		$edittitle = $res['title'] ;
		$editdesc = $res['description'] ;
		$edittags = $res['tags'] ;
		$editcat = $res['category'] ;
		$vidad = $res['vidad'] ;
		echo "<fieldset><ol><form action='' method='post' enctype='multipart/form-data'>" ;
		echo "<li><h2>&nbsp;&nbsp;Edit Video $editid</h2></li>" ;
		echo "<li><label for='edittitle'>Title:</label><input type='text' size='100' name='edittitle' value='$edittitle'></li>" ;
		echo "<li><label for='editdesc'>Desc:</label><input type='text' size='100' name='editdesc' value='$editdesc'></li>" ;
		echo "<li><label for='edittags'>Tags:</label><input type='text' size='100' name='edittags' value='$edittags'></li>" ;
		echo "<li><label for='editcat'>Category:</label><select name='editcat' style='width: 150px'>" ;
					$selected = $editcat ;
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
			
		echo "</select></li>" ;  
		echo "<li><label for='vidad'>Video Ad:</label><textarea rows='5' name='vidad'>".$vidad."</textarea></li>" ;
		echo "<li><label for='submit'>&nbsp;</label><input class='biggerbutton' type='submit' name='submit2' value='Edit video' /></li>" ;
		echo "<input type='hidden' name='editid' value='".$editid."'></form></ol></fieldset>" ;	
	}
}
if (isset($_POST['submit2'])) { 
	$db->query("UPDATE `media` SET title='".$_POST['edittitle']."',description='".$_POST['editdesc']."',tags='".$_POST['edittags']."',category='".$_POST['editcat']."',vidad='".$_POST['vidad']."' WHERE `id` = '".$_POST['editid']."'") ;
	echo "Updated video info to ID: $editid1<br>" ;
}
if (isset($_POST['deletevideo'])) {
	if ($_POST['massfunc'] == "") {
		$videoid = $_POST['deletevideoid'] ;
		$db->query("SELECT * FROM media WHERE id = '".$videoid."'") ;
		$res = $db->fetch() ;
		$fileid = $res['fileid'] ;
		$deleteid = $res['id'] ;
			if ($res['mediatype'] == "video") {
				if ($res['hd'] == "1") {
					unlink($rootpath."uploads/vids/".$fileid."/".$fileid.".mp4") ;
				}
				if ($res['mobile'] == "1") {
					unlink($rootpath."uploads/vids/".$fileid."/mob_".$fileid.".mp4") ;
				}
				unlink($rootpath."uploads/vids/".$fileid."/".$fileid.".flv") ;
				unlink($rootpath."uploads/thumbs/".$fileid.".jpg") ;
				rmdir($rootpath."uploads/vids/".$fileid."/") ;
				$db->query("DELETE FROM `media` WHERE id = '".$deleteid."'") ;
				echo "Deleted Video with id: $deleteid <br>" ;

			} else {
				$db->query("DELETE FROM `media` WHERE id = '".$deleteid."'") ;
				unlink($rootpath."uploads/thumbs/".$fileid.".jpg") ;
				echo "Deleted Embed Video with id: $deleteid <br>" ;
			}
	}
}

if ($_POST['massfunc'] !== "") {
	if ($_POST['massfunc'] == "deleteall") {
		$db->query("SELECT * FROM media")  ;
		$resv = $db->fetchAll() ;
			foreach ($resv as $resCheck) {
				if (isset($_POST['check_all_user'.$resCheck['id']])) {
							$fileid = $resCheck['fileid'] ;
							if ($resCheck['mediatype'] == "video") {
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
							} else {
								$deleteid = $resCheck['id'] ;
								$db->query("DELETE FROM `media` WHERE id = '".$deleteid."'") ;
								unlink($rootpath."uploads/thumbs/".$fileid.".jpg") ;
								echo "Deleted Embed Video with id: $deleteid <br>" ;
							}
						}
			}
				
				
	}


	if ($_POST['massfunc'] == "gendur") {
		$db->query("SELECT * FROM media")  ;
		$resv = $db->fetchAll() ;
			foreach ($resv as $resCheck) {
				if (isset($_POST['check_all_user'.$resCheck['id']])) {
							$genid = $resCheck['id'] ;
							$fileid = $resCheck['fileid'] ;
							if ($resCheck['mediatype'] == "video") {
								$duration = getduration($rootpath."uploads/vids/".$fileid."/".$fileid.".flv") ;
								$db->query("UPDATE `media` SET `duration` = '".$duration."' WHERE id = '".$resCheck['id']."'") ;
								echo "reGenerated duration for video: $genid New duration: $duration <br>" ;
							} else {
								echo "Video with id: $genid is embedded and can't reGenerated duration <br>" ;
							}
						}	
			}				
	}
	if ($_POST['massfunc'] == "genthumb") {
		$db->query("SELECT * FROM media")  ;
		$resv = $db->fetchAll() ;
			foreach ($resv as $resCheck) {
				if (isset($_POST['check_all_user'.$resCheck['id']])) {
					$genid = $resCheck['id'] ;
					$fileid = $resCheck['fileid'] ;
						if ($resCheck['mediatype'] == "video") {
								unlink($rootpath."uploads/thumbs/".$fileid.".jpg") ;
								$ffmpegpath = getSetting("ffmpegpath", $db) ;
								$thumbtime = getSetting("default_thumbtime", $db) ;
								$lw = getSetting("thumb_w1", $db) ;
								$lh = getSetting("thumb_h1", $db) ;
								exec($ffmpegpath." -y -i ".$rootpath."uploads/vids/".$fileid."/".$fileid.".flv -f mjpeg -s ".$lw."x".$lh." -vframes 1 -ss ".$thumbtime." -an ".$rootpath."uploads/thumbs/".$fileid.".jpg") ;
								chmod($rootpath."uploads/thumbs/".$fileid.".jpg", 0755) ;
								echo "New thumb generated for video $genid<br>" ;
							} else {
								echo "Video with id: $genid is embedded and can't reGenerated Thumbs <br>" ;
						}
				}
			}
	}
	if ($_POST['massfunc'] == "unapprove") {
		$db->query("SELECT * FROM media")  ;
		$resv = $db->fetchAll() ;
			foreach ($resv as $resCheck) {
				if (isset($_POST['check_all_user'.$resCheck['id']])) {
					$approveid = $resCheck['id'] ;
					$db->query("UPDATE `media` SET `status` = 'false' WHERE id = '".$approveid."'") ;
					echo "Unapproved Video with id: $approveid <br>" ;
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
<div id="main-content">


<div id="query-menu">
	<form method="post" action="">
	<table width="100%" cellpadding="0" cellspacing="5" border="0">
	
	<tr>
	<td align="right">Title:</td><td><input type="text" name="title" <?php if(isset($_POST['title'])) echo "value='" . $_POST['title'] . "'";?> /></td>
	<td align="right">Description:</td><td><input type="text" name="description" <?php if(isset($_POST['description'])) echo "value='" . $_POST['description'] . "'";?> /></td>
	<td align="right">Poster:</td><td><input type="text" name="poster" <?php if(isset($_POST['poster'])) echo "value='" . $_POST['poster'] . "'";?> /></td>
	</tr>
	
	<tr>
	<td align="right">Category:</td>
	<td>
	<select name="category">
	<option value="-----" <?php if(!isset($_POST['category'])) echo "selected";?>>-----</option>
	<?php
	if (isset($_POST['category']))
		$selected = $_POST['category'] ;
		$sql = "SELECT * FROM `category` ORDER BY name" ;
		$result = mysql_query($sql) or die(mysql_error()) ;
			if ($result) {
				$tmp = '' ;
				while ($row = mysql_fetch_array($result, MYSQL_ASSOC)) {
					$sel = "" ;
					if ($selected == $row['id']) {
						$sel = " selected" ;
					}
					echo "<option$sel value=\"".$row['id']."\">".$row['name']."</option>" ;
				}
			}
	?>
	</select>
	</td>

	<td align="right">Order BY:</td>
	<td>
	<select name="orderby">
	<option value="id" <?php if(!isset($_POST['orderby'])) echo "selected";?><?php if($_POST['orderby'] == "id") echo "selected";?>>ID</option>
	<option value="added" <?php if($_POST['orderby'] == "added") echo "selected";?>>Added</option>
	<option value="allviews" <?php if($_POST['orderby'] == "allviews") echo "selected";?>>Allviews</option>
	<option value="lastviewed" <?php if($_POST['orderby'] == "lastviewed") echo "selected";?>>Lastviewed</option>
	<option value="duration" <?php if($_POST['orderby'] == "duration") echo "selected";?>>Duration</option>
	<option value="cat" <?php if($_POST['orderby'] == "cat") echo "selected";?>>Category</option>
	</select>
	</td>
	
	<td align="right">Order:</td>
	<td>
	<select name="order">
	<option value="desc" <?php if(!isset($_POST['order'])) echo "selected";?><?php if($_POST['order'] == "desc") echo "selected";?>>DESC</option>
	<option value="asc" <?php if($_POST['order'] == "asc") echo "selected";?>>ASC</option>
	</select>
	</td>
	</tr>

	<tr>
	<td align="right">HD/mobile:</td>
	<td>
	<select name="hdmobile">
	<option value="all" <?php if(!isset($_POST['hdmobile'])) echo "selected";?><?php if($_POST['hdmobile'] == "all") echo "selected";?>>All</option>
	<option value="mobile" <?php if($_POST['hdmobile'] == "mobile") echo "selected";?>>Mobile</option>
	<option value="hd" <?php if($_POST['hdmobile'] == "hd") echo "selected";?>>HD</option>
	</select>
	</td>

	<td align="right">Video/embed:</td>
	<td>
	<select name="videoembed">
	<option value="all" <?php if(!isset($_POST['videoembed'])) echo "selected";?><?php if($_POST['videoembed'] == "all") echo "selected";?>>All</option>
	<option value="video" <?php if($_POST['videoembed'] == "video") echo "selected";?>>Video</option>
	<option value="embed" <?php if($_POST['videoembed'] == "embed") echo "selected";?>>Embed</option>
	</select>
	</td>
	
	
	<td align="right">pages:</td>
	<td>
	<select name="pages">
	<option value="10" <?php if($_POST['pages'] == "10") echo "selected";?>>10</option>
	<option value="25" <?php if(!isset($_POST['pages'])) echo "selected";?><?php if($_POST['pages'] == "25") echo "selected";?>>25</option>
	<option value="50" <?php if($_POST['pages'] == "50") echo "selected";?>>50</option>
	<option value="100" <?php if($_POST['pages'] == "100") echo "selected";?>>100</option>
	</select>
	</td>
	
	</tr>
	
	<tr>
	<td>
	<input type="submit" value="search" />
	<input type="submit" name="reset_search" value="clear" />
	</td>
 
	</tr>
	</table>
	</form>
	</div>

	
	<?php
	$sort = '' ;
	$query = "SELECT * FROM media WHERE status = 'true'" ;
if (isset($_POST['title'])) { 
	if ($_POST['title'] !== "") {
		$sort .= " AND (title LIKE  '%".$_POST['title']."%')" ;
	}
}
if (isset($_POST['description'])) { 
	if ($_POST['description'] !== "") {
		$sort .= " AND (description LIKE  '%".$_POST['desc']."%')" ;
	}
}
if (isset($_POST['poster'])) { 
	if ($_POST['poster'] !== "") {
		$sort .= " AND (poster LIKE  '%".$_POST['poster']."%')" ;
	}
}
if (isset($_POST['category'])) { 
	if ($_POST['category'] !== "-----") {
		$sort .= " AND (category = '".$_POST['category']."')" ;
	}
}
if (isset($_POST['orderby'])) {
		switch ($_POST['orderby']) {
			case "id":
				$orderby = " ORDER BY id" ;
			break ;
			case "added":
				$orderby = " ORDER BY added" ;
			break ;
			case "allviews":
				$orderby = " ORDER BY allviews" ;
			break ;
			case "lastviewed":
				$orderby = " ORDER BY lastviewed" ;
			break ;
			case "duration":
				$orderby = " ORDER BY duration" ;
			break ;
			case "cat":
				$orderby = " ORDER BY category" ;
			break ;
		}
}
if ($_POST['order'] !== "") {
	switch ($_POST['order']) {
		case "asc":
			$order .= " ASC" ;
		break ;
		case "desc":
			$order .= " DESC" ;
		break ;
	}
}
if ($_POST['hdmobile'] !== "") {
	switch ($_POST['hdmobile']) {
			case "all":
			break ;
			case "hd":
				$sort .= " AND (hd = '1')" ;
			break ;
			case "mobile":
				$sort .= " AND (mobile = '1')" ;
			break ;
	}
}
if ($_POST['videoembed'] !== "") {
	switch ($_POST['videoembed']) {
			case "all":
			break ;
			case "video":
				$sort .= " AND (mediatype = 'video')" ;
			break ;
			case "embed":
				$sort .= " AND (mediatype = 'embed')" ;
			break ;
	}
}
if (isset($_POST['reset_search'])) {
	$query = "SELECT * FROM media WHERE status = 'true'" ;
}
if ($orderby == "") {
	$orderby = " ORDER BY id DESC" ;
}
	
echo "Query: $query $sort $orderby $order <br>" ;
$db->query($query.$sort.$orderby.$order) ;
$numresults = $db->numRows() ;
$resultar = array() ;
$row = $db->fetchall() ;
if ($numresults == "0") {
	echo "<h2>No Results</h2>" ;
} else {
	foreach($row as $value) {
		$added = date("m/d/Y h:i:s a", $value['added']);
		$db->query("SELECT name FROM category WHERE id='".$value['category']."' ") ;
		$cat = $db->fetch() ;
		
		if ($value['flagged'] == "1") {
			$flagged = "yes" ;
		} else {
			$flagged = "no" ;
		}
		if ($value['lastviewed'] == "0") {
			$lastviewed = "0" ;
		} else {
			$lastviewed = date("m/d/Y h:i:s a", $value['lastviewed']);
		}
		$thumb = "<img src='".$sitepath."uploads/thumbs/".$value['fileid'].".jpg' width='160px' height='120px'>" ;
		
		
		if ($value['vidad'] == "") {
			$vidad = "No" ;
		} else {
			$vidad = "Yes";
		}		

		$idarray = array(
			id=>$value['id'],
			title=>$value['title'],
			description=>$value['description'],
			tags=>$value['tags'],
			cat=>$cat['name'],
			poster=>$value['poster'],
			added=>$added,
			thumb=>$thumb,
			mobile=>$value['mobile'],
			hd=>$value['hd'],
			mediatype=>$value['mediatype'],
			viewstoday=>$value['dayviews'],
			viewsweek=>$value['weekviews'],
			viewsmonth=>$value['monthviews'],
			viewsall=>$value['allviews'],
			flagged=>$flagged,
			lastviewed=>$lastviewed,
			duration=>$value['duration'],
			vidad=>$vidad);
		array_push($resultar, $idarray) ;


	} //end foreach loop
	
	if (isset($_POST['pages'])) {
		$max_page = $_POST['pages'] ;
	} else {
		$max_page = "25" ;
	}
	
	$numberarray = count($resultar); 
	$count_pages = $numberarray / $max_page ;
	$pages = ceil($count_pages) ;
	
	if(isset($_GET['page_id'])) { 
	    $page = $_GET['page_id'];
	} else {
	    $page = "1";
	}
	if ($page > $pages) {
		$page = $pages ;
	}
	
	$end = $page * $max_page; 
	$start = $end - $max_page; 
	$end = $end - 1 ;
	
	if ($end > $numresults) {
		$end = $numresults - 1 ;
	}

	//set page lines
	
	if ($page > "1") {
	    $Prev_Page = $page - 1;
	    $Prev_Page = '<a href="'.$_SERVER['PHP_SELF'].'?do=allvideos&sub=users&page_id='.$Prev_Page.'">&laquo; Previous Page</a>&nbsp;';
	    echo $Prev_Page;
	} else {
	    echo '';
	}
	$rijtje = '';

	for ($i = 1; $i <= $pages; $i++) {
	
	    if ($i == $page) {
	        
	        $rijtje .= '<b>'.$i.'</b>';
	    }
	    
	    else {
	        $rijtje .= '<a href="'.$_SERVER['PHP_SELF'].'?do=allvideos&sub=users&page_id='.$i.'">'.$i.'</a>&nbsp;';
	    }
	} 
	echo '&nbsp;'; echo $rijtje; echo '&nbsp;';
	if ($page < $pages) {
	    
	    $Next = $page + 1;
	    $Next = '<a href="'.$_SERVER['PHP_SELF'].'?do=allvideos&sub=users&page_id='.$Next.'">Next Page &raquo;</a>';
	    echo $Next;
	} else {
	    echo '';
	}
	?>
	<div id="query-content">

	<form method="post" action="">
	<table>
	<tr>
			<td align="right">Mass function:</td>
			<td>
			<select name="massfunc">
			<option value="deleteall" selected>Delete selected</option>
			<option value="genthumb">reGenerate thumb</option>
			<option value="gendur">reGenerate Duration</option>
			<option value="unapprove" >unapprove</option>
			
			</select>
			</td>
	<td><input class="biggerbutton" type="submit" value="Go"/></td></tr>
	
	
	</table>
	<table width="850px" cellspacing="1" cellpadding="3" border="1">
	<tr>
				<td align="center" width="15px"><b><input type="checkbox" name="checkall" onclick="checkUncheckAll(this);"/></b></td>
				<td align="center" width="15px"><b>Id</b></td>
				<td align="center" ><b>Video desc</b></td>
				<td align="center" width="162px"><b>Thumb</b></td>
				<td align="center" ><b>Video Info</b></td>
				<td align="center" width="85px"><b>Views</b></td>
				<td align="center" width="50px"><b>Action</b></td>
				
		</tr>
	
	<?php

	for ($f = $start; $f <= $end; $f++) {
		$action = '<form action="" method="POST">' ;
			$action .= '<input type="submit" class="biggerbutton" name="deletevideo" value="Delete">' ;
			$action .= '<input type="hidden" name="deletevideoid" value="'.$resultar[$f][id].'">' ;
		$action .= '</form>' ;
		$action .= '<form action="" method="POST">' ;
			$action .= '<input type="submit" class="biggerbutton" name="edit" value="Edit">' ;
			$action .= '<input type="hidden" name="editid" value="'.$resultar[$f][id].'">' ;
		$action .= '</form>' ;	
	?>
	
	<tr>
	<td align="left"><b><input name="check_all_user<?=$resultar[$f][id]?>" type="checkbox"></b></td>
		<td align="left"><b><?=$resultar[$f][id]?></b></td>
		<td align="left">Title: <?=$resultar[$f][title]?><br>Desc: <?=$resultar[$f][description]?><br>Tags: <?=$resultar[$f][tags]?><br>Category: <?=$resultar[$f][cat]?><br>Poster: <?=$resultar[$f][poster]?><br>Added: <?=$resultar[$f][added]?><br>Mediatype: <?=$resultar[$f][mediatype]?><br></td>
		<td align="left"><?=$resultar[$f][thumb]?></td>
		<td align="left">Mobile: <?=$resultar[$f][mobile]?><br>HD: <?=$resultar[$f][hd]?><br>Flagged: <?=$resultar[$f][flagged]?><br>Duration: <?=$resultar[$f][duration]?><br>Lastviewed: <?=$resultar[$f][lastviewed]?><br>Video AD: <?=$resultar[$f][vidad]?><br></td>
		
		<td align="left">Allviews: <?=$resultar[$f][viewsall]?><br>Today: <?=$resultar[$f][viewstoday]?><br>Week: <?=$resultar[$f][viewsweek]?><br>Month: <?=$resultar[$f][viewsmonth]?><br></td>
		
		<td align="left"><?=$action ?></td>		
	</tr>
	
<?php
}




?>
	

	</table>
	</form>
	</div>
	




</div>
<?php
}
}
?>

