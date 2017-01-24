var codeURL="https://raw.githubusercontent.com/captainjtx/freecoder/master/DataStructures/";
var imgURL="https://raw.githubusercontent.com/captainjtx/blog/master/image/";
//var codeURL="/lib/freecoder/DataStructures/";
//var imgURL="/image/";
$(function(){
	$('#img-stack').attr('src',imgURL+"stack.png");
	$('#img-queue').attr('src',imgURL+"queue.png");
	$('#img-list').attr('src',imgURL+"list.png");
	$('#img-radix').attr('src',imgURL+"radix-sort.png");
	$('#img-bucket').attr('src',imgURL+"bucket-sort.png");
	githubStars("captainjtx/freecoder",function(stars){
		$('#btn-star-count div').html(stars);
	});
	$("p.note").prepend("<strong>Note: </strong>");
});
$.when(
		$.get(codeURL+'stack.cpp', function (result) {
			$('#user-src-1').text(result);
		}),
		$.get(codeURL+'queue.cpp', function (result) {
			$('#user-src-2').text(result);
		}),
		$.get(codeURL+'list.cpp', function (result) {
			$('#user-src-3').text(result);
		}),
		$.get(codeURL+'list-sentinel.cpp', function (result) {
			$('#user-src-4').text(result);
		})
).then(function(){
	initAceEditor();
});
$('body').scrollspy({ 
		target: '.bs-docs-sidebar',
		offset: 40
	});

