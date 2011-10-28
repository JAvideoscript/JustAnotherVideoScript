<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
function LoginControle () {
			include_once("modules/settings.inc");

			$find_this = array(' ','__','[', ']','-','(',')','.','/','\\');
			$replace_wthis= array(' ',' ','','',' ','','',' ','','');
			$susername = str_replace($find_this,$replace_wthis,$_POST['susername']);
			$spass = str_replace($find_this,$replace_wthis,$_POST['spass']);

            if ($susername == $username  && md5($spass) == $pass) {
                $_SESSION['susername'] = $_POST['susername'];
                $_SESSION['blogged'] = TRUE;
                $_SESSION['iTime'] = time()+300;
                $_SESSION['iIp'] = $_SERVER['REMOTE_ADDR'];
                return true;
            }
}

function Beveiliging() {
    if ( isSet ( $_SESSION['blogged'] ) && ( $_SESSION['blogged'] == 1) ) {
        if ( $_SESSION['iTime'] > ( time() ) )
        {
            $_SESSION['iTime'] = time()+600;
            return true;
        }
        elseif ( $_SERVER['REMOTE_ADDR'] != $_SESSION['iIp'] )
        {
            return false;
        }
        else
        {
            return false;
        }
    }

}

?>