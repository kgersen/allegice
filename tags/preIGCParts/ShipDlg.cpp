// ShipDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICE.h"
#include "corestruct.h"
#include "MDLView.h"
#include "ShipDlg.h"
#include ".\shipdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
	if (!pship) return;
	if (!pcore) return;
	ASSERT(sArtPath != "");
	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		name = pship->name;
		model = pship->modelName;
		descr = pship->description;
		group = pship->groupID;
		obj = pship->iconName;
		mdlbmp.LoadMDLFile(sArtPath +"\\"+ obj + "bmp.mdl");

		CComboBox *cbac = (CComboBox *)GetDlgItem(IDC_AC);
		cbac->SetCurSel(pship->defenseType);
		uid = pship->hullID;
		CButton *cbb;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_BOARD);
		cbb->SetCheck((pship->habmCapabilities & c_habmBoard)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_RESCUE);
		cbb->SetCheck((pship->habmCapabilities & c_habmRescue)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_LIFEPOD);
		cbb->SetCheck((pship->habmCapabilities & c_habmLifepod)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_NOPICKUP);
		cbb->SetCheck((pship->habmCapabilities & c_habmCaptureThreat)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_NOEJECTION);
		cbb->SetCheck((pship->habmCapabilities & c_habmLandOnCarrier)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_NORIPCORD);
		cbb->SetCheck((pship->habmCapabilities & c_habmNoRipcord)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_ISRIP);
		cbb->SetCheck((pship->habmCapabilities & c_habmIsRipcordTarget)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_FIGHTER);
		cbb->SetCheck((pship->habmCapabilities & c_habmFighter)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_CAPITAL);
		cbb->SetCheck((pship->habmCapabilities & c_habmRemoteLeadIndicator)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_F2);
		cbb->SetCheck(((pship->habmCapabilities) & c_habmThreatToStation)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_ISDOCK);
		cbb->SetCheck(((pship->habmCapabilities) & c_habmCarrier)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_F8);
		cbb->SetCheck(((pship->habmCapabilities) & c_habmLeadIndicator)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_ISSMALLRIP);
		cbb->SetCheck(((pship->habmCapabilities) & c_habmIsLtRipcordTarget)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_RIPTOSMALL);
		cbb->SetCheck(((pship->habmCapabilities) & c_habmCanLtRipcord)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_MINER);
		cbb->SetCheck(((pship->habmCapabilities) & c_habmMiner)?BST_CHECKED:BST_UNCHECKED);
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_CONSTRUCTOR);
		cbb->SetCheck(((pship->habmCapabilities) & c_habmBuilder)?BST_CHECKED:BST_UNCHECKED);

	}
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_MODEL, model);
	DDX_Text(pDX, IDC_OBJ, obj);
	DDX_Text(pDX, IDC_DESCRIPTION, descr);
	DDX_Text(pDX, IDC_GROUP, group);
	//DDX_Text(pDX, IDC_TODO1, todo1);
	DDX_Text(pDX, IDC_COUT,pship->price);
	DDX_Text(pDX, IDC_S1, pship->mass);
	DDX_Text(pDX, IDC_S2, pship->signature);
	DDX_Text(pDX, IDC_S3, pship->speed);
	DDX_Text(pDX, IDC_S4, pship->maxTurnRates[c_axisYaw]);
	DDX_Text(pDX, IDC_S5, pship->maxTurnRates[c_axisPitch]);
	DDX_Text(pDX, IDC_S6, pship->maxTurnRates[c_axisRoll]);
	DDX_Text(pDX, IDC_S7, pship->turnTorques[c_axisYaw]);
	DDX_Text(pDX, IDC_S8, pship->turnTorques[c_axisPitch]);
	DDX_Text(pDX, IDC_S9, pship->turnTorques[c_axisRoll]);
	DDX_Text(pDX, IDC_S10, pship->thrust);
	DDX_Text(pDX, IDC_S11, pship->sideMultiplier);
	DDX_Text(pDX, IDC_S12, pship->backMultiplier);
	DDX_Text(pDX, IDC_S13, pship->scannerRange);
	DDX_Text(pDX, IDC_S14, pship->maxFuel);
	DDX_Text(pDX, IDC_S15, pship->ecm);
	DDX_Text(pDX, IDC_S16, pship->length);
	DDX_Text(pDX, IDC_S17, pship->maxEnergy);
	DDX_Text(pDX, IDC_S18, pship->rechargeRate);
	DDX_Text(pDX, IDC_S19, pship->ripcordSpeed);
	DDX_Text(pDX, IDC_S20, pship->ripcordCost);
	DDX_Text(pDX, IDC_UID, uid);
	DDX_Text(pDX, IDC_OVUID, pship->successorHullID);

	DDX_Text(pDX, IDC_SOUNDINT, pship->interiorSound);
	DDX_Text(pDX, IDC_SOUNDEXT, pship->exteriorSound);
	DDX_Text(pDX, IDC_SOUNDTHI, pship->mainThrusterInteriorSound);
	DDX_Text(pDX, IDC_SOUNDTHE, pship->mainThrusterExteriorSound);
	DDX_Text(pDX, IDC_SOUNDTUI, pship->manuveringThrusterInteriorSound);
	DDX_Text(pDX, IDC_SOUNDTUE, pship->manuveringThrusterExteriorSound);

	DDX_Text(pDX, IDC_HP, pship->hitPoints);

	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		strcpy(pship->name,name);
		strcpy(pship->modelName,model);
		strcpy(pship->iconName,obj);
		strncpy(pship->description,descr,IGC_DESCRIPTIONMAX);
		pship->groupID = group;
		CComboBox *cbac = (CComboBox *)GetDlgItem(IDC_AC);
		pship->defenseType = cbac->GetCurSel();

		CButton *cbb;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_BOARD);
		pship->habmCapabilities = cbb->GetCheck()?c_habmBoard:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_RESCUE);
		pship->habmCapabilities += cbb->GetCheck()?c_habmRescue:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_LIFEPOD);
		pship->habmCapabilities += cbb->GetCheck()?c_habmLifepod:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_NOPICKUP);
		pship->habmCapabilities += cbb->GetCheck()?c_habmCaptureThreat:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_NOEJECTION);
		pship->habmCapabilities += cbb->GetCheck()?c_habmLandOnCarrier:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_NORIPCORD);
		pship->habmCapabilities += cbb->GetCheck()?c_habmNoRipcord:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_ISRIP);
		pship->habmCapabilities += cbb->GetCheck()?c_habmIsRipcordTarget:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_FIGHTER);
		pship->habmCapabilities += cbb->GetCheck()?c_habmFighter:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_CAPITAL);
		pship->habmCapabilities += cbb->GetCheck()?c_habmRemoteLeadIndicator:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_F2);
		pship->habmCapabilities += cbb->GetCheck()?c_habmThreatToStation:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_ISDOCK);
		pship->habmCapabilities += cbb->GetCheck()?c_habmCarrier:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_F8);
		pship->habmCapabilities += cbb->GetCheck()?c_habmLeadIndicator:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_ISSMALLRIP);
		pship->habmCapabilities += cbb->GetCheck()?c_habmIsLtRipcordTarget:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_RIPTOSMALL);
		pship->habmCapabilities += cbb->GetCheck()?c_habmCanLtRipcord:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_MINER);
		pship->habmCapabilities += cbb->GetCheck()?c_habmMiner:0;
		cbb = (CButton *)CWnd::GetDlgItem(IDC_HB_CONSTRUCTOR);
		pship->habmCapabilities += cbb->GetCheck()?c_habmBuilder:0;
	}
	CDialog::DoDataExchange(pDX);
}

void CShipLoadout::DoDataExchange(CDataExchange* pDX)
{
	int nbparts;
	if (!pship) return;
	if (!pcore) return;
	ASSERT(sArtPath != "");
	CListBox *clb = (CListBox *)GetDlgItem(IDC_WEPLIST);
	if (!pDX->m_bSaveAndValidate) // data to dialog
	{

		nbparts = pship->maxWeapons;

		// IDC_PARTLIST
		for (int i=0;i<c_cMaxPreferredPartTypes;i++)
			DLList[i] = pship->preferredPartsTypes[i];
		BuildDL();

		clb->ResetContent();
		for (int p=0;p<pship->maxWeapons;p++)
		{
			CString wpn;
			wpn.Format("PART %d",p);
			clb->AddString(wpn);
		}
		if (pship->maxWeapons >0)
		{
			clb->SetCurSel(0);
		}
		OnSelchangeWepsel();
		OnSelchangePartsel();
	}
	DDX_Text(pDX, IDC_SS1, pship->maxAmmo);
	DDX_Text(pDX, IDC_SS5, pship->capacityMagazine);
	DDX_Text(pDX, IDC_SS6, pship->capacityDispenser);
	DDX_Text(pDX, IDC_SS7, pship->capacityChaffLauncher);
	DDX_Text(pDX, IDC_NBPARTS, nbparts);


	if (pDX->m_bSaveAndValidate) // dialog to data
	{

		pship->maxWeapons = clb->GetCount();//nbparts;

		// Default loadout
		SaveDL();
		for (int i=0;i<c_cMaxPreferredPartTypes;i++)
			pship->preferredPartsTypes[i] = DLList[i]; 

		int idx;
		//CComboBox * cbpm = (CComboBox *)GetDlgItem(IDC_PARTSEL);
		//idx = cbpm->GetCurSel();
		//if (idx != CB_ERR)
		//{
		//	idx = (int)cbpm->GetItemData(idx);
		//	pship->can_use[idx] = 0;
		//	for (int i=0;i<16;i++) 
		//	{
		//		cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
		//		pship->can_use[idx] += cbb->GetCheck()?(1<<i):0;
		//	}
		//}
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
			pship->GetHardpointData(idx)->bFixed = (cbtype->GetCheck()==BST_CHECKED)?0:1;
			CString wp_pos;
			int wp_uk1,wp_uk2;
			DDX_Text(pDX, IDC_WEPPOS, wp_pos);
			DDX_Text(pDX, IDC_WEPS1, wp_uk1);
			DDX_Text(pDX, IDC_WEPS2, wp_uk2);

			strcpy_s(pship->GetHardpointData(idx)->frameName,c_cbFileName,wp_pos);
			pship->GetHardpointData(idx)->interiorSound = wp_uk1;
			pship->GetHardpointData(idx)->turnSound = wp_uk2;
		}
		// recompute weapon slots (non turret)
		pship->maxFixedWeapons = 0;
		for (int p=0;p<pship->maxWeapons;p++)
		{
			if (pship->GetHardpointData(p)->bFixed == 1)
				pship->maxFixedWeapons++;
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
	for (int i = 0;i<ET_MAX;i++)
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
	//for (int i=0;i<16;i++) 
	//{
	//	CButton *cbb = (CButton *)CWnd::GetDlgItem(IDC_USEM0+i);
	//	if (idx == CB_ERR)
	//	{
	//		cbb->EnableWindow(FALSE);
	//		cbb->SetCheck(BST_UNCHECKED);
	//	}
	//	else
	//	{
	//		cbb->SetCheck((pship->can_use[idx] & (1<<i))?BST_CHECKED:BST_UNCHECKED);
	//		cbb->EnableWindow(TRUE);
	//	}
	//}


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
					if (ppart->usemask & pship->pmEquipment[idx])
					{
						pname = ppart->name;
						pcpart = (LPARAM)ppart;
					}
				if (ppart->isspec)
				{
					PtrCoreEntry pce = pcore->ProxyPart(ppart->usemask);
					if (pce->IGCPartType == idx)
					if (pce->usemask & pship->pmEquipment[idx])
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
						if (ppart->usemask & pship->pmEquipment[idx])
							bsel = true;
					}
					if (ppart->isspec)
					{
						PtrCoreEntry pce = pcore->ProxyPart(ppart->usemask);
						if ((pce->IGCPartType == idx) && (pce->usemask & umask))
						{
							pname = pcore->ProxyPartName(ppart->usemask);
							pcmask = pce->usemask;
							if (pce->usemask & pship->pmEquipment[idx]) bsel = true;
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

	//for (int i=0;i<16;i++) 
	//{
	//	CButton *cbb = (CButton *)GetDlgItem(IDC_USEM0+16+i);
	//	if (idx == CB_ERR)
	//	{
	//		cbb->EnableWindow(FALSE);
	//		cbb->SetCheck(BST_UNCHECKED);
	//	}
	//	else
	//	{
	//		cbb->SetCheck((pship->parts[idx].part_mask & (1<<i))?BST_CHECKED:BST_UNCHECKED);
	//		cbb->EnableWindow(TRUE);
	//	}
	//}

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
					if (ppart->type == ET_Weapon)
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
								if (pship->GetHardpointData(idx)->partMask & ppart->usemask)
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
			if (ppart->type == ET_Weapon)
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
						if (pship->GetHardpointData(idx)->partMask & ppart->usemask)
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
		SetDlgItemText(IDC_WEPPOS,pship->GetHardpointData(idx)->frameName);
		SetDlgItemInt(IDC_WEPS1,pship->GetHardpointData(idx)->interiorSound,FALSE);
		SetDlgItemInt(IDC_WEPS2,pship->GetHardpointData(idx)->turnSound,FALSE);
		cbtype->SetCheck(pship->GetHardpointData(idx)->bFixed == 0?BST_CHECKED:BST_UNCHECKED);
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
	ON_BN_CLICKED(IDC_BEDITDESCR, &CShipDlg::OnBnClickedBeditdescr)
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
	ON_BN_CLICKED(IDC_DLUP, &CShipLoadout::OnBnClickedDlup)
	ON_BN_CLICKED(IDC_DLDOWN, &CShipLoadout::OnBnClickedDldown)
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
		GetDlgItem(IDC_DLUP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_DLDOWN)->ShowWindow(SW_HIDE);
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
				for (int i=0;i<c_cMaxPreferredPartTypes;i++)
				if (DLList[i] != -1)
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
		GetDlgItem(IDC_DLUP)->ShowWindow(SW_SHOWNA);
		GetDlgItem(IDC_DLDOWN)->ShowWindow(SW_SHOWNA);
		for (int i=0;i<c_cMaxPreferredPartTypes;i++)
			if (DLList[i] != -1)
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

	for (int i=0;i<c_cMaxPreferredPartTypes;i++)
		DLList[i] = -1;
	int ipart = 0;
	int nCount = (DLCheck==BST_CHECKED)?clb->GetSelCount():clb->GetCount();
	if (nCount > c_cMaxPreferredPartTypes)
	{
		AfxMessageBox("Too many entries in default loadout, last ones will be ignored");
		nCount = c_cMaxPreferredPartTypes;
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
			DLList[ipart++] = (PartID)clb->GetItemData(aryParts.GetAt(i));
		}
	}
	else // VIEW MODE
	{
		for (int i=0;i<nCount;i++)
		{
			DLList[ipart++] = (PartID)clb->GetItemData(i);
		}
	}
}

void CShipLoadout::OnLbnSelchangePartlist()
{
	CButton *ctog = (CButton *)GetDlgItem(IDC_DLTOGGLE);
	CListBox *clb = (CListBox *)GetDlgItem(IDC_PARTLIST);
	if (ctog->GetCheck() != BST_CHECKED)
	{
		//LPARAM p = (LPARAM)clb->GetItemDataPtr();
		int idx = clb->GetCurSel();
		for (int i=0;i<clb->GetCount();i++)
			if (i != idx) 
				clb->SetSel(i,FALSE);
		//if (p!=-1) MainUI->SelectPCE(p);
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
		pship->GetHardpointData(idx)->partMask = 0;
		for (int i=0;i<nCount;i++)
		{
			pship->GetHardpointData(idx)->partMask |= (unsigned short)clb->GetItemData(aryWeps.GetAt(i));
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
	if (pship->maxWeapons<c_maxMountedWeapons)
	{
		pship->maxWeapons++;
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
		*(pship->GetHardpointData(i)) = *(pship->GetHardpointData(i+1));
	pship->maxWeapons--;
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
		pship->pmEquipment[idx] = 0;
		for (int i=0;i<nCount;i++)
		{
			pship->pmEquipment[idx] |= (unsigned short)clb->GetItemData(aryParts.GetAt(i));
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
	if (pship->successorHullID == -1) return;
	PtrCoreShip succ = pcore->FindShip(pship->successorHullID);
	if (succ)
		MainUI->SelectPCE((LPARAM)succ);
	else
		AfxMessageBox("invalid successor!");
}

void CShipDlg::OnBnClickedBeditdescr()
{
	CDescrDlg dlg(pship->description);
	if (dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_DESCRIPTION,pship->description);
}

void CShipLoadout::OnBnClickedDlup()
{
	CButton *ctog = (CButton *)GetDlgItem(IDC_DLTOGGLE);
	CListBox *clb = (CListBox *)GetDlgItem(IDC_PARTLIST);
	if (ctog->GetCheck() == BST_CHECKED) return;
	int idx = clb->GetCurSel();
	if (idx == CB_ERR)return;
	if (idx == 0) return;
	CString currs; clb->GetText(idx,currs); PartID currp = (PartID) clb->GetItemData(idx);
	clb->DeleteString(idx);
	idx = clb->InsertString(idx-1,currs);
	clb->SetItemData(idx,currp);
	clb->SetSel(idx,true);
	//SaveDL();
}

void CShipLoadout::OnBnClickedDldown()
{
	CButton *ctog = (CButton *)GetDlgItem(IDC_DLTOGGLE);
	CListBox *clb = (CListBox *)GetDlgItem(IDC_PARTLIST);
	if (ctog->GetCheck() == BST_CHECKED) return;
	int idx = clb->GetCurSel();
	if (idx == CB_ERR) return;
	if (idx == (clb->GetCount()-1)) return;

	CString currs; clb->GetText(idx,currs); PartID currp = (PartID) clb->GetItemData(idx);
	clb->DeleteString(idx);
	idx = clb->InsertString(idx+1,currs);
	clb->SetItemData(idx,currp);
	clb->SetSel(idx,true);
	//SaveDL();
}
