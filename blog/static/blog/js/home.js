//Define a custom non-enumerable sortBy function using a Schwartzian transform on all arrays :
//If your date is not directly comparable, make a comparable date out of it, e.g.
//array.sortBy(function(o){ return new Date( o.date ) });

(function(){
  if (typeof Object.defineProperty === 'function'){
    try{Object.defineProperty(Array.prototype,'sortBy',{value:sb}); }catch(e){}
  }
  if (!Array.prototype.sortBy) Array.prototype.sortBy = sb;

  function sb(f){
    for (var i=this.length;i;){
      var o = this[--i];
      this[i] = [].concat(f.call(o,o,i),o);
    }
    this.sort(function(a,b){
      for (var i=0,len=a.length;i<len;++i){
        if (a[i]!=b[i]) return a[i]<b[i]?-1:1;
      }
      return 0;
    });
    for (var i=this.length;i;){
      this[--i]=this[i][this[i].length-1];
    }
    return this;
  }
})();
// Sort by date, then score (reversed), then name
array.sortBy(function(o){ return [ o.date, -o.score, o.name ] };
$(function(){
	$.getJSON("/blog/get/all/articles",function(data){
		console.log(data.articles);
		var content='';
		articles=data.articles;
		articles.sortBy(function(o){ return new Date( -o.datetime ) });
		for (var index=0; index<articles.length; ++index)
		{
			content+='<div class="excerpt-item">';
			var date=new Date(articles[index].datetime);
			content+='<a class="excerpt-title" href="/blog/';
			content+=articles[index].file;
			content+='">';
			content+=articles[index].title;
			content+='</a>';
			content+='<p class="excerpt-time">';
			content+=monthNames[date.getMonth()];
			content+=" ";
			content+=date.getDay();
			content+=" '";
			content+=date.getFullYear().toString().substr(2,2);
			content+=" at ";
			content+=date.getHours();
			content+=":";
			content+=pad(date.getMinutes());
			content+='</p>';
			content+='<p class="excerpt-content">';
			content+=articles[index].excerpt;
			content+='</p></br>';
			content+='</div>'
		}

		$('#excerpts').html(content);
	});
});
