#pragma once


// CShipDlg dialog

class CShipDlg : public CDialog
{
	DECLARE_DYNAMIC(CShipDlg)

public:
	CShipDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CShipDlg();
	PtrCoreShip pship;
	PtrCore pcore;
	CString sArtPath;
	IMainUI *MainUI;
	void SetIcons(HICON iJumpIcon);
	CBMPMDLButton mdlbmp;
	CBMPMDLButton mdlbmp2;
// Dialog Data
	enum { IDD = IDD_SHIPDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog(void);
	void OnClickedOk(void);
	void OnClickedCancel(void);
	void OnClickedModeledit(void);
	afx_msg void OnBnClickedBsucc();
};


class CShipLoadout : public CDialog
{
	DECLARE_DYNAMIC(CShipLoadout)

public:
	CShipLoadout(CWnd* pParent = NULL);   // standard constructor
	virtual ~CShipLoadout();
	PtrCoreShip pship;
	PtrCore pcore;
	CString sArtPath;
	IMainUI *MainUI;

	CBMPMDLButton mdlbmp;
	CBMPMDLButton mdlbmp2;
// Dialog Data
	enum { IDD = IDD_LOADOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog(void);
	void OnClickedOk(void);
	void OnClickedCancel(void);
	void OnSelchangePartsel(void);
	void OnSelchangeWepsel(void);
	void OnBnClickedDltoggle(void);
protected:
	int DLCheck;
	unsigned short DLList[IGCSHIPMAXPARTS];
	void BuildDL(void);
	void SaveDL(void);
public:
	void OnLbnSelchangePartlist();
	afx_msg void OnBnClickedWctoggle();
	afx_msg void OnLbnSelchangeWepchoice();
	afx_msg void OnBnClickedWepadd();
	afx_msg void OnBnClickedWepdel();
	afx_msg void OnBnClickedParttoggle();
	afx_msg void OnLbnSelcancelPartchoice();
	afx_msg void OnLbnSelchangePartchoice();
};
