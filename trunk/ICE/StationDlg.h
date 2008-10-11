#pragma once


// CStationDlg dialog

class CStationDlg : public CDialog
{
	DECLARE_DYNAMIC(CStationDlg)

public:
	CStationDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CStationDlg();
	PtrCoreStationType pstation;
	CString sArtPath;
	IMainUI *MainUI;
	PtrCore pcore;
	void SetIcons(HICON iJumpIcon);
	CBMPMDLButton mdlbmp;
	CBMPMDLButton imdlbmp;
	CComboBox *cbtype;
// Dialog Data
	enum { IDD = IDD_STATIONDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void OnClickedDecodesel(void);
	void OnClickedDecodeh(void);
	BOOL OnInitDialog(void);
	void OnClickedOk(void);
	void OnClickedCancel(void);
//	afx_msg void OnBnClickedUsem11();
	afx_msg void OnBnClickedUsem0();
	afx_msg void OnBnClickedUsem11();
	afx_msg void OnBnClickedBsucc();
};
