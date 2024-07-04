#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace app
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WebView : public wui::BasicWindow
{
public:
	ResourceWebContentsMap _ResourceWebContentsMap{};

public:
	wil::com_ptr<ICoreWebView2Environment> _ContentsWebViewEnvironment;
	wil::com_ptr<ICoreWebView2Controller>  _ContentsWebViewController;
	wil::com_ptr<ICoreWebView2>            _ContentsWebView;

	EventRegistrationToken _ContentsWebView_WebResourceRequested_Token{};
	EventRegistrationToken _ContentsWebView_WebMessageReceived_Token{};

public:
	EventRegistrationToken _ContentsWebView_HistoryChanged_Token = {};
	EventRegistrationToken _ContentsWebView_SourceChanged_Token = {};
	EventRegistrationToken _ContentsWebView_NavigationStarting_Token = {};
	EventRegistrationToken _ContentsWebView_NavigationCompleted_Token = {};

	wil::com_ptr<ICoreWebView2DevToolsProtocolEventReceiver> _ContentsWebView_Security_securityStateChanged_EventReceiver;
	EventRegistrationToken                                   _ContentsWebView_Security_securityStateChanged_Token = {};

	wil::com_ptr<ICoreWebView2DevToolsProtocolEventReceiver> _ContentsWebView_Log_entryAdded_EventReceiver;
	EventRegistrationToken                                   _ContentsWebView_Log_entryAdded_Token = {};

	wil::com_ptr<ICoreWebView2DevToolsProtocolEventReceiver> _ContentsWebView_Runtime_consoleAPICalled_EventReceiver;
	EventRegistrationToken                                   _ContentsWebView_Runtime_consoleAPICalled_Token = {};

	wil::com_ptr<ICoreWebView2DevToolsProtocolEventReceiver> _ContentsWebView_Runtime_exceptionThrown_EventReceiver;
	EventRegistrationToken                                   _ContentsWebView_Runtime_exceptionThrown_Token = {};

public:
	explicit WebView(HWND hParent);
	virtual ~WebView();

public:
	virtual void registerWindowMessageHandler(void) override;

public:
	void onCreate(wui::WindowMessage& windowMessage);
	void onDestory(wui::WindowMessage& windowMessage);
	void onClose(wui::WindowMessage& windowMessage);

	void onSize(wui::WindowMessage& windowMessage);
	void onDPIChanged(wui::WindowMessage& windowMessage);
	
	void onCommand(wui::WindowMessage& windowMessage);
	void onTest1(wui::WindowMessage& windowMessage);
	void onTest2(wui::WindowMessage& windowMessage);
	
public:
	int getDPIAwareBound(int bound);

public:
	std::wstring getContentsDataFolder(void);
	std::wstring getContentsHost(void);
	std::wstring getContentsURN(std::wstring uri);

public:
	void createWebView(void);
	void destroyWebView(void);
	void registerResourceWebContentsMap(void);

public:
	HRESULT createContentsWebViewController(void);
	HRESULT resizeContentsWebViewController(void);
	HRESULT  setupContentsWebViewController(void);
	HRESULT  setupContentsWebView(void);
	HRESULT  setupContentsWebViewSettings(void);

public:
	HRESULT ContentsWebView_setupWebResourceRequestedFilter(void);
	HRESULT ContentsWebView_setupWebMessageReceived(void);
	HRESULT ContentsWebView_onWebMessage(std::wstring urn, std::wstring webMessage);
	void    ContentsWebView_postWebMessageAsJson(void);

public:
	HRESULT ContentsWebView_registerEventHandler(void);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




