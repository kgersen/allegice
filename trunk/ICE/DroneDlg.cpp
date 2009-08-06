// DroneDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICE.h"
#include "corestruct.h"
#include "DroneDlg.h"
#include ".\dronedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CDroneDlg dialog

IMPLEMENT_DYNAMIC(CDroneDlg, CDialog)
CDroneDlg::CDroneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDroneDlg::IDD, pParent)
{
	pdrone = NULL;
	pcore = NULL;
	MainUI = NULL;
	sArtPath = "";
}

CDroneDlg::~CDroneDlg()
{
}

void CDroneDlg::DoDataExchange(CDataExchange* pDX)
{
	CString name,model,icon,description;
	int shipuid,ss1,partuid;
	if (!pdrone) return;
	ASSERT(sArtPath != "");

	int uid = pdrone->droneTypeID;
	CComboBox *cb = (CComboBox *) GetDlgItem(IDC_DEVELPATH);
	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		name = pdrone->name;
		model = pdrone->modelName;
		mdlbmp.LoadMDLFile(sArtPath + "\\i" + pdrone->modelName + "bmp.mdl");
		icon = pdrone->iconName;
		description = pdrone->description;
		shipuid = pdrone->hullTypeID;
		ss1 = pdrone->pilotType;
		partuid = pdrone->etidLaid;
		cb->SetCurSel(pdrone->groupID);
	}
	DDX_Text(pDX, IDC_COST, pdrone->price);
	DDX_Text(pDX, IDC_RTIME, pdrone->timeToBuild);

	DDX_Text(pDX, IDC_S1, pdrone->shootSkill);
	DDX_Text(pDX, IDC_S2, pdrone->moveSkill);
	DDX_Text(pDX, IDC_S3, pdrone->bravery);

	DDX_Text(pDX, IDC_UID, uid);
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_MODEL, model);
	DDX_Text(pDX, IDC_ICONNAME, icon);
	DDX_Text(pDX, IDC_DESCRIPTION, description);
	DDX_Text(pDX, IDC_SHIPUID, shipuid);
	DDX_Text(pDX, IDC_BUILDUID, partuid);
	DDX_Text(pDX, IDC_SS1, ss1);

	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		strcpy(pdrone->name,name);
		strcpy(pdrone->modelName,model);
		strcpy(pdrone->iconName,icon);
		strncpy(pdrone->description,description,IGC_DESCRIPTIONMAX);
		pdrone->hullTypeID = shipuid;
		pdrone->pilotType = ss1;
		pdrone->etidLaid = partuid;
		if (cb->GetCurSel() != CB_ERR)
			pdrone->groupID = (UCHAR)cb->GetCurSel();
	}
	CDialog::DoDataExchange(pDX);
}

void CDroneDlg::OnClickedOk(void)
{
	CString oldname = pdrone->name;
	UpdateData(TRUE);
	CString newname = pdrone->name;
	if (oldname != newname)
		GetParent()->UpdateData(TRUE);
	UpdateData(FALSE);
}

void CDroneDlg::OnClickedCancel(void)
{
	UpdateData(FALSE);
}


BEGIN_MESSAGE_MAP(CDroneDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnClickedCancel)
	ON_BN_CLICKED(IDC_BSHIPID, &CDroneDlg::OnBnClickedBshipid)
	ON_BN_CLICKED(IDC_BPARTID, &CDroneDlg::OnBnClickedBpartid)
	ON_BN_CLICKED(IDC_BEDITDESCR, &CDroneDlg::OnBnClickedBeditdescr)
END_MESSAGE_MAP()


// CDroneDlg message handlers

BOOL CDroneDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	VERIFY(mdlbmp.SubclassDlgItem(IDC_PICT, this));

	((CEdit *)GetDlgItem(IDC_DESCRIPTION))->SetLimitText(IGC_DESCRIPTIONMAX);
	((CEdit *)GetDlgItem(IDC_NAME))->SetLimitText(IGC_NAMEMAX);

	CComboBox *cb = (CComboBox *) GetDlgItem(IDC_DEVELPATH);
	cb->ResetContent();
	for (int j=0;j<MAXPATHS;j++)
	{
		cb->AddString(sPathsNames[j]);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDroneDlg::SetIcons(HICON iJumpIcon)
{
	((CButton *)GetDlgItem(IDC_BSHIPID))->SetIcon(iJumpIcon);
	((CButton *)GetDlgItem(IDC_BPARTID))->SetIcon(iJumpIcon);
}

void CDroneDlg::OnBnClickedBshipid()
{
	if (!pdrone) return;
	if (!pcore) return;
	if (!MainUI) return;

	LPARAM p = (LPARAM)pcore->FindShip(pdrone->hullTypeID);
	if (p)
		MainUI->SelectPCE(p);}

void CDroneDlg::OnBnClickedBpartid()
{
	if (!pdrone) return;
	if (!pcore) return;
	if (!MainUI) return;
	if (pdrone->etidLaid==-1) return;
	PtrCoreEntry pce = pcore->ProxyPart(pdrone->etidLaid);
	if (!pce) AfxMessageBox("can't find this part");
	LPARAM p = pce->entry;
	delete pce;
	if (p)
		MainUI->SelectPCE(p);
}

void CDroneDlg::OnBnClickedBeditdescr()
{
	CDescrDlg dlg(pdrone->description);
	if (dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_DESCRIPTION,pdrone->description);
}
