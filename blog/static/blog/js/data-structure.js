$(function(){
	$('#img-stack').attr('src',staticURL+"image/stack.png");
	$('#img-queue').attr('src',staticURL+"image/queue.png");
	$('#img-list').attr('src',staticURL+"image/list.png");
	$('#img-radix').attr('src',staticURL+"image/radix-sort.png");
	$('#img-bucket').attr('src',staticURL+"image/bucket-sort.png");
});
$.when(
		$.get(staticURL+'code/DataStructures/stack.cpp', function (result) {
			$('#user-src-1').text(result);
		}),
		$.get(staticURL+'code/DataStructures/queue.cpp', function (result) {
			$('#user-src-2').text(result);
		}),
		$.get(staticURL+'code/DataStructures/list.cpp', function (result) {
			$('#user-src-3').text(result);
		}),
		$.get(staticURL+'code/DataStructures/list-sentinel.cpp', function (result) {
			$('#user-src-4').text(result);
		})
).then(function(){
	initAceEditor();
});
