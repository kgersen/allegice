#pragma once


// CRockTplDlg dialog

class CRockTplDlg : public CDialog
{
	DECLARE_DYNAMIC(CRockTplDlg)

public:
	CRockTplDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRockTplDlg();
	CRockTpl rocktpl;
// Dialog Data
	enum { IDD = IDD_ROCKTPLDLG };

protected:
	int iCurTab;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog(void);
	void SetRadiusCheck(void);
	void SetSigCheck(void);
	void SetHPCheck(void);
	void OnSelchangeTabRocks(NMHDR *pNMHDR, LRESULT *pResult);
	void OnSelchangingTabRocks(NMHDR *pNMHDR, LRESULT *pResult);
	void OnClickedApplytosect(void);
	void OnClickedApplytoall(void);
};
