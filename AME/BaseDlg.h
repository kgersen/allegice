#pragma once


// CBaseDlg dialog

class CBaseDlg : public CDialog
{
	DECLARE_DYNAMIC(CBaseDlg)

public:
	CBaseDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBaseDlg();
public:
	CIGCBase *curbase;
	PtrCore pcore;
// Dialog Data
	enum { IDD = IDD_BASEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog(void);
	afx_msg void OnBaseChange( UINT nID );
	void OnClickedDelete(void);
	void OnClickedBaseSettype(void);
};
