#pragma once

typedef struct SMapAleph
{
	CIGCSector *sect1;
	CIGCAleph  *aleph1;
	CIGCSector *sect2;
	CIGCAleph  *aleph2;
} MapAleph;
// C2DMap


class C2DMap : public CWnd
{
	DECLARE_DYNAMIC(C2DMap)
public:
C2DMap();
	virtual ~C2DMap();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint(void);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
protected:
	float maxx;
	float maxy;
	float maxc;
	void Rescale();
	float Snap(float);
	CIGCSector *C2DMap::IsOverSector(CPoint);
	CIGCSector *dragsector;
	CIGCSector *createaleph;
	CPoint createalephTOpos2D;
	CPoint dragpoint;
	CPoint dragorigin;
	bool bGrid;
	bool bSnap;
	CString sDispSectName;
public:
	CIGCMap *igcmap;
	CIGCSector *igccursect;
	CList<SMapAleph,SMapAleph&> mapalephs;
	bool KnownAleph(CIGCAleph *);
	CIGCSector *FindSector(CIGCAleph *);
	CIGCAleph *FindConnectingAleph(CIGCAleph *);
	void RenameAlephs(CIGCSector *);
	void DeleteAleph(CIGCAleph *);
	void BuildMapTables(void);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	static 	const int MapW = W2DMAP;
	static const int MapH = H2DMAP;
	void SetGrid(bool);
	void SetSnap(bool);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

