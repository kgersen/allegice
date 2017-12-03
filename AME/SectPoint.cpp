// SectPoint.cpp : implementation file
//

#include "stdafx.h"
#include "AGM.h"
#include "IGCMap.h"
#include "SectDlg.h"
#include "SectPoint.h"


// CSectPoint

IMPLEMENT_DYNAMIC(CSectPoint, CWnd)
CSectPoint::CSectPoint(CIGCSect *psector)
{
}

CSectPoint::~CSectPoint()
{
}

void CSectPoint::OnPaint(void)
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
}

void CSectPoint::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

}

void CSectPoint::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonDown(nFlags, point);
}


BEGIN_MESSAGE_MAP(CSectPoint, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CSectPoint message handlers

