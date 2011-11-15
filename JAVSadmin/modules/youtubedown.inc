<?php
	include_once("adminfunctions.inc");
?>


<script language="javascript" type="text/javascript" src="./js/ydown.js"></script>


<fieldset>
	<ol>
		<li>
			<h2>&nbsp;&nbsp;Enter your YouTube Video URL</h2>
			<h6>Example: http://www.youtube.com/watch?v=abc-132fg</h6>
		</li>		

		<li>	
			<label>Youtube Url:</label>
			<input type="text" size="70" id="url" />
		</li>
		<li>	
			<label>Title:</label>
			<input type="text" size="70" id="title" />
		</li>
		<li>	
			<label>Description:</label>
			<input type="text" size="70" id="desc" />
		</li>
		<li>	
			<label>Tags:</label>
			<input type="text" size="70" id="tags" />
		</li>
		<li>
			<label>Category:</label>
					<select id="cater" style="width: 150px">
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
			<input type="submit" value="Download!" id="download" />
		</li>
		
		
		<div id="loading"><img src="./images/loading2.gif" width="340px" alt="Loading..." /></div>
	    <br />
	    <br />


	</ol>
</fieldset>
