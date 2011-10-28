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
		$mp_allvideos = $_POST['mp_allvideos'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mp_allvideos."' WHERE `setting` = 'mp_allvideos'") ;
		$mp_category = $_POST['mp_category'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mp_category."' WHERE `setting` = 'mp_category'") ;
		$mp_mostviewed = $_POST['mp_mostviewed'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mp_mostviewed."' WHERE `setting` = 'mp_mostviewed'") ;
		$mp_mediasearch = $_POST['mp_mediasearch'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mp_mediasearch."' WHERE `setting` = 'mp_mediasearch'") ;
		$mp_toprated = $_POST['mp_toprated'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mp_toprated."' WHERE `setting` = 'mp_toprated'") ;
		$mp_members = $_POST['mp_members'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mp_members."' WHERE `setting` = 'mp_members'") ;
		$mp_friend = $_POST['mp_friend'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mp_friend."' WHERE `setting` = 'mp_friend'") ;
		$mp_fav = $_POST['mp_fav'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mp_fav."' WHERE `setting` = 'mp_fav'") ;
		$mp_media = $_POST['mp_media'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mp_media."' WHERE `setting` = 'mp_media'") ;
		$mp_sub = $_POST['mp_sub'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mp_sub."' WHERE `setting` = 'mp_sub'") ;
		$mp_uploadedvideos = $_POST['mp_uploadedvideos'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mp_uploadedvideos."' WHERE `setting` = 'mp_uploadedvideos'") ;
		$mp_favoritevideos = $_POST['mp_favoritevideos'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mp_favoritevideos."' WHERE `setting` = 'mp_favoritevideos'") ;
		$mp_viewinghistory = $_POST['mp_viewinghistory'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mp_viewinghistory."' WHERE `setting` = 'mp_viewinghistory'") ;
		$mp_inbox = $_POST['mp_inbox'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mp_inbox."' WHERE `setting` = 'mp_inbox'") ;
		$mp_outbox = $_POST['mp_outbox'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mp_outbox."' WHERE `setting` = 'mp_outbox'") ;
		$mp_friends = $_POST['mp_friends'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mp_friends."' WHERE `setting` = 'mp_friends'") ;
		$mp_receivedrequests = $_POST['mp_receivedrequests'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mp_receivedrequests."' WHERE `setting` = 'mp_receivedrequests'") ;
		$mp_sentrequests = $_POST['mp_sentrequests'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mp_sentrequests."' WHERE `setting` = 'mp_sentrequests'") ;
		$mp_profileviews = $_POST['mp_profileviews'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mp_profileviews."' WHERE `setting` = 'mp_profileviews'") ;
		$mp_blockedmembers = $_POST['mp_blockedmembers'] ;
		$db->query("UPDATE `setting` SET `value` = '".$mp_blockedmembers."' WHERE `setting` = 'mp_blockedmembers'") ;
		$relateduserpage = $_POST['relateduserpage'] ;
		$db->query("UPDATE `setting` SET `value` = '".$relateduserpage."' WHERE `setting` = 'relateduserpage'") ;
		echo "Everything has been updated now." ;

	}
//front site
	$mp_allvideos = getSetting(mp_allvideos, $db) ;
	$mp_category = getSetting(mp_category, $db) ;
	$mp_mostviewed = getSetting(mp_mostviewed, $db) ;
	$mp_mediasearch = getSetting(mp_mediasearch, $db) ;
	$mp_toprated = getSetting(mp_toprated, $db) ;
	$mp_members = getSetting(mp_members, $db) ;
//member section
	$mp_favoritevideos = getSetting(mp_favoritevideos, $db) ;
	$mp_friends = getSetting(mp_friends, $db) ;
	$mp_inbox = getSetting(mp_inbox, $db) ;
	$mp_blockedmembers = getSetting(mp_blockedmembers, $db) ;
	$mp_outbox = getSetting(mp_outbox, $db) ;
	$mp_profileviews = getSetting(mp_profileviews, $db) ;
	$mp_receivedrequests = getSetting(mp_receivedrequests, $db) ;
	$mp_sentrequests = getSetting(mp_sentrequests, $db) ;
	$mp_uploadedvideos = getSetting(mp_uploadedvideos, $db) ;
	$mp_viewinghistory = getSetting(mp_viewinghistory, $db) ;	
//profile settings
	$mp_friend = getSetting(mp_friend, $db) ;
	$mp_fav = getSetting(mp_fav, $db) ;
	$mp_media = getSetting(mp_media, $db) ;	
	$mp_sub = getSetting(mp_sub, $db) ;
//related
	$relateduserpage = getSetting(relateduserpage, $db) ;
?>
<fieldset>
	<ol>
	<form action="" method="post" enctype="multipart/form-data">
		<li>
				<h2>&nbsp;&nbsp;Page Settings</h2>
		</li>
		<li>
						<h4>&nbsp;&nbsp;Front site</h4>
		</li>
		<li>
				<label for="mp_allvideos">Page items Allvideos:</label>
				<input type="text" size="3" name="mp_allvideos" value="<?=$mp_allvideos?>">
		</li>

		<li>
				<label for="mp_mostviewed">Page items Mostviewed:</label>
				<input type="text" size="3" name="mp_mostviewed" value="<?=$mp_mostviewed?>">
		</li>
		<li>
				<label for="mp_toprated">Page items Top Rated:</label>
				<input type="text" size="3" name="mp_toprated" value="<?=$mp_toprated?>">
		</li>
		<li>
				<label for="mp_members">Page items Members:</label>
				<input type="text" size="3" name="mp_members" value="<?=$mp_members?>">
		</li>
		<li>
				<label for="mp_mediasearch">Page items Mediasearch:</label>
				<input type="text" size="3" name="mp_mediasearch" value="<?=$mp_mediasearch?>">
		</li>
		<li>
				<label for="mp_category">Page items Category:</label>
				<input type="text" size="3" name="mp_category" value="<?=$mp_category?>">
		</li>
		<li>
						<h4>&nbsp;&nbsp;Member section</h4>
		</li>
		<li>
				<label for="mp_media">Page items profile Media:</label>
				<input type="text" size="3" name="mp_media" value="<?=$mp_media?>">
		</li>		
		<li>
				<label for="mp_fav">Page items profile Favorites:</label>
				<input type="text" size="3" name="mp_fav" value="<?=$mp_fav?>">
		</li>		
		<li>
				<label for="mp_sub">Page items profile Subscriptions:</label>
				<input type="text" size="3" name="mp_sub" value="<?=$mp_sub?>">
		</li>		
		<li>
				<label for="mp_friend">Page items profile Friends:</label>
				<input type="text" size="3" name="mp_friend" value="<?=$mp_friend?>">
		</li>		
		<li>
				<h4>&nbsp;&nbsp;Profile section</h4>
		</li>		
		<li>
				<label for="mp_uploadedvideos">Page items members Uploadedvideos:</label>
				<input type="text" size="3" name="mp_uploadedvideos" value="<?=$mp_uploadedvideos?>">
		</li>			
		<li>
				<label for="mp_favoritevideos">Page items members favoritevideos:</label>
				<input type="text" size="3" name="mp_favoritevideos" value="<?=$mp_favoritevideos?>">
		</li>			
		<li>
				<label for="mp_viewinghistory">Page items members Viewinghistory:</label>
				<input type="text" size="3" name="mp_viewinghistory" value="<?=$mp_viewinghistory?>">
		</li>			
		<li>
				<label for="mp_inbox">Page items members inbox:</label>
				<input type="text" size="3" name="mp_inbox" value="<?=$mp_inbox?>">
		</li>
		<li>
				<label for="mp_outbox">Page items members outbox:</label>
				<input type="text" size="3" name="mp_outbox" value="<?=$mp_outbox?>">
		</li>			
		<li>
				<label for="mp_friends">Page items members friends:</label>
				<input type="text" size="3" name="mp_friends" value="<?=$mp_friends?>">
		</li>			
		<li>
				<label for="mp_receivedrequests">Page items members receivedrequests:</label>
				<input type="text" size="3" name="mp_receivedrequests" value="<?=$mp_receivedrequests?>">
		</li>			
		<li>
				<label for="mp_sentrequests">Page items members Sentrequests:</label>
				<input type="text" size="3" name="mp_sentrequests" value="<?=$mp_sentrequests?>">
		</li>	
		<li>
				<label for="mp_profileviews">Page items members Profileviews:</label>
				<input type="text" size="3" name="mp_profileviews" value="<?=$mp_profileviews?>">
		</li>			
		<li>
				<label for="mp_blockedmembers">Page items members Blockedmembers:</label>
				<input type="text" size="3" name="mp_blockedmembers" value="<?=$mp_blockedmembers?>">
		</li>		
		<li>
				<h4>&nbsp;&nbsp;Related userpage</h4>
		</li>		
		<li>
				<label for="relateduserpage">Page items Related:</label>
				<input type="text" size="3" name="relateduserpage" value="<?=$relateduserpage?>">
		</li>
		<li>
				<label for="submit">&nbsp;</label>
				<input class="biggerbutton" type="submit" name="submit" value="Change" />
		</li>
	</form>
	</ol>
</fieldset>
		