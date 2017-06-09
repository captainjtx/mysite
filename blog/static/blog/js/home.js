$(function(){
	$.getJSON("/blog/get/all/articles",function(data){
		console.log(data.articles);
		var content='';
		for (var index=0; index<data.articles.length; ++index)
		{
			content+='<div class="comment-content">';
			content+=data.articles[index].excerpt;
			content+='</div></br>';
			content+='<div class="comment-reader">';
			content+='<p>';

			var date=new Date(data.articles[index].datetime);
			content+=monthNames[date.getMonth()];
			content+=" ";
			content+=date.getDay();
			content+=" '";
			content+=date.getFullYear().toString().substr(2,2);
			content+=" at ";
			content+=date.getHours();
			content+=":";
			content+=pad(date.getMinutes());

			content+='</br>';
			content+=data.articles[index].title;
			content+='</p></div>';
		}

		$('#excerpts').html(content);
	});
});
