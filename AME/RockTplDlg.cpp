// RockTplDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AGM.h"
#include "RockTpl.h"
#include "RockTplDlg.h"


// CRockTplDlg dialog

IMPLEMENT_DYNAMIC(CRockTplDlg, CDialog)
CRockTplDlg::CRockTplDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRockTplDlg::IDD, pParent)
{
	iCurTab = 0;
}

CRockTplDlg::~CRockTplDlg()
{
}

void CRockTplDlg::DoDataExchange(CDataExchange* pDX)
{
	int i = iCurTab;
	int radius;
	float sig,hp;
	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		radius = rocktpl.radius[i];
		if (rocktpl.hp_size[i])
			hp = rocktpl.hitpoints_fact[i];
		else
			hp = rocktpl.hitpoints[i];
		if (rocktpl.sig_size[i])
			sig = rocktpl.sig_fact[i];
		else
			sig = rocktpl.sig[i];

	}
	DDX_Check(pDX, IDC_RADIUS_RND,(rocktpl.random_radius[i]));
	DDX_Check(pDX, IDC_SIG_AUTO,(rocktpl.sig_size[i]));
	DDX_Check(pDX, IDC_HP_AUTO,(rocktpl.hp_size[i]));
	DDX_Check(pDX, IDC_RADIUS_INC,(rocktpl.radius_Included[i]));
	DDX_Check(pDX, IDC_SIG_INC,(rocktpl.sig_Included[i]));
	DDX_Check(pDX, IDC_HP_INC,(rocktpl.hp_Included[i]));

	DDX_Text(pDX, IDC_ROCK_RADIUS, radius);
	DDX_Text(pDX, IDC_ROCK_SIG, sig);
	DDX_Text(pDX, IDC_ROCK_HP, hp);

	DDX_Text(pDX, IDC_RADIUS_MIN, rocktpl.radius_min[i]);
	DDX_Text(pDX, IDC_RADIUS_MAX, rocktpl.radius_max[i]);

	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		rocktpl.radius[i]= radius;
 		if (rocktpl.hp_size[i])
			rocktpl.hitpoints_fact[i] = hp;
		else
			rocktpl.hitpoints[i] = hp;
		if (rocktpl.sig_size[i])
			rocktpl.sig_fact[i] = sig; 
		else
			rocktpl.sig[i] = sig;
	}
	CDialog::DoDataExchange(pDX);
}

BOOL CRockTplDlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	CTabCtrl *ctab = (CTabCtrl *) CWnd::GetDlgItem(IDC_TAB_ROCKS);
	
	for(int i=0;i<ROCKTPLMAX;i++)
	{
		ctab->InsertItem(i,rocktpl.Names[i]);
	}
	UpdateData(FALSE);
	SetRadiusCheck();
	//SetSigCheck();
	//SetHPCheck();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CRockTplDlg::SetRadiusCheck(void)
{
	CButton *cbc = (CButton *)CWnd::GetDlgItem(IDC_RADIUS_RND);
	CWnd *cwp;
	if (cbc->GetCheck()!=BST_CHECKED)
	{
		cwp = CWnd::GetDlgItem(IDC_ROCK_RADIUS);
		cwp->EnableWindow(TRUE);
		cwp = CWnd::GetDlgItem(IDC_RADIUS_MIN);
		cwp->ShowWindow(SW_HIDE);
		cwp = CWnd::GetDlgItem(IDC_RADIUS_MAX);
		cwp->ShowWindow(SW_HIDE);
		cwp = CWnd::GetDlgItem(IDC_A_RADIUS_MIN);
		cwp->ShowWindow(SW_HIDE);
		cwp = CWnd::GetDlgItem(IDC_A_RADIUS_MAX);
		cwp->ShowWindow(SW_HIDE);
		cwp = CWnd::GetDlgItem(IDC_S_RADFRAME);
		cwp->ShowWindow(SW_HIDE);
	}
	else
	{
		cwp = CWnd::GetDlgItem(IDC_ROCK_RADIUS);
		cwp->EnableWindow(FALSE);
		cwp = CWnd::GetDlgItem(IDC_RADIUS_MIN);
		cwp->ShowWindow(SW_SHOWNA);
		cwp = CWnd::GetDlgItem(IDC_RADIUS_MAX);
		cwp->ShowWindow(SW_SHOWNA);
		cwp = CWnd::GetDlgItem(IDC_A_RADIUS_MIN);
		cwp->ShowWindow(SW_SHOWNA);
		cwp = CWnd::GetDlgItem(IDC_A_RADIUS_MAX);
		cwp->ShowWindow(SW_SHOWNA);
		cwp = CWnd::GetDlgItem(IDC_S_RADFRAME);
		cwp->ShowWindow(SW_SHOWNA);
	}
}

void CRockTplDlg::SetSigCheck(void)
{
	CButton *cbc = (CButton *)CWnd::GetDlgItem(IDC_SIG_AUTO);
	CString s;
	if (cbc->GetCheck()!=BST_CHECKED)
		s.Format("%g",rocktpl.sig[iCurTab]);
	else
		s.Format("%g",rocktpl.sig_fact[iCurTab]);

	SetDlgItemText(IDC_ROCK_SIG,s);
}

void CRockTplDlg::SetHPCheck(void)
{
	CButton *cbc = (CButton *)CWnd::GetDlgItem(IDC_HP_AUTO);
	CString s;
	if (cbc->GetCheck()!=BST_CHECKED)
		s.Format("%g",rocktpl.hitpoints[iCurTab]);
	else
		s.Format("%g",rocktpl.hitpoints_fact[iCurTab]);

	SetDlgItemText(IDC_ROCK_HP,s);
}

void CRockTplDlg::OnSelchangeTabRocks(NMHDR *pNMHDR, LRESULT *pResult)
{
	CTabCtrl *ctab = (CTabCtrl *) CWnd::GetDlgItem(IDC_TAB_ROCKS);
	iCurTab = ctab->GetCurSel();
	UpdateData(FALSE);
	SetRadiusCheck();
	*pResult = 0;
}

void CRockTplDlg::OnSelchangingTabRocks(NMHDR *pNMHDR, LRESULT *pResult)
{
	//TODO: check values ranges
	UpdateData(TRUE);
	*pResult = 0;
}

void CRockTplDlg::OnClickedApplytosect(void)
{
	UpdateData(TRUE);
	EndDialog(IDAPPLYTOSECT);
}

void CRockTplDlg::OnClickedApplytoall(void)
{
	UpdateData(TRUE);
	EndDialog(IDAPPLYTOALL);
}


BEGIN_MESSAGE_MAP(CRockTplDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIUS_RND,SetRadiusCheck)
	ON_BN_CLICKED(IDC_SIG_AUTO,SetSigCheck)
	ON_BN_CLICKED(IDC_HP_AUTO,SetHPCheck)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_ROCKS, OnSelchangeTabRocks)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_ROCKS, OnSelchangingTabRocks)
	ON_BN_CLICKED(IDAPPLYTOSECT, OnClickedApplytosect)
	ON_BN_CLICKED(IDAPPLYTOALL, OnClickedApplytoall)
END_MESSAGE_MAP()


// CRockTplDlg message handlers
