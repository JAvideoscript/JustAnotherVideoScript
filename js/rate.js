/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
var ajaxfriendlyurl = document.getElementById('ajax').value;

function doRate(num, vidid)
{
	$.get(ajaxfriendlyurl+"ajaxplay.php",
       {id: 1, num: num, vidid: vidid},
       function(data)
       {
          $("#RaTe").html(data);
		  displayRate(vidid, ajaxfriendlyurl);
       });
}

function displayRate(vidid, pagelink)
{
	$.get(ajaxfriendlyurl+"ajaxplay.php",
       {id: 2, vidid: vidid, pagelink: pagelink},
       function(data)
       {
          $("#RaTe").html(data);
       });
}