<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
?>
<script type="text/javascript" src="http://s7.addthis.com/js/250/addthis_widget.js"></script>
<?php 
global $sitepath,$template ;
include_once "includes/play.inc" ;
if ($haltmessage != "") {
	echo '<h1>Private Media</h1><h2>'.$haltmessage.'</h2>' ;
}
else {
?>
<input type="hidden" id="ajax" name="ajax" value="<?=$sitepath?>">
<script type="text/javascript" >
video_id = <?php echo $vidid; ?>;
</script>
<script type="text/javascript" src="<?=$sitepath?>js/play.js">
</script>
<script type="text/javascript" src="<?=$sitepath?>js/rate.js">
</script>
<script type="text/javascript">
	$(document).ready(function(){
	    displayRate('<?=$vidid?>', '<?=$pagelink?>');
	});
</script>

<div id="tags"><?=$tags?></div>
<div id="posterz" style="display:none;"><?= $poster?></div>
	<? 
		$_SESSION['session_poster'] == $poster ;
	?>
	
	
	
<div id="main-col"> 
	<div id="main-play-left">
	<?=$ad14?><?=$ad15?>
			<div id="related-col">
				<div id="resultz">
				</div>
			</div>
	</div>
	<div id="main-play-right">
		<h2><?=$title?></h2>
		
		<h4><b>Description:</b> <?=$description?></h4>
		<div id="main-player">
			<?=$ad12?>
			<?=$mediaPlayer?>
			<?=$ad13?>
			<?=$personalvideoad?>
			<?= $showsocial?>
			<div id="RaTe"></div>Total Votes: <?= $numVotes?>
		</div>

		<div id="main-under-player-left">
			<li><?= $flagvidlink?></li>
			<li><?= $addfavlink?></li>
			
			<li><?= $downloadnormal?></li>
			<li><?= $downloadhd?></li>
			<li><?= $downloadmobile?></li>
		</div>
		<div id="main-under-player-right">
			<li><h4><b>From:</b> <a href="<? echo $sitepath."profile/".$poster;?>"> <?=$poster?></a></h4></li>
			<li><h4><b>Category:</b> <?= $category?></h4></li>
			<li><h4><b>Tags: </b><?= $taglinks?></h4></li>	
		</div>	
		
		
	</div>
	
	
<div id="main-play-right2">	
	<h2>Comments</h2>
	

	<div id="commentz">
	</div>
		<div id="Cstats">
	</div>
</div>	
	
	
</div>
		<? } ?>