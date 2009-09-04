// ChaffDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICE.h"
#include "corestruct.h"
#include "ChaffDlg.h"
#include ".\chaffdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CChaffDlg dialog

IMPLEMENT_DYNAMIC(CChaffDlg, CDialog)
CChaffDlg::CChaffDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChaffDlg::IDD, pParent)
{
	pcounter = NULL;
}

CChaffDlg::~CChaffDlg()
{
}
void CChaffDlg::SetIcons(HICON iJumpIcon)
{
	((CButton *)GetDlgItem(IDC_BSUCC))->SetIcon(iJumpIcon);
}
void CChaffDlg::DoDataExchange(CDataExchange* pDX)
{
	CString name,model,model2,type,icon,descr,ukbmp,invline;
	//CString todo1 = "";
	int uid,usemask;
	if (!pcounter) return;
	PtrCoreLauncher pl= pcore->GetLauncher(pcounter->expendabletypeID);
	int uidprox = pl->partID;

	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		name = pcounter->launcherDef.name;
		model = pcounter->launcherDef.modelName;
		model2 = pcounter->modelName;
		descr = pcounter->launcherDef.description;
		icon = pcounter->textureName;
		type = pcounter->launcherDef.iconName;
		ukbmp = pcounter->iconName;
		uid = pcounter->expendabletypeID;
		usemask = pcounter->launcherDef.partMask;

		mdlbmp2.LoadMDLFile(sArtPath +"\\"+ type + "bmp.mdl");
		mdlbmp.LoadMDLFile(sArtPath +"\\l"+ model + "bmp.mdl");
		mdlbmp3.LoadMDLFile(sArtPath +"\\"+ ukbmp + "bmp.mdl");

		for (int i=0;i<16;i++) 
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
			cbb->SetCheck((usemask & (1<<i))?BST_CHECKED:BST_UNCHECKED);
			cbb->EnableWindow(TRUE);
		}
		OnBnClickedUsem0();

		CComboBox *cbac = (CComboBox *)GetDlgItem(IDC_AC);
		cbac->SetCurSel(pcounter->defenseType);

		invline = pl->inventoryLineMDL;
	}
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_MODEL, model);
	DDX_Text(pDX, IDC_MODEL2, model2);
	DDX_Text(pDX, IDC_ICONE, icon);
	DDX_Text(pDX, IDC_TYPE, type);
	DDX_Text(pDX, IDC_UKBMP, ukbmp);
	DDX_Text(pDX, IDC_DESCRIPTION, descr);

	DDX_Text(pDX, IDC_S1, pcounter->radius);
	DDX_Text(pDX, IDC_S2, pcounter->rotation);
	DDX_Text(pDX, IDC_S3, pcounter->loadTime);
	DDX_Text(pDX, IDC_S4, pcounter->lifespan);
	DDX_Text(pDX, IDC_S5, pcounter->signature);
	DDX_Text(pDX, IDC_S6, pcounter->launcherDef.price);
	DDX_Text(pDX, IDC_S7, pcounter->launcherDef.timeToBuild);
	DDX_Text(pDX, IDC_S8, pcounter->launcherDef.signature);
	DDX_Text(pDX, IDC_S9, pcounter->launcherDef.mass);
	DDX_Text(pDX, IDC_S10, pcounter->hitPoints);
	DDX_Text(pDX, IDC_S11, pcounter->chaffStrength);
	DDX_Text(pDX, IDC_SS2, pcounter->launcherDef.expendableSize);

	DDX_Text(pDX, IDC_UID, uid);
	//DDX_Text(pDX, IDC_USEFLAGS, usemask);

	DDX_Text(pDX, IDC_UIDPROX, uidprox);

	DDX_Text(pDX, IDC_OVUIDPROX, pl->successorPartID);
	DDX_Text(pDX, IDC_LAUNCHCOUNT, pl->launchCount);
	DDX_Text(pDX, IDC_AMOUNT,pl->amount);
	DDX_Text(pDX, IDC_INVLINE, invline);

	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		strcpy(pcounter->launcherDef.name,name);
		strcpy(pcounter->launcherDef.modelName,model);
		strcpy(pcounter->modelName,model2);
		strcpy(pcounter->textureName,icon);
		strcpy(pcounter->launcherDef.iconName,type);
		strcpy(pcounter->iconName,ukbmp);
		strncpy(pcounter->launcherDef.description,descr,IGC_DESCRIPTIONMAX);
		//pcounter->use_mask = usemask;
		pcounter->launcherDef.partMask = 0;
		for (int i=0;i<16;i++) 
		{
			CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
			pcounter->launcherDef.partMask += cbb->GetCheck()?(1<<i):0;
		}
		if (pcounter->launcherDef.partMask == 0)
		{
			MessageBox("Warning usage mask is zero");
		}

		CComboBox *cbac = (CComboBox *)GetDlgItem(IDC_AC);
		pcounter->defenseType = cbac->GetCurSel();
		strcpy_s(pl->inventoryLineMDL,c_cbFileName,invline);
	}
	CDialog::DoDataExchange(pDX);
}

void CChaffDlg::OnClickedDecodesel(void)
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

void CChaffDlg::OnClickedDecodeh(void)
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

void CChaffDlg::OnClickedOk(void)
{
	CString oldname = pcounter->launcherDef.name;
	UpdateData(TRUE);
	CString newname = pcounter->launcherDef.name;
	if (oldname != newname)
		GetParent()->UpdateData(TRUE);
	UpdateData(FALSE);
}

void CChaffDlg::OnClickedCancel(void)
{
	UpdateData(FALSE);
}


BEGIN_MESSAGE_MAP(CChaffDlg, CDialog)
	ON_BN_CLICKED(IDC_DECODESEL, OnClickedDecodesel)
	ON_BN_CLICKED(IDC_DECODEH, OnClickedDecodeh)
	ON_BN_CLICKED(IDOK, OnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnClickedCancel)
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
	ON_BN_CLICKED(IDC_BSUCC, &CChaffDlg::OnBnClickedBsucc)
	ON_LBN_SELCHANGE(IDC_UMLIST, &CChaffDlg::OnLbnSelchangeUmlist)
	ON_BN_CLICKED(IDC_BEDITDESCR, &CChaffDlg::OnBnClickedBeditdescr)
END_MESSAGE_MAP()


// CChaffDlg message handlers

BOOL CChaffDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	VERIFY(mdlbmp.SubclassDlgItem(IDC_PICT, this));
	VERIFY(mdlbmp2.SubclassDlgItem(IDC_PICT2, this));
	VERIFY(mdlbmp3.SubclassDlgItem(IDC_PICT3, this));

	CComboBox *cbac = (CComboBox *)GetDlgItem(IDC_AC);
	cbac->ResetContent();
	for (int i=0;i<IGCACMAX;i++)
		cbac->AddString(IGCArmorClasses[i]);

	((CEdit *)GetDlgItem(IDC_DESCRIPTION))->SetLimitText(IGC_DESCRIPTIONMAX);
	((CEdit *)GetDlgItem(IDC_NAME))->SetLimitText(IGC_NAMEMAX);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

// display other ECM with same usemask
void CChaffDlg::OnBnClickedUsem0()
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
	for (int j=0;j<pcore->cl_Counters.GetSize();j++)
	{
		PtrCoreCounter pp = pcore->cl_Counters.GetAt(j);
		if ((pp->launcherDef.partMask & umask) && (pp->expendabletypeID != pcounter->expendabletypeID))
		{
			CString s;
			s.Format("%s (%d)",pp->launcherDef.name,pp->expendabletypeID);
			int idx = clb->AddString(s);
			clb->SetItemDataPtr(idx,pp);
		}
	}
}
void CChaffDlg::OnBnClickedBsucc()
{
	if (!pcounter) return;
	if (!pcore) return;
	PtrCoreLauncher pl = pcore->GetLauncher(pcounter->expendabletypeID);
	if (!pl) return;
	if (pl->successorPartID == -1) return;
	
	PtrCoreLauncher succ = pcore->FindLauncher(pl->successorPartID);
	if (succ)
	{
		LPARAM p = (LPARAM)succ;
		if (1) //TODO
		{
			PtrCoreEntry pce = pcore->ProxyPart(succ->expendabletypeID);
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
		AfxMessageBox("Error: invalid successor");}

void CChaffDlg::OnLbnSelchangeUmlist()
{
	CListBox *clb = (CListBox *)CWnd::GetDlgItem(IDC_UMLIST);
	int idx = clb->GetCurSel();
	if (idx==-1) return;
	MainUI->SelectPCE((LPARAM)clb->GetItemDataPtr(idx));
}

void CChaffDlg::OnBnClickedBeditdescr()
{
	CDescrDlg dlg(pcounter->launcherDef.description);
	if (dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_DESCRIPTION,pcounter->launcherDef.description);
}
