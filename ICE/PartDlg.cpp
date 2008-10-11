// PartDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICE.h"
#include "corestruct.h"
#include "PartDlg.h"
#include ".\partdlg.h"


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
	CString todo1 = "";
	int uid,usemask;
	int ss5,ss1,ss2,ss3,ss4;
	float s1,s2,s3,s4,*sigm;
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

	sigm = (float *)&(ppart->suk1);
	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		cbpt->ResetContent();
		if (ppart->isspec)
		{
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
				if (pcounter->uid == ppart->usemask)
					name = pcounter->name;
			}
			for (int i=0;i<pcore->cl_Mines.GetCount();i++)
			{
				PtrCoreMine pmine = pcore->cl_Mines.GetAt(i);
				if (pmine->uid == ppart->usemask)
					name = pmine->name;
			}
			for (int i=0;i<pcore->cl_Probes.GetCount();i++)
			{
				PtrCoreProbe pprobe = pcore->cl_Probes.GetAt(i);
				if (pprobe->uid == ppart->usemask)
					name = pprobe->name;
			}
			for (int i=0;i<pcore->cl_Missiles.GetCount();i++)
			{
				PtrCoreMissile pmis = pcore->cl_Missiles.GetAt(i);
				if (pmis->uid == ppart->usemask)
					name = pmis->name;
			}
		}
		else
		{
			DDX_Text(pDX, IDC_SIGM,*sigm);
			ls7 = "Sig %";
			for (int  i=0;i<AGCEquipmentType_MAX;i++)
				cbpt->AddString(ICGPartType[i]);
			cename->EnableWindow(TRUE);
			cemodel->EnableWindow(TRUE);
			ceicon->EnableWindow(TRUE);
			name = ppart->name;
			model = ppart->model;
			descr = ppart->description;
			obj = ppart->icon;
			usemask = ppart->usemask;
			for (int i=0;i<16;i++) 
			{
				CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
				if (ppart->isspec)
				{
					cbb->EnableWindow(FALSE);
					cbb->SetCheck(BST_UNCHECKED);
				}
				else
				{
					cbb->SetCheck((ppart->usemask & (1<<i))?BST_CHECKED:BST_UNCHECKED);
					cbb->EnableWindow(TRUE);
				}
			}
			OnBnClickedUsem0();
			todo1.AppendFormat("GS1 = %g\r\n",ppart->stats_s1);
			todo1.AppendFormat("usemask = %d (%04X)\r\n",ppart->usemask,ppart->usemask);
			CButton *cbproj = (CButton *)CWnd::GetDlgItem(IDC_BPROJID);
			cbproj->ShowWindow(SW_HIDE);
			switch (ppart->type)
			{
				case AGCEquipmentType_Weapon:
					cbproj->ShowWindow(SW_SHOWNA);
					s1 = ppart->specs.wep.wep_stats_s1; ls1 = "Time ready";
					s2 = ppart->specs.wep.wep_stats_s2; ls2 = "Shot interval";
					s3 = ppart->specs.wep.wep_stats_s3; ls3 = "Energy consumption";
					s4 = ppart->specs.wep.wep_stats_s4; ls4 = "Particle spread";
					ss1 = ppart->specs.wep.wep_stats_ss1; lss1 = "Bullets per shot";
					ss2 = ppart->specs.wep.wep_stats_ss2; lss2 = "Activation sound";
					ss3 = ppart->specs.wep.wep_stats_ss3; lss3 = "Shoot sound";
					ss4 = ppart->specs.wep.wep_stats_ss4; lss4 = "Burst sound";
					ss5 = ppart->specs.wep.wep_projectile_uid;  lss5 = "Projectile";
					break;
				case AGCEquipmentType_Cloak:
					s1 = ppart->specs.clk.clk_stats_s1; ls1 = "Energy drain";
					s2 = ppart->specs.clk.clk_stats_s2; ls2 = "Sig reduction";
					s3 = ppart->specs.clk.clk_stats_s3; ls3 = "Activation duration";
					s4 = ppart->specs.clk.clk_stats_s4; ls4 = "Release duration";
					ss1 = ppart->specs.clk.clk_sound1; lss1 = "Sound On";
					ss2 = ppart->specs.clk.clk_sound2; lss2 = "Sound Off";
				break;
				case AGCEquipmentType_Afterburner:
					s1 = ppart->specs.aftb.aftb_stats_s1; ls1 = "Rate of consumption";
					s2 = ppart->specs.aftb.aftb_stats_s2; ls2 = "Thrust amount";
					s3 = ppart->specs.aftb.aftb_stats_s3; ls3 = "% acceleration";
					s4 = ppart->specs.aftb.aftb_stats_s4; ls4 = "Release duration";
					ss1 = ppart->specs.aftb.aftb_stats_ss1; lss1 = "Sound activate";
					ss2 = ppart->specs.aftb.aftb_stats_ss2; lss2 = "Sound desactivate";
				break;
				case AGCEquipmentType_Pack:
					ss1 = ppart->specs.pak.pak_stats_ss1; lss1 = "Type (0=Ammo,1=fuel)";
					ss2 = ppart->specs.pak.pak_stats_ss2; lss2 = "Quantity";
				break;
				case AGCEquipmentType_Shield:
					s1 = ppart->specs.shld.shld_stats_s1; ls1 = "Recharge rate";
					s2 = ppart->specs.shld.shld_stats_s2; ls2 = "Hitpoints";
					ss1 = ppart->specs.shld.shld_sound1; lss1 = "Sound activate";
					ss2 = ppart->specs.shld.shld_sound2; lss2 = "Sound desactivate";
					cbac->SetCurSel(ppart->specs.shld.shld_AC);
				break;
			}
			cbpt->SetCurSel(ppart->type);
		}
		slot = ppart->slot;
		uid = ppart->uid;
		
		todo1.AppendFormat("suk1 = %d (%04X)\r\n",ppart->suk1,ppart->suk1);
		todo1.AppendFormat("suk2 = %d (%04X)\r\n",ppart->suk2,ppart->suk2);
		char *p1 = (char *)ppart;
		char *p2 = (char *)(&(ppart->TODO[0]));
		int maxi = ppart->size-(int)(p2-p1);
		for (int i=0;i<maxi;i++)
		{
			todo1.AppendFormat("%02X ",ppart->TODO[i]);
			if (!((i+1)%16)) todo1.AppendFormat("\r\n");
		}
		todo1.AppendFormat("\r\nType = %04x\r\n",ppart->type);
		todo1.AppendFormat("\r\npad3 = %02x\r\n",ppart->pad3[0]);
		todo1.AppendFormat("\r\npad4 = %02x%02x\r\n",ppart->pad4[0],ppart->pad4[1]);
	}
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_MODEL, model);
	DDX_Text(pDX, IDC_OBJ, obj);
	DDX_Text(pDX, IDC_SLOT, slot);
	DDX_Text(pDX, IDC_DESCRIPTION, descr);
	DDX_Text(pDX, IDC_TODO1, todo1);
	DDX_Text(pDX, IDC_UID, uid);
	DDX_Text(pDX, IDC_OVUID, ppart->overriding_uid);
	DDX_Text(pDX, IDC_SIZEOFTAG, ppart->size);
	cbac->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ACC)->ShowWindow(SW_HIDE);
	if (ppart->isspec)
	{
		CString gs1 = "N/A";
		GetDlgItem(IDC_GS1)->EnableWindow(FALSE);
		GetDlgItem(IDC_USEMASK)->EnableWindow(FALSE);
		DDX_Text(pDX, IDC_GS1, gs1);
		DDX_Text(pDX, IDC_USEMASK, gs1);
	}
	else
	{
		GetDlgItem(IDC_GS1)->EnableWindow(TRUE);
		GetDlgItem(IDC_USEMASK)->EnableWindow(TRUE);
		DDX_Text(pDX, IDC_GS1, ppart->stats_s1);
		DDX_Text(pDX, IDC_USEMASK, usemask);
		if (ppart->type == AGCEquipmentType_Shield)
		{
			cbac->ShowWindow(SW_SHOWNA);
			GetDlgItem(IDC_ACC)->ShowWindow(SW_SHOWNA);
		}
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
		if (!ppart->isspec)
		{
			DDX_Text(pDX, IDC_SIGM,*sigm);
			strcpy(ppart->name,name);
			strcpy(ppart->model,model);
			strcpy(ppart->icon,obj);
			strcpy(ppart->slot,slot);
			strncpy(ppart->description,descr,IGC_DESCRIPTIONMAX);
			
			// usemask
			ppart->usemask = usemask;
			ppart->usemask = 0;
			for (int i=0;i<16;i++) 
			{
				CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
				ppart->usemask += cbb->GetCheck()?(1<<i):0;
			}

			switch (ppart->type)
			{
				case AGCEquipmentType_Weapon:
					ppart->specs.wep.wep_stats_s1 = s1;
					ppart->specs.wep.wep_stats_s2 = s2;
					ppart->specs.wep.wep_stats_s3 = s3;
					ppart->specs.wep.wep_stats_s4 = s4;
					ppart->specs.wep.wep_stats_ss1 = ss1;
					ppart->specs.wep.wep_stats_ss2 = ss2;
					ppart->specs.wep.wep_stats_ss3 = ss3;
					ppart->specs.wep.wep_stats_ss4 = ss4;
					ppart->specs.wep.wep_projectile_uid = ss5;
					break;
				case AGCEquipmentType_Cloak:
					ppart->specs.clk.clk_stats_s1 = s1;
					ppart->specs.clk.clk_stats_s2 = s2;
					ppart->specs.clk.clk_stats_s3 = s3;
					ppart->specs.clk.clk_stats_s4 = s4;
					ppart->specs.clk.clk_sound1 = ss1;
					ppart->specs.clk.clk_sound2 = ss2;
				break;
				case AGCEquipmentType_Afterburner:
					ppart->specs.aftb.aftb_stats_s1 = s1;
					ppart->specs.aftb.aftb_stats_s2 = s2;
					ppart->specs.aftb.aftb_stats_s3 = s3;
					ppart->specs.aftb.aftb_stats_s4 = s4;
					ppart->specs.aftb.aftb_stats_ss1 = ss1;
					ppart->specs.aftb.aftb_stats_ss2 = ss2;
				break;
				case AGCEquipmentType_Pack:
					ppart->specs.pak.pak_stats_ss1 = ss1;
					ppart->specs.pak.pak_stats_ss2 = ss2;
				break;
				case AGCEquipmentType_Shield:
					ppart->specs.shld.shld_stats_s1 = s1;
					ppart->specs.shld.shld_stats_s2 = s2;
					ppart->specs.shld.shld_sound1 = ss1;
					ppart->specs.shld.shld_sound2 = ss2;
					//ppart->specs.shld.shld_b1 = ss3;
					ppart->specs.shld.shld_AC = cbac->GetCurSel();
				break;
			}
		}
		else
		{
			ppart->type	= (int)s1;
			ppart->suk2 = (int)s2;
		}
	}
	CDialog::DoDataExchange(pDX);
}

BOOL CPartDlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	CComboBox *cbac = (CComboBox *)GetDlgItem(IDC_AC);
	cbac->ResetContent();
	for (int i=0;i<IGCACMAX;i++)
		cbac->AddString(IGCArmorClasses[i]);

	((CEdit *)GetDlgItem(IDC_DESCRIPTION))->SetLimitText(IGC_DESCRIPTIONMAX);
	((CEdit *)GetDlgItem(IDC_NAME))->SetLimitText(IGC_NAMEMAX);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPartDlg::OnClickedDecodesel(void)
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
	// END OF NT SPECIFIC
}

void CPartDlg::OnClickedDecodeh(void)
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
	ON_BN_CLICKED(IDC_DECODEH, OnClickedDecodeh)
	ON_BN_CLICKED(IDC_DECODESEL, OnClickedDecodesel)
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
		if ((pp->type == ppart->type) && (!pp->isspec))
		{
			bool IsUpgrade = false;
			for (int jj=0;jj<pcore->cl_Parts.GetSize();jj++)
			{
				PtrCorePart ppart2 = pcore->cl_Parts.GetAt(jj);
				if (ppart2->overriding_uid == pp->uid)
				{
					IsUpgrade = true;
					break;
				}
			}
			if (!IsUpgrade)
			{
				if (pp->usemask & umask)
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
	if (ppart->type != AGCEquipmentType_Weapon) return;
	if (ppart->specs.wep.wep_projectile_uid == -1)
		AfxMessageBox("projectile is undefined");
	PtrCoreProjectile pp = pcore->FindProjectile(ppart->specs.wep.wep_projectile_uid);
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
	if (ppart->overriding_uid == -1) return;
	PtrCorePart succ = pcore->FindPart(ppart->overriding_uid);
	if (succ)
		MainUI->SelectPCE((LPARAM)succ);
	else
		AfxMessageBox("invalid successor!");
}
