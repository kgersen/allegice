// CivDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICE.h"
#include "corestruct.h"
#include "MDLView.h"
#include "CivDlg.h"


// CCivDlg dialog

IMPLEMENT_DYNAMIC(CCivDlg, CDialog)
CCivDlg::CCivDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCivDlg::IDD, pParent)
{
	pciv = NULL;
	pcore = NULL;
	MainUI = NULL;
	sArtPath = "";
}

CCivDlg::~CCivDlg()
{

}
void CCivDlg::SetIcons(HICON iJumpIcon)
{
	((CButton *)GetDlgItem(IDC_BGARID))->SetIcon(iJumpIcon);
	((CButton *)GetDlgItem(IDC_BLIFEPOD))->SetIcon(iJumpIcon);
}
void CCivDlg::DoDataExchange(CDataExchange* pDX)
{
	CString name,model;
	int podid,garid;
	if (!pciv) return;
	if (!pcore) return;

	int uid = pciv->uid;
	CString	obj = pciv->obj;
	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		name = pciv->name;
		model = pciv->model;
		podid = pciv->lifepod_uid;
		garid = pciv->gar_uid;
	}
	DDX_Text(pDX, IDC_FUK1, pciv->ukf[0]);
	DDX_Text(pDX, IDC_FUK2, pciv->ukf[1]);

	DDX_Text(pDX, IDC_UID, uid);
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_MODEL, model);
	DDX_Text(pDX, IDC_OBJ, obj);
	DDX_Text(pDX, IDC_SUK, podid);
	DDX_Text(pDX, IDC_GARID, garid);
	for (int i=0;i<25;i++)
		DDX_Text(pDX, IDC_FACTOR0+i, pciv->factors[i]);
	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		strcpy(pciv->name,name);
		strcpy(pciv->model,model);
		pciv->lifepod_uid = podid;
		pciv->gar_uid = garid;
	}
	CDialog::DoDataExchange(pDX);
}

BOOL CCivDlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	((CEdit *)GetDlgItem(IDC_NAME))->SetLimitText(IGC_NAMEMAX);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CCivDlg::OnClickedOk(void)
{
	CString oldname = pciv->name;
	UpdateData(TRUE);
	CString newname = pciv->name;
	if (oldname != newname)
		GetParent()->UpdateData(TRUE);
	UpdateData(FALSE);
}

void CCivDlg::OnClickedCancel(void)
{
	UpdateData(FALSE);
}
/*
void CCivDlg::OnClickedViewicon(void)
{
	CMDLView dlgmdl;
	CString s;
	GetDlgItemText(IDC_MODEL,s);
	dlgmdl.sFilePath = sArtPath + "\\icon" + s + "bmp.mdl";
	dlgmdl.DoModal();
}

void CCivDlg::OnClickedViewmodel(void)
{
	CMDLView dlgmdl;
	CString s;
	GetDlgItemText(IDC_MODEL,s);
	dlgmdl.sFilePath = sArtPath + "\\" + s + "bmp.mdl";
	dlgmdl.DoModal();
}

void CCivDlg::OnClickedViewhull(void)
{
	CMDLView dlgmdl;
	CString s;
	GetDlgItemText(IDC_MODEL,s);
	dlgmdl.sFilePath = sArtPath + "\\" + s + "hullinfobmp.mdl";
	dlgmdl.DoModal();
}

void CCivDlg::OnClickedViewpanel(void)
{
	CMDLView dlgmdl;
	CString s;
	GetDlgItemText(IDC_MODEL,s);
	dlgmdl.sFilePath = sArtPath + "\\" + s + "loadoutpanebmp.mdl";
	dlgmdl.DoModal();
}

void CCivDlg::OnClickedViewlobby(void)
{
	CMDLView dlgmdl;
	CString s;
	GetDlgItemText(IDC_MODEL,s);
	dlgmdl.sFilePath = sArtPath + "\\" + s + "lobbybmp.mdl";
	dlgmdl.DoModal();
}
*/

BEGIN_MESSAGE_MAP(CCivDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnClickedCancel)
	//ON_BN_CLICKED(IDC_VIEWICON, OnClickedViewicon)
	//ON_BN_CLICKED(IDC_VIEWMODEL, OnClickedViewmodel)
	//ON_BN_CLICKED(IDC_VIEWHULL, OnClickedViewhull)
	//ON_BN_CLICKED(IDC_VIEWPANEL, OnClickedViewpanel)
	//ON_BN_CLICKED(IDC_VIEWLOBBY, OnClickedViewlobby)
	ON_BN_CLICKED(IDC_BGARID, &CCivDlg::OnBnClickedBgarid)
	ON_BN_CLICKED(IDC_BLIFEPOD, &CCivDlg::OnBnClickedBlifepod)
END_MESSAGE_MAP()


// CCivDlg message handlers

void CCivDlg::OnBnClickedBgarid()
{
	if (!pciv) return;
	if (!pcore) return;
	if (!MainUI) return;
	LPARAM p = (LPARAM)pcore->FindStationType(pciv->gar_uid);
	if (p)
		MainUI->SelectPCE(p);
}

void CCivDlg::OnBnClickedBlifepod()
{
	if (!pciv) return;
	if (!pcore) return;
	if (!MainUI) return;
	LPARAM p = (LPARAM)pcore->FindShip(pciv->lifepod_uid);
	if (p)
		MainUI->SelectPCE(p);
}

