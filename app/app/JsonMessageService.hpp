#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace app
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class JsonMessageService
{
public:
	WebView* _WebView{ nullptr };

public:
	explicit JsonMessageService(WebView* webView);
	virtual ~JsonMessageService();

public:
	void onRuntimeExceptionThrown(const std::wstring& message);

public:
	void onWebMessage(const std::wstring& message);
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




