// ShipDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICE.h"
#include "corestruct.h"
#include "MDLView.h"
#include "ShipDlg.h"
#include ".\shipdlg.h"


// CShipDlg dialog

IMPLEMENT_DYNAMIC(CShipDlg, CDialog)
CShipDlg::CShipDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShipDlg::IDD, pParent)
{
	pship = NULL;
	pcore = NULL;
}

CShipDlg::~CShipDlg()
{
}

// CShipLoadout dialog

IMPLEMENT_DYNAMIC(CShipLoadout, CDialog)
CShipLoadout::CShipLoadout(CWnd* pParent /*=NULL*/)
	: CDialog(CShipLoadout::IDD, pParent)
{
	pship = NULL;
	pcore = NULL;
}

CShipLoadout::~CShipLoadout()
{
}
void CShipDlg::SetIcons(HICON iJumpIcon)
{
	((CButton *)GetDlgItem(IDC_BSUCC))->SetIcon(iJumpIcon);
}
void CShipDlg::DoDataExchange(CDataExchange* pDX)
{
	CString name,model,obj,descr;
	CString todo1 = "";
	int uid,group;
	int sound_int,sound_ext,sound_thi,sound_the,sound_tui,sound_tue;
	if (!pship) return;
	if (!pcore) return;
	ASSERT(sArtPath != "");
	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		name = pship->name;
		model = pship->model;
		descr = pship->description;
		group = pship->group;
		obj = pship->icon;
		mdlbmp.LoadMDLFile(sArtPath +"\\"+ obj + "bmp.mdl");
		sound_int = pship->Sound_Interior;
		sound_ext = pship->Sound_Exterior;
		sound_thi = pship->Sound_ThrustInterior;
		sound_the = pship->Sound_ThrustExterior;
		sound_tui = pship->Sound_TurnInterior;
		sound_tue = pship->Sound_TurnExterior;
		CComboBox *cbac = (CComboBox *)GetDlgItem(IDC_AC);
		cbac->SetCurSel(pship->AC);
		uid = pship->uid;
		CButton *cbb;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_BOARD);
		cbb->SetCheck((pship->hullability & IGCHullAbility_Board)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_RESCUE);
		cbb->SetCheck((pship->hullability & IGCHullAbility_Rescue)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_LIFEPOD);
		cbb->SetCheck((pship->hullability & IGCHullAbility_Lifepod)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_NOPICKUP);
		cbb->SetCheck((pship->hullability & IGCHullAbility_NoPickup)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_NOEJECTION);
		cbb->SetCheck((pship->hullability & IGCHullAbility_NoEjection)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_NORIPCORD);
		cbb->SetCheck((pship->hullability & IGCHullAbility_NoRipcord)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_ISRIP);
		cbb->SetCheck((pship->hullability & IGCHullAbility_IsRip)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_FIGHTER);
		cbb->SetCheck((pship->hullability & IGCHullAbility_Fighter)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_CAPITAL);
		cbb->SetCheck((pship->hullability & ((unsigned short)IGCHullAbility_Captital))?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_F2);
		cbb->SetCheck(((pship->hullability) & IGCHullAbility_F2)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_ISDOCK);
		cbb->SetCheck(((pship->hullability) & IGCHullAbility_IsDock)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_F8);
		cbb->SetCheck(((pship->hullability) & IGCHullAbility_F8)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_ISSMALLRIP);
		cbb->SetCheck(((pship->hullability) & IGCHullAbility_IsSmallRip)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_RIPTOSMALL);
		cbb->SetCheck(((pship->hullability) & IGCHullAbility_RipToSmallRip)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_MINER);
		cbb->SetCheck(((pship->hullability) & IGCHullAbility_IsMiner)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_CONSTRUCTOR);
		cbb->SetCheck(((pship->hullability) & IGCHullAbility_IsConstructor)?BST_CHECKED:BST_UNCHECKED);

	}
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_MODEL, model);
	DDX_Text(pDX, IDC_OBJ, obj);
	DDX_Text(pDX, IDC_DESCRIPTION, descr);
	DDX_Text(pDX, IDC_GROUP, group);
	//DDX_Text(pDX, IDC_TODO1, todo1);
	DDX_Text(pDX, IDC_COUT,pship->cost);
	DDX_Text(pDX, IDC_S1, pship->stats_s1);
	DDX_Text(pDX, IDC_S2, pship->stats_s2);
	DDX_Text(pDX, IDC_S3, pship->stats_s3);
	DDX_Text(pDX, IDC_S4, pship->stats_s4);
	DDX_Text(pDX, IDC_S5, pship->stats_s5);
	DDX_Text(pDX, IDC_S6, pship->stats_s6);
	DDX_Text(pDX, IDC_S7, pship->stats_s7);
	DDX_Text(pDX, IDC_S8, pship->stats_s8);
	DDX_Text(pDX, IDC_S9, pship->stats_s9);
	DDX_Text(pDX, IDC_S10, pship->stats_s10);
	DDX_Text(pDX, IDC_S11, pship->stats_s11);
	DDX_Text(pDX, IDC_S12, pship->stats_s12);
	DDX_Text(pDX, IDC_S13, pship->stats_s13);
	DDX_Text(pDX, IDC_S14, pship->stats_s14);
	DDX_Text(pDX, IDC_S15, pship->stats_s15);
	DDX_Text(pDX, IDC_S16, pship->stats_s16);
	DDX_Text(pDX, IDC_S17, pship->stats_s17);
	DDX_Text(pDX, IDC_S18, pship->stats_s18);
	DDX_Text(pDX, IDC_S19, pship->stats_s19);
	DDX_Text(pDX, IDC_S20, pship->stats_s20);
	DDX_Text(pDX, IDC_UID, uid);
	DDX_Text(pDX, IDC_OVUID, pship->overriding_uid);

	DDX_Text(pDX, IDC_SOUNDINT, sound_int);
	DDX_Text(pDX, IDC_SOUNDEXT, sound_ext);
	DDX_Text(pDX, IDC_SOUNDTHI, sound_thi);
	DDX_Text(pDX, IDC_SOUNDTHE, sound_the);
	DDX_Text(pDX, IDC_SOUNDTUI, sound_tui);
	DDX_Text(pDX, IDC_SOUNDTUE, sound_tue);

	DDX_Text(pDX, IDC_HP, pship->stats_hp);

	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		strcpy(pship->name,name);
		strcpy(pship->model,model);
		strcpy(pship->icon,obj);
		strncpy(pship->description,descr,IGC_DESCRIPTIONMAX);
		pship->group = group;
		CComboBox *cbac = (CComboBox *)GetDlgItem(IDC_AC);
		pship->AC = cbac->GetCurSel();

		pship->Sound_Interior=sound_int;
		pship->Sound_Exterior=sound_ext;
		pship->Sound_ThrustInterior=sound_thi;
		pship->Sound_ThrustExterior=sound_the;
		pship->Sound_TurnInterior=sound_tui;
		pship->Sound_TurnExterior=sound_tue;

		CButton *cbb;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_BOARD);
		pship->hullability = cbb->GetCheck()?IGCHullAbility_Board:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_RESCUE);
		pship->hullability += cbb->GetCheck()?IGCHullAbility_Rescue:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_LIFEPOD);
		pship->hullability += cbb->GetCheck()?IGCHullAbility_Lifepod:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_NOPICKUP);
		pship->hullability += cbb->GetCheck()?IGCHullAbility_NoPickup:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_NOEJECTION);
		pship->hullability += cbb->GetCheck()?IGCHullAbility_NoEjection:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_NORIPCORD);
		pship->hullability += cbb->GetCheck()?IGCHullAbility_NoRipcord:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_ISRIP);
		pship->hullability += cbb->GetCheck()?IGCHullAbility_IsRip:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_FIGHTER);
		pship->hullability += cbb->GetCheck()?IGCHullAbility_Fighter:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_CAPITAL);
		pship->hullability += cbb->GetCheck()?IGCHullAbility_Captital:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_F2);
		pship->hullability += cbb->GetCheck()?IGCHullAbility_F2:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_ISDOCK);
		pship->hullability += cbb->GetCheck()?IGCHullAbility_IsDock:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_F8);
		pship->hullability += cbb->GetCheck()?IGCHullAbility_F8:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_ISSMALLRIP);
		pship->hullability += cbb->GetCheck()?IGCHullAbility_IsSmallRip:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_RIPTOSMALL);
		pship->hullability += cbb->GetCheck()?IGCHullAbility_RipToSmallRip:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_MINER);
		pship->hullability += cbb->GetCheck()?IGCHullAbility_IsMiner:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_CONSTRUCTOR);
		pship->hullability += cbb->GetCheck()?IGCHullAbility_IsConstructor:0;
	}
	CDialog::DoDataExchange(pDX);
}

void CShipLoadout::DoDataExchange(CDataExchange* pDX)
{
	int ss1,ld1,ld2,ld3,nbparts;
	if (!pship) return;
	if (!pcore) return;
	ASSERT(sArtPath != "");
	CListBox *clb = (CListBox *)GetDlgItem(IDC_WEPLIST);
	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		ss1 = pship->stats_ss1;
		ld1 = pship->stats_ld1;
		ld2 = pship->stats_ld2;
		ld3 = pship->stats_ld3;
		nbparts = pship->nb_parts;

		// IDC_PARTLIST
		for (int i=0;i<IGCSHIPMAXPARTS;i++)
			DLList[i] = pship->def_loadout[i];
		BuildDL();

		clb->ResetContent();
		for (int p=0;p<pship->nb_parts;p++)
		{
			CString wpn;
			wpn.Format("PART %d",p);
			clb->AddString(wpn);
		}
		if (pship->nb_parts >0)
		{
			clb->SetCurSel(0);
		}
		OnSelchangeWepsel();
		OnSelchangePartsel();
	}
	DDX_Text(pDX, IDC_SS1, ss1);
	DDX_Text(pDX, IDC_SS5, ld1);
	DDX_Text(pDX, IDC_SS6, ld2);
	DDX_Text(pDX, IDC_SS7, ld3);
	DDX_Text(pDX, IDC_NBPARTS, nbparts);


	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		CButton *cbb;
		pship->stats_ss1 = ss1;
		pship->stats_ld1 = ld1;
		pship->stats_ld2 = ld2;
		pship->stats_ld3 = ld3;
		pship->nb_parts = clb->GetCount();//nbparts;

		// Default loadout
		SaveDL();
		for (int i=0;i<IGCSHIPMAXPARTS;i++)
			pship->def_loadout[i] = DLList[i]; 

		CComboBox * cbpm = (CComboBox *)GetDlgItem(IDC_PARTSEL);
		int idx = cbpm->GetCurSel();
		if (idx != CB_ERR)
		{
			idx = (int)cbpm->GetItemData(idx);
			pship->can_use[idx] = 0;
			for (int i=0;i<16;i++) 
			{
				cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
				pship->can_use[idx] += cbb->GetCheck()?(1<<i):0;
			}
		}
		CListBox * cbws = (CListBox *)GetDlgItem(IDC_WEPLIST);
		idx = cbws->GetCurSel();
		if (idx != CB_ERR)
		{
			//pship->parts[idx].part_mask = 0;
			//for (int i=0;i<16;i++) 
			//{
			//	cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+16+i);
			//	pship->parts[idx].part_mask += cbb->GetCheck()?(1<<i):0;
			//}
			CButton *cbtype = (CButton *)GetDlgItem(IDC_WEPTYPE);
			pship->parts[idx].part_type = (cbtype->GetCheck()==BST_CHECKED)?0:1;
			CString wp_pos;
			int wp_uk1,wp_uk2;
			DDX_Text(pDX, IDC_WEPPOS, wp_pos);
			DDX_Text(pDX, IDC_WEPS1, wp_uk1);
			DDX_Text(pDX, IDC_WEPS2, wp_uk2);

			strcpy(pship->parts[idx].position,wp_pos);
			pship->parts[idx].uk1 = wp_uk1;
			pship->parts[idx].uk2 = wp_uk2;
		}
		// recompute weapon slots (non turret)
		pship->mnt_nbwpslots = 0;
		for (int p=0;p<pship->nb_parts;p++)
		{
			if (pship->parts[p].part_type == 1)
				pship->mnt_nbwpslots++;
		}

	}
	CDialog::DoDataExchange(pDX);
}


BOOL CShipDlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	VERIFY(mdlbmp.SubclassDlgItem(IDC_PICT, this));

	CComboBox *cbac = (CComboBox *)GetDlgItem(IDC_AC);
	cbac->ResetContent();
	for (int i=0;i<IGCACMAX;i++)
		cbac->AddString(IGCArmorClasses[i]);

	((CEdit *)GetDlgItem(IDC_DESCRIPTION))->SetLimitText(IGC_DESCRIPTIONMAX);
	((CEdit *)GetDlgItem(IDC_NAME))->SetLimitText(IGC_NAMEMAX);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
BOOL CShipLoadout::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	CComboBox * cbpm = (CComboBox *)GetDlgItem(IDC_PARTSEL);
	cbpm->ResetContent();
	for (int i = 0;i<IGCSHIPMAXUSE;i++)
	{
		if (IGCShipUseMasks[i][0] != '*')
		{
			int idx = cbpm->AddString(IGCShipUseMasks[i]);
			cbpm->SetItemData(idx,i);
		}
	}
	DLCheck = BST_UNCHECKED;
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CShipDlg::OnClickedOk(void)
{
	CString oldname = pship->name;
	UpdateData(TRUE);
	CString newname = pship->name;
	if (oldname != newname)
		GetParent()->UpdateData(TRUE);
	UpdateData(FALSE);
}
void CShipLoadout::OnClickedOk(void)
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}

void CShipDlg::OnClickedCancel(void)
{
	UpdateData(FALSE);
}
void CShipLoadout::OnClickedCancel(void)
{
	UpdateData(FALSE);
}
void CShipDlg::OnClickedModeledit(void)
{
	CMDLView dlgmdl;
	CString s;
	GetDlgItemText(IDC_MODEL,s);
	dlgmdl.sArtPath = sArtPath;
	dlgmdl.sModel = s;
	dlgmdl.DoModal();
}

void CShipLoadout::OnSelchangePartsel(void)
{
	CComboBox * cbpm = (CComboBox *)GetDlgItem(IDC_PARTSEL);
	int idx = cbpm->GetCurSel();
	CListBox *cbpc = (CListBox *)GetDlgItem(IDC_PARTCHOICE);
	cbpc->ResetContent();
	if (idx==CB_ERR)
		return;

	idx = (int)cbpm->GetItemData(idx); // idx = part type here
	if (!pship) return;
	for (int i=0;i<16;i++) 
	{
		CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
		if (idx == CB_ERR)
		{
			cbb->EnableWindow(FALSE);
			cbb->SetCheck(BST_UNCHECKED);
		}
		else
		{
			cbb->SetCheck((pship->can_use[idx] & (1<<i))?BST_CHECKED:BST_UNCHECKED);
			cbb->EnableWindow(TRUE);
		}
	}


	CButton *ctog = (CButton *)GetDlgItem(IDC_PARTTOGGLE);

	if (ctog->GetCheck() == BST_UNCHECKED)
	// view mode
	for (int j=0;j<pcore->cl_Parts.GetSize();j++)
	{
		PtrCorePart ppart = pcore->cl_Parts.GetAt(j);
		if ((ppart->type == idx) || (ppart->isspec))
		{
			bool IsUpgrade = false;
			for (int jj=0;jj<pcore->cl_Parts.GetSize();jj++)
			{
				PtrCorePart ppart2 = pcore->cl_Parts.GetAt(jj);
				if (ppart2->overriding_uid == ppart->uid)
				{
					IsUpgrade = true;
					break;
				}
			}
			if (!IsUpgrade)
			{
				LPARAM pcpart;
				char *pname=NULL;
				if (!ppart->isspec)
					if (ppart->usemask & pship->can_use[idx])
					{
						pname = ppart->name;
						pcpart = (LPARAM)ppart;
					}
				if (ppart->isspec)
				{
					PtrCoreEntry pce = pcore->ProxyPart(ppart->usemask);
					if (pce->IGCPartType == idx)
					if (pce->usemask & pship->can_use[idx])
					{
						pname = pcore->ProxyPartName(ppart->usemask);
						pcpart = pce->entry;
					}
					delete pce;
				}
				if (pname != NULL)
				{
					int ipc = cbpc->AddString(pname);
					cbpc->SetItemData(ipc,pcpart);
				}
			}
		}
	}
	else // EDIT MODE
	for (int i=0;i<16;i++)
	{
		unsigned short umask = 1<<i;
		for (int j=0;j<pcore->cl_Parts.GetSize();j++)
		{
			PtrCorePart ppart = pcore->cl_Parts.GetAt(j);
			if ((ppart->type == idx) || (ppart->isspec))
			{
				bool IsUpgrade = false;
				for (int jj=0;jj<pcore->cl_Parts.GetSize();jj++)
				{
					PtrCorePart ppart2 = pcore->cl_Parts.GetAt(jj);
					if (ppart2->overriding_uid == ppart->uid)
					{
						IsUpgrade = true;
						break;
					}
				}
				if (!IsUpgrade)
				{
					bool bsel = false;
					unsigned short pcmask;
					char *pname=NULL;
					if ((!ppart->isspec) && (ppart->usemask & umask))
					{
						pname = ppart->name;
						pcmask = ppart->usemask;
						if (ppart->usemask & pship->can_use[idx])
							bsel = true;
					}
					if (ppart->isspec)
					{
						PtrCoreEntry pce = pcore->ProxyPart(ppart->usemask);
						if ((pce->IGCPartType == idx) && (pce->usemask & umask))
						{
							pname = pcore->ProxyPartName(ppart->usemask);
							pcmask = pce->usemask;
							if (pce->usemask & pship->can_use[idx]) bsel = true;
						}
						delete pce;
					}
					if (pname != NULL)
					{
						int ipc = cbpc->AddString(pname);
						cbpc->SetItemData(ipc,pcmask);
						if (bsel)
							cbpc->SetSel(ipc,TRUE);
					}
				}
			}
		}//for j
		int ipc = cbpc->AddString("----------------------------------------------");
		cbpc->SetItemData(ipc,0);
	}
}

void CShipLoadout::OnSelchangeWepsel(void)
{
	CListBox * cb = (CListBox *)GetDlgItem(IDC_WEPCHOICE);
	cb->ResetContent();

	CListBox * cbws = (CListBox *)GetDlgItem(IDC_WEPLIST);
	if(!pship) return;
	int idx = cbws->GetCurSel();

	for (int i=0;i<16;i++) 
	{
		CButton *cbb = (CButton *)GetDlgItem(IDC_USEM0+16+i);
		if (idx == CB_ERR)
		{
			cbb->EnableWindow(FALSE);
			cbb->SetCheck(BST_UNCHECKED);
		}
		else
		{
			cbb->SetCheck((pship->parts[idx].part_mask & (1<<i))?BST_CHECKED:BST_UNCHECKED);
			cbb->EnableWindow(TRUE);
		}
	}

	CButton *ctog = (CButton *)GetDlgItem(IDC_WCTOGGLE);
	bool WCEdit = (ctog->GetCheck()==BST_CHECKED);

	if (idx != CB_ERR)
	{
		GetDlgItem(IDC_WEPDEL)->EnableWindow(TRUE);
		if (WCEdit)
		{
			for (int i=0;i<16;i++)
			{
				unsigned short umask = 1<<i;
				for (int j=0;j<pcore->cl_Parts.GetSize();j++)
				{
					PtrCorePart ppart = pcore->cl_Parts.GetAt(j);
					if (ppart->type == AGCEquipmentType_Weapon)
					{
						if (!ppart->isspec)
						{
							bool IsUpgrade = false;
							for (int jj=0;jj<pcore->cl_Parts.GetSize();jj++)
							{
								PtrCorePart ppart2 = pcore->cl_Parts.GetAt(jj);
								if ((ppart2->overriding_uid == ppart->uid) && (ppart2->usemask == ppart->usemask))
								{
									IsUpgrade = true;
									break;
								}
							}
							if (!IsUpgrade)
							if (ppart->usemask & umask)
							{
								CString s;
								s.Format("%s",ppart->name);
								int widx = cb->AddString(s);
								cb->SetItemData(widx,ppart->usemask);
								if (pship->parts[idx].part_mask & ppart->usemask)
										cb->SetSel(widx,TRUE);
							}
						}
					}
				} // for j
				int widx = cb->AddString("----------------------------------------------");
				cb->SetItemData(widx,0);
			} // for i
		}
		else
		for (int j=0;j<pcore->cl_Parts.GetSize();j++)
		{
			PtrCorePart ppart = pcore->cl_Parts.GetAt(j);
			if (ppart->type == AGCEquipmentType_Weapon)
			{
				if (!ppart->isspec)
				{
					bool IsUpgrade = false;
					for (int jj=0;jj<pcore->cl_Parts.GetSize();jj++)
					{
						PtrCorePart ppart2 = pcore->cl_Parts.GetAt(jj);
						if ((ppart2->overriding_uid == ppart->uid) && (ppart2->usemask == ppart->usemask))
						{
							IsUpgrade = true;
							break;
						}
					}
					if (!IsUpgrade)
					{
						if (pship->parts[idx].part_mask & ppart->usemask)
						{
							CString s;
							s.Format("%s",ppart->name);
							int idx = cb->AddString(s);
							cb->SetItemDataPtr(idx,ppart);
						}
					}
				}
			}
		}
	}
	else
		GetDlgItem(IDC_WEPDEL)->EnableWindow(FALSE);

	CEdit *cepos = (CEdit *)GetDlgItem(IDC_WEPPOS);
	CEdit *ces1 = (CEdit *)GetDlgItem(IDC_WEPS1);
	CEdit *ces2 = (CEdit *)GetDlgItem(IDC_WEPS2);
	CButton *cbtype = (CButton *)GetDlgItem(IDC_WEPTYPE);
	if (idx == CB_ERR)
	{
		cepos->EnableWindow(FALSE);
		ces1->EnableWindow(FALSE);
		ces2->EnableWindow(FALSE);
		cbtype->EnableWindow(FALSE);
	}
	else
	{
		SetDlgItemText(IDC_WEPPOS,pship->parts[idx].position);
		SetDlgItemInt(IDC_WEPS1,pship->parts[idx].uk1,FALSE);
		SetDlgItemInt(IDC_WEPS2,pship->parts[idx].uk2,FALSE);
		cbtype->SetCheck(pship->parts[idx].part_type == 0?BST_CHECKED:BST_UNCHECKED);
		cepos->EnableWindow(TRUE);
		ces1->EnableWindow(TRUE);
		ces2->EnableWindow(TRUE);
		cbtype->EnableWindow(TRUE);
	}
}

BEGIN_MESSAGE_MAP(CShipDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnClickedCancel)
	ON_BN_CLICKED(IDC_MODELEDIT, OnClickedModeledit)
	ON_BN_CLICKED(IDC_BSUCC, &CShipDlg::OnBnClickedBsucc)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CShipLoadout, CDialog)
	ON_BN_CLICKED(IDOK, OnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnClickedCancel)
	ON_CBN_SELCHANGE(IDC_PARTSEL, OnSelchangePartsel)
	ON_LBN_SELCHANGE(IDC_WEPLIST, OnSelchangeWepsel)
	ON_BN_CLICKED(IDC_DLTOGGLE, OnBnClickedDltoggle)
	ON_LBN_SELCHANGE(IDC_PARTLIST, OnLbnSelchangePartlist)
	ON_BN_CLICKED(IDC_WCTOGGLE, OnBnClickedWctoggle)
	ON_LBN_SELCHANGE(IDC_WEPCHOICE, OnLbnSelchangeWepchoice)
	ON_BN_CLICKED(IDC_WEPADD, OnBnClickedWepadd)
	ON_BN_CLICKED(IDC_WEPDEL, OnBnClickedWepdel)
	ON_BN_CLICKED(IDC_PARTTOGGLE, OnBnClickedParttoggle)
	ON_LBN_SELCHANGE(IDC_PARTCHOICE, OnLbnSelchangePartchoice)
END_MESSAGE_MAP()


// CShipDlg message handlers

void CShipLoadout::OnBnClickedDltoggle()
{
	CButton *ctog = (CButton *)GetDlgItem(IDC_DLTOGGLE);
	SaveDL();
	DLCheck = ctog->GetCheck();
	BuildDL();
}

void CShipLoadout::BuildDL(void)
{
	CListBox *clb = (CListBox *)GetDlgItem(IDC_PARTLIST);
	clb->ResetContent();
	if (DLCheck ==BST_CHECKED) // EDIT MODE
	{
		//clb->EnableWindow(TRUE);
		for (int j=0;j<pcore->cl_Parts.GetSize();j++)
		{
			PtrCorePart ppart = pcore->cl_Parts.GetAt(j);
			CString s;
			bool IsUpgrade = false;
			for (int jj=0;jj<pcore->cl_Parts.GetSize();jj++)
			{
				PtrCorePart ppart2 = pcore->cl_Parts.GetAt(jj);
				if (ppart2->overriding_uid == ppart->uid)
					IsUpgrade = true;
			}
			if (!IsUpgrade)
			{
				if (ppart->isspec)
					s.Format("%s(%d)",pcore->ProxyPartName(ppart->usemask),ppart->uid);
				else
					s.Format("%s(%d)",ppart->name,ppart->uid);
				int idx = clb->AddString(s);
				clb->SetItemData(idx,ppart->uid);
				clb->SetSel(idx,FALSE);
				for (int i=0;i<IGCSHIPMAXPARTS;i++)
				if (DLList[i] != 0xFFFF)
				{
					if (ppart->uid == DLList[i])
						clb->SetSel(idx,TRUE);
				}
			}
		}
	}
	else // VIEW MODE
	{
		//clb->EnableWindow(FALSE);
		for (int i=0;i<IGCSHIPMAXPARTS;i++)
			if (DLList[i] != 0xFFFF)
			{
				CString s = "ERROR-UNKNOWN PART";
				for (int j=0;j<pcore->cl_Parts.GetSize();j++)
				{
					PtrCorePart ppart = pcore->cl_Parts.GetAt(j);
					if (ppart->uid == DLList[i])
					{
						if (ppart->isspec)
							s.Format("%s(%d)",pcore->ProxyPartName(ppart->usemask),ppart->uid);
						else
							s.Format("%s(%d)",ppart->name,ppart->uid);
					}
				}
				int idx = clb->AddString(s);
				clb->SetItemData(idx,DLList[i]);
			}
	}
}

void CShipLoadout::SaveDL(void)
{
	CListBox *clb = (CListBox *)GetDlgItem(IDC_PARTLIST);
	CButton *ctog = (CButton *)GetDlgItem(IDC_DLTOGGLE);

	for (int i=0;i<IGCSHIPMAXPARTS;i++)
		DLList[i] = 0xFFFF;
	int ipart = 0;
	int nCount = (DLCheck==BST_CHECKED)?clb->GetSelCount():clb->GetCount();
	if (nCount > IGCSHIPMAXPARTS)
	{
		AfxMessageBox("Too many entries in default loadout, last ones will be ignored");
		nCount = IGCSHIPMAXPARTS;
	}
	if (DLCheck==BST_CHECKED) // EDIT MODE
	{
		// retrieve the multi-selection in an array (aryParts)
		CArray<int,int> aryParts;
		aryParts.SetSize(nCount);
		clb->GetSelItems(nCount, aryParts.GetData()); 

		// fill in the partslist with aryParts
		for (int i=0;i<nCount;i++)
		{
			DLList[ipart++] = (unsigned short)clb->GetItemData(aryParts.GetAt(i));
		}
	}
	else // VIEW MODE
	{
		for (int i=0;i<nCount;i++)
		{
			DLList[ipart++] = (unsigned short)clb->GetItemData(i);
		}
	}
}

void CShipLoadout::OnLbnSelchangePartlist()
{
	CButton *ctog = (CButton *)GetDlgItem(IDC_DLTOGGLE);
	CListBox *clb = (CListBox *)GetDlgItem(IDC_PARTLIST);
	if (ctog->GetCheck() != BST_CHECKED)
	{
		LPARAM p = (LPARAM)clb->GetItemDataPtr(clb->GetCurSel());
		for (int i=0;i<clb->GetCount();i++)
			clb->SetSel(i,FALSE);
		if (p!=-1) MainUI->SelectPCE(p);
	}
}

void CShipLoadout::OnBnClickedWctoggle()
{
	CButton *ctog = (CButton *)GetDlgItem(IDC_WCTOGGLE);
	CListBox *clb = (CListBox *)GetDlgItem(IDC_WEPCHOICE);
	CListBox * cbws = (CListBox *)GetDlgItem(IDC_WEPLIST);
	int idx = cbws->GetCurSel();

	if (ctog->GetCheck() != BST_CHECKED) // unchecked so we save
	{
		int nCount = clb->GetSelCount();
		CArray<int,int> aryWeps;
		aryWeps.SetSize(nCount);
		clb->GetSelItems(nCount, aryWeps.GetData()); 
		pship->parts[idx].part_mask = 0;
		for (int i=0;i<nCount;i++)
		{
			pship->parts[idx].part_mask |= (unsigned short)clb->GetItemData(aryWeps.GetAt(i));
		}
		aryWeps.RemoveAll();
	}
	OnSelchangeWepsel();
}

void CShipLoadout::OnLbnSelchangeWepchoice()
{
	CButton *ctog = (CButton *)GetDlgItem(IDC_WCTOGGLE);
	CListBox *clb = (CListBox *)GetDlgItem(IDC_WEPCHOICE);
	if (ctog->GetCheck() != BST_CHECKED)
	{
		LPARAM p = (LPARAM)clb->GetItemDataPtr(clb->GetCurSel());
		for (int i=0;i<clb->GetCount();i++)
			clb->SetSel(i,FALSE);
		if (p != -1) MainUI->SelectPCE(p);
	}

}

void CShipLoadout::OnBnClickedWepadd()
{
	CListBox *clb = (CListBox *)GetDlgItem(IDC_WEPLIST);
	if (pship->nb_parts<IGCSHIPMAXWEAPONS)
	{
		pship->nb_parts++;
		UpdateData(FALSE);
	}
	else
	{
		MessageBox("Max number of weapons per ship reached");
	}
}

void CShipLoadout::OnBnClickedWepdel()
{
	CListBox *clb = (CListBox *)GetDlgItem(IDC_WEPLIST);
	int idx = clb->GetCurSel();
	if (idx==CB_ERR) return;
	for (int i=idx;i<clb->GetCount();i++)
		pship->parts[i] = pship->parts[i+1];
	pship->nb_parts--;
	UpdateData(FALSE);
}

void CShipLoadout::OnBnClickedParttoggle()
{
	CButton *ctog = (CButton *)GetDlgItem(IDC_PARTTOGGLE);
	CListBox *clb = (CListBox *)GetDlgItem(IDC_PARTCHOICE);
	CComboBox * cbp = (CComboBox *)GetDlgItem(IDC_PARTSEL);
	int idx = cbp->GetCurSel();
	if (idx == CB_ERR)
		return;
	idx = (int)cbp->GetItemData(idx);

	if (ctog->GetCheck() != BST_CHECKED) // unchecked so we save
	{
		int nCount = clb->GetSelCount();
		CArray<int,int> aryParts;
		aryParts.SetSize(nCount);
		clb->GetSelItems(nCount, aryParts.GetData()); 
		pship->can_use[idx] = 0;
		for (int i=0;i<nCount;i++)
		{
			pship->can_use[idx] |= (unsigned short)clb->GetItemData(aryParts.GetAt(i));
		}
		aryParts.RemoveAll();
	}
	OnSelchangePartsel();
}

void CShipLoadout::OnLbnSelchangePartchoice()
{
	CButton *ctog = (CButton *)GetDlgItem(IDC_PARTTOGGLE);
	CListBox *clb = (CListBox *)GetDlgItem(IDC_PARTCHOICE);
	if (ctog->GetCheck() != BST_CHECKED)
	{
		LPARAM p = (LPARAM)clb->GetItemDataPtr(clb->GetCurSel());
		for (int i=0;i<clb->GetCount();i++)
			clb->SetSel(i,FALSE);
		if (p!=-1) MainUI->SelectPCE(p);
	}
}

void CShipDlg::OnBnClickedBsucc()
{
	if (!pship) return;
	if (!pcore) return;
	if (pship->overriding_uid == -1) return;
	PtrCoreShip succ = pcore->FindShip(pship->overriding_uid);
	if (succ)
		MainUI->SelectPCE((LPARAM)succ);
	else
		AfxMessageBox("invalid successor!");
}
