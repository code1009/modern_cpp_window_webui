﻿/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"
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
WebUIManager::WebUIManager(HWND hMainWindow):
	_hMainWindow{ hMainWindow }
{
	_MessageService = std::make_shared<WebUIMessageService>(this);

	registerContentsMap();
}

WebUIManager::~WebUIManager()
{
	//-------------------------------------------------------------------------
	std::wostringstream oss;


	oss << L"_WindowMap.size() = ";
	oss << _WindowMap.size();

	WUI_TRACE(oss.str().c_str());


	//-------------------------------------------------------------------------
	_WindowMap.clear();
}

//===========================================================================
std::wstring WebUIManager::getContentsDataFolder(void) const
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

std::wstring WebUIManager::getContentsHost(void) const
{
	std::wstring host = L"https://code1009.github.io";


	return host;
}

std::wstring WebUIManager::getContentsURI(const std::wstring& urn) const
{
	std::wstring uri;


	uri = getContentsHost() + urn;

	return uri;
}

std::wstring WebUIManager::parseContentsURN(const std::wstring& uri) const
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
void WebUIManager::registerContentsMap(void)
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
		_ContentsMap.registerContents(res, std::make_shared<WebUIContentsResourceStream>(res));
	}

	//_ContentsMap.registerWebContents(L"/favicon.ico", std::make_shared<WebContentsResourceStream>(L"favicon.ico"));


	//------------------------------------------------------------------------
	std::wstring json;


	json = _MessageService->getMessage_page1_list0_json();

	_ContentsMap.registerContents(L"/page1/list0.json", std::make_shared<WebUIContentsUTF8StringStream>(json));
}

WebUIContentsMap* WebUIManager::getContentsMap(void)
{
	return &_ContentsMap;
}

//===========================================================================
WebUIMessageService* WebUIManager::getMessageService(void)
{
	return _MessageService.get();
}

//===========================================================================
std::shared_ptr<WebUIWindow> WebUIManager::newPopupWindow(HWND hParentWindow, std::wstring uri)
{
	auto e = std::make_shared<WebUIWindow>(this, uri, hParentWindow, true);

	
	_WindowMap[e->getHandle()] = e;


	return e;
}

std::shared_ptr<WebUIWindow> WebUIManager::newPopupWindow(HWND hParentWindow, std::wstring uri, const RECT& rect)
{
	auto e = std::make_shared<WebUIWindow>(this, uri, hParentWindow, true);

	
	wui::moveWindow(e->getHandle(), rect);


	_WindowMap[e->getHandle()] = e;


	return e;
}

std::shared_ptr<WebUIWindow> WebUIManager::newChildWindow(HWND hParentWindow, std::wstring uri)
{
	auto e = std::make_shared<WebUIWindow>(this, uri, hParentWindow, false);


	_WindowMap[e->getHandle()] = e;


	return e;
}

void WebUIManager::deleteWindow(HWND hWindow)
{
	auto it = _WindowMap.find(hWindow);


	if(it!=_WindowMap.end())
	{
		_WindowMap.erase(it);
	}
	else
	{
		WUI_TRACE(L"window handle not found");
	}
}

void WebUIManager::onDestroyWindow(HWND hWindow)
{
	::PostMessage(_hMainWindow, WM_USER + 0, (WPARAM)hWindow, 0);
}

void WebUIManager::deleteAndDestroyAllWindow(void)
{
	for (auto e : _WindowMap)
	{
		e.second->destroyWindow();
	}

	_WindowMap.clear();
}

void WebUIManager::moveWindow(HWND hParentWindow, const RECT& rect)
{
	HWND hParent;


	for(auto e : _WindowMap)
	{
		hParent = GetParent(e.first);

		if (hParent == hParentWindow)
		{
			wui::moveWindow(e.first, rect);
		}
	}
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




