#pragma once


// CTreasureDlg dialog

class CTreasureDlg : public CDialog
{
	DECLARE_DYNAMIC(CTreasureDlg)

public:
	CTreasureDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTreasureDlg();
	PtrCoreTreasureSet ptres;
	PtrCore pcore;

// Dialog Data
	enum { IDD = IDD_TREASUREDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CListBox *clParts;
	CListBox *clTres;
	void BuildPL();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeTreslist();
	afx_msg void OnBnClickedBttotres();
	afx_msg void OnBnClickedBttopart();
	afx_msg void OnBnClickedAddcash();
	afx_msg void OnBnClickedAddpwup();
	afx_msg void OnBnClickedSetchance();
};
