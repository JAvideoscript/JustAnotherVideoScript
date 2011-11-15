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

<script type="text/javascript" src="<?=$sitepath?>js/jquery.validate.min.js"></script>
<script type="text/javascript" src="<?=$sitepath?>swfupload/swfupload.js"></script>
<script type="text/javascript" src="<?=$sitepath?>swfupload/fileprogress.js"></script>
<script type="text/javascript" src="<?=$sitepath?>swfupload/handlers.js"></script>

<script type="text/javascript">

jQuery.validator.addMethod("selectNone", 
	function(value, element) { 
		if (element.value == "-----") { 
	      		return false; 
	    	} else {
	    		return true;
	    	}
	  }, "Select one please"
); 
jQuery.validator.addMethod("lettersonly", 
	function(value, element) {
  		return this.optional(element) || /^[a-z0-9 _]+$/i.test(value);
	}, "Letters only please"
);
jQuery.validator.addMethod("letterscomma", 
	function(value, element) {
  		return this.optional(element) || /^[a-z0-9 _,]+$/i.test(value);
	}, "Letters only please"
); 

$().ready(function() {
	// validate signup form on keyup and submit
	$("#embedform").validate({
		rules: {
			emtitle: {
				required: true,
				minlength: 10,
				lettersonly: true,
				remote: {
					url: "<?=$sitepath?>includes/titlecheck.php",
					type: "post",
				}				
			},
			emdescription: {
				required: true,
				minlength: 10
			},
			emtags: {
				required: true,
				letterscomma: true,
				minlength: 10
			},
			emcatergory: {
				selectNone: true 
			},
			emembedcode: {
				required: true,
				minlength: 10,			
			},
			emthumbe: {
				required: true
			}

		},
		messages: {
			emtitle: {
				required: "Please enter a title",
				minlength: "Your title must consist of at least 10 characters",
				remote: "Title already in use"
			},
			emdescription: {
				required: "Please enter a description",
				minlength: "Your description must consist of at least 10 characters"
			},
			emtags: {
				required: "Please enter some tags",
				minlength: "Your tags must consist of at least 10 characters"
			},
			emcatergory: "Please select a category from the list",
			emembedcode: {
				required: "Please enter a embed code",
				minlength: "Your tags must consist of at least 50 characters"
			},
			emthumbe: "Please select a gender from the list"
		}
	});
	$("#form1").validate({
		rules: {
			title: {
				required: true,
				minlength: 10,
				lettersonly: true,
				remote: {
					url: "<?=$sitepath?>includes/titlecheck.php",
					type: "post",
				}				
			},
			description: {
				required: true,
				minlength: 10
			},
			tags: {
				required: true,
				letterscomma: true,
				minlength: 10
			},
			catergory: {
				selectNone: true 
			},
			txtFileName: {
				required: true,
				accept: "wmv|mov|flv|mpg|avi|mpeg|mp4|3gp|rm|asf"
			},
			terms: {
				required: true
			}

		},
		messages: {
			title: {
				required: "Please enter a title",
				minlength: "Your title must consist of at least 10 characters",
				remote: "Title already in use"
			},
			description: {
				required: "Please enter a description",
				minlength: "Your description must consist of at least 10 characters"
			},
			tags: {
				required: "Please enter some tags",
				minlength: "Your tags must consist of at least 10 characters"
			},
			catergory: "Please select a category from the list",
			txtFileName: {
				required: "Please select a file",
				accept: "File Extension is not allowed",
			},
			terms: "Please agree to the terms"
		},
 
 		submitHandler: function(form) {
			//check again
			var txttitle = document.getElementById("title");
			var txtdescription = document.getElementById("description");
			var txttags = document.getElementById("tags");
			var txtFileName = document.getElementById("txtFileName");
			var txtcategory = document.getElementById("category");
			var txtterms = document.getElementById("terms");
			var isValid = true;
			if (txttitle.value === "") {
				isValid = false;
			}
			if (txtdescription.value === "") {
				isValid = false;
			}
			if (txttags.value === "") {
				isValid = false;
			}
			if (txtFileName.value === "") {
				isValid = false;
			}
			if (txtcategory.value === "-----") {
				isValid = false;
			}
			if (document.getElementById("terms").checked == false) {
				isValid = false;
			}			
			if (isValid == true) {
				swfUploadLoaded();
			}
	
 		}
	
	});

});

</script>
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
				<input id="terms" name="terms" type="checkbox" />
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
		<form action="" method="post" enctype="multipart/form-data" id="embedform">
			<div class="box">
				<?=$msgb?>
				<label>
					<span>Title</span>
				        <input type="text" class="input_text" name="emtitle" id="emtitle" />
            			</label>
			
				<label>
	                		<span>Description</span>
	                		<input type="text" class="input_text" name="emdescription" id="emdescription" />
            			</label>			
				<label>
	                		<span>Tags</span>
	                		<input type="text" class="input_text" name="emtags" id="emtags"/>
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
	                		<input type="file" class="input_text" name="emthumbe" id="emthumbe" />
            			</label>
			
				<label>
	                		<span>Embed code</span>		
					<textarea name="emembedcode" class="message" id="emembedcode" cols="0" rows="0"></textarea>
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