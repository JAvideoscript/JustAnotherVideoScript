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
		$meta_allvideos_header = $_POST['meta_allvideos_header'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_allvideos_header."' WHERE `setting` = 'meta_allvideos_header'") ;
		$meta_allvideos_key = $_POST['meta_allvideos_key'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_allvideos_key."' WHERE `setting` = 'meta_allvideos_key'") ;
		$meta_allvideos_desc = $_POST['meta_allvideos_desc'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_allvideos_desc."' WHERE `setting` = 'meta_allvideos_desc'") ;
		$meta_catlist_header = $_POST['meta_catlist_header'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_catlist_header."' WHERE `setting` = 'meta_catlist_header'") ;
		$meta_catlist_key = $_POST['meta_catlist_key'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_catlist_key."' WHERE `setting` = 'meta_catlist_key'") ;
		$meta_catlist_desc = $_POST['meta_catlist_desc'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_catlist_desc."' WHERE `setting` = 'meta_catlist_desc'") ;
		$meta_category_header = $_POST['meta_category_header'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_category_header."' WHERE `setting` = 'meta_category_header'") ;
		$meta_category_key = $_POST['meta_category_key'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_category_key."' WHERE `setting` = 'meta_category_key'") ;
		$meta_category_desc = $_POST['meta_category_desc'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_category_desc."' WHERE `setting` = 'meta_category_desc'") ;	
		$meta_home_header = $_POST['meta_home_header'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_home_header."' WHERE `setting` = 'meta_home_header'") ;
		$meta_home_key = $_POST['meta_home_key'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_home_key."' WHERE `setting` = 'meta_home_key'") ;
		$meta_home_desc = $_POST['meta_home_desc'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_home_desc."' WHERE `setting` = 'meta_home_desc'") ;
		$meta_members_header = $_POST['meta_members_header'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_members_header."' WHERE `setting` = 'meta_members_header'") ;
		$meta_members_key = $_POST['meta_members_key'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_members_key."' WHERE `setting` = 'meta_members_key'") ;
		$meta_members_desc = $_POST['meta_members_desc'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_members_desc."' WHERE `setting` = 'meta_members_desc'") ;	
		$meta_mostviewed_header = $_POST['meta_mostviewed_header'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_mostviewed_header."' WHERE `setting` = 'meta_mostviewed_header'") ;
		$meta_mostviewed_key = $_POST['meta_mostviewed_key'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_mostviewed_key."' WHERE `setting` = 'meta_mostviewed_key'") ;
		$meta_mostviewed_desc = $_POST['meta_mostviewed_desc'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_mostviewed_desc."' WHERE `setting` = 'meta_mostviewed_desc'") ;
		$meta_profile_header = $_POST['meta_profile_header'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_profile_header."' WHERE `setting` = 'meta_profile_header'") ;
		$meta_profile_key = $_POST['meta_profile_key'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_profile_key."' WHERE `setting` = 'meta_profile_key'") ;
		$meta_profile_desc = $_POST['meta_profile_desc'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_profile_desc."' WHERE `setting` = 'meta_profile_desc'") ;
		$meta_search_header = $_POST['meta_search_header'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_search_header."' WHERE `setting` = 'meta_search_header'") ;
		$meta_search_key = $_POST['meta_search_key'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_search_key."' WHERE `setting` = 'meta_search_key'") ;
		$meta_search_desc = $_POST['meta_search_desc'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_search_desc."' WHERE `setting` = 'meta_search_desc'") ;
		$meta_toprated_header = $_POST['meta_toprated_header'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_toprated_header."' WHERE `setting` = 'meta_toprated_header'") ;
		$meta_toprated_key = $_POST['meta_toprated_key'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_toprated_key."' WHERE `setting` = 'meta_toprated_key'") ;
		$meta_toprated_desc = $_POST['meta_toprated_desc'] ;
		$db->query("UPDATE `setting` SET `value` = '".$meta_toprated_desc."' WHERE `setting` = 'meta_toprated_desc'") ;

	}

	
$meta_catlist_header = getSetting(meta_catlist_header, $db) ;
$meta_catlist_key = getSetting(meta_catlist_key, $db) ;
$meta_catlist_desc = getSetting(meta_catlist_desc, $db) ;
	
$meta_allvideos_header = getSetting(meta_allvideos_header, $db) ;
$meta_allvideos_key = getSetting(meta_allvideos_key, $db) ;
$meta_allvideos_desc = getSetting(meta_allvideos_desc, $db) ;

$meta_category_header = getSetting(meta_category_header, $db) ;
$meta_category_key = getSetting(meta_category_key, $db) ;
$meta_category_desc = getSetting(meta_category_desc, $db) ;

$meta_home_header = getSetting(meta_home_header, $db) ;
$meta_home_key = getSetting(meta_home_key, $db) ;
$meta_home_desc = getSetting(meta_home_desc, $db) ;
$meta_members_header = getSetting(meta_members_header, $db) ;
$meta_members_key = getSetting(meta_members_key, $db) ;
$meta_members_desc = getSetting(meta_members_desc, $db) ;
$meta_mostviewed_header = getSetting(meta_mostviewed_header, $db) ;
$meta_mostviewed_key = getSetting(meta_mostviewed_key, $db) ;
$meta_mostviewed_desc = getSetting(meta_mostviewed_desc, $db) ;
$meta_profile_header = getSetting(meta_profile_header, $db) ;
$meta_profile_key = getSetting(meta_profile_key, $db) ;
$meta_profile_desc = getSetting(meta_profile_desc, $db) ;
$meta_search_header = getSetting(meta_search_header, $db) ;
$meta_search_key = getSetting(meta_search_key, $db) ;
$meta_search_desc = getSetting(meta_search_desc, $db) ;
$meta_toprated_header = getSetting(meta_toprated_header, $db) ;
$meta_toprated_key = getSetting(meta_toprated_key, $db) ;
$meta_toprated_desc = getSetting(meta_toprated_desc, $db) ;

?>
<fieldset>
	<ol>
	<form action="" method="post" enctype="multipart/form-data">
		<li>
				<h2>&nbsp;&nbsp;Seo, keywords, description, header</h2>
		</li>
		<li>
				<h3>&nbsp;&nbsp;Home</h3>
		</li>
		<li>
				<label for="meta_home_header">Home header:</label>
				<input type="text" size="100" name="meta_home_header" value="<?=$meta_home_header?>">
		</li>
		<li>
				<label for="meta_home_key">Home keywords:</label>
				<input type="text" size="100" name="meta_home_key" value="<?=$meta_home_key?>">
		</li>
		<li>
				<label for="meta_home_desc">Home description:</label>
				<input type="text" size="100" name="meta_home_desc" value="<?=$meta_home_desc?>">
		</li>
		<li>
				<h3>&nbsp;&nbsp;All videos</h3>
		</li>
		<li>
				<label for="meta_allvideos_header">All videos header:</label>
				<input type="text" size="100" name="meta_allvideos_header" value="<?=$meta_allvideos_header?>">
		</li>
		<li>
				<label for="meta_allvideos_key">All videos keywords:</label>
				<input type="text" size="100" name="meta_allvideos_key" value="<?=$meta_allvideos_key?>">
		</li>
		<li>
				<label for="meta_allvideos_desc">All videos description:</label>
				<input type="text" size="100" name="meta_allvideos_desc" value="<?=$meta_allvideos_desc?>">
		</li>
		<li>
				<h3>&nbsp;&nbsp;Mostviewed</h3>
		</li>
		<li>
				<label for="meta_mostviewed_header">Mostviewed header:</label>
				<input type="text" size="100" name="meta_mostviewed_header" value="<?=$meta_mostviewed_header?>">
		</li>
		<li>
				<label for="meta_mostviewed_key">Mostviewed keywords:</label>
				<input type="text" size="100" name="meta_mostviewed_key" value="<?=$meta_mostviewed_key?>">
		</li>
		<li>
				<label for="meta_mostviewed_desc">Mostviewed description:</label>
				<input type="text" size="100" name="meta_mostviewed_desc" value="<?=$meta_mostviewed_desc?>">
		</li>
				<h3>&nbsp;&nbsp;Catlist</h3>
		</li>
		<li>
				<label for="meta_catlist_header">Catlist header:</label>
				<input type="text" size="100" name="meta_catlist_header" value="<?=$meta_catlist_header?>">
		</li>
		<li>
				<label for="meta_catlist_key">Catlist keywords:</label>
				<input type="text" size="100" name="meta_catlist_key" value="<?=$meta_catlist_key?>">
		</li>
		<li>
				<label for="meta_catlist_desc">Catlist description:</label>
				<input type="text" size="100" name="meta_catlist_desc" value="<?=$meta_catlist_desc?>">
		</li>

		<li>
				<h3>&nbsp;&nbsp;Top rated</h3>
		</li>
		<li>
				<label for="meta_toprated_header">Top rated header:</label>
				<input type="text" size="100" name="meta_toprated_header" value="<?=$meta_toprated_header?>">
		</li>
		<li>
				<label for="meta_toprated_key">Top rated keywords:</label>
				<input type="text" size="100" name="meta_toprated_key" value="<?=$meta_toprated_key?>">
		</li>
		<li>
				<label for="meta_toprated_desc">Top rated description:</label>
				<input type="text" size="100" name="meta_toprated_desc" value="<?=$meta_toprated_desc?>">
		</li>
		<li>
				<h3>&nbsp;&nbsp;Members</h3>
		</li>
		<li>
				<label for="meta_members_header">Members header:</label>
				<input type="text" size="100" name="meta_members_header" value="<?=$meta_members_header?>">
		</li>
		<li>
				<label for="meta_members_key">Members keywords:</label>
				<input type="text" size="100" name="meta_members_key" value="<?=$meta_members_key?>">
		</li>
		<li>
				<label for="meta_members_desc">Members description:</label>
				<input type="text" size="100" name="meta_members_desc" value="<?=$meta_members_desc?>">
		</li>
		<li>
				<h3>&nbsp;&nbsp;Profile</h3>
		</li>
		<li>
				<label for="meta_profile_header">Profile header:</label>
				<input type="text" size="100" name="meta_profile_header" value="<?=$meta_profile_header?>">
		</li>
		<li>
				<label for="meta_profile_key">Profile keywords:</label>
				<input type="text" size="100" name="meta_profile_key" value="<?=$meta_profile_key?>">
		</li>
		<li>
				<label for="meta_profile_desc">Profile description:</label>
				<input type="text" size="100" name="meta_profile_desc" value="<?=$meta_profile_desc?>">
		</li>
		<li>
				<h3>&nbsp;&nbsp;Category</h3>
		</li>
		<li>
				<label for="meta_category_header">Category header:</label>
				<input type="text" size="100" name="meta_category_header" value="<?=$meta_category_header?>">
		</li>
		<li>
				<label for="meta_category_key">Category keywords:</label>
				<input type="text" size="100" name="meta_category_key" value="<?=$meta_category_key?>">
		</li>
		<li>
				<label for="meta_category_desc">Category description:</label>
				<input type="text" size="100" name="meta_category_desc" value="<?=$meta_category_desc?>">
		</li>
		<li>
				<h3>&nbsp;&nbsp;Search</h3>
		</li>
		<li>
				<label for="meta_search_header">Search header:</label>
				<input type="text" size="100" name="meta_search_header" value="<?=$meta_search_header?>">
		</li>
		<li>
				<label for="meta_search_key">Search keywords:</label>
				<input type="text" size="100" name="meta_search_key" value="<?=$meta_search_key?>">
		</li>
		<li>
				<label for="meta_search_desc">Search description:</label>
				<input type="text" size="100" name="meta_search_desc" value="<?=$meta_search_desc?>">
		</li>
		<li>
				<label for="submit">&nbsp;</label>
				<input class="biggerbutton" type="submit" name="submit" value="Change" />
		</li>
	</form>
	</ol>
</fieldset>
		