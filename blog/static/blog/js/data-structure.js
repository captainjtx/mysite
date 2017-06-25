$(function(){
	var scripts = document.getElementsByTagName("script"),src = scripts[scripts.length-1].src;
	$('#img-stack').attr('src',src+"/../../image/stack.png");
	$('#img-queue').attr('src',src+"/../../image/queue.png");
	$('#img-list').attr('src',src+"/../../image/list.png");
	$('#img-radix').attr('src',src+"/../../image/radix-sort.png");
	$('#img-bucket').attr('src',src+"/../../image/bucket-sort.png");

	$.when(
			$.get(src+'/../../code/DataStructures/stack.cpp', function (result) {
				$('#user-src-1').text(result);
			}),
			$.get(src+'/../../code/DataStructures/queue.cpp', function (result) {
				$('#user-src-2').text(result);
			}),
			$.get(src+'/../../code/DataStructures/list.cpp', function (result) {
				$('#user-src-3').text(result);
			}),
			$.get(src+'/../../code/DataStructures/list-sentinel.cpp', function (result) {
				$('#user-src-4').text(result);
			})
	      ).then(function(){
		initAceEditor();
	});
});
