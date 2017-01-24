var codeURL="https://raw.githubusercontent.com/captainjtx/freecoder/master/SortingAlgorithms/";
var imgURL="https://raw.githubusercontent.com/captainjtx/blog/master/image/";
//var codeURL="/lib/freecoder/SortingAlgorithms/";
//var imgURL="/image/";
$(function(){
	$('#img-partition').attr('src',imgURL+"partition.png");
	$('#img-max-heap').attr('src',imgURL+"max-heap.png");
	$('#img-build-max-heap').attr('src',imgURL+"build-max-heap.png");
	$('#img-radix').attr('src',imgURL+"radix-sort.png");
	$('#img-bucket').attr('src',imgURL+"bucket-sort.png");
	githubStars("captainjtx/freecoder",function(stars){
		$('#btn-star-count div').html(stars);
	});
	$("p.note").prepend("<strong>Note: </strong>");
});
$.when(
		$.get(codeURL+'insertSort.cpp', function (result) {
			$('#user-src-1').text(result);
		}),
		$.get(codeURL+'quickSort.cpp', function (result) {
			$('#user-src-2').text(result);
		}),
		$.get(codeURL+'mergeSort.cpp', function (result) {
			$('#user-src-3').text(result);
		}),
		$.get(codeURL+'heapSort.cpp', function (result) {
			$('#user-src-4').text(result);
		}),
		$.get(codeURL+'countSort.cpp', function (result) {
			$('#user-src-5').text(result);
		}),
		$.get(codeURL+'radixSort.cpp', function (result) {
			$('#user-src-6').text(result);
		}),
		$.get(codeURL+'bucketSort.cpp', function (result) {
			$('#user-src-7').text(result);
		})
).then(function(){
	initAceEditor();
	//$.getScript('/js/prism.js');
});

$('body').scrollspy({ 
	target: '.bs-docs-sidebar',
	offset: 40
});

