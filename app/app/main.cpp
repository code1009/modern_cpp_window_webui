#include "pch.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#if 0
#ifdef _DEBUG

#include "../vld/include/vld.h"

// 추가 라이브러리 디렉토리:
// $(ProjectDir)\vld\lib\Win64; % (AdditionalLibraryDirectories)

#endif // _DEBUG
#endif





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
	//-----------------------------------------------------------------------
	MessageBoxA(nullptr, (LPCSTR)u8"가나다라", (LPCSTR)u8"제목", MB_OK);
#if 0
	https://learn.microsoft.com/en-us/windows/apps/design/globalizing/use-utf8-code-page

	<application xmlns = "urn:schemas-microsoft-com:asm.v3">
		<windowsSettings>
		<activeCodePage xmlns = "http://schemas.microsoft.com/SMI/2019/WindowsSettings">UTF - 8 < / activeCodePage >
		<dpiAware xmlns = "http://schemas.microsoft.com/SMI/2005/WindowsSettings">true< / dpiAware>
		<dpiAwareness xmlns = "http://schemas.microsoft.com/SMI/2016/WindowsSettings">PerMonitorV2, PerMonitor< / dpiAwareness>
		</windowsSettings>
	</application>
#endif


	//-----------------------------------------------------------------------
	wui::getWindowInstance()->setHandle(hInstance);
	run();

	return 0;
}
