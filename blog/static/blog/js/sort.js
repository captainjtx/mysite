$(function(){
	var scripts = document.getElementsByTagName("script"),src = scripts[scripts.length-1].src;
	$('#img-insertion').attr('src',src+"/../../image/insertion-sort.png");
	$('#img-partition').attr('src',src+"/../../image/partition.png");
	$('#img-max-heap').attr('src',src+"/../../image/max-heap.png");
	$('#img-build-max-heap').attr('src',src+"/../../image/build-max-heap.png");
	$('#img-radix').attr('src',src+"/../../image/radix-sort.png");
	$('#img-bucket').attr('src',src+"/../../image/bucket-sort.png");

});


$.when(
		var scripts = document.getElementsByTagName("script"),src = scripts[scripts.length-1].src;
		$.get(src+'/../../code/SortingAlgorithms/insertSort.cpp', function (result) {
			$('#user-src-1').text(result);
		}),
		$.get(src+'/../../code/SortingAlgorithms/mergeSort.cpp', function (result) {
			$('#user-src-2').text(result);
		}),
		$.get(src+'/../../code/SortingAlgorithms/quickSort.cpp', function (result) {
			$('#user-src-3').text(result);
		}),
		$.get(src+'/../../code/SortingAlgorithms/heapSort.cpp', function (result) {
			$('#user-src-4').text(result);
		}),
		$.get(src+'/../../code/SortingAlgorithms/countSort.cpp', function (result) {
			$('#user-src-5').text(result);
		}),
		$.get(src+'/../../code/SortingAlgorithms/radixSort.cpp', function (result) {
			$('#user-src-6').text(result);
		}),
		$.get(src+'/../../code/SortingAlgorithms/bucketSort.cpp', function (result) {
			$('#user-src-7').text(result);
		})
).then(function(){
	initAceEditor();
	//$.getScript('/js/prism.js');
});
