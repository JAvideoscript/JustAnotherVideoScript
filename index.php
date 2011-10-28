<?php
/*
 *    Copyright (c) 2011 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
$starttime = microtime();
$startarray = explode(" ", $starttime);
$starttime = $startarray[1] + $startarray[0];
session_start() ;
ini_set("magic_quotes_gpc", "0") ;
include_once 'includes/bootstrap.inc' ;
include_once 'includes/common.inc' ;
include_once 'includes/content.inc' ;
global $sitepath ;
//if(!ob_start("ob_gzhandler")) ob_start();
$site_template = getSetting("sitetemplate", $db) ;
$sitefolder = getSetting("sitefolder", $db) ;
$path = "http://".$_SERVER['SERVER_NAME'].$sitefolder ;
if (isset($c_header)) {
	$s_header = str_replace("<strong>", "", $c_header) ;
	$s_header = str_replace("</strong>", "", $s_header) ;
	$s_header .= " - " ;
}
else {
	$s_header = "" ;
}
?>
 <!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=windows-1251" />
        <meta name="description" content="<?=isset($mediaDescription)?$mediaDescription:"Video Sharing Script JAVS"; ?>" />
        <meta name="keywords" content="<?=isset($mediaKeywords)?$mediaKeywords:"Video, Sharing, Script, JAVS"; ?>" />
        <title><?=$s_header?><?=getSetting("sitename", $db)?></title>

        <link href="<?php echo $path;?>templates/<?=$site_template?>/css/style.css" rel="stylesheet" type="text/css" />
		<?php
		if (getSetting("player", $db) == "flow") {
		echo '<script type="text/javascript" src="'.$sitepath.'js/flowplayer-3.2.6.min.js"></script>' ;
		} else {
		echo '<script type="text/javascript" src="'.$sitepath.'js/swfobject.js"></script>' ;
		}
		?>
		<script type="text/javascript" src="<?=$sitepath?>js/jquery.min.js"></script>
		<script type="text/javascript" src="<?=$sitepath?>js/jquery.combine.js"></script>
		<script type="text/javascript" src="<?=$sitepath?>js/combinejs.js"></script>
    </head>
    <body>
        <div id="content-area">
        	<a href="<?=$sitepath?>"><div id="logo"></div></a>

            <div class="wrapper">
            	<?php include_once ("templates/".$site_template."/menu.tpl")?>
            </div>



        <?php
        if (!checkBan($_SERVER['REMOTE_ADDR']) > 0) {
        ?>

            <div class="wrapper">


            <?php if (getSetting("enablelogin", $db) == '1') { ?>
	 		<?php if ($loggedIn) { ?>
				 <div id="submenu">
				 	<ul>
				 	<li class="left">&nbsp;</li>
						<li><em></em><a href="<?php echo $sitepath?>account">Account Management</a></li>
						<li><em></em><a href="<?php echo $sitepath?>account/uploadedvideos">My Media : <?php echo $numMedia?></a></li>
						<li><em></em><a href="<?php echo $sitepath?>account/favoritevideos">Favorites : <?php echo $numFavorites?></a></li>
						<li><em></em><a href="<?php echo $sitepath?>account/inbox">Inbox : <?php echo $numMessages?></a></li>
						<li><em></em><a href="<?php echo $sitepath?>account/friends">friends : <?php echo $approvedFriends?></a></li>
						<li><em></em><a href="<?php echo $path;?>logout">Logout</a></li>
					<li class="sep">&nbsp;</li>
					<li class="right">&nbsp;</li>
					</ul>
				 </div>



		   <?php } else { ?>
			<div id="login-box">
					<a href="<?php echo $path;?>login">Login</a> | <a href="<?php echo $path;?>signup">Signup</a>
			</div>
			<?php } } ?>
			</div>


            <div id="main-col">
                <?php include_once("templates/".$site_template."/content.tpl")?>
            </div>

            <?php
            }
            else {
            ?>
            <div id="sub-bar">
                <div class="wrapper">
                </div>
            </div>
            <div id="content-area">
                <div id="main-col" align=center>
                    <h1><b>You have been banned by admin</b></h1>
                </div>
            </div>
            <?php
            }
            ?>

  <div id="copyright-bar">
	  	<div class="wrapper">
	  		<?php include_once ("templates/".$site_template."/footer.tpl")?>
  		</div>
	</div>
<?php
$endtime = microtime();
$endarray = explode(" ", $endtime);
$endtime = $endarray[1] + $endarray[0];
$totaltime = $endtime - $starttime;
$totaltime = round($totaltime,5);
echo '<div id="copyright-bar"><div class="wrapper">Page generated in '.$totaltime.' seconds.</div></div>';
?>
	<?=$ad16?>
</div>
</body>
</html>