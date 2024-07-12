/////////////////////////////////////////////////////////////////////////////
//
// File: WindowMessageLoop.cpp
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

#include "WindowMessageLoop.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
WindowMessageLoop::WindowMessageLoop()
{
}

WindowMessageLoop::~WindowMessageLoop()
{
}

//===========================================================================
void WindowMessageLoop::runLoop(void)
{
	//-----------------------------------------------------------------------
	MSG msg;


	while (::GetMessageW(&msg, nullptr, 0, 0))
	{
		::TranslateMessage(&msg);
		::DispatchMessageW(&msg);
	}
}

//===========================================================================
#if 0

void WindowMessageLoop::runLoop(void)
{
	//-----------------------------------------------------------------------
	MSG msg;
	BOOL rv;


	do
	{
		rv = ::PeekMessageW(&msg, HWND{}, 0, 0, PM_REMOVE);
		if (rv != 0)
		{
			::TranslateMessage(&msg);
			::DispatchMessageW(&msg);
		}
	} while (msg.message != WM_QUIT);
}

#endif

//===========================================================================
#if 0

void WindowMessageLoop::runLoop(void)
{
	//-----------------------------------------------------------------------
	HACCEL hAccel;


	hAccel = getInstance()->loadAccelerators(_AccelId);


	//-----------------------------------------------------------------------
	MSG msg;


	while (::GetMessageW(&msg, nullptr, 0, 0))
	{
		if (!::TranslateAccelerator(msg.hwnd, hAccel, &msg))
		{
			::TranslateMessage(&msg);
			::DispatchMessageW(&msg);
		}
	}
}

#endif

//===========================================================================
#if 0

HACCEL _Accel{ nullptr };
HWND _AccelWnd{ nullptr };

void   setAccelerators(HACCEL accel, HWND accelWnd);
HACCEL getAcceleratorTable() const;
HWND   getAcceleratorsWindow() const;
bool   onIdle(int count);
bool   preTranslateMessage(MSG& msg);

int WindowMessageLoop::runLoop(void)
{
	MSG msg;


	ZeroMemory(&msg, sizeof(msg));


	int status = 1;
	int count = 0;

	while (status != 0)
	{
		while (
			(!::PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE))
			&& 
			(onIdle(count) != false)
		)
		{
			count++;
		}

		count = 0;

		if ((status = ::GetMessage(&msg, NULL, 0, 0)) == -1)
		{
			return -1;
		}

		if (!preTranslateMessage(msg))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}

	return LOWORD(msg.wParam);
}

void WindowMessageLoop::setAccelerators(HACCEL accel, HWND accelWnd)
{
	_AccelWnd = accelWnd;
	_Accel = accel;
}

HACCEL WindowMessageLoop::getAcceleratorTable() const { return _Accel; }
HWND   WindowMessageLoop::getAcceleratorsWindow() const { return _AccelWnd; }

bool WindowMessageLoop::onIdle(int count)
{
	return false;
}

bool WindowMessageLoop::preTranslateMessage(MSG& msg)
{
	BOOL isProcessed = false;


	if ((msg.message >= WM_KEYFIRST && msg.message <= WM_KEYLAST) ||
		(msg.message >= WM_MOUSEFIRST && msg.message <= WM_MOUSELAST))
	{
		if (::TranslateAccelerator(getAcceleratorsWindow(), getAcceleratorTable(), &msg))
		{
			isProcessed = true;
		}
		else
		{
			for (HWND wnd = msg.hwnd; wnd != 0; wnd = ::GetParent(wnd))
			{
				CWnd* pWnd = GetApp()->GetCWndFromMap(wnd);


				if (pWnd)
				{
					isProcessed = pWnd->PreTranslateMessage(msg);
					if (isProcessed)
					{
						break;
					}
				}
			}
		}
	}

	return isProcessed;
}

#endif





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




