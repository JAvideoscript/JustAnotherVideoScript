<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
include '../includes/mysql.inc' ;
if (!isset($_POST['page'])) {
	$pagenumber = 1 ;
}
else {
	$pagenumber = $_POST['page'] ;
}
switch ($pagenumber) {
	case 1:
		//Page 1 - Check server is ready
		$servercheckfail=false;
		//check server settings
		$settingmaxexec=ini_get('max_execution_time')!=1000?"<font color=red>(we recommend 1000)</font>":"<font color=green> OK</font>";
		$settingmaxinput=ini_get('max_input_time')!=1000?"<font color=red>(we recommend 1000)</font>":"<font color=green> OK</font>";
		$settinguploadmax=ini_get('upload_max_filesize')!='200M'?"<font color=red>(we recommend 200M)</font>":"<font color=green> OK</font>";
		$settingpostmax=ini_get('post_max_size')!='200M'?"<font color=red>(we recommend 200M)</font>":"<font color=green> OK</font>";
		$settingregister=((bool) ini_get('register_argc_argv')?'on':'off')=='off'?"<font color=red>(we recommend on)</font>":"<font color=green> OK</font>";
		$settingopenbase=ini_get('open_basedir')!=''?"<font color=red>(we recommend 'no value')</font>":"<font color=green> OK</font>";
		$settingsafemode=((bool) ini_get('safe_mode')?'on':'off')=='on'?"<font color=red>(we recommend off)</font>":"<font color=green> OK</font>";

if (file_exists('/usr/bin/ffmpeg')) {
	$ffmpegfail = '<font color=green>FFMPEG is installed at /usr/bin/ffmpeg</font>' ;
	$ffmpegpath = '/usr/bin/ffmpeg';
} else {
	if (file_exists('/usr/local/bin/ffmpeg')) {
			$ffmpegfail = '<font color=green>FFMPEG is installed at /usr/local/bin/ffmpeg</font>' ;
			$ffmpegpath = '/usr/local/bin/ffmpeg';
	} else {
		$ffmpegfail = '<font color=red>FFMPEG is not installed at /usr/bin/ffmpeg or /usr/local/bin/ffmpeg - please set the path to FFMPEG in admin settings after you have installed JAVS</font>';
		$ffmpegpath = '/set/ffmpeg/path';
	}
}
if (file_exists('/usr/bin/flvtool2')) {
	$flvtools2fail = '<font color=green>flvtool2 is installed at /usr/bin/ffmpeg</font>' ;
	$flvtoolpath = '/usr/bin/flvtool2';
} else {
	if (file_exists('/usr/local/bin/flvtool2')) {
			$flvtools2fail = '<font color=green>flvtool2 is installed at /usr/local/bin/ffmpeg</font>' ;
			$flvtoolpath = '/usr/local/bin/flvtool2';
	} else {
		$flvtools2fail = '<font color=red>flvtool2 is not installed at /usr/bin/flvtool2 or /usr/local/bin/flvtool2 - please set the path to flvtool2 in admin settings after you have installed JAVS</font>';
		$flvtoolpath = '/set/flvtool2/path';
	}
}
if (file_exists('/usr/bin/curl')) {
	$curlfail = '<font color=green>curl is installed at /usr/bin/curl</font>' ;
	$curlpath = '/usr/bin/curl';
} else {
	if (file_exists('/usr/local/bin/curl')) {
			$curlfail = '<font color=green>curl is installed at /usr/local/bin/curl</font>' ;
			$curlpath = '/usr/local/bin/curl';
	} else {
		$curlfail = '<font color=red>curl is not installed at /usr/bin/curl or /usr/local/bin/curl - please set the path to curl in admin settings after you have installed JAVS</font>';
		$curlpath = '/set/curl/path';
	}
}







		//check folder permissions
		if (!is_writable('../uploads'))
		{
			$folderuploadsfail="<font color=red>Folder 'uploads' is not writable - please CHMOD to 755 or 777</font>";
			$servercheckfail=true;
		}
		else
		{
			$folderuploadsfail="<font color=green>Folder 'uploads' is writable</font>";
		}
		if (!is_writable('../uploads/thumbs'))
		{
			$folderuploadsthumbsfail="<font color=red>Folder 'uploads/thumbs' is not writable - please CHMOD to 755 or 777</font>";
			$servercheckfail=true;
		}
		else
		{
			$folderuploadsthumbsfail="<font color=green>Folder 'uploads/thumbs'  is writable</font>";
		}

		if (!is_writable('../uploads/avatars'))
		{
			$folderuploadsavatarsfail="<font color=red>Folder 'uploads/avatars' is not writable - please CHMOD to 755 or 777</font>";
			$servercheckfail=true;
		}
		else
		{
			$folderuploadsavatarsfail="<font color=green>Folder 'uploads/avatars' is writable</font>";
		}
		if (!is_writable('../uploads/category'))
		{
			$folderuploadscategoryfail="<font color=red>Folder 'uploads/category' is not writable - please CHMOD to 755 or 777</font>";
			$servercheckfail=true;
		}
		else
		{
			$folderuploadscategoryfail="<font color=green>Folder 'uploads/category' is writable</font>";
		}
		if (!is_writable('../uploads/ads'))
		{
			$folderuploadsadsfail="<font color=red>Folder 'uploads/ads' is not writable - please CHMOD to 755 or 777</font>";
			$servercheckfail=true;
		}
		else
		{
			$folderuploadsadsfail="<font color=green>Folder 'uploads/ads' is writable</font>";
		}
		if (!is_writable('../uploads/encodelogs'))
		{
			$folderuploadsencodelogsfail="<font color=red>Folder 'uploads/encodelogs' is not writable - please CHMOD to 755 or 777</font>";
			$servercheckfail=true;
		}
		else
		{
			$folderuploadsencodelogsfail="<font color=green>Folder 'uploads/encodelogs' is writable</font>";
		}
		if (!is_writable('../uploads/encode'))
		{
			$folderuploadsencodefail="<font color=red>Folder 'uploads/encode' is not writable - please CHMOD to 755 or 777</font>";
			$servercheckfail=true;
		}
		else
		{
			$folderuploadsencodefail="<font color=green>Folder 'uploads/encode' is writable</font>";
		}

		if (!is_writable('../sitemap'))
		{
			$foldersitemapfail="<font color=red>Folder 'sitemap' is not writable - please CHMOD to 755 or 777</font>";
			$servercheckfail=true;
		}
		else
		{
			$foldersitemapfail="<font color=green>Folder 'sitemap' is writable</font>";
		}
		if (!is_writable('../uploads/import'))
		{
			$folderuploadsimportfail="<font color=red>Folder 'uploads/import' is not writable - please CHMOD to 755 or 777</font>";
			$servercheckfail=true;
		}
		else
		{
			$folderuploadsimportfail="<font color=green>Folder 'uploads/import' is writable</font>";
		}
		if (!is_writable('../uploads/newuploads'))
		{
			$folderuploadsnewuploadsfail="<font color=red>Folder 'uploads/newuploads' is not writable - please CHMOD to 755 or 777</font>";
			$servercheckfail=true;
		}
		else
		{
			$folderuploadsnewuploadsfail="<font color=green>Folder 'uploads/newuploads' is writable</font>";
		}
		if (!is_writable('../uploads/vids'))
		{
			$folderuploadsvidsfail="<font color=red>Folder 'uploads/vids' is not writable - please CHMOD to 755 or 777</font>";
			$servercheckfail=true;
		}
		else
		{
			$folderuploadsvidsfail="<font color=green>Folder 'uploads/vids' is writable</font>";
		}

		if (!is_writable('../includes/settings.inc'))
		{
			$filesettingsfail="<font color=red>File 'includes/settings.inc' is not writable - please CHMOD to 755 or 777</font>";
			$servercheckfail=true;
		}
		else
		{
			$filesettingsfail="<font color=green>File 'includes/settings.inc' is writable</font>";
		}
		if (!is_writable('../JAVSadmin/modules/settings.inc'))
		{
			$fileadminsettingsfail="<font color=red>File 'JAVSadmin/modules/settings.inc' is not writable - please CHMOD to 755 or 777</font>";
			$servercheckfail=true;
		}
		else
		{
			$fileadminsettingsfail="<font color=green>File 'JAVSadmin/modules/settings.inc' is writable</font>";
		}
		//$servercheckfail=false;
		if ($servercheckfail==true)
		{
			$submit1="<h3><font color=red>Please change the above folder permissions then refresh the page to continue</font></h3>";
		}
		else
		{
			$submit1="<form action='' method='POST'>
			<input type='hidden' name='page' value='1'>
			<input type='submit' name='submit1' value='Next Step'>
		</form>";
		}
		//If anything goes wrong set $servercheckfail=true
   		if (!$servercheckfail&&(isset($_POST['submit1'])))
		{
			$pagenumber++;
		}
		break;
	case 2:
		$dbdetailsfail=false;
		$dbhost = $_POST['dbhost'];
		if ($dbhost=='') {$dbhost='localhost';}
		$dbusername = $_POST['dbusername'];
		$dbpassword = $_POST['dbpassword'];
		$dbname = $_POST['dbname'];
		if (isset($_POST['submit2']))
		{
			$databaseconnect=mysql_connect($dbhost, $dbusername, $dbpassword);
			$connect=(!$databaseconnect)?"<h3><font color=red>Could not connect to MySQL - Please check Host Name, User Name and Password</font></h3>":"";
			if ($databaseconnect)
			{
				$databaseselect=mysql_select_db($dbname,$databaseconnect);
				$select=(!$databaseselect)?"<h3><font color=red>Could not find database '$dbname' - Please check the name is correct and that the user you specified has the correct permissions</font></h3>":"";
				if (!$databaseselect)
				{
					$dbdetailsfail=true;
				}
			}
			else
			{
				$dbdetailsfail=true;
			}
		}
		if (!$dbdetailsfail)
		{
			$settingsfile = '<?php
						$db_host = "' . $dbhost . '";
						$db_user = "' . $dbusername . '";
						$db_password = "' . $dbpassword. '";
						$db_database = "' . $dbname . '";
					?>';
			$fp = fopen('../includes/settings.inc', 'w');
			fwrite($fp, $settingsfile);
			fclose($fp);
			//Set up tables with SQL from database folder
			$db = new mysql($dbhost,$dbusername,$dbpassword,$dbname);
			$templine = '';
			$lines = file("database.sql");
			foreach ($lines as $line_num => $line)
			 {
				if (substr($line, 0, 2) != '--' && $line != '')
				{
					$templine .= $line;
					if (substr(trim($line), -1, 1) == ';')
					{
						$db->query($templine);
						$templine = '';
					}
				}
			}
 		}
		//If it fails then set $databasefail=true
   		if (!$dbdetailsfail&&(isset($_POST['submit2']))) {$pagenumber++;}
		break;
	case 3:
		$sitedetailsfail=false;
		if (isset($_POST['submit3']))
		{
			$dbhost = $_POST['dbhost'];
			$dbusername = $_POST['dbusername'];
			$dbpassword = $_POST['dbpassword'];
			$dbname = $_POST['dbname'];
			$sitename=$_POST['sitename'];
			$sitefolder=$_POST['sitefolder'];
			$sitefolder= ($sitefolder!='')?'/'.$sitefolder.'/':'/'.$sitefolder;
			$adminuname=$_POST['adminuname'];
			$adminpass=$_POST['adminpass'];
			$cronpass=$_POST['cronpass'];
			$ffmpegpath=$_POST['ffmpegpath'];
			$flvtoolpath=$_POST['flvtoolpath'];
			$curlpath=$_POST['curlpath'];

			$cronpasserror=($cronpass=='')?"<font color=red>Required</font>":"";
			$sitenameerror=($sitename=='')?"<font color=red>Required</font>":"";
			$adminunameerror=($adminuname=='')?"<font color=red>Required</font>":"";
			$adminpasserror=($adminpass=='')?"<font color=red>Required</font>":"";
			$sitedetailsfail=(($sitename=='')||($adminuname=='')||($adminpass==''));
		}
		$sitedetailserror=($sitedetailsfail)?"<h3><font color=red>Please fill in all fields below</font></h3>":"";
   		if (!$sitedetailsfail&&(isset($_POST['submit3']))) {
			//Insert Admin Record
			$settingsadminfile = '<?php
						$db_host = "' . $dbhost . '";
						$db_user = "' . $dbusername . '";
						$db_password = "' . $dbpassword. '";
						$db_database = "' . $dbname . '";
						$username = "' . $adminuname . '";
						$pass = "' . md5($adminpass) . '";
					?>';
			$fp = fopen('../JAVSadmin/modules/settings.inc', 'w');
			fwrite($fp, $settingsadminfile);
			fclose($fp);
			$db = new mysql($dbhost,$dbusername,$dbpassword,$dbname);
			$db->query("UPDATE setting SET value='".$sitename."' WHERE setting='sitename'");
			$db->query("UPDATE setting SET value='".$sitefolder."' WHERE setting='sitefolder'");
			$db->query("UPDATE setting SET value='".$cronpass."' WHERE setting='passcron'");


			$db->query("UPDATE setting SET value='".$ffmpegpath."' WHERE setting='ffmpegpath'");
			$db->query("UPDATE setting SET value='".$flvtoolpath."' WHERE setting='flvtool2path'");
			$db->query("UPDATE setting SET value='".$curlpath."' WHERE setting='curlpath'");
			$pagenumber++;
		}



	    break;
//No checks needed for page 4 :)
}
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
    <head>
        <title>Just Another Video Script - Installation</title>
        <link rel="stylesheet" type="text/css" media="all" href="style.css" />
    </head>
    <body>
        <div id="top">
            <div id="topmid">
                <div id="topright">
                    <ul>
                        <li>
                            <a href="http://forums.justanothervideoscript.com/">Forums</a>
                        </li>
                        <li>
						  <a href="http://www.justanothervideoscript.com/faq">FAQ</a>
                        </li>
                        <li>
                            <a href="http://www.justanothervideoscript.com/features">Features</a>
                        </li>
                        <li>
                            <a href="http://www.justanothervideoscript.com/contact">Contact</a>
                        </li>
                    </ul>
                </div>
            </div>
        </div>
        <div id="contentcontain">
            <div id="content">

                    <div id="boxcontent">

 <?php
	switch ($pagenumber) {
	case 1:
		?>
			<h2>Step 1 - Checking your server is ready to install Just Another Video Script 1.4</h2>
		<?php
		?>
        <h3>Server settings:</h3>
        <ul>
		<li>max_execution_time: <?=ini_get('max_execution_time');?><?=$settingmaxexec?></li>
		<li>max_input_time: <?=ini_get('max_input_time');?><?=$settingmaxinput?></li>
		<li>upload_max_filesize: <?=ini_get('upload_max_filesize');?><?=$settinguploadmax?></li>
		<li>post_max_size: <?=ini_get('post_max_size');?><?=$settingpostmax?></li>
		<li>register_argc_argv: <?=ini_get('register_argc_argv');?><?=$settingregister?></li>
		<li>open_basedir: <?=(bool) ini_get('open_basedir')==''?'no value':ini_get('open_basedir');?><?=$settingopenbase?></li>
		<li>safe_mode: <?=(bool) ini_get('safe_mode')?'on':'off';?><?=$settingsafemode?></li>
		</ul>
		<br>

		<h3>Program Paths Installed:</h3>
		<ul>
			<li>FFMPEG - <?=$ffmpegfail?></li>
			<li>FLVtools2 - <?=$flvtools2fail?></li>
			<li>Curl - <?=$curlfail?></li>
		</ul>
		<br>

		<h3>Folder Permissions:</h3>
		<ul>
		<li>Folder 'sitemap' - <?=$foldersitemapfail?></li>
		<li>Folder 'uploads' - <?=$folderuploadsfail?></li>
		<li>Folder 'uploads/thumbs' - <?=$folderuploadsthumbsfail?></li>
		<li>Folder 'uploads/avatars' - <?=$folderuploadsavatarsfail?></li>
		<li>Folder 'uploads/category' - <?=$folderuploadscategoryfail?></li>
		<li>Folder 'uploads/ads' - <?=$folderuploadsadsfail?></li>
		<li>Folder 'uploads/encode' - <?=$folderuploadsencodefail?></li>
		<li>Folder 'uploads/encodelogs' - <?=$folderuploadsencodelogsfail?></li>
		<li>Folder 'uploads/import' - <?=$folderuploadsimportfail?></li>
		<li>Folder 'uploads/vids' - <?=$folderuploadsvidsfail?></li>
		<li>Folder 'uploads/newuploads' - <?=$folderuploadsnewuploadsfail?></li>
		<li>File 'includes/settings.inc' - <?=$filesettingsfail?></li>
		<li>File 'JAVSadmin/modules/settings.inc' - <?=$fileadminsettingsfail?></li>
		<br>
		<br>
		<?php echo $submit1?>
		</ul>
		<?php
		//for all the above, there is the option of an error message, that will happen if the checks at the top fail
		//form submits with page = 1
		break;
	case 2:
		?>
		<h2>Step 2 - Database Details</h2>
		<br>
		<?php echo $connect?>
		<?php echo $select?>
		<br>
		<form action='' method="POST">
		<table>
			<tr>
				<td>
					<label for="dbname">Database name</label>
				</td>
				<td>
					<input type="text" size="20" name="dbname" value="<?=$dbname?>">
					<?=$dbnameerror?>
				</td>
			</tr>
			<tr>
				<td>
					<label for="dbhost">Host Name</label>
				</td>
				<td>
					<input type="text" size="20" name="dbhost" value="<?=$dbhost?>">
					<?=$dbhosterror?>
				</td>
			</tr>
			<tr>
				<td>
					<label for="dbusername">Login Username</label>
				</td>
				<td>
					<input type="text" size="20" name="dbusername" value="<?=$dbusername?>">
					<?=$dbusernameerror?>
				</td>
			</tr>
			<tr>
				<td>
					<label for="dbpassword">Login Password</label>
				</td>
				<td>
					<input type="text" size="20" name="dbpassword" value="<?=$dbpassword?>">
					<?=$dbpassworderror?>
				</td>
			</tr>
			<tr><td>&nbsp;</td><td>&nbsp;</td></tr>
			<input type="hidden" name="page" value="2">

			<input type="hidden" name="ffmpegpath" value="<?=$ffmpegpath?>">
			<input type="hidden" name="flvtoolpath" value="<?=$flvtoolpath?>">
			<input type="hidden" name="curlpath" value="<?=$curlpath?>">
			<tr><td>&nbsp;</td><td><input type="submit" name="submit2" value="Next Step">
		</table>
		</form>

		<?php
		break;
	case 3:
	    //Page 3 - Enter Site Details
		?>
		<h2>Step 3 - Site Details And Admin Login</h2>
		<br>
		<?php echo $sitedetailserror?>
		<form action='' method="POST">
		<table>
			<tr>
				<td>
					<label for="sitename">Site Name (you can change this later)</label>
				</td>
				<td>
					<input type="text" size="20" name="sitename" value="<?=$sitename?>">
					<?=$sitenameerror?>
				</td>
			</tr>
			<tr>
				<td width=500px>
					<label for="sitefolder">Site Folder (eg. if you have uploaded to 'http://yoursite.com/myfolder' enter 'myfolder' (not 'myfolder/') or leave blank if root folder)</label>
				</td>
				<td>
					<input type="text" size="20" name="sitefolder" value="<?=$sitefolder?>">
					<?=$sitefoldererror?>
				</td>
			</tr>
			<tr>
				<td>
					<label for="adminuname">Admin Username</label>
				</td>
				<td>
					<input type="text" size="20" name="adminuname" value="<?=$adminuname?>">
					<?=$adminunameerror?>
				</td>
			</tr>
			<tr>
				<td>
					<label for="adminpass">Admin Password</label>
				</td>
				<td>
					<input type="text" size="20" name="adminpass" value="<?=$adminpass?>">
					<?=$adminpasserror?>
				</td>
			</tr>
			<tr>
				<td>
					<label for="cronpass">Password for cronjob(use only a-zA-Z-0-9)</label>
							</td>
							<td>
								<input type="text" size="20" name="cronpass" value="<?=$cronpass?>">
								<?=$cronpasserror?>
							</td>
			</tr>


			<tr><td>&nbsp;</td><td>&nbsp;</td></tr>
			<input type="hidden" name="page" value="3">
			<input type="hidden" name="dbname" value="<?=$_POST['dbname']?>">
			<input type="hidden" name="dbhost" value="<?=$_POST['dbhost']?>">
			<input type="hidden" name="dbusername" value="<?=$_POST['dbusername']?>">
			<input type="hidden" name="dbpassword" value="<?=$_POST['dbpassword']?>">

			<input type="hidden" name="ffmpegpath" value="<?=$_POST['ffmpegpath']?>">
			<input type="hidden" name="flvtoolpath" value="<?=$_POST['flvtoolpath']?>">
			<input type="hidden" name="curlpath" value="<?=$_POST['curlpath']?>">



			<tr><td>&nbsp;</td><td><input type="submit" name="submit3" value="Next Step">
		</table>
		</form>
		<?php
	    break;
	case 4:
		?>
		<h2>Congratulations! Your new Just Another Video Script is installed and ready</h2>
		<br>
		<h3>Please delete the 'install' folder as soon as possible.</h3>
		<br>
		<h3>Also change the file permissions on JAVSadmin/modules/settings.inc and includes/settings.inc to 644, if you leave it writable it could be a security risk.</h3>
		<br>

		<h3><a href="../">Click here to go to your Just Another Video Script site</a></h3>
		<?php
	    break;
}
?>
   </div>

</div>
</div>
<div id="bottom">
</div>
</body>
</html>