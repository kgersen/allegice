// RandomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AGM.h"
#include "RandomDlg.h"


// CRandomDlg dialog

IMPLEMENT_DYNAMIC(CRandomDlg, CDialog)
CRandomDlg::CRandomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRandomDlg::IDD, pParent)
{
	SetDefaults();
}

CRandomDlg::~CRandomDlg()
{
}

void CRandomDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Text(pDX,IDC_RA1,ra_p1);
	DDX_Text(pDX,IDC_RA2,ra_p2);
	DDX_Text(pDX,IDC_RA3,ra_p3);
	DDX_Text(pDX,IDC_RA4,ra_p4);
	DDX_Text(pDX,IDC_RA5,ra_p5);
	DDX_Check(pDX,IDC_CKB19,ra_b19);
	DDX_Check(pDX,IDC_CKB42,ra_b42);
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRandomDlg, CDialog)
	ON_BN_CLICKED(IDC_DEFS, OnBnClickedDefs)
	ON_BN_CLICKED(IDC_CKB19, OnBnClickedCkb19)
	ON_BN_CLICKED(IDC_CKB42, OnBnClickedCkb42)
END_MESSAGE_MAP()


// CRandomDlg message handlers

void CRandomDlg::OnBnClickedDefs()
{
	SetDefaults();
	UpdateData(FALSE);
}

void CRandomDlg::SetDefaults()
{
	ra_p1 = 5625;
	ra_p2 = 4250;
	ra_p3 = 1875;
	ra_p4 = 0.25;
	ra_p5 = 0.1;
	ra_b19 = false;
	ra_b42 = false;
}
BOOL CRandomDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CRandomDlg::OnBnClickedCkb19()
{
	CButton *cb19 = (CButton *)GetDlgItem(IDC_CKB19);
	CButton *cb42 = (CButton *)GetDlgItem(IDC_CKB42);

	if (cb19->GetCheck() == BST_CHECKED)
		cb42->SetCheck(BST_UNCHECKED);
}

void CRandomDlg::OnBnClickedCkb42()
{
	CButton *cb19 = (CButton *)GetDlgItem(IDC_CKB19);
	CButton *cb42 = (CButton *)GetDlgItem(IDC_CKB42);

	if (cb42->GetCheck() == BST_CHECKED)
		cb19->SetCheck(BST_UNCHECKED);
}
