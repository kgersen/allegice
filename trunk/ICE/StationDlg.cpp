// StationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICE.h"
#include "corestruct.h"
#include "StationDlg.h"
#include ".\stationdlg.h"


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
}
void CStationDlg::DoDataExchange(CDataExchange* pDX)
{
	CString name,model,obj,constructor,descr;
	CString todo1 = "";
	int uid,ss0;
	int sounds[13];
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
		model = pstation->model;
		obj = pstation->icon;
		descr = pstation->description;
		mdlbmp.LoadMDLFile(sArtPath +"\\"+ obj + "bmp.mdl");
		imdlbmp.LoadMDLFile(sArtPath +"\\i"+ model + "bmp.mdl");
		constructor = pstation->constructor;
		uid = pstation->uid;
		cbach->SetCurSel(pstation->ACHull);
		cbashld->SetCurSel(pstation->ACShld);
		ss0 = pstation->stats_ss0;
	//		cbdock->SetCheck((pstation->dockable == 0x10)?BST_CHECKED:BST_UNCHECKED);
	//	cbisgar->SetCheck((pstation->stats_isgar == 1)?BST_CHECKED:BST_UNCHECKED);
		cbbhelium->SetCheck((pstation->buildon & IGCSTATIONF_BUILDON_HELIUM)?BST_CHECKED:BST_UNCHECKED);
		cbbasteriod->SetCheck((pstation->buildon & IGCSTATIONF_BUILDON_ASTERIOD)?BST_CHECKED:BST_UNCHECKED);
		cbburanium->SetCheck((pstation->buildon & IGCSTATIONF_BUILDON_URANIUM)?BST_CHECKED:BST_UNCHECKED);
		cbbsilicon->SetCheck((pstation->buildon & IGCSTATIONF_BUILDON_SILICON)?BST_CHECKED:BST_UNCHECKED);
		cbbcarbon->SetCheck((pstation->buildon & IGCSTATIONF_BUILDON_CARBON)?BST_CHECKED:BST_UNCHECKED);
		cbbthorium->SetCheck((pstation->buildon & IGCSTATIONF_BUILDON_THORIUM)?BST_CHECKED:BST_UNCHECKED);
		for (int i=0;i<IGCSTATION_TYPE_NBVALS;i++)
		{
			if (cbtype->GetItemData(i) == pstation->type)
			{
				cbtype->SetCurSel(i);
				i = IGCSTATION_TYPE_NBVALS;
			}
		}
		for (int i=0;i<13;i++) sounds[i] = pstation->Sounds[i];

		for (int i=0;i<15;i++) 
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
			cbb->SetCheck((pstation->AbilityBitMask & (1L<<i))?BST_CHECKED:BST_UNCHECKED);
		}
		/*
		for (int i=0;i<2;i++) 
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_SSTAT6+i);
			cbb->SetCheck((pstation->stats_flags & (1L<<i))?BST_CHECKED:BST_UNCHECKED);
		}*/

	}
	DDX_Text(pDX, IDC_GROUP, pstation->group);

	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_MODEL, model);
	DDX_Text(pDX, IDC_OBJ, obj);
	DDX_Text(pDX, IDC_CONSTRUCTOR, constructor);
	DDX_Text(pDX, IDC_DESCR, descr);
	DDX_Text(pDX, IDC_UID, uid);
	DDX_Text(pDX, IDC_OVUID, pstation->overriding_uid);
	DDX_Text(pDX, IDC_S1, pstation->stats_s1);
	DDX_Text(pDX, IDC_S2, pstation->stats_s2);
	DDX_Text(pDX, IDC_S3, pstation->stats_s3);
	DDX_Text(pDX, IDC_S4, pstation->stats_s4);
	DDX_Text(pDX, IDC_S5, pstation->stats_s5);
	DDX_Text(pDX, IDC_S6, pstation->stats_s6);
	DDX_Text(pDX, IDC_S7, pstation->stats_s7);
	DDX_Text(pDX, IDC_INCOME, pstation->stats_income);
	DDX_Text(pDX, IDC_COST, pstation->cost);
	DDX_Text(pDX, IDC_RTIME, pstation->research_time);

	DDX_Text(pDX, IDC_SOUND1, sounds[0]);
	DDX_Text(pDX, IDC_SOUND2, sounds[1]);
	DDX_Text(pDX, IDC_SOUND3, sounds[2]);
	DDX_Text(pDX, IDC_SOUND4, sounds[3]);
	DDX_Text(pDX, IDC_SOUND5, sounds[4]);
	DDX_Text(pDX, IDC_SOUND6, sounds[5]);
	DDX_Text(pDX, IDC_SOUND7, sounds[6]);
	DDX_Text(pDX, IDC_SOUND8, sounds[7]);
	DDX_Text(pDX, IDC_SOUND9, sounds[8]);
	DDX_Text(pDX, IDC_SOUND10, sounds[9]);
	DDX_Text(pDX, IDC_SOUND11, sounds[10]);
	DDX_Text(pDX, IDC_SOUND12, sounds[11]);
	DDX_Text(pDX, IDC_SOUND13, sounds[12]);

	DDX_Text(pDX, IDC_SS0, ss0);

	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		strcpy(pstation->name,name);
		strcpy(pstation->model,model);
		strcpy(pstation->icon,obj);
		strncpy(pstation->description,descr,IGC_DESCRIPTIONMAX);
		mdlbmp.LoadMDLFile(sArtPath +"\\"+ obj + "bmp.mdl");
		imdlbmp.LoadMDLFile(sArtPath +"\\i"+ model + "bmp.mdl");
		strcpy(pstation->constructor,constructor);
		pstation->ACHull = cbach->GetCurSel();
		pstation->ACShld = cbashld->GetCurSel();
		for (int i=0;i<13;i++)	 pstation->Sounds[i] = sounds[i];
		pstation->stats_ss0 = ss0;
		//	pstation->dockable = (cbdock->GetCheck()==BST_CHECKED)?0x10:0;
		// pstation->stats_isgar = (cbisgar->GetCheck()==BST_CHECKED)?1:0;
		pstation->buildon  = (cbbhelium->GetCheck()==BST_CHECKED)?IGCSTATIONF_BUILDON_HELIUM:0;
		pstation->buildon += (cbbasteriod->GetCheck()==BST_CHECKED)?IGCSTATIONF_BUILDON_ASTERIOD:0;
		pstation->buildon += (cbburanium->GetCheck()==BST_CHECKED)?IGCSTATIONF_BUILDON_URANIUM:0;
		pstation->buildon += (cbbsilicon->GetCheck()==BST_CHECKED)?IGCSTATIONF_BUILDON_SILICON:0;
		pstation->buildon += (cbbcarbon->GetCheck()==BST_CHECKED)?IGCSTATIONF_BUILDON_CARBON:0;
		pstation->buildon += (cbbthorium->GetCheck()==BST_CHECKED)?IGCSTATIONF_BUILDON_THORIUM:0;
		pstation->type = (UCHAR)cbtype->GetItemData(cbtype->GetCurSel());

		pstation->AbilityBitMask = 0;
		for (int i=0;i<15;i++) 
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
			pstation->AbilityBitMask += cbb->GetCheck()?(1<<i):0;
		}
		/*pstation->stats_flags = 0;
		for (int i=0;i<2;i++) 
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_SSTAT6+i);
			pstation->stats_flags += cbb->GetCheck()?(1<<i):0;
		}*/	

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
	if (pstation->overriding_uid == -1) return;
	PtrCoreStationType succ = pcore->FindStationType(pstation->overriding_uid);
	if (succ)
		MainUI->SelectPCE((LPARAM)succ);
	else
		AfxMessageBox("invalid successor!");
}
