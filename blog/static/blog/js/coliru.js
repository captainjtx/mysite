/* Compile Source *****************************************************/
function compileColiru(sourceCode, coliruReadyResponse)
{
    var linkOptions = '';

    var compileCommand = 
    [ 
        //'g++-4.8 -std=c++11 ', 
        'clang++ -std=c++11 ', 
        //'clang++ -std=c++11 -stdlib=libc++ -lsupc++ ', 
        '-O2 -Wall -pedantic -pthread ', 
        'main.cpp ', 
        linkOptions, 
        '&& ./a.out; echo COLIRUSTATUS $?'
    ].join(''); 


    var coliruConnection = new XMLHttpRequest(); 

    coliruConnection.onreadystatechange = 
        function() 
        { 
            if (coliruConnection.readyState == 4) 
            { 
                if (coliruConnection.status != 200) 
                { 
                    coliruReadyResponse(coliruConnection.response, 'error'); 
                } 
                else 
                { 
                    // Extract the last return code as the status.
                    var rawResponse = coliruConnection.response; 
                    var pattern = /^([\s\S]*)COLIRUSTATUS (\d+)\n$/m; 
                    var splitResponse = rawResponse.match(pattern); 
 

                    coliruReadyResponse( splitResponse[1], 
                                          parseInt(splitResponse[2])); 
                } 
            } 
            else 
            { 
                coliruReadyResponse(coliruConnection.response, 'running'); 
            } 
        } 
 

    coliruConnection.open( "POST", 
                           "http://coliru.stacked-crooked.com/compile", 
			   true); 

    coliruConnection.send( 
             JSON.stringify({ "cmd": compileCommand, "src": sourceCode })); 
}


/* Display the Output *************************************************/
function updateColiruOutput(out_id)
{
    var editor= ace.edit("user-src-"+out_id);
    var sourceCode = editor.getValue();

    compileColiru(  sourceCode,
                    function(response, state) 
                    { 
                        var outputArea   = document.getElementById("output-"+out_id);
			outputArea.style.display='block';

                        if (state == 'running') 
                        { 
                            outputArea.textContent = 'Running...\n'; 
                        } 
                        else if (state == 'error') 
                        { 
				outputArea.textContent='Error: ' + response;
                        } 
                        else 
                        { 
				outputArea.textContent = ''; 

				if (response != '') 
				{ 
					var formattedOutput = document.createElement('pre'); 
					outputArea.appendChild(formattedOutput); 
					formattedOutput.textContent = response; 
				} 
			}
		    }
               ); 
}


/* Initiate the coliru compiler */
function RunColiruEx(srcId) 
{ 
  var src_code_id = "user-src-" + srcId;
  
  var sourceArea = document.getElementById(src_code_id);
  updateColiruOutput(srcId);
}

/* Setup **************************************************************/
/* Associate the proper handler for identified buttons. */
function addButtonEvent(ctrl_button) 
{ 
	var btn_id = ctrl_button.getAttribute('id'); 
	var parts  = btn_id.split("-", 3);
	if ('code' == parts[0])
	{
		if ( 'init' == parts[1] ) 
		{
			ctrl_button.onclick = function() { InitColiruEx(parts[2]); };
		}
		else if ( 'run' == parts[1] ) 
		{
			ctrl_button.onclick = function() { RunColiruEx(parts[2]); };
		}
		else if ( 'exit' == parts[1] ) 
		{
			ctrl_button.onclick = function() { ExitColiruEx(parts[2]); };
		}
	}
}


/* Examine each div for identification as a button */
/* associated with displaying coliru compiled code. */
function registerButtonEvents() 
{ 
    var elts = document.getElementsByClassName('code-btn'); 
 
    for (var index = 0; index < elts.length; ++index) 
    { 
        addButtonEvent(elts[index]); 
    } 
}
 

