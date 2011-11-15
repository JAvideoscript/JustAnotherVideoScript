<?php 
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
include_once("adminfunctions.inc");

$db->query("SELECT * FROM media WHERE status = 'true'") ;
$numvideostrue = $db->numrows() ;
$db->query("SELECT * FROM media WHERE status = 'false'") ;
$numvideosfalse = $db->numrows() ;

$db->query("SELECT * FROM member WHERE activationkey = '0'") ;
$nummembersap = $db->numrows() ;
$db->query("SELECT * FROM member WHERE activationkey <> '0'") ;
$nummembersun = $db->numrows() ;

$db->query("SELECT * FROM media_comment") ;
$numcom = $db->numrows() ;

$db->query("SELECT allviews FROM media WHERE status = 'true'") ;
$res = $db->fetchall() ;
$numvideoall = '' ;
foreach($res as $value) {
	$numvideoall = $numvideoall + $value['allviews'] ;
}
$db->query("SELECT dayviews FROM media WHERE status = 'true'") ;
$res = $db->fetchall() ;
$numvideotoday = '' ;
foreach($res as $value) {
	$numvideotoday = $numvideotoday + $value['dayviews'] ;
}
	
$db->query("SELECT weekviews FROM media WHERE status = 'true'") ;
$res = $db->fetchall() ;
$numvideoweek = '' ;
foreach($res as $value) {
	$numvideoweek = $numvideoweek + $value['weekviews'] ;
}
$db->query("SELECT monthviews FROM media WHERE status = 'true'") ;
$res = $db->fetchall() ;
$numvideomonth = '' ;
foreach($res as $value) {
	$numvideomonth = $numvideomonth + $value['monthviews'] ;
}
$db->query("SELECT * FROM media WHERE flagged = '1'") ;
$numflag = $db->numrows() ;

//check shit for the encoding

$red = "<img src='./images/red.png' border=0>" ;
$green = "<img src='./images/green.png' border=0>" ;


$ffmpegpath = getSetting(ffmpegpath, $db) ;
$curlpath = getSetting(curlpath, $db) ;
$flvtool2path = getSetting(flvtool2path, $db) ;
$mp4box = getSetting(mp4box, $db) ;


if (file_exists($ffmpegpath)) {
	$ffmpegfail = $green ;
	$ffmpegpath = $ffmpegpath;
} else {
	$ffmpegfail = $red;
	$ffmpegpath = 'FFmpeg not found...Set correct path in settings';
}
if (file_exists($curlpath)) {
	$curlfail = $green ;
	$curlpath = $curlpath;
} else {
	$curlfail = $red;
	$curlpath = 'Curl not found...Set correct path in settings';
}
if (file_exists($flvtool2path)) {
	$flvtool2fail = $green ;
	$flvtool2path = $flvtool2path;
} else {
	$flvtool2fail = $red;
	$flvtool2path = 'flvtool2 not found...Set correct path in settings';
}
if (file_exists($mp4box)) {
	$MP4Boxfail = $green ;
	$MP4Boxpath = $mp4box;
} else {
	$MP4Boxfail = $red;
	$MP4Boxpath = 'MP4Box not found...Set correct path in settings';
}

if (is_writable($rootpath.'uploads/')) {
	$Fw_uploads = $green ;
} else {
	$Fw_uploads = $red;
}
if (is_writable($rootpath.'uploads/ads')) {
	$Fw_uploads_ads = $green ;
} else {
	$Fw_uploads_ads = $red;
}
if (is_writable($rootpath.'uploads/avatars')) {
	$Fw_uploads_avatars = $green ;
} else {
	$Fw_uploads_avatars = $red;
}
if (is_writable($rootpath.'uploads/category')) {
	$Fw_uploads_category = $green ;
} else {
	$Fw_uploads_category = $red;
}
if (is_writable($rootpath.'uploads/encode')) {
	$Fw_uploads_encode = $green ;
} else {
	$Fw_uploads_encode= $red;
}
if (is_writable($rootpath.'uploads/encodelogs')) {
	$Fw_uploads_encodelogs = $green ;
} else {
	$Fw_uploads_encodelogs= $red;
}
if (is_writable($rootpath.'uploads/import')) {
	$Fw_uploads_import = $green ;
} else {
	$Fw_uploads_import= $red;
}

if (is_writable($rootpath.'uploads/newuploads')) {
	$Fw_uploads_newuploads = $green ;
} else {
	$Fw_uploads_newuploads= $red;
}
if (is_writable($rootpath.'uploads/thumbs')) {
	$Fw_uploads_thumbs = $green ;
} else {
	$Fw_uploads_thumbs= $red;
}
if (is_writable($rootpath.'uploads/vids')) {
	$Fw_uploads_vids = $green ;
} else {
	$Fw_uploads_vids= $red;
}
if (is_writable($rootpath.'sitemap')) {
	$Fw_uploads_sitemap = $green ;
} else {
	$Fw_uploads_sitemap = $red;
}	


if (is_writable($rootpath.'includes/settings.inc')) {
	$Fw_uploads_incl_set = $green ;
} else {
	$Fw_uploads_incl_set = $red;
}
if (is_writable('modules/settings.inc')) {
	$Fw_uploads_incl_adm = $green ;
} else {
	$Fw_uploads_incl_adm = $red;
}



$df = disk_free_space($rootpath);
$dt = disk_total_space($rootpath);
$du = $dt - $df;
$dp = sprintf('%.2f',($du / $dt) * 100);
$df = formatSize($df);
$du = formatSize($du);
$dt = formatSize($dt);


?>
<style type='text/css'>
    .serverinfo {
            border: 2px solid #5E96E4;
            height: 32px;
            width: 540px;
            margin: 30px auto;
    }
    .serverinfo .prgbar {
            background: #A7C6FF;
            width: <?php echo $dp; ?>%;
            position: relative;
            height: 32px;
            z-index: 999;
    }
    .serverinfo .prgtext {
            color: #286692;
            text-align: center;
            font-size: 13px;
            padding: 9px 0 0;
            width: 540px;
            position: absolute;
            z-index: 1000;
    }
    .serverinfo .prginfo {
            margin: 3px 0;
    }
</style>

			
<fieldset>
	<ol>	
	
		<li>
			<h2>Server Info</h2>
		</li>	
		<li>
			<label>Total Disk Space</label>
			<div class='serverinfo'>
				<div class='prgtext'><?php echo $dp; ?>% Disk Used</div>
				<div class='prgbar'></div>
				<div class='prginfo'>
					<span><?php echo "$du used of $dt total"; ?></span>
				</div>
			</div>
		</li>	
		<li>
			<h2>Account overview</h2>
		</li>	
		<li>
			<label>Number of approved videos:</label> 
			<label><?=$numvideostrue?></label>
		</li>
		<li>
			<label>Number of Unapproved videos:</label>
			<label><?=$numvideosfalse?></label>
		</li>
		<li>
			<label>Number of approved members:</label>
			<label><?=$nummembersap?></label>
		</li>				
		<li>
			<label>Number of Unapproved members:</label>
			<label><?=$nummembersun?></label>
		</li>	
		<li>
			<label>Number of comments:</label>
			<label><?=$numcom?></label>
		</li>
		<li>
			<label>Number of flagged videos:</label>
			<label><?=$numflag?></label>
		</li>
		<li>
			<label>Video number all time:</label>
			<label><?=$numvideoall?></label>
		</li>	
		<li>
			<label>Video number viewed today:</label>
			<label><?=$numvideotoday?></label>
		</li>	
		<li>
			<label>Video number viewed this week:</label>
			<label><?=$numvideoweek?></label>
		</li>
		<li>
			<label>Video number viewed this month:</label>
			<label><?=$numvideomonth?></label>
		</li>	
		<li>
			<h2>Encoding program paths</h2>
		</li>		
		<li>
			<label>FFmpeg:</label>
			<label><?=$ffmpegpath?></label>
			<label><?=$ffmpegfail?></label>
		</li>	
		<li>
			<label>flvtool2:</label>
			<label><?=$flvtool2path?></label>
			<label><?=$flvtool2fail?></label>
		</li>			
		<li>
			<label>Curl:</label>
			<label><?=$curlpath?></label>
			<label><?=$curlfail?></label>
		</li>			
		<li>
			<label>MP4Box:</label>
			<label><?=$MP4Boxpath?></label>
			<label><?=$MP4Boxfail?></label>
		</li>	
		
		
		<li>
			<h2>Chmod Settings</h2>
		</li>			
		<li>
			<label>Folder /Uploads/:</label>
			<label><?=$Fw_uploads?></label>
		</li>	
		<li>
			<label>Folder /Uploads/ads/:</label>
			<label><?=$Fw_uploads_ads?></label>
		</li>	
		<li>
			<label>Folder /Uploads/avatars/:</label>
			<label><?=$Fw_uploads_avatars?></label>
		</li>			
		<li>
			<label>Folder /Uploads/category/:</label>
			<label><?=$Fw_uploads_category?></label>
		</li>			
		<li>
			<label>Folder /Uploads/encode/:</label>
			<label><?=$Fw_uploads_encode?></label>
		</li>			
		<li>
			<label>Folder /Uploads/encodelogs/:</label>
			<label><?=$Fw_uploads_encodelogs?></label>
		</li>						
		<li>
			<label>Folder /Uploads/import/:</label>
			<label><?=$Fw_uploads_import?></label>
		</li>	
		<li>
			<label>Folder /Uploads/newuploads/:</label>
			<label><?=$Fw_uploads_newuploads?></label>
		</li>		
		<li>
			<label>Folder /Uploads/thumbs/:</label>
			<label><?=$Fw_uploads_thumbs?></label>
		</li>		
		<li>
			<label>Folder /Uploads/vids/:</label>
			<label><?=$Fw_uploads_vids?></label>
		</li>	
		<li>
			<label>Folder /Uploads/vids/:</label>
			<label><?=$Fw_uploads_vids?></label>
		</li>			
		<li>
			<label>Folder /sitemap/:</label>
			<label><?=$Fw_uploads_sitemap?></label>
		</li>	
		<li>
			<label>File includes/settings.inc':</label>
			<label><?=$Fw_uploads_incl_set?></label>
		</li>			
		<li>
			<label>Folder /modules/settings.inc:</label>
			<label><?=$Fw_uploads_incl_adm?></label>
		</li>			
						
							
		
	</ol>
</fieldset>






