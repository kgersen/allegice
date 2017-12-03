#pragma once


// CRandomDlg dialog

class CRandomDlg : public CDialog
{
	DECLARE_DYNAMIC(CRandomDlg)

public:
	CRandomDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRandomDlg();
	int ra_p1;
	int ra_p2;
	int ra_p3;
	float ra_p4;
	float ra_p5;
	int ra_b19;
	int ra_b42;

// Dialog Data
	enum { IDD = IDD_RANDOMDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void SetDefaults();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDefs();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCkb19();
	afx_msg void OnBnClickedCkb42();
};
