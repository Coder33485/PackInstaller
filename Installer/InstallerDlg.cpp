
// InstallerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Installer.h"
#include "InstallerDlg.h"
#include "afxdialogex.h"
#include "GetPathDlg.h"

#include <ResourceProcessor.h>
#include <StringProcessor.h>
#include <FileProcessor.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define INSTALL_SUCCEED 0
#define INSTALL_FAIL    1
#define INSTALL_CANCEL  3


// CInstallerDlg 对话框



CInstallerDlg::CInstallerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INSTALLER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	Step = 0;
	LastStep = 2;
	InstallFlag = false;
	Message.Empty();
}

void CInstallerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DISPLAY, EditDisplay);
	DDX_Control(pDX, IDC_BUTTON_PREV, ButtonPrev);
	DDX_Control(pDX, IDC_BUTTON_NEXT, ButtonNext);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, ButtonCancel);
}

BEGIN_MESSAGE_MAP(CInstallerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_PREV, &CInstallerDlg::OnBnClickedButtonPrev)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CInstallerDlg::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CInstallerDlg::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CInstallerDlg 消息处理程序

BOOL CInstallerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	ProcessSteps();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CInstallerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CInstallerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CInstallerDlg::ProcessSteps()
{
	if (Step == 0)
	{
		ButtonPrev.EnableWindow(FALSE);
	}
	else
	{
		ButtonPrev.EnableWindow(TRUE);
	}
	if (Step == LastStep)
	{
		ButtonNext.EnableWindow(FALSE);
	}
	else
	{
		ButtonNext.EnableWindow(TRUE);
	}
	switch (Step)
	{
	case 0:
		PushMessage(IDR_TXT_START);
		break;
	case 1:
		PushMessage(IDR_TXT_LICENSE);
		break;
	default:
		CleanMessage();
		if (Step == LastStep)
		{
			Install();
		}
		break;
	}
}


void CInstallerDlg::PrevStep()
{
	if (Step > 0)
	{
		Step--;
	}
	ProcessSteps();
}


void CInstallerDlg::NextStep()
{
	if (Step < LastStep)
	{
		Step++;
	}
	ProcessSteps();
}


void CInstallerDlg::PushMessage(LPCWSTR lpMessage)
{
	Message += lpMessage;
	Message += L"\r\n";
	EditDisplay.SetWindowText(Message);
}


void CInstallerDlg::PushMessage(UINT nID)
{
	DWORD len = GetResource(0, nullptr, nID, L"TXT");
	if (len != 0)
	{
		LPSTR lpBuffer = new CHAR[len + 2];
		memset(lpBuffer, 0, len + 2);
		GetResource(len + 2, lpBuffer, nID, L"TXT");
		EditDisplay.SetWindowText((LPCWSTR)lpBuffer);
		delete[] lpBuffer;
	}
	else
	{
		EditDisplay.SetWindowText(nullptr);
	}
}


void CInstallerDlg::CleanMessage()
{
	Message.Empty();
	EditDisplay.SetWindowText(nullptr);
}


void CInstallerDlg::BlockExit()
{
	CMenu& pSysMenu = *GetSystemMenu(FALSE);
	pSysMenu.EnableMenuItem(SC_CLOSE, MF_DISABLED);
}


void CInstallerDlg::AllowExit()
{
	CMenu& pSysMenu = *GetSystemMenu(FALSE);
	pSysMenu.EnableMenuItem(SC_CLOSE, MF_ENABLED);
}


void CInstallerDlg::OnOK()
{
	// Nothing to do.
}


void CInstallerDlg::Install()
{
	CString Exit, Cancel, T_Installing, InstallSucceed, InstallFail, Unpacking, InstallCancel;
	Exit.LoadString(IDS_STRING_CANCELNORMAL);
	Cancel.LoadString(IDS_STRING_CANCELINSTALLING);
	T_Installing.LoadString(IDS_STRING_INSTALLING);
	InstallSucceed.LoadString(IDS_STRING_INSTALL_OK);
	InstallFail.LoadString(IDS_STRING_INSTALL_FAIL);
	Unpacking.LoadString(IDS_STRING_UNPACKING);
	InstallCancel.LoadString(IDS_STRING_INSTALL_CANCEL);
	auto Finish = [&](int type)
	{
		InstallFlag = false;
		switch (type)
		{
		case INSTALL_SUCCEED:
			PushMessage(InstallSucceed);
			ButtonCancel.SetWindowText(Exit);
			break;
		case INSTALL_FAIL:
			PushMessage(InstallFail);
			ButtonCancel.SetWindowText(Exit);
			break;
		case INSTALL_CANCEL:
			PushMessage(InstallCancel);
			ButtonCancel.SetWindowText(Exit);
			break;
		}
		AllowExit();
	};
	ButtonPrev.EnableWindow(FALSE);
	BlockExit();
	InstallFlag = true;
	ButtonCancel.SetWindowText(Cancel);
	PushMessage(T_Installing);
	// TODO: 安装代码
	CGetPathDlg Dlg;
	if (Dlg.DoModal() == IDCANCEL)
	{
		Finish(INSTALL_FAIL);
		return;
	}
	struct stat FStat;
	if (_wmkdir(Path) != 0)
	{
		if (stat(StringWideToMultiByte(Path.GetString()).c_str(), &FStat) == 0 && (FStat.st_mode & S_IFMT) == S_IFDIR)
		{
			if (_wrmdir(Path) == 0)
			{
				if (_wmkdir(Path) != 0)
				{
					Finish(INSTALL_FAIL);
					return;
				}
			}
			else
			{
				Finish(INSTALL_FAIL);
				return;
			}
		}
		else
		{
			Finish(INSTALL_FAIL);
			return;
		}
	}
	Delete(L"TMP-INSTALL");
	_wmkdir(L"TMP-INSTALL");
	SetFilePermission(L"TMP-INSTALL", true);
	ExpResource(L"TMP-INSTALL\\7za.exe", IDR_EXE_TOOL, L"EXE");
	ExpResource(L"TMP-INSTALL\\7za.dll", IDR_DLL_TOOL, L"DLL");
	ExpResource(L"TMP-INSTALL\\Pack.zip", IDR_ZIP_PACK, L"ZIP");
	CString _CMD = L" x -tzip TMP-INSTALL\\Pack.zip -r -o\"" + Path + L"\"\0";
	LPWSTR cmdline = new WCHAR[_CMD.GetLength() + 2];
	memset(cmdline, 0, (_CMD.GetLength() + 2) * sizeof(WCHAR));
	memcpy(cmdline, _CMD.GetString(), (_CMD.GetLength()) * sizeof(WCHAR));
	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = nullptr;
	ShExecInfo.lpVerb = L"runas";
	ShExecInfo.lpFile = L"TMP-INSTALL\\7za.exe\0";
	ShExecInfo.lpParameters = cmdline;
	ShExecInfo.lpDirectory = nullptr;
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = nullptr;
	ShellExecuteEx(&ShExecInfo);
	if (ShExecInfo.hProcess)
	{
		PushMessage(Unpacking);
		hProcess = ShExecInfo.hProcess;
		WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
		DWORD ExitCode = 0;
		GetExitCodeProcess(ShExecInfo.hProcess, &ExitCode);
		CloseHandle(ShExecInfo.hProcess);
		if (ExitCode == 0xf04ca17b)
		{
			Delete(L"TMP-INSTALL");
			Delete(Path);
			Finish(INSTALL_CANCEL);
			AllowExit();
			ButtonCancel.EnableWindow(TRUE);
			return;
		}
		if (ExitCode != 0)
		{
			Delete(L"TMP-INSTALL");
			Finish(INSTALL_FAIL);
			return;
		}
	}
	else
	{
		Delete(L"TMP-INSTALL");
		Finish(INSTALL_FAIL);
		return;
	}
	Delete(L"TMP-INSTALL");
	ExpResource(Path + L"\\Uninstaller.exe", IDR_EXE_UNINSTALLER, L"EXE");
	HKEY hKey = nullptr;
	int DWORD1 = 1;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, CString(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\") + RegKeyName, 0, nullptr, 0, KEY_ALL_ACCESS, nullptr, &hKey, nullptr);
	RegSetValueEx(hKey, L"DisplayIcon", 0, REG_SZ, (LPBYTE)(Path + L"\\" + ExecutableFileRelativePath).GetString(), (Path.GetLength() + 17) * sizeof(WCHAR));
	RegSetValueEx(hKey, L"DisplayName", 0, REG_SZ, (LPBYTE)DefaultName, (wcslen(DefaultName) + 1) * sizeof(WCHAR));
	RegSetValueEx(hKey, L"HelpLink", 0, REG_SZ, (LPBYTE)HelpLink, (wcslen(HelpLink) + 1) * sizeof(WCHAR));
	RegSetValueEx(hKey, L"InstallLocation", 0, REG_SZ, (LPBYTE)Path.GetString(), (Path.GetLength() + 1) * sizeof(WCHAR));
	RegSetValueEx(hKey, L"Publisher", 0, REG_SZ, (LPBYTE)Publisher, (wcslen(Publisher) + 1) * sizeof(WCHAR));
	RegSetValueEx(hKey, L"UninstallString", 0, REG_SZ, (LPBYTE)(Path + L"\\Uninstaller.exe").GetString(), (Path.GetLength() + 17) * sizeof(WCHAR));
	RegSetValueEx(hKey, L"NoModify ", 0, REG_DWORD, (LPBYTE)&DWORD1, sizeof(DWORD1));
	RegSetValueEx(hKey, L"NoRepair ", 0, REG_DWORD, (LPBYTE)&DWORD1, sizeof(DWORD1));
	RegCloseKey(hKey);
	_wmkdir(CString(L"C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\") + DefaultName);
	CreateShotCut(Path + L"\\" + ExecutableFileRelativePath, CString(L"C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\") + DefaultName + L"\\" + DefaultName + L".lnk", Path, Path + L"\\DisplayIcon.ico", nullptr);
	CreateShotCut(Path + L"\\" + ExecutableFileRelativePath, CString(L"C:\\Users\\Public\\Desktop\\") + DefaultName + L".lnk", Path, Path + L"\\DisplayIcon.ico", nullptr);
	Finish(INSTALL_SUCCEED);
}


void CInstallerDlg::OnBnClickedButtonPrev()
{
	PrevStep();
}


void CInstallerDlg::OnBnClickedButtonNext()
{
	NextStep();
}


void CInstallerDlg::OnBnClickedButtonCancel()
{
	CString Exit;
	Exit.LoadString(IDS_STRING_CANCELNORMAL);
	if (InstallFlag)
	{
		// TODO: 取消安装代码
		TerminateProcess(hProcess, 0xf04ca17b);
		InstallFlag = false;
		ButtonCancel.SetWindowText(Exit);
		ButtonCancel.EnableWindow(FALSE);
	}
	else
	{
		OnCancel();
	}
}
