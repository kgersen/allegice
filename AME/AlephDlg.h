#pragma once


// CAlephDlg dialog

class CAlephDlg : public CDialog
{
	DECLARE_DYNAMIC(CAlephDlg)

public:
	CAlephDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAlephDlg();
public:
	CIGCAleph *curaleph;
	bool bTplMode;
	CString sArtPath;

// Dialog Data
	enum { IDD = IDD_ALEPHDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog(void);
	void SetSpinCheck(void);
	void SetAutoCheck(void);
	CBMPMDLButton IconBmp;
	DECLARE_MESSAGE_MAP()

	
public:
	void OnClickedDelete(void);
	void OnClickedApplytosect(void);
	void OnClickedApplytoall(void);
	afx_msg void OnBnClickedAIconbmp();
};
