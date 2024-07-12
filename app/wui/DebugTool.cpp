/////////////////////////////////////////////////////////////////////////////
//
// File: DebugTool.cpp
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





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
static std::wstring get_file_of_file_path(std::wstring file_path)
{
	std::wstring result;

	std::wstring::size_type index;


	index = file_path.find_last_of(L"\\/");
	if (std::wstring::npos == index)
	{
		return result;
	}


	result = file_path.substr(index + 1);

	return result;
}

//===========================================================================
void trace(const std::wstring& message,
	const wchar_t* file, 
	const int line,
	const wchar_t* func
	)
{
	//-------------------------------------------------------------------------
	DWORD threadId;


	threadId = ::GetCurrentThreadId();


	//-------------------------------------------------------------------------
	SYSTEMTIME st;


	GetLocalTime(&st);


	//-------------------------------------------------------------------------
	std::wostringstream oss;


	//-------------------------------------------------------------------------
	oss << L"[";
	oss << L"0x" << std::uppercase << std::setfill(L'0') << std::setw(8) << std::hex;
	oss << threadId;
	oss << L"]";


	//-------------------------------------------------------------------------
	oss << L" ";


	//-------------------------------------------------------------------------
	oss << L"[";


	//-------------------------------------------------------------------------
#if 0
	oss.width(4);
	oss.fill(L'0');
	oss.setf(std::ios::dec | std::ios::right, std::ios::basefield | std::ios::adjustfield);
	oss << st.wYear;

	oss << L"-";

	oss.width(2);
	oss.fill(L'0');
	oss.setf(std::ios::dec | std::ios::right, std::ios::basefield | std::ios::adjustfield);
	oss << st.wMonth;

	oss << L"-";

	oss.width(2);
	oss.fill(L'0');
	oss.setf(std::ios::dec | std::ios::right, std::ios::basefield | std::ios::adjustfield);
	oss << st.wDay;


	//-------------------------------------------------------------------------
	oss << L" ";
#endif


	//-------------------------------------------------------------------------
	oss.width(2);
	oss.fill(L'0');
	oss.setf(std::ios::dec | std::ios::right, std::ios::basefield | std::ios::adjustfield);
	oss << st.wHour;

	oss << L":";

	oss.width(2);
	oss.fill(L'0');
	oss.setf(std::ios::dec | std::ios::right, std::ios::basefield | std::ios::adjustfield);
	oss << st.wMinute;

	oss << L":";

	oss.width(2);
	oss.fill(L'0');
	oss.setf(std::ios::dec | std::ios::right, std::ios::basefield | std::ios::adjustfield);
	oss << st.wSecond;

	oss << L".";

	oss.width(3);
	oss.fill(L'0');
	oss.setf(std::ios::dec | std::ios::right, std::ios::basefield | std::ios::adjustfield);
	oss << st.wMilliseconds;


	//-------------------------------------------------------------------------
	oss << L"]";


	//-------------------------------------------------------------------------
	oss << L" ";
	oss << message;

	oss << L" <";
	oss << get_file_of_file_path(file);
	oss << L":";
	oss << line;
	oss << L"> - ";
	oss << func;
	oss << L"()";

	oss << std::endl;


	//-------------------------------------------------------------------------
	OutputDebugStringW(oss.str().c_str());
}

void debugPrintln(const std::wstring& message)
{
	std::wostringstream oss;


	oss << message;
	oss << std::endl;


	OutputDebugStringW(oss.str().c_str());
}

void errorReport(const std::wstring& message)
{
	//-----------------------------------------------------------------------
	DWORD dwLastErrorCode;
	DWORD dwSystemLocale;
	DWORD dwFlags;
	HLOCAL hLocal;
	DWORD dwLength;


	dwLastErrorCode = GetLastError();
	dwSystemLocale = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);
	dwFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
	hLocal = NULL;
	dwLength = FormatMessageW(dwFlags, NULL, dwLastErrorCode, dwSystemLocale, (LPWSTR)&hLocal, 0, NULL);


	//-----------------------------------------------------------------------
	if (!dwLength)
	{
		ExitProcess(dwLastErrorCode);
		return;
	}


	//-----------------------------------------------------------------------
	std::wstring errorString = ((const WCHAR*)hLocal);


	//-----------------------------------------------------------------------
	WCHAR* errorMessageString;
	std::size_t errorMessageStringLength;


	errorMessageStringLength = message.size() + errorString.size() + 40;
	errorMessageString = new WCHAR[errorMessageStringLength];

	StringCchPrintfW(errorMessageString,
		errorMessageStringLength,
		L"%s failed with error %d: %s",
		message.c_str(),
		dwLastErrorCode,
		errorString.c_str()
	);
	debugPrintln(errorMessageString);
	MessageBoxW(NULL, errorMessageString, L"Error", MB_ICONEXCLAMATION|MB_OK);

	delete[] errorMessageString;
	

	//-----------------------------------------------------------------------
	LocalFree(hLocal);


	//-----------------------------------------------------------------------
	ExitProcess(dwLastErrorCode);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




