<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
include_once "includes/embed.inc" ;
include_once "includes/upload.inc" ;
if (!$loggedIn) {
		echo "<div id='home'><h2>You must log in before submitting a video</h2></div>" ;
} else {
$filezise = (getsetting("mediamaxsize", $db) / 1024) / 1024 ;
?>

<script language="JavaScript" type="text/javascript">
	function checkform ( form ) {
		if (form.emtitle.value == "") {
			alert( "Please enter a title." );
			form.title.focus();
			return false ;
		}
		if (form.emdescription.value == "") {
			alert( "Please enter a description." );
			form.emdescription.focus();
			return false ;
		}
		if (form.emtags.value == "") {
			alert( "Please enter tags." );
			form.emtags.focus();
			return false ;
		}
		if (form.emembedcode.value == "") {
			alert( "Please enter embed code." );
			form.emembedcode.focus();
			return false ;
		} 
		if (form.emthumbe.value == "") {
			alert( "Please select a thumb." );
			form.emthumbe.focus();
			return false ;
		} 
		if (form.emcatergory.value == "-----") {
			alert( "Please select a category." );
			form.emcatergory.focus();
			return false ;
		}  
	  return true ;
	}
</script>

<script type="text/javascript" src="<?=$sitepath?>swfupload/swfupload.js"></script>
<script type="text/javascript" src="<?=$sitepath?>swfupload/fileprogress.js"></script>
<script type="text/javascript" src="<?=$sitepath?>swfupload/handlers.js"></script>
<script type="text/javascript">
		var swfu;
		window.onload = function () {
			swfu = new SWFUpload({
				// Backend settings
				upload_url: "<?=$sitepath?>swfupload/upload.php",
				file_post_name: "resume_file",

				// Flash file settings
				file_size_limit : "<?=$filezise?> MB",
				file_types : "*.wmv;*.mov;*.flv;*.mpg;*.avi;*.mpeg;*.mp4;*.3gp;*.rm;*.asf;",
				file_types_description : "All Files",
				file_upload_limit : "0",
				file_queue_limit : "1",

				// Event handler settings
				swfupload_loaded_handler : swfUploadLoaded,

				file_dialog_start_handler: fileDialogStart,
				file_queued_handler : fileQueued,
				file_queue_error_handler : fileQueueError,
				file_dialog_complete_handler : fileDialogComplete,

				//upload_start_handler : uploadStart,
				upload_progress_handler : uploadProgress,
				upload_error_handler : uploadError,
				upload_success_handler : uploadSuccess,
				upload_complete_handler : uploadComplete,

				// Button Settings
				button_image_url : "<?=$templateimagepath?>buttonupload.png",
				button_placeholder_id : "spanButtonPlaceholder",
				button_width: 61,
				button_height: 22,

				// Flash Settings
				flash_url : "<?=$sitepath?>swfupload/swfupload.swf",

				custom_settings : {
					progress_target : "fsUploadProgress",
					upload_successful : false
				},

				// Debug settings
				debug: false
			});

		};
</script>

<div id="upload-left">
	<h2>Upload videos</h2>
	
	<?
	if (getSetting("showupload", $db) == '1') {	
	?>


	<form action="" method="post" id="form1" enctype="multipart/form-data">
		<div class="box">
			<?=$msgu?>
			<label>
				<span>Title</span>
				<input name="title" id="title" class="input_text" type="text"/>
            		</label>
			<label>
				<span>Description</span>
				<input name="description" id="description" class="input_text" type="text" />
            		</label>
			<label>
				<span>Tags</span>
				<input name="tags" id="tags" class="input_text" type="text" />
            		</label>
            		
			<label>
	                	<span>Catergory</span>		
	                	<select name="category" class="input_select" id="category">
	                	<option value="-----" selected>-----</option>
					<?php
								$db->query("SELECT * FROM `category` ORDER BY name") ;
								$cat = $db->fetchall() ;

								foreach($cat as $value) {
								echo '<option value="'.$value['id'].'">'.$value['name'].'</option>' ;
								}
					?>
				</select>  	
			</label>            		
            		
            		
            		
            		
			<label>
				<span>File</span>
				
				<div>
					<div>
						<input type="text" class="input_text" name="txtFileName" id="txtFileName"  />
						<span id="spanButtonPlaceholder"></span>
						(<?=$filezise?> MB max)
					</div>
					<div class="flash" id="fsUploadProgress">
					
					
					</div>
					
					<input type="hidden" name="hidFileID" id="hidFileID" value="" />
				</div>
            		</label>
            		
			<label>
				<span>Terms</span>
				<input id="terms" type="checkbox" />
			</label>



			<label>
		        	<input type="submit" value="Submit Video" id="btnSubmit" />
			</label>
		</div>
	</form>



		


	<?
	} else {
		echo '<h3>Upload videos is disabled</h3>';
	}
	?>
	
</div>





<div id="upload-right">
	<h2>Embed videos</h2>
	
	<?
	if (getSetting("showembed", $db) == '1') {
	?>
		<form action="" method="post" enctype="multipart/form-data" onsubmit="return checkform(this);">
			<div class="box">
				<?=$msgb?>
				<label>
					<span>Title</span>
				        <input type="text" class="input_text" name="emtitle" id="emtitle" <?php if(isset($_POST['title'])) echo "value='" . $_POST['title'] . "'";?> />
            			</label>
			
				<label>
	                		<span>Description</span>
	                		<input type="text" class="input_text" name="emdescription" id="emdescription" <?php if(isset($_POST['description'])) echo "value='" . $_POST['description'] . "'";?> />
            			</label>			
				<label>
	                		<span>Tags</span>
	                		<input type="text" class="input_text" name="emtags" id="emtags" <?php if(isset($_POST['tags'])) echo "value='" . $_POST['tags'] . "'";?> />
            			</label>						
				<label>
	                		<span>Catergory</span>				
					<select name="emcatergory" class="input_select" id="emcatergory" style="width: 150px">
							<option value="-----" selected>-----</option>
							<?php
								$db->query("SELECT * FROM `category` ORDER BY name") ;
								$cat = $db->fetchall() ;

								foreach($cat as $value) {
								echo '<option value="'.$value['id'].'">'.$value['name'].'</option>' ;
								}
							?>
					</select>  	
				</label>
				<label>
	                		<span>Thumbnail</span>
	                		<input type="file" class="input_text" name="emthumbe" id="emthumbe" <?php if(isset($_POST['thumbe'])) echo "value='" . $_POST['thumbe'] . "'";?> />
            			</label>
			
				<label>
	                		<span>Embed code</span>		
					<textarea name="emembedcode" class="message" id="emembedcode" cols="0" rows="0"><?php if(isset($_POST['embedcode'])) echo $_POST['embedcode'];?></textarea>
            			</label>		
		
		
		           	<label>
		               		<input type="submit" name="emsubmit" class="button" value="Embed Video" />	
            			</label>
			</div>
		</form>

	<?
	} else {
		echo '<h3>Embedding videos is disabled</h3>';
	}
	?>
	
	
	
</div>


<?php
}
?>