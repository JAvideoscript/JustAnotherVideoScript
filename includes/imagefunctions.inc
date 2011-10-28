<?php
/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
function ResizeMath($maxW, $maxH, $img) {
	$imageW = imagesx($img) ;
	$imageH = imagesy($img) ;
	if ($imageW <= $maxW && $imageH <= $maxH) {
		$thumbW = $imageW ;
		$thumbH = $imageH ;
	}
	else {
		if ($imageW >= $imageH) {
			$thumbW = $maxW ;
			$thumbH = $maxW / $imageW * $imageH ;
		}
		else {
			$thumbH = $maxH ;
			$thumbW = $maxH / $imageH * $imageW ;
		}
	}
	$thumbW = round($thumbW) ;
	$thumbH = round($thumbH) ;
	$thesize = array($thumbW, $thumbH, $imageW, $imageH) ;
	return $thesize ;
}
function findThumb($video, $just_file = false) {
	$thumbs = array() ;
	$extensions = array("jpg", "jpeg", "png", "gif") ;
	$searchpaths = array("uploads/thumbs/", "/uploads/thumbs/", "../uploads/thumbs/", "../../uploads/thumbs") ;
	foreach ($extensions as $ext) {
		foreach ($searchpaths as $path) {
			if (strlen($thumbs[0]) > 1 && strlen($thumbs[1]) > 1)
				break (2) ;
			if (@file_exists($path.$video.".small.".$ext) && strlen($thumbs[0]) < 1) {
				if ($just_file)
					$thumbs[0] = $video.".small.".$ext ;
				else
					$thumbs[0] = $path.$video.".small.".$ext ;
			}
			if (@file_exists($path.$video.".large.".$ext) && strlen($thumbs[1]) < 1) {
				if ($just_file)
					$thumbs[1] = $video.".large.".$ext ;
				else
					$thumbs[1] = $path.$video.".large.".$ext ;
			}
		}
	}
	if (isset($thumbs[0]) && isset($thumbs[1]))
		return $thumbs ;
}
function createThumb($name, $maxW, $maxH, $image_path, $outname) {
	global $db ;
	$ext = substr($name, strrpos($name, ".") + 1) ;
	switch (strtolower($ext)) {
		case "jpg":
		case "jpeg":
			$img = imagecreatefromjpeg($image_path.$name) ;
			$size = ResizeMath($maxW, $maxH, $img) ;
			$size[0] = $maxW ;
			$size[1] = $maxH ;
			$img2 = imagecreatetruecolor($size[0], $size[1]) ;
			imagecopyresized($img2, $img, 0, 0, 0, 0, $size[0], $size[1], $size[2], $size[3]) ;
			imagejpeg($img2, $image_path.$outname) ;
			return true ;
			break ;
		case "png":
			$img = imagecreatefrompng($image_path.$name) ;
			$size = ResizeMath($maxW, $maxH, $img) ;
			$size[0] = $maxW ;
			$size[1] = $maxH ;
			$img2 = imagecreatetruecolor($size[0], $size[1]) ;
			imagecopyresampled($img2, $img, 0, 0, 0, 0, $size[0], $size[1], $size[2], $size[3]) ;
			imagepng($img2, $image_path.$outname) ;
			return true ;
			break ;
		case "gif":
			$img = imagecreatefromgif($image_path.$name) ;
			$size = ResizeMath($maxW, $maxH, $img) ;
			$size[0] = $maxW ;
			$size[1] = $maxH ;
			$img2 = imagecreatetruecolor($size[0], $size[1]) ;
			imagecopyresampled($img2, $img, 0, 0, 0, 0, $size[0], $size[1], $size[2], $size[3]) ;
			imagegif($img2, $image_path.$outname) ;
			return true ;
			break ;
		default:
			return false ;
			break ;
	}
}
?>
