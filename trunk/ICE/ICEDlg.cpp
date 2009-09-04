// ICEDlg.cpp : implementation file
//
#include "stdafx.h"
#include "ICE.h"
#include "corestruct.h"
#include "CivDlg.h"
#include "ChaffDlg.h"
#include "DevelDlg.h"
#include "DroneDlg.h"
#include "MineDlg.h"
#include "MissileDlg.h"
#include "PartDlg.h"
#include "ProbeDlg.h"
#include "ProjectileDlg.h"
#include "ShipDlg.h"
#include "StationDlg.h"
#include "ConstantsDlg.h"
#include "TreasureDlg.h"
#include "ICEDlg.h"
#include ".\icedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
private:
	CString sVersion;
public:
	CAboutDlg(CString sVer);

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg(CString sVer) : CDialog(CAboutDlg::IDD)
{
	sVersion = sVer;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	SetDlgItemText(IDC_VERLABEL,sVersion);
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CICEDlg dialog



CICEDlg::CICEDlg(CWnd* pParent)
	: CDialog(CICEDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	sTechName = "";
	pTechTree = NULL;
	pTechTreeLocal = NULL;
	curpce = NULL;
	sCoreArg = "";
	ClearFilter();
}

void CICEDlg::DoDataExchange(CDataExchange* pDX)
{
	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
	}
	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		OnClickedRefresh();
	}
	ShowTechEntry(pTechTree,pTechTreeLocal);
	ShowTechBit(pTechTree,pTechTreeLocal,-1);
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CICEDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_MAINTREE, OnSelchangeMainTree)
	ON_BN_CLICKED(IDC_ABOUT, OnClickedAbout)
	ON_BN_CLICKED(IDLOAD, OnClickedLoad)
	ON_BN_CLICKED(IDSAVE, OnClickedSave)
	ON_BN_CLICKED(IDSAVEAS, OnClickedSaveas)
	ON_BN_CLICKED(IDCANCEL, OnClickedCancel)
	ON_BN_CLICKED(IDQUIT, OnClickedQuit)
//	ON_CBN_SELCHANGE(IDC_TECHLIST, OnSelchangeTechlist)
//	ON_BN_CLICKED(IDC_TECHVAL, OnClickTechVal)
	ON_BN_CLICKED(IDC_REFRESH, OnClickedRefresh)
	ON_BN_CLICKED(IDC_CLEARPRE, OnBnClickedClearpre)
	ON_BN_CLICKED(IDC_CLEARDEF, OnBnClickedCleardef)
	ON_BN_CLICKED(IDC_ADD, OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DELETE, OnBnClickedDelete)
//	ON_EN_CHANGE(IDC_TECHTREE, OnEnChangeTechtree)
	ON_BN_CLICKED(IDC_TECHTREEUP, OnBnClickedTechtreeup)
	ON_BN_CLICKED(IDC_TECHTREEDOWN, OnBnClickedTechtreedown)
	ON_BN_CLICKED(IDC_TOGGLEPRE, OnBnClickedTogglepre)
	ON_BN_CLICKED(IDC_TOGGLEDEF, OnBnClickedToggledef)
	ON_EN_CHANGE(IDC_TECHTREEIDX, OnEnChangeTechtreeidx)
	ON_EN_SETFOCUS(IDC_TECHTREEIDX, OnEnSetfocusTechtreeidx)
	ON_EN_SETFOCUS(IDC_TECHTREE, OnEnSetfocusTechtree)
	ON_BN_CLICKED(IDC_STORE1STORE, OnBnClickedStore1store)
	ON_BN_CLICKED(IDC_STORE2STORE, OnBnClickedStore2store)
	ON_BN_CLICKED(IDC_STORE1RECALL, OnBnClickedStore1recall)
	ON_BN_CLICKED(IDC_STORE2RECALL, OnBnClickedStore2recall)
	ON_BN_CLICKED(IDC_CKSORT, OnBnClickedCksort)
	ON_BN_CLICKED(IDC_MOVEUP, OnBnClickedMoveup)
	ON_BN_CLICKED(IDC_MOVEDOWN, OnBnClickedMovedown)
	ON_BN_CLICKED(IDC_TOGGLELOCAL, OnBnClickedTogglelocal)
	ON_BN_CLICKED(IDC_CLEARLOCAL, OnBnClickedClearlocal)
//	ON_NOTIFY(TCN_SELCHANGE, IDC_MAINTAB, OnTcnSelchangeMaintab)
//	ON_WM_KEYDOWN()
ON_BN_CLICKED(IDC_BUTFILTER, OnBnClickedButfilter)
ON_BN_CLICKED(IDC_CLEARFILTER, OnBnClickedClearfilter)
//ON_BN_CLICKED(IDC_ADDTOFILTER, OnBnClickedAddtofilter)
//ON_BN_CLICKED(IDC_REMFROMFILTER, OnBnClickedRemfromfilter)
//ON_NOTIFY(TVN_BEGINDRAG, IDC_MAINTREE, OnTvnBegindragMaintree)
//ON_BN_CLICKED(IDC_GENHTML, OnBnClickedGenhtml)
ON_BN_CLICKED(IDC_VALIDATE, &CICEDlg::OnBnClickedValidate)
ON_BN_CLICKED(IDC_BBACK, &CICEDlg::OnBnClickedBback)
ON_BN_CLICKED(IDC_COMPARE, &CICEDlg::OnBnClickedCompare)
ON_BN_CLICKED(IDC_DUMP, &CICEDlg::OnBnClickedDump)
ON_BN_CLICKED(IDC_CHKART, &CICEDlg::OnBnClickedChkart)
ON_LBN_SELCHANGE(IDC_TTLIST, &CICEDlg::OnLbnSelchangeTtlist)
ON_NOTIFY(TCN_SELCHANGE, IDC_MAINTAB, &CICEDlg::OnTcnSelchangeMaintab)
END_MESSAGE_MAP()


// CICEDlg message handlers

BOOL CICEDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	// Icons
	((CButton *)GetDlgItem(IDC_BBACK))->SetIcon(iBackIcon);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//
	curdiag = NULL;
	sCorename = "";
	sCorepath = "";
	CWnd *pname = CWnd::GetDlgItem(IDC_FILENAME);
	pname->SetWindowText("no core loaded");
	pigccore = NULL;
	changed = false;
	CButton *cbck = (CButton *)CWnd::GetDlgItem(IDC_CKSORT);
	cbck->SetCheck(BST_CHECKED);
	ShowMoveButtons(false);

	CTabCtrl *cbtab = (CTabCtrl *)CWnd::GetDlgItem(IDC_MAINTAB);
	cbtab->DeleteAllItems();
	cbtab->InsertItem(0,"&Properties");
	cbtab->InsertItem(1,"&Tech tree");
	ShowTechTree(SW_HIDE);

	dlgCiv.Create(IDD_CIVDLG,this);
	dlgChaff.Create(IDD_CHAFFDLG,this);
	dlgDevel.Create(IDD_DEVELDLG,this);
	dlgDrone.Create(IDD_DRONEDLG,this); dlgDrone.MainUI = this; dlgDrone.SetIcons(iJumpIcon);
	dlgMine.Create(IDD_MINEDLG,this);
	dlgMissile.Create(IDD_MISSILEDLG,this);
	dlgPart.Create(IDD_PARTDLG,this);
	dlgProbe.Create(IDD_PROBEDLG,this);
	dlgProjectile.Create(IDD_PROJECTILEDLG,this);
	dlgShip.Create(IDD_SHIPDLG,this);
	dlgShipLoadout.Create(IDD_LOADOUT,this);
	dlgStation.Create(IDD_STATIONDLG,this);
	dlgConstants.Create(IDD_CONSTANTSDLG,this);
	dlgTreasure.Create(IDD_TREASUREDLG,this);
	dlgConstants.MainUI = this;
	dlgDevel.sArtPath = cArtPath;
	dlgDrone.sArtPath = cArtPath;
	dlgChaff.sArtPath = cArtPath; dlgChaff.MainUI = this; dlgChaff.SetIcons(iJumpIcon);
	dlgProjectile.sArtPath = cArtPath; dlgProjectile.MainUI = this;
	dlgShip.sArtPath = cArtPath; dlgShip.MainUI = this; dlgShip.SetIcons(iJumpIcon);
	dlgShipLoadout.sArtPath = cArtPath; dlgShipLoadout.MainUI = this;
	dlgStation.sArtPath = cArtPath; dlgStation.MainUI = this; dlgStation.SetIcons(iJumpIcon);
	dlgProbe.sArtPath = cArtPath; dlgProbe.MainUI = this; dlgProbe.SetIcons(iJumpIcon);
	dlgMine.sArtPath = cArtPath; dlgMine.MainUI = this; dlgMine.SetIcons(iJumpIcon);
	dlgMissile.sArtPath = cArtPath; dlgMissile.MainUI = this; dlgMissile.SetIcons(iJumpIcon);
	dlgCiv.sArtPath = cArtPath; dlgCiv.MainUI = this; dlgCiv.SetIcons(iJumpIcon);
	dlgPart.sArtPath = cArtPath; dlgPart.MainUI = this; dlgPart.SetIcons(iJumpIcon);
	if (sCoreArg != "")
	{
		//AfxMessageBox(sCoreArg);
		LoadCore(sCoreArg);

	}

	CButton *cab = (CButton *)GetDlgItem(IDC_AUTOBACKUP);
	cab->SetCheck(BST_CHECKED);

	SetWindowText(sTitle);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CICEDlg::RefreshStores(PtrCoreEntry pce)
{
	if (store1 == pce->entry)
		SetDlgItemText(IDC_STORE1,pce->name);
	if (store2 == pce->entry)
		SetDlgItemText(IDC_STORE2,pce->name);
}
void CICEDlg::FreeTreePCE()
{
	if (maintree)
		FreeTreePCE(maintree,maintree->GetRootItem());
}
void CICEDlg::FreeTreePCE(CTreeCtrl *tree,HTREEITEM item)
{
	if (!tree) return;
	HTREEITEM hCurrent = item; 
	while (hCurrent != NULL)
	{
		if (tree->ItemHasChildren(hCurrent))
		{
			HTREEITEM hChildItem = tree->GetChildItem(hCurrent);
			while (hChildItem != NULL)
			{
				FreeTreePCE(tree,hChildItem);
				hChildItem = tree->GetNextItem(hChildItem, TVGN_NEXT);
			}
		}
		PtrCoreEntry pce = (PtrCoreEntry)tree->GetItemData(hCurrent);
		if (pce) {
			delete pce;
			tree->SetItemData(hCurrent,NULL);
		}
		hCurrent = tree->GetNextItem(hCurrent, TVGN_NEXT);
	}
}
void CICEDlg::BuildTree(void)
{
	if (!pigccore) return;
	maintree = (CTreeCtrl *)CWnd::GetDlgItem(IDC_MAINTREE);
	// TODO, memory leak: show free all pce in current maintree
	// TEST for 2.97 pre-release: FreeTreePCE();
	maintree->DeleteAllItems();
	SetDlgItemText(IDC_STORE1,"");
	SetDlgItemText(IDC_STORE2,"");

	HTREEITEM tvisort;
	CButton *cbck = (CButton *)CWnd::GetDlgItem(IDC_CKSORT);
	if (cbck->GetCheck()==BST_CHECKED)
	{
		tvisort = TVI_SORT;
	}
	else
	{
		tvisort = NULL;
	}


	TVINSERTSTRUCT tvInsert;
	tvInsert.hParent = NULL;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT;
	tvInsert.item.pszText = _T("CORE");

	{
		PtrCoreEntry pce = new CoreEntry;
		pce->tag = OT_constants;
		pce->entry = (LPARAM)pigccore->pConstants;
		pce->name = "Globals";
		RefreshStores(pce);
		hConstants = maintree->InsertItem(TVIF_TEXT|TVIF_PARAM,_T(pce->name), 0, 0, 0, 0,  (LPARAM)pce, NULL, NULL);
	}
	hCivs      = maintree->InsertItem(_T("Factions"));
	hDevels    = maintree->InsertItem(_T("Devels"));
	hDrones    = maintree->InsertItem(_T("Drones"));
	hParts     = maintree->InsertItem(_T("Parts"));
	hProjectiles= maintree->InsertItem(_T("Projectiles"));
	hShips     = maintree->InsertItem(_T("Ships"));
	hStationsRoot  = maintree->InsertItem(_T("Stations"));
	hTreasureSets = maintree->InsertItem(_T("Treasure sets"));
	for (int j=0;j<MAXCIVS;j++) hStations[j] = NULL;
    int j=0;
	for (j=0;j<pigccore->cl_Civs.GetSize();j++)
	{
		PtrCoreCiv pciv = pigccore->cl_Civs.GetAt(j);
		//maintree->InsertItem(pciv->name, hCivs, TVI_SORT);
		PtrCoreEntry pce = new CoreEntry;
		pce->tag = OT_civilization;
		pce->entry = (LPARAM)pciv;
		pce->name.Format("Faction: %s (%d)",pciv->name,pciv->civilizationID);
		RefreshStores(pce);
		maintree->InsertItem(TVIF_TEXT|TVIF_PARAM,pciv->name, 0, 0, 0, 0,  (LPARAM)pce, hCivs, tvisort);
		//hStations[j] = maintree->InsertItem(pciv->name, hStationsRoot, TVI_SORT);
	}

	// to handle stations that have no civs (like in static_core)
	for (;j<MAXCIVS;j++)
	{
		hStations[j] = hStationsRoot;
	}
	hStations[j] = hStationsRoot;

	for (int j=0;j<MAXPATHS;j++)
	{
		hTechPaths[j] = maintree->InsertItem(sPathsNames[j], hDevels, NULL);
	}
	bool bFilter = false;
	for (int i=0;i<50;i++)
		bFilter |= (tFilter[i] != 0);
	if (bFilter)
		SetDlgItemText(IDC_FILTERACTIVE,"Filtered");
	else
		SetDlgItemText(IDC_FILTERACTIVE,"");
	for (int j=0;j<pigccore->cl_Devels.GetSize();j++)
	{
		PtrCoreDevel pdevel = pigccore->cl_Devels.GetAt(j);
		if (bFilter & IsFiltered((UCHAR*)&(pdevel->ttbmRequired))) //TODO
			continue;
		CString s;
		PtrCoreEntry pce = new CoreEntry;
		pce->tag = OT_development;
		pce->entry = (LPARAM)pdevel;
		s.Format("%s (%d)",pdevel->name,pdevel->developmentID);
		pce->name.Format("Devel: %s",s);
		RefreshStores(pce);
		maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hTechPaths[pdevel->groupID], tvisort);
	}
	for (int j=0;j<pigccore->cl_Drones.GetSize();j++)
	{
		PtrCoreDrone pdrone = pigccore->cl_Drones.GetAt(j);
		if (bFilter & IsFiltered((UCHAR*)&(pdrone->ttbmRequired))) //TODO
			continue;
		CString s;
		PtrCoreEntry pce = new CoreEntry;
		pce->tag = OT_droneType;
		pce->entry = (LPARAM)pdrone;
		s.Format("%s (%d)",pdrone->name,pdrone->droneTypeID);
		pce->name.Format("Drone: %s",s);
		RefreshStores(pce);
		maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hDrones, tvisort);
	}

	for (int j=0;j<pigccore->cl_Ships.GetSize();j++)
	{
		PtrCoreShip pship = pigccore->cl_Ships.GetAt(j);
		if (bFilter & IsFiltered((UCHAR*)&(pship->ttbmRequired))) //TODO
			continue;
		CString s;
		PtrCoreEntry pce = new CoreEntry;
		pce->tag = OT_hullType;
		pce->entry = (LPARAM)pship;
		s.Format("%s (%d)",pship->name,pship->hullID);
		pce->name.Format("Ship: %s",s);
		RefreshStores(pce);
		maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hShips, tvisort);
	}

	for (int j=0;j<pigccore->cl_Parts.GetSize();j++)
	{
		PtrCorePart ppart = pigccore->cl_Parts.GetAt(j);
		if (bFilter & IsFiltered((UCHAR*)&(ppart->ttbmRequired))) //TODO
			continue;
		//if (!ppart->isspec)
		{
			CString s;
			PtrCoreEntry pce = new CoreEntry;
			pce->tag = OT_partType;
			pce->entry = (LPARAM)ppart;
			s.Format("%s (%d)",ppart->name,ppart->partID);
			pce->name.Format("Part: %s",s);
			RefreshStores(pce);
			maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hParts, tvisort);
		}
	//	if (ppart->isspec && tvisort==NULL)
	//	{
	//		PtrCoreEntry prox = pigccore->ProxyPart(ppart->usemask);
	//		if (prox)
	//		{
	//			CString s;
	//			PtrCoreEntry pce = new CoreEntry;
	//			switch (prox->tag)
	//			{
	//				case OT_chaffType:
	//				{
	//					PtrCoreCounter pcounter = (PtrCoreCounter)prox->entry;
	//					pce->tag = (ObjectType)prox->tag;
	//					pce->entry = (LPARAM)pcounter;
	//					s.Format("%s (%d)(%d)",pcounter->launcherDef.name,pcounter->expendabletypeID,ppart->uid);
	//					pce->name.Format("Counter: %s",s);
	//					RefreshStores(pce);
	//					maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hParts, tvisort);
	//				}
	//				break;
	//				case OT_probeType:
	//				{
	//					PtrCoreProbe pprobe = (PtrCoreProbe)prox->entry;
	//					pce->tag = (ObjectType)prox->tag;
	//					pce->entry = (LPARAM)pprobe;
	//					s.Format("%s (%d)(%d)",pprobe->launcherDef.name,pprobe->expendabletypeID,ppart->uid);
	//					pce->name.Format("Probe: %s",s);
	//					RefreshStores(pce);
	//					maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hParts, tvisort);
	//				}
	//				break;
	//				case OT_mineType:
	//				{
	//					PtrCoreMine pmine = (PtrCoreMine)prox->entry;
	//					pce->tag = (ObjectType)prox->tag;
	//					pce->entry = (LPARAM)pmine;
	//					s.Format("%s (%d)(%d)",pmine->launcherDef.name,pmine->expendabletypeID,ppart->uid);
	//					pce->name.Format("Mine: %s",s);
	//					RefreshStores(pce);
	//					maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hParts, tvisort);
	//				}
	//				break;
	//				case OT_missileType:
	//				{
	//					PtrCoreMissile pmissile = (PtrCoreMissile)prox->entry;
	//					pce->tag = (ObjectType)prox->tag;
	//					pce->entry = (LPARAM)pmissile;
	//					s.Format("%s (%d)(%d)",pmissile->launcherDef.name,pmissile->expendabletypeID,ppart->uid);
	//					pce->name.Format("Missile: %s",s);
	//					RefreshStores(pce);
	//					maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hParts, tvisort);
	//				}
	//				break;
	//			}
	//			delete prox;
	//		}
	//	}
	}
	if (tvisort!=NULL)
	{
		hProbes    = maintree->InsertItem(_T("Probes"),hParts, TVI_FIRST);
		hMissiles  = maintree->InsertItem(_T("Missiles"),hParts, TVI_FIRST);
		hMines     = maintree->InsertItem(_T("Mines"),hParts, TVI_FIRST);
		hCounters  = maintree->InsertItem(_T("Chaffs"),hParts, TVI_FIRST);

		for (int j=0;j<pigccore->cl_Counters.GetSize();j++)
		{
			PtrCoreCounter pcounter = pigccore->cl_Counters.GetAt(j);
			if (bFilter & IsFiltered((UCHAR*)&(pcounter->launcherDef.ttbmRequired))) //TODO
				continue;
			CString s;
			PtrCoreEntry pce = new CoreEntry;
			pce->tag = (ObjectType)OT_chaffType;
			pce->entry = (LPARAM)pcounter;
			CString pxs = "";
			PtrCoreLauncher px = pigccore->GetLauncher(pcounter->expendabletypeID);
			if (px)
				pxs.Format("(%d)",px->partID);
			s.Format("%s (%d)%s",pcounter->launcherDef.name,pcounter->expendabletypeID,pxs);
			pce->name.Format("Counter: %s",s);
			RefreshStores(pce);
			maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hCounters, tvisort);
		}

		for (int j=0;j<pigccore->cl_Probes.GetSize();j++)
		{
			PtrCoreProbe pprobe = pigccore->cl_Probes.GetAt(j);
			if (bFilter & IsFiltered((UCHAR*)&(pprobe->launcherDef.ttbmRequired))) //TODO
				continue;
			CString s;
			PtrCoreEntry pce = new CoreEntry;
			pce->tag = OT_probeType;
			pce->entry = (LPARAM)pprobe;
			CString pxs = "";
			PtrCoreLauncher px = pigccore->GetLauncher(pprobe->expendabletypeID);
			if (px)
				pxs.Format("(%d)",px->partID);
			s.Format("%s (%d)%s",pprobe->launcherDef.name,pprobe->expendabletypeID,pxs);
			pce->name.Format("Probe: %s",s);
			RefreshStores(pce);
			maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hProbes, tvisort);
		}
		for (int j=0;j<pigccore->cl_Mines.GetSize();j++)
		{
			PtrCoreMine pmine = pigccore->cl_Mines.GetAt(j);
			if (bFilter & IsFiltered((UCHAR*)&(pmine->launcherDef.ttbmRequired))) //TODO
				continue;
			CString s;
			PtrCoreEntry pce = new CoreEntry;
			pce->tag = OT_mineType;
			pce->entry = (LPARAM)pmine;
			CString pxs = "";
			PtrCoreLauncher px = pigccore->GetLauncher(pmine->expendabletypeID);
			if (px)
				pxs.Format("(%d)",px->partID);
			s.Format("%s (%d)%s",pmine->launcherDef.name,pmine->expendabletypeID,pxs);
			pce->name.Format("Mine: %s",s);
			RefreshStores(pce);
			maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hMines, tvisort);
		}
		for (int j=0;j<pigccore->cl_Missiles.GetSize();j++)
		{
			PtrCoreMissile pmissile = pigccore->cl_Missiles.GetAt(j);
			if (bFilter & IsFiltered((UCHAR*)&(pmissile->launcherDef.ttbmRequired))) //TODO
				continue;
			CString s;
			PtrCoreEntry pce = new CoreEntry;
			pce->tag = OT_missileType;
			pce->entry = (LPARAM)pmissile;
			CString pxs = "";
			PtrCoreLauncher px = pigccore->GetLauncher(pmissile->expendabletypeID);
			if (px)
				pxs.Format("(%d)",px->partID);
			s.Format("%s (%d)%s",pmissile->launcherDef.name,pmissile->expendabletypeID,pxs);
			pce->name.Format("Missile: %s",s);
			RefreshStores(pce);
			maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hMissiles, tvisort);
		}
	}

	for (int j=0;j<pigccore->cl_StationTypes.GetSize();j++)
	{
		PtrCoreStationType pstation = pigccore->cl_StationTypes.GetAt(j);
		if (bFilter & IsFiltered((UCHAR *)&(pstation->ttbmRequired)))
			continue;
		CString s;
		PtrCoreEntry pce = new CoreEntry;
		pce->tag = OT_stationType;
		pce->entry = (LPARAM)pstation;
		s.Format("%s (%d)",pstation->name,pstation->stationTypeID);
		pce->name.Format("Station: %s",s);
		RefreshStores(pce);
		maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hStationsRoot/*hStations[pstation->uid / 100]*/, tvisort);
	}
	for (int j=0;j<pigccore->cl_Projectiles.GetSize();j++)
	{
		PtrCoreProjectile pprojectile = pigccore->cl_Projectiles.GetAt(j);
		CString s;
		PtrCoreEntry pce = new CoreEntry;
		pce->tag = OT_projectileType;
		pce->entry = (LPARAM)pprojectile;
		s.Format("p #%d",pprojectile->projectileTypeID);
		pce->name.Format("Projectile: %s",s);
		RefreshStores(pce);
		maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hProjectiles, TVI_SORT);
	}

	for (int j=0;j<pigccore->cl_TreasureSets.GetSize();j++)
	{
		PtrCoreTreasureSet ptres = pigccore->cl_TreasureSets.GetAt(j);
		CString s;
		PtrCoreEntry pce = new CoreEntry;
		pce->tag = OT_treasureSet;
		pce->entry = (LPARAM)ptres;
		s.Format("%s (%d)",ptres->name,ptres->treasureSetID);
		pce->name.Format("Treasure set: %s",s);
		RefreshStores(pce);
		maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hTreasureSets, TVI_SORT);
	}

	dlgConstants.pcore = pigccore;
	dlgPart.pcore = pigccore;
	dlgShip.pcore = pigccore;
	dlgShipLoadout.pcore = pigccore;
	dlgCiv.pcore = pigccore;
	dlgDrone.pcore = pigccore;
	dlgProjectile.pcore = pigccore;
	dlgTreasure.pcore = pigccore;
	dlgMissile.pcore = pigccore;
	dlgMine.pcore = pigccore;
	dlgProbe.pcore = pigccore;
	dlgChaff.pcore = pigccore;
	dlgStation.pcore = pigccore;
}
void CICEDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout(sVersion);
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CICEDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CICEDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CICEDlg::OnSelchangeMainTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	pTechTree = NULL;
	pTechTreeLocal = NULL;
	curpce = NULL;
	LPNMTREEVIEW ptv = (LPNMTREEVIEW) pNMHDR;
	if (curdiag)
	{
		curdiag->ShowWindow(SW_HIDE);
		curdiag=NULL;
	}
	ShowMoveButtons(false);
	bool showmb = false;

	bool ShowLoadout = false;
	if (ptv->itemNew.lParam)
	{
		PtrCoreEntry pce = (PtrCoreEntry)ptv->itemNew.lParam;
		curpce = pce;
		switch(pce->tag)
		{
		case OT_civilization:{
			PtrCoreCiv pciv = (PtrCoreCiv) pce->entry;
			dlgCiv.pciv = pciv;
			dlgCiv.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgCiv;
			//AfxMessageBox(pciv->name);
			pTechTree = (UCHAR *)&(pciv->ttbmBaseTechs); //TODO
			sTechName.Format("Faction: %s (%d)",pciv->name,pciv->civilizationID);
			showmb=true;
			}break;
		case OT_development:{
			PtrCoreDevel pdevel = (PtrCoreDevel) pce->entry;
			dlgDevel.pdevel = pdevel;
			dlgDevel.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgDevel;
			pTechTree = (UCHAR *)&(pdevel->ttbmRequired); //TODO
			sTechName.Format("Devel: %s (%d)",pdevel->name,pdevel->developmentID);
			showmb=true;
			}break;
		case OT_hullType:{ // ship
			PtrCoreShip pship = (PtrCoreShip) pce->entry;
			dlgShip.pship = pship;
			dlgShip.UpdateData(FALSE);
			dlgShipLoadout.pship = pship;
			dlgShipLoadout.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgShip;
			pTechTree = (UCHAR *)&(pship->ttbmRequired); // TODO
			sTechName.Format("Ship: %s (%d)",pship->name,pship->hullID);
			showmb=true;
			ShowLoadout = true;
			}break;
		case OT_stationType:{ // station
			PtrCoreStationType pstation = (PtrCoreStationType) pce->entry;
			dlgStation.pstation = pstation;
			dlgStation.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgStation;
			pTechTree = (UCHAR *)&(pstation->ttbmRequired); //TODO
			pTechTreeLocal = (UCHAR *)&(pstation->ttbmLocal); //TODO
			sTechName.Format("Station: %s (%d)",pstation->name,pstation->stationTypeID);
			showmb=true;
			}break;
		case OT_droneType:{ // drone
			PtrCoreDrone pdrone = (PtrCoreDrone) pce->entry;
			dlgDrone.pdrone = pdrone;
			dlgDrone.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgDrone;
			pTechTree = (UCHAR *)&(pdrone->ttbmRequired); //TODO
			sTechName.Format("Drone: %s (%d)",pdrone->name,pdrone->droneTypeID);
			showmb=true;
			}break;
		case OT_missileType:{ // Missile
			PtrCoreMissile pmissile = (PtrCoreMissile) pce->entry;
			dlgMissile.pmissile = pmissile;
			dlgMissile.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgMissile;
			pTechTree = (UCHAR *)&(pmissile->launcherDef.ttbmRequired); //TODO
			sTechName.Format("Missile: %s (%d)",pmissile->launcherDef.name,pmissile->expendabletypeID);
			showmb=true;
			}break;
		case OT_partType:{ // part
			PtrCorePart ppart = (PtrCorePart) pce->entry;
			dlgPart.ppart = ppart;
			dlgPart.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgPart;
			pTechTree = (UCHAR *)&(ppart->ttbmRequired); //TODO
			sTechName.Format("Part: %s (%d)",ppart->name,ppart->partID);
			showmb=true;
			}break;
		case OT_mineType:{ // mine
			PtrCoreMine pmine = (PtrCoreMine) pce->entry;
			dlgMine.pmine = pmine;
			dlgMine.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgMine;
			pTechTree = (UCHAR *)&(pmine->launcherDef.ttbmRequired);//TODO
			sTechName.Format("Mine: %s (%d)",pmine->launcherDef.name,pmine->expendabletypeID);
			showmb=true;
			}break;
		case OT_chaffType:{
			PtrCoreCounter pcounter = (PtrCoreCounter) pce->entry;
			dlgChaff.pcounter = pcounter;
			dlgChaff.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgChaff;
			pTechTree = (UCHAR *)&(pcounter->launcherDef.ttbmRequired); //TODO
			sTechName.Format("Counter: %s (%d)",pcounter->launcherDef.name,pcounter->expendabletypeID);
			showmb=true;
			}break;
		case OT_probeType:{
			PtrCoreProbe pprobe = (PtrCoreProbe) pce->entry;
			dlgProbe.pprobe = pprobe;
			dlgProbe.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgProbe;
			pTechTree = (UCHAR *)&(pprobe->launcherDef.ttbmRequired); //TODO
			sTechName.Format("Probe: %s (%d)",pprobe->launcherDef.name,pprobe->expendabletypeID);
			showmb=true;
			}break;
		case OT_projectileType:{
			PtrCoreProjectile pprojectile = (PtrCoreProjectile) pce->entry;
			dlgProjectile.pprojectile = pprojectile;
			dlgProjectile.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgProjectile;
			}break;
		case OT_constants:{
			dlgConstants.pconst = (PtrCoreConstants) pce->entry;
			dlgConstants.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgConstants;
			}break;
		case OT_treasureSet:{ // treasuresets
			PtrCoreTreasureSet ptres = (PtrCoreTreasureSet) pce->entry;
			dlgTreasure.ptres = ptres;
			dlgTreasure.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgTreasure;
			sTechName.Format("TreasureSet: %s (%d)",ptres->name,ptres->treasureSetID);
			}break;
		default:
			break;
		}
	}
	CButton *cbck = (CButton *)CWnd::GetDlgItem(IDC_CKSORT);
	if (cbck->GetCheck()==BST_UNCHECKED)
		ShowMoveButtons(showmb);

	CTabCtrl *cbtab = (CTabCtrl *)CWnd::GetDlgItem(IDC_MAINTAB);
	//if (cbtab->GetCurSel()==0)
	//	if (curdiag)
	//		curdiag->ShowWindow(SW_SHOWNA);
	if (ShowLoadout)
	{
		if ( cbtab->GetItemCount() == 2)
			cbtab->InsertItem(2,"&Loadout");
	}
	else
	{
		if ( cbtab->GetItemCount() == 3)
		{
			cbtab->DeleteItem(2);
			cbtab->SetCurSel(0);
		}
	}
	SelchangeMaintab();
	UpdateData(FALSE);
	*pResult = 0;
}

void CICEDlg::OnClickedAbout(void)
{
	CAboutDlg dlgAbout(sVersion);
	dlgAbout.DoModal();
}

void CICEDlg::OnClickedLoad(void)
{
	if (DiscardChanges() == IDNO) return;
	CString startpath = cArtPath + "\\*.igc";
#ifdef _ICEPUB
	CFileDialog cfd(TRUE,"igc",NULL,OFN_FILEMUSTEXIST|OFN_NOCHANGEDIR|OFN_NONETWORKBUTTON,"Allegiance Core|*.igc|",this,OPENFILENAME_SIZE_VERSION_400);
#else
	CFileDialog cfd(TRUE,"igc",startpath,OFN_FILEMUSTEXIST|OFN_NOCHANGEDIR|OFN_NONETWORKBUTTON,"Allegiance Core|*.igc|",this);//,OPENFILENAME_SIZE_VERSION_400);
#endif
	if (cfd.DoModal() == IDOK)
	{
		CString fileTitle = cfd.GetFileTitle();
		if ((fileTitle == "training_1") ||
			(fileTitle == "training_3") ||
			(fileTitle == "training_5"))
		{
			CString mes;
			mes.Format("%s is not an Allegiance core",fileTitle);

			AfxMessageBox(_T(mes));
		}
		else
			LoadCore(cfd.GetPathName());
	}
}
void CICEDlg::LoadCore(CString filename)
{
	CIGCCore *cigccore = new CIGCCore;
	if (cigccore->ReadFromFile(filename))
	{
		CString fileTitle;
		char ft[250];
		GetFileTitle(filename,ft,250);
		fileTitle = ft;
		sCorepath.Format("%s",filename);
		sCorename.Format("%s",fileTitle);
		CWnd *pname = CWnd::GetDlgItem(IDC_FILENAME);
		pname->SetWindowText(sCorename);
		store = NULL;
		store1 = NULL;
		store2 = NULL;
		if (pigccore)
		{
			FreeTreePCE();
			delete pigccore;
		}
		pigccore = cigccore;
		CButton *pbut = (CButton *)CWnd::GetDlgItem(IDSAVEAS);
		pbut->EnableWindow(TRUE);
		if ((fileTitle == "static_core") ||	(fileTitle == "zone_core"))
		{
			AfxMessageBox("This core is part of the game. Use 'save as' to mod it"); 
			pbut = (CButton *)CWnd::GetDlgItem(IDSAVE);
			pbut->EnableWindow(FALSE);
		}
		else
		{
			pbut = (CButton *)CWnd::GetDlgItem(IDSAVE);
			pbut->EnableWindow(TRUE);
		}
		pTechTree = NULL;
		pTechTreeLocal = NULL;
		ClearFilter();
		BuildTree();
		changed = true; // TODO
	}
	else
	{
		delete cigccore;
		cigccore = NULL;
	}

}

void CICEDlg::OnClickedSave(void)
{
#ifdef _ICELITE
	AfxMessageBox("ICE Lite version - save not implemented");
#else
	if (curdiag)
		curdiag->UpdateData(TRUE); 
#ifdef _ICESEC
	pigccore->iCoreHeader = 0x3B02EF03; //EF = ice, 02 = version (maj)
#endif
	CButton *cab = (CButton *)GetDlgItem(IDC_AUTOBACKUP);
	CString bkname = "";
	if (cab->GetCheck() == BST_CHECKED)
	{
		bkname = DoBackup(sCorepath, sCorename);
		if (bkname != "")
		{
			bkname = " (backup = "+bkname+")";
		}
	}
	pigccore->SaveToFile(sCorepath); // should check
	AfxMessageBox("Core saved to " + sCorepath + bkname);
	changed = false;
	OnClickedRefresh();
#endif
}
CString CICEDlg::DoBackup(CString file, CString name)
{
	CString root = file.Left(file.GetLength()-4);
	CString ext = file.Right(3); // should always be 'igc' but let's make it more generic

	// find next unusued backup name
	CString bkfile;
	CFileStatus dummy;
    int backnum=1;
	for (backnum=1;backnum<1000;backnum++)
	{
		bkfile.Format("%s.%03d.%s",root,backnum,ext);
		
		if (!CFile::GetStatus(bkfile,dummy))
			break;
	}
	if (backnum == 1000)
	{
		AfxMessageBox("backup overflow (more than 999 versions) for " + bkfile);
		return "";
	}
	// special check for save as
	if (CFile::GetStatus(file,dummy))
		CFile::Rename(file,bkfile);
	else
		return "";
	CString dispname;
	dispname.Format("%s.%03d.%s",name,backnum,ext);
	return dispname;
}
void CICEDlg::OnClickedSaveas(void)
{
	CString startpath = cArtPath + "\\*.igc";
#ifdef _ICEPUB
	CFileDialog cfd(FALSE,"igc",NULL,OFN_NOCHANGEDIR|OFN_NONETWORKBUTTON|OFN_OVERWRITEPROMPT,"Allegiance Core|*.igc|",this,OPENFILENAME_SIZE_VERSION_400);
#else
	CFileDialog cfd(FALSE,"igc",startpath,OFN_NOCHANGEDIR|OFN_NONETWORKBUTTON|OFN_OVERWRITEPROMPT,"Allegiance Core|*.igc|",this,OPENFILENAME_SIZE_VERSION_400);
#endif
	if (cfd.DoModal() == IDOK)
	{
		CString fileTitle = cfd.GetFileTitle();
		if ((fileTitle == "static_core") ||
			(fileTitle == "zone_core") ||
			(fileTitle == "training_1") ||
			(fileTitle == "training_3") ||
			(fileTitle == "training_5"))
		{
			AfxMessageBox(_T("ERROR: CANT OVERWRITE AN ALLEGIANCE SYSTEM FILE ! Choose another name."));
			return;
		}
		sCorepath.Format("%s",cfd.GetPathName());
		sCorename.Format("%s",fileTitle);
		CWnd *pname = CWnd::GetDlgItem(IDC_FILENAME);
		pname->SetWindowText(sCorename);
		CButton *pbut = (CButton *)CWnd::GetDlgItem(IDSAVE);
		pbut->EnableWindow(TRUE);
		changed = true;
		OnClickedSave();
	}
}

void CICEDlg::OnClickedCancel(void)
{
	if (DiscardChanges() == IDNO)
		return;
	if (pigccore)
	{
		FreeTreePCE();
		delete pigccore;
	}
	EndDialog(IDCANCEL);
}

int CICEDlg::DiscardChanges(void)
{
	if (changed)
		return AfxMessageBox(_T("CORE not saved !!! Are you sure ? "),MB_YESNO|MB_DEFBUTTON2);
	return IDYES;
}


void CICEDlg::OnCancel(void)
{
	// trap 'escape'
	//CDialog::OnCancel();
}

void CICEDlg::OnOK(void)
{
	// trap 'return'
	//CDialog::OnOK();
}

void CICEDlg::OnClickedQuit(void)
{
	if (DiscardChanges() == IDNO)
		return;
	if (pigccore)
	{
		FreeTreePCE();
		delete pigccore;
	}
	EndDialog(IDCANCEL);
}

CString CICEDlg::TTHaveBit(int ipBit,CListBox *clb, CString prefix)
{
	int ibit = ipBit; 
	int idx = ibit/8;
	int imask = 1<<(ibit%8);
	CString s ="";
	CString t;
	if (ibit>400){
		ibit -=400;
		//if (ibit == 1) s = "GP: Allow Devel\r\n";
		//if (ibit == 2) s = "GP: Deatch Match\r\n";
		if (ibit == 3) s = "GP: Allow supremacy\r\n";
		if (ibit == 4) s = "GP: Allow tactical\r\n";
		if (ibit == 5) s = "GP: Allow expansion\r\n";
		if (ibit == 6) s = "GP: Allow shipyard\r\n";
		//if (ibit == 7) s = "GP: CTF or money\r\n"; 
		// 7 is actually used in MS core as a 'never defined' bit to allow hiding some techs.
		// and it's not related to a game parameter
		if (s != "") clb->AddString(prefix+s);
	}
	ibit = ipBit;

	if (ibit>=400)
	{
		int idxciv = idx-50;
		for (int j=0;j<pigccore->cl_Civs.GetSize();j++)
		{
			PtrCoreCiv pciv = pigccore->cl_Civs.GetAt(j);
			UCHAR *techtree = (UCHAR *)&(pciv->ttbmBaseTechs); //TODO
			if (techtree[idxciv] & imask)
			{
				t.Format("Faction: %s (%d) 'Devel'\r\n",pciv->name,pciv->civilizationID);
				s+=t;
				int idx = clb->AddString(prefix+t); clb->SetItemDataPtr(idx,pciv);
			}
			if (techtree[idx] & imask)
			{
				t.Format("Faction: %s (%d) 'No Devel'\r\n",pciv->name,pciv->civilizationID);
				s+=t;
				int idx = clb->AddString(prefix+t); clb->SetItemDataPtr(idx,pciv);
			}
		}
		for (int j=0;j<pigccore->cl_StationTypes.GetSize();j++)
		{
			PtrCoreStationType p = pigccore->cl_StationTypes.GetAt(j);
			UCHAR *techtreeloc = (UCHAR *)&(p->ttbmLocal); //TODO
			if (techtreeloc[idxciv] & imask)
			{
				t.Format("Station: %s (%d) - local\r\n",p->name,p->stationTypeID);
				s+=t;
				int idx = clb->AddString(prefix+t); clb->SetItemDataPtr(idx,p);
			}
		}


	}
	//idx = ibit/8+50;
	for (int j=0;j<pigccore->cl_Devels.GetSize();j++)
	{
		PtrCoreDevel p = pigccore->cl_Devels.GetAt(j);
		UCHAR *techtree = (UCHAR*)&(p->ttbmRequired); // TODO
		if (techtree[idx] & imask)
		{
			t.Format("Devel: %s (%d)\r\n",p->name,p->developmentID);
			s+=t;
			int idx = clb->AddString(prefix+t); clb->SetItemDataPtr(idx,p);
		}
	}

	for (int j=0;j<pigccore->cl_Ships.GetSize();j++)
	{
		PtrCoreShip pship = pigccore->cl_Ships.GetAt(j);
		UCHAR *techtree = (UCHAR*)&(pship->ttbmRequired); // TODO
		if (techtree[idx] & imask)
		{
			t.Format("Ship: %s (%d)\r\n",pship->name,pship->hullID);
			s+=t;
			int idx = clb->AddString(prefix+t); clb->SetItemDataPtr(idx,pship);
		}
	}

	for (int j=0;j<pigccore->cl_StationTypes.GetSize();j++)
	{
		PtrCoreStationType p = pigccore->cl_StationTypes.GetAt(j);
		UCHAR *techtree = (UCHAR*)&(p->ttbmRequired); // TODO
		if (techtree[idx] & imask)
		{
			t.Format("Station: %s (%d)\r\n",p->name,p->stationTypeID);
			s+=t;
			int idx = clb->AddString(prefix+t); clb->SetItemDataPtr(idx,p);
		}
	}

	for (int j=0;j<pigccore->cl_Drones.GetSize();j++)
	{
		PtrCoreDrone p = pigccore->cl_Drones.GetAt(j);
		UCHAR *techtree = (UCHAR*)&(p->ttbmRequired); // TODO
		if (techtree[idx] & imask)
		{
			t.Format("Drone: %s (%d)\r\n",p->name,p->droneTypeID);
			s+=t;
			int idx = clb->AddString(prefix+t); clb->SetItemDataPtr(idx,p);
		}
	}
	for (int j=0;j<pigccore->cl_Missiles.GetSize();j++)
	{
		PtrCoreMissile p = pigccore->cl_Missiles.GetAt(j);
		UCHAR *techtree = (UCHAR*)&(p->launcherDef.ttbmRequired); //TODO
		if (techtree[idx] & imask)
		{
			t.Format("Missile: %s (%d)\r\n",p->launcherDef.name,p->expendabletypeID);
			s+=t;
			int idx = clb->AddString(prefix+t); clb->SetItemDataPtr(idx,p);
		}
	}
	for (int j=0;j<pigccore->cl_Parts.GetSize();j++)
	{
		PtrCorePart p = pigccore->cl_Parts.GetAt(j);
		UCHAR *techtree = (UCHAR*)&(p->ttbmRequired); //TODO
		if (techtree[idx] & imask)
		{
			t.Format("Part: %s (%d)\r\n",p->name,p->partID);
			s+=t;
			int idx = clb->AddString(prefix+t); clb->SetItemDataPtr(idx,p);
		}
	}
	for (int j=0;j<pigccore->cl_Mines.GetSize();j++)
	{
		PtrCoreMine p = pigccore->cl_Mines.GetAt(j);
		UCHAR *techtree = (UCHAR*)&(p->launcherDef.ttbmRequired); //TODO
		if (techtree[idx] & imask)
		{
			t.Format("Mine: %s (%d)\r\n",p->launcherDef.name,p->expendabletypeID);
			s+=t;
			int idx = clb->AddString(prefix+t); clb->SetItemDataPtr(idx,p);
		}
	}
	for (int j=0;j<pigccore->cl_Counters.GetSize();j++)
	{
		PtrCoreCounter p = pigccore->cl_Counters.GetAt(j);
		UCHAR *techtree = (UCHAR*)&(p->launcherDef.ttbmRequired); //TODO
		if (techtree[idx] & imask)
		{
			t.Format("Counter: %s (%d)\r\n",p->launcherDef.name,p->expendabletypeID);
			s+=t;
			int idx = clb->AddString(prefix+t); clb->SetItemDataPtr(idx,p);
		}
	}
	for (int j=0;j<pigccore->cl_Probes.GetSize();j++)
	{
		PtrCoreProbe p = pigccore->cl_Probes.GetAt(j);
		UCHAR *techtree = (UCHAR*)&(p->launcherDef.ttbmRequired); //TODO
		if (techtree[idx] & imask)
		{
			t.Format("Probe: %s (%d)\r\n",p->launcherDef.name,p->expendabletypeID);
			s+=t;
			int idx = clb->AddString(prefix+t); clb->SetItemDataPtr(idx,p);
		}
	}

	if (s=="")
		s.Format("NONE FOUND\r\n",ibit);
	return s;
}

void CICEDlg::OnClickedRefresh(void)
{
	if (!pigccore) return;
	pTechTree = NULL;
	pTechTreeLocal = NULL;
	curpce = NULL;
	maintree = (CTreeCtrl *)CWnd::GetDlgItem(IDC_MAINTREE);
	HTREEITEM hItem = maintree->GetSelectedItem();
	LPARAM entry = NULL;
	if (hItem != NULL)
	{
		PtrCoreEntry pce = (PtrCoreEntry)maintree->GetItemData(hItem);
		if (pce) 
			entry = pce->entry;
		pce = NULL;
	}
	FreeTreePCE();
	BuildTree();
	SelectPCE(entry,NULL);
}

void CICEDlg::MoveEntry(int dir)
{
	CButton *cbck = (CButton *)CWnd::GetDlgItem(IDC_CKSORT);
	if (cbck->GetCheck()==BST_CHECKED)
		return;
	if ((dir != 1) && (dir !=-1))
		return;
	if (curpce == NULL)
		return;
	CArray<LPARAM,LPARAM> *cl_Gen = NULL;
	LPARAM curp = curpce->entry;
	switch (curpce->tag)
	{
		case OT_development:
			//cl_Gen = (CArray<LPARAM,LPARAM> *)&pigccore->cl_Devels;
			if (pigccore->MoveDevel((PtrCoreDevel)curpce->entry,dir))
				OnClickedRefresh();
			return;
			break;
		case OT_stationType:
			cl_Gen = (CArray<LPARAM,LPARAM> *)&pigccore->cl_StationTypes;
			break;
		case OT_droneType:
			cl_Gen = (CArray<LPARAM,LPARAM> *)&pigccore->cl_Drones;
			break;
		case OT_hullType:
			cl_Gen = (CArray<LPARAM,LPARAM> *)&pigccore->cl_Ships;
			break;
		case OT_partType:
			cl_Gen = (CArray<LPARAM,LPARAM> *)&pigccore->cl_Parts;
			break;
		case OT_civilization:
			cl_Gen = (CArray<LPARAM,LPARAM> *)&pigccore->cl_Civs;
			break;
		case OT_mineType:
			{
			cl_Gen = (CArray<LPARAM,LPARAM> *)&pigccore->cl_Parts;
			PtrCoreMine pmine = (PtrCoreMine) curp;
			curp = (LPARAM)pigccore->GetLauncher(pmine->expendabletypeID);
			}
			break;
		case OT_missileType:
			{
			cl_Gen = (CArray<LPARAM,LPARAM> *)&pigccore->cl_Parts;
			PtrCoreMissile pmissile = (PtrCoreMissile) curp;
			curp = (LPARAM)pigccore->GetLauncher(pmissile->expendabletypeID);
			}
			break;
		case OT_chaffType:
			{
			cl_Gen = (CArray<LPARAM,LPARAM> *)&pigccore->cl_Parts;
			PtrCoreCounter pcounter = (PtrCoreCounter) curp;
			curp = (LPARAM)pigccore->GetLauncher(pcounter->expendabletypeID);
			}
			break;
		case OT_probeType:
			{
			cl_Gen = (CArray<LPARAM,LPARAM> *)&pigccore->cl_Parts;
			PtrCoreProbe pprobe = (PtrCoreProbe) curp;
			curp = (LPARAM)pigccore->GetLauncher(pprobe->expendabletypeID);
			}
			break;
		default:
			return;
	}
	if (cl_Gen == NULL)
		return;
	if (curp == NULL)
		return;
	int curi = -1;
	for (int i=0;i<cl_Gen->GetCount();i++)
	{
		if (cl_Gen->GetAt(i) == curp)
			curi = i;
	}
	if (curi == -1)
		return;
	if ((curi == 0) && (dir == -1))
		return;
	if ((curi == (cl_Gen->GetCount()-1)) && (dir == 1))
		return;
	LPARAM op = cl_Gen->GetAt(curi+dir);
	cl_Gen->SetAt(curi+dir,curp);
	cl_Gen->SetAt(curi,op);
	OnClickedRefresh();
}

void CICEDlg::OnBnClickedAdd()
{
	if (!pigccore) return;
 //(NMHDR *pNMHDR, LRESULT *pResult)
	maintree = (CTreeCtrl *)CWnd::GetDlgItem(IDC_MAINTREE);
	HTREEITEM hItem = maintree->GetSelectedItem();
	if (hItem == NULL) return;
	PtrCoreEntry pce = (PtrCoreEntry)maintree->GetItemData(hItem);
	if (pce == NULL) return;
/*	CString mes;
	mes.Format("%d - %d",pce->tag,pce->entry);
	AfxMessageBox(mes);
	return;
*/

	LPARAM entry = NULL;
	switch(pce->tag)
	{
	case OT_probeType:{
		PtrCoreProbe pprobecur = (PtrCoreProbe) pce->entry;
		PtrCoreProbe pprobe = new IGCCoreProbe;
		memcpy(pprobe,pprobecur,sizeof(IGCCoreProbe));
		pigccore->AddProbe(pprobe);
		entry = (LPARAM)pprobe;
		}break;
	case OT_mineType:{
		PtrCoreMine pminecur = (PtrCoreMine) pce->entry;
		PtrCoreMine pmine = new IGCCoreMine;
		memcpy(pmine,pminecur,sizeof(IGCCoreMine));
		pigccore->AddMine(pmine);
		entry = (LPARAM)pmine;
		}break;
	case OT_missileType:{
		PtrCoreMissile pcur = (PtrCoreMissile) pce->entry;
		PtrCoreMissile p = new IGCCoreMissile;
		memcpy(p,pcur,sizeof(IGCCoreMissile));
		pigccore->AddMissile(p);
		entry = (LPARAM)p;
		PtrCoreLauncher plcur = pigccore->GetLauncher(pcur->expendabletypeID);
		PtrCoreLauncher pl = new IGCCoreLauncher;
		memcpy(pl,plcur,sizeof(IGCCoreLauncher));
		pl->expendabletypeID = p->expendabletypeID;
		pl->successorPartID = -1;
		pigccore->AddLauncher(pl);
		}break;
	case OT_chaffType:{
		PtrCoreCounter pcur = (PtrCoreCounter) pce->entry;
		PtrCoreCounter p = new IGCCoreCounter;
		memcpy(p,pcur,sizeof(IGCCoreCounter));
		pigccore->AddCounter(p);
		entry = (LPARAM)p;
		PtrCoreLauncher plcur = pigccore->GetLauncher(pcur->expendabletypeID);
		PtrCoreLauncher pl = new IGCCoreLauncher;
		memcpy(pl,plcur,sizeof(IGCCoreLauncher));
		pl->expendabletypeID = p->expendabletypeID;
		pl->successorPartID = -1;
		pigccore->AddLauncher(pl);
		}break;
	case OT_civilization:{
		PtrCoreCiv pcivcur = (PtrCoreCiv) pce->entry;
		PtrCoreCiv pciv = new IGCCoreCiv;
		memcpy(pciv,pcivcur,sizeof(IGCCoreCiv));
		pigccore->AddCiv(pciv);
		entry = (LPARAM)pciv;
		}break;
	case OT_development:{
		PtrCoreDevel pdevelcur = (PtrCoreDevel) pce->entry;
		PtrCoreDevel pdevel = new IGCCoreDevel;
		memcpy(pdevel,pdevelcur,sizeof(IGCCoreDevel));
		pigccore->AddDevel(pdevel);
		entry = (LPARAM)pdevel;
		}break;
	case OT_hullType:{ // ship
		PtrCoreShip pshipcur = (PtrCoreShip) pce->entry;
		PtrCoreShip pship = new IGCCoreShip;
		memcpy(pship,pshipcur,sizeof(IGCCoreShip));
		pigccore->AddShip(pship);
		entry = (LPARAM)pship;
		}break;
	case OT_stationType:{ // station
		PtrCoreStationType pstationcur = (PtrCoreStationType) pce->entry;
		PtrCoreStationType pstation = new IGCCoreStationType;
		memcpy(pstation,pstationcur,sizeof(IGCCoreStationType));
		pigccore->AddStationType(pstation);
		entry = (LPARAM)pstation;
		}break;
	case OT_droneType:{ // drone
		PtrCoreDrone pdronecur = (PtrCoreDrone) pce->entry;
		PtrCoreDrone pdrone = new IGCCoreDrone;
		memcpy(pdrone,pdronecur,sizeof(IGCCoreDrone));
		pigccore->AddDrone(pdrone);
		entry = (LPARAM)pdrone;
		}break;
	case OT_projectileType:{
		PtrCoreProjectile pprojcur = (PtrCoreProjectile) pce->entry;
		PtrCoreProjectile pproj = new IGCCoreProjectile;
		memcpy(pproj,pprojcur,sizeof(IGCCoreProjectile));
		pigccore->AddProjectile(pproj);
		entry = (LPARAM)pproj;
		}break;
	case OT_partType:{ // part
		PtrCorePart ppartcur = (PtrCorePart) pce->entry;
		PtrCorePart ppart = new IGCCorePart;
		memcpy(ppart,ppartcur,sizeof(IGCCorePart));
		pigccore->AddPart(ppart);
		entry = (LPARAM)ppart;
		}break;
	case OT_constants:{
		//dlgConstants.pconst = (PtrCoreConstants) pce->entry;
		}break;
	default:
		break;
	}
	if (entry != NULL)
	{
		FreeTreePCE();
		BuildTree();
		SelectPCE(entry,NULL);
	}
}

void CICEDlg::OnBnClickedDelete()
{
	if (!pigccore) return;
	maintree = (CTreeCtrl *)CWnd::GetDlgItem(IDC_MAINTREE);
	HTREEITEM hItem = maintree->GetSelectedItem();
	if (hItem == NULL) return;
	PtrCoreEntry pce = (PtrCoreEntry)maintree->GetItemData(hItem);
	if (pce == NULL) return;
	LPARAM entry = NULL;
	switch(pce->tag)
	{
	case OT_partType:{ // part
		entry = pigccore->DeletePart((PtrCorePart) pce->entry);
		}break;
	case OT_probeType:{
		entry = pigccore->DeleteProbe((PtrCoreProbe) pce->entry);
		}break;
	case OT_mineType:{
		entry = pigccore->DeleteMine((PtrCoreMine) pce->entry);
		}break;
	case OT_chaffType:{
		entry = pigccore->DeleteCounter((PtrCoreCounter) pce->entry);
		}break;
	case OT_missileType:{
		entry = pigccore->DeleteMissile((PtrCoreMissile) pce->entry);
		}break;
	case OT_civilization:{
		entry = pigccore->DeleteCiv((PtrCoreCiv) pce->entry);
		}break;
	case OT_development:{
		entry = pigccore->DeleteDevel((PtrCoreDevel) pce->entry);
		}break;
	case OT_hullType:{ // ship
		entry = pigccore->DeleteShip((PtrCoreShip) pce->entry);
		}break;
	case OT_stationType:{ // station
		entry = pigccore->DeleteStationType((PtrCoreStationType) pce->entry);
		}break;
	case OT_droneType:{ // drone
		entry = pigccore->DeleteDrone((PtrCoreDrone) pce->entry);
		}break;
	case OT_projectileType:{
		entry = pigccore->DeleteProjectile((PtrCoreProjectile) pce->entry);
		}break;
	default:
		break;
	}
	if (entry != NULL)
	{
		maintree->SetItemData(hItem,NULL);
		delete pce;
		FreeTreePCE();
		BuildTree();
		SelectPCE(entry,NULL);
	}
}

// warning recursive function
void CICEDlg::SelectPCE(LPARAM entry)
{
	SelectPCE(entry,NULL);
}
void CICEDlg::SelectPCE(LPARAM entry,HTREEITEM hmyItem)
{
	if(!entry) return;

	maintree = (CTreeCtrl *)CWnd::GetDlgItem(IDC_MAINTREE);
	HTREEITEM hChildItem;
	if (hmyItem == NULL) 
		hChildItem = maintree->GetRootItem();
	else
		hChildItem = maintree->GetChildItem(hmyItem);
	while (hChildItem != NULL)
	{
		PtrCoreEntry pce;
		if (maintree->ItemHasChildren(hChildItem))
				SelectPCE(entry,hChildItem);
		if ((pce = (PtrCoreEntry)maintree->GetItemData(hChildItem)))
			if (pce->entry == entry)
			{
				if (curpce) store = curpce->entry;
				maintree->SelectItem(hChildItem);
				maintree->Select(hChildItem,TVGN_CARET | TVGN_FIRSTVISIBLE);
				maintree->SetFocus();
				curpce = pce;
				break;
			}
		hChildItem = maintree->GetNextItem(hChildItem, TVGN_NEXT);
	}
}

void CICEDlg::OnBnClickedTechtreeup()
{
	int iBit = (int)GetDlgItemInt(IDC_TECHTREEIDX);
	if (iBit <399) iBit++;
	SetDlgItemInt(IDC_TECHTREEIDX,iBit);
	ShowTechBit(NULL,NULL,iBit);
}

void CICEDlg::OnBnClickedTechtreedown()
{
	int iBit = (int)GetDlgItemInt(IDC_TECHTREEIDX);
	if (iBit >0) iBit--;
	SetDlgItemInt(IDC_TECHTREEIDX,iBit);
	ShowTechBit(NULL,NULL,iBit);
}

void CICEDlg::OnBnClickedTogglepre()
{
	if (!pTechTree) return;
	int idx = (int)GetDlgItemInt(IDC_TECHTREEIDX);
	if (pTechTree[idx/8] & (1<<(idx%8)))
		pTechTree[idx/8] =  pTechTree[idx/8] & (~(1<<(idx%8)));
	else
		pTechTree[idx/8] =  pTechTree[idx/8] | (1<<(idx%8));
	ShowTechEntry(pTechTree,pTechTreeLocal);
	ShowTechBit(pTechTree,pTechTreeLocal,-1);
}


void CICEDlg::OnBnClickedToggledef()
{
	if (!pTechTree) return;
	int idx = (int)GetDlgItemInt(IDC_TECHTREEIDX);
	idx+=400;
	if (pTechTree[idx/8] & (1<<(idx%8)))
		pTechTree[idx/8] =  pTechTree[idx/8] & (~(1<<(idx%8)));		
	else
		pTechTree[idx/8] =  pTechTree[idx/8] | (1<<(idx%8));
	ShowTechEntry(pTechTree,pTechTreeLocal);
	ShowTechBit(pTechTree,pTechTreeLocal,-1);
}

void CICEDlg::OnBnClickedTogglelocal()
{
	if (!pTechTreeLocal) return;
	int idx = (int)GetDlgItemInt(IDC_TECHTREEIDX);
	if (pTechTreeLocal[idx/8] & (1<<(idx%8)))
		pTechTreeLocal[idx/8] =  pTechTreeLocal[idx/8] & (~(1<<(idx%8)));		
	else
		pTechTreeLocal[idx/8] =  pTechTreeLocal[idx/8] | (1<<(idx%8));
	ShowTechEntry(pTechTree,pTechTreeLocal);
	ShowTechBit(pTechTree,pTechTreeLocal,-1);
}


void CICEDlg::OnEnChangeTechtreeidx()
{
	int iBit = (int)GetDlgItemInt(IDC_TECHTREEIDX);
	if ((iBit <0) || (iBit >=400))
	{
		SetDlgItemText(IDC_TECHTREEIDX,"0");
	}
	else
	{
		ShowTechBit(NULL,NULL,iBit);
	}
}
void CICEDlg::OnEnSetfocusTechtreeidx()
{
	OnEnChangeTechtreeidx();
}

void CICEDlg::OnEnSetfocusTechtree()
{
	ShowTechBit(pTechTree,pTechTreeLocal,-1);
}

void CICEDlg::OnBnClickedClearpre()
{
	if (pTechTree != NULL)
	{
		for (int i=0;i<50;i++)
			pTechTree[i] = 0;
		ShowTechEntry(pTechTree,pTechTreeLocal);
		ShowTechBit(pTechTree,pTechTreeLocal,-1);
	}
}

void CICEDlg::OnBnClickedCleardef()
{
	if (pTechTree != NULL)
	{
		for (int i=50;i<100;i++)
			pTechTree[i] = 0;
		ShowTechEntry(pTechTree,pTechTreeLocal);
		ShowTechBit(pTechTree,pTechTreeLocal,-1);
	}
}

void CICEDlg::OnBnClickedClearlocal()
{
	if (pTechTreeLocal != NULL)
	{
		for (int i=0;i<50;i++)
			pTechTreeLocal[i] = 0;
		ShowTechEntry(pTechTree,pTechTreeLocal);
		ShowTechBit(pTechTree,pTechTreeLocal,-1);
	}
}

//void CICEDlg::OnSelchangeTechlist(void)
//{
//	CComboBox *ccb = (CComboBox *)GetDlgItem(IDC_TECHLIST);
//	CButton *cb = (CButton *)GetDlgItem(IDC_TECHVAL);
//	int idx = ccb->GetCurSel();
//	if (idx != CB_ERR)
//	{
//		cb->ShowWindow(SW_SHOWNA);
//		cb->SetCheck(pTechTree[idx/8] & (1<<(idx%8))?BST_CHECKED:BST_UNCHECKED);
//	}
//	else
//		cb->ShowWindow(SW_HIDE);
//}
//void CICEDlg::OnClickTechVal(void)
//{
//	CComboBox *ccb = (CComboBox *)GetDlgItem(IDC_TECHLIST);
//	CButton *cb = (CButton *)GetDlgItem(IDC_TECHVAL);
//	int idx = ccb->GetCurSel();
//	if (idx != CB_ERR)
//	{
//		if (cb->GetCheck() == BST_CHECKED)
//			pTechTree[idx/8] =  pTechTree[idx/8] | (1<<(idx%8));
//		else
//			pTechTree[idx/8] =  pTechTree[idx/8] & (~(1<<(idx%8)));
//		UpdateData(FALSE);
//	}
//}
void CICEDlg::ShowTechBit(UCHAR *pTT,UCHAR *pTTLocal, int iBit)
{
	CString tt = "";
	CString t="";
	CString t2 = "";
	if (!pigccore) return;
	CListBox* clb = (CListBox*)GetDlgItem(IDC_TTLIST);
	clb->ResetContent();
	if (pTT)
	{
		tt = "Depends on:\r\n"; clb->AddString(tt);
		for (int i=0;i<50;i++)
		{
			for (int j=0;j<8;j++)
			{
				if (pTT[i] & (1<<j))
				{
					t.Format("%d:\r\n",i*8+j); tt+=t; int idx = clb->AddString(t); clb->SetItemData(idx,i*8+j);
					CString hb = TTHaveBit(400+i*8+j,clb,"  ");
					hb.Replace("\r\n","\r\n  ");
					tt.AppendFormat("  %s\r\n", hb);
				}
			}
		}
		t2.Format("%s\r\n",tt);
	}
	if ((pTT == NULL) & (iBit!=-1))
	{
		t.Format("%d defined by:\r\n",iBit); tt+=t; int idx = clb->AddString(t); clb->SetItemData(idx,iBit);
		CString hb = TTHaveBit(400+iBit,clb,"  ");
		hb.Replace("\r\n","\r\n  ");
		tt.AppendFormat("  %s\r\n", hb);
		t.Format("%d pre-required in:\r\n",iBit); tt+=t; idx = clb->AddString(t);  clb->SetItemData(idx,iBit);
		hb = TTHaveBit(iBit,clb,"  ");
		hb.Replace("\r\n","\r\n  ");
		tt.AppendFormat("  %s\r\n", hb);
		t2.Format("%s\r\n",tt);
	}
	SetDlgItemText(IDC_TECHTREE2, t2);
}

void CICEDlg::ShowTechEntry(UCHAR *pTT,UCHAR *pTTLocal)
{
	CString tb = "";
	CString t1 = "";
	if (!pigccore) return;
	if (pTT)
	{
		if (sTechName.Left(7) == "Faction")
			tb.Format("%s:\r\n'Devel' Def = ",sTechName);
		else
			tb.Format("%s:\r\nPre = ",sTechName);
		for (int i=0;i<50;i++)
		{
			for (int j=0;j<8;j++)
			{
				if (pTT[i] & (1<<j))
				{
					tb.AppendFormat("%d ",i*8+j);
				}
			}
		}
		if (sTechName.Left(7) == "Faction")
			tb.AppendFormat("\r\n'No Devel' Def = ");
		else
			tb.AppendFormat("\r\nDef = ");
		for (int i=50;i<100;i++)
		{
			for (int j=0;j<8;j++)
			{
				if (pTT[i] & (1<<j))
					tb.AppendFormat("%d ",(i-50)*8+j);
			}
		}
		t1.Format("%s\r\n",tb);

	}
	if (pTTLocal)
	{
		t1.AppendFormat("Local = ",sTechName);
		for (int i=0;i<50;i++)
		{
			for (int j=0;j<8;j++)
			{
				if (pTTLocal[i] & (1<<j))
				{
					t1.AppendFormat("%d ",i*8+j);
				}
			}
		}
		t1.AppendFormat("\r\n");
	}
	SetDlgItemText(IDC_TECHTREE, t1);
}

void CICEDlg::OnBnClickedStore1store()
{
	if (!curpce) return;
	SetDlgItemText(IDC_STORE1,curpce->name);
	store1 = curpce->entry;
}

void CICEDlg::OnBnClickedStore2store()
{
	if (!curpce) return;
	SetDlgItemText(IDC_STORE2,curpce->name);
	store2 = curpce->entry;
}

void CICEDlg::OnBnClickedStore1recall()
{
	if (!pigccore) return;
	if (!store1) return;
	SelectPCE(store1,NULL);
}

void CICEDlg::OnBnClickedStore2recall()
{
	if (!pigccore) return;
	if (!store2) return;
	SelectPCE(store2,NULL);
}

void CICEDlg::OnBnClickedCksort()
{
    OnClickedRefresh();
}

void CICEDlg::OnBnClickedMoveup()
{
	MoveEntry(-1);
}

void CICEDlg::OnBnClickedMovedown()
{
	MoveEntry(1);
}
void CICEDlg::ShowMoveButtons(bool b)
{
	CButton *cbmu = (CButton *)CWnd::GetDlgItem(IDC_MOVEUP);
	CButton *cbmd = (CButton *)CWnd::GetDlgItem(IDC_MOVEDOWN);
	int ishow = b?SW_SHOWNA:SW_HIDE;
	cbmu->ShowWindow(ishow);
	cbmd->ShowWindow(ishow);
}

void CICEDlg::ShowTechTree(int swf)
{
	GetDlgItem(IDC_TECHTREE)->ShowWindow(swf);
	GetDlgItem(IDC_TECHTREEIDX)->ShowWindow(swf);
	GetDlgItem(IDC_TECHTREEUP)->ShowWindow(swf);
	GetDlgItem(IDC_TECHTREEDOWN)->ShowWindow(swf);
	GetDlgItem(IDC_TOGGLEPRE)->ShowWindow(swf);
	GetDlgItem(IDC_TOGGLEDEF)->ShowWindow(swf);
	GetDlgItem(IDC_TOGGLELOCAL)->ShowWindow(swf);
	GetDlgItem(IDC_CLEARPRE)->ShowWindow(swf);
	GetDlgItem(IDC_CLEARDEF)->ShowWindow(swf);
	GetDlgItem(IDC_CLEARLOCAL)->ShowWindow(swf);
	GetDlgItem(IDC_TECHTREE2)->ShowWindow(SW_HIDE); // never show this, keep it to debug TTLIST
	GetDlgItem(IDC_TTLIST)->ShowWindow(swf);


	GetDlgItem(IDC_BUTFILTER)->ShowWindow(swf);
	GetDlgItem(IDC_CLEARFILTER)->ShowWindow(swf);
	GetDlgItem(IDC_FILTER)->ShowWindow(swf);

	GetDlgItem(IDC_FILTERLABEL)->ShowWindow(swf);
	UpdateFilter(false);
}
// main tab (properties / tech tree) change
void CICEDlg::SelchangeMaintab()
{
	CTabCtrl *cbtab = (CTabCtrl *)CWnd::GetDlgItem(IDC_MAINTAB);

	if (cbtab->GetCurSel()==0)
	{
		// properties tag
		if (curdiag)
			curdiag->ShowWindow(SW_SHOWNA);
		ShowTechTree(SW_HIDE);
		dlgShipLoadout.ShowWindow(SW_HIDE);
	}
	else if (cbtab->GetCurSel()==1)
	{
		// techtree tags
		if (curdiag)
			curdiag->ShowWindow(SW_HIDE);
		ShowTechTree(SW_SHOWNA);
		dlgShipLoadout.ShowWindow(SW_HIDE);
	}
	else if (cbtab->GetCurSel()==2)
	{
		if (curdiag)
			curdiag->ShowWindow(SW_HIDE);
		ShowTechTree(SW_HIDE);
		dlgShipLoadout.ShowWindow(SW_SHOWNA);
	}
	else
	{
		if (curdiag)
			curdiag->ShowWindow(SW_HIDE);
		ShowTechTree(SW_HIDE);
		dlgShipLoadout.ShowWindow(SW_HIDE);
	}
}
void CICEDlg::OnTcnSelchangeMaintab(NMHDR *pNMHDR, LRESULT *pResult)
{
	SelchangeMaintab();
	*pResult = 0;
}
void CICEDlg::ClearFilter(void)
{
	for (int i=0;i<50;i++)
		tFilter[i] = 0;
}
void CICEDlg::UpdateFilter(bool rebuild)
{
	CString sfilt = "";
	for (int i=0;i<50;i++)
	{
		for (int j=0;j<8;j++)
		{
			if (tFilter[i] & (1<<j))
			{
				sfilt.AppendFormat("%d ",i*8+j);
			}
		}
	}
	if (sfilt == "")
		sfilt = "no filter";
	SetDlgItemText(IDC_FILTER,sfilt);
	if (rebuild)
	{
		FreeTreePCE();
		BuildTree();
	}
}
void CICEDlg::OnBnClickedButfilter()
{
	if (!pigccore) return;
	int idx = (int)GetDlgItemInt(IDC_TECHTREEIDX);

	if (tFilter[idx/8] & (1<<(idx%8)))
		tFilter[idx/8] =  tFilter[idx/8] & (~(1<<(idx%8)));
	else
		tFilter[idx/8] =  tFilter[idx/8] | (1<<(idx%8));
	UpdateFilter(true);
}

void CICEDlg::OnBnClickedClearfilter()
{
	ClearFilter();
	UpdateFilter(true);
}

bool CICEDlg::IsFiltered(UCHAR *pTT)
{
	for (int i=0;i<50;i++)
		for (int j=0;j<8;j++)
		{
			if(tFilter[i] & (1<<j))
				if (!(pTT[i] & (1<<j)))
					return true;
		}
	return false;
}
//http://www.codeguru.com/treeview/

//void CICEDlg::OnTvnBegindragMaintree(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
//	*pResult = 0;
//
//	m_hitemDrag = pNMTreeView->itemNew.hItem;
//	m_hitemDrop = NULL;
//
//	m_pDragImage = maintree->CreateDragImage(m_hitemDrag);  // get the image list for dragging
//	// CreateDragImage() returns NULL if no image list
//	// associated with the tree view control
//	if( !m_pDragImage )
//		return;
//
//	m_bLDragging = TRUE;
//	m_pDragImage->BeginDrag(0, CPoint(-15,-15));
//	POINT pt = pNMTreeView->ptDrag;
//	maintree->ClientToScreen( &pt );
//	m_pDragImage->DragEnter(NULL, pt);
//	SetCapture();
//}


void CICEDlg::OnBnClickedValidate()
{
	if (!pigccore) return;
	char *szReason;

	LPARAM pce = pigccore->FindError(&szReason);

	if (pce)
	{
		SelectPCE(pce);
		AfxMessageBox(szReason);
	}
	else
		AfxMessageBox("no errors found");
}

HICON CICEDlg::GetJumpIcon()
{
	return iJumpIcon;
}
void CICEDlg::OnBnClickedBback()
{
	SelectPCE(store);
}

void CICEDlg::OnBnClickedCompare()
{
	// TODO: compare feature
}

void CICEDlg::OnBnClickedDump()
{
	if (!pigccore) return;
	CFileDialog cfd(FALSE,"txt","*.txt",OFN_NOCHANGEDIR|OFN_NONETWORKBUTTON|OFN_OVERWRITEPROMPT,"Text file|*.txt|XML file|*.xml",this,OPENFILENAME_SIZE_VERSION_400);
	if (cfd.DoModal() == IDOK)
	{
		CString filename = cfd.GetPathName();
		if (cfd.GetFileExt()=="txt")
			pigccore->SaveAsText(filename);
		if (cfd.GetFileExt()=="xml")
			pigccore->SaveAsXML(filename);
	}
}

void CICEDlg::OnBnClickedChkart()
{
	// TODO: check artwork feature
}

void CICEDlg::OnLbnSelchangeTtlist()
{
	if (!pigccore) return;
	CListBox *clb = (CListBox *)GetDlgItem(IDC_TTLIST);
	int idx = clb->GetCurSel();
	CString t=""; 
	clb->GetText(idx,t);
	if (!t.GetLength()) return;
	if (isdigit(t.GetAt(0)))
	{
		SetDlgItemInt(IDC_TECHTREEIDX,clb->GetItemData(idx));
		OnEnChangeTechtreeidx();
	}
	if (t.Left(2) == "  ")
	{
		LPARAM p = (LPARAM)clb->GetItemDataPtr(idx);
		if (p!=-1) SelectPCE(p);
	}
}


CDescrDlg::CDescrDlg(char *p) : CDialog(CDescrDlg::IDD)
{
	m_descr = p;
}

void CDescrDlg::DoDataExchange(CDataExchange* pDX)
{
	CString descr;
	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		descr = m_descr;
	}
	DDX_Text(pDX, IDC_DESCR, descr);
	DDV_MaxChars(pDX, descr, 200);
	if (pDX->m_bSaveAndValidate) // dialog to data
	{
		strcpy_s(m_descr,200,descr);
	}
	CDialog::DoDataExchange(pDX);
}
BOOL CDescrDlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	((CEdit *)GetDlgItem(IDC_DESCR))->SetLimitText(199);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CDescrDlg, CDialog)
END_MESSAGE_MAP()
