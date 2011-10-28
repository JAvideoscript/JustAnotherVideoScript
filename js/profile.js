/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
var ajaxfriendlyurl = document.getElementById('ajax').value;
function doFriend(user, page)
{
	$.get(ajaxfriendlyurl+"ajaxprofile.php",
       {id: 1, user: user, page: page},
       function(data)
       {
          $("#tabC").html(data);
       });
}
function doMedia(user, page)
{
	$.get(ajaxfriendlyurl+"ajaxprofile.php",
       {id: 2, user: user, page: page},
       function(data)
       {
          $("#tabC").html(data);
       });
}
function doSub(user, page)
{
	$.get(ajaxfriendlyurl+"ajaxprofile.php",
       {id: 3, user: user, page: page},
       function(data)
       {
          $("#tabC").html(data);
       });
}
function doFav(user, page)
{
	$.get(ajaxfriendlyurl+"ajaxprofile.php",
       {id: 4, user: user, page: page},
       function(data)
       {
          $("#tabC").html(data);
       });
}

