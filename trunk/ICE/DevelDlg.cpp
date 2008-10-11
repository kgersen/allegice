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
	int rtime,cost,cat;
	if (!pdevel) return;
	ASSERT(sArtPath != "");
	int uid = pdevel->uid;
	CString	obj = pdevel->icon;
	CComboBox *cb = (CComboBox *) GetDlgItem(IDC_DEVELPATH);

	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		name = pdevel->name;
		model = pdevel->model;
		mdlbmp.LoadMDLFile(sArtPath + "\\i" + pdevel->model +"bmp.mdl");
		rtime = pdevel->research_time;
		cost = pdevel->cost;
		descr = pdevel->description; 
		cat = pdevel->cat;
		cb->SetCurSel(pdevel->root_tree);
	}
	DDX_Text(pDX, IDC_UID, uid);
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_MODEL, model);
	DDX_Text(pDX, IDC_OBJ, obj);
	DDX_Text(pDX, IDC_RTIME, rtime);
	DDX_Text(pDX, IDC_COST, cost);
	DDX_Text(pDX, IDC_CAT, cat);
	DDX_Text(pDX, IDC_DESCRIPTION, descr);
	for (int i=0;i<25;i++)
		DDX_Text(pDX, IDC_FACTOR0+i, pdevel->factors[i]);
	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		strcpy(pdevel->name,name);
		strcpy(pdevel->model,model);
		pdevel->research_time = rtime;
		pdevel->cost = cost;
		pdevel->cat = cat;
		strncpy(pdevel->description,descr,IGC_DESCRIPTIONMAX);
		if (cb->GetCurSel() != CB_ERR)
			pdevel->root_tree = (UCHAR)cb->GetCurSel();
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
	UCHAR oldroot = pdevel->root_tree;
	UpdateData(TRUE);
	CString newname = pdevel->name;
	UCHAR newroot = pdevel->root_tree;
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
END_MESSAGE_MAP()


// CDevelDlg message handlers
