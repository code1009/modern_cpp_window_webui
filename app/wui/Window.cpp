/////////////////////////////////////////////////////////////////////////////
//
// File: Window.cpp
//
// Part of the wui library.
//
// Created by code1009.
// Created on Jul-12th, 2024.
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include <string>
#include <map>
#include <functional>
#include <iomanip>
#include <sstream>

//===========================================================================
#include <windows.h>
#include <strsafe.h>

//===========================================================================
#include "DebugTool.hpp"
#include "Instance.hpp"
#include "WindowMessage.hpp"

#include "Window.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
static LRESULT __stdcall WindowProc(HWND hwnd, uint32_t message, WPARAM wParam, LPARAM lParam);
static INT_PTR __stdcall DialogProc(HWND hwnd, uint32_t message, WPARAM wParam, LPARAM lParam);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
Window::Window()
{
}

Window::~Window()
{
	HWND handle;


	handle = getHandle();
	if (nullptr != handle)
	{
		WUI_TRACE(L"window handle is not nullptr!");
	}
}

HWND Window::getHandle(void) const
{
	return _Handle;
}

HWND Window::setHandle(HWND handle)
{
	HWND old;


	old = _Handle;
	_Handle = handle;

	return _Handle;
}

WindowMessageHandler& Window::getWindowMessageHandler(std::uint32_t umsg)
{
	return _WindowMessageHandlerMap[umsg];
}

void Window::callDefWindowProc(WindowMessage& windowMessage)
{
	windowMessage.lResult =
		::DefWindowProcW(
			windowMessage.hWnd,
			windowMessage.uMsg,
			windowMessage.wParam,
			windowMessage.lParam);
}

void Window::defaultWindowMessageHandler(WindowMessage& windowMessage)
{
	callDefWindowProc(windowMessage);
}

void Window::onWindowMessage(WindowMessage& windowMessage)
{
	auto found = _WindowMessageHandlerMap.find(windowMessage.uMsg);


	if (found != _WindowMessageHandlerMap.end())
	{
		auto handler = (*found).second;
		if (handler)
		{
			handler(windowMessage);
			return;
		}
	}


	defaultWindowMessageHandler(windowMessage);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
SubclassWindow::SubclassWindow()
{
}

SubclassWindow::~SubclassWindow()
{
}

WNDPROC SubclassWindow::subclassWindow(HWND hwnd)
{
	//-----------------------------------------------------------------------
#ifdef _DEBUG
	if (reinterpret_cast<void*>(::GetWindowLongPtrW(hwnd, GWLP_USERDATA)))
	{
		errorReport(L"SubclassWindow::subclassWindow(): GWLP_USERDATA");
	}
#endif


	//-----------------------------------------------------------------------
	setHandle(hwnd);


	//-----------------------------------------------------------------------
	LONG_PTR rv;
	WNDPROC oldWindowProc;


	rv = ::SetWindowLongPtrW(getHandle(), GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	rv = ::SetWindowLongPtrW(getHandle(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WindowProc));
	oldWindowProc = reinterpret_cast<WNDPROC>(rv);


	//-----------------------------------------------------------------------
	_ChainWindowProc = oldWindowProc;


	//-----------------------------------------------------------------------

	return oldWindowProc;
}

WNDPROC SubclassWindow::unsubclassWindow(WNDPROC windowProc)
{
	//-----------------------------------------------------------------------
	if (nullptr== windowProc)
	{
		windowProc = _ChainWindowProc;
	}


	//-----------------------------------------------------------------------
	LONG_PTR rv;
	WNDPROC oldWindowProc;


	rv = ::SetWindowLongPtrW(getHandle(), GWLP_USERDATA, reinterpret_cast<LONG_PTR>(nullptr));
	rv = ::SetWindowLongPtrW(getHandle(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(windowProc));
	oldWindowProc = reinterpret_cast<WNDPROC>(rv);


	//-----------------------------------------------------------------------
	setHandle(nullptr);
	_ChainWindowProc = nullptr;


	return oldWindowProc;
}

void SubclassWindow::callWindowProc(WindowMessage& windowMessage, WNDPROC windowProc)
{
	//-----------------------------------------------------------------------
	if (nullptr == windowProc)
	{
		windowProc = _ChainWindowProc;
	}


	//-----------------------------------------------------------------------
	windowMessage.lResult =
		::CallWindowProcW(
			windowProc,
			windowMessage.hWnd,
			windowMessage.uMsg,
			windowMessage.wParam,
			windowMessage.lParam);
}

WNDPROC SubclassWindow::getChainWindowProc(void)
{
	return _ChainWindowProc;
}

void SubclassWindow::defaultWindowMessageHandler(WindowMessage& windowMessage)
{
	if (_ChainWindowProc)
	{
		callWindowProc(windowMessage, _ChainWindowProc);
	}
	else
	{
		callDefWindowProc(windowMessage);
	}
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
BasicWindow::BasicWindow()
{
}

BasicWindow::~BasicWindow()
{
}

WNDCLASSEXW& BasicWindow::getWindowClass(void)
{
	return _WindowClass;
}

void BasicWindow::initializeWindowClass(void)
{
	memset(&_WindowClass, 0, sizeof(_WindowClass));

	_WindowClass.cbSize        = sizeof(_WindowClass);
	_WindowClass.style         = CS_HREDRAW | CS_VREDRAW;
	_WindowClass.cbClsExtra    = 0;
	_WindowClass.cbWndExtra    = 0;
	_WindowClass.hInstance     = getInstance()->getHandle();
	_WindowClass.lpfnWndProc   = WindowProc;
	_WindowClass.lpszClassName = L"wui.BasicWindowClass";
	_WindowClass.lpszMenuName  = nullptr;
	_WindowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	_WindowClass.hCursor       = getInstance()->loadCursor(IDC_ARROW);
	_WindowClass.hIcon         = nullptr;
	_WindowClass.hIconSm       = nullptr;
}

void BasicWindow::registerWindowClass(void)
{
	WNDCLASSEXW wndClass;
	BOOL rv;


	rv = ::GetClassInfoExW(_WindowClass.hInstance, _WindowClass.lpszClassName, &wndClass);
	if (FALSE == rv)
	{
		ATOM atom = ::RegisterClassExW(&_WindowClass);
		if (!atom)
		{
			errorReport(L"BasicWindow::registerWindowClass(): RegisterClassExW()");
		}
	}
}

HWND BasicWindow::createWindow(
	HWND    hWndParent  ,
	LPCWSTR lpWindowName,
	DWORD   dwStyle     ,
	DWORD   dwExStyle   ,
	int     X           ,
	int     Y           ,
	int     nWidth      ,
	int     nHeight     ,
	HMENU   hMenu
)
{
	HWND handle;


	handle = ::CreateWindowExW(
		dwExStyle                 ,
		_WindowClass.lpszClassName,
		lpWindowName              ,
		dwStyle                   ,
		X                         ,
		Y                         ,
		nWidth                    ,
		nHeight                   ,
		hWndParent                ,
		hMenu                     ,
		_WindowClass.hInstance    ,
		this
	);

	return handle;
}

HWND BasicWindow::createWindow(
	HWND        hWndParent  ,
	const RECT& rect        ,
	LPCWSTR     lpWindowName,
	DWORD       dwStyle     ,
	DWORD       dwExStyle   ,
	HMENU       hMenu
)
{
	return createWindow(
		hWndParent            , 
		lpWindowName          , 
		dwStyle               , 
		dwExStyle             , 
		rect.left             ,
		rect.top              ,
		rect.right - rect.left,
		rect.bottom - rect.top, 
		hMenu
		);
}

void BasicWindow::destroyWindow(void)
{
	HWND handle;
	BOOL rv;


	handle = getHandle();
	if (handle)
	{
		rv = ::DestroyWindow(handle);
		if(FALSE == rv)
		{
			WUI_TRACE(L"DestroyWindow() failed");
		}
	}

	setHandle(nullptr);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
BasicModalDialog::BasicModalDialog(std::int32_t templateNameId):
	_TemplateNameId{ templateNameId }
{
}

BasicModalDialog::~BasicModalDialog()
{
}

std::int32_t BasicModalDialog::getTemplateNameId(void)
{
	return _TemplateNameId;
}

std::int64_t BasicModalDialog::doModal(HWND hwndParent)
{
	std::int64_t rv;


	rv = ::DialogBoxParamW(
		getInstance()->getHandle(),
		getInstance()->makeIntResource(getTemplateNameId()),
		hwndParent,
		DialogProc, 
		reinterpret_cast<LPARAM>(this)
	);

	return rv;
}

std::int64_t BasicModalDialog::endDialog(std::int64_t result)
{
	std::int64_t rv;


	rv = ::EndDialog(getHandle(), static_cast<INT_PTR>(result));

	return rv;
}




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
BasicModelessDialog::BasicModelessDialog(std::int32_t templateNameId) :
	_TemplateNameId{ templateNameId }
{
}

BasicModelessDialog::~BasicModelessDialog()
{
}

std::int32_t BasicModelessDialog::getTemplateNameId(void)
{
	return _TemplateNameId;
}

HWND BasicModelessDialog::createDialog(HWND hwndParent)
{
	HWND hwnd;


	hwnd = ::CreateDialogParamW(
		getInstance()->getHandle(), 
		getInstance()->makeIntResource(getTemplateNameId()),
		hwndParent,
		DialogProc, 
		reinterpret_cast<LPARAM>(this)
	);


	return hwnd;
}

void BasicModelessDialog::destroyWindow(void)
{
	HWND handle;


	handle = getHandle();
	if (handle)
	{
		::DestroyWindow(handle);
	}

	setHandle(nullptr);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
LRESULT __stdcall WindowProc(HWND hwnd, uint32_t message, WPARAM wParam, LPARAM lParam)
{
	if (WM_NCCREATE == message)
	{
		//-------------------------------------------------------------------
#ifdef _DEBUG
		if (reinterpret_cast<void*>(::GetWindowLongPtrW(hwnd, GWLP_USERDATA)))
		{
			errorReport(L"WindowProc(): GWLP_USERDATA");
		}
#endif


		//-------------------------------------------------------------------
		auto userData = reinterpret_cast<CREATESTRUCTW*>(lParam)->lpCreateParams;
		::SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(userData));

		(reinterpret_cast<Window*>(userData))->setHandle(hwnd);
	}


	auto windowPtr = reinterpret_cast<Window*>(::GetWindowLongPtrW(hwnd, GWLP_USERDATA));
	if (windowPtr)
	{
		WindowMessage windowMessage{ hwnd, message, wParam, lParam };


		windowPtr->onWindowMessage(windowMessage);


		if (WM_NCDESTROY == message)
		{
			::SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(nullptr));
			windowPtr->setHandle(nullptr);
		}


		return windowMessage.lResult;
	}


	return ::DefWindowProcW(hwnd, message, wParam, lParam);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
INT_PTR __stdcall DialogProc(HWND hwnd, uint32_t message, WPARAM wParam, LPARAM lParam)
{
	if (WM_INITDIALOG == message)
	{
		//-------------------------------------------------------------------
#ifdef _DEBUG
		if (reinterpret_cast<void*>(::GetWindowLongPtrW(hwnd, GWLP_USERDATA)))
		{
			errorReport(L"DialogProc(): GWLP_USERDATA");
		}
#endif


		//-------------------------------------------------------------------
		auto userData = reinterpret_cast<BasicModalDialog*>(lParam);
		::SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(userData));

		(reinterpret_cast<BasicModalDialog*>(userData))->setHandle(hwnd);
	}


	auto dialogPtr = reinterpret_cast<BasicModalDialog*>(::GetWindowLongPtrW(hwnd, GWLP_USERDATA));
	if (dialogPtr)
	{
		WindowMessage windowMessage{ hwnd, message, wParam, lParam };


		dialogPtr->onWindowMessage(windowMessage);


		if (WM_NCDESTROY == message)
		{
			::SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(nullptr));
			dialogPtr->setHandle(nullptr);
		}


		return windowMessage.lResult;
	}


	return ::DefWindowProcW(hwnd, message, wParam, lParam);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




