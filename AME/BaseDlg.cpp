// BaseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AGM.h"
#include "IGCMap.h"
#include "ColorButton.h"
#include "BaseDlg.h"

// CBaseDlg dialog

IMPLEMENT_DYNAMIC(CBaseDlg, CDialog)
CBaseDlg::CBaseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBaseDlg::IDD, pParent)
{
}

CBaseDlg::~CBaseDlg()
{

}

void CBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CString name,type_name,faction_name;
	int stationtype,team;
	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		name  = curbase->igcbase.name;
		stationtype = curbase->igcbase.igcstationtype;
		team = curbase->igcbase.team;
		type_name = pcore->GetBaseName(stationtype);
		faction_name = pcore->GetBaseCivName(stationtype);
	}
	DDX_CBIndex(pDX, IDC_BASE_TEAM, team);
	DDX_Text(pDX, IDC_BASE_NAME, name);
	DDX_Text(pDX, IDC_BASE_POSX, curbase->igcbase.posx);
	DDX_Text(pDX, IDC_BASE_POSY, curbase->igcbase.posy);
	DDX_Text(pDX, IDC_BASE_POSZ, curbase->igcbase.posz);
	DDX_Text(pDX, IDC_BASE_O1X, curbase->igcbase.O1x);
	DDX_Text(pDX, IDC_BASE_O1Y, curbase->igcbase.O1y);
	DDX_Text(pDX, IDC_BASE_O1Z, curbase->igcbase.O1z);
	DDX_Text(pDX, IDC_BASE_O2X, curbase->igcbase.O2x);
	DDX_Text(pDX, IDC_BASE_O2Y, curbase->igcbase.O2y);
	DDX_Text(pDX, IDC_BASE_O2Z, curbase->igcbase.O2z);
	DDX_Text(pDX, IDC_BASE_SPIN_SPEED, curbase->igcbase.spinspeed);
	DDX_Text(pDX, IDC_BASE_SPINX, curbase->igcbase.spinX);
	DDX_Text(pDX, IDC_BASE_SPINY, curbase->igcbase.spinY);
	DDX_Text(pDX, IDC_BASE_SPINZ, curbase->igcbase.spinZ);
	DDX_Text(pDX, IDC_BASE_TYPE, stationtype);
	DDX_Text(pDX, IDC_BASE_TYPENAME, type_name);
	DDX_Text(pDX, IDC_BASE_FACTION, faction_name);

	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		strncpy(curbase->igcbase.name,name,sizeof(curbase->igcbase.name));
		curbase->igcbase.igcstationtype = stationtype;
		curbase->igcbase.team = team;
	}

	CDialog::DoDataExchange(pDX);
}

BOOL CBaseDlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CBaseDlg::OnClickedDelete(void)
{
	// should confirm
	EndDialog(IDDELETE);
}

afx_msg void CBaseDlg::OnBaseChange( UINT nID )
{
	SetDlgItemInt(IDC_BASE_TYPE,nID-DYNMENUSID);
	SetDlgItemText(IDC_BASE_TYPENAME,pcore->GetBaseName(nID-DYNMENUSID));
	SetDlgItemText(IDC_BASE_NAME,pcore->GetBaseName(nID-DYNMENUSID));
	SetDlgItemText(IDC_BASE_FACTION,pcore->GetBaseCivName(nID-DYNMENUSID));
}

void CBaseDlg::OnClickedBaseSettype(void)
{
	CButton *cb = (CButton *)CWnd::GetDlgItem(IDC_BASE_SETTYPE);
	CRect rect;
	cb->GetWindowRect(&rect);
	pcore->mBasesMenu.TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, rect.left, rect.top, this);
}
BEGIN_MESSAGE_MAP(CBaseDlg, CDialog)
	ON_BN_CLICKED(IDDELETE, OnClickedDelete)
	ON_COMMAND_RANGE(DYNMENUSID, DYNMENUSID+1000, OnBaseChange)
	ON_BN_CLICKED(IDC_BASE_SETTYPE, OnClickedBaseSettype)
END_MESSAGE_MAP()


