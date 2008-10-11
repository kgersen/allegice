#pragma once


// CBMPMDLButton

class CBMPMDLButton : public CBitmapButton
{
	DECLARE_DYNAMIC(CBMPMDLButton)

public:
CBMPMDLButton();
	virtual ~CBMPMDLButton();
protected:
	DECLARE_MESSAGE_MAP()
public:
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void LoadMDLFile(CString sMDLPath);
};


