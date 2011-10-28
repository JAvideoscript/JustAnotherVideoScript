<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
	  global $sitepath;
	  echo '<div align="center"><h2> Rss Feeds </h2></div><br /><br />';
	  echo "<h3> Select an Rss Feed To View! </h3><br /><br />";

	  $db->query("SELECT id, name FROM category");
	  echo "<ol>";
	  echo '<li><a href="'.$sitepath.'rss.php">See All </a><br /><br /></li>';
	  while($row = $db->fetch())
	  {
	  	echo '<li><a href="'.$sitepath.'rss.php?feed='.$row['id'].'"> '.$row['name'].' </a><br/></li>';
	  }
	  echo "</ol>";
?>