// StationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICE.h"
#include "corestruct.h"
#include "StationDlg.h"
#include ".\stationdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CStationDlg dialog

IMPLEMENT_DYNAMIC(CStationDlg, CDialog)
CStationDlg::CStationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStationDlg::IDD, pParent)
{
	pstation = NULL;
	pcore = NULL;
}

CStationDlg::~CStationDlg()
{
}
void CStationDlg::SetIcons(HICON iJumpIcon)
{
	((CButton *)GetDlgItem(IDC_BSUCC))->SetIcon(iJumpIcon);
	((CButton *)GetDlgItem(IDC_BDRONE))->SetIcon(iJumpIcon);

}
void CStationDlg::DoDataExchange(CDataExchange* pDX)
{
	CString name,model,obj,constructor,descr;
	CString todo1 = "";
	int uid,ss0,groupID;

	if (!pstation) return;
	ASSERT(sArtPath != "");

	CButton *cbdock  = (CButton *)CWnd::GetDlgItem(IDC_DOCKABLE);
	CButton *cbisgar = (CButton *)CWnd::GetDlgItem(IDC_ISGAR);
	CButton *cbcapsdock = (CButton *)CWnd::GetDlgItem(IDC_CAPSCANDOCK);
	CButton *cbstartingbase = (CButton *)CWnd::GetDlgItem(IDC_STARTINGBASE);
	CButton *cbbhelium = (CButton *)CWnd::GetDlgItem(IDC_BUILDON_HELIUM);
	CButton *cbbasteriod = (CButton *)CWnd::GetDlgItem(IDC_BUILDON_ASTERIOD);
	CButton *cbburanium = (CButton *)CWnd::GetDlgItem(IDC_BUILDON_URANIUM);
	CButton *cbbsilicon = (CButton *)CWnd::GetDlgItem(IDC_BUILDON_SILICON);
	CButton *cbbcarbon = (CButton *)CWnd::GetDlgItem(IDC_BUILDON_CARBON);
	CButton *cbbthorium = (CButton *)CWnd::GetDlgItem(IDC_BUILDON_THORIUM);

	CComboBox *cbach = (CComboBox *)GetDlgItem(IDC_ACHULL);
	CComboBox *cbashld = (CComboBox *)GetDlgItem(IDC_ACSHLD);

	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		name = pstation->name;
		model = pstation->modelName;
		obj = pstation->iconName;
		descr = pstation->description;
		mdlbmp.LoadMDLFile(sArtPath +"\\"+ obj + "bmp.mdl");
		imdlbmp.LoadMDLFile(sArtPath +"\\i"+ model + "bmp.mdl");
		constructor = pstation->builderName;
		uid = pstation->stationTypeID;
		cbach->SetCurSel(pstation->defenseTypeArmor);
		cbashld->SetCurSel(pstation->defenseTypeShield);
		ss0 = pstation->constructionDroneTypeID;
	//		cbdock->SetCheck((pstation->dockable == 0x10)?BST_CHECKED:BST_UNCHECKED);
	//	cbisgar->SetCheck((pstation->stats_isgar == 1)?BST_CHECKED:BST_UNCHECKED);
		cbbhelium->SetCheck((pstation->aabmBuild & IGCSTATIONF_BUILDON_HELIUM)?BST_CHECKED:BST_UNCHECKED);
		cbbasteriod->SetCheck((pstation->aabmBuild & IGCSTATIONF_BUILDON_ASTERIOD)?BST_CHECKED:BST_UNCHECKED);
		cbburanium->SetCheck((pstation->aabmBuild & IGCSTATIONF_BUILDON_URANIUM)?BST_CHECKED:BST_UNCHECKED);
		cbbsilicon->SetCheck((pstation->aabmBuild & IGCSTATIONF_BUILDON_SILICON)?BST_CHECKED:BST_UNCHECKED);
		cbbcarbon->SetCheck((pstation->aabmBuild & IGCSTATIONF_BUILDON_CARBON)?BST_CHECKED:BST_UNCHECKED);
		cbbthorium->SetCheck((pstation->aabmBuild & IGCSTATIONF_BUILDON_THORIUM)?BST_CHECKED:BST_UNCHECKED);
		for (int i=0;i<IGCSTATION_TYPE_NBVALS;i++)
		{
			if (cbtype->GetItemData(i) == pstation->classID)
			{
				cbtype->SetCurSel(i);
				i = IGCSTATION_TYPE_NBVALS;
			}
		}

		for (int i=0;i<15;i++) 
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
			cbb->SetCheck((pstation->sabmCapabilities & (1L<<i))?BST_CHECKED:BST_UNCHECKED);
		}
		/*
		for (int i=0;i<2;i++) 
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_SSTAT6+i);
			cbb->SetCheck((pstation->stats_flags & (1L<<i))?BST_CHECKED:BST_UNCHECKED);
		}*/
		groupID = pstation->groupID;

	}
	DDX_Text(pDX, IDC_GROUP, groupID);

	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_MODEL, model);
	DDX_Text(pDX, IDC_OBJ, obj);
	DDX_Text(pDX, IDC_CONSTRUCTOR, constructor);
	DDX_Text(pDX, IDC_DESCR, descr);
	DDX_Text(pDX, IDC_UID, uid);
	DDX_Text(pDX, IDC_OVUID, pstation->successorStationTypeID);
	DDX_Text(pDX, IDC_S1, pstation->signature);
	DDX_Text(pDX, IDC_S2, pstation->maxArmorHitPoints);
	DDX_Text(pDX, IDC_S3, pstation->maxShieldHitPoints);
	DDX_Text(pDX, IDC_S4, pstation->armorRegeneration);
	DDX_Text(pDX, IDC_S5, pstation->shieldRegeneration);
	DDX_Text(pDX, IDC_S6, pstation->scannerRange);
	DDX_Text(pDX, IDC_S7, pstation->radius);
	DDX_Text(pDX, IDC_INCOME, pstation->income);
	DDX_Text(pDX, IDC_COST, pstation->price);
	DDX_Text(pDX, IDC_RTIME, pstation->timeToBuild);

	DDX_Text(pDX, IDC_SOUND1, pstation->constructorNeedRockSound);
	DDX_Text(pDX, IDC_SOUND2, pstation->constructorUnderAttackSound);
	DDX_Text(pDX, IDC_SOUND3, pstation->constructorDestroyedSound);
	DDX_Text(pDX, IDC_SOUND4, pstation->completionSound);
	DDX_Text(pDX, IDC_SOUND5, pstation->interiorSound);
	DDX_Text(pDX, IDC_SOUND6, pstation->exteriorSound);
	DDX_Text(pDX, IDC_SOUND7, pstation->interiorAlertSound);
	DDX_Text(pDX, IDC_SOUND8, pstation->underAttackSound);
	DDX_Text(pDX, IDC_SOUND9, pstation->criticalSound);
	DDX_Text(pDX, IDC_SOUND10,pstation->destroyedSound);
	DDX_Text(pDX, IDC_SOUND11,pstation->capturedSound);
	DDX_Text(pDX, IDC_SOUND12,pstation->enemyCapturedSound);
	DDX_Text(pDX, IDC_SOUND13,pstation->enemyDestroyedSound);

	DDX_Text(pDX, IDC_SS0, ss0);

	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		strcpy(pstation->name,name);
		strcpy(pstation->modelName,model);
		strcpy(pstation->iconName,obj);
		strncpy(pstation->description,descr,IGC_DESCRIPTIONMAX);
		mdlbmp.LoadMDLFile(sArtPath +"\\"+ obj + "bmp.mdl");
		imdlbmp.LoadMDLFile(sArtPath +"\\i"+ model + "bmp.mdl");
		strcpy(pstation->builderName,constructor);
		pstation->defenseTypeArmor = cbach->GetCurSel();
		pstation->defenseTypeShield = cbashld->GetCurSel();
		pstation->constructionDroneTypeID = ss0;
		//	pstation->dockable = (cbdock->GetCheck()==BST_CHECKED)?0x10:0;
		// pstation->stats_isgar = (cbisgar->GetCheck()==BST_CHECKED)?1:0;
		pstation->aabmBuild  = (cbbhelium->GetCheck()==BST_CHECKED)?IGCSTATIONF_BUILDON_HELIUM:0;
		pstation->aabmBuild += (cbbasteriod->GetCheck()==BST_CHECKED)?IGCSTATIONF_BUILDON_ASTERIOD:0;
		pstation->aabmBuild += (cbburanium->GetCheck()==BST_CHECKED)?IGCSTATIONF_BUILDON_URANIUM:0;
		pstation->aabmBuild += (cbbsilicon->GetCheck()==BST_CHECKED)?IGCSTATIONF_BUILDON_SILICON:0;
		pstation->aabmBuild += (cbbcarbon->GetCheck()==BST_CHECKED)?IGCSTATIONF_BUILDON_CARBON:0;
		pstation->aabmBuild += (cbbthorium->GetCheck()==BST_CHECKED)?IGCSTATIONF_BUILDON_THORIUM:0;
		pstation->classID = (UCHAR)cbtype->GetItemData(cbtype->GetCurSel());

		pstation->sabmCapabilities = 0;
		for (int i=0;i<15;i++) 
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
			pstation->sabmCapabilities += cbb->GetCheck()?(1<<i):0;
		}
		/*pstation->stats_flags = 0;
		for (int i=0;i<2;i++) 
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_SSTAT6+i);
			pstation->stats_flags += cbb->GetCheck()?(1<<i):0;
		}*/	
		pstation->groupID = groupID;
	}
	CDialog::DoDataExchange(pDX);
}

void CStationDlg::OnClickedDecodesel(void)
{
	CEdit *cetodo = (CEdit *) CWnd::GetDlgItem(IDC_TODO1);
	int i,j;
	cetodo->GetSel(i,j);

	// NT SPECIFIC
   HLOCAL h = cetodo->GetHandle();
   LPCTSTR lpszText = (LPCTSTR)LocalLock(h);
	char res[1000];
	strncpy(res,&(lpszText[i]),j-i);res[j-i] = 0;
	CString sres = res;
	sres.Replace("\r\n","");
	SetDlgItemText(IDC_DECDEC,sres);
	float f;
	unsigned char *pf;
	unsigned int b1,b2,b3,b4;
	pf = (unsigned char *)&f;
	sscanf(sres,"%x %x %x %x",&b1,&b2,&b3,&b4);
	pf[0] = b1;
	pf[1] = b2;
	pf[2] = b3;
	pf[3] = b4;
	sres.Format("%g",f);
	SetDlgItemText(IDC_DECFLOAT,sres);
	
   LocalUnlock(h);
	// END OF NT SPECIFIC
}

void CStationDlg::OnClickedDecodeh(void)
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

BOOL CStationDlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();
	VERIFY(mdlbmp.SubclassDlgItem(IDC_PICT, this));
	VERIFY(imdlbmp.SubclassDlgItem(IDC_PICTI, this));

	CComboBox *cbach = (CComboBox *)GetDlgItem(IDC_ACHULL);
	CComboBox *cbashld = (CComboBox *)GetDlgItem(IDC_ACSHLD);
	cbach->ResetContent();
	cbashld->ResetContent();
	for (int i=0;i<IGCACMAX;i++)
	{
		cbach->AddString(IGCArmorClasses[i]);
		cbashld->AddString(IGCArmorClasses[i]);
	}
	cbtype = (CComboBox *) CWnd::GetDlgItem(IDC_STATIONTYPE);
	for (int i=0;i<IGCSTATION_TYPE_NBVALS;i++)
	{
		int idx = cbtype->AddString(IGCStationTypeNames[i]);
		cbtype->SetItemData(idx,i);
	}

	((CEdit *)GetDlgItem(IDC_DESCR))->SetLimitText(IGC_DESCRIPTIONMAX);
	((CEdit *)GetDlgItem(IDC_NAME))->SetLimitText(IGC_NAMEMAX);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CStationDlg::OnClickedOk(void)
{
	CString oldname = pstation->name;
	UpdateData(TRUE);
	CString newname = pstation->name;
	if (oldname != newname)
		GetParent()->UpdateData(TRUE);
	UpdateData(FALSE);
}

void CStationDlg::OnClickedCancel(void)
{
	UpdateData(FALSE);
}


BEGIN_MESSAGE_MAP(CStationDlg, CDialog)
	ON_BN_CLICKED(IDC_DECODESEL, OnClickedDecodesel)
	ON_BN_CLICKED(IDC_DECODEH, OnClickedDecodeh)
	ON_BN_CLICKED(IDOK, OnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnClickedCancel)
//	ON_BN_CLICKED(IDC_USEM11, OnBnClickedUsem11)
	ON_BN_CLICKED(IDC_USEM0, OnBnClickedUsem0)
	ON_BN_CLICKED(IDC_USEM11, OnBnClickedUsem11)
	ON_BN_CLICKED(IDC_BSUCC, &CStationDlg::OnBnClickedBsucc)
	ON_BN_CLICKED(IDC_BEDITDESCR, &CStationDlg::OnBnClickedBeditdescr)
	ON_BN_CLICKED(IDC_BDRONE, &CStationDlg::OnBnClickedBdrone)
END_MESSAGE_MAP()


// CStationDlg message handlers


void CStationDlg::OnBnClickedUsem0()
{
	// 'Miners can offload'
	CButton *cbTeleU  = (CButton *)CWnd::GetDlgItem(IDC_USEM11);
	CButton *cbU  = (CButton *)CWnd::GetDlgItem(IDC_USEM0);

	if (!cbU->GetCheck())
		cbTeleU->SetCheck(BST_UNCHECKED);
}

void CStationDlg::OnBnClickedUsem11()
{
	// 'Miners can tele offload'
	CButton *cbTeleU  = (CButton *)CWnd::GetDlgItem(IDC_USEM11);
	CButton *cbU  = (CButton *)CWnd::GetDlgItem(IDC_USEM0);

	if (cbTeleU->GetCheck())
		cbU->SetCheck(BST_CHECKED);
}

void CStationDlg::OnBnClickedBsucc()
{
	if (!pstation) return;
	if (!pcore) return;
	if (pstation->successorStationTypeID == -1) return;
	PtrCoreStationType succ = pcore->FindStationType(pstation->successorStationTypeID);
	if (succ)
		MainUI->SelectPCE((LPARAM)succ);
	else
		AfxMessageBox("invalid successor!");
}

void CStationDlg::OnBnClickedBeditdescr()
{
	CDescrDlg dlg(pstation->description);
	if (dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_DESCRIPTION,pstation->description);
}

void CStationDlg::OnBnClickedBdrone()
{
	if (!pstation) return;
	if (!pcore) return;
	PtrCoreDrone pdrone = pcore->FindDrone(pstation->constructionDroneTypeID);
	if (pdrone)
		MainUI->SelectPCE((LPARAM)pdrone);
	else
		AfxMessageBox("invalid drone!");
}
