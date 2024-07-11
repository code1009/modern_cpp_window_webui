#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace app
{




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WebView;




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WebUIMessageService
{
public:
	WebView* _WebView{ nullptr };

public:
	WebUIMessageService();
	explicit WebUIMessageService(WebView* webView);
	virtual ~WebUIMessageService();

public:
	void onRuntimeExceptionThrown(const std::wstring& message);

public:
	void onWebMessage(const std::wstring& message);

private:
	bool onWebMessageTargetType(const std::wstring& message);
	bool onWebMessageTargetType0(web::json::value& jsonMessage, web::json::value& jsonTarget, web::json::value& jsonType);
	bool onWebMessageTargetType1(web::json::value& jsonMessage, web::json::value& jsonTarget, web::json::value& jsonType);

public:
	void postMessage_gridUpdate(void);
	void postMessage_gridRecord(int no);

public:
	std::wstring getMessage_page1_list0_json(void);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




