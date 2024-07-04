/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace app
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
bool ResourceWebContents::load(void)
{
//	LPCWSTR pType = RT_HTML;
	LPCWSTR pType = L"WEB";



	HRSRC hResource = ::FindResourceW(wui::getWindowInstance()->getHandle(), _ResourceName.c_str(), pType);
	if (!hResource)
	{
		return false;
	}

	DWORD resourceSize = ::SizeofResource(wui::getWindowInstance()->getHandle(), hResource);
	if (!resourceSize)
	{
		return false;
	}

	const void* pResourceData = ::LockResource(::LoadResource(wui::getWindowInstance()->getHandle(), hResource));
	if (!pResourceData)
	{
		return false;
	}

	_hResourceGlobal = ::GlobalAlloc(GMEM_MOVEABLE, resourceSize);
	if (_hResourceGlobal)
	{
		_pResource = ::GlobalLock(_hResourceGlobal);
		if (_pResource)
		{
			CopyMemory(_pResource, pResourceData, resourceSize);


			if (::CreateStreamOnHGlobal(_hResourceGlobal, FALSE, &_pStream) == S_OK)
			{
				_dwResourceSize = resourceSize;

				return true;
			}


			::GlobalUnlock(_hResourceGlobal);
		}
		::GlobalFree(_hResourceGlobal);
	}


	_hResource = nullptr;
	_hResourceGlobal = nullptr;
	_pResource = nullptr;
	_dwResourceSize = 0;

	_pStream = nullptr;

	return false;
}

void ResourceWebContents::unload(void)
{
	if (_pStream)
	{
		_pStream->Release();
		_pStream = nullptr;
	}

	if (_hResource)
	{
		::GlobalUnlock(_hResource);
		::GlobalFree(_hResource);

		_hResource = nullptr;
		_hResourceGlobal = nullptr;
		_pResource = nullptr;
		_dwResourceSize = 0;
	}
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
ResourceWebContentsMap::ResourceWebContentsMap()
{

}

ResourceWebContentsMap::~ResourceWebContentsMap()
{
	std::for_each(_Container.begin(), _Container.end(),
		[](std::pair<std::wstring, ResourceWebContents*> pair)
		{
			pair.second->unload();

			delete pair.second;
		}
	);

	_Container.clear();
}

void ResourceWebContentsMap::registerResourceWebContents(std::wstring urn, std::wstring webContentsType, std::wstring resourceName)
{
	ResourceWebContents* o;


	o = new ResourceWebContents();

	o->_WebContentsType = webContentsType;
	o->_ResourceName = resourceName;

	o->load();

	_Container[urn] = o;
}

ResourceWebContents* ResourceWebContentsMap::find(std::wstring name)
{
	auto it = _Container.find(name);


	if (_Container.end()==it)
	{
		return nullptr;
	}


	ResourceWebContents* o;


	o = (*it).second;

	return o;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




