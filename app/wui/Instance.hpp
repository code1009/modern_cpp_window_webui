#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class Instance final
{
private:
	HINSTANCE _Handle{ nullptr };

public:
	Instance();

public:
	Instance(const Instance&) = delete;
	Instance& operator=(const Instance&) = delete;

	Instance(Instance&&) = delete;
	Instance& operator=(Instance&&) = delete;

public:
	HINSTANCE getHandle(void) const;
	HINSTANCE setHandle(HINSTANCE handle);

public:
	std::wstring loadString(int id);

	HCURSOR loadCursor(int id);
	HICON loadIcon(int id);
	HBITMAP loadBitmap(int id);

	HCURSOR loadCursor(LPCWSTR id);	
	HICON loadIcon(LPCWSTR id);
	HBITMAP loadBitmap(LPCWSTR id);

	LPCWSTR makeIntResource(int id);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
Instance* getInstance(void);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




