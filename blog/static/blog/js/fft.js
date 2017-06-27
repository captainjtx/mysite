(function(){
	var scripts = document.getElementsByTagName("script"),src = scripts[scripts.length-1].src;
	$(function(){
		$('#img-recursion-tree').attr('src',src+"/../../image/bit-reversal.png");
	});

	$.when(
			$.get(src+'/../../code/DSP/recursive_fft.cpp', function (result) {
				$('#user-src-1').text(result);
			}),
			$.get(src+'/../../code/DSP/iterative_fft.cpp', function (result) {
				$('#user-src-2').text(result);
			})
		).then(function(){
				initAceEditor();
				//$.getScript('/js/prism.js');
			});

})();
