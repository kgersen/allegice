#pragma once


// CConstantsDlg dialog

class CConstantsDlg : public CDialog
{
	DECLARE_DYNAMIC(CConstantsDlg)

public:
	CConstantsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CConstantsDlg();
	PtrCoreConstants pconst;
	PtrCore pcore;
	IMainUI *MainUI;

// Dialog Data
	enum { IDD = IDD_CONSTANTSDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeDm();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLbnSelchangeGloballist();
	afx_msg void OnBnClickedGlobalset();
protected:
	bool bIniChanged;
	bool bShowAC;
	void BuildConstList(int);
	void SetLabels();
	CString ConstLabs[IGCNUMC];
	void OnEnSetfocusS(int i);
	void FillUsage();
	void FillUsage(int i);
	void FillDMUsage(int i);
	void FillACUsage(int i);
public:
	afx_msg void OnLbnSelchangeDmusage();
	afx_msg void OnBnClickedBswtich();
	afx_msg void OnEnSetfocusS1();
	afx_msg void OnEnSetfocusS2();
	afx_msg void OnEnSetfocusS3();
	afx_msg void OnEnSetfocusS4();
	afx_msg void OnEnSetfocusS5();
	afx_msg void OnEnSetfocusS6();
	afx_msg void OnEnSetfocusS7();
	afx_msg void OnEnSetfocusS8();
	afx_msg void OnEnSetfocusS9();
	afx_msg void OnEnSetfocusS10();
	afx_msg void OnEnSetfocusS11();
	afx_msg void OnEnSetfocusS12();
	afx_msg void OnEnSetfocusS13();
	afx_msg void OnEnSetfocusS14();
	afx_msg void OnEnSetfocusS15();
	afx_msg void OnEnSetfocusS16();
	afx_msg void OnEnSetfocusS17();
	afx_msg void OnEnSetfocusS18();
	afx_msg void OnEnSetfocusS19();
	afx_msg void OnEnSetfocusS20();
	afx_msg void OnEnKillfocusS();
};
