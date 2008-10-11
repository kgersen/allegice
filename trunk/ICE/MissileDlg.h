#pragma once


// CMissileDlg dialog

class CMissileDlg : public CDialog
{
	DECLARE_DYNAMIC(CMissileDlg)

public:
	CMissileDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMissileDlg();
	PtrCoreMissile pmissile;
	CString sArtPath;
	PtrCore pcore;
	IMainUI *MainUI;
	void SetIcons(HICON iJumpIcon);
	CBMPMDLButton mdlbmp;
	CBMPMDLButton mdlbmp2;

// Dialog Data
	enum { IDD = IDD_MISSILEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void OnClickedDecodeh(void);
	void OnClickedDecodesel(void);
	BOOL OnInitDialog(void);
	void OnClickedOk(void);
	void OnClickedCancel(void);
	afx_msg void OnBnClickedUsem0();
	afx_msg void OnBnClickedBsucc();
	afx_msg void OnLbnSelchangeUmlist();
};
