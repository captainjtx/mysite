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
	$.getJSON("/blog/comment/get/"+$('.blog-post-title').text(),function(data){
		console.log(data.comment);
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
});

$('body').scrollspy({ 
		target: '.bs-docs-sidebar',
		offset: 40
	});
//var codeURL="https://raw.githubusercontent.com/captainjtx/freecoder/master/DataStructures/";
