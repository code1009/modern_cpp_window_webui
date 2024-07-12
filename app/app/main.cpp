#include "pch.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#if 1
#ifdef _DEBUG

#include "../vld/include/vld.h"

// 추가 라이브러리 디렉토리:
// $(ProjectDir)\vld\lib\Win64;%(AdditionalLibraryDirectories)

#endif // _DEBUG
#endif





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
// winver.h(Windows.h 포함)
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
int runApp(void)
{
	//-----------------------------------------------------------------------
#if 1
	HRESULT hr;


	//hr = ::CoInitialize(nullptr);
	hr = ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
	if (FAILED(hr))
	{
		return -1;
	}
#endif
	

	//-----------------------------------------------------------------------
	runAppWindow();

	
	//-----------------------------------------------------------------------
#if 1
	::CoUninitialize();
#endif

	return 0;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
int run(void)
{
	//-----------------------------------------------------------------------
	::SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);


	//-----------------------------------------------------------------------
#if 0
	HRESULT hr;


	hr = ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
	if (FAILED(hr))
	{
		return -1;
	}
#endif


	//-----------------------------------------------------------------------
	std::thread thread1(runApp);
	::Sleep(1000);

	std::thread thread2(runApp);


	//-----------------------------------------------------------------------
	//runApp();
	//runAppWindow();


	//-----------------------------------------------------------------------
	thread1.join();
	thread2.join();


	//-----------------------------------------------------------------------
#if 0
	::CoUninitialize();
#endif


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
#if 0
	//-----------------------------------------------------------------------
	MessageBoxA(nullptr, (LPCSTR)u8"가나다라", (LPCSTR)u8"제목", MB_OK);
	/*
	.manifest에 아래 적용하면 vld에서 오류가 발생함.

	https://learn.microsoft.com/en-us/windows/apps/design/globalizing/use-utf8-code-page

	<application xmlns = "urn:schemas-microsoft-com:asm.v3">
		<windowsSettings>
		<activeCodePage xmlns = "http://schemas.microsoft.com/SMI/2019/WindowsSettings">UTF - 8 < / activeCodePage >
		<dpiAware xmlns = "http://schemas.microsoft.com/SMI/2005/WindowsSettings">true< / dpiAware>
		<dpiAwareness xmlns = "http://schemas.microsoft.com/SMI/2016/WindowsSettings">PerMonitorV2, PerMonitor< / dpiAwareness>
		</windowsSettings>
	</application>
	*/
#endif


	//-----------------------------------------------------------------------
	wui::getInstance()->setHandle(hInstance);
	run();

	return 0;
}
