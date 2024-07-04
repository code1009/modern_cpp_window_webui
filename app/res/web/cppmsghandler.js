/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class cppMsgHandler
{
	_value;

	constructor() 
	{
		this._value = 0;
		
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
						this.onHandle100(name);
						break;
					}
				}
			}
		);
	}

	onHandle100(name) 
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
}




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
/*

let _cppMsgHandler;

_cppMsgHandler = new cppMsgHandler();

*/




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
export { cppMsgHandler };



