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
	int ss1,ss2;
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
		uid = pprojectile->uid;
		file_texture = pprojectile->file_texture;
		mdlbmp.LoadMDLFile(sArtPath +"\\"+ file_texture + "bmp.mdl");
		file_model = pprojectile->file_model;
		ss1 = pprojectile->stats_ss1;
		ss2 = pprojectile->stats_ss2;
		CComboBox *cbdm = (CComboBox *)GetDlgItem(IDC_DM);
		cbdm->SetCurSel(pprojectile->DM);

		// display weapon that use this projectil
		for (int j=0;j<pcore->cl_Parts.GetSize();j++)
		{
			PtrCorePart ppart = pcore->cl_Parts.GetAt(j);
			if ((ppart->type == AGCEquipmentType_Weapon) && (!ppart->isspec))
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
	//DDX_Text(pDX, IDC_TODO1, todo1);
	DDX_Text(pDX, IDC_UID, uid);
	DDX_Text(pDX, IDC_TEXTURE, file_texture);
	DDX_Text(pDX, IDC_MODEL, file_model);
	DDX_Text(pDX, IDC_S1, pprojectile->stats_s1);
	DDX_Text(pDX, IDC_S2, pprojectile->stats_s2);
	DDX_Text(pDX, IDC_S3, pprojectile->stats_s3);
	DDX_Text(pDX, IDC_S4, pprojectile->stats_s4);
	DDX_Text(pDX, IDC_S5, pprojectile->stats_s5);
	DDX_Text(pDX, IDC_S6, pprojectile->stats_s6);
	DDX_Text(pDX, IDC_S7, pprojectile->stats_s7);
	DDX_Text(pDX, IDC_S8, pprojectile->stats_s8);

	DDX_Text(pDX, IDC_REDP, pprojectile->percentRed);
	DDX_Text(pDX, IDC_GREENP, pprojectile->percentGreen);
	DDX_Text(pDX, IDC_BLUEP, pprojectile->percentBlue);
	DDX_Text(pDX, IDC_ALPHAP, pprojectile->percentAlpha);

	DDX_Text(pDX, IDC_SS1, ss1);
	DDX_Text(pDX, IDC_SS2, ss2);
	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		strcpy(pprojectile->file_texture,file_texture);
		strcpy(pprojectile->file_model,file_model);
		pprojectile->stats_ss1 = ss1;
		pprojectile->stats_ss2 = ss2;
		CComboBox *cbdm = (CComboBox *)GetDlgItem(IDC_DM);
		pprojectile->DM = cbdm->GetCurSel();

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
