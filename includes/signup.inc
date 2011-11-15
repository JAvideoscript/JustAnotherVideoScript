<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
global $sitepath ;
$validated = True ;
if (isset($_POST['username'])) {
//we do this server check because the world needs it
	if (($_POST['username'] != '') || ($_POST['password'] != '') || ($_POST['confirm_password'] != '') || ($_POST['email'] != '') || ($_POST['location'] != '') || ($_POST['age'] !='') || ($_POST['gender'] != '')) {
		$username = quote_smart($_POST['username']) ;
		$password = quote_smart($_POST['password']) ;
		$confirm_password = quote_smart($_POST['confirm_password']) ;
		$email = quote_smart($_POST['email']) ;
		$location = quote_smart($_POST['location']) ;
		$age = quote_smart($_POST['age']) ;
		$gender = quote_smart($_POST['gender']) ;

//check valid username		
		$checkname = preg_replace('/[^a-zA-Z0-9\-]/', '', $username) ;
		if ($checkname != $username) {
			$validated = False ;
		}
//check valid email		
		$checkmail = checkmail($email);
		if ($checkmail != 1) {
			$validated = False ;
		}	
//check duplicated username
		$db->query("SELECT * FROM member WHERE username = '".$username."'") ;
		$memcheck = $db->numRows();
		if ($memcheck > 0) {
			$validated = False;
		}
//check duplicated email
		$db->query("SELECT * from `member` WHERE email = '".$email."'") ;
		$mailcheck = $db->numRows();
		if ($mailcheck > 0) {
			$validated = False;
		}
//check is passwords match
		if (strcmp($password, $confirm_password) != 0) {
			$validated = False ;
		}
//check location is not a weird
		$locations = alllands();	
		if (!strpos($locations,$location)) {
			$validated = False ;
		}
//check age is number and between 12 and 120
		if (is_numeric($age)) {
			if (($age > 120) || ($age < 12)) {
				$validated = False ;
			}
		} else {
			$validated = False ;
		}
//check which gender 
		if ($gender == 'male') {
			$gender = '0' ;
		} else {
			$gender = '1' ;
		}
		
		
		if ($validated) {
			$password = md5($password);
			$activation = getSetting("activation", $db) ;
			
			if ($activation == "1") {
				$actkey = md5(uniqid(rand())) ;
				$db->query("INSERT INTO member (username,password,email,activationkey,created,location,age,gender) VALUES ('".$username."','".$password."','".$email."','$actkey','".time()."','".$location."','".$age."',".$gender.")") ;
				$message = getEmailformat("email_activate") ;
				$message = str_replace("[SITEURL]", "http://".$_SERVER['SERVER_NAME'], $message) ;
				$message = str_replace("[ACTLINK]", $sitepath."?id=10&u=".$db->getLastId()."&key=".$actkey, $message) ;
				$message = str_replace("[SITENAME]", getSetting("sitename", $db), $message) ;
				$headers = "From: \"".getSetting("default_from", $db)."\" <".getSetting("contact_email", $db).">>\r\n"."Reply-To: ".getSetting("contact_email", $db)."\r\n"."X-Mailer: PHP/".phpversion() ;
			
				echo "<div id='home'><h2>New Registration</h2></div> <h4>An e-mail has been sent to the address you supplied with instructions on how to complete the registration process.<br/>Thankyou for registering.</h4>" ;
				$ans = sendmail(array(array("email"=>$email, "name"=>$username)), 'Activation required', $message, $headers) ;
				echo $ans."<br />" ;
				$halt = true ;
			
			} else {
				$db->query("INSERT INTO member (username,password,email,activationkey,created,location,age,gender) VALUES ('$username','$password','$email','0','".time()."','".$location."','".$age."',".$gender.")") ;
				$isLogged = $user->_checkLogin($username, $password, False) ;
				if ($isLogged == 0) {
					echo "<meta http-equiv=\"refresh\" content=\"0; URL='index.php'\">" ;
				}
			}
		}
	}
}


function alllands() {
$output = '<option value="USA">USA</option>
<option value="Albania">Albania</option>
<option value="Algeria">Algeria</option>
<option value="AmericanSamoa">American Samoa</option>
<option value="Andorra">Andorra</option>
<option value="Angola">Angola</option>
<option value="Anguilla">Anguilla</option>
<option value="Antigua">Antigua</option>
<option value="Argentina">Argentina</option>
<option value="Armenia">Armenia</option>
<option value="Aruba">Aruba</option>
<option value="Australia">Australia</option>
<option value="Austria">Austria</option>
<option value="Azerbaijan">Azerbaijan</option>
<option value="Bahamas">Bahamas</option>
<option value="Bahrain">Bahrain</option>
<option value="Bangladesh">Bangladesh</option>
<option value="Barbados">Barbados</option>
<option value="Barbuda">Barbuda</option>
<option value="Belgium">Belgium</option>
<option value="Belize">Belize</option>
<option value="Benin">Benin</option>
<option value="Bermuda">Bermuda</option>
<option value="Bhutan">Bhutan</option>
<option value="Bolivia">Bolivia</option>
<option value="Bonaire">Bonaire</option>
<option value="Botswana">Botswana</option>
<option value="Brazil">Brazil</option>
<option value="Virginislands">British Virgin isl.</option>
<option value="Brunei">Brunei</option>
<option value="Bulgaria">Bulgaria</option>
<option value="Burundi">Burundi</option>
<option value="Cambodia">Cambodia</option>
<option value="Cameroon">Cameroon</option>
<option value="Canada">Canada</option>
<option value="Cape Verde">Cape Verde</option>
<option value="Cayman isl">Cayman Islands</option>
<option value="Central African Rep">Central African Rep.</option>
<option value="Chad">Chad</option>
<option value="Channel isl">Channel Islands</option>
<option value="Chile">Chile</option>
<option value="China">China</option>
<option value="Colombia">Colombia</option>
<option value="Congo">Congo</option>
<option value="cook isl">Cook Islands</option>
<option value="Costa Rica">Costa Rica</option>
<option value="Croatia">Croatia</option>
<option value="Curacao">Curacao</option>
<option value="Cyprus">Cyprus</option>
<option value="Czech Republic">Czech Republic</option>
<option value="Denmark">Denmark</option>
<option value="Djibouti">Djibouti</option>
<option value="Dominica">Dominica</option>
<option value="Dominican Republic">Dominican Republic</option>
<option value="Ecuador">Ecuador</option>
<option value="Egypt">Egypt</option>
<option value="ElSalvador">El Salvador</option>
<option value="EquatorialGuinea">Equatorial Guinea</option>
<option value="Eritrea">Eritrea</option>
<option value="Estonia">Estonia</option>
<option value="Ethiopia">Ethiopia</option>
<option value="Faeroe isl">Faeroe Islands</option>
<option value="Fiji">Fiji</option>
<option value="Finland">Finland</option>
<option value="France">France</option>
<option value="French Guiana">French Guiana</option>
<option value="French Polynesia">French Polynesia</option>
<option value="Gabon">Gabon</option>
<option value="Gambia">Gambia</option>
<option value="Georgia">Georgia</option>
<option value="Gemany">Germany</option>
<option value="Ghana">Ghana</option>
<option value="Gibraltar">Gibraltar</option>
<option value="GB">Great Britain</option>
<option value="Greece">Greece</option>
<option value="Greenland">Greenland</option>
<option value="Grenada">Grenada</option>
<option value="Guadeloupe">Guadeloupe</option>
<option value="Guam">Guam</option>
<option value="Guatemala">Guatemala</option>
<option value="Guinea">Guinea</option>
<option value="Guinea Bissau">Guinea Bissau</option>
<option value="Guyana">Guyana</option>
<option value="Haiti">Haiti</option>
<option value="Honduras">Honduras</option>
<option value="HongKong">Hong Kong</option>
<option value="Hungary">Hungary</option>
<option value="Iceland">Iceland</option>
<option value="India">India</option>
<option value="Indonesia">Indonesia</option>
<option value="Irak">Irak</option>
<option value="Iran">Iran</option>
<option value="Ireland">Ireland</option>
<option value="NorthernIreland">Ireland Northern</option>
<option value="Israel">Israel</option>
<option value="Italy">Italy</option>
<option value="Ivory Coast">Ivory Coast</option>
<option value="Jamaica">Jamaica</option>
<option value="Japan">Japan</option>
<option value="Jordan">Jordan</option>
<option value="Kazakhstan">Kazakhstan</option>
<option value="Kenya">Kenya</option>
<option value="Kuwait">Kuwait</option>
<option value="Kyrgyzstan">Kyrgyzstan</option>
<option value="Latvia">Latvia</option>
<option value="Lebanon">Lebanon</option>
<option value="Liberia">Liberia</option>
<option value="Liechtenstein">Liechtenstein</option>
<option value="Lithuania">Lithuania</option>
<option value="Luxembourg">Luxembourg</option>
<option value="Macau">Macau</option>
<option value="Macedonia">Macedonia</option>
<option value="Madagascar">Madagascar</option>
<option value="Malawi">Malawi</option>
<option value="Malaysia">Malaysia</option>
<option value="Maldives">Maldives</option>
<option value="Mali">Mali</option>
<option value="Malta">Malta</option>
<option value="Marshallisl">Marshall Islands</option>
<option value="Martinique">Martinique</option>
<option value="Mauritania">Mauritania</option>
<option value="Mauritius">Mauritius</option>
<option value="Mexico">Mexico</option>
<option value="Micronesia">Micronesia</option>
<option value="Moldova">Moldova</option>
<option value="Monaco">Monaco</option>
<option value="Mongolia">Mongolia</option>
<option value="Montserrat">Montserrat</option>
<option value="Morocco">Morocco</option>
<option value="Mozambique">Mozambique</option>
<option value="Myanmar">Myanmar/Burma</option>
<option value="Namibia">Namibia</option>
<option value="Nepal">Nepal</option>
<option value="Netherlands">Netherlands</option>
<option value="Netherlands Antilles">Netherlands Antilles</option>
<option value="New Caledonia">New Caledonia</option>
<option value="New Zealand">New Zealand</option>
<option value="Nicaragua">Nicaragua</option>
<option value="Niger">Niger</option>
<option value="Nigeria">Nigeria</option>
<option value="Norway">Norway</option>
<option value="Oman">Oman</option>
<option value="Palau">Palau</option>
<option value="Panama">Panama</option>
<option value="Papua New Guinea">Papua New Guinea</option>
<option value="Paraguay">Paraguay</option>
<option value="Peru">Peru</option>
<option value="Philippines">Philippines</option>
<option value="Poland">Poland</option>
<option value="Portugal">Portugal</option>
<option value="Puerto Rico">Puerto Rico</option>
<option value="Qatar">Qatar</option>
<option value="Reunion">Reunion</option>
<option value="Rwanda">Rwanda</option>
<option value="Saba">Saba</option>
<option value="Saipan">Saipan</option>
<option value="Saudi Arabia">Saudi Arabia</option>
<option value="Scotland">Scotland</option>
<option value="Senegal">Senegal</option>
<option value="Seychelles">Seychelles</option>
<option value="Sierra Leone">Sierra Leone</option>
<option value="Singapore">Singapore</option>
<option value="Slovac Republic">Slovak Republic</option>
<option value="Slovenia">Slovenia</option>
<option value="South Africa">South Africa</option>
<option value="South Korea">South Korea</option>
<option value="Spain">Spain</option>
<option value="SriLanka">Sri Lanka</option>
<option value="Sudan">Sudan</option>
<option value="Suriname">Suriname</option>
<option value="Swaziland">Swaziland</option>
<option value="Sweden">Sweden</option>
<option value="Switzerland">Switzerland</option>
<option value="Syria">Syria</option>
<option value="Taiwan">Taiwan</option>
<option value="Tanzania">Tanzania</option>
<option value="Thailand">Thailand</option>
<option value="Togo">Togo</option>
<option value="Trinidad-Tobago">Trinidad-Tobago</option>
<option value="Tunesia">Tunisia</option>
<option value="Turkey">Turkey</option>
<option value="Turkmenistan">Turkmenistan</option>
<option value="United Arab Emirates">United Arab Emirates</option>
<option value="USVirginisl">U.S. Virgin Islands</option>
<option value="USA">U.S.A.</option>
<option value="Uganda">Uganda</option>
<option value="UnitedKingdom">United Kingdom</option>
<option value="Urugay">Uruguay</option>
<option value="Uzbekistan">Uzbekistan</option>
<option value="Vanuatu">Vanuatu</option>
<option value="Vatican City">Vatican City</option>
<option value="Venezuela">Venezuela</option>
<option value="Vietnam">Vietnam</option>
<option value="Wales">Wales</option>
<option value="Yemen">Yemen</option>
<option value="Zaire">Zaire</option>
<option value="Zambia">Zambia</option>
<option value="UK">UK</option>
<option value="Zimbabwe">Zimbabwe</option>' ;
return $output ;
}
?>