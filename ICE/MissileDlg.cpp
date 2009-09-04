// MissileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICE.h"
#include "corestruct.h"
#include "MissileDlg.h"
#include ".\missiledlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CMissileDlg dialog

IMPLEMENT_DYNAMIC(CMissileDlg, CDialog)
CMissileDlg::CMissileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMissileDlg::IDD, pParent)
{
	pmissile = NULL;
}

CMissileDlg::~CMissileDlg()
{
}
void CMissileDlg::SetIcons(HICON iJumpIcon)
{
	((CButton *)GetDlgItem(IDC_BSUCC))->SetIcon(iJumpIcon);
}
void CMissileDlg::DoDataExchange(CDataExchange* pDX)
{
	CString name,model,ldbmp,type,icon,descr,invline;
	CString todo1 = "";
	int ss1,ss3,ss4,useflags;
	int uid;
	if (!pmissile) return;
	ASSERT(sArtPath != "");
	CComboBox *cbse = (CComboBox *)CWnd::GetDlgItem(IDC_SEFFECT);
	PtrCoreLauncher pl = pcore->GetLauncher(pmissile->expendabletypeID);
	int uidprox = pl->partID;
 
	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		name = pmissile->launcherDef.name;
		model = pmissile->launcherDef.modelName;
		icon = pmissile->iconName;
		mdlbmp.LoadMDLFile(sArtPath +"\\"+ icon + "bmp.mdl");
		ldbmp = pmissile->modelName;
		mdlbmp2.LoadMDLFile(sArtPath +"\\l"+ ldbmp + "bmp.mdl");
		descr = pmissile->launcherDef.description;
		type = pmissile->launcherDef.iconName;
		mdlbmp3.LoadMDLFile(sArtPath +"\\"+ type + "bmp.mdl");
		uid = pmissile->expendabletypeID;

		cbse->SetCurSel(-1); // pmissile->special_effect);
		for (int i=0;i<IGCMISSILE_EFFECT_NBVALS;i++)
		{
			if (pmissile->eabmCapabilities == ICGMissileEffectsValues[i])
			{
				cbse->SetCurSel(i);
				break;
			}
		}
		
		useflags = pmissile->launcherDef.partMask;
		for (int i=0;i<16;i++) 
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
			cbb->SetCheck((useflags & (1<<i))?BST_CHECKED:BST_UNCHECKED);
			cbb->EnableWindow(TRUE);
		}
		OnBnClickedUsem0();

		ss1 = pmissile->launcherDef.expendableSize;
		CComboBox *cbdm = (CComboBox *)GetDlgItem(IDC_DM);
		cbdm->SetCurSel(pmissile->damageType);
		CComboBox *cbac = (CComboBox *)GetDlgItem(IDC_AC);
		cbac->SetCurSel(pmissile->defenseType);

		((CButton*)GetDlgItem(IDC_DIRECTIONNAL))->SetCheck( pmissile->bDirectional ? BST_CHECKED : BST_UNCHECKED);

		ss3 = pmissile->launchSound;
		ss4 = pmissile->ambientSound;

		invline = pl->inventoryLineMDL;
	}
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_MODEL, model);
	DDX_Text(pDX, IDC_UKBMP, ldbmp);
	DDX_Text(pDX, IDC_ICONE, icon);
	DDX_Text(pDX, IDC_TYPE, type);
	DDX_Text(pDX, IDC_DESCRIPTION, descr);
	// DDX_Text(pDX, IDC_TODO1, todo1);

	DDX_Text(pDX, IDC_SS1, ss1);
	DDX_Text(pDX, IDC_SS3, ss3);
	DDX_Text(pDX, IDC_SS4, ss4);
	DDX_Text(pDX, IDC_USEFLAGS, useflags);

	DDX_Text(pDX, IDC_S1, pmissile->radius);
	DDX_Text(pDX, IDC_S2, pmissile->rotation);
	DDX_Text(pDX, IDC_S3, pmissile->loadTime);
	DDX_Text(pDX, IDC_S4, pmissile->lifespan);
	DDX_Text(pDX, IDC_S5, pmissile->signature);
	DDX_Text(pDX, IDC_S6, pmissile->launcherDef.mass);
	DDX_Text(pDX, IDC_SIG, pmissile->launcherDef.signature);
	DDX_Text(pDX, IDC_COST, pmissile->launcherDef.price);
	DDX_Text(pDX, IDC_S16, pmissile->hitPoints);

	// missile specific attributes
	DDX_Text(pDX, IDC_S7, pmissile->acceleration);
	DDX_Text(pDX, IDC_S8, pmissile->turnRate);
	DDX_Text(pDX, IDC_S9, pmissile->initialSpeed);
	DDX_Text(pDX, IDC_S10, pmissile->lockTime);
	DDX_Text(pDX, IDC_S11, pmissile->readyTime);
	DDX_Text(pDX, IDC_S12, pmissile->maxLock);
	DDX_Text(pDX, IDC_S13, pmissile->chaffResistance);
	DDX_Text(pDX, IDC_S14, pmissile->dispersion);
	DDX_Text(pDX, IDC_S15, pmissile->lockAngle);
	DDX_Text(pDX, IDC_DAMAGE, pmissile->power);
	DDX_Text(pDX, IDC_DAMAGE_RADIUS, pmissile->blastRadius);
	DDX_Text(pDX, IDC_BLAST_POWER, pmissile->blastPower);
	
	DDX_Text(pDX, IDC_UID, uid);

	DDX_Text(pDX, IDC_UIDPROX, uidprox);
	DDX_Text(pDX, IDC_OVUIDPROX, pl->successorPartID);
	DDX_Text(pDX, IDC_LAUNCHCOUNT, pl->launchCount);
	DDX_Text(pDX, IDC_AMOUNT,pl->amount);
	DDX_Text(pDX, IDC_INVLINE, invline);

	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		strcpy(pmissile->launcherDef.name,name);
		strcpy(pmissile->launcherDef.modelName,model);
		strcpy(pmissile->modelName,ldbmp);
		strcpy(pmissile->iconName,icon);
		strcpy(pmissile->launcherDef.iconName,type);
		strncpy(pmissile->launcherDef.description,descr,IGC_DESCRIPTIONMAX);
		
		pmissile->eabmCapabilities = ICGMissileEffectsValues[cbse->GetCurSel()];

		CComboBox *cbdm = (CComboBox *)GetDlgItem(IDC_DM);
		pmissile->damageType = cbdm->GetCurSel();
		CComboBox *cbac = (CComboBox *)GetDlgItem(IDC_AC);
		pmissile->defenseType = cbac->GetCurSel();

		//pmissile->use_flags = useflags;
		pmissile->launcherDef.partMask = 0;
		for (int i=0;i<16;i++) 
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
			pmissile->launcherDef.partMask += cbb->GetCheck()?(1<<i):0;
		}
		if (pmissile->launcherDef.partMask == 0)
		{
			MessageBox("Warning usage mask is zero");
		}
		pmissile->launcherDef.expendableSize = ss1;

		pmissile->bDirectional = (((CButton*)GetDlgItem(IDC_DIRECTIONNAL))->GetCheck()) == BST_CHECKED;

		pmissile->launchSound = ss3;
		pmissile->ambientSound = ss4;

		strcpy_s(pl->inventoryLineMDL,c_cbFileName,invline);
	}
	CDialog::DoDataExchange(pDX);
}

void CMissileDlg::OnClickedDecodesel(void)
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

void CMissileDlg::OnClickedDecodeh(void)
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

BOOL CMissileDlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	VERIFY(mdlbmp.SubclassDlgItem(IDC_PICT, this));
	VERIFY(mdlbmp2.SubclassDlgItem(IDC_PICT2, this));
	VERIFY(mdlbmp3.SubclassDlgItem(IDC_PICT3, this));

	CComboBox *cbse = (CComboBox *)CWnd::GetDlgItem(IDC_SEFFECT);
	for (int  i=0;i<IGCMISSILE_EFFECT_NBVALS;i++)
	{
		int idx = cbse->AddString(ICGMissileEffects[i]);
		cbse->SetItemDataPtr(idx,(void *)ICGMissileEffectsValues[i]);
	}

	CComboBox *cbdm = (CComboBox *)GetDlgItem(IDC_DM);
	cbdm->ResetContent();
	for (int i=0;i<IGCDMMAX;i++)
	{
		CString s;
		s.Format("DM%02d",i);
		cbdm->AddString(s);
	}
	CComboBox *cbac = (CComboBox *)GetDlgItem(IDC_AC);
	cbac->ResetContent();
	for (int i=0;i<IGCACMAX;i++)
		cbac->AddString(IGCArmorClasses[i]);

	((CEdit *)GetDlgItem(IDC_DESCRIPTION))->SetLimitText(IGC_DESCRIPTIONMAX);
	((CEdit *)GetDlgItem(IDC_NAME))->SetLimitText(IGC_NAMEMAX);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CMissileDlg::OnClickedOk(void)
{
	CString oldname = pmissile->launcherDef.name;
	UpdateData(TRUE);
	CString newname = pmissile->launcherDef.name;
	if (oldname != newname)
		GetParent()->UpdateData(TRUE);
	UpdateData(FALSE);
}

void CMissileDlg::OnClickedCancel(void)
{
	UpdateData(FALSE);
}


BEGIN_MESSAGE_MAP(CMissileDlg, CDialog)
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
	ON_BN_CLICKED(IDC_BSUCC, &CMissileDlg::OnBnClickedBsucc)
	ON_LBN_SELCHANGE(IDC_UMLIST, &CMissileDlg::OnLbnSelchangeUmlist)
	ON_BN_CLICKED(IDC_BEDITDESCR, &CMissileDlg::OnBnClickedBeditdescr)
END_MESSAGE_MAP()


// CMissileDlg message handlers
// display other missiles with same usemask
void CMissileDlg::OnBnClickedUsem0()
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
	for (int j=0;j<pcore->cl_Missiles.GetSize();j++)
	{
		PtrCoreMissile pp = pcore->cl_Missiles.GetAt(j);
		if ((pp->launcherDef.partMask & umask) && (pp->expendabletypeID != pmissile->expendabletypeID))
		{
			CString s;
			s.Format("%s (%d)",pp->launcherDef.name,pp->expendabletypeID);
			int idx = clb->AddString(s);
			clb->SetItemDataPtr(idx,pp);
		}
	}
}

void CMissileDlg::OnBnClickedBsucc()
{
	if (!pmissile) return;
	if (!pcore) return;
	PtrCoreLauncher pl = pcore->GetLauncher(pmissile->expendabletypeID);
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
		AfxMessageBox("Error: invalid successor");}

void CMissileDlg::OnLbnSelchangeUmlist()
{
	CListBox *clb = (CListBox *)CWnd::GetDlgItem(IDC_UMLIST);
	int idx = clb->GetCurSel();
	if (idx==-1) return;
	MainUI->SelectPCE((LPARAM)clb->GetItemDataPtr(idx));
}

void CMissileDlg::OnBnClickedBeditdescr()
{
	CDescrDlg dlg(pmissile->launcherDef.description);
	if (dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_DESCRIPTION,pmissile->launcherDef.description);
}
