#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
constexpr DWORD ControlWindowStyle = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
constexpr DWORD ControlWindowStyleEx = 0;

constexpr DWORD FrameWindowStyle = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
constexpr DWORD FrameWindowStyleEx = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

constexpr DWORD MDIChildWindowStyle = WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
constexpr DWORD MDIChildWindowStyleEx = WS_EX_MDICHILD;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
using WindowMessageHandler = std::function<void(WindowMessage& windowMessage)>;
using WindowMessageHandlerMap = std::map<std::uint32_t, WindowMessageHandler>;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class Window
{
private:
	HWND _Handle{ nullptr };
	WindowMessageHandlerMap _WindowMessageHandlerMap{ };

public:
	Window();
	virtual ~Window();

public:
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	Window(Window&&) = delete;
	Window& operator=(Window&&) = delete;

public:
	virtual HWND getHandle(void) const;
	virtual HWND setHandle(HWND handle);

public:
	virtual WindowMessageHandler& getWindowMessageHandler(std::uint32_t umsg);
	virtual void registerWindowMessageHandler(void) = 0;

public:
	virtual void callDefWindowProc(WindowMessage& windowMessage);
	virtual void defaultWindowMessageHandler(WindowMessage& windowMessage);
	virtual void onWindowMessage(WindowMessage& windowMessage);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class SubclassWindow : public Window
{
private:
	WNDPROC _ChainWindowProc{ nullptr };

public:
	SubclassWindow();
	virtual ~SubclassWindow();

public:
	SubclassWindow(const SubclassWindow&) = delete;
	SubclassWindow& operator=(const SubclassWindow&) = delete;

	SubclassWindow(SubclassWindow&&) = delete;
	SubclassWindow& operator=(SubclassWindow&&) = delete;

public:
	virtual WNDPROC subclassWindow(HWND hwnd);
	virtual WNDPROC unsubclassWindow(WNDPROC windowProc = nullptr);

public:
	virtual void defaultWindowMessageHandler(WindowMessage& windowMessage) override;

public:
	virtual WNDPROC getChainWindowProc(void);

public:
	virtual void callWindowProc(WindowMessage& windowMessage, WNDPROC windowProc = nullptr);
};




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class BasicWindow : public Window
{
private:
	WNDCLASSEXW _WindowClass{ };

public:
	BasicWindow();
	virtual ~BasicWindow();

public:
	BasicWindow(const BasicWindow&) = delete;
	BasicWindow& operator=(const BasicWindow&) = delete;

	BasicWindow(BasicWindow&&) = delete;
	BasicWindow& operator=(BasicWindow&&) = delete;

public:
	virtual WNDCLASSEXW& getWindowClass(void);
	virtual void initializeWindowClass(void);
	virtual void registerWindowClass(void);
	virtual HWND createWindow(
		HWND hWndParent = nullptr,
		LPCWSTR lpWindowName = L"Window",
		DWORD dwStyle = FrameWindowStyle,
		DWORD dwExStyle = FrameWindowStyleEx,
		int X = CW_USEDEFAULT,
		int Y = CW_USEDEFAULT,
		int nWidth = CW_USEDEFAULT,
		int nHeight = CW_USEDEFAULT,
		HMENU hMenu = nullptr
	);
	virtual HWND createWindow(
		HWND hWndParent,
		const RECT& rect,
		LPCWSTR lpWindowName = L"Window",
		DWORD dwStyle = FrameWindowStyle,
		DWORD dwExStyle = FrameWindowStyleEx,
		HMENU hMenu = nullptr
	);
	virtual void destroyWindow(void);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class BasicModalDialog : public Window
{
private:
	std::int32_t _TemplateNameId{ -1 };

public:
	explicit BasicModalDialog(std::int32_t templateNameId);
	virtual ~BasicModalDialog();

public:
	BasicModalDialog(const BasicModalDialog&) = delete;
	BasicModalDialog& operator=(const BasicModalDialog&) = delete;

	BasicModalDialog(BasicModalDialog&&) = delete;
	BasicModalDialog& operator=(BasicModalDialog&&) = delete;

public:
	virtual std::int32_t getTemplateNameId(void);

public:
	virtual std::int64_t doModal(HWND hwndParent);

public:
	virtual std::int64_t endDialog(std::int64_t result);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class BasicModelessDialog : public Window
{
private:
	std::int32_t _TemplateNameId{ -1 };

public:
	explicit BasicModelessDialog(std::int32_t templateNameId);
	virtual ~BasicModelessDialog();

public:
	BasicModelessDialog(const BasicModelessDialog&) = delete;
	BasicModelessDialog& operator=(const BasicModelessDialog&) = delete;

	BasicModelessDialog(BasicModelessDialog&&) = delete;
	BasicModelessDialog& operator=(BasicModelessDialog&&) = delete;

public:
	virtual std::int32_t getTemplateNameId(void);

public:
	virtual HWND createDialog(HWND hwndParent);
	virtual void destroyWindow(void);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




