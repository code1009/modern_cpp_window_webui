#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace app
{




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WebUIManager;
class WebUIWindow;




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WebUIMessageService
{
private:
	WebUIManager* _Manager{ nullptr };

public:
	explicit WebUIMessageService(WebUIManager* manager);
	virtual ~WebUIMessageService();

public:
	void onRuntimeExceptionThrown(WebUIWindow* window, const std::wstring& message);

public:
	void onWebMessage(WebUIWindow* window, const std::wstring& message);

private:
	bool onWebMessageTargetType(WebUIWindow* window, const std::wstring& message);
	bool onWebMessageTargetType0(WebUIWindow* window, web::json::value& jsonMessage, web::json::value& jsonTarget, web::json::value& jsonType);
	bool onWebMessageTargetType1(WebUIWindow* window, web::json::value& jsonMessage, web::json::value& jsonTarget, web::json::value& jsonType);

public:
	void postMessage_gridUpdate(WebUIWindow* window);
	void postMessage_gridRecord(WebUIWindow* window, int no);

public:
	std::wstring getMessage_page1_list0_json(void);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




