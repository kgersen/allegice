#pragma once


// CDevelDlg dialog

class CDevelDlg : public CDialog
{
	DECLARE_DYNAMIC(CDevelDlg)

public:
	CDevelDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDevelDlg();
	PtrCoreDevel pdevel;
	CString sArtPath;
	CBMPMDLButton mdlbmp;
// Dialog Data
	enum { IDD = IDD_DEVELDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog(void);
	void OnClickedOk(void);
	void OnClickedCancel(void);
};
