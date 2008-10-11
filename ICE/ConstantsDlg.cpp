// ConstantsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICE.h"
#include "corestruct.h"
#include "ConstantsDlg.h"


// CConstantsDlg dialog

IMPLEMENT_DYNAMIC(CConstantsDlg, CDialog)
CConstantsDlg::CConstantsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConstantsDlg::IDD, pParent)
{
	pconst = NULL;
	pcore = NULL;
	bIniChanged = true;
	bShowAC = false;
}

CConstantsDlg::~CConstantsDlg()
{
}

void CConstantsDlg::DoDataExchange(CDataExchange* pDX)
{
	if (pconst == NULL) return;
	if (pcore == NULL) return;
	CComboBox *cbdm = (CComboBox *)GetDlgItem(IDC_DM);
	int idx = cbdm->GetCurSel();
	

	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		if (!bShowAC) 
			FillDMUsage(idx);
		else
			FillACUsage(idx);
	}
	int i = 0;
	if (idx != CB_ERR)
	{
		if (!bShowAC)
		{
			DDX_Text(pDX, IDC_S1, pconst->damages[idx][i++]);
			DDX_Text(pDX, IDC_S2, pconst->damages[idx][i++]);
			DDX_Text(pDX, IDC_S3, pconst->damages[idx][i++]);
			DDX_Text(pDX, IDC_S4, pconst->damages[idx][i++]);
			DDX_Text(pDX, IDC_S5, pconst->damages[idx][i++]);
			DDX_Text(pDX, IDC_S6, pconst->damages[idx][i++]);
			DDX_Text(pDX, IDC_S7, pconst->damages[idx][i++]);
			DDX_Text(pDX, IDC_S8, pconst->damages[idx][i++]);
			DDX_Text(pDX, IDC_S9, pconst->damages[idx][i++]);
			DDX_Text(pDX, IDC_S10, pconst->damages[idx][i++]);
			DDX_Text(pDX, IDC_S11, pconst->damages[idx][i++]);
			DDX_Text(pDX, IDC_S12, pconst->damages[idx][i++]);
			DDX_Text(pDX, IDC_S13, pconst->damages[idx][i++]);
			DDX_Text(pDX, IDC_S14, pconst->damages[idx][i++]);
			DDX_Text(pDX, IDC_S15, pconst->damages[idx][i++]);
			DDX_Text(pDX, IDC_S16, pconst->damages[idx][i++]);
			DDX_Text(pDX, IDC_S17, pconst->damages[idx][i++]);
			DDX_Text(pDX, IDC_S18, pconst->damages[idx][i++]);
			DDX_Text(pDX, IDC_S19, pconst->damages[idx][i++]);
			DDX_Text(pDX, IDC_S20, pconst->damages[idx][i++]);
		}
		else
		{
			DDX_Text(pDX, IDC_S1, pconst->damages[i++][idx]);
			DDX_Text(pDX, IDC_S2, pconst->damages[i++][idx]);
			DDX_Text(pDX, IDC_S3, pconst->damages[i++][idx]);
			DDX_Text(pDX, IDC_S4, pconst->damages[i++][idx]);
			DDX_Text(pDX, IDC_S5, pconst->damages[i++][idx]);
			DDX_Text(pDX, IDC_S6, pconst->damages[i++][idx]);
			DDX_Text(pDX, IDC_S7, pconst->damages[i++][idx]);
			DDX_Text(pDX, IDC_S8, pconst->damages[i++][idx]);
			DDX_Text(pDX, IDC_S9, pconst->damages[i++][idx]);
			DDX_Text(pDX, IDC_S10, pconst->damages[i++][idx]);
			DDX_Text(pDX, IDC_S11, pconst->damages[i++][idx]);
			DDX_Text(pDX, IDC_S12, pconst->damages[i++][idx]);
			DDX_Text(pDX, IDC_S13, pconst->damages[i++][idx]);
			DDX_Text(pDX, IDC_S14, pconst->damages[i++][idx]);
			DDX_Text(pDX, IDC_S15, pconst->damages[i++][idx]);
			DDX_Text(pDX, IDC_S16, pconst->damages[i++][idx]);
			DDX_Text(pDX, IDC_S17, pconst->damages[i++][idx]);
			DDX_Text(pDX, IDC_S18, pconst->damages[i++][idx]);
			DDX_Text(pDX, IDC_S19, pconst->damages[i++][idx]);
			DDX_Text(pDX, IDC_S20, pconst->damages[i++][idx]);
		}
	}
	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		CListBox *cbglobals = (CListBox *)GetDlgItem(IDC_GLOBALLIST);
		int idx = cbglobals->GetCurSel();
		if (idx != CB_ERR)
		{
			DDX_Text(pDX, IDC_GLOBALVAL, pcore->pConstants->constants[idx]);
			CString lab;
			GetDlgItemText(IDC_GLOBALLAB,lab);
			if (lab != ConstLabs[idx])
			{
				ConstLabs[idx] = lab;
				BuildConstList(idx);
				bIniChanged = true;
			}
		}
	}
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConstantsDlg, CDialog)
ON_CBN_SELCHANGE(IDC_DM, OnCbnSelchangeDm)
ON_BN_CLICKED(IDOK, OnBnClickedOk)
ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
ON_LBN_SELCHANGE(IDC_GLOBALLIST, OnLbnSelchangeGloballist)
ON_BN_CLICKED(IDC_GLOBALSET, OnBnClickedGlobalset)
ON_LBN_SELCHANGE(IDC_DMUSAGE, &CConstantsDlg::OnLbnSelchangeDmusage)
ON_BN_CLICKED(IDC_BSWTICH, &CConstantsDlg::OnBnClickedBswtich)
ON_EN_SETFOCUS(IDC_S1, &CConstantsDlg::OnEnSetfocusS1)
ON_EN_SETFOCUS(IDC_S2, &CConstantsDlg::OnEnSetfocusS2)
ON_EN_SETFOCUS(IDC_S3, &CConstantsDlg::OnEnSetfocusS3)
ON_EN_SETFOCUS(IDC_S4, &CConstantsDlg::OnEnSetfocusS4)
ON_EN_SETFOCUS(IDC_S5, &CConstantsDlg::OnEnSetfocusS5)
ON_EN_SETFOCUS(IDC_S6, &CConstantsDlg::OnEnSetfocusS6)
ON_EN_SETFOCUS(IDC_S7, &CConstantsDlg::OnEnSetfocusS7)
ON_EN_SETFOCUS(IDC_S8, &CConstantsDlg::OnEnSetfocusS8)
ON_EN_SETFOCUS(IDC_S9, &CConstantsDlg::OnEnSetfocusS9)
ON_EN_SETFOCUS(IDC_S10, &CConstantsDlg::OnEnSetfocusS10)
ON_EN_SETFOCUS(IDC_S11, &CConstantsDlg::OnEnSetfocusS11)
ON_EN_SETFOCUS(IDC_S12, &CConstantsDlg::OnEnSetfocusS12)
ON_EN_SETFOCUS(IDC_S13, &CConstantsDlg::OnEnSetfocusS13)
ON_EN_SETFOCUS(IDC_S14, &CConstantsDlg::OnEnSetfocusS14)
ON_EN_SETFOCUS(IDC_S15, &CConstantsDlg::OnEnSetfocusS15)
ON_EN_SETFOCUS(IDC_S16, &CConstantsDlg::OnEnSetfocusS16)
ON_EN_SETFOCUS(IDC_S17, &CConstantsDlg::OnEnSetfocusS17)
ON_EN_SETFOCUS(IDC_S18, &CConstantsDlg::OnEnSetfocusS18)
ON_EN_SETFOCUS(IDC_S19, &CConstantsDlg::OnEnSetfocusS19)
ON_EN_SETFOCUS(IDC_S20, &CConstantsDlg::OnEnSetfocusS20)
ON_EN_KILLFOCUS(IDC_S1, &CConstantsDlg::FillUsage)
ON_EN_KILLFOCUS(IDC_S2, &CConstantsDlg::FillUsage)
ON_EN_KILLFOCUS(IDC_S3, &CConstantsDlg::FillUsage)
ON_EN_KILLFOCUS(IDC_S4, &CConstantsDlg::FillUsage)
ON_EN_KILLFOCUS(IDC_S5, &CConstantsDlg::FillUsage)
ON_EN_KILLFOCUS(IDC_S6, &CConstantsDlg::FillUsage)
ON_EN_KILLFOCUS(IDC_S7, &CConstantsDlg::FillUsage)
ON_EN_KILLFOCUS(IDC_S8, &CConstantsDlg::FillUsage)
ON_EN_KILLFOCUS(IDC_S9, &CConstantsDlg::FillUsage)
ON_EN_KILLFOCUS(IDC_S10, &CConstantsDlg::FillUsage)
ON_EN_KILLFOCUS(IDC_S11, &CConstantsDlg::FillUsage)
ON_EN_KILLFOCUS(IDC_S12, &CConstantsDlg::FillUsage)
ON_EN_KILLFOCUS(IDC_S13, &CConstantsDlg::FillUsage)
ON_EN_KILLFOCUS(IDC_S14, &CConstantsDlg::FillUsage)
ON_EN_KILLFOCUS(IDC_S15, &CConstantsDlg::FillUsage)
ON_EN_KILLFOCUS(IDC_S16, &CConstantsDlg::FillUsage)
ON_EN_KILLFOCUS(IDC_S17, &CConstantsDlg::FillUsage)
ON_EN_KILLFOCUS(IDC_S18, &CConstantsDlg::FillUsage)
ON_EN_KILLFOCUS(IDC_S19, &CConstantsDlg::FillUsage)
ON_EN_KILLFOCUS(IDC_S20, &CConstantsDlg::FillUsage)
END_MESSAGE_MAP()


// CConstantsDlg message handlers


void CConstantsDlg::OnCbnSelchangeDm()
{
	UpdateData(FALSE);
}

BOOL CConstantsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	SetLabels();

	CStdioFile cf;
	if (cf.Open("ice.ini",CFile::modeRead))
	{
		for (int i=0;i<IGCNUMC;i++)
			cf.ReadString(ConstLabs[i]);
		bIniChanged = false;
		cf.Close();
	}
	BuildConstList(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CConstantsDlg::OnBnClickedOk()
{
	if (bIniChanged)
	{
		CStdioFile cf;
		CFileException e;
		if (cf.Open("ice.ini",CFile::modeCreate|CFile::modeWrite,&e))
		{
			for (int i=0;i<IGCNUMC;i++)
			{
				cf.WriteString(ConstLabs[i]);
				cf.WriteString("\n");
			}
			bIniChanged = false;
			cf.Close();
		}
		else
		{
			CString err;    
			err.Format("Error: cant open ice.ini for writing !!! (%d)",e.m_cause);
			AfxMessageBox(err);
		}
	}
	UpdateData(TRUE);
	UpdateData(FALSE);
}

void CConstantsDlg::OnBnClickedCancel()
{
	UpdateData(FALSE);
}

void CConstantsDlg::OnLbnSelchangeGloballist()
{
	CListBox *cbglobals = (CListBox *)GetDlgItem(IDC_GLOBALLIST);
	int idx = cbglobals->GetCurSel();
	if (idx == CB_ERR) return;
	if (pcore == NULL) return;
	CString val;
	val.Format("%g",pcore->pConstants->constants[idx]);
	SetDlgItemText(IDC_GLOBALVAL,val);
	SetDlgItemText(IDC_GLOBALLAB,ConstLabs[idx]);
}

void CConstantsDlg::OnBnClickedGlobalset()
{
	UpdateData(TRUE);
}
void CConstantsDlg::BuildConstList(int idx)
{
	CListBox *cbglobals = (CListBox *)GetDlgItem(IDC_GLOBALLIST);
	cbglobals->ResetContent();
	for (int i=0;i<40;i++)
	{
		CString s;
		s.Format("%02d/%02X - %s",i,i,ConstLabs[i]);
		cbglobals->AddString(s);
	}
	cbglobals->SetCurSel(idx);
}
void CConstantsDlg::OnLbnSelchangeDmusage()
{
	if (!pcore) return;
	CListBox *cbusage = (CListBox *)GetDlgItem(IDC_DMUSAGE);
	LPARAM p = (LPARAM)cbusage->GetItemDataPtr(cbusage->GetCurSel());
	if (p!=-1) MainUI->SelectPCE(p);
}

void CConstantsDlg::OnBnClickedBswtich()
{
	bShowAC = !bShowAC;
	CComboBox *cbdm = (CComboBox *)GetDlgItem(IDC_DM);
	int idx = cbdm->GetCurSel();
	SetLabels();
	cbdm->SetCurSel(idx);
	UpdateData(FALSE);
}

void CConstantsDlg::SetLabels()
{
		if (!bShowAC)
		{
			// DM/AC
			SetDlgItemText(IDC_DMLABEL,"Damage modifier (DM)");
			for (int i=0;i<IGCACMAX;i++)
			{
				SetDlgItemText(i+IDC_ACL1,IGCArmorClasses[i]);
			}
			CComboBox *cbdm = (CComboBox *)GetDlgItem(IDC_DM);
			cbdm->ResetContent();
			for (int i=0;i<IGCDMMAX;i++)
			{
				CString s;
				s.Format("DM%02d",i);
				cbdm->AddString(s);
			}
		}
		else
		{
			// AC/DM
			SetDlgItemText(IDC_DMLABEL,"Armor Class (AC)");
			for (int i=0;i<IGCACMAX;i++)
			{
				CString s;
				s.Format("DM%02d",i);
				SetDlgItemText(i+IDC_ACL1,s);
			}
			CComboBox *cbdm = (CComboBox *)GetDlgItem(IDC_DM);
			cbdm->ResetContent();
			for (int i=0;i<IGCDMMAX;i++)
			{
				cbdm->AddString(IGCArmorClasses[i]);
			}
		}
}

void CConstantsDlg::FillDMUsage(int idx) 
{
	CListBox *cbusage = (CListBox *)GetDlgItem(IDC_DMUSAGE);
	CString usedby;
	cbusage->ResetContent();
	if (idx <0) return;
	if (idx >=20) return;

	usedby.Format("DM%02d is used by:",idx);
	SetDlgItemText(IDC_USEDBYLABEL,usedby);
	if (idx == 0)
		cbusage->AddString("Collisions");
	
	for (int i=0;i<pcore->cl_Projectiles.GetCount();i++)
	{
			PtrCoreProjectile pproj = pcore->cl_Projectiles.GetAt(i);
			if (pproj->DM  == idx)
			{
				// usedby.AppendFormat("Projectile - p #%d ",pproj->uid);

				// display weapon that use this projectil
				for (int j=0;j<pcore->cl_Parts.GetSize();j++)
				{
					PtrCorePart ppart = pcore->cl_Parts.GetAt(j);
					if ((ppart->type == AGCEquipmentType_Weapon) && (!ppart->isspec))
					{
						if (ppart->specs.wep.wep_projectile_uid == pproj->uid)
						{
							usedby.Format("Weapon - %s (%d) (projectile - p #%d)",ppart->name,ppart->uid,pproj->uid);
							int idx = cbusage->AddString(usedby);
							cbusage->SetItemDataPtr(idx,ppart);
						}
					}
				}
				for (int j=0;j<pcore->cl_Probes.GetSize();j++)
				{
					PtrCoreProbe pprobe = pcore->cl_Probes.GetAt(j);
					if (pprobe->stats_projectile == pproj->uid)
					{
						usedby.Format("%s (%d) (projectile - p #%d)",pprobe->name,pprobe->uid,pproj->uid);
						int idx = cbusage->AddString(usedby);
						cbusage->SetItemDataPtr(idx,pprobe);
					}
				}
			}
	}
	for (int i=0;i<pcore->cl_Mines.GetCount();i++)
	{
		PtrCoreMine pmine = pcore->cl_Mines.GetAt(i);
		if (pmine->DM == idx)
		{
			usedby.Format("Mine - %s (%d)",pmine->name,pmine->uid);
			int idx = cbusage->AddString(usedby);
			cbusage->SetItemDataPtr(idx,pmine);
		}
	}
	for (int i=0;i<pcore->cl_Missiles.GetCount();i++)
	{
		PtrCoreMissile pmis = pcore->cl_Missiles.GetAt(i);
		if (pmis->DM == idx)
		{
			usedby.Format("Missile - %s (%d)",pmis->name,pmis->uid);
			int idx = cbusage->AddString(usedby);
			cbusage->SetItemDataPtr(idx,pmis);
		}
	}
}
void CConstantsDlg::FillACUsage(int idx)
{
	CListBox *cbusage = (CListBox *)GetDlgItem(IDC_DMUSAGE);
	CString usedby;
	cbusage->ResetContent();
	if (idx <0) return;
	if (idx >=20) return;

	usedby.Format("%s AC is used by:",IGCArmorClasses[idx]);
	SetDlgItemText(IDC_USEDBYLABEL,usedby);
	if (idx==0) cbusage->AddString("Asteriods");

	for (int i=0;i<pcore->cl_StationTypes.GetCount();i++)
	{
		PtrCoreStationType p = pcore->cl_StationTypes.GetAt(i);
		if (p->ACHull == idx)
		{
			usedby.Format("Station Hull - %s (%d)",p->name,p->uid);
			int idx = cbusage->AddString(usedby);
			cbusage->SetItemDataPtr(idx,p);
		}
		if (p->ACShld == idx)
		{
			usedby.Format("Station Shield - %s (%d)",p->name,p->uid);
			int idx = cbusage->AddString(usedby);
			cbusage->SetItemDataPtr(idx,p);
		}
	}
	for (int i=0;i<pcore->cl_Ships.GetCount();i++)
	{
		PtrCoreShip p = pcore->cl_Ships.GetAt(i);
		if (p->AC == idx)
		{
			usedby.Format("Ship Hull - %s (%d)",p->name,p->uid);
			int idx = cbusage->AddString(usedby);
			cbusage->SetItemDataPtr(idx,p);
		}
	}
	for (int i=0;i<pcore->cl_Parts.GetCount();i++)
	{
		PtrCorePart p = pcore->cl_Parts.GetAt(i);
		if (p->isspec) continue;
		if (p->type != AGCEquipmentType_Shield) continue;
		if (p->specs.shld.shld_AC == idx)
		{
			usedby.Format("Shield - %s (%d)",p->name,p->uid);
			int idx = cbusage->AddString(usedby);
			cbusage->SetItemDataPtr(idx,p);
		}
	}
}
void CConstantsDlg::OnEnSetfocusS(int i)
{
	if (bShowAC) 
		FillDMUsage(i); 
	//else 
	//	FillACUsage(i);
}
void CConstantsDlg::OnEnSetfocusS1() { OnEnSetfocusS(0);}
void CConstantsDlg::OnEnSetfocusS2() { OnEnSetfocusS(1);}
void CConstantsDlg::OnEnSetfocusS3() { OnEnSetfocusS(2);}
void CConstantsDlg::OnEnSetfocusS4() { OnEnSetfocusS(3);}
void CConstantsDlg::OnEnSetfocusS5() { OnEnSetfocusS(4);}
void CConstantsDlg::OnEnSetfocusS6() { OnEnSetfocusS(5);}
void CConstantsDlg::OnEnSetfocusS7() { OnEnSetfocusS(6);}
void CConstantsDlg::OnEnSetfocusS8() { OnEnSetfocusS(7);}
void CConstantsDlg::OnEnSetfocusS9() { OnEnSetfocusS(8);}
void CConstantsDlg::OnEnSetfocusS10() { OnEnSetfocusS(9);}
void CConstantsDlg::OnEnSetfocusS11() { OnEnSetfocusS(10);}
void CConstantsDlg::OnEnSetfocusS12() { OnEnSetfocusS(11);}
void CConstantsDlg::OnEnSetfocusS13() { OnEnSetfocusS(12);}
void CConstantsDlg::OnEnSetfocusS14() { OnEnSetfocusS(13);}
void CConstantsDlg::OnEnSetfocusS15() { OnEnSetfocusS(14);}
void CConstantsDlg::OnEnSetfocusS16() { OnEnSetfocusS(15);}
void CConstantsDlg::OnEnSetfocusS17() { OnEnSetfocusS(16);}
void CConstantsDlg::OnEnSetfocusS18() { OnEnSetfocusS(17);}
void CConstantsDlg::OnEnSetfocusS19() { OnEnSetfocusS(18);}
void CConstantsDlg::OnEnSetfocusS20() { OnEnSetfocusS(19);}

void CConstantsDlg::FillUsage()
{
	//CComboBox *cbdm = (CComboBox *)GetDlgItem(IDC_DM);
	//int idx = cbdm->GetCurSel();
	//FillUsage(idx);
}
void CConstantsDlg::FillUsage(int idx)
{
	if (!bShowAC) 
		FillDMUsage(idx);
	else
		FillACUsage(idx);
}