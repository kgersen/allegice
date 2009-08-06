// ProjectileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICE.h"
#include "corestruct.h"
#include "ProjectileDlg.h"


// CProjectileDlg dialog

IMPLEMENT_DYNAMIC(CProjectileDlg, CDialog)
CProjectileDlg::CProjectileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProjectileDlg::IDD, pParent)
{
	pprojectile = NULL;
	MainUI = NULL;
	sArtPath = "";
}

CProjectileDlg::~CProjectileDlg()
{
}

void CProjectileDlg::DoDataExchange(CDataExchange* pDX)
{
	int uid;
	CString file_texture, file_model;
	CString todo1 = "";
	if (!pprojectile) return;
	ASSERT(sArtPath != "");
	ASSERT(pcore != NULL);
	CListBox *clusage = (CListBox *)GetDlgItem(IDC_PROJWEPLIST);

	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		CString weplist = "";
		clusage->ResetContent();
		uid = pprojectile->projectileTypeID;
		file_texture = pprojectile->textureName;
		mdlbmp.LoadMDLFile(sArtPath +"\\"+ file_texture + "bmp.mdl");
		file_model = pprojectile->modelName;

		((CButton*)GetDlgItem(IDC_ABSSPEED))->SetCheck( pprojectile->absoluteF ? BST_CHECKED : BST_UNCHECKED);
		((CButton*)GetDlgItem(IDC_DIRECTIONNAL))->SetCheck( pprojectile->bDirectional ? BST_CHECKED : BST_UNCHECKED);

		CComboBox *cbdm = (CComboBox *)GetDlgItem(IDC_DM);
		cbdm->SetCurSel(pprojectile->damageType);

		// display weapon that use this projectil
		for (int j=0;j<pcore->cl_Parts.GetSize();j++)
		{
			PtrCorePart ppart = pcore->cl_Parts.GetAt(j);
			if ((ppart->type == ET_Weapon) && (!ppart->isspec))
			{
				if (ppart->specs.wep.wep_projectile_uid == uid)
				{
					weplist.Format("%s (%d)\r\n",ppart->name,ppart->uid);
					int idx = clusage->AddString(weplist);
					clusage->SetItemDataPtr(idx,ppart);
				}
			}
		}
		for (int j=0;j<pcore->cl_Probes.GetSize();j++)
		{
			PtrCoreProbe pprobe = pcore->cl_Probes.GetAt(j);
			if (pprobe->stats_projectile == uid)
			{
					weplist.Format("%s (%d)\r\n",pprobe->name,pprobe->uid);
					int idx = clusage->AddString(weplist);
					clusage->SetItemDataPtr(idx,pprobe);
			}
		}

	}
	DDX_Text(pDX, IDC_UID, uid);
	DDX_Text(pDX, IDC_TEXTURE, file_texture);
	DDX_Text(pDX, IDC_MODEL, file_model);
	DDX_Text(pDX, IDC_S1, pprojectile->radius);
	DDX_Text(pDX, IDC_S2, pprojectile->rotation);
	DDX_Text(pDX, IDC_S3, pprojectile->power);
	DDX_Text(pDX, IDC_S4, pprojectile->blastPower);
	DDX_Text(pDX, IDC_S5, pprojectile->blastRadius);
	DDX_Text(pDX, IDC_S6, pprojectile->speed);
	DDX_Text(pDX, IDC_S7, pprojectile->lifespan);
	DDX_Text(pDX, IDC_S8, pprojectile->width);

	DDX_Text(pDX, IDC_REDP, pprojectile->color.r);
	DDX_Text(pDX, IDC_GREENP, pprojectile->color.g);
	DDX_Text(pDX, IDC_BLUEP, pprojectile->color.b);
	DDX_Text(pDX, IDC_ALPHAP, pprojectile->color.a);

	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		strcpy(pprojectile->textureName,file_texture);
		strcpy(pprojectile->modelName,file_model);
		pprojectile->absoluteF = (((CButton*)GetDlgItem(IDC_ABSSPEED))->GetCheck()) == BST_CHECKED;
		pprojectile->bDirectional = (((CButton*)GetDlgItem(IDC_DIRECTIONNAL))->GetCheck()) == BST_CHECKED;
		CComboBox *cbdm = (CComboBox *)GetDlgItem(IDC_DM);
		pprojectile->damageType = cbdm->GetCurSel();

	}
	CDialog::DoDataExchange(pDX);
}

void CProjectileDlg::OnClickedDecodesel(void)
{
	CEdit *cetodo = (CEdit *) CWnd::GetDlgItem(IDC_TODO1);
	int i,j;
	cetodo->GetSel(i,j);

	// NT SPECIFIC
   HLOCAL h = cetodo->GetHandle();
   LPCTSTR lpszText = (LPCTSTR)LocalLock(h);
	char res[1000];
	strncpy(res,&(lpszText[i]),j-i);
	SetDlgItemText(IDC_DECDEC,res);
	float f;
	unsigned char *pf;
	unsigned int b1,b2,b3,b4;
	pf = (unsigned char *)&f;
	sscanf(res,"%x %x %x %x",&b1,&b2,&b3,&b4);
	pf[0] = b1;
	pf[1] = b2;
	pf[2] = b3;
	pf[3] = b4;
	CString sres;
	sres.Format("%g",f);
	SetDlgItemText(IDC_DECFLOAT,sres);
	
   LocalUnlock(h);
}

void CProjectileDlg::OnClickedDecodeh(void)
{
	CEdit *cetodo = (CEdit *) CWnd::GetDlgItem(IDC_TODO1);
	int i,j;
	cetodo->GetSel(i,j);

	// NT SPECIFIC
   HLOCAL h = cetodo->GetHandle();
   LPCTSTR lpszText = (LPCTSTR)LocalLock(h);
	char res[1000];
	strncpy(res,&(lpszText[i]),j-i);
	SetDlgItemText(IDC_DECDEC,res);
	unsigned short f;
	unsigned char *pf;
	unsigned int b1,b2;
	pf = (unsigned char *)&f;
	sscanf(res,"%x %x",&b1,&b2);
	pf[0] = b1;
	pf[1] = b2;
	CString sres;
	sres.Format("%04X = %d",f,f);
	SetDlgItemText(IDC_DECFLOAT,sres);
	
   LocalUnlock(h);
	// END OF NT SPECIFIC
}

BOOL CProjectileDlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	VERIFY(mdlbmp.SubclassDlgItem(IDC_PICT, this));

	CComboBox *cbdm = (CComboBox *)GetDlgItem(IDC_DM);
	cbdm->ResetContent();
	for (int i=0;i<IGCDMMAX;i++)
	{
		CString s;
		s.Format("DM%02d",i);
		cbdm->AddString(s);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CProjectileDlg::OnClickedOk(void)
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}

void CProjectileDlg::OnClickedCancel(void)
{
	UpdateData(FALSE);
}


BEGIN_MESSAGE_MAP(CProjectileDlg, CDialog)
	ON_BN_CLICKED(IDC_DECODESEL, OnClickedDecodesel)
	ON_BN_CLICKED(IDC_DECODEH, OnClickedDecodeh)
	ON_BN_CLICKED(IDOK, OnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnClickedCancel)
	ON_LBN_SELCHANGE(IDC_PROJWEPLIST, &CProjectileDlg::OnLbnSelchangeProjweplist)
END_MESSAGE_MAP()


// CProjectileDlg message handlers

void CProjectileDlg::OnLbnSelchangeProjweplist()
{
	CListBox *clusage = (CListBox *)GetDlgItem(IDC_PROJWEPLIST);
	int idx = clusage->GetCurSel();
	if (idx == -1) return;
	MainUI->SelectPCE((LPARAM)clusage->GetItemDataPtr(idx));
}
