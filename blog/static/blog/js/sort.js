$(function(){
	$('#img-partition').attr('src',staticURL+"image/partition.png");
	$('#img-max-heap').attr('src',staticURL+"image/max-heap.png");
	$('#img-build-max-heap').attr('src',staticURL+"image/build-max-heap.png");
	$('#img-radix').attr('src',staticURL+"image/radix-sort.png");
	$('#img-bucket').attr('src',staticURL+"image/bucket-sort.png");
});
$.when(
		$.get(staticURL+'code/SortingAlgorithms/insertSort.cpp', function (result) {
			$('#user-src-1').text(result);
		}),
		$.get(staticURL+'code/SortingAlgorithms/mergeSort.cpp', function (result) {
			$('#user-src-2').text(result);
		}),
		$.get(staticURL+'code/SortingAlgorithms/quickSort.cpp', function (result) {
			$('#user-src-3').text(result);
		}),
		$.get(staticURL+'code/SortingAlgorithms/heapSort.cpp', function (result) {
			$('#user-src-4').text(result);
		}),
		$.get(staticURL+'code/SortingAlgorithms/countSort.cpp', function (result) {
			$('#user-src-5').text(result);
		}),
		$.get(staticURL+'code/SortingAlgorithms/radixSort.cpp', function (result) {
			$('#user-src-6').text(result);
		}),
		$.get(staticURL+'code/SortingAlgorithms/bucketSort.cpp', function (result) {
			$('#user-src-7').text(result);
		})
).then(function(){
	initAceEditor();
	//$.getScript('/js/prism.js');
});


