#pragma once


// CColorButton

class CColorButton : public CButton
{
public:
	COLORREF color;
	virtual void DrawItem(LPDRAWITEMSTRUCT) ;
	virtual void MeasureItem(LPMEASUREITEMSTRUCT);
	void ChangeColor(void);
	void ChangeColor(BYTE, BYTE, BYTE);
	Srgbval toIGCColor(void);
};


