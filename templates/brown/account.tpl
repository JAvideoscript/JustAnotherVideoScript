<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
include_once 'includes/account.inc' ;
if (isset($haltMessage)) {
	echo $haltMessage ;
}
else {
?>

	<div id="account-front">
		<div class="account-pic"><?=$profileimg?></div>
			<div class="account-text">
				Username: <em><?=$profileusername?></em><br />
				E-mail: <em><?=$profileemail?></em><br />
				Joined: <em><?=$profilejoined?></em><br />
				Last Login: <em><?=$profilelastlogin?></em><br />
				Last used ip: <em><?=$profilelastip?></em><br />
				Gender: <em><?=$profilegender?></em><br />
				Age: <em><?=$profileage?></em><br />
				Location: <em><?=$profilelocation?></em><br />
			</div>
			<div class="account-text">
				Media: <em><?=$profilemedia?></em><br />
				Favorites: <em><?=$profilefavorites?></em><br />
				Subscriptions: <em><?=$profilesubscriptions?></em><br />
				Profile Views: <em><?=$profileviews?></em><br />
				Blocked Members: <em><?=$profileblocked?></em><br />
				Inbox Messages: <em><?=$profileinbox?></em><br />
				Outbox Messages: <em><?=$profileoutbox?></em><br />
				Media Comments: <em><?=$profilecomments?></em><br />
			</div>
			<div class="account-text">
				Friends: <em><?=$profilefriends?></em><br />
				Friends received requests: <em><?=$profilefriendsreceived?></em><br />
				Friends sent requests: <em><?=$profilefriendssent?></em><br />
			</div>	
	</div>	 	




<div class="glossymenu">
		<a class="menuitem submenuheader">Account</a>
			<div class="submenu">
				<ul>
					<li><a href="<?php echo $sitepath?>account/changepass">Change Password</a></li>
					<li><a href="<?php echo $sitepath?>account/changeavatar">Change Avatar</a></li>
					<li><a href="<?php echo $sitepath?>account/changeemail">Change Email</a></li>
					<li><a href="<?php echo $sitepath?>account/personalinformation">Personal Information</a></li>
					<li><a href="<?php echo $sitepath?>account/memberprivacy">Privacy</a></li>
				</ul>
			</div>
		<a class="menuitem submenuheader">My Media</a>
			<div class="submenu">
				<ul>
					<li><a href="<?php echo $sitepath?>account/uploadedvideos">Uploaded Videos (<?=$profilemedia?>)</a></li>
					<li><a href="<?php echo $sitepath?>account/favoritevideos">Favorite Videos (<?=$profilefavorites?>)</a></li>
					<li><a href="<?php echo $sitepath?>account/viewinghistory">Viewing History</a></li>
				</ul>
			</div>
		<a class="menuitem submenuheader">Contacts</a>
			<div class="submenu">
				<ul>
					<li><a href="<?php echo $sitepath?>account/inbox">Inbox (<?=$profileinbox?>)</a></li>
					<li><a href="<?php echo $sitepath?>account/outbox">Outbox (<?=$profileoutbox?>)</a></li>
					<li><a href="<?php echo $sitepath?>account/friends">Friends (<?=$profilefriends?>)</a></li>
					<li><a href="<?php echo $sitepath?>account/receivedrequests">Received Requests (<?=$profilefriendsreceived?>)</a></li>
					<li><a href="<?php echo $sitepath?>account/sentrequests">Sent Requests (<?=$profilefriendssent?>)</a></li>
				</ul>
			</div>
		<a class="menuitem submenuheader">Members</a>
			<div class="submenu">
				<ul>
					<li><a href="<?php echo $sitepath?>account/profileviews">Profile Views</a></li>
					<li><a href="<?php echo $sitepath?>account/blockedmembers">Blocked Members</a></li>
				</ul>
			</div>

</div>




<div id="account-main">
<?php
include_once "includes/accountcontent.inc" ;
}
?>

</div>
