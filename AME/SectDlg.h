
#pragma once


// CSectDlg dialog

class CSectDlg : public CDialog
{
	DECLARE_DYNAMIC(CSectDlg)

public:
	CSectDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSectDlg();

// Dialog Data
	enum { IDD = IDD_SECTDLG };
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
protected:
	CColorButton LightColor;
	CBMPMDLButton PlanetBmp;

public:
	CIGCSector *cursect;
	CString sArtPath;
	bool bTplMode;

protected:
	void OnClickedSectLightColor(void);
	void OnClickedMapSApply(void);
	void OnClickedMapSDelete(void);
public:
	void OnClickedSdlgCancel(void);
	afx_msg void OnCbnSelchangeSectNebbg();
	afx_msg void OnCbnSelchangeSectGlobe();
};

#define S_SECTOR_DELETE ((HRESULT)0x00000005L)
#define S_SECTOR_CANCEL ((HRESULT)0x00000006L)