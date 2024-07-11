#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace app
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WebUIManager;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WebUIWindow : public wui::BasicWindow
{
	//-------------------------------------------------------------------------
public:
	WebUIManager* _Manager{ nullptr };
	std::wstring  _URI{ };
	bool          _PopupWindowStyle{ false };


	//-------------------------------------------------------------------------
public:
	wil::com_ptr<ICoreWebView2Environment> _WebView_Environment;
	wil::com_ptr<ICoreWebView2Controller>  _WebView_Controller;
	wil::com_ptr<ICoreWebView2>            _WebView;


	//-------------------------------------------------------------------------
	EventRegistrationToken _WebView_WebResourceRequested_Token{};
	EventRegistrationToken _WebView_WebMessageReceived_Token{};
	EventRegistrationToken _WebView_HistoryChanged_Token{};
	EventRegistrationToken _WebView_SourceChanged_Token{};
	EventRegistrationToken _WebView_NavigationStarting_Token{};
	EventRegistrationToken _WebView_NavigationCompleted_Token{};
	EventRegistrationToken _WebView_NewWindowRequested_Token{};


	//-------------------------------------------------------------------------
	wil::com_ptr<ICoreWebView2DevToolsProtocolEventReceiver> _WebView_DevToolsProtocol_Security_securityStateChanged_EventReceiver;
	EventRegistrationToken                                   _WebView_DevToolsProtocol_Security_securityStateChanged_Token{};
	wil::com_ptr<ICoreWebView2DevToolsProtocolEventReceiver> _WebView_DevToolsProtocol_Log_entryAdded_EventReceiver;
	EventRegistrationToken                                   _WebView_DevToolsProtocol_Log_entryAdded_Token{};
	wil::com_ptr<ICoreWebView2DevToolsProtocolEventReceiver> _WebView_DevToolsProtocol_Runtime_consoleAPICalled_EventReceiver;
	EventRegistrationToken                                   _WebView_DevToolsProtocol_Runtime_consoleAPICalled_Token{};
	wil::com_ptr<ICoreWebView2DevToolsProtocolEventReceiver> _WebView_DevToolsProtocol_Runtime_exceptionThrown_EventReceiver;
	EventRegistrationToken                                   _WebView_DevToolsProtocol_Runtime_exceptionThrown_Token{};


	//-------------------------------------------------------------------------
public:
	explicit WebUIWindow(WebUIManager* manager, std::wstring uri, HWND hParentWindow, bool popupWindowStyle);
	virtual ~WebUIWindow();


	//-------------------------------------------------------------------------
public:
	virtual void registerWindowMessageHandler(void) override;


	//-------------------------------------------------------------------------
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


	//-------------------------------------------------------------------------
public:
	void     createWebView                      (void);
	HRESULT      onWebView_Environment_Completed(HRESULT errorCode, ICoreWebView2Environment* createdEnvironment);
	void    destroyWebView                      (void);


	//-------------------------------------------------------------------------
public:
	HRESULT createWebView_Controller         (void);
	HRESULT     onWebView_ControllerCompleted(HRESULT errorCode, ICoreWebView2Controller* createdController);

	HRESULT resizeWebView_Controller(void);
	HRESULT  setupWebView_Controller(void);

public:
	HRESULT setupWebView_Settings(void);

public:
	HRESULT setupWebView(void);
	
	HRESULT setupWebView_WebResourceRequested(void);
	HRESULT    onWebView_WebResourceRequested(ICoreWebView2* sender, ICoreWebView2WebResourceRequestedEventArgs* args);
	HRESULT setupWebView_WebMessageReceived  (void);
	HRESULT    onWebView_WebMessageReceived  (ICoreWebView2* sender, ICoreWebView2WebMessageReceivedEventArgs* args);
	HRESULT setupWebView_HistoryChanged      (void);
	HRESULT    onWebView_HistoryChanged      (ICoreWebView2* sender, IUnknown* args);
	HRESULT setupWebView_SourceChanged       (void);
	HRESULT    onWebView_SourceChanged       (ICoreWebView2* sender, ICoreWebView2SourceChangedEventArgs* args);
	HRESULT setupWebView_NavigationStarting  (void);
	HRESULT    onWebView_NavigationStarting  (ICoreWebView2* sender, ICoreWebView2NavigationStartingEventArgs* args);
	HRESULT setupWebView_NavigationCompleted (void);
	HRESULT    onWebView_NavigationCompleted (ICoreWebView2* sender, ICoreWebView2NavigationCompletedEventArgs* args);
	HRESULT setupWebView_NewWindowRequested  (void);
	HRESULT    onWebView_NewWindowRequested  (ICoreWebView2* sender, ICoreWebView2NewWindowRequestedEventArgs* args);

	HRESULT setupWebView_DevToolsProtocol_Security_securityStateChanged(void);
	HRESULT    onWebView_DevToolsProtocol_Security_securityStateChanged(ICoreWebView2* sender, ICoreWebView2DevToolsProtocolEventReceivedEventArgs* args);
	HRESULT setupWebView_DevToolsProtocol_Log_entryAdded               (void);
	HRESULT    onWebView_DevToolsProtocol_Log_entryAdded               (ICoreWebView2* sender, ICoreWebView2DevToolsProtocolEventReceivedEventArgs* args);
	HRESULT setupWebView_DevToolsProtocol_Runtime_consoleAPICalled     (void);
	HRESULT    onWebView_DevToolsProtocol_Runtime_consoleAPICalled     (ICoreWebView2* sender, ICoreWebView2DevToolsProtocolEventReceivedEventArgs* args);
	HRESULT setupWebView_DevToolsProtocol_Runtime_exceptionThrown      (void);
	HRESULT    onWebView_DevToolsProtocol_Runtime_exceptionThrown      (ICoreWebView2* sender, ICoreWebView2DevToolsProtocolEventReceivedEventArgs* args);

public:
	void onWebMessage(const std::wstring& urn, const std::wstring& webMessage);
	void postWebMessageAsJson(const std::wstring& msg);

public:
	void navigate(const std::wstring& uri);
	void navigateContents(const std::wstring& urn);
	void executeScript(const std::wstring& script);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




