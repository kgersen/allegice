#pragma once


// CCivDlg dialog

class CCivDlg : public CDialog
{
	DECLARE_DYNAMIC(CCivDlg)

public:
	CCivDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCivDlg();
	PtrCoreCiv pciv;
	PtrCore pcore;
	IMainUI *MainUI;
	void SetIcons(HICON iJumpIcon);
	CString sArtPath;
// Dialog Data
	enum { IDD = IDD_CIVDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog(void);
	void OnClickedOk(void);
	void OnClickedCancel(void);
	//void OnClickedViewicon(void);
	//void OnClickedViewmodel(void);
	//void OnClickedViewhull(void);
	//void OnClickedViewpanel(void);
	//void OnClickedViewlobby(void);
	afx_msg void OnBnClickedBgarid();
	afx_msg void OnBnClickedBlifepod();
};
