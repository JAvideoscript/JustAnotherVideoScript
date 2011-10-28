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
}
else
{
if (isset($_POST['reset_search'])) {
		unset($_POST) ;
		unset($orderby) ;
		unset($order) ;
		unset($sort) ;
		$query = "SELECT * FROM member WHERE (activationkey=0) " ;
}
if (isset($_POST['useraction'])) { 
	if ($_POST['massfunc'] == "") {
		$tmpid = $_POST['useraction'] ;
		switch($tmpid[0][0]) {
			case'b':
				$banid = str_replace(b, '', $tmpid[0]) ;
				$db->query("UPDATE `member` SET `banned` = '1' WHERE id = '".$banid."'") ;
				echo "Banned User with id: $banid <br>" ;
			break;
			case'u':
				$unbanid = str_replace(u, '', $tmpid[0]) ;
				$db->query("UPDATE `member` SET `banned` = '0' WHERE id = '".$unbanid."'") ;
				echo "Unbanned User with id: $unbanid <br>" ;
			break;
		}
	}
}
if ($_POST['massfunc'] !== "") {
	if ($_POST['massfunc'] == "deleteall") {
		$db->query("SELECT * FROM member")  ;
		$resv = $db->fetchAll() ;
		foreach ($resv as $resCheck) {
			if (isset($_POST['check_all_user'.$resCheck['id']])) {
				$resname = $resCheck['username'] ;
				$resid = $resCheck['id'] ;

				echo "Removed User: $resname with id: $resid <br>" ;
				$db->query("DELETE FROM `member` WHERE id = '".$resCheck['id']."'") ;
			}
		}
	}
	if ($_POST['massfunc'] == "unbanall") {
		$db->query("SELECT * FROM member")  ;
		$resv = $db->fetchAll() ;
			foreach ($resv as $resCheck) {
				if (isset($_POST['check_all_user'.$resCheck['id']])) {
					$resname = $resCheck['username'] ;
					$resid = $resCheck['id'] ;
					echo "unBanned User: $resname with id: $resid <br>" ;
					$db->query("UPDATE `member` SET `banned` = '0' WHERE id = '".$resCheck['id']."'") ;
				}
			}
	}
	if ($_POST['massfunc'] == "banall") {
		$db->query("SELECT * FROM member")  ;
		$resv = $db->fetchAll() ;
			foreach ($resv as $resCheck) {
				if (isset($_POST['check_all_user'.$resCheck['id']])) {
				
				
					$resname = $resCheck['username'] ;
					$resid = $resCheck['id'] ;
					echo "Banned User: $resname with id: $resid <br>" ;
					$db->query("UPDATE `member` SET `banned` = '1' WHERE id = '".$resCheck['id']."'") ;
				}
			}
	}
	if ($_POST['massfunc'] == "approveall") {
		$db->query("SELECT * FROM member")  ;
		$resv = $db->fetchAll() ;
			foreach ($resv as $resCheck) {
				if (isset($_POST['check_all_user'.$resCheck['id']])) {
					$resname = $resCheck['username'] ;
					$resid = $resCheck['id'] ;
					echo "test" ;
					
					echo "Approved User: $resname with id: $resid <br>" ;
					$db->query("UPDATE `member` SET `activationkey` = '0' WHERE id = '".$resCheck['id']."'") ;
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
	<td align="right">Username:</td><td><input type="text" name="username" <?php if(isset($_POST['username'])) echo "value='" . $_POST['username'] . "'";?> /></td>
	<td align="right">Email:</td><td><input type="text" name="email" <?php if(isset($_POST['email'])) echo "value='" . $_POST['email'] . "'";?> /></td>
	<td align="right">Country:</td><td><input type="text" name="country" <?php if(isset($_POST['country'])) echo "value='" . $_POST['country'] . "'";?> /></td>
	</tr>
	
	<tr>
	<td align="right">Gender:</td>
	<td>
	<select name="gender">
	<option value="none" <?php if(!isset($_POST['gender'])) echo "selected";?>>-----</option>
	<option value="female" <?php if($_POST['gender'] == "female") echo "selected";?>>Female</option>
	<option value="male" <?php if($_POST['gender'] == "male") echo "selected";?>>Male</option>
	</select>
	</td>
	
	<td align="right">Order BY:</td>
	<td>
	<select name="orderby">
	<option value="id" <?php if(!isset($_POST['orderby'])) echo "selected";?><?php if($_POST['orderby'] == "id") echo "selected";?>>ID</option>
	<option value="username" <?php if($_POST['orderby'] == "username") echo "selected";?>>Username</option>
	<option value="lastlogin" <?php if($_POST['orderby'] == "lastlogin") echo "selected";?>>Lastlogin</option>
	<option value="joined" <?php if($_POST['orderby'] == "joined") echo "selected";?>>Joined</option>
	<option value="activated" <?php if($_POST['orderby'] == "activated") echo "selected";?>>Activated</option>
	<option value="location" <?php if($_POST['orderby'] == "location") echo "selected";?>>Country</option>
	<option value="age" <?php if($_POST['orderby'] == "age") echo "selected";?>>Age</option>
	<option value="profile" <?php if($_POST['orderby'] == "profile") echo "selected";?>>Profile views</option>
	</select>
	</td>
	
	<td align="right">Order:</td>
	<td>
	<select name="order">
	<option value="asc" <?php if(!isset($_POST['order'])) echo "selected";?><?php if($_POST['order'] == "asc") echo "selected";?>>ASC</option>
	<option value="desc" <?php if($_POST['order'] == "desc") echo "selected";?>>DESC</option>
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
	$query = "SELECT * FROM member WHERE created <> ''" ;
	
	if (isset($_POST['username'])) {
		$sort .= " AND (username LIKE  '%".$_POST['username']."%')" ;	
	}
	if (isset($_POST['email'])) {
		$sort .= " AND (email LIKE  '%".$_POST['email']."%')" ;	
	}
	if (isset($_POST['country'])) {
			$sort .= " AND (location LIKE  '%".$_POST['country']."%')" ;	
	}
	if ($_POST['gender'] !== "") {
	switch ($_POST['gender']) {
				case "male":
					$sort .= " AND (gender=0)" ;
					break ;
				case "female":
					$sort .= " AND (gender=1)" ;
					break ;
		}	
	}
	if (isset($_POST['orderby'])) {
		switch ($_POST['orderby']) {
					case "id":
						$orderby = " ORDER BY id" ;
					break ;
					case "username":
						$orderby = " ORDER BY username" ;
					break ;
					case "lastlogin":
						$orderby = " ORDER BY lastlogin" ;
					break ;
					case "joined":
						$orderby = " ORDER BY created" ;
					break ;
					case "location":
						$orderby = " ORDER BY location" ;
					break ;
					case "age":
						$orderby = " ORDER BY age" ;
					break ;
					case "profile":
						$orderby = " ORDER BY profileviews" ;
					break ;
					case "activated":
						$orderby = " ORDER BY activationkey" ;
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
	if ($orderby == "") {
		$orderby = " ORDER BY id" ;
	}
	
	echo "Query: $query $sort $orderby $order <br>" ;
	$db->query($query.$sort.$orderby.$order) ;
	$numresults = $db->numRows() ;
	$resultar = array() ;
	
	while ($row = $db->fetch()) {
	

		$lastlogin =  date("m/d/Y h:i:s a", $row['lastlogin']);
			if ($row['activationkey'] == "0")  {
			$active = "no" ;
			} else {
			$active = "yes" ;
		}
		if ($row['banned'] == "0")  {
			$banned = "no" ;
			} else {
			$banned = "yes" ;
		}
		$joined = date("m/d/Y h:i:s a", $row['created']);
		
		if ($row['gender'] == "1")  {
			$gender = "Female" ;
		} else {
			$gender = "male" ;
		}
		
		if ($row['avatar'] == '') {
			$thumb = "No avatar";
		} else {
			$thumb = "<img src='".$sitepath."uploads/avatars/".$row['avatar']."' width='160px' height='120px'>" ;
		}
		
		
		$idarray = array(id=>$row['id'],
	    	    	username=>$row['username'],
	    	    	email=>$row['email'],
	    	    	location=>$row['location'],
	    	 	email=>$row['email'],
	     	  	lastlogin=>$lastlogin,
	    	    	lastip=>$row['ip'],
	   	     	active=>$active,
			joined=>$joined,
			gender=>$gender,
			thumb=>$thumb,
	   	     	banned=>$banned);
		array_push($resultar, $idarray) ;


	} //end while loop
	
	if (isset($_POST['pages'])) {
		$max_page = $_POST['pages'] ;
	} else {
		$max_page = "10" ;
	}
	
	$numberarray = count($resultar); //242 in array
	$count_pages = $numberarray / $max_page ;
	$pages = ceil($count_pages) ; //aantal pages gemaakt 
	
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
	
	if ($page > "1") { // vorige link wegzetten
	    $Prev_Page = $page - 1;
	    $Prev_Page = '<a href="'.$_SERVER['PHP_SELF'].'?do=allusers&sub=users&page_id='.$Prev_Page.'">&laquo; Previous Page</a>&nbsp;';
	    echo $Prev_Page;
	} else {
	    echo '';
	}
	$rijtje = ''; // Een rij wegzetten bijv 123456
	
	for ($i = 1; $i < $count_pages; $i++) {
	
	    if ($i == $page) {
	        
	        $rijtje .= '<b>'.$i.'</b>';
	    }
	    
	    else {
	        
	        $rijtje .= '<a href="'.$_SERVER['PHP_SELF'].'?do=allusers&sub=users&page_id='.$i.'">'.$i.'</a>&nbsp;';
	    }
	} 
	echo '&nbsp;'; echo $rijtje; echo '&nbsp;';
	if ($page < $pages) {
	    
	    $Next = $page + 1;
	    $Next = '<a href="'.$_SERVER['PHP_SELF'].'?do=allusers&sub=users&page_id='.$Next.'">Next Page &raquo;</a>';
	    echo $Next;
	} else {
	    echo '';
	}
	?>
	<div id="query-content">

	<form method="post" action="<?php $_SERVER['PHP_SELF']; ?>">
	<table>
	<tr>
			<td align="right">Mass function:</td>
			<td>
			<select name="massfunc">
			<option value="deleteall" selected>Delete selected</option>
			<option value="approveall">Approve users</option>
			<option value="banall" >Ban selected</option>
			<option value="unbanall" >Unban selected</option>
			</select>
			</td>
	<td><input class="biggerbutton" type="submit" value="Go"/></td></tr>
	
	
	</table>
	<table width="850px" cellspacing="1" cellpadding="3" border="1">
	<tr>
				<td align="center" width="15px"><b><input type="checkbox" name="checkall" onclick="checkUncheckAll(this);"/></b></td>
				<td align="center" width="15px"><b>Id</b></td>
				<td align="center" width="400px"><b>User info</b></td>
				<td align="center" width="163px"><b>Avatar</b></td>
				<td align="center" width="50px"><b>Banned</b></td>
				<td align="center" width="50px"><b>Activated</b></td>
				<td align="center" width="100px"><b>Action</b></td>
				
		</tr>
	
	<?php
	
	

	for ($f = $start; $f <= $end; $f++) {
		$action = '<form action="" method="POST">' ;
		if ($resultar[$f][banned] == "no")  {
			$action .= '<input type="submit" class="biggerbutton" name="useraction" value="Ban User">' ;
			$action .= '<input type="hidden" name="useraction[]" value="b'.$resultar[$f][id].'">' ;
		} else {
			$action .= '<input type="submit" class="biggerbutton" name="useraction" value="unBan User">' ;
			$action .= '<input type="hidden" name="useraction[]" value="u'.$resultar[$f][id].'">' ;
		}
		$action .= '</form>' ;
			
	?>
	
	<tr>
	<td align="left"><b><input name="check_all_user<?=$resultar[$f][id]?>" type="checkbox"></b></td>
		<td align="left"><b><?=$resultar[$f][id]?></b></td>
		<td align="left">Username: <?=$resultar[$f][username]?><br>Email: <?=$resultar[$f][email]?><br>Gender: <?=$resultar[$f][gender]?><br>Country: <?=$resultar[$f][location]?><br>Joined: <?=$resultar[$f][joined]?><br>Last Login: <?=$resultar[$f][lastlogin]?><br>Last Ip: <?=$resultar[$f][lastip]?><br></td>
		<td align="left"><?=$resultar[$f][thumb]?></td>		
		<td align="left"><?=$resultar[$f][banned]?></td>
		<td align="left"><?=$resultar[$f][active]?></td>
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
?>

