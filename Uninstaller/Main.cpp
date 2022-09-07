#include <Windows.h>
#include <FileProcessor.h>
#include <ResourceProcessor.h>
#include <fstream>

#include "resource.h"

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

using namespace std;

wchar_t
RegKeyName[] = L"Installer Test Package",
ProgramName[] = L"测试安装包";

int main(int argc, char* argv[])
{
	if (MessageBox(nullptr, L"确定要卸载吗？\r\n程序及其数据将从计算机中移除，且不可恢复", L"卸载确认", MB_OKCANCEL | MB_ICONINFORMATION) != IDOK)
	{
		return -1;
	}
	HKEY hKey = nullptr;
	wchar_t Path[128] = { 0 };
	DWORD PathLen = 128;
	if (RegOpenKey(HKEY_LOCAL_MACHINE, (std::wstring(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\") + RegKeyName).c_str(), &hKey) != ERROR_SUCCESS)
	{
		return -1;
	}
	GetLocalFolderPath(Path, 128);
	SetCurrentDirectory(Path);
	if (RegGetValue(hKey, nullptr, L"InstallLocation", RRF_RT_REG_SZ, nullptr, Path, &PathLen) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return -1;
	}
	SHELLEXECUTEINFO ShExecInfo;
	if (PathExist("./PreUninstall.exe"))
	{
		memset(&ShExecInfo, 0, sizeof(ShExecInfo));
		ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
		ShExecInfo.hwnd = nullptr;
		ShExecInfo.lpVerb = L"runas";
		ShExecInfo.lpFile = L".\\PreUninstall.exe\0";
		ShExecInfo.lpParameters = nullptr;
		ShExecInfo.lpDirectory = nullptr;
		ShExecInfo.nShow = SW_HIDE;
		ShExecInfo.hInstApp = nullptr;
		ShellExecuteEx(&ShExecInfo);
		if (ShExecInfo.hProcess)
		{
			WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
		}
		CloseHandle(ShExecInfo.hProcess);
	}
	Delete((std::wstring(L"C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\") + ProgramName).c_str());
	Delete((std::wstring(L"C:\\Users\\Public\\Desktop\\") + ProgramName + L".lnk").c_str());
	RegDeleteKey(HKEY_LOCAL_MACHINE, (std::wstring(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\") + RegKeyName).c_str());
	ExpResource(L".\\Uninstall_DeletePath_ByCoder33485.bat", IDR_BAT_DELETE, L"BAT");
	ShellExecuteA(nullptr, "runas", ".\\Uninstall_DeletePath_ByCoder33485.bat", nullptr, nullptr, SW_HIDE);  
	return 0;
}