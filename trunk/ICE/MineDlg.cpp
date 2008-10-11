// MineDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICE.h"
#include "corestruct.h"
#include "MineDlg.h"
#include ".\minedlg.h"


// CMineDlg dialog

IMPLEMENT_DYNAMIC(CMineDlg, CDialog)
CMineDlg::CMineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMineDlg::IDD, pParent)
{
	pmine = NULL;
}

CMineDlg::~CMineDlg()
{
}
void CMineDlg::SetIcons(HICON iJumpIcon)
{
	((CButton *)GetDlgItem(IDC_BSUCC))->SetIcon(iJumpIcon);
}
void CMineDlg::DoDataExchange(CDataExchange* pDX)
{
	CString name,model,type,icon,descr,ukbmp;
	CString todo1 = "";
	int uid,ss1,ss2;
	if (!pmine) return;
	PtrCorePart prox = pcore->ProxyGet(pmine->uid);
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
		name = pmine->name;
		model = pmine->model;
		descr = pmine->description;
		icon = pmine->icon;
		type = pmine->type;
		ukbmp = pmine->ukbmp;
		uid = pmine->uid;
		ss1 = pmine->usemask;
		for (int i=0;i<16;i++) 
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
			cbb->SetCheck((ss1 & (1<<i))?BST_CHECKED:BST_UNCHECKED);
			cbb->EnableWindow(TRUE);
		}
		OnBnClickedUsem0();

		ss2 = pmine->stats_ss2;
		CComboBox *cbdm = (CComboBox *)GetDlgItem(IDC_DM);
		cbdm->SetCurSel(pmine->DM);
		CComboBox *cbac = (CComboBox *)GetDlgItem(IDC_AC);
		cbac->SetCurSel(pmine->AC);

		//todo1.AppendFormat("ss1 = %d (%04X)\r\n",pmine->stats_ss1,pmine->stats_ss1);
		//todo1.AppendFormat("ss2 = %d (%04X)\r\n",pmine->stats_ss2,pmine->stats_ss2);
		//todo1.AppendFormat("\r\n");
		//todo1.AppendFormat("pad7 = %02X\r\n",pmine->pad7);
		/*
		for (int i=0;i<sizeof(pmine->pad8);i++)
		{
			todo1.AppendFormat("%02X ",pmine->pad8[i]);
			if (!((i+1)%16)) todo1.AppendFormat("\r\n");
		}
		todo1.AppendFormat("\r\n");
		todo1.AppendFormat("RGBA = %f %f %f %f\r\n",pmine->pcRED,pmine->pcBlue,pmine->pcGreen,pmine->pcAlpha);

		todo1.AppendFormat("\r\nEND");*/
	}
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_MODEL, model);
	DDX_Text(pDX, IDC_ICONE, icon);
	DDX_Text(pDX, IDC_TYPE, type);
	DDX_Text(pDX, IDC_UKBMP, ukbmp);
	DDX_Text(pDX, IDC_DESCRIPTION, descr);
	//DDX_Text(pDX, IDC_TODO1, todo1);

	DDX_Text(pDX, IDC_SS1, ss1);
	DDX_Text(pDX, IDC_SS2, ss2);

	DDX_Text(pDX, IDC_S1, pmine->stats_s1);
	DDX_Text(pDX, IDC_S2, pmine->stats_s2);
	DDX_Text(pDX, IDC_S3, pmine->stats_s3);
	DDX_Text(pDX, IDC_S4, pmine->stats_s4);
	DDX_Text(pDX, IDC_S5, pmine->stats_s5);
	DDX_Text(pDX, IDC_S6, pmine->stats_s6);
	DDX_Text(pDX, IDC_S7, pmine->stats_endurance);
	DDX_Text(pDX, IDC_DURATION, pmine->stats_duration);

	DDX_Text(pDX, IDC_DAMAGE, pmine->stats_damage);
	DDX_Text(pDX, IDC_DAMAGE_RADIUS, pmine->stats_radius);
	DDX_Text(pDX, IDC_COST, pmine->cost);
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
		strcpy(pmine->name,name);
		strcpy(pmine->model,model);
		strcpy(pmine->icon,icon);
		strcpy(pmine->type,type);
		strcpy(pmine->ukbmp,ukbmp);
		strncpy(pmine->description,descr,IGC_DESCRIPTIONMAX);
		//pmine->usemask = ss1;
		pmine->usemask = 0;
		for (int i=0;i<16;i++) 
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
			pmine->usemask += cbb->GetCheck()?(1<<i):0;
		}
		if (pmine->usemask == 0)
		{
			MessageBox("Warning usage mask is zero");
		}

		pmine->stats_ss2 = ss2;
		CComboBox *cbdm = (CComboBox *)GetDlgItem(IDC_DM);
		pmine->DM = cbdm->GetCurSel();
		CComboBox *cbac = (CComboBox *)GetDlgItem(IDC_AC);
		pmine->AC = cbac->GetCurSel();

	}
	CDialog::DoDataExchange(pDX);
}

void CMineDlg::OnClickedDecodesel(void)
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

void CMineDlg::OnClickedDecodeh(void)
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

void CMineDlg::OnClickedOk(void)
{
	CString oldname = pmine->name;
	UpdateData(TRUE);
	CString newname = pmine->name;
	if (oldname != newname)
		GetParent()->UpdateData(TRUE);
	UpdateData(FALSE);
}

void CMineDlg::OnClickedCancel(void)
{
	UpdateData(FALSE);
}


BEGIN_MESSAGE_MAP(CMineDlg, CDialog)
	ON_BN_CLICKED(IDC_DECODESEL, OnClickedDecodesel)
	ON_BN_CLICKED(IDC_DECODEH, OnClickedDecodeh)
	ON_BN_CLICKED(IDOK, OnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnClickedCancel)
	ON_BN_CLICKED(IDC_PROXYBUT, OnBnClickedProxybut)
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
	ON_BN_CLICKED(IDC_BSUCC, &CMineDlg::OnBnClickedBsucc)
	ON_LBN_SELCHANGE(IDC_UMLIST, &CMineDlg::OnLbnSelchangeUmlist)
END_MESSAGE_MAP()


// CMineDlg message handlers

BOOL CMineDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

void CMineDlg::OnBnClickedProxybut()
{
	if (!pmine) return;
	PtrCorePart prox = pcore->ProxyGet(pmine->uid);
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
		prox->usemask = pmine->uid;
		prox->overriding_uid = -1;
		strcpy(prox->slot,"invsmine");
		pcore->AddPart(prox);
		UpdateData(FALSE);
		GetParent()->UpdateData(TRUE);
	}
}
// display probes/mines with same usemask
void CMineDlg::OnBnClickedUsem0()
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
	for (int j=0;j<pcore->cl_Mines.GetSize();j++)
	{
		PtrCoreMine pp = pcore->cl_Mines.GetAt(j);
		if ((pp->usemask & umask) && (pp->uid != pmine->uid))
		{
			CString s;
			s.Format("Mine: %s (%d)",pp->name,pp->uid);
			int idx = clb->AddString(s);
			clb->SetItemDataPtr(idx,pp);
		}
	}
	for (int j=0;j<pcore->cl_Probes.GetSize();j++)
	{
		PtrCoreProbe pp = pcore->cl_Probes.GetAt(j);
		if ((pp->usemask & umask))
		{
			CString s;
			s.Format("Probe: %s (%d)",pp->name,pp->uid);
			int idx = clb->AddString(s);
			clb->SetItemDataPtr(idx,pp);
		}
	}
}

void CMineDlg::OnBnClickedBsucc()
{
	if (!pmine) return;
	if (!pcore) return;
	PtrCorePart prox = pcore->ProxyGet(pmine->uid);
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
void CMineDlg::OnLbnSelchangeUmlist()
{
	CListBox *clb = (CListBox *)CWnd::GetDlgItem(IDC_UMLIST);
	int idx = clb->GetCurSel();
	if (idx==-1) return;
	MainUI->SelectPCE((LPARAM)clb->GetItemDataPtr(idx));
}
