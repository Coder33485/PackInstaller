#pragma once
#include "afxdialogex.h"


// CGetPathDlg 对话框

class CGetPathDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGetPathDlg)

public:
	CGetPathDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGetPathDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GETPATH_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditPath();
	CEdit EditPath;
	CStatic StaticDisplay;
	CButton ButtonOK;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonScan();
	virtual void OnOK();
	afx_msg void OnBnClickedButtonOk();
};
