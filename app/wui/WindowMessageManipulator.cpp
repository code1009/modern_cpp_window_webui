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
#include "Core.hpp"
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




