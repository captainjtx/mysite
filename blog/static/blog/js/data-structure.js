$(function(){
	$('#img-stack').attr('src',"../image/stack.png");
	$('#img-queue').attr('src',"../image/queue.png");
	$('#img-list').attr('src',"../image/list.png");
	$('#img-radix').attr('src',"../image/radix-sort.png");
	$('#img-bucket').attr('src',"../image/bucket-sort.png");
});
$.when(
		$.get('../code/DataStructures/stack.cpp', function (result) {
			$('#user-src-1').text(result);
		}),
		$.get('../code/DataStructures/queue.cpp', function (result) {
			$('#user-src-2').text(result);
		}),
		$.get('../code/DataStructures/list.cpp', function (result) {
			$('#user-src-3').text(result);
		}),
		$.get('../code/DataStructures/list-sentinel.cpp', function (result) {
			$('#user-src-4').text(result);
		})
).then(function(){
	initAceEditor();
});
