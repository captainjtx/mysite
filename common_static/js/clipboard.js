$.getScript('/lib/clipboard/dist/clipboard.min.js').done(function(script,textStatus){
	var cpy="<button class='copy-btn' data-clipboard-target='#' data-toggle='tooltip' data-placement='top' title='Copy to clipboard' ><img src='/image/clippy.svg' alt='Copy to clipboard'></button>";
	$(cpy).insertAfter('.code-block');

	$('.copy-btn').each(function(){
		//this requires that the code must have an id
		var prev_selector='#'+$(this).prev().children().attr('id');
		$(this).attr('data-clipboard-target',prev_selector);
	});

	$('[data-toggle="tooltip"]').tooltip();
	$('[data-toggle="tooltip"]').hover(
			function(){
				$('[data-toggle="tooltip"]').attr('data-original-title', 'Copy to clipboard');
			}
			);
	function clearSelection(ele)
	{

		if (window.getSelection) {
			if (window.getSelection().empty) {  // Chrome
				window.getSelection().empty();
			} else if (window.getSelection().removeAllRanges) {  // Firefox
				window.getSelection().removeAllRanges();
			}
		} else if (document.selection) {  // IE?
			document.selection.empty();
		}
	}

	var clipboard = new Clipboard('.copy-btn');
	clipboard.on('success', function(e) {
		var ele=$(event.target);
		if(ele.attr('class')!='copy-btn') 
		{
			ele=$(event.target.parentNode);	
		}

		ele.attr('data-original-title', 'Copied').tooltip('show');
		e.clearSelection();
	});

	clipboard.on('error', function(e) {
		var ele=$(event.target);
		if(ele.attr('class')!='copy-btn') 
		{
			ele=$(event.target.parentNode);	
		}

		ele.attr('data-original-title', 'Failed').tooltip('show');
	});
});
