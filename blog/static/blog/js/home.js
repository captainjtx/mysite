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
			commentContent+=date.getDay();
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
