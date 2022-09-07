
// InstallerDlg.h: 头文件
//

#pragma once


// CInstallerDlg 对话框
class CInstallerDlg : public CDialogEx
{
	// 构造
public:
	CInstallerDlg(CWnd* pParent = nullptr);	// 标准构造函数

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSTALLER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	int Step;
	int LastStep;
	bool InstallFlag;
	CString Message;
public:
	void ProcessSteps();
	void PrevStep();
	void NextStep();
	void PushMessage(LPCWSTR lpMessage);
	void PushMessage(UINT nID);
	void CleanMessage();
	void BlockExit();
	void AllowExit();
	virtual void OnOK();
	void Install();
	CEdit EditDisplay;
	CButton ButtonPrev;
	CButton ButtonNext;
	CButton ButtonCancel;
	afx_msg void OnBnClickedButtonPrev();
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedButtonCancel();
};
