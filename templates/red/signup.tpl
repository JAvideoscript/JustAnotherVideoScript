<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
include_once "includes/signup.inc";
if (getSetting("enablelogin", $db) == '0') {
	echo '<div id="home"><h2>Sign up is disabled</h2></div>' ;
} else {
?>
<script type="text/javascript" src="<?=$sitepath?>js/jquery.validate.min.js">
</script>
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
  		return this.optional(element) || /^[a-z0-9]+$/i.test(value);
	}, "Letters only please"
); 

$().ready(function() {
	// validate signup form on keyup and submit
	$("#signupForm").validate({
		rules: {
			username: {
				required: true,
				minlength: 5,
				lettersonly: true,
				remote: {
					url: "<?=$sitepath?>includes/signupcheck.php",
					type: "post",
				}
			},
			password: {
				required: true,
				minlength: 5
			},
			confirm_password: {
				required: true,
				minlength: 5,
				equalTo: "#password"
			},
			email: {
				required: true,
				email: true,
				remote: {
					url: "<?=$sitepath?>includes/signupcheck.php",
					type: "post",
				} 				
			},
			location: {
				selectNone: true 
			},
			age: {
				required: true,
				number: true,
				min: 12,
				max: 120
			},
			gender: {
				selectNone: true 
			}

		},
		messages: {
			username: {
				required: "Please enter a username",
				minlength: "Your username must consist of at least 4 characters",
				remote: "Username already in use"
			},
			password: {
				required: "Please provide a password",
				minlength: "Your password must be at least 5 characters long"
			},
			confirm_password: {
				required: "Please provide a password",
				minlength: "Your password must be at least 5 characters long",
				equalTo: "Please enter the same password as above"
			},
			email: {
				required: "Please enter a email address",
				email: "Please enter a valid email address",
				remote: "Email already in use"
			
			},
			location: "Please select a location from the list",
			age: {
				required: "Please enter an age",
				number: "Only enter numbers",
				min: "Please enter a valid age, above 12",
				max: "Please enter a valid age, under 120"
			},
			gender: "Please select a gender from the list"
		}

	
	});
	
});

</script>
<?
	if($halt != 'true') {
?>
<div id="home">
<h2>Sign up</h2>
<form method="post" action="" id="signupForm">

	<div class="box">
		<label>
	                <span>Username</span>
	                <input id="username" type="text" class="input_text" name="username" />
            	</label>
		<label>
	                <span>Password</span>
	                <input id="password" type="password" autocomplete="off" class="input_text" name="password" />
            	</label>  
		<label>
	                <span>Confirm Password</span>
	                <input id="confirm_password" type="password" autocomplete="off" class="input_text" name="confirm_password" />
            	</label> 

		<label>
	                <span>Email Address</span>
	                <input id="email" type="text" name="email" class="input_text" />
            	</label>
		<label>
	                <span>Location</span>
	               	<select id="location" class="input_select" name="location">
		       		<option selected="selected" value="-----">-----</option>
		       		<?php echo alllands()?>
			</select>
            	</label>
		<label>
	                <span>Age</span>
	                <input id="age" "type="text" class="input_text" name="age" />
            	</label>            	
		<label>
	                <span>Gender</span>
	               	<select id="Gender" class="input_select" name="gender">
		       		<option value="-----">-----</option>
		       		<option value="male">male</option>
		       		<option value="female">female</option>
			</select>
            	</label> 	
            	
            	
           	<label>
               		<input type="submit" class="button" value="Sign up" />	
            	</label>
	</div>
</form>
</div>
<?
	}
}
?>

