// MissileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICE.h"
#include "corestruct.h"
#include "MissileDlg.h"
#include ".\missiledlg.h"


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
	CString name,model,ldbmp,type,icon,descr;
	CString todo1 = "";
	int ss1,ss3,ss4,useflags;
	int uid;
	if (!pmissile) return;
	ASSERT(sArtPath != "");
	CComboBox *cbse = (CComboBox *)CWnd::GetDlgItem(IDC_SEFFECT);
	PtrCorePart prox = pcore->ProxyGet(pmissile->uid);
	int uidprox = prox->uid;
 
	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		name = pmissile->name;
		model = pmissile->model;
		icon = pmissile->icon;
		mdlbmp.LoadMDLFile(sArtPath +"\\"+ icon + "bmp.mdl");
		ldbmp = pmissile->ldbmp;
		mdlbmp2.LoadMDLFile(sArtPath +"\\l"+ ldbmp + "bmp.mdl");
		descr = pmissile->description;
		type = pmissile->type;
		uid = pmissile->uid;

		cbse->SetCurSel(-1); // pmissile->special_effect);
		for (int i=0;i<IGCMISSILE_EFFECT_NBVALS;i++)
		{
			if (pmissile->special_effect == ICGMissileEffectsValues[i])
			{
				cbse->SetCurSel(i);
				break;
			}
		}
		
		useflags = pmissile->use_flags;
		for (int i=0;i<16;i++) 
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
			cbb->SetCheck((useflags & (1<<i))?BST_CHECKED:BST_UNCHECKED);
			cbb->EnableWindow(TRUE);
		}
		OnBnClickedUsem0();

		ss1 = pmissile->stats_ss1;
		CComboBox *cbdm = (CComboBox *)GetDlgItem(IDC_DM);
		cbdm->SetCurSel(pmissile->DM);
		CComboBox *cbac = (CComboBox *)GetDlgItem(IDC_AC);
		cbac->SetCurSel(pmissile->AC);

		ss3 = pmissile->stats_ss3;
		ss4 = pmissile->stats_ss4;

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

	DDX_Text(pDX, IDC_S1, pmissile->stats_s1);
	DDX_Text(pDX, IDC_S2, pmissile->stats_s2);
	DDX_Text(pDX, IDC_S3, pmissile->stats_s3);
	DDX_Text(pDX, IDC_S4, pmissile->stats_s4);
	DDX_Text(pDX, IDC_S5, pmissile->stats_s5);
	DDX_Text(pDX, IDC_S6, pmissile->stats_s6);
	DDX_Text(pDX, IDC_S7, pmissile->stats_s7);
	DDX_Text(pDX, IDC_S8, pmissile->stats_s8);
	DDX_Text(pDX, IDC_S9, pmissile->stats_s9);
	DDX_Text(pDX, IDC_S10, pmissile->stats_s10);
	DDX_Text(pDX, IDC_S11, pmissile->stats_s11);
	DDX_Text(pDX, IDC_S12, pmissile->stats_s12);
	DDX_Text(pDX, IDC_S13, pmissile->stats_s13);
	DDX_Text(pDX, IDC_S14, pmissile->stats_s14);
	DDX_Text(pDX, IDC_S15, pmissile->stats_s15);
	DDX_Text(pDX, IDC_S16, pmissile->stats_s16);
	DDX_Text(pDX, IDC_DAMAGE, pmissile->stats_power);
	DDX_Text(pDX, IDC_DAMAGE_RADIUS, pmissile->stats_blast_radius);
	DDX_Text(pDX, IDC_BLAST_POWER, pmissile->stats_blast_power);
	DDX_Text(pDX, IDC_SIG, pmissile->stats_sig);
	DDX_Text(pDX, IDC_COST, pmissile->cost);

	DDX_Text(pDX, IDC_UID, uid);

	DDX_Text(pDX, IDC_UIDPROX, uidprox);
	DDX_Text(pDX, IDC_OVUIDPROX, prox->overriding_uid);
	DDX_Text(pDX, IDC_LAUNCHCOUNT, prox->type);
	DDX_Text(pDX, IDC_AMOUNT,prox->suk2);

	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		strcpy(pmissile->name,name);
		strcpy(pmissile->model,model);
		strcpy(pmissile->ldbmp,ldbmp);
		strcpy(pmissile->icon,icon);
		strcpy(pmissile->type,type);
		strncpy(pmissile->description,descr,IGC_DESCRIPTIONMAX);
		
		pmissile->special_effect = ICGMissileEffectsValues[cbse->GetCurSel()];

		CComboBox *cbdm = (CComboBox *)GetDlgItem(IDC_DM);
		pmissile->DM = cbdm->GetCurSel();
		CComboBox *cbac = (CComboBox *)GetDlgItem(IDC_AC);
		pmissile->AC = cbac->GetCurSel();

		//pmissile->use_flags = useflags;
		pmissile->use_flags = 0;
		for (int i=0;i<16;i++) 
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
			pmissile->use_flags += cbb->GetCheck()?(1<<i):0;
		}
		if (pmissile->use_flags == 0)
		{
			MessageBox("Warning usage mask is zero");
		}
		pmissile->stats_ss1 = ss1;
		pmissile->stats_ss3 = ss3;
		pmissile->stats_ss4 = ss4;

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
	CString oldname = pmissile->name;
	UpdateData(TRUE);
	CString newname = pmissile->name;
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
		if ((pp->use_flags & umask) && (pp->uid != pmissile->uid))
		{
			CString s;
			s.Format("%s (%d)",pp->name,pp->uid);
			int idx = clb->AddString(s);
			clb->SetItemDataPtr(idx,pp);
		}
	}
}

void CMissileDlg::OnBnClickedBsucc()
{
	if (!pmissile) return;
	if (!pcore) return;
	PtrCorePart prox = pcore->ProxyGet(pmissile->uid);
	if (!prox) return;
	if (prox->overriding_uid == -1) return;
	
	PtrCorePart succ = pcore->FindPart(prox->overriding_uid);
	if (succ)
	{
		LPARAM p = (LPARAM)succ;
		if (succ->isspec)
		{
			PtrCoreEntry pce = pcore->ProxyPart(succ->usemask);
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
