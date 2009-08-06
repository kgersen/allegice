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
		uid = ptres->treasureSetID;

		BuildPL();

		for (int n=0;n<ptres->nTreasureData;n++)
		{
			CString s;
			char *pn;
			TreasureData *p = ptres->treasureData0()+n;
			switch(p->treasureCode)
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
				case c_tcPart:
					{
					pn = pcore->PartName(p->treasureID);
					if (pn)
						s.Format("Part: %s (%d)",pn,p->treasureID);
					else
						s.Format("UNKNOWN PART ! (%d)",p->treasureID);
					}
					break;
				case c_tcPowerup:
					s.Format("Powerup (%d)",p->treasureID);
					break;
				case c_tcCash:
					s.Format("Cash: $%d",p->treasureID);
					break;
				case c_tcDevelopment:
					// NYI
					break;
				default:
					s.Format("????");
			}
			int idx = clTres->AddString(s);
			TreasureData *t = new TreasureData;
			*t = *p;
			clTres->SetItemDataPtr(idx,t);
		}
		OnLbnSelchangeTreslist();
	}
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_UID, uid);

	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		if (clTres->GetCount() >= MAXTREASURES)
			AfxMessageBox("too many entries in treasure set");
		else
		{
			strcpy(ptres->name,name);
			ptres->nTreasureData = clTres->GetCount();
			for (int n=0;n<ptres->nTreasureData;n++)
			{
				TreasureData *t = (TreasureData *) clTres->GetItemData(n);
				*(ptres->treasureData0()+n) = *t;
			}
		}
	}
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTreasureDlg, CDialog)
	ON_BN_CLICKED(IDWRITE, OnBnClickedOk)
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

	GetDlgItem(IDC_PWR_HULL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PWR_SHIELD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PWR_ENERGY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PWR_FUEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PWR_AMMO)->ShowWindow(SW_HIDE);

	int idx = clTres->GetCurSel();
	if (idx == LB_ERR)
	{
		return;
	}
	TreasureData *t = (TreasureData *) clTres->GetItemData(idx);
	SetDlgItemInt(IDC_CHANCE,t->chance);
	switch (t->treasureCode)
	{
		case c_tcPart:
			break;
		case c_tcPowerup:
			GetDlgItem(IDC_PWR_HULL)->ShowWindow(SW_SHOWNA);
			GetDlgItem(IDC_PWR_SHIELD)->ShowWindow(SW_SHOWNA);
			GetDlgItem(IDC_PWR_ENERGY)->ShowWindow(SW_SHOWNA);
			GetDlgItem(IDC_PWR_FUEL)->ShowWindow(SW_SHOWNA);
			GetDlgItem(IDC_PWR_AMMO)->ShowWindow(SW_SHOWNA);
			((CButton *)GetDlgItem(IDC_PWR_HULL))->SetCheck(t->treasureID & c_pcHull ? BST_CHECKED : BST_UNCHECKED);
			((CButton *)GetDlgItem(IDC_PWR_SHIELD))->SetCheck(t->treasureID & c_pcShield ? BST_CHECKED : BST_UNCHECKED);
			((CButton *)GetDlgItem(IDC_PWR_ENERGY))->SetCheck(t->treasureID & c_pcEnergy ? BST_CHECKED : BST_UNCHECKED);
			((CButton *)GetDlgItem(IDC_PWR_FUEL))->SetCheck(t->treasureID & c_pcFuel ? BST_CHECKED : BST_UNCHECKED);
			((CButton *)GetDlgItem(IDC_PWR_AMMO))->SetCheck(t->treasureID & c_pcAmmo ? BST_CHECKED : BST_UNCHECKED);
				
			break;
		case c_tcCash:
			cecash->ShowWindow(SW_SHOWNA);
			cescash->ShowWindow(SW_SHOWNA);
			SetDlgItemInt(IDC_CASH,t->treasureID);
			break;
	}
}

void CTreasureDlg::OnBnClickedBttotres()
{
	int idx = clParts->GetCurSel();
	if (idx == LB_ERR)
		return;
	TreasureData *t = (TreasureData *) clParts->GetItemData(idx);
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
	TreasureData *t = (TreasureData *) clTres->GetItemDataPtr(idx);
	
	if (t->treasureCode == c_tcPart)
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
		TreasureData *t = (TreasureData *) clParts->GetItemDataPtr(n);
		clParts->SetItemDataPtr(n,NULL);
		delete t;
	}
	clParts->ResetContent();
	for (int n=0;n<clTres->GetCount();n++)
	{
		TreasureData *t = (TreasureData *) clTres->GetItemDataPtr(n);
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
		for (int n=0;n<ptres->nTreasureData;n++)
		{
			TreasureData *t = ptres->treasureData0()+n;
			if(t->treasureCode == c_tcPart)
				if (t->treasureID == ppart->uid)
					bSkip = true;
		}
		if (!bSkip)
		{
			int idx = clParts->AddString(s);
			TreasureData *t = new TreasureData;
			t->chance = 2;
			t->treasureCode = c_tcPart;
			t->treasureID = ppart->uid;
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
	TreasureData *t = new TreasureData;
	t->treasureCode = c_tcCash;
	t->treasureID = 500;
	t->chance = 30;
	s.Format("Cash: $%d",t->treasureID);
	int idx = clTres->AddString(s);
	clTres->SetItemDataPtr(idx,t);
}

void CTreasureDlg::OnBnClickedAddpwup()
{
	CString s;
	TreasureData *t = new TreasureData;
	t->treasureCode = c_tcPowerup;
	t->treasureID = c_pcHull + c_pcShield + c_pcEnergy + c_pcFuel + c_pcAmmo;
	t->chance = 60;
	s.Format("Powerup (%d)",t->treasureID);
	int idx = clTres->AddString(s);
	clTres->SetItemDataPtr(idx,t);
}

void CTreasureDlg::OnBnClickedSetchance()
{
	int idx = clTres->GetCurSel();
	if (idx == LB_ERR)
		return;
	TreasureData *t = (TreasureData *) clTres->GetItemDataPtr(idx);
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
	t->chance = (BYTE) val;
	if (t->treasureCode == c_tcCash)
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
		t->treasureID = val;
		CString s;
		s.Format("Cash: $%d",val);
		clTres->DeleteString(idx);
		idx = clTres->AddString(s);
		clTres->SetItemDataPtr(idx,t);
		clTres->SetSel(idx);
	}
	if (t->treasureCode == c_tcPowerup)
	{
		t->treasureID =
			((((CButton *)GetDlgItem(IDC_PWR_HULL))->GetCheck() == BST_CHECKED) ? c_pcHull : 0) +
			((((CButton *)GetDlgItem(IDC_PWR_SHIELD))->GetCheck() == BST_CHECKED) ? c_pcShield : 0) +
			((((CButton *)GetDlgItem(IDC_PWR_ENERGY))->GetCheck() == BST_CHECKED) ? c_pcEnergy : 0) +
			((((CButton *)GetDlgItem(IDC_PWR_FUEL))->GetCheck() == BST_CHECKED) ? c_pcFuel : 0) +
			((((CButton *)GetDlgItem(IDC_PWR_AMMO))->GetCheck() == BST_CHECKED) ? c_pcAmmo : 0);
		CString s;
		s.Format("Powerup (%d)",t->treasureID);
		clTres->DeleteString(idx);
		idx = clTres->AddString(s);
		clTres->SetItemDataPtr(idx,t);
		clTres->SetSel(idx);		
	}
}
