#pragma once


// CRockDlg dialog

class CRockDlg : public CDialog
{
	DECLARE_DYNAMIC(CRockDlg)

public:
	CRockDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRockDlg();

// Dialog Data
	enum { IDD = IDD_ROCKDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CIGCRock *currock;
	CString cArtPath;
	PtrCore pcore;
	BOOL OnInitDialog(void);
	void SetFlags(unsigned short);
	void ShowHeVals(bool);
	void OnSelchangeRockRender(void);
	void OnSelchangeRockTemplate(void);
	void OnClickF1(void);
	void OnClickPhantom(void);
	//afx_msg void OnCbnSelchangeRockRenderCustom();
};
