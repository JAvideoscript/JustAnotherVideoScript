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
		$autoacceptvideo = $_POST['autoacceptvideo'] == 'on' ? 1 : 0 ;
		$db->query("UPDATE `setting` SET `value` = '".$autoacceptvideo."' WHERE `setting` = 'autoacceptvideo'") ;
		$captchaformembers = $_POST['captchaformembers'] == 'on' ? 1 : 0 ;
		$db->query("UPDATE `setting` SET `value` = '".$captchaformembers."' WHERE `setting` = 'captchaformembers'") ;		
		$comment_length = $_POST['comment_length'] ;
		$db->query("UPDATE `setting` SET `value` = '".$comment_length."' WHERE `setting` = 'comment_length'") ;	
$downnormalmembers = $_POST['downnormalmembers'] == 'on' ? 1 : 0 ;
$db->query("UPDATE `setting` SET `value` = '".$downnormalmembers."' WHERE `setting` = 'downnormalmembers'") ;	
$downhdmember = $_POST['downhdmember'] == 'on' ? 1 : 0 ;
$db->query("UPDATE `setting` SET `value` = '".$downhdmember."' WHERE `setting` = 'downhdmember'") ;	
$downmobilemember = $_POST['downmobilemember'] == 'on' ? 1 : 0 ;
$db->query("UPDATE `setting` SET `value` = '".$downmobilemember."' WHERE `setting` = 'downmobilemember'") ;	
$downGuest = $_POST['downGuest'] == 'on' ? 1 : 0 ;
$db->query("UPDATE `setting` SET `value` = '".$downGuest."' WHERE `setting` = 'downGuest'") ;
$downmobileGuest = $_POST['downmobileGuest'] == 'on' ? 1 : 0 ;
$db->query("UPDATE `setting` SET `value` = '".$downmobileGuest."' WHERE `setting` = 'downmobileGuest'") ;
$downhdguest = $_POST['downhdguest'] == 'on' ? 1 : 0 ;
$db->query("UPDATE `setting` SET `value` = '".$downhdguest."' WHERE `setting` = 'downhdguest'") ;

$membervideodelete = $_POST['membervideodelete'] == 'on' ? 1 : 0 ;
$db->query("UPDATE `setting` SET `value` = '".$membervideodelete."' WHERE `setting` = 'membervideodelete'") ;


		$maxsizememberavatar = $_POST['maxsizememberavatar'] ;
		$db->query("UPDATE `setting` SET `value` = '".$maxsizememberavatar."' WHERE `setting` = 'maxsizememberavatar'") ;	
		$mediamaxsize = $_POST['mediamaxsize'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mediamaxsize."' WHERE `setting` = 'mediamaxsize'") ;		
		$player = $_POST['player'] ;
		$db->query("UPDATE `setting` SET `value` = '".$player."' WHERE `setting` = 'player'") ;
		$player = $_POST['player'] == 'flow' ? flow : jwplayer ;
		$db->query("UPDATE `setting` SET `value` = '".$player."' WHERE `setting` = 'player'") ;
		$avatar_h = $_POST['avatar_h'] ;
		$db->query("UPDATE `setting` SET `value` = '".$avatar_h."' WHERE `setting` = 'avatar_h'") ;
		$avatar_w = $_POST['avatar_w'] ;
		$db->query("UPDATE `setting` SET `value` = '".$avatar_w."' WHERE `setting` = 'avatar_w'") ;
		$restrictpc = $_POST['restrictpc'] == 'on' ? 0 : 1 ;
		$db->query("UPDATE `setting` SET `value` = '".$restrictpc."' WHERE `setting` = 'restrictpc'") ;
		$skinjw = $_POST['skinjw'] ;
		$db->query("UPDATE `setting` SET `value` = '".$skinjw."' WHERE `setting` = 'skinjw'") ;
		echo "Everything has been updated now." ;

	}
	$autoacceptvideo = getSetting(autoacceptvideo, $db) == 1 ? 'CHECKED' : '' ;
	$captchaformembers = getSetting(captchaformembers, $db) == 1 ? 'CHECKED' : '' ;
	$comment_length = getSetting(comment_length, $db) ;
	$maxsizememberavatar = getSetting(maxsizememberavatar, $db) ;
	$mediamaxsize = getSetting(mediamaxsize, $db) ;
	$downnormalmembers = getSetting(downnormalmembers, $db) == 1 ? 'CHECKED' : '' ;
	$downhdmember = getSetting(downhdmember, $db) == 1 ? 'CHECKED' : '' ;
	$downmobilemember = getSetting(downmobilemember, $db) == 1 ? 'CHECKED' : '' ;
	$downGuest = getSetting(downGuest, $db) == 1 ? 'CHECKED' : '' ;
	$downhdguest = getSetting(downhdguest, $db) == 1 ? 'CHECKED' : '' ;
	$downmobileGuest = getSetting(downmobileGuest, $db) == 1 ? 'CHECKED' : '' ;
	$membervideodelete = getSetting(membervideodelete, $db) == 1 ? 'CHECKED' : '' ;
	$player = getSetting(player, $db) ;
	$flowcheck = getSetting(player, $db) == flow ? 'CHECKED' : '' ;
	$jwplayercheck = getSetting(player, $db) == jwplayer ? 'CHECKED' : '' ;
	$avatar_h = getSetting(avatar_h, $db) ;
	$avatar_w = getSetting(avatar_w, $db) ;
	$restrictpc = getSetting(restrictpc, $db)  == 0 ? 'CHECKED' : '' ;
	$skinjw = getSetting(skinjw, $db) ;
?>
<fieldset>
	<ol>
	<form action="" method="post" enctype="multipart/form-data">
		<li>
				<h2>&nbsp;&nbsp;Media Settings</h2>
		</li>
		<li>
				<label for="player">Flash Player:</label>
				FlowPlayer<input type="radio" name="player" value="flow"<?= $flowcheck?>/> &nbsp;Jwplayer&nbsp;<input type="radio" name="player" value="jwplayer"<?= $jwplayercheck?>/> 
		</li>
		<li>
				<label for="skinjw">Jwplayer skin:</label>
				<select name="skinjw" class="select">
					<? 
						foreach (skinList() as $skin) {
							echo "<option" ;
							if ($skin == $skinjw)
									echo " selected" ;
							echo ">".$skin."</option>" ;
						}
					?>
				</select>
		</li>
		<li>
				<label for="autoacceptvideo">Auto accept videos:</label>
				<input type="checkbox" name="autoacceptvideo" <?=$autoacceptvideo?>>
		</li>
		<li>
				<label for="membervideodelete">Members can delete there own videos:</label>
				<input type="checkbox" name="membervideodelete" <?=$membervideodelete?>>
		</li>		
		<li>
				<label for="captchaformembers">Captcha for members:</label>
				<input type="checkbox" name="captchaformembers" <?=$captchaformembers?>>
		</li>
		<li>
				<label for="comment_length">Comment length:</label>
				<input type="text" size="10" name="comment_length" value="<?=$comment_length?>">
		</li>	
		<li>
				<label for="downGuest">Guest can download normal videos(flv):</label>
				<input type="checkbox" name="downGuest" <?=$downGuest?>>
		</li>
		<li>
				<label for="downhdguest">Guest can download HD videos(mp4):</label>
				<input type="checkbox" name="downhdguest" <?=$downhdguest?>>
		</li>		
		<li>
				<label for="downmobileGuest">Guest can download mobile videos(mp4):</label>
				<input type="checkbox" name="downmobileGuest" <?=$downmobileGuest?>>
		</li>
		<li>
				<label for="downnormalmembers">Members can download normal videos(flv):</label>
				<input type="checkbox" name="downnormalmembers" <?=$downnormalmembers?>>
		</li>
		<li>
				<label for="downhdmember">Members can download HD videos(flv):</label>
				<input type="checkbox" name="downhdmember" <?=$downhdmember?>>
		</li>		
		<li>
				<label for="downmobilemember">Members can download normal videos(flv):</label>
				<input type="checkbox" name="downmobilemember" <?=$downmobilemember?>>
		</li>
		<li>
				<label for="restrictpc">Guest can comment videos(always with captcha):</label>
				<input type="checkbox" name="restrictpc" <?=$restrictpc?>>
		</li>
		<li>
				<label for="mediamaxsize">Max Video size (bytes):</label>
				<input type="text" size="15" name="mediamaxsize" value="<?=$mediamaxsize?>">
		</li>
		<li>
				<label for="maxsizememberavatar">Max size member avatar (bytes):</label>
				<input type="text" size="10" name="maxsizememberavatar" value="<?=$maxsizememberavatar?>">
		</li>							
		<li>
				<label for="avatar_w">Member avatar width:</label>
				<input type="text" size="5" name="avatar_w" value="<?=$avatar_w?>">
		</li>				
		<li>
				<label for="avatar_h">Member avatar height:</label>
				<input type="text" size="5" name="avatar_h" value="<?=$avatar_h?>">
		</li>				
						
		
		
		
		
		
		<li>
				<label for="submit">&nbsp;</label>
				<input class="biggerbutton" type="submit" name="submit" value="Change" />
		</li>
	</form>
	</ol>
</fieldset>
