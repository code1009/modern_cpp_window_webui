/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class MyCanvas
{
	_test; // public _ 그냥 붙인거
	#documentElement; // private
	#ctx;

	constructor(de) 
	{
		this._test = 0;

		this.#documentElement = de;
		this.#ctx = this.#documentElement.getContext("2d");

		this.#ctx.fillStyle = "white";
		this.#ctx.fillRect(0, 0, this.#documentElement.width, this.#documentElement.height);
	}

	draw() 
	{
		this.#ctx.beginPath();
		this.#ctx.arc(95, 50, 40, 0, 2 * Math.PI);
		this.#ctx.stroke();
	}

	draw2() 
	{
		this.#ctx.moveTo(0, 0);
		this.#ctx.lineTo(200, 100);
		this.#ctx.stroke();
	}
}





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
}





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
let _myCanvas;
let _cppMessageHandler;

function coreEntry() 
{
	//-----------------------------------------------------------------------
	uiSetting();


	//-----------------------------------------------------------------------
	var myCanvasDocElement = document.getElementById("myCanvas");

	_myCanvas = new MyCanvas(myCanvasDocElement);
	_myCanvas.draw();

	//-----------------------------------------------------------------------
	_cppMessageHandler = new CPPMessageHandler();


	//-----------------------------------------------------------------------
	var button1 = document.getElementById("button1");
	var button2 = document.getElementById("button2");
	var button3 = document.getElementById("button3");
	var button4 = document.getElementById("button4");
	var button5 = document.getElementById("button5");


	button1.addEventListener(
		"click", 
		function() 
		{
			alert("Hello world");
		}
	);

	button2.addEventListener(
		"click", 
		function() 
		{
			_myCanvas.draw2();
		}
	);

	button3.addEventListener(
		"click", 
		function() 
		{
			window.chrome.webview.postMessage("javascript-message");
		}
	);

	button4.addEventListener(
		"click", 
		function() 
		{
			let jsonMessage = 
			{
				id: "command",
				args: 
				{
					from: 1,
					count: 100
				}
			};
			
			window.chrome.webview.postMessage(jsonMessage);
		}
	);

	button5.addEventListener(
		"click", 
		function() 
		{
		}
	);


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
