<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
global $db,$sitepath ;
if (!$loggedIn) {
      $haltMessage = "<div id='home'><h2>You must log in to use Account Management</h2></div>" ;
}
else {
      //Get ID of logged in user
      $db->query("SELECT * FROM member WHERE username = '".quote_smart($_SESSION['session_username'])."'") ;
      $resUID = $db->fetch() ;
      $username = $resUID['username'] ;
      //Count favorites, messages, subscriptions, etc. for numbers on account management page
      if (isset($resUID['id'])) {
            $uid = $resUID['id'] ;
            $db->query("SELECT * FROM favorite WHERE userid = $uid") ;
            $favorites = $db->numRows() ;
	    $profilefavorites = $favorites ;
            $db->query("SELECT * FROM friend WHERE (userid =".$uid." OR friendid =".$uid.") AND friend_removed=0 AND friend_approved=1") ;
            $friends = $db->numRows() ;
	    $profilefriends = $friends ;
            $db->query("SELECT * FROM friend WHERE userid =".$uid." AND friend_approved = 0") ;
            $receivedRequests = $db->numRows() ;
	    $profilefriendsreceived = $receivedRequests ;
            $db->query("SELECT * FROM friend WHERE friendid =".$uid." AND friend_approved = 0 AND friend_removed = 0") ; //don't count declined messages
            $sentRequests = $db->numRows() ;
	    $profilefriendssent = $sentRequests ;
            $db->query("SELECT * FROM blocked WHERE blocker_id = ".$uid) ;
            $blocked = $db->numRows() ;
	    $profileblocked = $blocked ;
            $db->query("SELECT * FROM subscription WHERE userid = $uid") ;
            $subscriptions = $db->numRows() ;
	    $profilesubscriptions = $subscriptions ;
            $db->query("SELECT * FROM media WHERE poster = '".quote_smart(strtolower($_SESSION['session_username']))."' AND status = 'true'") ;
            $media = $db->numRows() ;
	    $profilemedia = $media ;
            $db->query("SELECT * FROM message WHERE toid = $uid") ;
            $totalMessages = $db->numRows() ;
            $db->query("SELECT * FROM message WHERE toid = $uid AND msgread = 0") ;
            $newMessages = $db->numRows() ;
	    $profileinbox = $newMessages ;
            $db->query("SELECT * FROM message WHERE fromid = $uid AND auto=0") ;
            $sentMessages = $db->numRows() ;
	    $profileoutbox = $sentMessages ;
            $db->query("SELECT * FROM message WHERE fromid = $uid AND auto=0 AND msgread = 0") ;
            $unreadMessages = $db->numRows() ;
	    $db->query("SELECT * FROM media_comment WHERE leftbyname = '".quote_smart(strtolower($_SESSION['session_username']))."' AND regdposter=1") ;
	    $profilecomments = $db->numRows() ;
      }
}

$SnewMessage = $newMessages != 1 ? ' new messages' : ' new message' ;
$SsentMessage = $sentMessages != 1 ? ' sent messages' : ' sent message' ;
$Sfriend = $friends != 1 ? ' members' : ' member' ;
$SreceivedRequest = $receivedRequests != 1 ? ' friend requests' : ' friend request' ;
$SsentRequest = $sentRequests != 1 ? ' friend requests' : ' friend request' ;
$Ssubscription = $subscriptions != 1 ? ' members' : ' member' ;
$Sblocked = $blocked != 1 ? ' members' : ' member' ;
$Smedia = $media != 1 ? ' media items' : ' media item' ;
$Sfavorite = $favorites != 1 ? ' media items' : ' media item' ;
$newMessages = $newMessages.''.$SnewMessage ;
$sentMessages = $sentMessages.''.$SsentMessage ;
$friends = $friends.''.$Sfriend ;
$receivedRequests = $receivedRequests.''.$SreceivedRequest ;
$sentRequests = $sentRequests.''.$SsentRequest ;
$subscriptions = $subscriptions.''.$Ssubscription ;
$blocked = $blocked.''.$Sblocked ;
$media = $media.''.$Smedia ;
$favorites = $favorites.''.$Sfavorite ;
$inboxLink = '<a href="'.$sitepath.'usermenu/inbox">' ;
$outboxLink = '<a href="'.$sitepath.'usermenu/outbox">' ;
$receivedRequestsLink = '<a href="'.$sitepath.'usermenu/myreceivedrequests">' ;
$sentRequestsLink = '<a href="'.$sitepath.'usermenu/mysentrequests">' ;
$blockedLink = '<a href="'.$sitepath.'usermenu/blocked">' ;
$subscriptionsLink = '<a href="'.$sitepath.'usermenu/subscriptions">' ;
$friendsLink = '<a href="'.$sitepath.'usermenu/myfriends">' ;
$favoritesLink = '<a href="'.$sitepath.'usermenu/favorites">' ;
$mediaLink = '<a href="'.$sitepath.'usermenu/media">' ;
$profileLink = '<a href="'.$sitepath.'usermenu/profile">' ;
$profileviews = $resUID['profileviews'] ;

$url = $sitepath."profile/".$resUID['username'] ;
$avatargender = $resUID['gender'] > 0 ? 'female' : 'male' ;
$avatar = $templateimagepath."default_".$avatargender."_avatar.png" ;
if (@file_exists("uploads/avatars/".$resUID['avatar']) && ($resUID['avatar'] != "")) {
	$avatar = $sitepath."uploads/avatars/".$resUID['avatar'] ;
}
$img = str_replace(" ", "%20", $avatar) ;
$profileimg = '<img src="'.$img.'" width="160" height="120" alt="'.$resUID['username'].'" />';
$profileusername = $resUID['username'] ;
$profileemail = $resUID['email'] ;
$profilelastlogin = date("Y-m-d H:i:s", $resUID['lastlogin']) ;
$profilejoined = date("Y-m-d H:i:s", $resUID['created']) ;
$profilelastip = $resUID['ip'] ;
$profilegender = $resUID['gender'] != 1 ? ' Male' : ' Female' ;
$profileage = $resUID['age'] ;
$profilelocation = $resUID['location'] ;

$historyLink = '<a href="'.$sitepath.'usermenu/history">' ;
$profileHistoryLink = '<a href="'.$sitepath.'usermenu/profilehistory">' ;
$uploadLink = '<a href="'.$sitepath.'upload">' ;
?>

















