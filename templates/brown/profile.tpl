<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
include_once 'includes/profile.inc';
$exists = checkMemberExists();
?>
<input type="hidden" name="ajax" id="ajax" value="<?=$sitepath?>">
<script type="text/javascript" src="<?=$sitepath?>js/profile.js"></script>
<script type="text/javascript">
$(document).ready(function() {
   // other code here
	doMedia('<?=$_GET['user']?>','<?=$_GET['page']?>');
 });
</script>

<?
if ($exists!='')
{
	echo $exists;
}
else
{
	$action = $_GET['act'];
	if (($action == 'sm')&&(canMessage()=='')&&(!isset($_POST['submit'])))
	{
?>
<div class="main-col">
<form method="post" action="">
<input type="hidden" name="to" value="<?=$toID?>"/>
<input type="hidden" name="from" value="<?=$fromID?>"/>
<input type="hidden" name="type" value="sendmessage"/>
	<h2>(sending to <?=$userandavatar?>)</h2>
	<h3>Enter your message in the box below and click 'send'</h3>
	<p><div id="message"><textarea name="msgbody" rows=6 cols=65></textarea></div></p>
	<p><input class="biggerbutton" type="submit" name="submit" value=" send "/></p>
</form>
</div>
<?
	}
	else
	{
?>
<!-- s:LEFT COL -->
<div id="profile-left">
	<h2>Profile Info</h2>
	<!-- s:PROFILE BOX -->
		<?=profileBox()?>
	<!-- e:PROFILE BOX -->

</div>
<!-- e:LEFT COL -->
		<!-- s:MID COL -->
		<?=$ad3?>
		<div id="profile-right">
			<!-- s:TABS -->
			<?=profileTabs()?>
			<!-- e:TABS -->
			<!-- s:TAB CONTENT -->
			<div id="tabC" name="tabC"> </div>
			<!-- e:TAB CONTENT -->
		</div>
		<!-- e:MID COL -->

<?
	}
}
?>
