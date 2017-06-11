$(function(){
	$('#img-insertion').attr('src',"../image/insertion-sort.png");
	$('#img-partition').attr('src',"../image/partition.png");
	$('#img-max-heap').attr('src',"../image/max-heap.png");
	$('#img-build-max-heap').attr('src',"../image/build-max-heap.png");
	$('#img-radix').attr('src',"../image/radix-sort.png");
	$('#img-bucket').attr('src',"../image/bucket-sort.png");
});
$.when(
		$.get('../code/SortingAlgorithms/insertSort.cpp', function (result) {
			$('#user-src-1').text(result);
		}),
		$.get('../code/SortingAlgorithms/mergeSort.cpp', function (result) {
			$('#user-src-2').text(result);
		}),
		$.get('../code/SortingAlgorithms/quickSort.cpp', function (result) {
			$('#user-src-3').text(result);
		}),
		$.get('../code/SortingAlgorithms/heapSort.cpp', function (result) {
			$('#user-src-4').text(result);
		}),
		$.get('../code/SortingAlgorithms/countSort.cpp', function (result) {
			$('#user-src-5').text(result);
		}),
		$.get('../code/SortingAlgorithms/radixSort.cpp', function (result) {
			$('#user-src-6').text(result);
		}),
		$.get('../code/SortingAlgorithms/bucketSort.cpp', function (result) {
			$('#user-src-7').text(result);
		})
).then(function(){
	initAceEditor();
	//$.getScript('/js/prism.js');
});


