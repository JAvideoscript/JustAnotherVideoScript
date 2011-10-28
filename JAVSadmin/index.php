<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
session_start();

include ( "./functions.php" );

if ( $_SERVER['REQUEST_METHOD'] == 'POST' )
{

    if ( $_POST['susername'] == "" )
    {
        echo "Please fill in a username, go <a href='javascript:history.back(-1)';>back</a>";
    }
    elseif ( $_POST['spass'] == "" )
    {
        echo "Please fill in a password, go <a href='javascript:history.back(-1)';>back</a>";
    }
    {
        if ( !LoginControle() )
        {
            echo "Username or password not correct, go <a href='javascript:history.back(-1)';>back</a>";
        }
        else
        {
            header ( "location: main.php" );
        }

    }
}
else
{
    ?>
    <form method="post" action="" >
            <table>
                <tr>
                    <td style="width: 100px;">
                    Gebruikersnaam:
                    </td>
                    <td>
                    <input type="text" name="susername" value="" />
                    </td>
                </tr>
                <tr>
                    <td style="width: 100px;">
                    Wachtwoord:
                    </td>
                    <td>
                    <input type="password" name="spass" value="" />
                    </td>
                </tr>
                <tr>
                    <td colspan="2">
                    <input type="submit" name="submit" value="Login" />
                    </td>
                </tr>
            </table>
    </form>
    <?php
}


?>