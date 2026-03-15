// AlephDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AGM.h"
#include "IGCMap.h"
#include "AlephDlg.h"


// CAlephDlg dialog

IMPLEMENT_DYNAMIC(CAlephDlg, CDialog)
CAlephDlg::CAlephDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAlephDlg::IDD, pParent)
{
	bTplMode = false;
}

CAlephDlg::~CAlephDlg()
{
}

void CAlephDlg::DoDataExchange(CDataExchange* pDX)
{
	CString render,name,icon;
	int radius;
	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		name  = curaleph->igcaleph.DestinationSectorName;
		render = curaleph->igcaleph.renderbmp;
		radius = curaleph->igcaleph.radius;
		icon = curaleph->igcaleph.imagebmp;
		IconBmp.LoadMDLFile(sArtPath + "\\" + icon +"bmp.mdl");
	}
	DDX_Check(pDX, IDC_APPLYSPIN, curaleph->bIncludeSpin);
	DDX_Check(pDX, IDC_ALEPH_AUTOORIENT, curaleph->bAutoOrient);
	DDX_Check(pDX, IDC_ALEPH_NOSPIN, curaleph->bNoSpin);
	DDX_Check(pDX, IDC_ALEPH_FIXED, curaleph->bFixedPosition); // KG 8/6/08

	DDX_CBString(pDX, IDC_ALEPH_RENDER, render);

	DDX_Text(pDX, IDC_A_ICON, icon); // KG 8/6/08

	DDX_Text(pDX, IDC_A_NAME, name);
	DDX_Text(pDX, IDC_ALEPH_POSX, curaleph->igcaleph.posx);
	DDX_Text(pDX, IDC_ALEPH_POSY, curaleph->igcaleph.posy);
	DDX_Text(pDX, IDC_ALEPH_POSZ, curaleph->igcaleph.posz);
	DDX_Text(pDX, IDC_ALEPH_O1X, curaleph->igcaleph.O1x);
	DDX_Text(pDX, IDC_ALEPH_O1Y, curaleph->igcaleph.O1y);
	DDX_Text(pDX, IDC_ALEPH_O1Z, curaleph->igcaleph.O1z);
	DDX_Text(pDX, IDC_ALEPH_SPINX, curaleph->igcaleph.spinx);
	DDX_Text(pDX, IDC_ALEPH_SPINY, curaleph->igcaleph.spiny);
	DDX_Text(pDX, IDC_ALEPH_SPINZ, curaleph->igcaleph.spinz);
	DDX_Text(pDX, IDC_ALEPH_SPIN_SPEED, curaleph->igcaleph.spinspeed);
	DDX_Text(pDX, IDC_ALEPH_SIG, curaleph->igcaleph.sig);
	DDX_Text(pDX, IDC_ALEPH_RADIUS, radius);

	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		strncpy(curaleph->igcaleph.renderbmp,render,sizeof(curaleph->igcaleph.renderbmp));
		strncpy(curaleph->igcaleph.DestinationSectorName,name,sizeof(curaleph->igcaleph.DestinationSectorName));
		strncpy(curaleph->igcaleph.imagebmp,icon,sizeof(curaleph->igcaleph.imagebmp));
		curaleph->igcaleph.radius = radius;
		curaleph->OrientTo();
	}

	CDialog::DoDataExchange(pDX);


}

BOOL CAlephDlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	CComboBox *cbrender = (CComboBox *) CWnd::GetDlgItem(IDC_ALEPH_RENDER);
	VERIFY(IconBmp.SubclassDlgItem(IDC_A_ICONBMP, this));

	if (bTplMode)
	{
		SetWindowText("Aleph defaults");
		SetDlgItemText(IDOK,"Save");
		cbrender->AddString("Random");

		CWnd *t = CWnd::GetDlgItem(IDC_A_NAME);
		t->ShowWindow(SW_HIDE);
		t = CWnd::GetDlgItem(IDC_AL_Name);
		t->ShowWindow(SW_HIDE);
		t = CWnd::GetDlgItem(IDC_ALEPH_POSX);
		t->ShowWindow(SW_HIDE);
		t = CWnd::GetDlgItem(IDC_AL_x);
		t->ShowWindow(SW_HIDE);
		t = CWnd::GetDlgItem(IDC_ALEPH_POSY);
		t->ShowWindow(SW_HIDE);
		t = CWnd::GetDlgItem(IDC_AL_y);
		t->ShowWindow(SW_HIDE);
		t = CWnd::GetDlgItem(IDC_ALEPH_POSZ);
		t->ShowWindow(SW_HIDE);
		t = CWnd::GetDlgItem(IDC_AL_z);
		t->ShowWindow(SW_HIDE);
		t = CWnd::GetDlgItem(IDC_ALEPH_FIXED);
		t->ShowWindow(SW_HIDE);
		t = CWnd::GetDlgItem(IDAPPLYTOSECT);
		t->ShowWindow(SW_SHOWNA);
		t = CWnd::GetDlgItem(IDAPPLYTOALL);
		t->ShowWindow(SW_SHOWNA);
		t = CWnd::GetDlgItem(IDC_APPLYSPIN);
		t->ShowWindow(SW_SHOWNA);
		t = CWnd::GetDlgItem(IDC_S_INCAPPLY);
		t->ShowWindow(SW_SHOWNA);
		t = NULL;

	}
	cbrender->AddString("plnt19");
	cbrender->AddString("plnt42");
	UpdateData(FALSE);
	SetAutoCheck();
	SetSpinCheck();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAlephDlg::OnClickedApplytosect(void)
{
	UpdateData(TRUE);
	EndDialog(IDAPPLYTOSECT);
}

void CAlephDlg::OnClickedApplytoall(void)
{
	UpdateData(TRUE);
	EndDialog(IDAPPLYTOALL);
}
void CAlephDlg::SetSpinCheck(void)
{
	CButton *cbc = (CButton *)CWnd::GetDlgItem(IDC_ALEPH_NOSPIN);
	CWnd *cwp;
	if (cbc->GetCheck()!=BST_CHECKED)
	{
		cwp = CWnd::GetDlgItem(IDC_ALEPH_SPINX);
		cwp->EnableWindow(TRUE);
		cwp = CWnd::GetDlgItem(IDC_ALEPH_SPINY);
		cwp->EnableWindow(TRUE);
		cwp = CWnd::GetDlgItem(IDC_ALEPH_SPINZ);
		cwp->EnableWindow(TRUE);
	}
	else
	{
		cwp = CWnd::GetDlgItem(IDC_ALEPH_SPINX);
		cwp->EnableWindow(FALSE);
		cwp = CWnd::GetDlgItem(IDC_ALEPH_SPINY);
		cwp->EnableWindow(FALSE);
		cwp = CWnd::GetDlgItem(IDC_ALEPH_SPINZ);
		cwp->EnableWindow(FALSE);
	}
}
void CAlephDlg::SetAutoCheck(void)
{
	CButton *cbc = (CButton *)CWnd::GetDlgItem(IDC_ALEPH_AUTOORIENT);
	CWnd *cwp;
	if (cbc->GetCheck()!=BST_CHECKED)
	{
		cwp = CWnd::GetDlgItem(IDC_ALEPH_O1X);
		cwp->EnableWindow(TRUE);
		cwp = CWnd::GetDlgItem(IDC_ALEPH_O1Y);
		cwp->EnableWindow(TRUE);
		cwp = CWnd::GetDlgItem(IDC_ALEPH_O1Z);
		cwp->EnableWindow(TRUE);
	}
	else
	{
		cwp = CWnd::GetDlgItem(IDC_ALEPH_O1X);
		cwp->EnableWindow(FALSE);
		cwp = CWnd::GetDlgItem(IDC_ALEPH_O1Y);
		cwp->EnableWindow(FALSE);
		cwp = CWnd::GetDlgItem(IDC_ALEPH_O1Z);
		cwp->EnableWindow(FALSE);
	}
}

BEGIN_MESSAGE_MAP(CAlephDlg, CDialog)
	ON_BN_CLICKED(IDAPPLYTOSECT, OnClickedApplytosect)
	ON_BN_CLICKED(IDAPPLYTOALL, OnClickedApplytoall)
	ON_BN_CLICKED(IDC_ALEPH_NOSPIN,SetSpinCheck)
	ON_BN_CLICKED(IDC_ALEPH_AUTOORIENT,SetAutoCheck)
	ON_BN_CLICKED(IDC_A_ICONBMP, &CAlephDlg::OnBnClickedAIconbmp)
END_MESSAGE_MAP()


// CAlephDlg message handlers

void CAlephDlg::OnBnClickedAIconbmp()
{
	CString icon;
	
	if (GetDlgItemText(IDC_A_ICON,icon))
	{
		IconBmp.LoadMDLFile(sArtPath + "\\" + icon +"bmp.mdl");
		IconBmp.Invalidate(true);
	}
}
