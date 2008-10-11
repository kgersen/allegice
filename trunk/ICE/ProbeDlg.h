#pragma once


// CProbeDlg dialog

class CProbeDlg : public CDialog
{
	DECLARE_DYNAMIC(CProbeDlg)

public:
	CProbeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProbeDlg();
	PtrCoreProbe pprobe;
	PtrCore pcore;
	CString sArtPath;
	IMainUI *MainUI;
	void SetIcons(HICON iJumpIcon);
	CBMPMDLButton mdlbmp;
	CBMPMDLButton mdlbmp2;
// Dialog Data
	enum { IDD = IDD_PROBEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void OnClickedDecodesel(void);
	void OnClickedDecodeh(void);
	BOOL OnInitDialog(void);
	void OnClickedOk(void);
	void OnClickedCancel(void);
	afx_msg void OnBnClickedProxybut();
	afx_msg void OnBnClickedUsem48();
	afx_msg void OnBnClickedBprojid();
	afx_msg void OnBnClickedBsucc();
	afx_msg void OnLbnSelchangeUmlist();
};
