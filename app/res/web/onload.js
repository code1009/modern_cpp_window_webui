/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class CPPMessageHandler
{
	_value;

	constructor() 
	{
		this._value = 0;
	}

	onHandle(name) 
	{
		const body = document.querySelector("body");

		var html;
		

		html = "<div>";
		html += "<pre>{";
		html += name;
		html += "}: C++에서 보냄";
		html += "</pre>";
		html += "</div>";

		body.insertAdjacentHTML("beforeEnd", html);
	}
};





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
let _cppMessageHandler;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
function coreEntry() 
{
	//-----------------------------------------------------------------------
	uiSetting();


	//-----------------------------------------------------------------------
	_cppMessageHandler = new CPPMessageHandler();

	//-----------------------------------------------------------------------
	window.chrome.webview.addEventListener(
		"message", 
		arg => 
		{
			if (("id" in arg.data) && ("name" in arg.data))
			{
				var id = arg.data.id;
				var name = arg.data.name;


				switch(id)
				{
				case "100":
					_cppMessageHandler.onHandle(name);
					break;
				}
			}
		}
	);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
window.onload = function ()
{
	coreEntry();
}
