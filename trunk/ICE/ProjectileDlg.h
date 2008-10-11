#pragma once


// CProjectileDlg dialog

class CProjectileDlg : public CDialog
{
	DECLARE_DYNAMIC(CProjectileDlg)

public:
	CProjectileDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProjectileDlg();
	PtrCoreProjectile pprojectile;
	PtrCore pcore;
	CString sArtPath;
	IMainUI *MainUI;
	CBMPMDLButton mdlbmp;
// Dialog Data
	enum { IDD = IDD_PROJECTILEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void OnClickedDecodesel(void);
	void OnClickedDecodeh(void);
	BOOL OnInitDialog(void);
	void OnClickedOk(void);
	void OnClickedCancel(void);
//	afx_msg void OnLbnDblclkProjweplist();
	afx_msg void OnLbnSelchangeProjweplist();
};
