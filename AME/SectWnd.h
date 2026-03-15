#pragma once


// CSectWnd

class CSectWnd : public CWnd
{
	DECLARE_DYNAMIC(CSectWnd)

public:
CSectWnd();
	virtual ~CSectWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint(void);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	CIGCMap *cigcmap;
	CString cArtPath;
	int bShowZ;
	void ChangeSector(CIGCSector *);
	void DeleteAllBases(void);
	void DeleteAllRocks(void);
protected:
	PtrObject ClipBoard;
	CMenu rmenu;
	CMenu rmenu_rocks;
	CMenu alephmenu;
	CMenu basemenu;
	CMenu rockmenu;
	CMenu *ObjectMenu(PtrObject);
	CIGCSector *cursect;
	CList<PtrAleph,PtrAleph&> cl_palephs;
	CList<PtrBase,PtrBase&> cl_pbases;
	CList<PtrRock,PtrRock&> cl_procks;
	PtrObject IsOverObject(CPoint);
	PtrObject dragobject;
	PtrObject menuobject;
	CPoint dragpoint; // used to drag and to store rightmenu
	float dragZ;
	bool bSettingZ;
	bool bMakingAleph;
	LONG AlephX,AlephY;
	LONG AlephDestX,AlephDestY;
	void DrawGrid(CPaintDC *);
	bool grid_on;
	void ObjProps(PtrObject);
	void ObjDelete(PtrObject);
	SectorInfos sectinfo;
	CFont fontsm;
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void AllUpdate(void);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRMenu( UINT nID );
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};


