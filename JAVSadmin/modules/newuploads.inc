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
					//send mail to poster video is rejected before deleting all video info
					if (getSetting("mail_video_rejected", $db) == '1') {
						$msg = getEmailformat("email_rejected") ;
						
						$db->query("SELECT title, poster FROM media WHERE id = '".$resCheck['id']."' LIMIT 1") ;
						$mediainfo = $db->fetch() ;
						$db->query("SELECT email FROM member WHERE username = '".$mediainfo['poster']."' LIMIT 1") ;
						$mailinfo = $db->fetch() ;
						$msg = str_replace(array('[TITLE]', '[POSTER]', '[SITEURL]', '[SITENAME]'), array($mediainfo['title'], $mediainfo['poster'], $sitepath, getSetting("sitename", $db)), $msg);			
						sendmail(array(array("email"=>$mailinfo['email'], "name"=>$mediainfo['poster'])), 'Video Redjected', $msg) ;
					}
					if ($resCheck['mediatype'] == "video") {
						if ($resCheck['hd'] == "1") {
							unlink($rootpath."uploads/vids/".$fileid."/".$fileid.".mp4") ;
						}
						if ($resCheck['mobile'] == "1") {
							unlink($rootpath."uploads/vids/".$fileid."/mob_".$fileid.".mp4") ;
						}
						unlink($rootpath."uploads/vids/".$fileid."/".$fileid.".flv") ;
						rmdir($rootpath."uploads/vids/".$fileid."/") ;
						
						$thumbdir = $rootpath."uploads/thumbs/".$fileid."/" ;
						if (file_exists($thumbdir)) {
							foreach(glob($thumbdir.'*.*') as $v){
								unlink($v);
							}
							rmdir($thumbdir);
						}						
						
						$deleteid = $resCheck['id'] ;
						$db->query("DELETE FROM `media` WHERE id = '".$deleteid."'") ;
						echo "Deleted Video with id: $deleteid <br>" ;
					} else {
						$thumbdir = $rootpath."uploads/thumbs/".$fileid."/" ;
						if (file_exists($thumbdir)) {
							foreach(glob($thumbdir.'*.*') as $v){
								unlink($v);
							}
							rmdir($thumbdir);
						}						
					
						$deleteid = $resCheck['id'] ;
						$db->query("DELETE FROM `media` WHERE id = '".$deleteid."'") ;
						echo "Deleted Video with id: $deleteid <br>" ;
					}					
				}
			}
	}
	if ($_POST['massfunc'] == "approve") {
		$db->query("SELECT * FROM media")  ;
		$resv = $db->fetchAll() ;
		foreach ($resv as $resCheck) {
			if (isset($_POST['check_all_user'.$resCheck['id']])) {
				$approveid = $resCheck['id'] ;
				$db->query("UPDATE `media` SET `status` = 'true' WHERE id = '".$approveid."'") ;
				echo "Approved Video with id: $approveid <br>" ;
				//send mail to the poster, subscripber and friends
				
					if (getSetting("mail_video_approved", $db) == '1') {
						$msg = getEmailformat("email_approved") ;
						$db->query("SELECT title, poster FROM media WHERE id = '".$resCheck['id']."' LIMIT 1") ;
						$mediainfo = $db->fetch() ;
						$db->query("SELECT email FROM member WHERE username = '".$mediainfo['poster']."' LIMIT 1") ;
						$mailinfo = $db->fetch() ;
						
						$msg = str_replace(array('[TITLE]', '[POSTER]', '[MEDIALINK]', '[SITEURL]', '[SITENAME]'), array($mediainfo['title'], $mediainfo['poster'], $sitepath."play/".url_encode($mediainfo['title']),$sitepath, getSetting("sitename", $db)), $msg);
						
						sendmail(array(array("email"=>$mailinfo['email'], "name"=>$mediainfo['poster'])), 'Video Approved', $msg) ;
					}							
					if (getSetting("mail_friend_subscribed", $db) == '1') {
						$db->query("SELECT title, poster FROM media WHERE id = '".$resCheck['id']."' LIMIT 1") ;
						$mediainfo = $db->fetch() ;
						$db->query("SELECT id, email FROM member WHERE username = '".$mediainfo['poster']."' LIMIT 1") ;
						$mailinfo = $db->fetch() ;
						
						
						$msg = getEmailformat("email_approved_subscriber") ;				
						$msg = str_replace(array('[TITLE]', '[SITENAME]', '[MEDIALINK]', '[SITEURL]', '[POSTER]'), array($mediainfo['title'], getSetting("sitename", $db), $sitepath."play/".url_encode($mediainfo['title']), $sitepath, $mediainfo['poster']), $msg);
						
					
						$db->query("SELECT userid FROM subscription WHERE subscribedtoid = '".$mailinfo['id']."'");
						$subscripids = $db->fetchAll() ;				
						$subarray = array() ;
					
							foreach($subscripids as $subvalue) {
								$db->query("SELECT email, username FROM member WHERE id = '".$subvalue['userid']."' LIMIT 1") ;
								$subinfo = $db->fetch() ;
								array_push($subarray, array("email"=>$subinfo['email'], "name"=>$subinfo['username']));
							}							
						sendmail($subarray, $mediainfo['poster'].' Uploaded a new video', $msg) ;
					}
					if (getSetting("mail_video_friends", $db) == '1') {
						$db->query("SELECT title, poster FROM media WHERE id = '".$resCheck['id']."' LIMIT 1") ;
						$mediainfo = $db->fetch() ;
						$db->query("SELECT id FROM member WHERE username = '".$mediainfo['poster']."' LIMIT 1") ;
						$memberid = $db->fetch() ;				
					
						
					
						$msg = getEmailformat("email_approved_friend") ;
						$msg = str_replace(array('[TITLE]', '[SITENAME]', '[MEDIALINK]', '[SITEURL]', '[POSTER]'), array($mediainfo['title'], getSetting("sitename", $db), $sitepath."play/".url_encode($mediainfo['title']), $sitepath, $mediainfo['poster']), $msg);
						
						
						$db->query("SELECT * FROM friend WHERE (userid = '".$memberid['id']."' OR friendid = '".$memberid['id']."') AND friend_approved = '1'");
						$friendids = $db->fetchAll() ;
					
						$friarray = array() ;
							foreach($friendids as $frivalue) {
								if ($memberid['id'] != $frivalue['userid']) {
									$db->query("SELECT email, username, friendmail_privacy FROM member WHERE id = '".$frivalue['userid']."' LIMIT 1") ;
									$friinfo = $db->fetch() ;
									if ($friinfo['friendmail_privacy'] != '0') {
										array_push($friarray, array("email"=>$friinfo['email'], "name"=>$friinfo['username']));
									}
								}						
					
								if ($memberid['id'] != $frivalue['friendid']) {
									$db->query("SELECT email, username, friendmail_privacy FROM member WHERE id = '".$frivalue['friendid']."' LIMIT 1") ;
									$friinfo = $db->fetch() ;
									if ($friinfo['friendmail_privacy'] != '0') {
										array_push($friarray, array("email"=>$friinfo['email'], "name"=>$friinfo['username']));
									}
								}							
							}
						sendmail($friarray, $mediainfo['poster'].' Uploaded a new video', $msg) ;
					}
					
				
				
				
				
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
<h2>New Uploads</h2>
<?php
$db->query("SELECT * FROM media WHERE status = 'false'") ;
$row = $db->fetchAll() ;

	echo "<form method='post' action=''>" ;
	echo "<table><tr><td align='right'>Mass function:</td>" ;
	echo "<td><select name='massfunc'>" ;
	echo "<option value='deleteall'>Delete all selected</option>" ;
	echo "<option value='approve' selected>Approve all selected</option>" ;	
	
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
		$thumb = "<img src='".$sitepath."uploads/thumbs/".$value['fileid']."/1.jpg' width='160px' height='120px'>" ;
			
		
		echo "<tr><td align='left'><b><input name='check_all_user".$value['id']."' type='checkbox'></b></td>" ;
		echo "<td align='left'><b>".$value['id']."</b></td>" ;
		echo "<td align='left'>".$thumb."</td>" ;
		echo "<td align='left'>Title: ".$value['title']."<br>Desc: ".$value['description']."<br>Tags: ".$value['tags']."</td>" ;
		echo "<td align='left'>".$value['category']."</td>" ;
		echo "<td align='left'>MediaType: ".$value['mediatype']."<br>Poster: ".$value['poster']."<br>Duration: ".$value['duration']."<br>Added: ".$added."</td>" ;
		echo "<td align='left'>Mobile: ".$mobilecheck."<br>HD: ".$hdcheck."</td>" ;
	}
echo "</table></form>" ;

?>