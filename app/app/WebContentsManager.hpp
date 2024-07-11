#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace app
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WebContentsManager
{
public:
	WebContentsMap _ContentsMap{};
	std::wstring _StartURI;
	JsonMessageService _JsonMessageService;

public:
	WebContentsManager();
	virtual ~WebContentsManager();

public:
	std::wstring getContentsDataFolder(void) const;
	std::wstring getContentsHost(void) const;
	std::wstring getContentsURI(const std::wstring& urn) const;
	std::wstring parseContentsURN(const std::wstring& uri) const;

public:
	void registerContentsMap(void);

};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




