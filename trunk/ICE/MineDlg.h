#pragma once


// CMineDlg dialog

class CMineDlg : public CDialog
{
	DECLARE_DYNAMIC(CMineDlg)

public:
	CMineDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMineDlg();
	PtrCoreMine pmine;
	PtrCore pcore;
	IMainUI *MainUI;
	void SetIcons(HICON iJumpIcon);
// Dialog Data
	enum { IDD = IDD_MINEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void OnClickedDecodesel(void);
	void OnClickedDecodeh(void);
	void OnClickedOk(void);
	void OnClickedCancel(void);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedProxybut();
	afx_msg void OnBnClickedUsem0();
	afx_msg void OnBnClickedBsucc();
	afx_msg void OnLbnSelchangeUmlist();
};
