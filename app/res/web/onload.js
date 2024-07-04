/////////////////////////////////////////////////////////////////////////////
//===========================================================================
function uiSetting()
{
	window.onkeydown = 
		function(event) 
		{
			if (event.ctrlKey) 
			{
				switch (event.key) 
				{
				case 'a':
				case 'A':
					
				case 'r':
				case 'R':
				case 'd':
				case 'D':
				case 't':
				case 'T':
				case 'p':
				case 'P':
				case '+':
				case '-':
				case '_':
				case '=':
					break;

				default:
					return;
				}
		
				event.preventDefault();
			}
		};

	// Prevent zooming the UI
	window.addEventListener(
		"wheel", 
		function(event) 
		{
			if (event.ctrlKey) 
			{
				event.preventDefault();
			}
		},
		{
			passive: false 
		}
	);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
function coreEntry() 
{
	//-----------------------------------------------------------------------
	uiSetting();
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
window.onload = function ()
{
	coreEntry();
}
