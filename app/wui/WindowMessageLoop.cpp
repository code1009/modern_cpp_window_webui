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

void WindowMessageLoop::runLoop(void)
{
#if 0
	//------------------------------------------------------------------------
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
#endif


	//------------------------------------------------------------------------
	//HACCEL hAccel;
	
	
	//hAccel = getInstance()->loadAccelerators(_AccelId);



	//------------------------------------------------------------------------
#if 0
	MSG msg;

	
	while (::GetMessage(&msg, nullptr, 0, 0))
	{
		if (!::TranslateAccelerator(msg.hwnd, hAccel, &msg))
		{
			::TranslateMessage(&msg);
			::DispatchMessageW(&msg);
		}
	}
#endif


	//------------------------------------------------------------------------
	MSG msg;


	while (::GetMessage(&msg, nullptr, 0, 0))
	{
		::TranslateMessage(&msg);
		::DispatchMessageW(&msg);
	}
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




