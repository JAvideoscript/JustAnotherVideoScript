<?php
	include_once("adminfunctions.inc");
?>

<script language="javascript" type="text/javascript" src="./js/jquery.validate.min.js"></script>

<script type="text/javascript">




$().ready(function() {
	// validate signup form on keyup and submit
	$("#videodownloadform").validate({
		rules: {
			url: {
				required: true,
				remote: {
					url: "http://javsdemo.com/JAVSadmin/test1.php",
					type: "post",
				}
			}


		},
		messages: {
			url: {
				required: "Please enter a website url",
				remote: "Website is not valid"
			}
		}

	
	});
	
});











</script>


            	
<form method="post" action="" id="videodownloadform">
			<h1>&nbsp;&nbsp;Download video's from websites in the list</h1>
			<br/>

		<label>
	                <span>website url</span>
	                <input id="url" type="text" name="url" />
            	</label>    
      
      
</form>   
      
      
      
      
      
           