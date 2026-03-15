// RockDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AGM.h"
#include "IGCMap.h"
#include "ColorButton.h"
#include "RockDlg.h"
#include "MDLFile.h"

// CRockDlg dialog

IMPLEMENT_DYNAMIC(CRockDlg, CDialog)
CRockDlg::CRockDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRockDlg::IDD, pParent)
	, currock(NULL)
{
}

CRockDlg::~CRockDlg()
{
}

void CRockDlg::DoDataExchange(CDataExchange* pDX)
{

	CString name,render,icon;
	BOOL namehidden,phantom,gauge;
	int radius;
	BOOL f1,f4,f8,f16,f32,f64;
	CComboBox *cbrender = (CComboBox *) CWnd::GetDlgItem(IDC_ROCK_RENDER);
	CEdit *cerendermodel = (CEdit *)  CWnd::GetDlgItem(IDC_ROCK_CUSTOM_MODEL);

	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		if (currock->igcrock.name[0] == 0)
		{
			name = &(currock->igcrock.name[1]);
			namehidden = TRUE;
		}
		else
		{
			name = currock->igcrock.name;
			namehidden = FALSE;
		}
		phantom = (currock->igcrock.dispandhp)?FALSE:TRUE;
		gauge = (currock->igcrock.dispandhp & 0xF)?FALSE:TRUE;
		icon   = currock->igcrock.iconbmp;
		// render & custom render part
		render = currock->igcrock.renderbmp;

		if (strncmp(render,"bgrnd",strlen("bgrnd")))
		{
			cbrender->SetCurSel(IGCMAXROCKRENDERS);
		}
		else
		{
			DDX_CBString(pDX, IDC_ROCK_RENDER, render);
		}

		// end of render & custom render part
		radius = currock->igcrock.radius;
		f1 = f4 = f8 = f16 = f32 = f64 = FALSE;
		if (currock->igcrock.flags & 1) f1 = TRUE;
		if (currock->igcrock.flags & 8) f8 = TRUE;
		if (currock->igcrock.flags & 4) f4 = TRUE;
		if (currock->igcrock.flags & 16) f16 = TRUE;
		if (currock->igcrock.flags & 32) f32 = TRUE;
		if (currock->igcrock.flags & 64) f64 = TRUE;
		ShowHeVals(currock->igcrock.flags & 1);

	}
	DDX_Text(pDX, IDC_ROCK_CUSTOM_MODEL, render);

	DDX_Check(pDX, IDC_ROCK_GAUGE,gauge);
	DDX_Check(pDX, IDC_ROCK_PHANTOM,phantom);
	DDX_Check(pDX, IDC_ROCK_F1,f1);
	DDX_Check(pDX, IDC_ROCK_F8,f8);
	DDX_Check(pDX, IDC_ROCK_F4,f4);
	DDX_Check(pDX, IDC_ROCK_F16,f16);
	DDX_Check(pDX, IDC_ROCK_F32,f32);
	DDX_Check(pDX, IDC_ROCK_F64,f64);
	DDX_Check(pDX, IDC_ROCK_NHIDDEN,namehidden);
	DDX_Text(pDX, IDC_ROCK_NAME, name);
	DDX_CBString(pDX, IDC_ROCK_ICON, icon);
	DDX_Text(pDX, IDC_ROCK_POSX, currock->igcrock.posx);
	DDX_Text(pDX, IDC_ROCK_POSY, currock->igcrock.posy);
	DDX_Text(pDX, IDC_ROCK_POSZ, currock->igcrock.posz);
	DDX_Text(pDX, IDC_ROCK_O1X, currock->igcrock.O1x);
	DDX_Text(pDX, IDC_ROCK_O1Y, currock->igcrock.O1y);
	DDX_Text(pDX, IDC_ROCK_O1Z, currock->igcrock.O1z);
	DDX_Text(pDX, IDC_ROCK_O2X, currock->igcrock.O2x);
	DDX_Text(pDX, IDC_ROCK_O2Y, currock->igcrock.O2y);
	DDX_Text(pDX, IDC_ROCK_O2Z, currock->igcrock.O2z);
	DDX_Text(pDX, IDC_ROCK_SPIN_SPEED, currock->igcrock.spinspeed);
	DDX_Text(pDX, IDC_ROCK_SPINX, currock->igcrock.spinX);
	DDX_Text(pDX, IDC_ROCK_SPINY, currock->igcrock.spinY);
	DDX_Text(pDX, IDC_ROCK_SPINZ, currock->igcrock.spinZ);
	DDX_Text(pDX, IDC_ROCK_RADIUS, radius);
	DDX_Text(pDX, IDC_ROCK_SIG, currock->igcrock.sig);
	DDX_Text(pDX, IDC_ROCK_HP, currock->igcrock.hitpoints);
	DDX_Text(pDX, IDC_ROCK_HE1, currock->igcrock.ore);
	DDX_Text(pDX, IDC_ROCK_HE2, currock->igcrock.oreMax);
	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		if (namehidden)
		{
			currock->igcrock.name[0] = 0;
			strncpy(&(currock->igcrock.name[1]),name,sizeof(currock->igcrock.name)-1);
		}
		else
		{
			strncpy(currock->igcrock.name,name,sizeof(currock->igcrock.name));
		}
		strncpy(currock->igcrock.iconbmp,icon,sizeof(currock->igcrock.iconbmp));
		currock->igcrock.radius = radius;
		currock->igcrock.flags = (f1?1:0)+(f4?4:0)+(f8?8:0)+(f16?16:0)+(f32?32:0)+(f64?64:0);
		if (phantom)
		{
			currock->igcrock.dispandhp = 0;
		}
		else
		{
			currock->igcrock.dispandhp = gauge?0xF0:0xF1;
		}
		strncpy(currock->igcrock.renderbmp,render,sizeof(currock->igcrock.renderbmp));
	}


	CDialog::DoDataExchange(pDX);
}

BOOL CRockDlg::OnInitDialog(void)
{
	//CComboBox *cbrendercust = (CComboBox *) CWnd::GetDlgItem(IDC_ROCK_RENDER_CUSTOM);
	//pcore->BuildRenders(cbrendercust);

	CDialog::OnInitDialog();


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CRockDlg::OnSelchangeRockRender(void)
{
	// TODO: handle custom
	CComboBox *cbrender = (CComboBox *) CWnd::GetDlgItem(IDC_ROCK_RENDER);

	if (cbrender->GetCurSel() == IGCMAXROCKRENDERS)
	{
		CString startpath = cArtPath + "\\*.mdl";
		CFileDialog cfd(TRUE,"mdl",startpath,OFN_FILEMUSTEXIST|OFN_NOCHANGEDIR|OFN_NONETWORKBUTTON,"Allegiance Model|*.mdl|",this,OPENFILENAME_SIZE_VERSION_400);
		if (cfd.DoModal() == IDOK)
		{
			CString render = cfd.GetFileTitle();
			if (render.GetLength()>12)
			{
				AfxMessageBox("'"+render+"'model name is too long (max 12 cars)");
				return;
			}
			CMDLFile mdlfile;
			if (!mdlfile.ReadFromFile(cfd.GetPathName()))
			{
				AfxMessageBox("error opening model file '"+cfd.GetFileName()+"'");
				return;
			}
			if (mdlfile.RootObject)
				if (mdlfile.RootObject->type != mdl_image)
				{
					SetDlgItemText(IDC_ROCK_CUSTOM_MODEL,render);
					return;
				}
			AfxMessageBox("invalid 3d model file '"+cfd.GetFileName()+"'");
		}
	}
	else
	{
		CString r;
		cbrender->GetLBText(cbrender->GetCurSel(),r);
		SetDlgItemText(IDC_ROCK_CUSTOM_MODEL,r);
	}
}

void CRockDlg::SetFlags(unsigned short f)
{
	CButton *cb1   = (CButton *) CWnd::GetDlgItem(IDC_ROCK_F1);
	CButton *cb4   = (CButton *) CWnd::GetDlgItem(IDC_ROCK_F4);
	CButton *cb8   = (CButton *) CWnd::GetDlgItem(IDC_ROCK_F8);
	CButton *cb16  = (CButton *) CWnd::GetDlgItem(IDC_ROCK_F16);
	CButton *cb32  = (CButton *) CWnd::GetDlgItem(IDC_ROCK_F32);
	CButton *cb64  = (CButton *) CWnd::GetDlgItem(IDC_ROCK_F64);

	if (f & 1) cb1->SetCheck(BST_CHECKED); else cb1->SetCheck(BST_UNCHECKED);
	if (f & 4) cb4->SetCheck(BST_CHECKED); else cb4->SetCheck(BST_UNCHECKED);
	if (f & 8) cb8->SetCheck(BST_CHECKED); else cb8->SetCheck(BST_UNCHECKED);
	if (f & 16) cb16->SetCheck(BST_CHECKED); else cb16->SetCheck(BST_UNCHECKED);
	if (f & 32) cb32->SetCheck(BST_CHECKED); else cb32->SetCheck(BST_UNCHECKED);
	if (f & 64) cb64->SetCheck(BST_CHECKED); else cb64->SetCheck(BST_UNCHECKED);
	ShowHeVals(f&1);
}

void CRockDlg::ShowHeVals(bool onoff)
{
	CEdit   *cehe1 = (CEdit *)   CWnd::GetDlgItem(IDC_ROCK_HE1);
	CEdit   *cehe2 = (CEdit *)   CWnd::GetDlgItem(IDC_ROCK_HE2);
	CWnd	*celhe1 = CWnd::GetDlgItem(IDC_ROCK_HE1capt);
	CWnd	*celhe2 = CWnd::GetDlgItem(IDC_ROCK_HE2capt);
	if (onoff)
	{
		cehe1->ShowWindow(SW_SHOWNA);
		cehe2->ShowWindow(SW_SHOWNA);
		celhe1->ShowWindow(SW_SHOWNA);
		celhe2->ShowWindow(SW_SHOWNA);
	}
	else
	{
		cehe1->ShowWindow(SW_HIDE);
		cehe2->ShowWindow(SW_HIDE);
		celhe1->ShowWindow(SW_HIDE);
		celhe2->ShowWindow(SW_HIDE);
	}
}

void CRockDlg::OnSelchangeRockTemplate(void)
{
	// TODO: Add your control notification handler code here
	CComboBox *cbtpl = (CComboBox *) CWnd::GetDlgItem(IDC_ROCK_TEMPLATE);
	// Asteriod;Helium;Uranium;Silicon;Carbon;
	CComboBox *cbicon = (CComboBox *) CWnd::GetDlgItem(IDC_ROCK_ICON);
	// 0=meteoricon;1=heliumrock;2=carbonrock;3=copperrock;4=goldrock;5=hotrock;6=waterrock;
	CComboBox *cbrender = (CComboBox *) CWnd::GetDlgItem(IDC_ROCK_RENDER);
	CButton *cbhide = (CButton *)CWnd::GetDlgItem(IDC_ROCK_NHIDDEN);
	CButton *cbp = (CButton *)CWnd::GetDlgItem(IDC_ROCK_PHANTOM);
	CButton *cbg  = (CButton *)CWnd::GetDlgItem(IDC_ROCK_GAUGE);

// asteriod = bgrnd03 = 0 / meteoricon = 0
// asteriod = bgrnd05 = 2 / meteoricon = 0
// helium   = bgrnd56 = 9 / heliumrock = 1
// uranium  = bgrnd51 = 4 / hotrock    = 5
// silicon  = bgrnd52 = 5 / copperrock = 3
// carbon   = bgrnd53 = 6 / carbonrock = 2
// thorium  = bgrnd55 = 8 / goldrock = 4
	CString name;
	name.Format("%d",currock->igcrock.uid);
	cbp->SetCheck(BST_UNCHECKED);
	cbg->SetCheck(BST_CHECKED);
	switch (cbtpl->GetCurSel())
	{
		case 0: // Asteriod
			SetFlags(8);
			cbicon->SetCurSel(0);
			cbrender->SetCurSel((rand()>(RAND_MAX/2))?0:2);
			name.Insert(0,'A');
			cbhide->SetCheck(BST_CHECKED);
			cbg->SetCheck(BST_UNCHECKED);
			break;
		case 1: // Helium
			SetFlags(1);
			cbicon->SetCurSel(1);
			cbrender->SetCurSel(9);
			name.Insert(0,"He");
			cbhide->SetCheck(BST_UNCHECKED);
			break;
		case 2: // Uranium
			SetFlags(16);
			cbicon->SetCurSel(5); // hotrock
			cbrender->SetCurSel(4);
			name.Insert(0,'U');
			cbhide->SetCheck(BST_UNCHECKED);
			break;
		case 3: // Silicon
			SetFlags(32);
			cbicon->SetCurSel(3); // copperrock
			cbrender->SetCurSel(5);
			name.Insert(0,"Si");
			cbhide->SetCheck(BST_UNCHECKED);
			break;
		case 4: // Carbon
			SetFlags(64);
			cbicon->SetCurSel(2); //carbonrock
			cbrender->SetCurSel(6);
			name.Insert(0,'C');
			cbhide->SetCheck(BST_UNCHECKED);
			break;
		case 5: // Thorium
			SetFlags(4);
			cbicon->SetCurSel(4); //goldrock
			cbrender->SetCurSel(8);
			name.Insert(0,'T');
			cbhide->SetCheck(BST_UNCHECKED);
			break;
	}
	SetDlgItemText(IDC_ROCK_NAME,name);
	OnSelchangeRockRender();
}

void CRockDlg::OnClickF1(void)
{
	CButton *cbf1 = (CButton *)CWnd::GetDlgItem(IDC_ROCK_F1);
	ShowHeVals(cbf1->GetCheck()==BST_CHECKED?true:false);
}

void CRockDlg::OnClickPhantom(void)
{
	CButton *cbp = (CButton *)CWnd::GetDlgItem(IDC_ROCK_PHANTOM);
	CButton *cbg  = (CButton *)CWnd::GetDlgItem(IDC_ROCK_GAUGE);

	if (cbp->GetCheck()==BST_CHECKED)
		cbg->SetCheck(BST_CHECKED);
}

BEGIN_MESSAGE_MAP(CRockDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_ROCK_RENDER, OnSelchangeRockRender)
	ON_CBN_SELCHANGE(IDC_ROCK_TEMPLATE, OnSelchangeRockTemplate)
	ON_BN_CLICKED(IDC_ROCK_F1,OnClickF1)
	ON_BN_CLICKED(IDC_ROCK_PHANTOM,OnClickPhantom)
END_MESSAGE_MAP()
