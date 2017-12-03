// ColorButton.cpp : implementation file
//

#include "stdafx.h"
#include "mapstruct.h"
#include "ColorButton.h"



void CColorButton::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
	// all items are of fixed size
	// must use LBS_OWNERDRAWVARIABLE for this to work
	lpMIS->itemHeight = 20;
	lpMIS->itemWidth  = 40;
}

void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);

	CBrush br(color);
	pDC->FillRect(&lpDIS->rcItem, &br);

//		pDC->FrameRect(&lpDIS->rcItem, &br);
}

void CColorButton::ChangeColor(void)
{
	CColorDialog dlg(color, CC_FULLOPEN);
	if (dlg.DoModal() == IDOK)
	{
		color = dlg.GetColor();
		Invalidate(FALSE);
	}
}
void CColorButton::ChangeColor(BYTE red, BYTE green, BYTE blue)
{
		color = RGB(red,green,blue);
		Invalidate(FALSE);
}
Srgbval CColorButton::toIGCColor(void)
{
	Srgbval rgb;
	rgb.red   = GetRValue(color);
	rgb.green = GetGValue(color);
	rgb.blue  = GetBValue(color);
	return rgb;
}