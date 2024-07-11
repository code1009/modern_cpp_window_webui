/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace app
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
WebUIMessageService::WebUIMessageService():
	_WebView{ nullptr }
{
}

WebUIMessageService::WebUIMessageService(WebView* webView):
	_WebView{ webView }
{
}

WebUIMessageService::~WebUIMessageService()
{
}

//===========================================================================
void WebUIMessageService::onRuntimeExceptionThrown(const std::wstring& message)
{
	//------------------------------------------------------------------------
	if (message == L"undefined")
	{
		return;
	}


	//------------------------------------------------------------------------
	web::json::value jsonMessage = web::json::value::parse(message);


	//------------------------------------------------------------------------
	if (!jsonMessage.has_field(L"exceptionDetails"))
	{
		return;
	}


	web::json::value jsonExceptionDetails;


	jsonExceptionDetails = jsonMessage.at(L"exceptionDetails");
	if (web::json::value::Object != jsonExceptionDetails.type())
	{
		return;
	}


	//------------------------------------------------------------------------
	if (!jsonExceptionDetails.has_field(L"columnNumber"))
	{
		return;
	}
	if (!jsonExceptionDetails.has_field(L"lineNumber"))
	{
		return;
	}
	if (!jsonExceptionDetails.has_field(L"text"))
	{
		return;
	}
	if (!jsonExceptionDetails.has_field(L"url"))
	{
		return;
	}


	//------------------------------------------------------------------------
	web::json::value jsonUrl;
	web::json::value jsonLineNumber;
	web::json::value jsonColumnNumber;
	web::json::value jsonText;


	jsonUrl = jsonExceptionDetails.at(L"url");
	jsonLineNumber = jsonExceptionDetails.at(L"lineNumber");
	jsonColumnNumber = jsonExceptionDetails.at(L"columnNumber");
	jsonText = jsonExceptionDetails.at(L"text");


	if (web::json::value::String != jsonUrl.type())
	{
		return;
	}
	if (web::json::value::Number != jsonLineNumber.type())
	{
		return;
	}
	if (web::json::value::Number != jsonColumnNumber.type())
	{
		return;
	}
	if (web::json::value::String != jsonText.type())
	{
		return;
	}


	//------------------------------------------------------------------------
	std::wstring url;
	int lineNumber;
	int columnNumber;
	std::wstring text;


	url = jsonUrl.as_string();
	lineNumber = jsonLineNumber.as_integer();
	columnNumber = jsonColumnNumber.as_integer();
	text = jsonText.as_string();


	//------------------------------------------------------------------------
	if (!jsonExceptionDetails.has_field(L"exception"))
	{
		return;
	}


	web::json::value jsonException;


	jsonException = jsonExceptionDetails.at(L"exception");


	if (web::json::value::Object != jsonException.type())
	{
		return;
	}
	

	//------------------------------------------------------------------------
	if (!jsonException.has_field(L"className"))
	{
		return;
	}

	if (!jsonException.has_field(L"description"))
	{
		return;
	}


	web::json::value jsonClassName;
	web::json::value jsonDescription;


	jsonClassName = jsonException.at(L"className");
	jsonDescription = jsonException.at(L"description");

	if (web::json::value::String != jsonClassName.type())
	{
		return;
	}

	if (web::json::value::String != jsonDescription.type())
	{
		return;
	}


	std::wstring className;
	std::wstring description;


	className = jsonClassName.as_string();
	description = jsonDescription.as_string();


	//------------------------------------------------------------------------
	std::wostringstream oss;


	oss << L"exception" << std::endl;
	oss << L"url: " << url << std::endl;
	oss << L"lineNumber: " << lineNumber << std::endl;
	oss << L"columnNumber: " << columnNumber << std::endl;
	oss << L"text: " << text << std::endl;
	oss << L"className: " << className << std::endl;
	oss << L"description: " << description << std::endl;
	oss << std::endl;

	
	OutputDebugStringW(oss.str().c_str());
	//::MessageBoxW(_WebView->getHandle(), oss.str().c_str(), L"RuntimeExceptionThrown", MB_OK);


	//------------------------------------------------------------------------
	oss.str(L"");
	oss.clear();
}


//===========================================================================
void WebUIMessageService::onWebMessage(const std::wstring& message)
{
	//------------------------------------------------------------------------
	if (message == L"undefined")
	{
		return;
	}


	//------------------------------------------------------------------------
	onWebMessageTargetType(message);
}

bool WebUIMessageService::onWebMessageTargetType(const std::wstring& message)
{
	//------------------------------------------------------------------------
	web::json::value jsonMessage = web::json::value::parse(message);


	if (!jsonMessage.has_field(L"target"))
	{
		return false;
	}

	if (!jsonMessage.has_field(L"type"))
	{
		return false;
	}


	//------------------------------------------------------------------------
	bool rv;


	//------------------------------------------------------------------------
	web::json::value jsonTarget;
	web::json::value jsonType;


	jsonTarget = jsonMessage.at(L"target");
	jsonType = jsonMessage.at(L"type");


	//------------------------------------------------------------------------
	try
	{
		rv = onWebMessageTargetType0(jsonMessage, jsonTarget, jsonType);
		if (true == rv)
		{
			return true;
		}
	}
	catch (...)
	{

	}


	//------------------------------------------------------------------------
	try
	{
		rv = onWebMessageTargetType1(jsonMessage, jsonTarget, jsonType);
		if (true == rv)
		{
			return true;
		}
	}
	catch (...)
	{

	}


	return false;
}

bool WebUIMessageService::onWebMessageTargetType0(web::json::value& jsonMessage, web::json::value& jsonTarget, web::json::value& jsonType)
{
	//------------------------------------------------------------------------
	switch (jsonTarget.type())
	{
	case web::json::value::Number:
	case web::json::value::Boolean:
	case web::json::value::String:
		break;

	default:
		return false;
		break;
	}


	switch (jsonType.type())
	{
	case web::json::value::Number:
	case web::json::value::Boolean:
	case web::json::value::String:
		break;

	default:
		return false;
		break;
	}


	//------------------------------------------------------------------------
	std::wstring target;
	std::wstring type;


	target = jsonTarget.as_string();
	type = jsonType.as_string();


	//------------------------------------------------------------------------
	if ((target == L"gridUpdate") && (type == L"click"))
	{
		postMessage_gridUpdate();
	}
	else
	{
		std::wstring message = target + L" : " + type;


		//::MessageBoxW(_WebView->getHandle(), message.c_str(), L"C++에서 이벤트 받음", MB_OK);
	}

	return true;
}

bool WebUIMessageService::onWebMessageTargetType1(web::json::value& jsonMessage, web::json::value& jsonTarget, web::json::value& jsonType)
{
	//------------------------------------------------------------------------
	web::json::value jsonTargetId;


	switch (jsonTarget.type())
	{
	case web::json::value::Object:
		if (!jsonTarget.has_field(L"id"))
		{
			return false;
		}

		jsonTargetId = jsonTarget.at(L"id");
		if (web::json::value::String != jsonTargetId.type())
		{
			return false;
		}
		break;

	default:
		return false;
		break;
	}


	switch (jsonType.type())
	{
	case web::json::value::Number:
	case web::json::value::Boolean:
	case web::json::value::String:
		break;

	default:
		return false;
		break;
	}


	//------------------------------------------------------------------------
	std::wstring targetId;
	std::wstring type;


	targetId = jsonTargetId.as_string();
	type = jsonType.as_string();


	//------------------------------------------------------------------------
	std::wstring message = targetId + L" : " + type;


	//::MessageBoxW(_WebView->getHandle(), message.c_str(), L"C++에서 이벤트 받음", MB_OK);


	return true;
}

//===========================================================================
void WebUIMessageService::postMessage_gridUpdate(void)
{
	static int id = 100;

	int i;


	for (i = 0; i < 25; i++)
	{
		id++;


		postMessage_gridRecord(id);
	}
}

void WebUIMessageService::postMessage_gridRecord(int no)
{
	web::json::value jsonMessage = web::json::value::parse(L"{}");


	jsonMessage[L"id"] = web::json::value::number(100);
	jsonMessage[L"name"] = web::json::value::string(L"C++에서 보냄");
	jsonMessage[L"no"] = web::json::value::number(no);



	utility::stringstream_t stream;


	jsonMessage.serialize(stream);

	
	//_WebView->ContentsWebView_postWebMessageAsJson(stream.str().c_str());
}

//===========================================================================
std::wstring WebUIMessageService::getMessage_page1_list0_json(void)
{
	web::json::value jsonMessage = web::json::value::parse(L"{}");


	jsonMessage[L"fname"] = web::json::value::string(L"code1009");
	jsonMessage[L"lname"] = web::json::value::string(L"한글");
	jsonMessage[L"sdate"] = web::json::value::string(L"1446-10-09");
	jsonMessage[L"random"] = web::json::value::string(L"세종대왕");


	utility::stringstream_t stream;


	jsonMessage.serialize(stream);


	return stream.str();
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




