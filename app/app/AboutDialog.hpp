#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace app
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class AboutDialog : public wui::BasicModalDialog
{
public:
	AboutDialog():
		wui::BasicModalDialog{ IDD_ABOUTBOX }
	{
		//-------------------------------------------------------------------
		registerWindowMessageHandler();
	}

	~AboutDialog()
	{
	}

	virtual void registerWindowMessageHandler(void) override
	{
		getWindowMessageHandler(WM_INITDIALOG) = [this](wui::WindowMessage& windowMessage) { onInitDialog(windowMessage); };
		getWindowMessageHandler(WM_DESTROY   ) = [this](wui::WindowMessage& windowMessage) { onDestory(windowMessage); };
		getWindowMessageHandler(WM_COMMAND   ) = [this](wui::WindowMessage& windowMessage) { onCommand(windowMessage); };
	}

	void onInitDialog(wui::WindowMessage& windowMessage)
	{
		//-----------------------------------------------------------------------
		int v0;
		int v1;
		int v2;
		int v3;


		v0 = 0;
		v1 = 0;
		v2 = 0;
		v3 = 0;


		//-----------------------------------------------------------------------
		TCHAR szFileName[MAX_PATH] = { '\0' };


		GetModuleFileName(NULL, szFileName, sizeof(szFileName));


		//-----------------------------------------------------------------------
		DWORD dwHandle = 0;
		DWORD dwLen = 0;


		dwLen = GetFileVersionInfoSize(szFileName, &dwHandle);
		if (dwLen)
		{
			std::vector<BYTE> data(dwLen);


			if (GetFileVersionInfo(szFileName, dwHandle, dwLen, &data[0]))
			{
				VS_FIXEDFILEINFO* pInfo;
				UINT uLen;


				if (VerQueryValue(&data[0], _T("\\"), reinterpret_cast<LPVOID*>(&pInfo), &uLen))
				{
					v0 = pInfo->dwProductVersionMS >> 16;
					v1 = pInfo->dwProductVersionMS & 0xffff;
					v2 = pInfo->dwProductVersionLS >> 16;
					v3 = pInfo->dwProductVersionLS & 0xffff;
				}
			}
		}


		//-----------------------------------------------------------------------
		TCHAR app_version[256];


		_stprintf_s(app_version, _T("버젼 %d.%d.%d.%d"),
			v0,
			v1,
			v2,
			v3
		);

		SetDlgItemText(getHandle(), IDC_ABOUT_APP_VERSION, app_version);


		//-----------------------------------------------------------------------
		std::wstring note;


		note = L"https://github.com/code1009/modern_cpp_window_webui.git\n\n즐거운 셈말짓기 되세요!";
		SetDlgItemText(getHandle(), IDC_ABOUT_APP_NOTE, note.c_str());


		//-----------------------------------------------------------------------
		std::wstring windowText;


		windowText = wui::getInstance()->loadString(IDS_APP_TITLE);


		SetDlgItemText(getHandle(), IDC_ABOUT_APP_NAME, windowText.c_str());


		//-------------------------------------------------------------------
		defaultWindowMessageHandler(windowMessage);
	}

	void onDestory(wui::WindowMessage& windowMessage)
	{
	}

	void onCommand(wui::WindowMessage& windowMessage)
	{
		wui::WM_COMMAND_WindowMessageManipulator windowMessageManipulator(&windowMessage);


		switch (windowMessageManipulator.nID())
		{
		case IDOK:
			onOK(windowMessage);
			return;
			break;

		case IDCANCEL:
			onCancel(windowMessage);
			return;
			break;

		default:
			break;
		}


		defaultWindowMessageHandler(windowMessage);
	}

	void onOK(wui::WindowMessage& windowMessage)
	{
		endDialog(IDOK);
	}

	void onCancel(wui::WindowMessage& windowMessage)
	{
		endDialog(IDCANCEL);
	}
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




