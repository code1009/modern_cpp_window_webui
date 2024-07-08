/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"
#include "JsonMessageService.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
using namespace Microsoft::WRL;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace app
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
WebView::WebView(HWND hParent)
{
	//-----------------------------------------------------------------------
	registerWindowMessageHandler();


	//-----------------------------------------------------------------------
	initializeWindowClass();
	registerWindowClass();


	//-----------------------------------------------------------------------
	DWORD style = WS_CHILD | WS_VISIBLE; // | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	DWORD styleEx = 0; // WS_EX_CLIENTEDGE;
	std::wstring windowText;
	RECT rect;


	windowText = L"WebView";
	GetClientRect(hParent, &rect);


	//-----------------------------------------------------------------------
	HWND hwnd;


	hwnd = createWindow(
		hParent,
		rect,
		windowText.c_str(),
		static_cast<DWORD>(style),
		static_cast<DWORD>(styleEx)
	);
	if (!hwnd)
	{
		throw std::wstring(L"WebView::WebView(): createWindow() failed");
	}


	//-----------------------------------------------------------------------
	registerContentsMap();


	//-----------------------------------------------------------------------
	WUI_TRACE(L"createWebView-begin");
	createWebView();
	WUI_TRACE(L"createWebView-end");


	//-----------------------------------------------------------------------
	::ShowWindow(getHandle(), SW_SHOW);
	::UpdateWindow(getHandle());


	//-----------------------------------------------------------------------
	/*
	std::wstring text;


	text = getWindowText(this);
	text = L"WebView";
	setWindowText(this, text);
	text = getWindowText(this);
	wui::debugPrintln(text);
	*/
}

WebView::~WebView()
{
}

void WebView::registerWindowMessageHandler(void)
{
	getWindowMessageHandler(WM_CREATE) = [this](wui::WindowMessage& windowMessage) { onCreate(windowMessage); };
	getWindowMessageHandler(WM_DESTROY) = [this](wui::WindowMessage& windowMessage) { onDestory(windowMessage); };
	getWindowMessageHandler(WM_CLOSE) = [this](wui::WindowMessage& windowMessage) { onClose(windowMessage); };
	getWindowMessageHandler(WM_SIZE) = [this](wui::WindowMessage& windowMessage) { onSize(windowMessage); };
	getWindowMessageHandler(WM_DPICHANGED) = [this](wui::WindowMessage& windowMessage) { onDPIChanged(windowMessage); };
	getWindowMessageHandler(WM_COMMAND) = [this](wui::WindowMessage& windowMessage) { onCommand(windowMessage); };
}

void WebView::onCreate(wui::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	//SetWindowTextW(windowMessage.hWnd, L"WebView");


	defaultWindowMessageHandler(windowMessage);
}

void WebView::onDestory(wui::WindowMessage& windowMessage)
{
	WUI_TRACE(L"destroyWebView-begin");
	destroyWebView();
	WUI_TRACE(L"destroyWebView-end");
}

void WebView::onClose(wui::WindowMessage& windowMessage)
{
}

void WebView::onSize(wui::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	wui::WM_SIZE_WindowMessageManipulator windowMessageManipulator(&windowMessage);


	//-----------------------------------------------------------------------
	RECT rect;


	if (_ContentsWebViewController != nullptr)
	{
		::GetClientRect(getHandle(), &rect);

		_ContentsWebViewController->put_Bounds(rect);
	}
}

void WebView::onDPIChanged(wui::WindowMessage& windowMessage)
{
	RECT* pWindowRect = reinterpret_cast<RECT*>(windowMessage.lParam);


	wui::setWindowPos(this, HWND_TOP, *pWindowRect, SWP_SHOWWINDOW);
}

void WebView::onCommand(wui::WindowMessage& windowMessage)
{
	wui::WM_COMMAND_WindowMessageManipulator windowMessageManipulator(&windowMessage);

/*
	switch (windowMessageManipulator.nID())
	{
	case IDM_TEST1:
		onTest1(windowMessage);
		return;
		break;

	case IDM_TEST2:
		onTest2(windowMessage);
		return;
		break;

	default:
		break;
	}
*/

	defaultWindowMessageHandler(windowMessage);
}

void WebView::onTest1(wui::WindowMessage& windowMessage)
{
}

void WebView::onTest2(wui::WindowMessage& windowMessage)
{
}

//===========================================================================
int WebView::getDPIAwareBound(int bound) const
{
	constexpr int DEFAULT_DPI = 96;

	return (bound * GetDpiForWindow(getHandle()) / DEFAULT_DPI);
}

//===========================================================================
std::wstring WebView::getContentsDataFolder(void) const
{
	WCHAR path[MAX_PATH];


	std::wstring dataDirectory;
	HRESULT hr;
	
	
	// L"C:\\Users\\USER\\AppData\\Roaming";
	hr = SHGetFolderPathW(nullptr, CSIDL_APPDATA, NULL, 0, path);
	if (SUCCEEDED(hr))
	{
		dataDirectory = std::wstring(path);

		dataDirectory.append(L"\\wui\\");
	}
	else
	{
		dataDirectory = std::wstring(L".\\");
	}

	dataDirectory.append(L"app");
	dataDirectory.append(L"\\data");
	

	return dataDirectory;
}

std::wstring WebView::getContentsHost(void) const
{
	std::wstring host = L"https://www.code1009.com";


	return host;
}

std::wstring WebView::getContentsURI(const std::wstring& urn) const
{
	std::wstring uri;


	uri = getContentsHost() + urn;

	return uri;
}

std::wstring WebView::parseContentsURN(const std::wstring& uri) const
{
	std::wstring host = getContentsHost();
	std::wstring urn;


	if (0 == uri.compare(0, host.size(), host))
	{
		urn = uri.substr(host.size());
	}


	auto pos = urn.find_first_of(L'?');


	if (pos != std::string::npos)
	{
		return urn.substr(0, pos);
	}


	return urn;
}

void WebView::registerContentsMap(void)
{
	//------------------------------------------------------------------------
	std::vector<std::wstring> resourceCollection
	{
		L"/w2ui/master/dist/w2ui.css",
		L"/w2ui/master/dist/w2ui.js",
		L"/w2ui/master/dist/w2ui.es6.js",
		L"/w2ui/master/dist/w2ui.es6.min.js",
		L"/w2ui/master/dist/w2ui.min.css",
		L"/w2ui/master/dist/w2ui.min.js",
		L"/index.html",
		L"/basic.css",
		L"/basic.js",
		L"/onload.js",
		L"/cppmsghandler.js",
		L"/page0/index.html",
		L"/page1/index.html"
	};


	for (std::wstring res : resourceCollection)
	{
		_ContentsMap.registerWebContents(res, std::make_shared<WebContentsResourceStream>(res));
	}

	//_ContentsMap.registerWebContents(L"/favicon.ico", std::make_shared<WebContentsResourceStream>(L"favicon.ico"));


	//------------------------------------------------------------------------
	JsonMessageService jsonMessageService(this);
	std::wstring json;


	json = jsonMessageService.getMessage_page1_list0_json();

	_ContentsMap.registerWebContents(L"/page1/list0.json", std::make_shared<WebContentsUTF8StringStream>(json));


	//------------------------------------------------------------------------
	//_StartURI = getContentsURI(L"/page1/list0.json");
	_StartURI = getContentsURI(L"/index.html");
}


//===========================================================================
#pragma region webview2

//===========================================================================
void WebView::createWebView(void)
{	
	//-----------------------------------------------------------------------
	HRESULT hr;


	hr = CreateCoreWebView2EnvironmentWithOptions(
		nullptr, 
		getContentsDataFolder().c_str(),
		nullptr,
		Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
			[this](HRESULT hresult, ICoreWebView2Environment* env) -> HRESULT
			{
				//-----------------------------------------------------------------------
				RETURN_IF_FAILED(hresult);


				//-----------------------------------------------------------------------
				_ContentsWebViewEnvironment = env;


				//-----------------------------------------------------------------------
				HRESULT hr;


				hr = createContentsWebViewController();

				return hr;
			}
		).Get()
	);
}

void WebView::destroyWebView(void)
{
	//_ContentsWebViewController->Release(); DO NOT CALL!!!
	_ContentsWebViewEnvironment->Release();
}

HRESULT WebView::createContentsWebViewController(void)
{
	HRESULT hr;


	hr = _ContentsWebViewEnvironment->CreateCoreWebView2Controller(
		getHandle(),
		Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
			[this](HRESULT hresult, ICoreWebView2Controller* controller) -> HRESULT
			{
				RETURN_IF_FAILED(hresult);


				if (controller != nullptr)
				{
					//-----------------------------------------------------------------------
					_ContentsWebViewController = controller;
					

					//-----------------------------------------------------------------------
					HRESULT hr;


					//-----------------------------------------------------------------------
					hr = setupContentsWebViewController();
					RETURN_IF_FAILED(hr);


					//-----------------------------------------------------------------------
					hr = _ContentsWebViewController->get_CoreWebView2(&_ContentsWebView);
					RETURN_IF_FAILED(hr);


					//-----------------------------------------------------------------------
					hr = setupContentsWebViewSettings();
					RETURN_IF_FAILED(hr);


					//-----------------------------------------------------------------------
					hr = setupContentsWebView();
					RETURN_IF_FAILED(hr);


					//-----------------------------------------------------------------------
					hr = resizeContentsWebViewController();
					RETURN_IF_FAILED(hr);
				}

				return S_OK;
			}
		).Get()
	);

	return hr;
}

HRESULT WebView::setupContentsWebViewController(void)
{
	//-----------------------------------------------------------------------
	HRESULT hr;


	//-----------------------------------------------------------------------
	/*
	hr = resizeContentsWebViewController();
	RETURN_IF_FAILED(hr);
	*/


	//-----------------------------------------------------------------------
	wil::com_ptr<ICoreWebView2Controller4> controller4 = 
		_ContentsWebViewController.try_query<ICoreWebView2Controller4>();


	if (controller4)
	{
		hr = controller4->put_AllowExternalDrop(FALSE);
		RETURN_IF_FAILED(hr);
	}


	return S_OK;
}

HRESULT WebView::resizeContentsWebViewController(void)
{
	//-----------------------------------------------------------------------
	HRESULT hr;


	//-----------------------------------------------------------------------
	RECT rect;


	::GetClientRect(getHandle(), &rect);


	hr = _ContentsWebViewController->put_Bounds(rect);
	RETURN_IF_FAILED(hr);


	return S_OK;
}

HRESULT WebView::setupContentsWebView(void)
{
	//-----------------------------------------------------------------------
	HRESULT hr;


	//-----------------------------------------------------------------------
	hr = ContentsWebView_setupWebResourceRequestedFilter();
	RETURN_IF_FAILED(hr);

	hr = ContentsWebView_setupWebMessageReceived();
	RETURN_IF_FAILED(hr);

	hr = ContentsWebView_registerEventHandler();
	RETURN_IF_FAILED(hr);


	//-----------------------------------------------------------------------
	navigate(_StartURI);


	return S_OK;
}

HRESULT WebView::setupContentsWebViewSettings(void)
{
	//-----------------------------------------------------------------------
	HRESULT hr;


	//-----------------------------------------------------------------------
	wil::com_ptr<ICoreWebView2Settings>  _ContentsWebViewSettings;
	wil::com_ptr<ICoreWebView2Settings2> _ContentsWebViewSettings2;
	wil::com_ptr<ICoreWebView2Settings3> _ContentsWebViewSettings3;
	wil::com_ptr<ICoreWebView2Settings4> _ContentsWebViewSettings4;
	wil::com_ptr<ICoreWebView2Settings5> _ContentsWebViewSettings5;
	wil::com_ptr<ICoreWebView2Settings6> _ContentsWebViewSettings6;
	wil::com_ptr<ICoreWebView2Settings7> _ContentsWebViewSettings7;
	wil::com_ptr<ICoreWebView2Settings8> _ContentsWebViewSettings8;


	//-----------------------------------------------------------------------
	hr = _ContentsWebView->get_Settings(&_ContentsWebViewSettings);
	RETURN_IF_FAILED(hr);

	_ContentsWebViewSettings2 = _ContentsWebViewSettings.try_query<ICoreWebView2Settings2>();
	_ContentsWebViewSettings3 = _ContentsWebViewSettings.try_query<ICoreWebView2Settings3>();
	_ContentsWebViewSettings4 = _ContentsWebViewSettings.try_query<ICoreWebView2Settings4>();
	_ContentsWebViewSettings5 = _ContentsWebViewSettings.try_query<ICoreWebView2Settings5>();
	_ContentsWebViewSettings6 = _ContentsWebViewSettings.try_query<ICoreWebView2Settings6>();
	_ContentsWebViewSettings7 = _ContentsWebViewSettings.try_query<ICoreWebView2Settings7>();
	_ContentsWebViewSettings8 = _ContentsWebViewSettings.try_query<ICoreWebView2Settings8>();


	//-----------------------------------------------------------------------
	if (_ContentsWebViewSettings2)
	{
		_ContentsWebViewSettings2->put_IsZoomControlEnabled(FALSE);
		_ContentsWebViewSettings2->put_AreDefaultContextMenusEnabled(FALSE);
	}

	if (_ContentsWebViewSettings3)
	{
		_ContentsWebViewSettings3->put_AreBrowserAcceleratorKeysEnabled(FALSE);
	}


	//-----------------------------------------------------------------------
#if 0
	std::wstring script;


	script = L"window.addEventListener(\"contextmenu\", window => {window.preventDefault();});";
	hr = _ContentsWebView->AddScriptToExecuteOnDocumentCreated(script.c_str(), nullptr);
	RETURN_IF_FAILED(hr);
#endif

	return S_OK;
}

HRESULT WebView::ContentsWebView_setupWebResourceRequestedFilter(void)
{
	//-----------------------------------------------------------------------
	HRESULT hr;


	//-----------------------------------------------------------------------
	std::wstring uri;


	uri = getContentsHost() + L"/*";
	hr = _ContentsWebView->AddWebResourceRequestedFilter(uri.c_str(), COREWEBVIEW2_WEB_RESOURCE_CONTEXT_ALL);
	RETURN_IF_FAILED(hr);


	//-----------------------------------------------------------------------
	hr = _ContentsWebView->add_WebResourceRequested(
		Callback<ICoreWebView2WebResourceRequestedEventHandler>(
			[this](ICoreWebView2* sender, ICoreWebView2WebResourceRequestedEventArgs* args)
			{
				//-----------------------------------------------------------------------
				HRESULT hr;


				//-----------------------------------------------------------------------
				COREWEBVIEW2_WEB_RESOURCE_CONTEXT resourceContext;


				hr = args->get_ResourceContext(&resourceContext);
				RETURN_IF_FAILED(hr);

				
				/*
				if (resourceContext != COREWEBVIEW2_WEB_RESOURCE_CONTEXT_IMAGE)
				{
					//return E_INVALIDARG;
				}
				*/


				//-----------------------------------------------------------------------
				wil::com_ptr<ICoreWebView2WebResourceRequest> webResourceRequest;


				hr = args->get_Request(&webResourceRequest);
				RETURN_IF_FAILED(hr);


				//-----------------------------------------------------------------------
				wil::unique_cotaskmem_string ucsUri;


				hr = webResourceRequest->get_Uri(&ucsUri);
				RETURN_IF_FAILED(hr);


				//-----------------------------------------------------------------------
				std::wstring uri(ucsUri.get());
				std::wstring urn = parseContentsURN(uri);


				WUI_TRACE(urn);


				//-----------------------------------------------------------------------
				WebContents* o = _ContentsMap.find(urn);


				//-----------------------------------------------------------------------
				wil::com_ptr<ICoreWebView2WebResourceResponse> response;
				wil::com_ptr<ICoreWebView2Environment> environment;
				wil::com_ptr<ICoreWebView2_2> webview;


				hr = _ContentsWebView->QueryInterface(IID_PPV_ARGS(&webview));
				RETURN_IF_FAILED(hr);

				hr = webview->get_Environment(&environment);
				RETURN_IF_FAILED(hr);


				if (nullptr == o)
				{
					hr = environment->CreateWebResourceResponse(
						nullptr, 
						404, L"Not found", 
						nullptr, 
						&response
					);
					RETURN_IF_FAILED(hr);
				}
				else
				{
					hr = environment->CreateWebResourceResponse(
						o->getStream(), 
						200, L"OK", 
						o->getHeaders().c_str(), 
						&response
					);
					RETURN_IF_FAILED(hr);
				}


				hr = args->put_Response(response.get());
				RETURN_IF_FAILED(hr);

				return S_OK;
			}
		).Get(),
		&_ContentsWebView_WebResourceRequested_Token
	);
	RETURN_IF_FAILED(hr);


	return S_OK;
}

HRESULT WebView::ContentsWebView_setupWebMessageReceived(void)
{
	//-----------------------------------------------------------------------
	HRESULT hr;


	//-----------------------------------------------------------------------
	hr = _ContentsWebView->add_WebMessageReceived(
		Microsoft::WRL::Callback<ICoreWebView2WebMessageReceivedEventHandler>(
			[this](ICoreWebView2* sender, ICoreWebView2WebMessageReceivedEventArgs* args)
			{
				//-----------------------------------------------------------------------
				HRESULT hr;


				//-----------------------------------------------------------------------
				wil::unique_cotaskmem_string ucsUri;


				hr = args->get_Source(&ucsUri);
				RETURN_IF_FAILED(hr);


				//-----------------------------------------------------------------------
				std::wstring uri(ucsUri.get());
				std::wstring urn = parseContentsURN(uri);


				if (urn.empty())
				{
					return S_OK;
				}


#if 1
				//-----------------------------------------------------------------------
				wil::unique_cotaskmem_string ucsWebMessage;


				hr = args->TryGetWebMessageAsString(&ucsWebMessage);
				RETURN_IF_FAILED(hr);
#else


				//-----------------------------------------------------------------------
				wil::unique_cotaskmem_string ucsWebMessage;


				hr = args->get_WebMessageAsJson(&ucsWebMessage);
				RETURN_IF_FAILED(hr);
#endif


				//-----------------------------------------------------------------------
				std::wstring webMessage(ucsWebMessage.get());


				//-----------------------------------------------------------------------
				ContentsWebView_onWebMessage(urn, webMessage);


				return S_OK;
			}
		).Get(), 
		&_ContentsWebView_WebMessageReceived_Token
	);
	RETURN_IF_FAILED(hr);


	return S_OK;
}

void WebView::ContentsWebView_postWebMessageAsJson(const std::wstring& msg)
{
	HRESULT hr;


	hr = _ContentsWebView->PostWebMessageAsJson(msg.c_str());
	if (FAILED(hr))
	{
		WUI_TRACE(L"failed");
	}
}

void WebView::ContentsWebView_onWebMessage(const std::wstring& urn, const std::wstring& webMessage)
{
#if 0
#if 1
	//------------------------------------------------------------------------
	// TryGetWebMessageAsString
	if (webMessage.compare(L"javascript-message") == 0)
	{
		ContentsWebView_postWebMessageAsJson();
	}
#else


	//------------------------------------------------------------------------
	// get_WebMessageAsJson
	if (webMessage.compare(L"\"javascript-message\"") == 0)
	{
		ContentsWebView_postWebMessageAsJson();
	}
#endif
#endif


	//------------------------------------------------------------------------
	WUI_TRACE(urn);
	WUI_TRACE(webMessage);
	

	//------------------------------------------------------------------------
	JsonMessageService jsonMessageService(this);


	jsonMessageService.onWebMessage(webMessage);
}

//===========================================================================
HRESULT WebView::ContentsWebView_registerEventHandler(void)
{
	//-----------------------------------------------------------------------
	HRESULT hr;


	//-----------------------------------------------------------------------
	hr = _ContentsWebView->add_HistoryChanged(
		Callback<ICoreWebView2HistoryChangedEventHandler>(
			[this](ICoreWebView2* webview, IUnknown* args) -> HRESULT
			{
				//-----------------------------------------------------------------------
				HRESULT hr;


				//-----------------------------------------------------------------------
				wil::unique_cotaskmem_string ucsSource;
				
				
				hr = webview->get_Source(&ucsSource);
				RETURN_IF_FAILED(hr);


				//-----------------------------------------------------------------------
				std::wstring source(ucsSource.get());


				WUI_TRACE(source);


				//-----------------------------------------------------------------------

				return S_OK;
			}
		).Get(),
		&_ContentsWebView_HistoryChanged_Token
	);
	RETURN_IF_FAILED(hr);


	//-----------------------------------------------------------------------
	hr = _ContentsWebView->add_SourceChanged(
		Callback<ICoreWebView2SourceChangedEventHandler>(
			[this](ICoreWebView2* webview, ICoreWebView2SourceChangedEventArgs* args) -> HRESULT
			{
				//-----------------------------------------------------------------------
				HRESULT hr;


				//-----------------------------------------------------------------------
				wil::unique_cotaskmem_string ucsSource;


				hr = webview->get_Source(&ucsSource);
				RETURN_IF_FAILED(hr);


				//-----------------------------------------------------------------------
				std::wstring source(ucsSource.get());
				WUI_TRACE(source);


				return S_OK;
			}
		).Get(),
		&_ContentsWebView_SourceChanged_Token
	);
	RETURN_IF_FAILED(hr);


	//-----------------------------------------------------------------------
	hr = _ContentsWebView->add_NavigationStarting(
		Callback<ICoreWebView2NavigationStartingEventHandler>(
			[this](ICoreWebView2* webview, ICoreWebView2NavigationStartingEventArgs* args) -> HRESULT
			{
				//-----------------------------------------------------------------------
				HRESULT hr;


				//-----------------------------------------------------------------------
				wil::unique_cotaskmem_string ucsUri;


				hr = args->get_Uri(&ucsUri);
				RETURN_IF_FAILED(hr);


				//-----------------------------------------------------------------------
				std::wstring uri(ucsUri.get());
				WUI_TRACE(uri);


				//-----------------------------------------------------------------------
				BOOL cancel = FALSE;


				hr = args->get_Cancel(&cancel);
				RETURN_IF_FAILED(hr);


				//hr = args->put_Cancel(cancel);
				//RETURN_IF_FAILED(hr);


				return S_OK;
			}
		).Get(),
		&_ContentsWebView_NavigationStarting_Token
	);
	RETURN_IF_FAILED(hr);


	//-----------------------------------------------------------------------
	hr = _ContentsWebView->add_NavigationCompleted(
		Callback<ICoreWebView2NavigationCompletedEventHandler>(
			[this](ICoreWebView2* webview, ICoreWebView2NavigationCompletedEventArgs* args) -> HRESULT
			{
				//-----------------------------------------------------------------------
				HRESULT hr;


				//-----------------------------------------------------------------------
				BOOL navigationSucceeded = FALSE;

				
				hr = args->get_IsSuccess(&navigationSucceeded);
				if (SUCCEEDED(hr))
				{
					WUI_TRACE(L"navigationSucceeded");


					//executeScript(L"alert(\"navigationSucceeded\"); var win = window.open(\"/page1/list0.json\", \"PopupWin\", \"width=500,height=600\");");
				}
				else
				{
					WUI_TRACE(L"navigationFailed");
				}


				return S_OK;
			}
		).Get(),
		&_ContentsWebView_NavigationCompleted_Token
	);
	RETURN_IF_FAILED(hr);


	//-----------------------------------------------------------------------
	hr = _ContentsWebView->CallDevToolsProtocolMethod(L"Security.enable", L"{}", nullptr);
	RETURN_IF_FAILED(hr);

	hr = _ContentsWebView->GetDevToolsProtocolEventReceiver(L"Security.securityStateChanged", &_ContentsWebView_Security_securityStateChanged_EventReceiver);
	RETURN_IF_FAILED(hr);

	hr = _ContentsWebView_Security_securityStateChanged_EventReceiver->add_DevToolsProtocolEventReceived(
		Callback<ICoreWebView2DevToolsProtocolEventReceivedEventHandler>(
			[this](ICoreWebView2* webview, ICoreWebView2DevToolsProtocolEventReceivedEventArgs* args) -> HRESULT
			{
				//-----------------------------------------------------------------------
				HRESULT hr;


				//-----------------------------------------------------------------------
				wil::unique_cotaskmem_string ucsJsonArgs;


				hr = args->get_ParameterObjectAsJson(&ucsJsonArgs);
				RETURN_IF_FAILED(hr);


				//-----------------------------------------------------------------------
				std::wstring jsonArgs(ucsJsonArgs.get());
				WUI_TRACE(jsonArgs);


				return S_OK;
			}
		).Get(),
		&_ContentsWebView_Security_securityStateChanged_Token
	);
	RETURN_IF_FAILED(hr);


	//-----------------------------------------------------------------------
	hr = _ContentsWebView->CallDevToolsProtocolMethod(L"Log.enable", L"{}", nullptr);
	RETURN_IF_FAILED(hr);

	hr = _ContentsWebView->GetDevToolsProtocolEventReceiver(L"Log.entryAdded", &_ContentsWebView_Log_entryAdded_EventReceiver);
	RETURN_IF_FAILED(hr);

	hr = _ContentsWebView_Log_entryAdded_EventReceiver->add_DevToolsProtocolEventReceived(
		Callback<ICoreWebView2DevToolsProtocolEventReceivedEventHandler>(
			[this](ICoreWebView2* webview, ICoreWebView2DevToolsProtocolEventReceivedEventArgs* args) -> HRESULT
			{
				//-----------------------------------------------------------------------
				HRESULT hr;


				//-----------------------------------------------------------------------
				wil::unique_cotaskmem_string ucsJsonArgs;


				hr = args->get_ParameterObjectAsJson(&ucsJsonArgs);
				RETURN_IF_FAILED(hr);


				//-----------------------------------------------------------------------
				std::wstring jsonArgs(ucsJsonArgs.get());
				//WUI_TRACE(jsonArgs);
				wui::debugPrintln(L"Log.entryAdded: ");
				wui::debugPrintln(jsonArgs);


				return S_OK;
			}
		).Get(),
		&_ContentsWebView_Log_entryAdded_Token
	);
	RETURN_IF_FAILED(hr);


	//-----------------------------------------------------------------------
	hr = _ContentsWebView->CallDevToolsProtocolMethod(L"Runtime.enable", L"{}", nullptr);
	RETURN_IF_FAILED(hr);

	hr = _ContentsWebView->GetDevToolsProtocolEventReceiver(L"Runtime.consoleAPICalled", &_ContentsWebView_Runtime_consoleAPICalled_EventReceiver);
	RETURN_IF_FAILED(hr);

	hr = _ContentsWebView_Runtime_consoleAPICalled_EventReceiver->add_DevToolsProtocolEventReceived(
		Callback<ICoreWebView2DevToolsProtocolEventReceivedEventHandler>(
			[this](ICoreWebView2* webview, ICoreWebView2DevToolsProtocolEventReceivedEventArgs* args) -> HRESULT
			{
				//-----------------------------------------------------------------------
				HRESULT hr;


				//-----------------------------------------------------------------------
				wil::unique_cotaskmem_string ucsJsonArgs;


				hr = args->get_ParameterObjectAsJson(&ucsJsonArgs);
				RETURN_IF_FAILED(hr);


				//-----------------------------------------------------------------------
				std::wstring jsonArgs(ucsJsonArgs.get());
				//WUI_TRACE(jsonArgs);
				wui::debugPrintln(L"Runtime.consoleAPICalled: ");
				wui::debugPrintln(jsonArgs);


				return S_OK;
			}
		).Get(),
		&_ContentsWebView_Runtime_consoleAPICalled_Token
	);
	RETURN_IF_FAILED(hr);


	//-----------------------------------------------------------------------
	hr = _ContentsWebView->GetDevToolsProtocolEventReceiver(L"Runtime.exceptionThrown", &_ContentsWebView_Runtime_exceptionThrown_EventReceiver);
	RETURN_IF_FAILED(hr);

	hr = _ContentsWebView_Runtime_exceptionThrown_EventReceiver->add_DevToolsProtocolEventReceived(
		Callback<ICoreWebView2DevToolsProtocolEventReceivedEventHandler>(
			[this](ICoreWebView2* webview, ICoreWebView2DevToolsProtocolEventReceivedEventArgs* args) -> HRESULT
			{
				//-----------------------------------------------------------------------
				HRESULT hr;


				//-----------------------------------------------------------------------
				wil::unique_cotaskmem_string ucsJsonArgs;


				hr = args->get_ParameterObjectAsJson(&ucsJsonArgs);
				RETURN_IF_FAILED(hr);


				//-----------------------------------------------------------------------
				std::wstring jsonArgs(ucsJsonArgs.get());
				//WUI_TRACE(jsonArgs);
				wui::debugPrintln(L"Runtime.exceptionThrown: ");
				wui::debugPrintln(jsonArgs);


				//-----------------------------------------------------------------------
				JsonMessageService jsonMessageService(this);


				jsonMessageService.onRuntimeExceptionThrown(jsonArgs);


				return S_OK;
			}
		).Get(),
		&_ContentsWebView_Runtime_exceptionThrown_Token
	);
	RETURN_IF_FAILED(hr);


	return S_OK;
}

//===========================================================================
void WebView::navigate(const std::wstring& uri)
{
	HRESULT hr;


	hr = _ContentsWebView->Navigate(uri.c_str());
	if (FAILED(hr))
	{
		WUI_TRACE(L"failed");
	}
}

void WebView::navigateContents(const std::wstring& urn)
{
	std::wstring uri;


	uri = getContentsHost() + urn;
	navigate(uri);
}

void WebView::executeScript(const std::wstring& script)
{
	_ContentsWebView->ExecuteScript(script.c_str(),
		Callback<ICoreWebView2ExecuteScriptCompletedHandler>(
			[this](HRESULT errorCode, LPCWSTR resultObjectAsJson) -> HRESULT
			{
				if (FAILED(errorCode))
				{

				}



				return S_OK;
			}
		).Get()
	);
}

//===========================================================================
#pragma endregion





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




