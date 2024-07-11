/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"
#include "JsonMessageService.hpp"
#include <wrl.h>





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
//using namespace Microsoft::WRL;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace app
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
WebContentsManager::WebContentsManager()
{
}

WebContentsManager::~WebContentsManager()
{
}

//===========================================================================
std::wstring WebContentsManager::getContentsDataFolder(void) const
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

std::wstring WebContentsManager::getContentsHost(void) const
{
	std::wstring host = L"https://www.code1009.com";


	return host;
}

std::wstring WebContentsManager::getContentsURI(const std::wstring& urn) const
{
	std::wstring uri;


	uri = getContentsHost() + urn;

	return uri;
}

std::wstring WebContentsManager::parseContentsURN(const std::wstring& uri) const
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

//===========================================================================
void WebContentsManager::registerContentsMap(void)
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
//	JsonMessageService jsonMessageService(this);
//	std::wstring json;


//	json = jsonMessageService.getMessage_page1_list0_json();

//	_ContentsMap.registerWebContents(L"/page1/list0.json", std::make_shared<WebContentsUTF8StringStream>(json));


	//------------------------------------------------------------------------
	//_StartURI = getContentsURI(L"/page1/list0.json");
	_StartURI = getContentsURI(L"/index.html");
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




