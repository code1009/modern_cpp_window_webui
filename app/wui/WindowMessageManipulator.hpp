#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include <windowsx.h>





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WindowMessageManipulator
{
private:
	WindowMessage* _windowMessage{ nullptr };

public:
	explicit WindowMessageManipulator(WindowMessage* windowMessage);
	virtual ~WindowMessageManipulator();

public:
	WindowMessageManipulator(const WindowMessageManipulator&) = delete;
	WindowMessageLoop& operator=(const WindowMessageManipulator&) = delete;

	WindowMessageManipulator(WindowMessageManipulator&&) = delete;
	WindowMessageManipulator& operator=(WindowMessageManipulator&&) = delete;

public:
	WindowMessage* getWindowMessage(void);
};





/////////////////////////////////////////////////////////////////////////////
//
// https://github.com/Win32-WTL/WTL/blob/main/Include/atlcrack.h
// 
/////////////////////////////////////////////////////////////////////////////
//===========================================================================





/////////////////////////////////////////////////////////////////////////////
/// 
// Standard Windows message macros
// 
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
//int OnCreate(LPCREATESTRUCT lpCreateStruct)
/*
WM_CREATE
		lResult = (LRESULT)func((LPCREATESTRUCT)lParam);
*/
class WM_CREATE_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_CREATE_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	LPCREATESTRUCT lpCreateStruct(void) 
	{ 
		return (LPCREATESTRUCT)(getWindowMessage()->lParam);
	}

public:
	void Result(int rv)
	{
		getWindowMessage()->lResult = (LRESULT)rv;
	}	
};

//===========================================================================
// BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
/*
WM_INITDIALOG
		lResult = (LRESULT)func((HWND)wParam, lParam);
*/
class WM_INITDIALOG_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_INITDIALOG_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	HWND wndFocus(void)
	{ 
		return (HWND)getWindowMessage()->wParam; 
	}

	LPARAM lInitParam(void) 
	{ 
		return getWindowMessage()->lParam; 
	}

public:
	void Result(BOOL rv)
	{
		getWindowMessage()->lResult = (LRESULT) rv;
	}
};

//===========================================================================
// BOOL OnCopyData(CWindow wnd, PCOPYDATASTRUCT pCopyDataStruct)
/*
WM_COPYDATA
		lResult = (LRESULT)func((HWND)wParam, (PCOPYDATASTRUCT)lParam);
*/
class WM_COPYDATA_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_COPYDATA_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	HWND wnd(void) 
	{ 
		return (HWND)getWindowMessage()->wParam; 
	}

	PCOPYDATASTRUCT pCopyDataStruct(void) 
	{ 
		return (PCOPYDATASTRUCT)getWindowMessage()->lParam; 
	}

public:
	void Result(BOOL rv)
	{
		getWindowMessage()->lResult = (LRESULT)rv;
	}
};

//===========================================================================
//void OnDestroy()
/*
WM_DESTROY
	func(); \
	lResult = 0; \
*/
class WM_DESTROY_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_DESTROY_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:

public:
	void Result(void)
	{
		getWindowMessage()->lResult = (LRESULT)0;
	}
};

//===========================================================================
// void OnMove(CPoint ptPos)
/*
WM_MOVE
		func(_WTYPES_NS::CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))); \
		lResult = 0; \
*/
class WM_MOVE_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_MOVE_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	POINT point(void)
	{
		POINT pt{ GET_X_LPARAM(getWindowMessage()->lParam), GET_Y_LPARAM(getWindowMessage()->lParam) };

		return pt;
	}

public:
	void Result(void)
	{
		getWindowMessage()->lResult = (LRESULT)0;
	}
};

//===========================================================================
// void OnSize(UINT nType, CSize size)
/*
WM_SIZE
		func((UINT)wParam, _WTYPES_NS::CSize(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))); \
		lResult = 0; \
*/
class WM_SIZE_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_SIZE_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	UINT nTYPE(void)
	{
		return (UINT)getWindowMessage()->wParam;
	}

	SIZE size(void)
	{
		SIZE size{ GET_X_LPARAM(getWindowMessage()->lParam), GET_Y_LPARAM(getWindowMessage()->lParam) };

		return size;
	}

public:
	void Result(void)
	{
		getWindowMessage()->lResult = (LRESULT)0;
	}
};

//===========================================================================
// void OnActivate(UINT nState, BOOL bMinimized, CWindow wndOther)
/*
WM_ACTIVATE
		func((UINT)LOWORD(wParam), (BOOL)HIWORD(wParam), (HWND)lParam); \
		lResult = 0; \
*/
class WM_ACTIVATE_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_ACTIVATE_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	UINT nState(void)
	{
		return (UINT)LOWORD(getWindowMessage()->wParam);
	}

	BOOL bMinimized(void)
	{
		return (BOOL)HIWORD(getWindowMessage()->wParam);
	}

	HWND wndOther(void)
	{
		return (HWND)getWindowMessage()->lParam;
	}

public:
	void Result(void)
	{
		getWindowMessage()->lResult = (LRESULT)0;
	}
};

//===========================================================================
// void OnSetFocus(CWindow wndOld)
/*
WM_SETFOCUS
		func((HWND)wParam); \
		lResult = 0; \
*/
class WM_SETFOCUS_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_SETFOCUS_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	HWND wndOld(void)
	{
		return (HWND)getWindowMessage()->wParam;
	}

public:
	void Result(void)
	{
		getWindowMessage()->lResult = (LRESULT)0;
	}
};

//===========================================================================
// void OnKillFocus(CWindow wndFocus)
/*
WM_KILLFOCUS
		func((HWND)wParam); \
		lResult = 0; \
*/
class WM_KILLFOCUS_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_KILLFOCUS_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	HWND wndFocus(void)
	{
		return (HWND)getWindowMessage()->wParam;
	}

public:
	void Result(void)
	{
		getWindowMessage()->lResult = (LRESULT)0;
	}
};

//===========================================================================
// void OnEnable(BOOL bEnable)
/*
WM_ENABLE
		func((BOOL)wParam); \
		lResult = 0; \
*/
class WM_ENABLE_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_ENABLE_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	BOOL bEnable(void)
	{
		return (BOOL)getWindowMessage()->wParam;
	}

public:
	void Result(void)
	{
		getWindowMessage()->lResult = (LRESULT)0;
	}
};

//===========================================================================
// void OnPaint(CDCHandle dc)
/*
WM_PAINT
		func((HDC)wParam); \
		lResult = 0; \
*/
class WM_PAINT_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_PAINT_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	HDC dc(void)
	{
		return (HDC)getWindowMessage()->wParam;
	}

public:
	void Result(void)
	{
		getWindowMessage()->lResult = (LRESULT)0;
	}
};

//===========================================================================
// void OnClose()
/*
WM_CLOSE
		func(); \
		lResult = 0; \
*/
class WM_CLOSE_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_CLOSE_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:

public:
	void Result(void)
	{
		getWindowMessage()->lResult = (LRESULT)0;
	}
};

//===========================================================================
// BOOL OnQueryEndSession(UINT nSource, UINT uLogOff)
/*
WM_QUERYENDSESSION
		lResult = (LRESULT)func((UINT)wParam, (UINT)lParam); \
*/
class WM_QUERYENDSESSION_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_QUERYENDSESSION_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	UINT nSource(void)
	{
		return (UINT)getWindowMessage()->wParam;
	}

	UINT uLogOff(void)
	{
		return (UINT)getWindowMessage()->lParam;
	}

public:
	void Result(BOOL rv)
	{
		getWindowMessage()->lResult = (LRESULT)rv;
	}
};

//===========================================================================
// BOOL OnQueryOpen()
/*
WM_QUERYOPEN
		lResult = (LRESULT)func(); \
*/
class WM_QUERYOPEN_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_QUERYOPEN_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:

public:
	void Result(BOOL rv)
	{
		getWindowMessage()->lResult = (LRESULT)rv;
	}
};

//===========================================================================
// BOOL OnEraseBkgnd(CDCHandle dc)
/*
WM_ERASEBKGND
		lResult = (LRESULT)func((HDC)wParam); \
*/
class WM_ERASEBKGND_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_ERASEBKGND_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	HDC dc(void)
	{
		return (HDC)getWindowMessage()->wParam;
	}

public:
	void Result(BOOL rv)
	{
		getWindowMessage()->lResult = (LRESULT)rv;
	}
};

//===========================================================================
// void OnSysColorChange()
/*
WM_SYSCOLORCHANGE
		func(); \
		lResult = 0; \
*/
class WM_SYSCOLORCHANGE_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_SYSCOLORCHANGE_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:

public:
	void Result(void)
	{
		getWindowMessage()->lResult = (LRESULT)0;
	}
};

//===========================================================================
// void OnEndSession(BOOL bEnding, UINT uLogOff)
/*
WM_ENDSESSION
		func((BOOL)wParam, (UINT)lParam); \
		lResult = 0; \
*/
class WM_ENDSESSION_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_ENDSESSION_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	BOOL bEnding(void)
	{
		return (BOOL)getWindowMessage()->wParam;
	}

	UINT uLogOff(void)
	{
		return (UINT)getWindowMessage()->lParam;
	}

public:
	void Result(void)
	{
		getWindowMessage()->lResult = (LRESULT)0;
	}
};

//===========================================================================
// void OnShowWindow(BOOL bShow, UINT nStatus)
/*
WM_SHOWWINDOW
		func((BOOL)wParam, (int)lParam); \
		lResult = 0; \
*/
class WM_SHOWWINDOW_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_SHOWWINDOW_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	BOOL bShow(void)
	{
		return (BOOL)getWindowMessage()->wParam;
	}

	UINT nStatus(void)
	{
		return (UINT)getWindowMessage()->lParam;
	}

public:
	void Result(void)
	{
		getWindowMessage()->lResult = (LRESULT)0;
	}
};

//===========================================================================
// HBRUSH OnCtlColorEdit(CDCHandle dc, CEdit edit)
/*
WM_CTLCOLOREDIT
		lResult = (LRESULT)func((HDC)wParam, (HWND)lParam); \
*/
class WM_CTLCOLOREDIT_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_CTLCOLOREDIT_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	HDC dc(void)
	{
		return (HDC)getWindowMessage()->wParam;
	}

	HWND ctl(void)
	{
		return (HWND)getWindowMessage()->lParam;
	}

public:
	void Result(HBRUSH rv)
	{
		getWindowMessage()->lResult = (LRESULT)rv;
	}
};

//===========================================================================
// HBRUSH OnCtlColorListBox(CDCHandle dc, CListBox listBox)
/*
WM_CTLCOLORLISTBOX
		lResult = (LRESULT)func((HDC)wParam, (HWND)lParam); \
*/
using WM_CTLCOLORLISTBOX_WindowMessageManipulator = WM_CTLCOLOREDIT_WindowMessageManipulator;

//===========================================================================
// HBRUSH OnCtlColorBtn(CDCHandle dc, CButton button)
/*
WM_CTLCOLORBTN
		lResult = (LRESULT)func((HDC)wParam, (HWND)lParam); \
*/
using WM_CTLCOLORBTN_WindowMessageManipulator = WM_CTLCOLOREDIT_WindowMessageManipulator;

//===========================================================================
// HBRUSH OnCtlColorDlg(CDCHandle dc, CWindow wnd)
/*
WM_CTLCOLORDLG
		lResult = (LRESULT)func((HDC)wParam, (HWND)lParam); \
*/
using WM_CTLCOLORDLG_WindowMessageManipulator = WM_CTLCOLOREDIT_WindowMessageManipulator;

//===========================================================================
// HBRUSH OnCtlColorScrollBar(CDCHandle dc, CScrollBar scrollBar)
/*
WM_CTLCOLORSCROLLBAR
		lResult = (LRESULT)func((HDC)wParam, (HWND)lParam); \
*/
using WM_CTLCOLORSCROLLBAR_WindowMessageManipulator = WM_CTLCOLOREDIT_WindowMessageManipulator;

//===========================================================================
// HBRUSH OnCtlColorScrollBar(CDCHandle dc, CScrollBar scrollBar)
/*
WM_CTLCOLORSCROLLBAR
		lResult = (LRESULT)func((HDC)wParam, (HWND)lParam); \
*/
using WM_CTLCOLORSCROLLBAR_WindowMessageManipulator = WM_CTLCOLOREDIT_WindowMessageManipulator;

//===========================================================================
// HBRUSH OnCtlColorStatic(CDCHandle dc, CStatic wndStatic)
/*
WM_CTLCOLORSTATIC
		lResult = (LRESULT)func((HDC)wParam, (HWND)lParam); \
*/
using WM_CTLCOLORSTATIC_WindowMessageManipulator = WM_CTLCOLOREDIT_WindowMessageManipulator;


//===========================================================================
// void OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
/*
WM_SETTINGCHANGE
		func((UINT)wParam, (LPCTSTR)lParam); \
		lResult = 0; \
*/
class WM_SETTINGCHANGE_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_SETTINGCHANGE_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	UINT uFlags(void)
	{
		return (UINT)getWindowMessage()->wParam;
	}

	LPCTSTR lpszSection(void)
	{
		return (LPCTSTR)getWindowMessage()->lParam;
	}

public:
	void Result(void)
	{
		getWindowMessage()->lResult = (LRESULT)0;
	}
};




//===========================================================================
// BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct)
/*
WM_NCCREATE
		lResult = (LRESULT)func((LPCREATESTRUCT)lParam);
*/
class WM_NCCREATE_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_NCCREATE_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	LPCREATESTRUCT lpCreateStruct(void)
	{
		return (LPCREATESTRUCT)(getWindowMessage()->lParam);
	}

public:
	void Result(BOOL rv)
	{
		getWindowMessage()->lResult = (LRESULT)rv;
	}
};

//===========================================================================
// void OnNcDestroy()
/*
WM_NCDESTROY
		func(); \
		lResult = 0; \
*/
using WM_NCDESTROY_WindowMessageManipulator = WM_DESTROY_WindowMessageManipulator;





//===========================================================================
// void OnCommand(UINT uNotifyCode, int nID, CWindow wndCtl)
/*
WM_COMMAND
		func((UINT)HIWORD(wParam), (int)LOWORD(wParam), (HWND)lParam); \
		lResult = 0; \
*/
class WM_COMMAND_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_COMMAND_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	UINT uNotifyCode(void)
	{
		return (UINT)HIWORD(getWindowMessage()->wParam);
	}

	int nID(void)
	{
		return (int)LOWORD(getWindowMessage()->wParam);
	}

	HWND wndCtl(void)
	{
		return (HWND)getWindowMessage()->lParam;
	}

public:
	void Result(void)
	{
		getWindowMessage()->lResult = (LRESULT)0;
	}
};




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}






