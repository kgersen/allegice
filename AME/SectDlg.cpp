// SectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AGM.h"
#include "IGCMap.h"
#include "ColorButton.h"
#include "BMPMDLButton.h"
#include "SectDlg.h"
#include "MDLFile.h"

// CSectDlg dialog

IMPLEMENT_DYNAMIC(CSectDlg, CDialog)
CSectDlg::CSectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSectDlg::IDD, pParent)
{
	bTplMode = false;
}

CSectDlg::~CSectDlg()
{
}

void CSectDlg::DoDataExchange(CDataExchange* pDX)
{
	float x,y,z;
	CString nebbg,globe,name,team;
	if (!cursect)
		return;
	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		nebbg = cursect->igcsector.nebbg;
		globe = cursect->igcsector.globe;
		name  = cursect->igcsector.name;
		team.Format("%d",cursect->igcsector.team);
		x = cursect->igcsector.LightX;
		y = cursect->igcsector.LightY;
		z = cursect->igcsector.LightZ;
		PlanetBmp.LoadMDLFile(sArtPath + "\\" + nebbg +".mdl");

		DDX_CBString(pDX, IDC_SECT_GLOBE, globe);
		CComboBox *cbglobe = (CComboBox *) CWnd::GetDlgItem(IDC_SECT_GLOBE);
		if (cbglobe->GetCurSel() == CB_ERR)
		{
			cbglobe->SetCurSel(cbglobe->GetCount()-1);
		}
		
		DDX_CBString(pDX, IDC_SECT_NEBBG, nebbg);
		CComboBox* cbnebp = (CComboBox*)CWnd::GetDlgItem(IDC_SECT_NEBBG);
		if (cbnebp->GetCurSel() == CB_ERR)
		{
			cbnebp->SetCurSel(cbnebp->GetCount() - 1);
		}
	}
	DDX_Text(pDX, IDC_SECT_NEBBGNAME, nebbg);
	DDX_Text(pDX, IDC_SECT_GLOBENAME, globe);
	DDX_CBString(pDX, IDC_SECT_TEAM, team);
	DDX_Text(pDX, IDC_SECT_NAME, name);
	DDX_Text(pDX, IDC_SECT_POSX, cursect->igcsector.posx);
	DDX_Text(pDX, IDC_SECT_POSY, cursect->igcsector.posy);
	DDX_Text(pDX, IDC_SECT_PLLAT,cursect->igcsector.PlanetSinPct);
	DDX_Text(pDX, IDC_SECT_PLLONG,cursect->igcsector.PlanetLonPct);
	DDX_Text(pDX, IDC_SECT_PLRADIUS,cursect->igcsector.PanetRadius);
	DDX_Text(pDX, IDC_SECT_LITEX,x);
	DDX_Text(pDX, IDC_SECT_LITEY,y);
	DDX_Text(pDX, IDC_SECT_LITEZ,z);
	DDX_Text(pDX, IDC_SECT_DEBRISC,cursect->igcsector.debrisCount);
	DDX_Text(pDX, IDC_SECT_STARSC,cursect->igcsector.starCount);
	DDX_Text(pDX, IDC_SECT_STARSEED, cursect->igcsector.starSeed);

	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		strncpy(cursect->igcsector.nebbg,nebbg,sizeof(cursect->igcsector.nebbg));
		strncpy(cursect->igcsector.globe,globe,sizeof(cursect->igcsector.globe));
		strncpy(cursect->igcsector.name,name,sizeof(cursect->igcsector.name));
		cursect->igcsector.team = atoi(team);
		cursect->igcsector.LightColor = LightColor.toIGCColor();
		if (cursect->igcsector.PlanetSinPct > 100)
		{
			cursect->igcsector.PlanetSinPct = 100;
		}
		if (cursect->igcsector.PlanetLonPct > 100)
		{
			cursect->igcsector.PlanetLonPct = 100;
		}
		// Normalize light direction
		float norm = sqrtf(	x*x +	y*y +	z*z);
		if (!norm)
		{
			AfxMessageBox("Invalid light direction ! (null norm)\nResetting to default direction");
			cursect->igcsector.LightX = 1.0f;
			cursect->igcsector.LightY = -1.0f;
			cursect->igcsector.LightZ = 1.0f;
		}
		else
		{
			cursect->igcsector.LightX = x / norm;
			cursect->igcsector.LightY = y / norm;
			cursect->igcsector.LightZ = z / norm;
		}
	}

	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSectDlg, CDialog)
	ON_BN_CLICKED(IDC_SECT_LightColor, OnClickedSectLightColor)
	ON_BN_CLICKED(ID_MAP_S_APPLY, OnClickedMapSApply)
	ON_BN_CLICKED(ID_MAP_S_DELETE, OnClickedMapSDelete)
	ON_BN_CLICKED(ID_SDLG_CANCEL, OnClickedSdlgCancel)
	ON_CBN_SELCHANGE(IDC_SECT_NEBBG, OnCbnSelchangeSectNebbg)
	ON_CBN_SELCHANGE(IDC_SECT_GLOBE, OnCbnSelchangeSectGlobe)
END_MESSAGE_MAP()


// CSectDlg message handlers
BOOL CSectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// subclass buttons created with res editor
	VERIFY(LightColor.SubclassDlgItem(IDC_SECT_LightColor, this));
	VERIFY(PlanetBmp.SubclassDlgItem(IDC_PLANET, this));

	LightColor.ChangeColor(cursect->igcsector.LightColor.red,cursect->igcsector.LightColor.green,cursect->igcsector.LightColor.blue);

	// fill in the ComnBoxes
	CComboBox *cbglobe = (CComboBox *) CWnd::GetDlgItem(IDC_SECT_GLOBE);
	CComboBox *cbneb = (CComboBox *) CWnd::GetDlgItem(IDC_SECT_NEBBG);
	CComboBox *cbteam = (CComboBox *) CWnd::GetDlgItem(IDC_SECT_TEAM);
	if (bTplMode)
	{
		SetWindowText("Sector defaults");
		SetDlgItemText(ID_MAP_S_APPLY,"Save");
		SetDlgItemText(ID_MAP_S_DELETE,"Apply to all");
		SetDlgItemText(ID_SDLG_CANCEL,"Close");
		cbneb->AddString("Random");
		cbglobe->AddString("Random");
		cbteam->ShowWindow(SW_HIDE);
		CWnd *t = CWnd::GetDlgItem(IDC_SECT_NAME);
		t->ShowWindow(SW_HIDE);
		t = CWnd::GetDlgItem(IDC_S_Team);
		t->ShowWindow(SW_HIDE);
		t = CWnd::GetDlgItem(IDC_S_Name);
		t->ShowWindow(SW_HIDE);
		t = CWnd::GetDlgItem(IDC_SECT_POSX);
		t->ShowWindow(SW_HIDE);
		t = CWnd::GetDlgItem(IDC_S_PosX);
		t->ShowWindow(SW_HIDE);
		t = CWnd::GetDlgItem(IDC_SECT_POSY);
		t->ShowWindow(SW_HIDE);
		t = CWnd::GetDlgItem(IDC_S_PosY);
		t->ShowWindow(SW_HIDE);
		t = NULL;
	}
	else
	{
		SetWindowText("Sector properties");
		SetDlgItemText(ID_MAP_S_APPLY,"Apply");
		SetDlgItemText(ID_MAP_S_DELETE,"Delete");
		SetDlgItemText(ID_SDLG_CANCEL,"Cancel");
	}
	for (int i=0;i<9;i++)
	{
		CString buff;
		buff.Format("globe%d",i+1);
		cbglobe->AddString(buff);
	}
	cbglobe->AddString("custom model");
	for (int i=0;i<ICGBASE_NEBPLNT;i++)
	{
		cbneb->AddString(IGCNebplnt[i]);
	}
	cbneb->AddString("custom bitmap");

	for (int i=0;i<7;i++)
	{
		CString buff;
		buff.Format("%d",i);
		cbteam->AddString(buff);
	}

	UpdateData(FALSE); // perform DDX
	return TRUE;
}

void CSectDlg::OnClickedSectLightColor(void)
{
	LightColor.ChangeColor();
}

void CSectDlg::OnClickedMapSApply(void)
{
	UpdateData(TRUE);
	EndDialog(S_OK);
}

void CSectDlg::OnClickedMapSDelete(void) // delete sector
{
	if (bTplMode)
		UpdateData(TRUE);
	EndDialog(S_SECTOR_DELETE);
}

void CSectDlg::OnClickedSdlgCancel(void)
{
	EndDialog(S_SECTOR_CANCEL);
}

void CSectDlg::OnCbnSelchangeSectNebbg()
{
	CString nebbg;
	CComboBox* cbneb = (CComboBox*)CWnd::GetDlgItem(IDC_SECT_NEBBG);

	if (cbneb->GetCurSel() == (cbneb->GetCount() - 1)) // last = custom
	{
		CString startpath = sArtPath + "\\*.mdl";
		CFileDialog cfd(TRUE, "mdl", startpath, OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR | OFN_NONETWORKBUTTON, "Allegiance bitmap|*bmp.mdl|", this, OPENFILENAME_SIZE_VERSION_400);
		if (cfd.DoModal() == IDOK)
		{

			nebbg = cfd.GetFileTitle();
			if (nebbg.GetLength() > 12)
			{
				AfxMessageBox("'" + nebbg + "' bitmap name is too long (max 12 cars)");
				return;
			}
			CMDLFile mdlfile;
			if (!mdlfile.ReadFromFile(cfd.GetPathName()))
			{
				AfxMessageBox("error opening bitmap file '" + cfd.GetFileName() + "'");
				return;
			}
			if (mdlfile.RootObject)
				if (mdlfile.RootObject->type != mdl_image)
				{
					AfxMessageBox("invalid bitmap file '" + cfd.GetFileName() + "'");
					return;
				}
		}
	}
	else
	{
		cbneb->GetLBText(cbneb->GetCurSel(), nebbg);
	}
	SetDlgItemText(IDC_SECT_NEBBGNAME, nebbg);
	PlanetBmp.LoadMDLFile(sArtPath + "\\" + nebbg + ".mdl");
	PlanetBmp.Invalidate(TRUE);
}

void CSectDlg::OnCbnSelchangeSectGlobe()
{
	CComboBox *cbglobe = (CComboBox *) CWnd::GetDlgItem(IDC_SECT_GLOBE);

	if (cbglobe->GetCurSel() == (cbglobe->GetCount()-1)) // last = custom
	{
		CString startpath = sArtPath + "\\*.mdl";
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
					SetDlgItemText(IDC_SECT_GLOBENAME,render);
					return;
				}
			AfxMessageBox("invalid 3d model file '"+cfd.GetFileName()+"'");
		}

	}
	else
	{
		CString r;
		cbglobe->GetLBText(cbglobe->GetCurSel(),r);
		SetDlgItemText(IDC_SECT_GLOBENAME,r);
	}

}
