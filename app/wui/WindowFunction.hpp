#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class Window;
class WindowMessage;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
std::wstring getWindowText(const Window* window);
void         setWindowText(const Window* window, const std::wstring& s);

void moveWindow(const Window* window, const RECT& rect, bool repaint = false);
void setWindowPos(const Window* window, const HWND insertAfter, const RECT& rect, UINT flags);

void sendMessage(const Window* window, WindowMessage& windowMessage);




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void moveWindow(const HWND hwnd, const RECT& rect, bool repaint = false);
void setWindowPos(const HWND hwnd, const HWND insertAfter, const RECT& rect, UINT flags);
void sendMessage(const HWND hwnd, WindowMessage& windowMessage);






/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




