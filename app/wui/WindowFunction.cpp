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
#include "WindowFunction.hpp"
#include "Core.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
std::wstring getWindowText(const Window* window)
{
	std::wstring s;


	int length;


	length = GetWindowTextLengthW(window->getHandle());


	if (length > 0)
	{
		s.resize(length + 1, 0);

		GetWindowTextW(window->getHandle(), s.data(), length + 1);
	}


	return s;
}

void setWindowText(const Window* window, const std::wstring& s)
{
	SetWindowText(window->getHandle(), s.c_str());
}

void moveWindow(const Window* window, const RECT& rect, bool repaint)
{
	moveWindow(window->getHandle(), rect, repaint);
}

void setWindowPos(const Window* window, const HWND insertAfter, const RECT& rect, UINT flags)
{
	setWindowPos(window->getHandle(), insertAfter, rect, flags);
}

void sendMessage(const Window* window, WindowMessage& windowMessage)
{
	sendMessage(window->getHandle(), windowMessage);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void moveWindow(const HWND hwnd, const RECT& rect, bool repaint)
{
	::MoveWindow(hwnd,
		rect.left, rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		repaint ? TRUE : FALSE);
}

void setWindowPos(const HWND hwnd, const HWND insertAfter, const RECT& rect, UINT flags)
{
	::SetWindowPos(hwnd,
		insertAfter,
		rect.left, rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		flags);
}

void sendMessage(const HWND hwnd, WindowMessage& windowMessage)
{
	windowMessage.lResult =
		::SendMessageW(
			hwnd,
			windowMessage.uMsg,
			windowMessage.wParam,
			windowMessage.lParam
		);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




