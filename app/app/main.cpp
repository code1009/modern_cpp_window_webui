#include "pch.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#if 0

# Code alignment for Visual Studio
https ://marketplace.visualstudio.com/items?itemName=cpmcgrath.Codealignment

#endif





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
// 	winver.h(Windows.h 포함)
// Api-ms-win-core-version-l1-1-0.dll
#pragma comment (lib, "Version.lib")





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void runAppWindow(void)
{
	wui::WindowMessageLoop windowMessageLoop;


	app::MainFrame mainFrame;


	windowMessageLoop.runLoop();
}




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
int run(void)
{
	//-----------------------------------------------------------------------
	::SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);


	//-----------------------------------------------------------------------
	HRESULT hr;


	hr = ::CoInitialize(NULL);
	if (FAILED(hr))
	{
		return -1;
	}
	

	//-----------------------------------------------------------------------
	runAppWindow();

	
	//-----------------------------------------------------------------------
	::CoUninitialize();

	return 0;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
int APIENTRY wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR    lpCmdLine,
	int       nCmdShow)
{
	wui::getWindowInstance()->setHandle(hInstance);
	run();

	return 0;
}
