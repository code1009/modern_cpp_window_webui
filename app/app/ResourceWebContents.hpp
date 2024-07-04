#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace app
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class ResourceWebContents
{
public:
	std::wstring _WebContentsType{};
	std::wstring _ResourceName{};
	HRSRC        _hResource{ nullptr };
	HGLOBAL      _hResourceGlobal{ nullptr };
	LPVOID       _pResource{ nullptr };
	DWORD        _dwResourceSize{ 0 };
	IStream*     _pStream{ nullptr };

public:
	bool load(void);
	void unload(void);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class ResourceWebContentsMap
{
public:
	std::map<std::wstring, ResourceWebContents*> _Container{};

public:
	ResourceWebContentsMap();
	~ResourceWebContentsMap();

public:
	void registerResourceWebContents(std::wstring urn, std::wstring webContentsType, std::wstring resourceName);

public:
	ResourceWebContents* find(std::wstring keyName);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




