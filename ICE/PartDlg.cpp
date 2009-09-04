// PartDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICE.h"
#include "corestruct.h"
#include "PartDlg.h"
#include ".\partdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CPartDlg dialog

IMPLEMENT_DYNAMIC(CPartDlg, CDialog)
CPartDlg::CPartDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPartDlg::IDD, pParent)
{
	ppart = NULL;
	pcore = NULL;
}

CPartDlg::~CPartDlg()
{
}
void CPartDlg::SetIcons(HICON iJumpIcon)
{
	((CButton *)GetDlgItem(IDC_BPROJID))->SetIcon(iJumpIcon);
	((CButton *)GetDlgItem(IDC_BSUCC))->SetIcon(iJumpIcon);
}
void CPartDlg::DoDataExchange(CDataExchange* pDX)
{
	CString name,model,obj,descr,slot;

	int uid,usemask;
	int ss5,ss1,ss2,ss3,ss4;
	float s1,s2,s3,s4;
	CString ls1,ls2,ls3,ls4,ls7;
	CString lss5,lss1,lss2,lss3,lss4;
	if (!ppart) return;
	if (!pcore) return;
	CComboBox *cbpt = (CComboBox *)CWnd::GetDlgItem(IDC_PARTTYPE);
	CComboBox *cbac = (CComboBox *)GetDlgItem(IDC_AC);
	CEdit *cename = (CEdit *)CWnd::GetDlgItem(IDC_NAME);
	CEdit *cemodel = (CEdit *)CWnd::GetDlgItem(IDC_MODEL);
	CEdit *ceicon = (CEdit *)CWnd::GetDlgItem(IDC_OBJ);
	ls1 = ""; ls2 = ""; ls3 = ""; ls4 = ""; ls7= ""; 
	lss1 = ""; lss2 = ""; lss3 = ""; lss4 = ""; lss5 = "";

	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		cbpt->ResetContent();
		//if (ppart->isspec)
		/*{
			cbpt->AddString("Proxy");
			cbpt->SetCurSel(0);
			s1 = ppart->type; ls1 = "Launch count";
			s2 = ppart->suk2; ls2 = "Amount";

			cename->EnableWindow(FALSE);
			cemodel->EnableWindow(FALSE);
			ceicon->EnableWindow(FALSE);
			model = "";
			descr = "**** 'PROXY' PART : see name for real part ****";
			obj = "";
			name = "!!! NO MATCHING PART !!!"; 
			for (int i=0;i<pcore->cl_Counters.GetCount();i++)
			{
				PtrCoreCounter pcounter = pcore->cl_Counters.GetAt(i);
				if (pcounter->expendabletypeID == ppart->usemask)
					name = pcounter->launcherDef.name;
			}
			for (int i=0;i<pcore->cl_Mines.GetCount();i++)
			{
				PtrCoreMine pmine = pcore->cl_Mines.GetAt(i);
				if (pmine->expendabletypeID == ppart->usemask)
					name = pmine->launcherDef.name;
			}
			for (int i=0;i<pcore->cl_Probes.GetCount();i++)
			{
				PtrCoreProbe pprobe = pcore->cl_Probes.GetAt(i);
				if (pprobe->expendabletypeID == ppart->usemask)
					name = pprobe->launcherDef.name;
			}
			for (int i=0;i<pcore->cl_Missiles.GetCount();i++)
			{
				PtrCoreMissile pmis = pcore->cl_Missiles.GetAt(i);
				if (pmis->expendabletypeID == ppart->usemask)
					name = pmis->launcherDef.name;
			}
		}*/
		//else
		{
			ls7 = "Sig %";
			for (int  i=0;i<ET_MAX;i++)
				cbpt->AddString(ICGPartType[i]);
			cename->EnableWindow(TRUE);
			cemodel->EnableWindow(TRUE);
			ceicon->EnableWindow(TRUE);
			name = ppart->name;
			model = ppart->modelName;
			descr = ppart->description;
			obj = ppart->iconName;
			mdlbmp2.LoadMDLFile(sArtPath +"\\"+ obj + "bmp.mdl");
			mdlbmp.LoadMDLFile(sArtPath +"\\L"+ model + "bmp.mdl");
			usemask = ppart->partMask;
			for (int i=0;i<16;i++) 
			{
				CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
				//if (ppart->isspec)
				//{
				//	cbb->EnableWindow(FALSE);
				//	cbb->SetCheck(BST_UNCHECKED);
				//}
				//else
				{
					cbb->SetCheck((ppart->partMask & (1<<i))?BST_CHECKED:BST_UNCHECKED);
					cbb->EnableWindow(TRUE);
				}
			}
			OnBnClickedUsem0();
			CButton *cbproj = (CButton *)CWnd::GetDlgItem(IDC_BPROJID);
			cbproj->ShowWindow(SW_HIDE);
			switch (ppart->equipmentType)
			{
				case ET_Weapon:
					{
					cbproj->ShowWindow(SW_SHOWNA);
					DataWeaponTypeIGC *p = (DataWeaponTypeIGC *)ppart;
					s1 = p->dtimeReady; ls1 = "dt Ready";
					s2 = p->dtimeBurst; ls2 = "dt Burst";
					s3 = p->energyPerShot; ls3 = "Energy per shot";
					s4 = p->dispersion; ls4 = "Dispersion";
					ss1 = p->cAmmoPerShot; lss1 = "Ammo per shot";
					ss2 = p->activateSound; lss2 = "Activation sound";
					ss3 = p->singleShotSound; lss3 = "Single shot sound";
					ss4 = p->burstSound; lss4 = "Burst sound";
					ss5 = p->projectileTypeID;  lss5 = "Projectile";
					}
					break;
				case ET_Cloak:
					{
					DataCloakTypeIGC *p = (DataCloakTypeIGC *)ppart;
					s1 = p->energyConsumption; ls1 = "Energy Consumption";
					s2 = p->maxCloaking; ls2 = "Max cloaking";
					s3 = p->onRate; ls3 = "On rate";
					s4 = p->offRate; ls4 = "Off rate";
					ss1 = p->engageSound; lss1 = "Engage sound";
					ss2 = p->disengageSound; lss2 = "Disengage sound";
					}
				break;
				case ET_Afterburner:
					{
					DataAfterburnerTypeIGC *p = (DataAfterburnerTypeIGC *)ppart;
					s1 = p->fuelConsumption; ls1 = "Rate of consumption";
					s2 = p->maxThrust; ls2 = "Thrust amount";
					s3 = p->onRate; ls3 = "On rate";
					s4 = p->offRate; ls4 = "Off rate";
					ss1 = p->interiorSound; lss1 = "Interior sound";
					ss2 = p->exteriorSound; lss2 = "Exterior sound";
					}
				break;
				case ET_Pack:
					{
					DataPackTypeIGC *p = (DataPackTypeIGC *)ppart;
					ss1 = p->packType; lss1 = "Type (0=Ammo,1=fuel)";
					ss2 = p->amount; lss2 = "Quantity";
					}
				break;
				case ET_Shield:
					{
					DataShieldTypeIGC *p = (DataShieldTypeIGC *)ppart;
					s1 = p->rateRegen; ls1 = "Regen rate";
					s2 = p->maxStrength; ls2 = "Hitpoints";
					ss1 = p->activateSound; lss1 = "Activate sound";
					ss2 = p->deactivateSound; lss2 = "Desactivate sound";
					cbac->SetCurSel(p->defenseType);
					}
				break;
			}
			cbpt->SetCurSel(ppart->equipmentType);
		}
		slot = ppart->inventoryLineMDL;
		uid = ppart->partID;

	}
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_MODEL, model);
	DDX_Text(pDX, IDC_OBJ, obj);
	DDX_Text(pDX, IDC_SLOT, slot);
	DDX_Text(pDX, IDC_DESCRIPTION, descr);
	DDX_Text(pDX, IDC_UID, uid);
	DDX_Text(pDX, IDC_OVUID, ppart->successorPartID);

	DDX_Text(pDX, IDC_SIGM,ppart->signature);

	DDX_Text(pDX, IDC_COST, ppart->price);
	cbac->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ACC)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GS1)->EnableWindow(TRUE);
	GetDlgItem(IDC_USEMASK)->EnableWindow(TRUE);

	DDX_Text(pDX, IDC_GS1, ppart->mass);
	DDX_Text(pDX, IDC_USEMASK, usemask);

	if (ppart->equipmentType == ET_Shield)
	{
		cbac->ShowWindow(SW_SHOWNA);
		GetDlgItem(IDC_ACC)->ShowWindow(SW_SHOWNA);
	}

	SetDlgItemText(IDC_PS1,ls1);
	SetDlgItemText(IDC_PS2,ls2);
	SetDlgItemText(IDC_PS3,ls3);
	SetDlgItemText(IDC_PS4,ls4);
	SetDlgItemText(IDC_PS7,ls7);
	SetDlgItemText(IDC_PSS1,lss1);
	SetDlgItemText(IDC_PSS2,lss2);
	SetDlgItemText(IDC_PSS3,lss3);
	SetDlgItemText(IDC_PSS4,lss4);
	SetDlgItemText(IDC_PSS5,lss5);
	GetDlgItem(IDC_S1)->ShowWindow(ls1==""?SW_HIDE:SW_SHOWNA);
	GetDlgItem(IDC_S2)->ShowWindow(ls2==""?SW_HIDE:SW_SHOWNA);
	GetDlgItem(IDC_S3)->ShowWindow(ls3==""?SW_HIDE:SW_SHOWNA);
	GetDlgItem(IDC_S4)->ShowWindow(ls4==""?SW_HIDE:SW_SHOWNA);
	GetDlgItem(IDC_SIGM)->ShowWindow(ls7==""?SW_HIDE:SW_SHOWNA);
	GetDlgItem(IDC_SS1)->ShowWindow(lss1==""?SW_HIDE:SW_SHOWNA);
	GetDlgItem(IDC_SS2)->ShowWindow(lss2==""?SW_HIDE:SW_SHOWNA);
	GetDlgItem(IDC_SS3)->ShowWindow(lss3==""?SW_HIDE:SW_SHOWNA);
	GetDlgItem(IDC_SS4)->ShowWindow(lss4==""?SW_HIDE:SW_SHOWNA);
	GetDlgItem(IDC_SS5)->ShowWindow(lss5==""?SW_HIDE:SW_SHOWNA);

	DDX_Text(pDX, IDC_SS1, ss1);
	DDX_Text(pDX, IDC_SS2, ss2);
	DDX_Text(pDX, IDC_SS3, ss3);
	DDX_Text(pDX, IDC_SS4, ss4);
	DDX_Text(pDX, IDC_SS5, ss5);

	DDX_Text(pDX, IDC_S1, s1);
	DDX_Text(pDX, IDC_S2, s2);
	DDX_Text(pDX, IDC_S3, s3);
	DDX_Text(pDX, IDC_S4, s4);

	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		strcpy(ppart->name,name);
		strcpy(ppart->modelName,model);
		strcpy(ppart->iconName,obj);
		strcpy(ppart->inventoryLineMDL,slot);
		strncpy(ppart->description,descr,IGC_DESCRIPTIONMAX);
		
		// usemask
		ppart->partMask = usemask;
		ppart->partMask = 0;
		for (int i=0;i<16;i++) 
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
			ppart->partMask += cbb->GetCheck()?(1<<i):0;
		}

		switch (ppart->equipmentType)
		{
			case ET_Weapon:{
				DataWeaponTypeIGC *p = (DataWeaponTypeIGC *)ppart;
				 p->dtimeReady         = s1;
				 p->dtimeBurst         = s2;
				 p->energyPerShot      = s3;
				 p->dispersion         = s4;
				 p->cAmmoPerShot       = ss1;
				 p->activateSound      = ss2;
				 p->singleShotSound    = ss3;
				 p->burstSound         = ss4;
				 p->projectileTypeID   = ss5;
	 			 }break;
			case ET_Cloak:{
				DataCloakTypeIGC *p = (DataCloakTypeIGC *)ppart;
				p->energyConsumption = s1;
				p->maxCloaking       = s2;
				p->onRate            = s3;
				p->offRate           = s4;
				p->engageSound       = ss1;
				p->disengageSound    = ss2;
				}break;
			case ET_Afterburner:{
				DataAfterburnerTypeIGC *p = (DataAfterburnerTypeIGC *)ppart;
				p->fuelConsumption = s1;
				p->maxThrust       = s2;
				p->onRate          = s3;
				p->offRate         = s4;
				p->interiorSound   = ss1;
				p->exteriorSound   = ss2;
				}break;
			case ET_Pack:{
				DataPackTypeIGC *p = (DataPackTypeIGC *)ppart;
				p->packType = ss1;
				p->amount = ss2;
				}break;
			case ET_Shield:{
				DataShieldTypeIGC *p = (DataShieldTypeIGC *)ppart;
				p->rateRegen = s1;
				p->maxStrength = s2;
				p->activateSound = ss1;
				p->deactivateSound = ss2;
				p->defenseType = cbac->GetCurSel();
				}break;
		}
	}
	CDialog::DoDataExchange(pDX);
}

BOOL CPartDlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	VERIFY(mdlbmp.SubclassDlgItem(IDC_PICT, this));
	VERIFY(mdlbmp2.SubclassDlgItem(IDC_PICT2, this));

	CComboBox *cbac = (CComboBox *)GetDlgItem(IDC_AC);
	cbac->ResetContent();
	for (int i=0;i<IGCACMAX;i++)
		cbac->AddString(IGCArmorClasses[i]);

	((CEdit *)GetDlgItem(IDC_DESCRIPTION))->SetLimitText(IGC_DESCRIPTIONMAX);
	((CEdit *)GetDlgItem(IDC_NAME))->SetLimitText(IGC_NAMEMAX);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//void CPartDlg::OnClickedDecodesel(void)
//{
//	CEdit *cetodo = (CEdit *) CWnd::GetDlgItem(IDC_TODO1);
//	int i,j;
//	cetodo->GetSel(i,j);
//
//	// NT SPECIFIC
//   HLOCAL h = cetodo->GetHandle();
//   LPCTSTR lpszText = (LPCTSTR)LocalLock(h);
//	char res[1000];
//	strncpy(res,&(lpszText[i]),j-i);
//	SetDlgItemText(IDC_DECDEC,res);
//	float f;
//	unsigned char *pf;
//	unsigned int b1,b2,b3,b4;
//	pf = (unsigned char *)&f;
//	sscanf(res,"%x %x %x %x",&b1,&b2,&b3,&b4);
//	pf[0] = b1;
//	pf[1] = b2;
//	pf[2] = b3;
//	pf[3] = b4;
//	CString sres;
//	sres.Format("%g",f);
//	SetDlgItemText(IDC_DECFLOAT,sres);
//	
//   LocalUnlock(h);
//	// END OF NT SPECIFIC
//}

//void CPartDlg::OnClickedDecodeh(void)
//{
//	CEdit *cetodo = (CEdit *) CWnd::GetDlgItem(IDC_TODO1);
//	int i,j;
//	cetodo->GetSel(i,j);
//
//	// NT SPECIFIC
//   HLOCAL h = cetodo->GetHandle();
//   LPCTSTR lpszText = (LPCTSTR)LocalLock(h);
//	char res[1000];
//	strncpy(res,&(lpszText[i]),j-i);
//	SetDlgItemText(IDC_DECDEC,res);
//	unsigned short f;
//	unsigned char *pf;
//	unsigned int b1,b2;
//	pf = (unsigned char *)&f;
//	sscanf(res,"%x %x",&b1,&b2);
//	pf[0] = b1;
//	pf[1] = b2;
//	CString sres;
//	sres.Format("%04X = %d",f,f);
//	SetDlgItemText(IDC_DECFLOAT,sres);
//	
//   LocalUnlock(h);
//	// END OF NT SPECIFIC
//}

void CPartDlg::OnClickedOk(void)
{
	CString oldname = ppart->name;
	UpdateData(TRUE);
	CString newname = ppart->name;
	if (oldname != newname)
		GetParent()->UpdateData(TRUE);
	UpdateData(FALSE);
}

void CPartDlg::OnClickedCancel(void)
{
	UpdateData(FALSE);
}

BEGIN_MESSAGE_MAP(CPartDlg, CDialog)
//	ON_BN_CLICKED(IDC_DECODEH, OnClickedDecodeh)
//	ON_BN_CLICKED(IDC_DECODESEL, OnClickedDecodesel)
	ON_BN_CLICKED(IDOK, OnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnClickedCancel)
	ON_BN_CLICKED(IDC_USEM0, OnBnClickedUsem0)
	ON_BN_CLICKED(IDC_USEM1, OnBnClickedUsem0)
	ON_BN_CLICKED(IDC_USEM2, OnBnClickedUsem0)
	ON_BN_CLICKED(IDC_USEM3, OnBnClickedUsem0)
	ON_BN_CLICKED(IDC_USEM4, OnBnClickedUsem0)
	ON_BN_CLICKED(IDC_USEM5, OnBnClickedUsem0)
	ON_BN_CLICKED(IDC_USEM6, OnBnClickedUsem0)
	ON_BN_CLICKED(IDC_USEM7, OnBnClickedUsem0)
	ON_BN_CLICKED(IDC_USEM8, OnBnClickedUsem0)
	ON_BN_CLICKED(IDC_USEM9, OnBnClickedUsem0)
	ON_BN_CLICKED(IDC_USEM10, OnBnClickedUsem0)
	ON_BN_CLICKED(IDC_USEM11, OnBnClickedUsem0)
	ON_BN_CLICKED(IDC_USEM12, OnBnClickedUsem0)
	ON_BN_CLICKED(IDC_USEM13, OnBnClickedUsem0)
	ON_BN_CLICKED(IDC_USEM14, OnBnClickedUsem0)
	ON_BN_CLICKED(IDC_USEM15, OnBnClickedUsem0)
	ON_BN_CLICKED(IDC_BPROJID, &CPartDlg::OnBnClickedBprojid)
	ON_LBN_SELCHANGE(IDC_UMLIST, &CPartDlg::OnLbnSelchangeUmlist)
	ON_BN_CLICKED(IDC_BSUCC, &CPartDlg::OnBnClickedBsucc)
	ON_BN_CLICKED(IDC_BEDITDESCR, &CPartDlg::OnBnClickedBeditdescr)
END_MESSAGE_MAP()


// CPartDlg message handlers


// display parts with same usemask
void CPartDlg::OnBnClickedUsem0()
{
	// compute currently displayed umask
	unsigned short umask = 0;
	for (int i=0;i<16;i++) 
	{
		CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
		umask += cbb->GetCheck()?(1<<i):0;
	}

	CListBox *clb = (CListBox *)CWnd::GetDlgItem(IDC_UMLIST);
	clb->ResetContent();
	// get all parts that use umask
	for (int j=0;j<pcore->cl_Parts.GetSize();j++)
	{
		PtrCorePart pp = pcore->cl_Parts.GetAt(j);
		if ((pp->equipmentType == ppart->equipmentType))
		{
			bool IsUpgrade = false;
			for (int jj=0;jj<pcore->cl_Parts.GetSize();jj++)
			{
				PtrCorePart ppart2 = pcore->cl_Parts.GetAt(jj);
				if (ppart2->successorPartID == pp->partID)
				{
					IsUpgrade = true;
					break;
				}
			}
			if (!IsUpgrade)
			{
				if (pp->partMask & umask)
				{
					int idx = clb->AddString(pp->name);
					clb->SetItemDataPtr(idx,pp);
				}
			}
		}
	}

}

void CPartDlg::OnBnClickedBprojid()
{
	if (!ppart) return;
	if (!pcore) return;
	if (ppart->equipmentType != ET_Weapon) return;
	if (((DataWeaponTypeIGC*)ppart)->projectileTypeID == -1)
		AfxMessageBox("projectile is undefined");
	PtrCoreProjectile pp = pcore->FindProjectile(((DataWeaponTypeIGC*)ppart)->projectileTypeID);
	if (pp)
		MainUI->SelectPCE((LPARAM)pp);
	else
		AfxMessageBox("Error: can't find this projectile");

}

void CPartDlg::OnLbnSelchangeUmlist()
{
	CListBox *clb = (CListBox *)CWnd::GetDlgItem(IDC_UMLIST);
	int idx = clb->GetCurSel();
	if (idx==-1) return;
	MainUI->SelectPCE((LPARAM)clb->GetItemDataPtr(idx));
}

void CPartDlg::OnBnClickedBsucc()
{
	if (!ppart) return;
	if (!pcore) return;
	if (ppart->successorPartID == -1) return;
	PtrCorePart succ = pcore->FindPart(ppart->successorPartID);
	if (succ)
		MainUI->SelectPCE((LPARAM)succ);
	else
		AfxMessageBox("invalid successor!");
}

void CPartDlg::OnBnClickedBeditdescr()
{
	CDescrDlg dlg(ppart->description);
	if (dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_DESCRIPTION,ppart->description);
}
