﻿/////////////////////////////////////////////////////////////////////////////
//
// File: Instance.cpp
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





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
Instance::Instance():
	_Handle{ nullptr }
{
}

//===========================================================================
HINSTANCE Instance::getHandle(void) const
{
	return _Handle;
}

HINSTANCE Instance::setHandle(HINSTANCE handle)
{
	HINSTANCE old;


	old = _Handle;
	_Handle = handle;

	return _Handle;
}

//===========================================================================
std::wstring Instance::loadString(int id)
{
	LPWSTR ptr;
	LPWSTR* pptr;
	int rv;


	ptr = nullptr;
	pptr = &ptr;
	rv = ::LoadStringW(getHandle(),
		id,
		(LPWSTR)pptr,
		0
	);


	std::wstring s;


	if (rv)
	{
		if (ptr)
		{
			s = ptr;
		}
	}

	return s;
}

//===========================================================================
HCURSOR Instance::loadCursor(int id)
{
	return loadCursor(makeIntResource(id));
}

HICON Instance::loadIcon(int id)
{
	return loadIcon(makeIntResource(id));
}

HBITMAP Instance::loadBitmap(int id)
{
	return loadBitmap(makeIntResource(id));
}

HACCEL Instance::loadAccelerators(int id)
{
	return loadAccelerators(makeIntResource(id));
}

//===========================================================================
HCURSOR Instance::loadCursor(LPCWSTR id)
{
	return ::LoadCursorW(getHandle(), id);
}

HICON Instance::loadIcon(LPCWSTR id)
{
	return ::LoadIconW(getHandle(), id);
}

HBITMAP Instance::loadBitmap(LPCWSTR id)
{
	return ::LoadBitmapW(getHandle(), id);
}

HACCEL Instance::loadAccelerators(LPCWSTR id)
{
	return ::LoadAcceleratorsW(getHandle(), id);
}

//===========================================================================
LPCWSTR Instance::makeIntResource(int id)
{
	return MAKEINTRESOURCE(id);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
Instance* getInstance(void)
{
	static Instance instance;

	return &instance;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




