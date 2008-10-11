#pragma once


// CMDLView dialog

class CMDLView : public CDialog
{
	DECLARE_DYNAMIC(CMDLView)

public:
	CMDLView(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMDLView();
	CString sModel;
	CString sArtPath;
	CBMPMDLButton mdlbmp;
// Dialog Data
	enum { IDD = IDD_MDLVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog(void);
	afx_msg void OnBnClickedDecodeh();
	afx_msg void OnBnClickedDecodesel();
protected:
	UCHAR *rawdata;
	UINT rawsize;
};
