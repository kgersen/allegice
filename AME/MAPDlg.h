#pragma once
#include "IGCMap.h"
#include "ColorButton.h"
#include "BMPMDLButton.h"
#include "SectDlg.h"
#include "SectWnd.h"
#include "2DMap.h"
#include "RockTpl.h"
#include "RockTplDlg.h"

// CMAPDlg dialog

class CMAPDlg : public CDialog
{
	DECLARE_DYNAMIC(CMAPDlg)

public:
	CMAPDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMAPDlg();

// Dialog Data
	enum { IDD = IDD_MAP };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString cArtPath;
	CString cArtPathClient;
	CString sCorename;
	CString mappath;
	PtrCore pcore;
protected:
	HICON m_hIcon;
	bool changed;
	CIGCMap * pigcmap;
	CIGCSector *cursect; // for DDX
	CListBox *plbsect;
	/*CIGCBase *curaleph;  //
	CListBox *plbaleph;
	CIGCBase *curbase;   //
	CListBox *plbbase;
	CIGCRock *currock;   //
	CListBox *plbrock;*/
	void ChangeSector(void);
public:
	unsigned short last_sector_uid;
	unsigned short last_aleph_uid;
	unsigned short last_base_uid;
	unsigned short last_rock_uid;
	void SetSector(PtrSector);
	void LoadSectors();
	C2DMap map2d;
	CSectWnd sect2d;
	void OnSelchangeLbSectors(void);
	void Paint2dview(void);
	void NewSector(float, float);
	void CreateAleph(CIGCSector *,float ,float ,CIGCSector *,float ,float);
	void CreateAleph(CIGCSector *, CIGCSector *);

	void OnDblclkLbSectors(void);
	void OnClickedMapNew(void);
	void OnClickedMapLoad(void);
	void OnClickedMapSave(void);
	void OnClickedMapSaveas(void);
	void OnClickedMapQuit(void);
	int DiscardChanges(void);

	afx_msg HCURSOR OnQueryDragIcon(void);
	void OnClickedBDelallAlephs(void);
	void OnClickedBDelallBases(void);
	void OnClickedBDelallRocks(void);
protected:
	void OnOK(void);
	void OnCancel(void);
	CMenu tplmenu;
public:
	void OnClickedBRdallAlephs(void);
	void OnClickedBRdallRocks(void);
	void OnClickedGrid(void);
	void OnClickedSnap(void);
	void OnClickedBTemplates(void);
	afx_msg void OnSelTemplates(UINT);
	CIGCSector tplsector;
	CIGCAleph tplaleph;
	CRockTpl tplrock;
	int ra_p1;
	int ra_p2;
	int ra_p3;
	float ra_p4;
	float ra_p5;
	bool ra_b19;
	bool ra_b42;
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnBnClickedCkzview();
	afx_msg void OnBnClickedBRenameSectors();
	afx_msg void OnBnClickedCoreload();
	afx_msg void OnBnClickedAbout();
};

