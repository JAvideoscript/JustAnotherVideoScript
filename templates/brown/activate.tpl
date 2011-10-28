<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
if(isset($_GET['u']) && isset($_GET['key'])){
	$user = quote_smart($_GET['u']);
	$key = quote_smart($_GET['key']);
	$db->query("SELECT * FROM `member` WHERE `id` = '$user'");
	$res = $db->fetch();
	if($res['activationkey'] == $key)
	{
		$db->query("UPDATE `member` SET `activationkey` = '0' WHERE `id` = '$user'");
		echo "Thankyou. Your account was succesfully activated.";
	}
	elseif ($res['activationkey'] == '0')
	{
		echo "You have already activated your account, you can login now";
	}
	else{
		echo "Invalid activation key. Please try again or re-register!";
	}
}else{
	echo "Invalid URL data!";
}?>