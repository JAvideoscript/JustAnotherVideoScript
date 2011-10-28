<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
if (file_exists('includes/mysql.inc')) {
	require_once 'includes/mysql.inc' ;
	require_once 'includes/settings.inc' ;
	require_once 'includes/functions.inc' ;
}
else {
	require_once '../includes/mysql.inc' ;
	require_once '../includes/settings.inc' ;
	require_once '../includes/functions.inc' ;
}
function db_connect() {
	global $db_host,$db_user,$db_password,$db_database ;
	$db = new mysql($db_host, $db_user, $db_password, $db_database) ;
	return $db ;
}
function session_defaults() {
	$_SESSION['session_logged'] = false ;
	$_SESSION['session_uid'] = 0 ;
	$_SESSION['session_username'] = '' ;
	$_SESSION['session_cookie'] = 0 ;
	$_SESSION['session_remember'] = false ;
	setcookie('vidlogin', $cookie, time() - 31104000, '/') ;
}
class User {
	var $db = null ; // DB pointer
	var $failed = false ; // failed login attempt
	var $date ; // current date GMT
	var $id = 0 ; // the current user's id
	function User(&$db) {
		$this->db = $db ;
		$this->date = $GLOBALS['date'] ;
		if (isset($_SESSION['session_logged'])) {
			if ($_SESSION['session_logged']) {
				$this->_checkSession() ;
			}
		}
		elseif (isset($_COOKIE['vidlogin'])) {
			$this->_checkRemembered($_COOKIE['vidlogin']) ;
		}
	}
	function _checkLogin($username, $password, $remember) {
		$password = md5($password) ;
		$testcook = md5(uniqid(rand())) ;
		$this->db->query("SELECT * FROM member WHERE username = '".quote_smart($username)."' AND password = '".quote_smart($password)."'") ;
		$result = $this->db->fetch() ;
		if (isset($result['id'])) {
			if ($result['activationkey'] == "0") {
				$this->db->query("UPDATE member SET cookie = '$testcook',lastlogin = '".time()."' WHERE id = ".$result['id']) ;
				$result['cookie'] = $testcook ;
				$this->_setSession($result, $remember) ;
				return 0 ;
			}
			else {
				return 2 ;
			}
		}
		else {
			$this->failed = true ;
			$this->_logout() ;
			return 1 ;
		}
	}
	function _setSession(&$values, $remember, $init = true) {
		$this->id = $values['id'] ;
		$_SESSION['session_uid'] = $this->id ;
		$_SESSION['session_username'] = htmlspecialchars($values['username']) ;
		$_SESSION['session_cookie'] = $values['cookie'] ;
		$_SESSION['session_logged'] = true ;
		if ($remember) {
			$this->updateCookie($values['cookie'], true) ;
		}
		if ($init) {
			$session = session_id() ;
			$ip = $_SERVER['REMOTE_ADDR'] ;
			$this->db->query("UPDATE member SET session = '$session', ip = '$ip' WHERE id = $this->id") ;
		}
	}
	function updateCookie($cookie, $save) {
		$_SESSION['session_cookie'] = $cookie ;
		if ($save) {
			$cookie = serialize(array($_SESSION['session_username'], $cookie)) ;
			setcookie('vidlogin', $cookie, time() + 31104000, '/') ;
		}
	}
	function _checkRemembered($cookie) {
		list($username, $cookie) = @unserialize($cookie) ;
		if (!$username or !$cookie)
			return ;
		$this->db->query("SELECT * FROM member WHERE username = '".quote_smart($username)."' AND cookie = '$cookie'") ;
		$result = $this->db->fetch() ;
		if (isset($result['id'])) {
			$this->_setSession($result, true) ;
		}
	}
	function _checkSession() {
		$username = $_SESSION['session_username'] ;
		$cookie = $_SESSION['session_cookie'] ;
		$session = session_id() ;
		$ip = $_SERVER['REMOTE_ADDR'] ;
		$this->db->query("SELECT * FROM member WHERE (username = '".quote_smart($username)."') AND (cookie = '$cookie') AND (session = '$session') AND (ip = '$ip')") ;
		$result = $this->db->fetch() ;
		if (isset($result)) {
			$this->_setSession($result, false, false) ;
		}
		else {
			$this->_logout() ;
		}
	}
	function _logout() {
		session_defaults() ;
	}
}
?>