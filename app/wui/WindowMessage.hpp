﻿#pragma once

/////////////////////////////////////////////////////////////////////////////
//
// File: WindowMessage.hpp
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
class WindowMessage final
{
public:
	HWND     hWnd;
	uint32_t uMsg;
	WPARAM   wParam;
	LPARAM   lParam;
	LRESULT  lResult;

public:
	explicit WindowMessage(
		HWND          hwnd,
		std::uint32_t umsg,
		WPARAM        wparam,
		LPARAM        lparam
	);

public:
	WindowMessage(const WindowMessage& other);
	WindowMessage& operator=(const WindowMessage& other);

	WindowMessage(WindowMessage&& other) noexcept;
	WindowMessage& operator=(WindowMessage&& other) noexcept;
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




