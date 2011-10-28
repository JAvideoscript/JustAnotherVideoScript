/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
var ajaxfriendlyurl = document.getElementById('ajax').value;
$(document).ready(function() {
   $.get(ajaxfriendlyurl+"ajaxfunc.php",
       {id: 1, tags: $("#tags").html(), poster: $("#posterz").html()},
	   
       function(data)
       {
         $("#resultz").html(data);
       });
    $("#tags").hide();
 });

$(document).ready(function() {
   $.get(ajaxfriendlyurl+"ajaxfunc.php",
       {id: 4, vidid: video_id},
       function(data)
       {
         $("#commentz").append(data);
       });
 });

function doRelated(tagz,posterz)
{
	$.get(ajaxfriendlyurl+"ajaxfunc.php",
       {id:1, tags: tagz, poster: posterz},
       function(data)
       {
          $("#resultz").html(data);
       });							
}

function doUser(tagz,posterz)
{
	
	$.get(ajaxfriendlyurl+"ajaxfunc.php",
       {id: 2, tags: tagz, poster: posterz}, 
       function(data)
       {
          $("#resultz").html(data);
       });							
}


function RefreshComments()
{
   $.get(ajaxfriendlyurl+"ajaxfunc.php",
       {id: 4, vidid: video_id},
       function(data)
       {
         $("#commentz").html(data);
       });
}

function Mcomment(vidid, loggedIn)
{	
	$.get(ajaxfriendlyurl+"ajaxfunc.php",
		  {id: 3, name: $("#name").val(), comment: $("#text").val(), scode2: $("#security_code").val(), visitor: $("#visitor").val(), vidid: vidid, loggedIn: loggedIn},
		 function(data)
		 {
			  RefreshComments();
			 $("#Cstats").html(data);
			 $("#text").val("");
			 $("#security_code").val("");
		 });
}
function deleteComment(num)
{
   $.get(ajaxfriendlyurl+"ajaxfunc.php",
       {id: 5, num: num},
       function(data)
       {
         RefreshComments();
       });
}