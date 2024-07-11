#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace app
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WebUIManager
{
	//-------------------------------------------------------------------------
private:
	HWND                                         _hMainWindow{ nullptr };
	WebUIContentsMap                             _ContentsMap{};
	WebUIMessageService                          _MessageService;
	std::map<HWND, std::shared_ptr<WebUIWindow>> _WindowMap;


	//-------------------------------------------------------------------------
public:
	explicit WebUIManager(HWND hMainWindow);
	virtual ~WebUIManager();


	//-------------------------------------------------------------------------
public:
	WebUIManager(const WebUIManager& other) = delete;
	WebUIManager& operator=(const WebUIManager& other) = delete;

	WebUIManager(WebUIManager&& other) noexcept = delete;
	WebUIManager& operator=(WebUIManager&& other) noexcept = delete;


	//-------------------------------------------------------------------------
public:
	std::wstring getContentsDataFolder(void) const;
	std::wstring getContentsHost(void) const;
	std::wstring getContentsURI(const std::wstring& urn) const;
	std::wstring parseContentsURN(const std::wstring& uri) const;


	//-------------------------------------------------------------------------
public:
	void registerContentsMap(void);
	WebUIContentsMap* getContentsMap(void);

public:
	WebUIMessageService* getMessageService(void);

	//-------------------------------------------------------------------------
public:
	void newPopupWindow(HWND hParentWindow, std::wstring uri);
	void newChildWindow(HWND hParentWindow, std::wstring uri);
	void deleteWindow(HWND hWindow);

	void moveWindow(HWND hParentWindow, const RECT& rect);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




