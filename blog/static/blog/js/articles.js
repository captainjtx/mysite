function initAceEditor()
{
	var elts = document.getElementsByClassName('code-block'); 
	for (var index = 0; index < elts.length; ++index) 
	{ 
		var code_id = elts[index].getAttribute('id'); 
		var parts  = code_id.split("-", 3);
		var btn_id = 'code-run-'+parts[2];

		var editor= ace.edit("user-src-"+parts[2]);
		editor.setTheme("ace/theme/twilight");
		editor.getSession().setMode("ace/mode/c_cpp");

		$('#user-src-'+parts[2]).after("<a target='_blank' class='btn btn-success code-btn' id='"+btn_id+"'>Run the code</a>");
		$('#user-src-'+parts[2]).before("<div class='ace-coliru-declare'>Powered by <a target='_blank' href='https://ace.c9.io/'>Ace editor</a> and <a target='_blank' href='http://coliru.stacked-crooked.com/'>Coliru online compiler</a></div>");
	} 
	registerButtonEvents();
}

