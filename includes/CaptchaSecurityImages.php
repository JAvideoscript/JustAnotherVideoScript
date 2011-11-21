<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/
 */
session_start() ;
class CaptchaSecurityImages {
      var $font = 'Ash.ttf' ;

      function generateCode($characters) {
            /* list all possible characters, similar looking characters and vowels have been removed */
            $possible = '23456789bcdfghjkmnpqrstvwxyz' ;
            $code = '' ;
            $i = 0 ;
            while ($i < $characters) {
                  $code .= substr($possible, mt_rand(0, strlen($possible) - 1), 1) ;
                  $i++ ;
            }
            return $code ;
      }

      function CaptchaSecurityImages($width = '120', $height = '40', $characters = '6') {
            $code = $this->generateCode($characters) ;
            /* font size will be 75% of the image height */
            $font_size = $height * 0.30 ;
            $image = @imagecreate($width, $height) or die('Cannot initialize new GD image stream') ;
            /* set the colours */
            $background_color = imagecolorallocate($image, 0, 0, 0) ;
            $text_color = imagecolorallocate($image, 255, 255, 255) ;
            $noise_color = imagecolorallocate($image, 157, 157, 157) ;

            /* generate random lines in background */
            for ($i = 0; $i < ($width * $height) / 150; $i++) {
                  imageline($image, mt_rand(0, $width), mt_rand(0, $height), mt_rand(0, $width), mt_rand(0, $height), $noise_color) ;
            }
            /* create textbox and add text */
            $textbox = imagettfbbox($font_size, 0, $this->font, $code) or die('Error in imagettfbbox function') ;
            $x = ($width - $textbox[4]) / 2 ;
            $y = ($height - $textbox[5]) / 2 ;
            imagettftext($image, $font_size, 0, $x, $y, $text_color, $this->font, $code) or die('Error in imagettftext function') ;
            /* output captcha image to browser */
            header('Content-Type: image/jpeg') ;
            imagejpeg($image) ;
            imagedestroy($image) ;
            $_SESSION['session_security_code'] = $code ;
      }
}
$width = isset($_GET['width']) ? $_GET['width'] : '120' ;
$height = isset($_GET['height']) ? $_GET['height'] : '40' ;
$characters = isset($_GET['characters']) && $_GET['characters'] > 1 ? $_GET['characters'] : '6' ;
$captcha = new CaptchaSecurityImages($width, $height, $characters) ;

?>
