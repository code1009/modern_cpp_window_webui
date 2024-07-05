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
	WebContentsMap _ContentsMap{};
	std::wstring _StartURI;

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
	int getDPIAwareBound(int bound) const;

public:
	std::wstring getContentsDataFolder(void) const;
	std::wstring getContentsHost(void) const;
	std::wstring getContentsURI(const std::wstring& urn) const;
	std::wstring parseContentsURN(const std::wstring& uri) const;

public:
	void createWebView(void);
	void destroyWebView(void);
	void registerContentsMap(void);

public:
	HRESULT createContentsWebViewController(void);
	HRESULT resizeContentsWebViewController(void);
	HRESULT  setupContentsWebViewController(void);
	HRESULT  setupContentsWebView(void);
	HRESULT  setupContentsWebViewSettings(void);

public:
	HRESULT ContentsWebView_setupWebResourceRequestedFilter(void);

public:
	HRESULT ContentsWebView_setupWebMessageReceived(void);
	void ContentsWebView_onWebMessage(const std::wstring& urn, const std::wstring& webMessage);
	void ContentsWebView_postWebMessageAsJson(const std::wstring& msg);

public:
	HRESULT ContentsWebView_registerEventHandler(void);

public:
	void navigate(const std::wstring& uri);
	void navigateContents(const std::wstring& urn);

public:
	void postCppMessage0ToContentsWebView(void);
	void postCppMessage1ToContentsWebView(void);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




