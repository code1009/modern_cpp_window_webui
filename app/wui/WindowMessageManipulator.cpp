/////////////////////////////////////////////////////////////////////////////
//
// File: WindowMessageManipulator.cpp
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
#include "WindowMessage.hpp"
#include "Window.hpp"
#include "WindowMessageLoop.hpp"

#include "WindowMessageManipulator.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
WindowMessageManipulator::WindowMessageManipulator(WindowMessage* windowMessage) :
	_windowMessage{ windowMessage }
{
}

WindowMessageManipulator::~WindowMessageManipulator()
{
}

WindowMessage* WindowMessageManipulator::getWindowMessage(void)
{
	return _windowMessage;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




