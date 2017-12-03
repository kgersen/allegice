#pragma once


// CSectPoint

class CSectPoint : public CWnd
{
	DECLARE_DYNAMIC(CSectPoint)

public:
	CSectPoint(CIGCSector *);
	virtual ~CSectPoint();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint(void);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
protected:
	CIGCSector *cursect;
};


