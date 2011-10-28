<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
global $rootpath,$sitepath;
$site_template = getSetting("sitetemplate",$db);
$filepath = $rootpath.'templates/'.$site_template.'/'.$c_file;
if (file_exists($filepath) || isset($c_content)) {
	if(isset($c_content)){
		$c_content='?'.'>'.trim($c_content).'<'.'?';
		eval($c_content);
	}else{
		include($filepath);
	}
}
?>