<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
include_once 'includes/category.inc';

?>
<script type="text/javascript">
        $(document).ready(function() {
        $("select[id='change_order']").change(function() {
            $('#orderform').submit();
        });
        });
</script>
<?php

if (getSetting("showcategorie", $db) == '1') {
	echo '<div id="main-left"><h2>Categories</h2>' ;
	echo catplainlist() ;
	echo '</div>' ;

	echo '<div id="main-right"><h2>'.$catnameh2.'</h2>' ;
?>

	<div class=top-filter>
	<form action="" method="POST" name="orderform" id="orderform">
		most viewed&nbsp;
	<select name="mostviewed" id="change_order">
	      		<option value="alltime" <?=$mvalltimesel?>>all time</option>
			<option value="today" <?=$mvtodaysel?>>today</option>
			<option value="thisweek" <?=$mvweeksel?>>this week</option>
			<option value="thismonth" <?=$mvmonthsel?>>this month</option>
	</select>&nbsp;&nbsp;&nbsp;&nbsp;
	</form>
	</div>



<?php
	echo $reply ;
	echo '</div>' ;	
} else {
	echo "<h2>Categories are disabled</h2>" ;
}

?>
