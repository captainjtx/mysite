function initAceEditor()
{
	var elts = document.getElementsByClassName('code-block'); 
	for (var index = 0; index < elts.length; ++index) 
	{ 
		var code_id = elts[index].getAttribute('id'); 
		var parts  = code_id.split("-", 3);
		var btn_id = 'code-run-'+parts[2];

		var editor= ace.edit("user-src-"+parts[2]);
		editor.setTheme("ace/theme/twilight");
		editor.getSession().setMode("ace/mode/c_cpp");

		$('#user-src-'+parts[2]).after("<a target='_blank' class='btn btn-success code-btn' id='"+btn_id+"'>Run the code</a>");
		$('#user-src-'+parts[2]).before("<div class='ace-coliru-declare'>Powered by <a target='_blank' href='https://ace.c9.io/'>Ace editor</a> and <a target='_blank' href='http://coliru.stacked-crooked.com/'>Coliru online compiler</a></div>");
	} 
	registerButtonEvents();
}

$(function(){

	var article_path= window.location.pathname.split( '/' );
	var article_id=article_path[article_path.length-2];

	$.getJSON('/blog/meta/'+article_id, function (meta) {
		$('#blog-post-title').text(meta.title);
		var pub_date=new Date(meta.pub_date);
		var modify_date=new Date(meta.modified_date);
		var meta_str=monthNames[pub_date.getMonth()]+" "+pub_date.getDate()+", "+pub_date.getFullYear().toString()+ ' by Tianxiao Jiang';
		var update_str='updated '+monthNames[modify_date.getMonth()]+" "+modify_date.getDate()+", "+modify_date.getFullYear().toString();
		console.log(meta_str)
		$('#blog-post-meta').text(meta_str);
		$('#blog-post-update').text(update_str);
	});

	$.getJSON("/blog/comment/get/"+article_id,function(data){
		var commentContent='';
		for (var index=0; index<data.comment.length; ++index)
		{
			commentContent+='<div class="comment-content">';
			commentContent+=data.comment[index].content;
			commentContent+='</div></br>';
			commentContent+='<div class="comment-reader">';
			commentContent+='<p>';

			var date=new Date(data.comment[index].datetime);
			commentContent+=monthNames[date.getMonth()];
			commentContent+=" ";
			commentContent+=date.getDate();
			commentContent+=" '";
			commentContent+=date.getFullYear().toString().substr(2,2);
			commentContent+=" at ";
			commentContent+=date.getHours();
			commentContent+=":";
			commentContent+=pad(date.getMinutes());

			commentContent+='</br>';
			commentContent+=data.comment[index].reader;
			commentContent+='</p></div>';
		}

		$('#comment-list').html(commentContent);
	});
	githubStars("captainjtx/mysite",function(stars){
		$('#btn-star-count div').html(stars);
	});
	$("p.note").prepend("<strong>Note: </strong>");
	var tags=$("h2,h3");
	var sidebar='<nav class="bs-docs-sidebar hidden-sm hidden-xs">';
	sidebar+='<ul class="nav nav-stacked" data-spy="affix" data-offset-top="175" id="nav-sidebar">';
	sidebar+='<p>In this article</p>';
	for (var i=0; i<tags.length; ++i)
	{
		if(tags[i].nodeName=='H2')
		{
			sidebar+='<li><a href="#';
			sidebar+=tags.eq(i).attr('id');
			sidebar+='">';
			sidebar+=tags.eq(i).html();
			sidebar+='</a>';

			if(i==tags.length-1||tags[i+1].nodeName=='H2')
			{
				sidebar+='</li>'
			}
		}
		else if(tags[i].nodeName=='H3')
		{
			if(i>0&&tags[i-1].nodeName=='H2')
			{
				sidebar+='<ul class="nav nav-stacked">';
			}

			sidebar+='<li><a href="#';
			sidebar+=tags.eq(i).attr('id');
			sidebar+='">';
			sidebar+=tags.eq(i).html();
			sidebar+='</a></li>';
			if(i==tags.length-1||tags[i+1].nodeName=='H2')
			{
				sidebar+='</ul></li>';
			}
		}
	}
	sidebar+='<a class="btn btn-default" id="btn-github-star" href="https://github.com/captainjtx/codingground" target="_blank">';
	sidebar+='<svg height="16" width="16">';
	sidebar+='<path d="M8 0C3.58 0 0 3.58 0 8c0 3.54 2.29 6.53 5.47 7.59.4.07.55-.17.55-.38 0-.19-.01-.82-.01-1.49-2.01.37-2.53-.49-2.69-.94-.09-.23-.48-.94-.82-1.13-.28-.15-.68-.52-.01-.53.63-.01 1.08.58 1.23.82.72 1.21 1.87.87 2.33.66.07-.52.28-.87.51-1.07-1.78-.2-3.64-.89-3.64-3.95 0-.87.31-1.59.82-2.15-.08-.2-.36-1.02.08-2.12 0 0 .67-.21 2.2.82.64-.18 1.32-.27 2-.27.68 0 1.36.09 2 .27 1.53-1.04 2.2-.82 2.2-.82.44 1.1.16 1.92.08 2.12.51.56.82 1.27.82 2.15 0 3.07-1.87 3.75-3.65 3.95.29.25.54.73.54 1.48 0 1.07-.01 1.93-.01 2.2 0 .21.15.46.55.38A8.013 8.013 0 0 0 16 8c0-4.42-3.58-8-8-8z"></path>';
	sidebar+='</svg><div>Star</div><a class="btn btn-default" id="btn-star-count"><div>0</div></a></a></ul></nav>';
	$('#right-sidebar').html(sidebar);
});

$('body').scrollspy({ 
	target: '.bs-docs-sidebar',
	offset: 40
});
//var codeURL="https://raw.githubusercontent.com/captainjtx/freecoder/master/DataStructures/";
