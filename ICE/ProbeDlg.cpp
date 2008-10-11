// ProbeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICE.h"
#include "corestruct.h"
#include "ProbeDlg.h"
#include ".\probedlg.h"


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
	CString name,model,type,icon,descr,ukbmp;
	CString todo1 = "";
	int uid,ss1,ss2,ss3,ss4,proj,sound;
	if (!pprobe) return;
	ASSERT(sArtPath != "");
	PtrCorePart prox = pcore->ProxyGet(pprobe->uid);
	bool mountable;
	int uidprox = -1;
	if (prox)
	{
		mountable = true;
		uidprox = prox->uid;
		GetDlgItem(IDC_UIDPROX)->ShowWindow(SW_SHOWNA);
		GetDlgItem(IDC_OVUIDPROX)->ShowWindow(SW_SHOWNA);
		GetDlgItem(IDC_LAUNCHCOUNT)->ShowWindow(SW_SHOWNA);
		GetDlgItem(IDC_AMOUNT)->ShowWindow(SW_SHOWNA);
		GetDlgItem(IDC_UIDPROXLABEL)->ShowWindow(SW_SHOWNA);
		GetDlgItem(IDC_OVUIDPROXLABEL)->ShowWindow(SW_SHOWNA);
		GetDlgItem(IDC_LAUNCHCOUNTLABEL)->ShowWindow(SW_SHOWNA);
		GetDlgItem(IDC_AMOUNTLABEL)->ShowWindow(SW_SHOWNA);
		GetDlgItem(IDC_BSUCC)->ShowWindow(SW_SHOWNA);
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
		CWnd::SetDlgItemText(IDC_PROXYBUT,"Enable");
	}

	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		name = pprobe->name;
		model = pprobe->model;
		descr = pprobe->description;
		icon = pprobe->icon;
		mdlbmp.LoadMDLFile(sArtPath +"\\"+ icon + "bmp.mdl");
		type = pprobe->type;
		ukbmp = pprobe->ukbmp;
		mdlbmp2.LoadMDLFile(sArtPath +"\\l"+ ukbmp + "bmp.mdl");
		uid = pprobe->uid;
		// usemask
		ss1	= pprobe->usemask;
		for (int i=0;i<16;i++) 
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM48+i);
			cbb->SetCheck((ss1 & (1<<i))?BST_CHECKED:BST_UNCHECKED);
			cbb->EnableWindow(TRUE);
		}
		OnBnClickedUsem48();

		CComboBox *cbac = (CComboBox *)GetDlgItem(IDC_AC);
		cbac->SetCurSel(pprobe->AC);

		ss2	= pprobe->stats_ss2;
		ss3	= pprobe->stats_ss3;
		ss4 = pprobe->stats_ss4;
		sound = pprobe->stats_sound;
		proj = pprobe->stats_projectile;
		todo1.AppendFormat("\r\nEND");
		for (int i=0;i<16;i++)
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
			cbb->SetCheck((pprobe->stats_ss3 & (1<<i))?BST_CHECKED:BST_UNCHECKED);
		}
	}
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_MODEL, model);
	DDX_Text(pDX, IDC_ICONE, icon);
	DDX_Text(pDX, IDC_TYPE, type);
	DDX_Text(pDX, IDC_UKBMP, ukbmp);
	DDX_Text(pDX, IDC_DESCRIPTION, descr);
	//DDX_Text(pDX, IDC_TODO1, todo1);

	DDX_Text(pDX, IDC_COST, pprobe->cost);

	DDX_Text(pDX, IDC_S1, pprobe->stats_s1);
	DDX_Text(pDX, IDC_S2, pprobe->stats_s2);
	DDX_Text(pDX, IDC_S3, pprobe->stats_s3);
	DDX_Text(pDX, IDC_S4, pprobe->stats_s4);
	DDX_Text(pDX, IDC_S5, pprobe->stats_s5);
	DDX_Text(pDX, IDC_S6, pprobe->stats_s6);
	DDX_Text(pDX, IDC_S7, pprobe->stats_s7);
	DDX_Text(pDX, IDC_S8, pprobe->stats_s8);
	DDX_Text(pDX, IDC_S9, pprobe->stats_s9);
	DDX_Text(pDX, IDC_S10, pprobe->stats_s10);
	DDX_Text(pDX, IDC_S11, pprobe->stats_s11);
	DDX_Text(pDX, IDC_SS1, ss1);
	DDX_Text(pDX, IDC_SS2, ss2);
	DDX_Text(pDX, IDC_SS3, ss3);
	DDX_Text(pDX, IDC_SS4, ss4);
	DDX_Text(pDX, IDC_SOUND, sound);
	DDX_Text(pDX, IDC_PROJ, proj);
	DDX_Text(pDX, IDC_DELAY, pprobe->stats_activation_delay);
//	DDX_Text(pDX, IDC_DURATION, pprobe->stats_duration);
	DDX_Text(pDX, IDC_UID, uid);

	if (mountable)
	{
		DDX_Text(pDX, IDC_UIDPROX, uidprox);
		DDX_Text(pDX, IDC_OVUIDPROX, prox->overriding_uid);
		DDX_Text(pDX, IDC_LAUNCHCOUNT, prox->type);
		DDX_Text(pDX, IDC_AMOUNT,prox->suk2);
	}
	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		strcpy(pprobe->name,name);
		strcpy(pprobe->model,model);
		strcpy(pprobe->icon,icon);
		strcpy(pprobe->type,type);
		strcpy(pprobe->ukbmp,ukbmp);
		strncpy(pprobe->description,descr,IGC_DESCRIPTIONMAX);
		// usemask
		//pprobe->stats_ss1 = ss1;
		pprobe->usemask = 0;
		for (int i=0;i<16;i++) 
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM48+i);
			pprobe->usemask += cbb->GetCheck()?(1<<i):0;
		}
		if (pprobe->usemask == 0)
		{
			MessageBox("Warning usage mask is zero");
		}

		CComboBox *cbac = (CComboBox *)GetDlgItem(IDC_AC);
		pprobe->AC = cbac->GetCurSel();

		pprobe->stats_ss2 = ss2;
		pprobe->stats_ss3 = ss3;
		pprobe->stats_ss4 = ss4;
		pprobe->stats_projectile = proj;
		pprobe->stats_sound = sound;

		pprobe->stats_ss3 = 0;
		for (int i=0;i<16;i++)
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
			pprobe->stats_ss3 += (cbb->GetCheck()==BST_CHECKED)?(1<<i):0;
		}

	}
	CDialog::DoDataExchange(pDX);
}

void CProbeDlg::OnClickedDecodesel(void)
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

void CProbeDlg::OnClickedDecodeh(void)
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

BOOL CProbeDlg::OnInitDialog(void)
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

void CProbeDlg::OnClickedOk(void)
{
	CString oldname = pprobe->name;
	UpdateData(TRUE);
	CString newname = pprobe->name;
	if (oldname != newname)
		GetParent()->UpdateData(TRUE);
	UpdateData(FALSE);
}

void CProbeDlg::OnClickedCancel(void)
{
	UpdateData(FALSE);
}


BEGIN_MESSAGE_MAP(CProbeDlg, CDialog)
	ON_BN_CLICKED(IDC_DECODESEL, OnClickedDecodesel)
	ON_BN_CLICKED(IDC_DECODEH, OnClickedDecodeh)
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
END_MESSAGE_MAP()


// CProbeDlg message handlers

void CProbeDlg::OnBnClickedProxybut()
{
	if (!pprobe) return;
	PtrCorePart prox = pcore->ProxyGet(pprobe->uid);
	if (prox) // dismount
	{
		pcore->DeletePart(prox,false);
		UpdateData(FALSE);
		GetParent()->UpdateData(TRUE);
	}
	else // mount
	{
		prox = new IGCCorePart;
		prox->isspec = true;
		prox->size = IGC_PROXYPARTSIZE;
		prox->suk2 = 1;
		prox->type = 1;
		prox->usemask = pprobe->uid;
		prox->overriding_uid = -1;
		strcpy(prox->slot,"invsmine");
		pcore->AddPart(prox);
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
		if ((pp->usemask & umask) && (pp->uid != pprobe->uid))
		{
			CString s;
			s.Format("Probe: %s (%d)",pp->name,pp->uid);
			int idx = clb->AddString(s);
			clb->SetItemDataPtr(idx,pp);
		}
	}
	for (int j=0;j<pcore->cl_Mines.GetSize();j++)
	{
		PtrCoreMine pp = pcore->cl_Mines.GetAt(j);
		if ((pp->usemask & umask))
		{
			CString s;
			s.Format("Mine: %s (%d)",pp->name,pp->uid);
			int idx = clb->AddString(s);
			clb->SetItemDataPtr(idx,pp);
		}
	}
}

void CProbeDlg::OnBnClickedBprojid()
{
	if (!pprobe) return;
	if (!pcore) return;
	if (pprobe->stats_projectile == -1) return;
	PtrCoreProjectile pp = pcore->FindProjectile(pprobe->stats_projectile);
	if (pp)
		MainUI->SelectPCE((LPARAM)pp);
	else
		AfxMessageBox("Error: can't find this projectile");
}

void CProbeDlg::OnBnClickedBsucc()
{
	if (!pprobe) return;
	if (!pcore) return;
	PtrCorePart prox = pcore->ProxyGet(pprobe->uid);
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
		AfxMessageBox("Error: invalid successor");
}

void CProbeDlg::OnLbnSelchangeUmlist()
{
	CListBox *clb = (CListBox *)CWnd::GetDlgItem(IDC_UMLIST);
	int idx = clb->GetCurSel();
	if (idx==-1) return;
	MainUI->SelectPCE((LPARAM)clb->GetItemDataPtr(idx));
}
