#pragma once

/////////////////////////////////////////////////////////////////////////////
//
// File: WindowMessageLoop.hpp
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
namespace wui
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WindowMessageLoop
{
public:
	WindowMessageLoop();
	virtual ~WindowMessageLoop();

public:
	WindowMessageLoop(const WindowMessageLoop&) = delete;
	WindowMessageLoop& operator=(const WindowMessageLoop&) = delete;

	WindowMessageLoop(WindowMessageLoop&&) = delete;
	WindowMessageLoop& operator=(WindowMessageLoop&&) = delete;

public:
	virtual void runLoop(void);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




