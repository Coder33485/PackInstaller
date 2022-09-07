// GetPathDlg.cpp: 实现文件
//

#include "pch.h"
#include "Installer.h"
#include "afxdialogex.h"
#include "GetPathDlg.h"

#include <StringProcessor.h>


// CGetPathDlg 对话框

IMPLEMENT_DYNAMIC(CGetPathDlg, CDialogEx)

CGetPathDlg::CGetPathDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GETPATH_DIALOG, pParent)
{

}

CGetPathDlg::~CGetPathDlg()
{
}

void CGetPathDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PATH, EditPath);
	DDX_Control(pDX, IDC_STATIC_DISPLAY, StaticDisplay);
	DDX_Control(pDX, IDC_BUTTON_OK, ButtonOK);
}


BEGIN_MESSAGE_MAP(CGetPathDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_PATH, &CGetPathDlg::OnEnChangeEditPath)
	ON_BN_CLICKED(IDC_BUTTON_SCAN, &CGetPathDlg::OnBnClickedButtonScan)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CGetPathDlg::OnBnClickedButtonOk)
END_MESSAGE_MAP()


// CGetPathDlg 消息处理程序


void CGetPathDlg::OnEnChangeEditPath()
{
	CString Path, CannotInstall, WillInstallat;
	CannotInstall.LoadString(IDS_STRING_CANNOTINSTALL);
	WillInstallat.LoadString(IDS_STRING_WILLINSTALLAT);
	auto Tips = [&](BOOL INSTALL)
	{
		if (INSTALL)
		{
			StaticDisplay.SetWindowText(WillInstallat + L" " + Path);
		}
		else
		{
			StaticDisplay.SetWindowText(CannotInstall);
		}
		ButtonOK.EnableWindow(INSTALL);
	};
	EditPath.GetWindowText(Path);
	if (Path.GetLength() < 4 || Path[0] < 'A' || Path[0] > 'Z' || Path[1] != ':' || Path[2] != '\\')
	{
		Tips(FALSE);
		return;
	}
	if (IsStringMatchingHead(L"C:\\Windows", Path.GetString()))
	{
		Tips(FALSE);
		return;
	}
	bool slash = false;
	for (UINT i = 2; i < Path.GetLength(); i++)
	{
		if (Path[i] == '/' || Path[i] == ':' || Path[i] == '*' || Path[i] == '?' || Path[i] == '\"' || Path[i] == '<' || Path[i] == '>' || Path[i] == '|')
		{
			Tips(FALSE);
			return;
		}
		if (Path[i] == '\\')
		{
			if (slash)
			{
				Tips(FALSE);
				return;
			}
			else
			{
				slash = true;
			}
		}
		else
		{
			slash = false;
		}
	}
	Tips(TRUE);
}


BOOL CGetPathDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	EditPath.SetWindowText(DefaultPath);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CGetPathDlg::OnBnClickedButtonScan()
{
	CFolderPickerDialog Dlg(DefaultPath);
	Dlg.DoModal();
	CString Path = Dlg.GetPathName();
	EditPath.SetWindowText(Path);
}


void CGetPathDlg::OnOK()
{
	// Nothing to do.
}


void CGetPathDlg::OnBnClickedButtonOk()
{
	EditPath.GetWindowText(Path);
	CDialogEx::OnOK();
}
