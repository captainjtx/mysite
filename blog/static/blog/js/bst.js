(function(){
	var scripts = document.getElementsByTagName("script"),src = scripts[scripts.length-1].src;
	$(function(){
		$('#img-bst').attr('src',src+"/../../image/bst.png");
		$('#img-tree-walk').attr('src',src+"/../../image/tree-walk.png");
	});

	$.when(
			$.get(src+'/../../code/DataStructures/bst-walk.cpp', function (result) {
				$('#user-src-1').text(result);
			}),
			$.get(src+'/../../code/DataStructures/bst-query.cpp', function (result) {
				$('#user-src-2').text(result);
			})
		).then(function(){
				initAceEditor();
				//$.getScript('/js/prism.js');
			});

})();
