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
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CICEDlg dialog



CICEDlg::CICEDlg(CWnd* pParent /*=NULL*/)
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
	ON_NOTIFY(TCN_SELCHANGE, IDC_MAINTAB, OnTcnSelchangeMaintab)
//	ON_WM_KEYDOWN()
ON_BN_CLICKED(IDC_BUTFILTER, OnBnClickedButfilter)
ON_BN_CLICKED(IDC_CLEARFILTER, OnBnClickedClearfilter)
ON_BN_CLICKED(IDC_ADDTOFILTER, OnBnClickedAddtofilter)
ON_BN_CLICKED(IDC_REMFROMFILTER, OnBnClickedRemfromfilter)
//ON_NOTIFY(TVN_BEGINDRAG, IDC_MAINTREE, OnTvnBegindragMaintree)
//ON_BN_CLICKED(IDC_GENHTML, OnBnClickedGenhtml)
ON_BN_CLICKED(IDC_VALIDATE, &CICEDlg::OnBnClickedValidate)
ON_BN_CLICKED(IDC_BBACK, &CICEDlg::OnBnClickedBback)
ON_BN_CLICKED(IDC_COMPARE, &CICEDlg::OnBnClickedCompare)
ON_BN_CLICKED(IDC_DUMP, &CICEDlg::OnBnClickedDump)
ON_BN_CLICKED(IDC_CHKART, &CICEDlg::OnBnClickedChkart)
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
	dlgChaff.MainUI = this; dlgChaff.SetIcons(iJumpIcon);
	dlgProjectile.sArtPath = cArtPath; dlgProjectile.MainUI = this;
	dlgShip.sArtPath = cArtPath; dlgShip.MainUI = this; dlgShip.SetIcons(iJumpIcon);
	dlgShipLoadout.sArtPath = cArtPath; dlgShipLoadout.MainUI = this;
	dlgStation.sArtPath = cArtPath; dlgStation.MainUI = this; dlgStation.SetIcons(iJumpIcon);
	dlgProbe.sArtPath = cArtPath; dlgProbe.MainUI = this; dlgProbe.SetIcons(iJumpIcon);
	dlgMine.MainUI = this; dlgMine.SetIcons(iJumpIcon);
	dlgMissile.sArtPath = cArtPath; dlgMissile.MainUI = this; dlgMissile.SetIcons(iJumpIcon);
	dlgCiv.sArtPath = cArtPath; dlgCiv.MainUI = this; dlgCiv.SetIcons(iJumpIcon);
	dlgPart.MainUI = this; dlgPart.SetIcons(iJumpIcon);
	if (sCoreArg != "")
	{
		//AfxMessageBox(sCoreArg);
		LoadCore(sCoreArg);

	}

	CButton *cab = (CButton *)GetDlgItem(IDC_AUTOBACKUP);
	cab->SetCheck(BST_CHECKED);
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
		pce->tag = AGC_Constants;
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
		pce->tag = AGC_Civilization;
		pce->entry = (LPARAM)pciv;
		pce->name.Format("Faction: %s (%d)",pciv->name,pciv->uid);
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
		if (bFilter & IsFiltered(pdevel->techtree))
			continue;
		CString s;
		PtrCoreEntry pce = new CoreEntry;
		pce->tag = AGC_Development;
		pce->entry = (LPARAM)pdevel;
		s.Format("%s (%d)",pdevel->name,pdevel->uid);
		pce->name.Format("Devel: %s",s);
		RefreshStores(pce);
		maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hTechPaths[pdevel->root_tree], tvisort);
	}
	for (int j=0;j<pigccore->cl_Drones.GetSize();j++)
	{
		PtrCoreDrone pdrone = pigccore->cl_Drones.GetAt(j);
		if (bFilter & IsFiltered(pdrone->techtree))
			continue;
		CString s;
		PtrCoreEntry pce = new CoreEntry;
		pce->tag = AGC_DroneType;
		pce->entry = (LPARAM)pdrone;
		s.Format("%s (%d)",pdrone->name,pdrone->uid);
		pce->name.Format("Drone: %s",s);
		RefreshStores(pce);
		maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hDrones, tvisort);
	}

	for (int j=0;j<pigccore->cl_Ships.GetSize();j++)
	{
		PtrCoreShip pship = pigccore->cl_Ships.GetAt(j);
		if (bFilter & IsFiltered(pship->techtree))
			continue;
		CString s;
		PtrCoreEntry pce = new CoreEntry;
		pce->tag = AGC_BucketStart;
		pce->entry = (LPARAM)pship;
		s.Format("%s (%d)",pship->name,pship->uid);
		pce->name.Format("Ship: %s",s);
		RefreshStores(pce);
		maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hShips, tvisort);
	}

	for (int j=0;j<pigccore->cl_Parts.GetSize();j++)
	{
		PtrCorePart ppart = pigccore->cl_Parts.GetAt(j);
		if (bFilter & IsFiltered(ppart->techtree))
			continue;
		if (!ppart->isspec)
		{
			CString s;
			PtrCoreEntry pce = new CoreEntry;
			pce->tag = AGC_PartType;
			pce->entry = (LPARAM)ppart;
			s.Format("%s (%d)",ppart->name,ppart->uid);
			pce->name.Format("Part: %s",s);
			RefreshStores(pce);
			maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hParts, tvisort);
		}
		if (ppart->isspec && tvisort==NULL)
		{
			PtrCoreEntry prox = pigccore->ProxyPart(ppart->usemask);
			if (prox)
			{
				CString s;
				PtrCoreEntry pce = new CoreEntry;
				switch (prox->tag)
				{
					case AGC_ChaffTypeOK:
					{
						PtrCoreCounter pcounter = (PtrCoreCounter)prox->entry;
						pce->tag = (AGCObjectType)prox->tag;
						pce->entry = (LPARAM)pcounter;
						s.Format("%s (%d)(%d)",pcounter->name,pcounter->uid,ppart->uid);
						pce->name.Format("Counter: %s",s);
						RefreshStores(pce);
						maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hParts, tvisort);
					}
					break;
					case AGC_ProbeType:
					{
						PtrCoreProbe pprobe = (PtrCoreProbe)prox->entry;
						pce->tag = (AGCObjectType)prox->tag;
						pce->entry = (LPARAM)pprobe;
						s.Format("%s (%d)(%d)",pprobe->name,pprobe->uid,ppart->uid);
						pce->name.Format("Probe: %s",s);
						RefreshStores(pce);
						maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hParts, tvisort);
					}
					break;
					case AGC_MineType:
					{
						PtrCoreMine pmine = (PtrCoreMine)prox->entry;
						pce->tag = (AGCObjectType)prox->tag;
						pce->entry = (LPARAM)pmine;
						s.Format("%s (%d)(%d)",pmine->name,pmine->uid,ppart->uid);
						pce->name.Format("Mine: %s",s);
						RefreshStores(pce);
						maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hParts, tvisort);
					}
					break;
					case AGC_MissileType:
					{
						PtrCoreMissile pmissile = (PtrCoreMissile)prox->entry;
						pce->tag = (AGCObjectType)prox->tag;
						pce->entry = (LPARAM)pmissile;
						s.Format("%s (%d)(%d)",pmissile->name,pmissile->uid,ppart->uid);
						pce->name.Format("Missile: %s",s);
						RefreshStores(pce);
						maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hParts, tvisort);
					}
					break;
				}
				delete prox;
			}
		}
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
			if (bFilter & IsFiltered(pcounter->techtree))
				continue;
			CString s;
			PtrCoreEntry pce = new CoreEntry;
			pce->tag = (AGCObjectType)AGC_ChaffTypeOK;
			pce->entry = (LPARAM)pcounter;
			CString pxs = "";
			PtrCorePart px = pigccore->ProxyGet(pcounter->uid);
			if (px)
				pxs.Format("(%d)",px->uid);
			s.Format("%s (%d)%s",pcounter->name,pcounter->uid,pxs);
			pce->name.Format("Counter: %s",s);
			RefreshStores(pce);
			maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hCounters, tvisort);
		}

		for (int j=0;j<pigccore->cl_Probes.GetSize();j++)
		{
			PtrCoreProbe pprobe = pigccore->cl_Probes.GetAt(j);
			if (bFilter & IsFiltered(pprobe->techtree))
				continue;
			CString s;
			PtrCoreEntry pce = new CoreEntry;
			pce->tag = AGC_ProbeType;
			pce->entry = (LPARAM)pprobe;
			CString pxs = "";
			PtrCorePart px = pigccore->ProxyGet(pprobe->uid);
			if (px)
				pxs.Format("(%d)",px->uid);
			s.Format("%s (%d)%s",pprobe->name,pprobe->uid,pxs);
			pce->name.Format("Probe: %s",s);
			RefreshStores(pce);
			maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hProbes, tvisort);
		}
		for (int j=0;j<pigccore->cl_Mines.GetSize();j++)
		{
			PtrCoreMine pmine = pigccore->cl_Mines.GetAt(j);
			if (bFilter & IsFiltered(pmine->techtree))
				continue;
			CString s;
			PtrCoreEntry pce = new CoreEntry;
			pce->tag = AGC_MineType;
			pce->entry = (LPARAM)pmine;
			CString pxs = "";
			PtrCorePart px = pigccore->ProxyGet(pmine->uid);
			if (px)
				pxs.Format("(%d)",px->uid);
			s.Format("%s (%d)%s",pmine->name,pmine->uid,pxs);
			pce->name.Format("Mine: %s",s);
			RefreshStores(pce);
			maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hMines, tvisort);
		}
		for (int j=0;j<pigccore->cl_Missiles.GetSize();j++)
		{
			PtrCoreMissile pmissile = pigccore->cl_Missiles.GetAt(j);
			if (bFilter & IsFiltered(pmissile->techtree))
				continue;
			CString s;
			PtrCoreEntry pce = new CoreEntry;
			pce->tag = AGC_MissileType;
			pce->entry = (LPARAM)pmissile;
			CString pxs = "";
			PtrCorePart px = pigccore->ProxyGet(pmissile->uid);
			if (px)
				pxs.Format("(%d)",px->uid);
			s.Format("%s (%d)%s",pmissile->name,pmissile->uid,pxs);
			pce->name.Format("Missile: %s",s);
			RefreshStores(pce);
			maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hMissiles, tvisort);
		}
	}

	for (int j=0;j<pigccore->cl_StationTypes.GetSize();j++)
	{
		PtrCoreStationType pstation = pigccore->cl_StationTypes.GetAt(j);
		if (bFilter & IsFiltered(pstation->techtree))
			continue;
		CString s;
		PtrCoreEntry pce = new CoreEntry;
		pce->tag = AGC_StationType;
		pce->entry = (LPARAM)pstation;
		s.Format("%s (%d)",pstation->name,pstation->uid);
		pce->name.Format("Station: %s",s);
		RefreshStores(pce);
		maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hStationsRoot/*hStations[pstation->uid / 100]*/, tvisort);
	}
	for (int j=0;j<pigccore->cl_Projectiles.GetSize();j++)
	{
		PtrCoreProjectile pprojectile = pigccore->cl_Projectiles.GetAt(j);
		CString s;
		PtrCoreEntry pce = new CoreEntry;
		pce->tag = AGC_ProjectileType;
		pce->entry = (LPARAM)pprojectile;
		s.Format("p #%d",pprojectile->uid);
		pce->name.Format("Projectile: %s",s);
		RefreshStores(pce);
		maintree->InsertItem(TVIF_TEXT|TVIF_PARAM, s, 0, 0, 0, 0,  (LPARAM)pce, hProjectiles, TVI_SORT);
	}

	for (int j=0;j<pigccore->cl_TreasureSets.GetSize();j++)
	{
		PtrCoreTreasureSet ptres = pigccore->cl_TreasureSets.GetAt(j);
		CString s;
		PtrCoreEntry pce = new CoreEntry;
		pce->tag = AGC_TreasureSet;
		pce->entry = (LPARAM)ptres;
		s.Format("%s (%d)",ptres->name,ptres->uid);
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
		CAboutDlg dlgAbout;
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
		case AGC_Civilization:{
			PtrCoreCiv pciv = (PtrCoreCiv) pce->entry;
			dlgCiv.pciv = pciv;
			dlgCiv.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgCiv;
			//AfxMessageBox(pciv->name);
			pTechTree = pciv->techtree;
			sTechName.Format("Faction: %s (%d)",pciv->name,pciv->uid);
			showmb=true;
			}break;
		case AGC_Development:{
			PtrCoreDevel pdevel = (PtrCoreDevel) pce->entry;
			dlgDevel.pdevel = pdevel;
			dlgDevel.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgDevel;
			pTechTree = pdevel->techtree;
			sTechName.Format("Devel: %s (%d)",pdevel->name,pdevel->uid);
			showmb=true;
			}break;
		case AGC_BucketStart:{ // ship
			PtrCoreShip pship = (PtrCoreShip) pce->entry;
			dlgShip.pship = pship;
			dlgShip.UpdateData(FALSE);
			dlgShipLoadout.pship = pship;
			dlgShipLoadout.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgShip;
			pTechTree = pship->techtree;
			sTechName.Format("Ship: %s (%d)",pship->name,pship->uid);
			showmb=true;
			ShowLoadout = true;
			}break;
		case AGC_StationType:{ // station
			PtrCoreStationType pstation = (PtrCoreStationType) pce->entry;
			dlgStation.pstation = pstation;
			dlgStation.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgStation;
			pTechTree = pstation->techtree;
			pTechTreeLocal = pstation->TechTreeLocal;
			sTechName.Format("Station: %s (%d)",pstation->name,pstation->uid);
			showmb=true;
			}break;
		case AGC_DroneType:{ // drone
			PtrCoreDrone pdrone = (PtrCoreDrone) pce->entry;
			dlgDrone.pdrone = pdrone;
			dlgDrone.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgDrone;
			pTechTree = pdrone->techtree;
			sTechName.Format("Drone: %s (%d)",pdrone->name,pdrone->uid);
			showmb=true;
			}break;
		case AGC_MissileType:{ // Missile
			PtrCoreMissile pmissile = (PtrCoreMissile) pce->entry;
			dlgMissile.pmissile = pmissile;
			dlgMissile.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgMissile;
			pTechTree = pmissile->techtree;
			sTechName.Format("Missile: %s (%d)",pmissile->name,pmissile->uid);
			showmb=true;
			}break;
		case AGC_PartType:{ // part
			PtrCorePart ppart = (PtrCorePart) pce->entry;
			dlgPart.ppart = ppart;
			dlgPart.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgPart;
			if (!ppart->isspec){
				pTechTree = ppart->techtree;
				sTechName.Format("Part: %s (%d)",ppart->name,ppart->uid);
			}
			showmb=true;
			}break;
		case AGC_MineType:{ // mine
			PtrCoreMine pmine = (PtrCoreMine) pce->entry;
			dlgMine.pmine = pmine;
			dlgMine.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgMine;
			pTechTree = pmine->techtree;
			sTechName.Format("Mine: %s (%d)",pmine->name,pmine->uid);
			showmb=true;
			}break;
		case AGC_ChaffTypeOK:{
			PtrCoreCounter pcounter = (PtrCoreCounter) pce->entry;
			dlgChaff.pcounter = pcounter;
			dlgChaff.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgChaff;
			pTechTree = pcounter->techtree;
			sTechName.Format("Counter: %s (%d)",pcounter->name,pcounter->uid);
			showmb=true;
			}break;
		case AGC_ProbeType:{
			PtrCoreProbe pprobe = (PtrCoreProbe) pce->entry;
			dlgProbe.pprobe = pprobe;
			dlgProbe.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgProbe;
			pTechTree = pprobe->techtree;
			sTechName.Format("Probe: %s (%d)",pprobe->name,pprobe->uid);
			showmb=true;
			}break;
		case AGC_ProjectileType:{
			PtrCoreProjectile pprojectile = (PtrCoreProjectile) pce->entry;
			dlgProjectile.pprojectile = pprojectile;
			dlgProjectile.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgProjectile;
			}break;
		case AGC_Constants:{
			dlgConstants.pconst = (PtrCoreConstants) pce->entry;
			dlgConstants.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgConstants;
			}break;
		case AGC_TreasureSet:{ // treasuresets
			PtrCoreTreasureSet ptres = (PtrCoreTreasureSet) pce->entry;
			dlgTreasure.ptres = ptres;
			dlgTreasure.UpdateData(FALSE);
			curdiag = (CDialog *)&dlgTreasure;
			sTechName.Format("TreasureSet: %s (%d)",ptres->name,ptres->uid);
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
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CICEDlg::OnClickedLoad(void)
{
	if (DiscardChanges() == IDNO) return;
	CString startpath = cArtPath + "\\*.igc";
#ifdef _ICEPUB
	CFileDialog cfd(TRUE,"igc",NULL,OFN_FILEMUSTEXIST|OFN_NOCHANGEDIR|OFN_NONETWORKBUTTON,"Allegiance Core|*.igc|",this,OPENFILENAME_SIZE_VERSION_400);
#else
	CFileDialog cfd(TRUE,"igc",startpath,OFN_FILEMUSTEXIST|OFN_NOCHANGEDIR|OFN_NONETWORKBUTTON,"Allegiance Core|*.igc|",this,OPENFILENAME_SIZE_VERSION_400);
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

CString CICEDlg::TTHaveBit(int ipBit)
{
	int ibit = ipBit; 
	int idx = ibit/8;
	int imask = 1<<(ibit%8);
	CString s ="";
	if (ibit>400){
		ibit -=400;
		//if (ibit == 1) s = "GP: Allow Devel\r\n";
		//if (ibit == 2) s = "GP: Deatch Match\r\n";
		if (ibit == 3) s = "GP: Allow supremacy\r\n";
		if (ibit == 4) s = "GP: Allow tactical\r\n";
		if (ibit == 5) s = "GP: Allow expansion\r\n";
		if (ibit == 6) s = "GP: Allow shipyard\r\n";
		//if (ibit == 7) s = "GP: CTF or money\r\n";
		//if (s != "") return s;
	}
	ibit = ipBit;

	if (ibit>=400)
	{
		int idxciv = idx-50;
		for (int j=0;j<pigccore->cl_Civs.GetSize();j++)
		{
			PtrCoreCiv pciv = pigccore->cl_Civs.GetAt(j);
			if (pciv->techtree[idxciv] & imask)
			{
				s.AppendFormat("Faction: %s (%d) 'Devel'\r\n",pciv->name,pciv->uid);
			}
			if (pciv->techtree[idx] & imask)
			{
				s.AppendFormat("Faction: %s (%d) 'No Devel'\r\n",pciv->name,pciv->uid);
			}
		}
		for (int j=0;j<pigccore->cl_StationTypes.GetSize();j++)
		{
			PtrCoreStationType p = pigccore->cl_StationTypes.GetAt(j);
			if (p->TechTreeLocal[idxciv] & imask)
			{
				s.AppendFormat("Station: %s (%d) - local\r\n",p->name,p->uid);
			}
		}


	}
	//idx = ibit/8+50;
	for (int j=0;j<pigccore->cl_Devels.GetSize();j++)
	{
		PtrCoreDevel p = pigccore->cl_Devels.GetAt(j);
		if (p->techtree[idx] & imask)
		{
			s.AppendFormat("Devel: %s (%d)\r\n",p->name,p->uid);
		}
	}

	for (int j=0;j<pigccore->cl_Ships.GetSize();j++)
	{
		PtrCoreShip pship = pigccore->cl_Ships.GetAt(j);
		if (pship->techtree[idx] & imask)
		{
			s.AppendFormat("Ship: %s (%d)\r\n",pship->name,pship->uid);
		}
	}

	for (int j=0;j<pigccore->cl_StationTypes.GetSize();j++)
	{
		PtrCoreStationType p = pigccore->cl_StationTypes.GetAt(j);
		if (p->techtree[idx] & imask)
		{
			s.AppendFormat("Station: %s (%d)\r\n",p->name,p->uid);
		}
	}

	for (int j=0;j<pigccore->cl_Drones.GetSize();j++)
	{
		PtrCoreDrone p = pigccore->cl_Drones.GetAt(j);
		if (p->techtree[idx] & imask)
		{
			s.AppendFormat("Drone: %s (%d)\r\n",p->name,p->uid);
		}
	}
	for (int j=0;j<pigccore->cl_Missiles.GetSize();j++)
	{
		PtrCoreMissile p = pigccore->cl_Missiles.GetAt(j);
		if (p->techtree[idx] & imask)
		{
			s.AppendFormat("Missile: %s (%d)\r\n",p->name,p->uid);
		}
	}
	for (int j=0;j<pigccore->cl_Parts.GetSize();j++)
	{
		PtrCorePart p = pigccore->cl_Parts.GetAt(j);
		if (!p->isspec)
			if (p->techtree[idx] & imask)
			{
				s.AppendFormat("Part: %s (%d)\r\n",p->name,p->uid);
			}
	}
	for (int j=0;j<pigccore->cl_Mines.GetSize();j++)
	{
		PtrCoreMine p = pigccore->cl_Mines.GetAt(j);
		if (p->techtree[idx] & imask)
		{
			s.AppendFormat("Mine: %s (%d)\r\n",p->name,p->uid);
		}
	}
	for (int j=0;j<pigccore->cl_Counters.GetSize();j++)
	{
		PtrCoreCounter p = pigccore->cl_Counters.GetAt(j);
		if (p->techtree[idx] & imask)
		{
			s.AppendFormat("Counter: %s (%d)\r\n",p->name,p->uid);
		}
	}
	for (int j=0;j<pigccore->cl_Probes.GetSize();j++)
	{
		PtrCoreProbe p = pigccore->cl_Probes.GetAt(j);
		if (p->techtree[idx] & imask)
		{
			s.AppendFormat("Probe: %s (%d)\r\n",p->name,p->uid);
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
		case AGC_Development:
			//cl_Gen = (CArray<LPARAM,LPARAM> *)&pigccore->cl_Devels;
			if (pigccore->MoveDevel((PtrCoreDevel)curpce->entry,dir))
				OnClickedRefresh();
			return;
			break;
		case AGC_StationType:
			cl_Gen = (CArray<LPARAM,LPARAM> *)&pigccore->cl_StationTypes;
			break;
		case AGC_DroneType:
			cl_Gen = (CArray<LPARAM,LPARAM> *)&pigccore->cl_Drones;
			break;
		case AGC_BucketStart:
			cl_Gen = (CArray<LPARAM,LPARAM> *)&pigccore->cl_Ships;
			break;
		case AGC_PartType:
			cl_Gen = (CArray<LPARAM,LPARAM> *)&pigccore->cl_Parts;
			break;
		case AGC_Civilization:
			cl_Gen = (CArray<LPARAM,LPARAM> *)&pigccore->cl_Civs;
			break;
		case AGC_MineType:
			{
			cl_Gen = (CArray<LPARAM,LPARAM> *)&pigccore->cl_Parts;
			PtrCoreMine pmine = (PtrCoreMine) curp;
			curp = (LPARAM)pigccore->ProxyGet(pmine->uid);
			}
			break;
		case AGC_MissileType:
			{
			cl_Gen = (CArray<LPARAM,LPARAM> *)&pigccore->cl_Parts;
			PtrCoreMissile pmissile = (PtrCoreMissile) curp;
			curp = (LPARAM)pigccore->ProxyGet(pmissile->uid);
			}
			break;
		case AGC_ChaffTypeOK:
			{
			cl_Gen = (CArray<LPARAM,LPARAM> *)&pigccore->cl_Parts;
			PtrCoreCounter pcounter = (PtrCoreCounter) curp;
			curp = (LPARAM)pigccore->ProxyGet(pcounter->uid);
			}
			break;
		case AGC_ProbeType:
			{
			cl_Gen = (CArray<LPARAM,LPARAM> *)&pigccore->cl_Parts;
			PtrCoreProbe pprobe = (PtrCoreProbe) curp;
			curp = (LPARAM)pigccore->ProxyGet(pprobe->uid);
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
	if (pce->tag == AGC_MissileType)
	{
		PtrCoreMissile pp = (PtrCoreMissile) pce->entry;
		PtrCorePart p = pigccore->ProxyGet(pp->uid);
		if (p != NULL)
		{
			pce->tag = AGC_PartType;
			pce->entry = (LPARAM)p;
		}
	}
	if (pce->tag == AGC_ChaffTypeOK)
	{
		PtrCoreCounter pp = (PtrCoreCounter) pce->entry;
		PtrCorePart p = pigccore->ProxyGet(pp->uid);
		if (p != NULL)
		{
			pce->tag = AGC_PartType;
			pce->entry = (LPARAM)p;
		}
	}
	if (pce->tag == AGC_ProbeType)
	{
		PtrCoreProbe pp = (PtrCoreProbe) pce->entry;
		PtrCorePart p = pigccore->ProxyGet(pp->uid);
		if (p != NULL)
		{
			pce->tag = AGC_PartType;
			pce->entry = (LPARAM)p;
		}
	}

	if (pce->tag == AGC_MineType)
	{
		PtrCoreMine pp = (PtrCoreMine) pce->entry;
		PtrCorePart p = pigccore->ProxyGet(pp->uid);
		if (p != NULL)
		{
			pce->tag = AGC_PartType;
			pce->entry = (LPARAM)p;
		}
	}

	LPARAM entry = NULL;
	switch(pce->tag)
	{
	case AGC_ProbeType:{
		PtrCoreProbe pprobecur = (PtrCoreProbe) pce->entry;
		PtrCoreProbe pprobe = new IGCCoreProbe;
		memcpy(pprobe,pprobecur,sizeof(IGCCoreProbe));
		pigccore->AddProbe(pprobe);
		entry = (LPARAM)pprobe;
		}break;
	case AGC_MineType:{
		PtrCoreMine pminecur = (PtrCoreMine) pce->entry;
		PtrCoreMine pmine = new IGCCoreMine;
		memcpy(pmine,pminecur,sizeof(IGCCoreMine));
		pigccore->AddMine(pmine);
		entry = (LPARAM)pmine;
		}break;
	case AGC_Civilization:{
		PtrCoreCiv pcivcur = (PtrCoreCiv) pce->entry;
		PtrCoreCiv pciv = new IGCCoreCiv;
		memcpy(pciv,pcivcur,sizeof(IGCCoreCiv));
		pigccore->AddCiv(pciv);
		entry = (LPARAM)pciv;
		}break;
	case AGC_Development:{
		PtrCoreDevel pdevelcur = (PtrCoreDevel) pce->entry;
		PtrCoreDevel pdevel = new IGCCoreDevel;
		memcpy(pdevel,pdevelcur,sizeof(IGCCoreDevel));
		pigccore->AddDevel(pdevel);
		entry = (LPARAM)pdevel;
		}break;
	case AGC_BucketStart:{ // ship
		PtrCoreShip pshipcur = (PtrCoreShip) pce->entry;
		PtrCoreShip pship = new IGCCoreShip;
		memcpy(pship,pshipcur,sizeof(IGCCoreShip));
		pigccore->AddShip(pship);
		entry = (LPARAM)pship;
		}break;
	case AGC_StationType:{ // station
		PtrCoreStationType pstationcur = (PtrCoreStationType) pce->entry;
		PtrCoreStationType pstation = new IGCCoreStationType;
		memcpy(pstation,pstationcur,sizeof(IGCCoreStationType));
		pigccore->AddStationType(pstation);
		entry = (LPARAM)pstation;
		}break;
	case AGC_DroneType:{ // drone
		PtrCoreDrone pdronecur = (PtrCoreDrone) pce->entry;
		PtrCoreDrone pdrone = new IGCCoreDrone;
		memcpy(pdrone,pdronecur,sizeof(IGCCoreDrone));
		pigccore->AddDrone(pdrone);
		entry = (LPARAM)pdrone;
		}break;
	case AGC_ProjectileType:{
		PtrCoreProjectile pprojcur = (PtrCoreProjectile) pce->entry;
		PtrCoreProjectile pproj = new IGCCoreProjectile;
		memcpy(pproj,pprojcur,sizeof(IGCCoreProjectile));
		pigccore->AddProjectile(pproj);
		entry = (LPARAM)pproj;
		}break;
	case AGC_PartType:{ // part
		PtrCorePart ppartcur = (PtrCorePart) pce->entry;
		PtrCorePart ppart = new IGCCorePart;
		memcpy(ppart,ppartcur,sizeof(IGCCorePart));
		pigccore->AddPart(ppart);
		entry = (LPARAM)ppart;
		if (ppart->isspec)
		{
            PtrCoreEntry pce = pigccore->ProxyPart(ppartcur->usemask);
			if (pce != NULL)
			{
				switch(pce->tag)
				{
				case AGC_MissileType:{ // drone
					PtrCoreMissile pmissilecur = (PtrCoreMissile) pce->entry;
					PtrCoreMissile pmissile = new IGCCoreMissile;
					memcpy(pmissile,pmissilecur,sizeof(IGCCoreMissile));
					pigccore->AddMissile(pmissile);
					ppart->usemask = pmissile->uid;
					entry = (LPARAM)pmissile;
					}break;
				case AGC_MineType:{ // mine
					PtrCoreMine pminecur = (PtrCoreMine) pce->entry;
					PtrCoreMine pmine = new IGCCoreMine;
					memcpy(pmine,pminecur,sizeof(IGCCoreMine));
					pigccore->AddMine(pmine);
					ppart->usemask = pmine->uid;
					entry = (LPARAM)pmine;
					}break;
				case AGC_ChaffTypeOK:{
					PtrCoreCounter pcountercur = (PtrCoreCounter) pce->entry;
					PtrCoreCounter pcounter = new IGCCoreCounter;
					memcpy(pcounter,pcountercur,sizeof(IGCCoreCounter));
					pigccore->AddCounter(pcounter);
					ppart->usemask = pcounter->uid;
					entry = (LPARAM)pcounter;
					}break;
				case AGC_ProbeType:{
					PtrCoreProbe pprobecur = (PtrCoreProbe) pce->entry;
					PtrCoreProbe pprobe = new IGCCoreProbe;
					memcpy(pprobe,pprobecur,sizeof(IGCCoreProbe));
					pigccore->AddProbe(pprobe);
					ppart->usemask = pprobe->uid;
					entry = (LPARAM)pprobe;
					}break;
				}
				delete pce;
			}
		}
		}break;
	case AGC_MissileType:
	case AGC_ChaffTypeOK:
		AfxMessageBox("Warning: unproxied part ! - this should not happend ! - contact the author of ICE");
		break;
	case AGC_Constants:{
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
	case AGC_PartType:{ // part
		entry = pigccore->DeletePart((PtrCorePart) pce->entry,true);
		}break;
	case AGC_ProbeType:{
		entry = pigccore->DeleteProbe((PtrCoreProbe) pce->entry);
		}break;
	case AGC_MineType:{
		entry = pigccore->DeleteMine((PtrCoreMine) pce->entry);
		}break;
	case AGC_ChaffTypeOK:{
		entry = pigccore->DeleteCounter((PtrCoreCounter) pce->entry);
		}break;
	case AGC_MissileType:{
		entry = pigccore->DeleteMissile((PtrCoreMissile) pce->entry);
		}break;
	case AGC_Civilization:{
		entry = pigccore->DeleteCiv((PtrCoreCiv) pce->entry);
		}break;
	case AGC_Development:{
		entry = pigccore->DeleteDevel((PtrCoreDevel) pce->entry);
		}break;
	case AGC_BucketStart:{ // ship
		entry = pigccore->DeleteShip((PtrCoreShip) pce->entry);
		}break;
	case AGC_StationType:{ // station
		entry = pigccore->DeleteStationType((PtrCoreStationType) pce->entry);
		}break;
	case AGC_DroneType:{ // drone
		entry = pigccore->DeleteDrone((PtrCoreDrone) pce->entry);
		}break;
	case AGC_ProjectileType:{
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
	CString t2 = "";
	if (!pigccore) return;
	if (pTT)
	{
		tt = "Depends on:\r\n";
		for (int i=0;i<50;i++)
		{
			for (int j=0;j<8;j++)
			{
				if (pTT[i] & (1<<j))
				{
					tt.AppendFormat("%d:\r\n",i*8+j);
					CString hb = TTHaveBit(400+i*8+j);
					hb.Replace("\r\n","\r\n  ");
					tt.AppendFormat("  %s\r\n", hb);
				}
			}
		}
		t2.Format("%s\r\n",tt);
	}
	if ((pTT == NULL) & (iBit!=-1))
	{
		tt.Format("%d defined by:\r\n",iBit);
		CString hb = TTHaveBit(400+iBit);
		hb.Replace("\r\n","\r\n  ");
		tt.AppendFormat("  %s\r\n", hb);
		tt.AppendFormat("%d pre-required in:\r\n",iBit);
		hb = TTHaveBit(iBit);
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
	GetDlgItem(IDC_TECHTREE2)->ShowWindow(swf);

	GetDlgItem(IDC_BUTFILTER)->ShowWindow(swf);
	GetDlgItem(IDC_CLEARFILTER)->ShowWindow(swf);
	GetDlgItem(IDC_FILTER)->ShowWindow(swf);
	//GetDlgItem(IDC_ADDTOFILTER)->ShowWindow(swf);
	//GetDlgItem(IDC_REMFROMFILTER)->ShowWindow(swf);
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
		BuildTree();
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

void CICEDlg::OnBnClickedAddtofilter()
{
	if (!pigccore) return;
	if (!pTechTree) return;
	int base = 50;
	if (sTechName.Left(7) == "Faction")
		base = 0;
	for (int i=0;i<50;i++)
		tFilter[i] |= pTechTree[base+i];
	UpdateFilter(true);
}

void CICEDlg::OnBnClickedRemfromfilter()
{
	if (!pigccore) return;
	if (!pTechTree) return;
	int base = 50;
	if (sTechName.Left(7) == "Faction")
		base = 0;
	for (int i=0;i<50;i++)
		tFilter[i] &= ~(pTechTree[base+i]);
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
	// TODO: Add your control notification handler code here
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
	// TODO: Add your control notification handler code here
}
