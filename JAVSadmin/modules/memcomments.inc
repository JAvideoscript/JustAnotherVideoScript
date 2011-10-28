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
		$db->query("SELECT * FROM media_comment")  ;
		$resv = $db->fetchAll() ;
			foreach ($resv as $resCheck) {
				if (isset($_POST['check_all_user'.$resCheck['id']])) {
					$deleteid = $resCheck['id'] ;
					$db->query("DELETE FROM `media_comment` WHERE id = '".$deleteid."'") ;
					echo "Deleted comment with id: $deleteid <br>" ;	
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
<h2>Video Comments</h2>
<?php
$db->query("SELECT * FROM media_comment ORDER BY id DESC") ;
$row = $db->fetchAll() ;

	echo "<form method='post' action=''>" ;
	echo "<table><tr><td align='right'>Mass function:</td>" ;
	echo "<td><select name='massfunc'>" ;
	echo "<option value='deleteall'>Delete all selected</option>" ;
	echo "</select></td><td><input class='biggerbutton' type='submit' value='Go'></td></tr></table>" ;
	echo "<table width='850px' cellspacing='1' cellpadding='3' border='1'><tr>" ;
	echo "<td align='left' width='30px'><b><input type='checkbox' name='checkall' onclick='checkUncheckAll(this);'/></b></td>" ;
	echo "<td align='left' width='30px'><b>Id</b></td>" ;
	echo "<td align='left' width='40px'><b>Vid Id</b></td>" ;
	echo "<td align='left' width='80px'><b>Date</b></td>" ;
	echo "<td align='left' width='80px'><b>Name</b></td>" ;
	echo "<td align='left' width='80px'><b>registered</b></td>" ;
	echo "<td align='left' width='350px'><b>Comment</b></td></tr>" ;



	foreach ($row as $key=>$value) {		
		
		echo "<tr><td align='left'><b><input name='check_all_user".$value['id']."' type='checkbox'></b></td>" ;
		echo "<td align='left'><b>".$value['id']."</b></td>" ;
		echo "<td align='left'><b>".$value['vid_id']."</b></td>" ;
		echo "<td align='left'><b>".$value['date']."</b></td>" ;
		echo "<td align='left'><b>".$value['leftbyname']."</b></td>" ;
		echo "<td align='left'><b>".$value['regdposter']."</b></td>" ;
		echo "<td align='left'><b>".$value['text']."</b></td>" ;
	}
echo "</table></form>" ;

?>