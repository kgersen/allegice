// TreasureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICE.h"
#include "corestruct.h"
#include "TreasureDlg.h"


// CTreasureDlg dialog

IMPLEMENT_DYNAMIC(CTreasureDlg, CDialog)
CTreasureDlg::CTreasureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTreasureDlg::IDD, pParent)
{
	ptres = NULL;
	pcore = NULL;
}

CTreasureDlg::~CTreasureDlg()
{
}

void CTreasureDlg::DoDataExchange(CDataExchange* pDX)
{
	if (!ptres) return;
	if (!pcore) return;

	CString name;
	int uid;
	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		name = ptres->name;
		uid = ptres->uid;

		BuildPL();

		for (int n=0;n<ptres->count;n++)
		{
			CString s;
			char *pn;
			switch(ptres->ChanceEntries[n].Code)
			{
				//case 8:
				//	{
				//	pn = pcore->DevelName(ptres->ChanceEntries[n].uid);
				//	if (pn)
				//		s.Format("Dev: %s (%d)",pn,ptres->ChanceEntries[n].uid);
				//	else
				//		s.Format("UNKNOWN DEVEL ! (%d)",ptres->ChanceEntries[n].uid);
				//	}
				//	break;
				case 1:
					{
					pn = pcore->PartName(ptres->ChanceEntries[n].uid);
					if (pn)
						s.Format("Part: %s (%d)",pn,ptres->ChanceEntries[n].uid);
					else
						s.Format("UNKNOWN PART ! (%d)",ptres->ChanceEntries[n].uid);
					}
					break;
				case 2:
					s.Format("Powerup (%d)",ptres->ChanceEntries[n].uid);
					break;
				case 4:
					s.Format("Cash: $%d",ptres->ChanceEntries[n].uid);
					break;
				default:
					s.Format("????");
			}
			int idx = clTres->AddString(s);
			IGCCoreTreasureChance *t = new IGCCoreTreasureChance;
			*t = ptres->ChanceEntries[n];
			clTres->SetItemDataPtr(idx,t);
		}
		OnLbnSelchangeTreslist();
	}
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_UID, uid);

	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		strcpy(ptres->name,name);
		delete ptres->ChanceEntries;
		ptres->count = clTres->GetCount();
		ptres->ChanceEntries = new IGCCoreTreasureChance[ptres->count];
		for (int n=0;n<ptres->count;n++)
		{
			IGCCoreTreasureChance *t = (IGCCoreTreasureChance *) clTres->GetItemData(n);
			ptres->ChanceEntries[n] = *t;
		}
	}
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTreasureDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_LBN_SELCHANGE(IDC_TRESLIST, OnLbnSelchangeTreslist)
	ON_BN_CLICKED(IDC_BTTOTRES, OnBnClickedBttotres)
	ON_BN_CLICKED(IDC_BTTOPART, OnBnClickedBttopart)
	ON_BN_CLICKED(IDC_ADDCASH, OnBnClickedAddcash)
	ON_BN_CLICKED(IDC_ADDPWUP, OnBnClickedAddpwup)
	ON_BN_CLICKED(IDC_SETCHANCE, OnBnClickedSetchance)
END_MESSAGE_MAP()


// CTreasureDlg message handlers

void CTreasureDlg::OnBnClickedOk()
{
	CString oldname = ptres->name;
	UpdateData(TRUE);
	CString newname = ptres->name;
	if (oldname != newname)
		GetParent()->UpdateData(TRUE);
	UpdateData(FALSE);
}

void CTreasureDlg::OnBnClickedCancel()
{
	UpdateData(FALSE);
}

BOOL CTreasureDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	clParts = (CListBox *) GetDlgItem(IDC_PARTLIST);
	clTres  = (CListBox *) GetDlgItem(IDC_TRESLIST);

	((CEdit *)GetDlgItem(IDC_NAME))->SetLimitText(IGC_NAMEMAX);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CTreasureDlg::OnLbnSelchangeTreslist()
{
	CEdit *cecash = (CEdit *) GetDlgItem(IDC_CASH);
	CWnd *cescash = GetDlgItem(IDC_SCASH);
	cecash->ShowWindow(SW_HIDE);
	cescash->ShowWindow(SW_HIDE);
	int idx = clTres->GetCurSel();
	if (idx == LB_ERR)
	{
		return;
	}
	IGCCoreTreasureChance *t = (IGCCoreTreasureChance *) clTres->GetItemData(idx);
	SetDlgItemInt(IDC_CHANCE,t->Chance);
	switch (t->Code)
	{
		case 1:
			break;
		case 2:
			break;
		case 4:
			cecash->ShowWindow(SW_SHOWNA);
			cescash->ShowWindow(SW_SHOWNA);
			SetDlgItemInt(IDC_CASH,t->uid);
			break;
	}
}

void CTreasureDlg::OnBnClickedBttotres()
{
	int idx = clParts->GetCurSel();
	if (idx == LB_ERR)
		return;
	IGCCoreTreasureChance *t = (IGCCoreTreasureChance *) clParts->GetItemData(idx);
	CString s;
	clParts->GetText(idx,s);
	int idxt = clTres->AddString(s);
	clTres->SetItemDataPtr(idxt,t);

	clParts->SetItemDataPtr(idx,NULL);
	clParts->DeleteString(idx);
}

void CTreasureDlg::OnBnClickedBttopart()
{
	int idx = clTres->GetCurSel();
	if (idx == LB_ERR)
		return;
	IGCCoreTreasureChance *t = (IGCCoreTreasureChance *) clTres->GetItemDataPtr(idx);
	
	if (t->Code == 1)
	{
		CString s;
		clTres->GetText(idx,s);
		int idxp = clParts->AddString(s);
		clParts->SetItemDataPtr(idxp,t);
	}
	else
	{
		delete t;
	}
	clTres->SetItemDataPtr(idx,NULL);
	clTres->DeleteString(idx);
}

void CTreasureDlg::BuildPL()
{
	for (int n=0;n<clParts->GetCount();n++)
	{
		IGCCoreTreasureChance *t = (IGCCoreTreasureChance *) clParts->GetItemDataPtr(n);
		clParts->SetItemDataPtr(n,NULL);
		delete t;
	}
	clParts->ResetContent();
	for (int n=0;n<clTres->GetCount();n++)
	{
		IGCCoreTreasureChance *t = (IGCCoreTreasureChance *) clTres->GetItemDataPtr(n);
		clTres->SetItemDataPtr(n,NULL);
		delete t;
	}
	clTres->ResetContent();
	for (int j=0;j<pcore->cl_Parts.GetSize();j++)
	{
		PtrCorePart ppart = pcore->cl_Parts.GetAt(j);
		CString s;
		if (ppart->isspec)
			s.Format("Part: %s (%d)",pcore->ProxyPartName(ppart->usemask),ppart->uid);
		else
			s.Format("Part: %s (%d)",ppart->name,ppart->uid);

		bool bSkip = false;
		for (int n=0;n<ptres->count;n++)
		{
			if(ptres->ChanceEntries[n].Code == 1)
				if (ptres->ChanceEntries[n].uid == ppart->uid)
					bSkip = true;
		}
		if (!bSkip)
		{
			int idx = clParts->AddString(s);
			IGCCoreTreasureChance *t = new IGCCoreTreasureChance;
			t->Chance = 2;
			t->Code = 1;
			t->uid = ppart->uid;
			clParts->SetItemDataPtr(idx,t);
		}
	}
	//for (int j=0;j<pcore->cl_Devels.GetSize();j++)
	//{
	//	PtrCoreDevel devel = pcore->cl_Devels.GetAt(j);
	//	CString s;
	//	s.Format("Dev: %s (%d)",devel->name,devel->uid);

	//	bool bSkip = false;
	//	for (int n=0;n<ptres->count;n++)
	//	{
	//		if(ptres->ChanceEntries[n].Code == 0)
	//			if (ptres->ChanceEntries[n].uid == devel->uid)
	//				bSkip = true;
	//	}
	//	if (!bSkip)
	//	{
	//		int idx = clParts->AddString(s);
	//		IGCCoreTreasureChance *t = new IGCCoreTreasureChance;
	//		t->Chance = 2;
	//		t->Code = 8;
	//		t->uid = devel->uid;
	//		clParts->SetItemDataPtr(idx,t);
	//	}
	//}
}
void CTreasureDlg::OnBnClickedAddcash()
{
	CString s;
	IGCCoreTreasureChance *t = new IGCCoreTreasureChance;
	t->Code = 4;
	t->uid = 500;
	t->Chance = 30;
	s.Format("Cash: $%d",t->uid);
	int idx = clTres->AddString(s);
	clTres->SetItemDataPtr(idx,t);
}

void CTreasureDlg::OnBnClickedAddpwup()
{
	CString s;
	IGCCoreTreasureChance *t = new IGCCoreTreasureChance;
	t->Code = 2;
	t->uid = 31;
	t->Chance = 60;
	s.Format("Powerup (%d)",t->uid);
	int idx = clTres->AddString(s);
	clTres->SetItemDataPtr(idx,t);
}

void CTreasureDlg::OnBnClickedSetchance()
{
	int idx = clTres->GetCurSel();
	if (idx == LB_ERR)
		return;
	IGCCoreTreasureChance *t = (IGCCoreTreasureChance *) clTres->GetItemDataPtr(idx);
	BOOL bValid = FALSE;
	UINT val = GetDlgItemInt(IDC_CHANCE,&bValid);
	if (!bValid)
	{
		AfxMessageBox("Invalide chance value");
		return;
	}
	if ((val<1) || (val>255))
	{
		AfxMessageBox("chance value must be between 1 and 255");
		return;
	}
	t->Chance = (BYTE) val;
	if (t->Code == 4)
	{
		val = GetDlgItemInt(IDC_CASH,&bValid);
		if (!bValid)
		{
			AfxMessageBox("Invalide cash amount value");
			return;
		}
		if ((val<1) || (val>65535))
		{
			AfxMessageBox("cash amount value must be between 1 and 65535");
			return;
		}
		t->uid = val;
		CString s;
		s.Format("Cash: $%d",val);
		clTres->DeleteString(idx);
		idx = clTres->AddString(s);
		clTres->SetItemDataPtr(idx,t);
		clTres->SetSel(idx);
	}
}
