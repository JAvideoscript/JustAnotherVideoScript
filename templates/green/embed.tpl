<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
include_once "includes/embed.inc" ;

if (getSetting("showupload", $db) == '1') {

	if (!$loggedIn) {
		echo "<h2>You must log in before Embedding a video</h2>" ;
	} else {
	?>

	

	<fieldset>
		<ol>
			<form action="" method="post" enctype="multipart/form-data" onsubmit="return checkform(this);">
			<li>
					<h2>&nbsp;&nbsp;Embed video</h2>
			</li>
			<li>
					<label for="title">Title:</label>
					<input size=80 name="title" id="title" <?php if(isset($_POST['title'])) echo "value='" . $_POST['title'] . "'";?> />
			</li>
			<li>
					<label for="description">Description:</label>
					<input size=80 name="description" id="description" <?php if(isset($_POST['description'])) echo "value='" . $_POST['description'] . "'";?> />
			</li>
			<li>
					<label for="tags">Tags:</label>
					<input size=80 name="tags" id="tags" <?php if(isset($_POST['tags'])) echo "value='" . $_POST['tags'] . "'";?> />
			</li>
			<li>
			<label for="catergorie">Catergorie:</label>
				<select name="catergorie" id="catergorie" style="width: 150px">
						<option value="-----" selected>-----</option>
						<?php
							$db->query("SELECT * FROM `category` ORDER BY name") ;
							$cat = $db->fetchall() ;

							foreach($cat as $value) {
							echo '<option value="'.$value['id'].'">'.$value['name'].'</option>' ;
							}
						?>
				</select>  	
			</li>
			<li>
				<label for="thumbe">Thumb:</label>
				<input type="file" name="thumbe" <?php if(isset($_POST['thumbe'])) echo "value='" . $_POST['thumbe'] . "'";?>>
			</li>
			<li>
				<label for="embedcode">Embed code:</label>
				<textarea name="embedcode" id="embedcode" cols="0" rows="0" style="width: 350px; height: 100px;"><?php if(isset($_POST['embedcode'])) echo $_POST['embedcode'];?></textarea>
			</li>
			<li>
					<label for="submit">&nbsp;</label>
					<input class="biggerbutton" type="submit" name="submit" value="Embed Video" />
			</li>
			</form>
		</ol>
	</fieldset>

	<?php } 

} else {
	echo "<h2>Embed video is disabled</h2>" ;
}




?>