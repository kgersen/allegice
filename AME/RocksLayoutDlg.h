#pragma once


// CRocksLayoutDlg dialog

class CRocksLayoutDlg : public CDialog
{
	DECLARE_DYNAMIC(CRocksLayoutDlg)

public:
	CRocksLayoutDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRocksLayoutDlg();
	float cx,cy,cz;
	float radius;
	float varz;
	int nbrocks;

// Dialog Data
	enum { IDD = IDD_ROCKSLAYOUTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
