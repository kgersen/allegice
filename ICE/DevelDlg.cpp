// DevelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICE.h"
#include "corestruct.h"
#include "DevelDlg.h"


// CDevelDlg dialog

IMPLEMENT_DYNAMIC(CDevelDlg, CDialog)
CDevelDlg::CDevelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDevelDlg::IDD, pParent)
{
	pdevel = NULL;
	sArtPath = "";
}

CDevelDlg::~CDevelDlg()
{
}

void CDevelDlg::DoDataExchange(CDataExchange* pDX)
{
	CString name,model,descr;
	int rtime;
	if (!pdevel) return;
	ASSERT(sArtPath != "");
	int uid = pdevel->developmentID;
	CString	obj = pdevel->iconName;
	CComboBox *cb = (CComboBox *) GetDlgItem(IDC_DEVELPATH);

	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		name = pdevel->name;
		model = pdevel->modelName;
		mdlbmp.LoadMDLFile(sArtPath + "\\i" + pdevel->modelName +"bmp.mdl");
		rtime = pdevel->timeToBuild;
		descr = pdevel->description; 
		cb->SetCurSel(pdevel->groupID);
	}
	DDX_Text(pDX, IDC_UID, uid);
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_MODEL, model);
	DDX_Text(pDX, IDC_OBJ, obj);
	DDX_Text(pDX, IDC_RTIME, rtime);
	DDX_Text(pDX, IDC_COST, pdevel->price);
	DDX_Text(pDX, IDC_CSOUND, pdevel->completionSound);
	DDX_Text(pDX, IDC_DESCRIPTION, descr);
	for (int i=0;i<c_gaMax;i++) //TODO: add a DDX_GA ?
	{
		float ga;
		if (!pDX->m_bSaveAndValidate) ga = pdevel->gas.GetAttribute(i);
		DDX_Text(pDX, IDC_FACTOR0+i, ga);
		if (pDX->m_bSaveAndValidate) pdevel->gas.SetAttribute(i,ga);
	}

	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		strcpy(pdevel->name,name);
		strcpy(pdevel->modelName,model);

		strncpy(pdevel->description,descr,IGC_DESCRIPTIONMAX);
		if (cb->GetCurSel() != CB_ERR)
			pdevel->groupID = (UCHAR)cb->GetCurSel();
	}
	CDialog::DoDataExchange(pDX);
}

BOOL CDevelDlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();
	VERIFY(mdlbmp.SubclassDlgItem(IDC_PICT, this));
	CComboBox *cb = (CComboBox *) GetDlgItem(IDC_DEVELPATH);
	cb->ResetContent();
	for (int j=0;j<MAXPATHS;j++)
	{
		cb->AddString(sPathsNames[j]);
	}

	((CEdit *)GetDlgItem(IDC_DESCRIPTION))->SetLimitText(IGC_DESCRIPTIONMAX);
	((CEdit *)GetDlgItem(IDC_NAME))->SetLimitText(IGC_NAMEMAX);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDevelDlg::OnClickedOk(void)
{
	CString oldname = pdevel->name;
	BuyableGroupID oldroot = pdevel->groupID;
	UpdateData(TRUE);
	CString newname = pdevel->name;
	BuyableGroupID newroot = pdevel->groupID;
	if ((oldname != newname) || (oldroot != newroot))
		GetParent()->UpdateData(TRUE);
	UpdateData(FALSE);
}

void CDevelDlg::OnClickedCancel(void)
{
	UpdateData(FALSE);
}


BEGIN_MESSAGE_MAP(CDevelDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnClickedCancel)
	ON_BN_CLICKED(IDC_BEDITDESCR, &CDevelDlg::OnBnClickedBeditdescr)
END_MESSAGE_MAP()


// CDevelDlg message handlers

void CDevelDlg::OnBnClickedBeditdescr()
{
	CDescrDlg dlg(pdevel->description);
	if (dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_DESCRIPTION,pdevel->description);
}
