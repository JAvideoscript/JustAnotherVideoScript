<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
class mysql {
	var $conId ;
	var $lastId ;
	var $result ;
	function mysql($host, $user, $password, $database) {
		$this->conId = @mysql_connect($host, $user, $password) or $this->_error(mysql_error()) ;
		@mysql_select_db($database) or $this->_error(mysql_error()) ;
	}
	function query($query) {
		$this->result = mysql_query($query, $this->conId) ;
		$this->lastId = mysql_insert_id($this->conId) ;
		if ($this->result == false) {
			$this->_queryError(mysql_error(), $query) ;
		}
		else {
			return true ;
		}
	}
	function numRows() {
		return mysql_num_rows($this->result) ;
	}
	function fetch($mode = MYSQL_ASSOC ) {
		return mysql_fetch_array($this->result, $mode) ;
	}
	function fetchAll($mode = MYSQL_ASSOC ) {
		$arr = array() ;
		while ($row = $this->fetch($mode)) {
			$arr[] = $row ;
		}
		return $arr ;
	}
	function getLastId() {
		return $this->lastId ;
	}
	function freeResult() {
		return mysql_free_result($this->result) ;
	}
	function disconnect() {
		$ret = mysql_close($this->conId) ;
		$this->conId = NULL ;
		return $ret ;
	}
	function _error($error) {
		die($error) ;
	}
	function _queryError($error, $query) {
		die('<p><pre>Query error:<br/>'.htmlspecialchars($query).'</pre></p><p>'.$error.'</p>') ;
	}
}
?>
