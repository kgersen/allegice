#pragma once


// CGetNumDlg dialog

class CGetNumDlg : public CDialog
{
	DECLARE_DYNAMIC(CGetNumDlg)

public:
	CGetNumDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGetNumDlg();
	int value;
	CString caption;

// Dialog Data
	enum { IDD = IDD_GETNUMDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
