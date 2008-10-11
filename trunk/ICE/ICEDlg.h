// ICEDlg.h : header file
//

#pragma once

// CICEDlg dialog
class CICEDlg : public CDialog, public IMainUI
{
// Construction
public:
	CICEDlg(CWnd* pParent = NULL);	// standard constructor
	CString cArtPath;
	CString sCorename;
	CString sCorepath;
	PtrCore pigccore;
	CString sCoreArg;
	HICON iJumpIcon;
	HICON iBackIcon;
// Dialog Data
	enum { IDD = IDD_ICE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	CString sTechName;
	UCHAR *pTechTree;
	UCHAR *pTechTreeLocal;
	PtrCoreEntry curpce;
	LPARAM store;
	LPARAM store1;
	LPARAM store2;
	UCHAR tFilter[50];
	bool changed;
	HICON m_hIcon;
	CTreeCtrl * maintree;
	CDialog *curdiag;
	CCivDlg dlgCiv;
	CChaffDlg dlgChaff;
	CDevelDlg dlgDevel;
	CDroneDlg dlgDrone;
	CMineDlg dlgMine;
	CMissileDlg dlgMissile;
	CPartDlg dlgPart;
	CProbeDlg dlgProbe;
	CProjectileDlg dlgProjectile;
	CShipDlg dlgShip;
	CShipLoadout dlgShipLoadout;
	CStationDlg dlgStation;
	CConstantsDlg dlgConstants;
	CTreasureDlg dlgTreasure;
	HTREEITEM hCore;     
	HTREEITEM hCivs;     
	HTREEITEM hConstants;
	HTREEITEM hCounters;
	HTREEITEM hDevels;
	HTREEITEM hDrones;  
	HTREEITEM hMines;   
	HTREEITEM hMissiles;
	HTREEITEM hShips;
	HTREEITEM hParts;
	HTREEITEM hProbes;
	HTREEITEM hProjectiles;
	HTREEITEM hStationsRoot;
	HTREEITEM hTreasureSets;
	HTREEITEM hStations[MAXCIVS]; // should be dyn 
	HTREEITEM hTechPaths[MAXPATHS]; // should be dyn

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void FreeTreePCE();
	void FreeTreePCE(CTreeCtrl *, HTREEITEM);
	void BuildTree(void);
	void OnSelchangeMainTree(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
public:
	void OnClickedAbout(void);
	void OnClickedLoad(void);
	void OnClickedSave(void);
	CString DoBackup(CString, CString);
	void OnClickedSaveas(void);
	void OnClickedCancel(void);
	int DiscardChanges(void);
protected:
	void OnCancel(void);
	void OnOK(void);
	void LoadCore(CString);
public:
	void OnClickedQuit(void);
//	void OnSelchangeTechlist(void);
//	void OnClickTechVal(void);
	CString TTHaveBit(int ibit);
	void OnClickedRefresh(void);
	afx_msg void OnBnClickedClearpre();
	afx_msg void OnBnClickedCleardef();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDelete();
	void SelectPCE(LPARAM);
	HICON GetJumpIcon();
	void SelectPCE(LPARAM,HTREEITEM);
//	afx_msg void OnEnChangeTechtree();
	afx_msg void OnBnClickedTechtreeup();
	afx_msg void OnBnClickedTechtreedown();
	afx_msg void OnBnClickedTogglepre();
	afx_msg void OnBnClickedToggledef();
	void SelchangeMaintab();
protected:
	void ShowTechBit(UCHAR *,UCHAR *,int);
    void ShowTechEntry(UCHAR *,UCHAR *);
	void RefreshStores(PtrCoreEntry pce);
	void MoveEntry(int);
	void ShowMoveButtons(bool);
	void ShowTechTree(int);
	void ClearFilter(void);
	void UpdateFilter(bool);
	bool IsFiltered(UCHAR *pTT);

public:
	afx_msg void OnEnChangeTechtreeidx();
	afx_msg void OnEnSetfocusTechtreeidx();
	afx_msg void OnEnSetfocusTechtree();
	afx_msg void OnBnClickedStore1store();
	afx_msg void OnBnClickedStore2store();
	afx_msg void OnBnClickedStore1recall();
	afx_msg void OnBnClickedStore2recall();
	afx_msg void OnBnClickedCksort();
	afx_msg void OnBnClickedMoveup();
	afx_msg void OnBnClickedMovedown();
	afx_msg void OnBnClickedTogglelocal();
	afx_msg void OnBnClickedClearlocal();
	afx_msg void OnTcnSelchangeMaintab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButfilter();
	afx_msg void OnBnClickedClearfilter();
	afx_msg void OnBnClickedAddtofilter();
	afx_msg void OnBnClickedRemfromfilter();
	afx_msg void OnBnClickedValidate();
	afx_msg void OnBnClickedBback();
	afx_msg void OnBnClickedCompare();
	afx_msg void OnBnClickedDump();
	afx_msg void OnBnClickedChkart();
};
