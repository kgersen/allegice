// ProbeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICE.h"
#include "corestruct.h"
#include "ProbeDlg.h"
#include ".\probedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CProbeDlg dialog

IMPLEMENT_DYNAMIC(CProbeDlg, CDialog)
CProbeDlg::CProbeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProbeDlg::IDD, pParent)
{
	pprobe = NULL;
}

CProbeDlg::~CProbeDlg()
{
}
void CProbeDlg::SetIcons(HICON iJumpIcon)
{
	((CButton *)GetDlgItem(IDC_BSUCC))->SetIcon(iJumpIcon);
	((CButton *)GetDlgItem(IDC_BPROJID))->SetIcon(iJumpIcon);
}

void CProbeDlg::DoDataExchange(CDataExchange* pDX)
{
	CString name,model,type,icon,descr,ukbmp,invline;

	int uid,ss1,ss2,ss3,ss4,proj,sound;
	if (!pprobe) return;
	ASSERT(sArtPath != "");
	PtrCoreLauncher pl = pcore->GetLauncher(pprobe->expendabletypeID);
	bool mountable;
	int uidprox = -1;
	if (pl)
	{
		mountable = true;
		uidprox = pl->partID;
		GetDlgItem(IDC_UIDPROX)->ShowWindow(SW_SHOWNA);
		GetDlgItem(IDC_OVUIDPROX)->ShowWindow(SW_SHOWNA);
		GetDlgItem(IDC_LAUNCHCOUNT)->ShowWindow(SW_SHOWNA);
		GetDlgItem(IDC_AMOUNT)->ShowWindow(SW_SHOWNA);
		GetDlgItem(IDC_UIDPROXLABEL)->ShowWindow(SW_SHOWNA);
		GetDlgItem(IDC_OVUIDPROXLABEL)->ShowWindow(SW_SHOWNA);
		GetDlgItem(IDC_LAUNCHCOUNTLABEL)->ShowWindow(SW_SHOWNA);
		GetDlgItem(IDC_AMOUNTLABEL)->ShowWindow(SW_SHOWNA);
		GetDlgItem(IDC_BSUCC)->ShowWindow(SW_SHOWNA);
		GetDlgItem(IDC_INVLINE)->ShowWindow(SW_SHOWNA);
		GetDlgItem(IDC_INVLINELABEL)->ShowWindow(SW_SHOWNA);
		CWnd::SetDlgItemText(IDC_PROXYBUT,"Disable");
	}
	else
	{
		mountable = false;
		GetDlgItem(IDC_UIDPROX)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_OVUIDPROX)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LAUNCHCOUNT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_AMOUNT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_UIDPROXLABEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_OVUIDPROXLABEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LAUNCHCOUNTLABEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_AMOUNTLABEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BSUCC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_INVLINE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_INVLINELABEL)->ShowWindow(SW_HIDE);
		CWnd::SetDlgItemText(IDC_PROXYBUT,"Enable");
	}

	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		name = pprobe->launcherDef.name;
		model = pprobe->modelName;
		descr = pprobe->launcherDef.description;
		icon = pprobe->iconName;
		mdlbmp.LoadMDLFile(sArtPath +"\\"+ icon + "bmp.mdl");
		type = pprobe->launcherDef.iconName;
		mdlbmp3.LoadMDLFile(sArtPath +"\\"+ type + "bmp.mdl");
		ukbmp = pprobe->launcherDef.modelName;
		mdlbmp2.LoadMDLFile(sArtPath +"\\l"+ ukbmp + "bmp.mdl");
		uid = pprobe->expendabletypeID;

		ss1	= pprobe->launcherDef.partMask;
		for (int i=0;i<16;i++) 
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM48+i);
			cbb->SetCheck((ss1 & (1<<i))?BST_CHECKED:BST_UNCHECKED);
			cbb->EnableWindow(TRUE);
		}
		OnBnClickedUsem48();

		CComboBox *cbac = (CComboBox *)GetDlgItem(IDC_AC);
		cbac->SetCurSel(pprobe->defenseType);

		ss2	= pprobe->launcherDef.expendableSize;
		ss3	= pprobe->eabmCapabilities;
		ss4 = pprobe->ammo;
		sound = pprobe->ambientSound;
		proj = pprobe->projectileTypeID;

		for (int i=0;i<16;i++)
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
			cbb->SetCheck((pprobe->eabmCapabilities & (1<<i))?BST_CHECKED:BST_UNCHECKED);
		}

		if (mountable)
			invline = pl->inventoryLineMDL;
	}
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_MODEL, model);
	DDX_Text(pDX, IDC_ICONE, icon);
	DDX_Text(pDX, IDC_TYPE, type);
	DDX_Text(pDX, IDC_UKBMP, ukbmp);
	DDX_Text(pDX, IDC_DESCRIPTION, descr);

	DDX_Text(pDX, IDC_COST, pprobe->launcherDef.price);

	DDX_Text(pDX, IDC_S1, pprobe->radius);
	DDX_Text(pDX, IDC_S2, pprobe->rotation);
	DDX_Text(pDX, IDC_S3, pprobe->loadTime);
	DDX_Text(pDX, IDC_S4, pprobe->lifespan);
	DDX_Text(pDX, IDC_S5, pprobe->signature);
	DDX_Text(pDX, IDC_S6, pprobe->launcherDef.mass);
	DDX_Text(pDX, IDC_S7, pprobe->hitPoints);
	DDX_Text(pDX, IDC_S8, pprobe->scannerRange);
	DDX_Text(pDX, IDC_S9, pprobe->dtimeBurst);
	DDX_Text(pDX, IDC_S10, pprobe->dispersion);
	DDX_Text(pDX, IDC_S11, pprobe->accuracy);
	DDX_Text(pDX, IDC_SS1, ss1);
	DDX_Text(pDX, IDC_SS2, ss2);
	DDX_Text(pDX, IDC_SS3, ss3);
	DDX_Text(pDX, IDC_SS4, ss4);
	DDX_Text(pDX, IDC_SOUND, sound);
	DDX_Text(pDX, IDC_PROJ, proj);
	DDX_Text(pDX, IDC_DELAY, pprobe->dtRipcord);

	DDX_Text(pDX, IDC_UID, uid);

	if (mountable)
	{
		DDX_Text(pDX, IDC_UIDPROX, uidprox);
		DDX_Text(pDX, IDC_OVUIDPROX, pl->successorPartID);
		DDX_Text(pDX, IDC_LAUNCHCOUNT, pl->launchCount);
		DDX_Text(pDX, IDC_AMOUNT,pl->amount);
		DDX_Text(pDX, IDC_INVLINE,invline);
	}
	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		strcpy(pprobe->launcherDef.name,name);
		strcpy(pprobe->modelName,model);
		strcpy(pprobe->iconName,icon);
		strcpy(pprobe->launcherDef.iconName,type);
		strcpy(pprobe->launcherDef.modelName,ukbmp);
		strncpy(pprobe->launcherDef.description,descr,IGC_DESCRIPTIONMAX);

		pprobe->launcherDef.partMask = 0;
		for (int i=0;i<16;i++) 
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM48+i);
			pprobe->launcherDef.partMask += cbb->GetCheck()?(1<<i):0;
		}
		if (pprobe->launcherDef.partMask == 0)
		{
			MessageBox("Warning usage mask is zero");
		}

		CComboBox *cbac = (CComboBox *)GetDlgItem(IDC_AC);
		pprobe->defenseType = cbac->GetCurSel();

		pprobe->launcherDef.expendableSize = ss2;
		pprobe->eabmCapabilities = ss3;
		pprobe->ammo = ss4;
		pprobe->projectileTypeID = proj;
		pprobe->ambientSound = sound;

		pprobe->eabmCapabilities = 0;
		for (int i=0;i<16;i++)
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
			pprobe->eabmCapabilities += (cbb->GetCheck()==BST_CHECKED)?(1<<i):0;
		}

		if (mountable)
			strcpy_s(pl->inventoryLineMDL,c_cbFileName,invline);

	}
	CDialog::DoDataExchange(pDX);
}

BOOL CProbeDlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	VERIFY(mdlbmp.SubclassDlgItem(IDC_PICT, this));
	VERIFY(mdlbmp2.SubclassDlgItem(IDC_PICT2, this));
	VERIFY(mdlbmp3.SubclassDlgItem(IDC_PICT3, this));

	CComboBox *cbac = (CComboBox *)GetDlgItem(IDC_AC);
	cbac->ResetContent();
	for (int i=0;i<IGCACMAX;i++)
		cbac->AddString(IGCArmorClasses[i]);

	((CEdit *)GetDlgItem(IDC_DESCRIPTION))->SetLimitText(IGC_DESCRIPTIONMAX);
	((CEdit *)GetDlgItem(IDC_NAME))->SetLimitText(IGC_NAMEMAX);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CProbeDlg::OnClickedOk(void)
{
	CString oldname = pprobe->launcherDef.name;
	UpdateData(TRUE);
	CString newname = pprobe->launcherDef.name;
	if (oldname != newname)
		GetParent()->UpdateData(TRUE);
	UpdateData(FALSE);
}

void CProbeDlg::OnClickedCancel(void)
{
	UpdateData(FALSE);
}


BEGIN_MESSAGE_MAP(CProbeDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnClickedCancel)
	ON_BN_CLICKED(IDC_PROXYBUT, OnBnClickedProxybut)
	ON_BN_CLICKED(IDC_USEM48, OnBnClickedUsem48)
	ON_BN_CLICKED(IDC_USEM49, OnBnClickedUsem48)
	ON_BN_CLICKED(IDC_USEM50, OnBnClickedUsem48)
	ON_BN_CLICKED(IDC_USEM51, OnBnClickedUsem48)
	ON_BN_CLICKED(IDC_USEM52, OnBnClickedUsem48)
	ON_BN_CLICKED(IDC_USEM53, OnBnClickedUsem48)
	ON_BN_CLICKED(IDC_USEM54, OnBnClickedUsem48)
	ON_BN_CLICKED(IDC_USEM55, OnBnClickedUsem48)
	ON_BN_CLICKED(IDC_USEM56, OnBnClickedUsem48)
	ON_BN_CLICKED(IDC_USEM57, OnBnClickedUsem48)
	ON_BN_CLICKED(IDC_USEM58, OnBnClickedUsem48)
	ON_BN_CLICKED(IDC_USEM59, OnBnClickedUsem48)
	ON_BN_CLICKED(IDC_USEM60, OnBnClickedUsem48)
	ON_BN_CLICKED(IDC_USEM61, OnBnClickedUsem48)
	ON_BN_CLICKED(IDC_USEM62, OnBnClickedUsem48)
	ON_BN_CLICKED(IDC_USEM63, OnBnClickedUsem48)
	ON_BN_CLICKED(IDC_BPROJID, &CProbeDlg::OnBnClickedBprojid)
	ON_BN_CLICKED(IDC_BSUCC, &CProbeDlg::OnBnClickedBsucc)
	ON_LBN_SELCHANGE(IDC_UMLIST, &CProbeDlg::OnLbnSelchangeUmlist)
	ON_BN_CLICKED(IDC_BEDITDESCR, &CProbeDlg::OnBnClickedBeditdescr)
END_MESSAGE_MAP()


// CProbeDlg message handlers

void CProbeDlg::OnBnClickedProxybut()
{
	if (!pprobe) return;
	PtrCoreLauncher pl = pcore->GetLauncher(pprobe->expendabletypeID);
	if (pl) // dismount
	{
		pcore->DeleteLauncher(pl);
		UpdateData(FALSE);
		GetParent()->UpdateData(TRUE);
	}
	else // mount
	{
		pl = new IGCCoreLauncher;
		pl->amount = 1;
		pl->launchCount = 1;
		pl->expendabletypeID = pprobe->expendabletypeID;
		pl->successorPartID = -1;
		strcpy(pl->inventoryLineMDL,"invsmine"); //TODO
		pcore->AddLauncher(pl);
		UpdateData(FALSE);
		GetParent()->UpdateData(TRUE);
	}
}
// display probes/mines with same usemask
void CProbeDlg::OnBnClickedUsem48()
{
	// compute currently displayed umask
	unsigned short umask = 0;
	for (int i=0;i<16;i++) 
	{
		CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM48+i);
		umask += cbb->GetCheck()?(1<<i):0;
	}

	CListBox *clb = (CListBox *)CWnd::GetDlgItem(IDC_UMLIST);
	clb->ResetContent();
	// get all parts that use umask
	for (int j=0;j<pcore->cl_Probes.GetSize();j++)
	{
		PtrCoreProbe pp = pcore->cl_Probes.GetAt(j);
		if ((pp->launcherDef.partMask & umask) && (pp->expendabletypeID != pprobe->expendabletypeID))
		{
			CString s;
			s.Format("Probe: %s (%d)",pp->launcherDef.name,pp->expendabletypeID);
			int idx = clb->AddString(s);
			clb->SetItemDataPtr(idx,pp);
		}
	}
	for (int j=0;j<pcore->cl_Mines.GetSize();j++)
	{
		PtrCoreMine pp = pcore->cl_Mines.GetAt(j);
		if ((pp->launcherDef.partMask & umask))
		{
			CString s;
			s.Format("Mine: %s (%d)",pp->launcherDef.name,pp->expendabletypeID);
			int idx = clb->AddString(s);
			clb->SetItemDataPtr(idx,pp);
		}
	}
}

void CProbeDlg::OnBnClickedBprojid()
{
	if (!pprobe) return;
	if (!pcore) return;
	if (pprobe->projectileTypeID == -1) return;
	PtrCoreProjectile pp = pcore->FindProjectile(pprobe->projectileTypeID);
	if (pp)
		MainUI->SelectPCE((LPARAM)pp);
	else
		AfxMessageBox("Error: can't find this projectile");
}

void CProbeDlg::OnBnClickedBsucc()
{
	if (!pprobe) return;
	if (!pcore) return;
	PtrCoreLauncher pl = pcore->GetLauncher(pprobe->expendabletypeID);
	if (!pl) return;
	if (pl->successorPartID == -1) return;
	
	PtrCoreLauncher succ = pcore->FindLauncher(pl->successorPartID);
	if (succ)
	{
		LPARAM p = (LPARAM)succ;
		if (1) //TODO
		{
			PtrCoreEntry pce = pcore->ProxyPart(succ->expendabletypeID);
			if (pce)
			{
				p = pce->entry;
				delete pce;
			}
			else
			{
				AfxMessageBox("Error: invalid successor");
				return;
			}
		}
		MainUI->SelectPCE(p);
	}
	else
		AfxMessageBox("Error: invalid successor");
}

void CProbeDlg::OnLbnSelchangeUmlist()
{
	CListBox *clb = (CListBox *)CWnd::GetDlgItem(IDC_UMLIST);
	int idx = clb->GetCurSel();
	if (idx==-1) return;
	MainUI->SelectPCE((LPARAM)clb->GetItemDataPtr(idx));
}

void CProbeDlg::OnBnClickedBeditdescr()
{
	CDescrDlg dlg(pprobe->launcherDef.description);
	if (dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_DESCRIPTION,pprobe->launcherDef.description);
}
