#pragma once





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




