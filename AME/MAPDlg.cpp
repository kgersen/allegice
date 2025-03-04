// MAPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AGM.h"
#include <corestruct.h>
#include "MAPDlg.h"
#include "igcmap.h"
#include "SectDlg.h"
#include "AlephDlg.h"
#include "RockDlg.h"
#include "2DMap.h"
#include "MAPDlg.h"
#include "RandomDlg.h"
#include <math.h>

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


// CMAPDlg dialog

IMPLEMENT_DYNAMIC(CMAPDlg, CDialog)
CMAPDlg::CMAPDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMAPDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	pcore = NULL;
}

CMAPDlg::~CMAPDlg()
{
	if (pcore) delete pcore;
}

void CMAPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX,IDC_CKZVIEW,sect2d.bShowZ);
	if (!pDX->m_bSaveAndValidate)
		DDX_Text(pDX,IDC_CORE_NAME,sCorename);
}


BEGIN_MESSAGE_MAP(CMAPDlg, CDialog)
	ON_LBN_DBLCLK(IDC_LB_SECTORS, OnDblclkLbSectors)
	ON_LBN_SELCHANGE(IDC_LB_SECTORS, OnSelchangeLbSectors)
	ON_BN_CLICKED(ID_MAP_NEW, OnClickedMapNew)
	ON_BN_CLICKED(ID_MAP_LOAD, OnClickedMapLoad)
	ON_BN_CLICKED(ID_MAP_SAVE, OnClickedMapSave)
	ON_BN_CLICKED(ID_MAP_SAVEAS, OnClickedMapSaveas)
	ON_BN_CLICKED(ID_MAP_QUIT, OnClickedMapQuit)
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_B_DELALL_ALEPHS, OnClickedBDelallAlephs)
	ON_BN_CLICKED(IDC_B_DELALL_BASES, OnClickedBDelallBases)
	ON_BN_CLICKED(IDC_B_DELALL_ROCKS, OnClickedBDelallRocks)
	ON_BN_CLICKED(IDC_B_RDALL_ALEPHS, OnClickedBRdallAlephs)
	ON_BN_CLICKED(IDC_B_RDALL_ROCKS, OnClickedBRdallRocks)
	ON_BN_CLICKED(IDC_MAP_GRID,OnClickedGrid)
	ON_BN_CLICKED(IDC_MAP_SNAP,OnClickedSnap)
	ON_BN_CLICKED(IDC_B_TEMPLATES, OnClickedBTemplates)
	ON_COMMAND_RANGE(IDM_TPL_ALEPHS,IDM_TPL_SECTORS,OnSelTemplates)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_CKZVIEW, OnBnClickedCkzview)
	ON_BN_CLICKED(IDC_B_RENAME_SECTORS, OnBnClickedBRenameSectors)
	ON_BN_CLICKED(IDC_CORELOAD, OnBnClickedCoreload)
	ON_BN_CLICKED(IDC_ABOUT, OnBnClickedAbout)
END_MESSAGE_MAP()

// CMAPDlg message handlers
BOOL CMAPDlg::OnInitDialog()
{
	cursect = NULL;
	pigcmap = NULL;
	changed = false;
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	plbsect = (CListBox *) CWnd::GetDlgItem(IDC_LB_SECTORS);
	CRect rect2dmap(7,330,7+map2d.MapW,330+map2d.MapH);

	map2d.igcmap = pigcmap;
	map2d.igccursect = NULL;
	map2d.BuildMapTables();
	map2d.Create(NULL, "",WS_CHILD | WS_VISIBLE, rect2dmap, this, IDC_2DMAP);

	CRect rectsect2d(265,40,MAP2DSIZE+265,MAP2DSIZE+40);
	sect2d.cigcmap = pigcmap;
	sect2d.cArtPath = cArtPath;
	sect2d.Create(NULL, "", WS_CHILD | WS_VISIBLE, rectsect2d, this, ID_SECTWND);
	sect2d.ChangeSector(NULL);

	mappath = "";

	CButton *cbpg = (CButton *)CWnd::GetDlgItem(IDC_MAP_GRID);
	CButton *cbps = (CButton *)CWnd::GetDlgItem(IDC_MAP_SNAP);

	cbpg->SetCheck(BST_CHECKED);
	cbps->SetCheck(BST_CHECKED);

	tplmenu.CreatePopupMenu(); //should check
	tplmenu.AppendMenu(MF_STRING,IDM_TPL_ALEPHS,"Alephs");
	tplmenu.AppendMenu(MF_STRING,IDM_TPL_SECTORS,"Sectors");
	tplmenu.AppendMenu(MF_STRING,IDM_TPL_ROCKS,"Rocks");
	strcpy(tplsector.igcsector.globe,"Random");
	strcpy(tplsector.igcsector.nebbg,"Random");
	strcpy(tplaleph.igcaleph.renderbmp,"Random");
	strcpy_s(tplaleph.igcaleph.imagebmp,"");

	CRandomDlg dlgrand;
	ra_p1 = dlgrand.ra_p1;
	ra_p2 = dlgrand.ra_p2;
	ra_p3 = dlgrand.ra_p3;
	ra_p4 = dlgrand.ra_p4;
	ra_p5 = dlgrand.ra_p5;

	// read the parameters in the registry
	cArtPathClient = "";
	char pdata[255];
	DWORD psize = 255;
	HKEY hKey;
	LONG regres;

	regres = RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Microsoft Games\\Allegiance\\1.4", 0, KEY_READ, &hKey);
	if (regres != ERROR_SUCCESS)
		regres = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Microsoft Games\\Allegiance\\1.4", 0, KEY_READ, &hKey);
	if (regres != ERROR_SUCCESS)
		regres = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Microsoft Games\\Allegiance\\1.2", 0, KEY_READ, &hKey);

	if (regres == ERROR_SUCCESS)
	{
		if (RegQueryValueEx(hKey,"ArtPath",NULL,NULL,(LPBYTE)pdata,&psize)==ERROR_SUCCESS)
		{
			cArtPathClient = pdata;
		}
		else if (RegQueryValueEx(hKey,"EXE Path",NULL,NULL,(LPBYTE)pdata,&psize)==ERROR_SUCCESS)
		{
			cArtPathClient = pdata;
			cArtPathClient  += "\\Artwork";
		}
		RegCloseKey(hKey);
	}

	pcore = NULL;
	PtrCore pc = new CIGCCore();
	if (pc->ReadFromFile(cArtPath+"\\"+sCorename))
	{
		if (pcore)
			delete pcore;
		pcore = pc;
	}
	else
	{
		delete pc;
		AfxMessageBox("cannot load core: "+ sCorename);
		while (pcore == NULL)
		{
			OnBnClickedCoreload();
		}
	}
	return TRUE;
}

void CMAPDlg::LoadSectors()
{
	// load the sectors

	last_sector_uid = UID_SEED;
	plbsect->ResetContent();
	if (pigcmap == NULL) return;

	POSITION pos = pigcmap->cl_sectors.GetHeadPosition();
	for (int i=0;i < pigcmap->cl_sectors.GetCount();i++)
	{
		PtrSector psector = &(pigcmap->cl_sectors.GetNext(pos));
		int idx = plbsect->AddString(psector->igcsector.name);
		plbsect->SetItemDataPtr(idx,psector);
		if (last_sector_uid < psector->igcsector.uid)
			last_sector_uid = psector->igcsector.uid;
	}
	for (int i=0;i < plbsect->GetCount();i++)
	{
		PtrSector psector = (PtrSector) plbsect->GetItemDataPtr(i);
		psector->lbindex = i;
	}
	// compute last*uid
	last_aleph_uid = UID_SEED;
	pos = pigcmap->cl_alephs.GetHeadPosition();
	for (int i=0;i < pigcmap->cl_alephs.GetCount();i++)
	{
		CIGCAleph *paleph;
		paleph = &(pigcmap->cl_alephs.GetNext(pos));
		if (last_aleph_uid < paleph->igcaleph.uid)
			last_aleph_uid = paleph->igcaleph.uid;
	}

	last_base_uid = UID_SEED;
	pos = pigcmap->cl_bases.GetHeadPosition();
	for (int i=0;i < pigcmap->cl_bases.GetCount();i++)
	{
		CIGCBase *pbase;
		pbase = &(pigcmap->cl_bases.GetNext(pos));
		if (last_base_uid < pbase->igcbase.uid)
			last_base_uid = pbase->igcbase.uid;
	}

	last_rock_uid = UID_SEED;
	pos = pigcmap->cl_rocks.GetHeadPosition();
	for (int i=0;i < pigcmap->cl_rocks.GetCount();i++)
	{
		CIGCRock *prock;
		prock = &(pigcmap->cl_rocks.GetNext(pos));
		if (last_rock_uid < prock->igcrock.uid)
			last_rock_uid = prock->igcrock.uid;
	}
	
}

void CMAPDlg::SetSector(PtrSector psect)
{
	plbsect->SetCurSel(psect->lbindex);
	ChangeSector();
}

void CMAPDlg::ChangeSector(void)
{
	int nIndex = plbsect->GetCurSel();
	if (nIndex != LB_ERR)
	{
		//POSITION pos = pigcmap->cl_sectors.FindIndex(nIndex);
		PtrSector psector = (PtrSector) plbsect->GetItemDataPtr(nIndex);//&(pigcmap->cl_sectors.GetAt(pos));
		cursect = psector;
		sect2d.ChangeSector(psector);
		map2d.igccursect = psector;
		map2d.BuildMapTables();
	}
	else
	{
		cursect = NULL;
		sect2d.ChangeSector(NULL);
		map2d.igccursect = NULL;
		map2d.BuildMapTables();

	}

	map2d.Invalidate(TRUE);
	map2d.UpdateWindow();

	sect2d.AllUpdate();
}

void CMAPDlg::OnSelchangeLbSectors(void) 
{
	// TODO: Add your control notification handler code here
	ChangeSector();

}


void CMAPDlg::NewSector(float x, float y) // add a sector
{
	CIGCSector *newsect;
	CString n;

	newsect = & CIGCSector::CIGCSector();

	last_sector_uid++;
	newsect->igcsector.uid = last_sector_uid;
	n.Format("Sector%d",newsect->igcsector.uid);
	strcpy(newsect->igcsector.name,n);
	newsect->igcsector.posx = x;
	newsect->igcsector.posy = y;
	newsect->ApplyTemplate(&tplsector,true);
	pigcmap->cl_sectors.AddTail(*newsect);
	LoadSectors();
	Invalidate(FALSE);
	Paint2dview();
}

void CMAPDlg::Paint2dview(void)
{
	// repaint both views
	map2d.BuildMapTables();
	map2d.Invalidate(TRUE);
	map2d.UpdateWindow();

	sect2d.AllUpdate();
}

void CMAPDlg::CreateAleph(CIGCSector *psec1,float x1,float y1,CIGCSector *psec2,float x2,float y2)
{
	CIGCAleph *al1;
	CIGCAleph *al2;
	al1 = & CIGCAleph::CIGCAleph();
	al2 = & CIGCAleph::CIGCAleph();
	al1->igcaleph.posx=x1; al1->igcaleph.posy=y1;
	al2->igcaleph.posx=x2; al2->igcaleph.posy=y2;
	last_aleph_uid++;
	al1->igcaleph.uid = last_aleph_uid;
	last_aleph_uid++;
	al2->igcaleph.uid = last_aleph_uid;
	al1->igcaleph.connecting_aleph_uid = al2->igcaleph.uid;
	al2->igcaleph.connecting_aleph_uid = al1->igcaleph.uid;
	al1->igcaleph.sector_uid = psec1->igcsector.uid;
	al2->igcaleph.sector_uid = psec2->igcsector.uid;
	strcpy(al1->igcaleph.DestinationSectorName,psec2->igcsector.name);
	strcpy(al2->igcaleph.DestinationSectorName,psec1->igcsector.name);
	al1->ApplyTemplate(&tplaleph,true);
	al2->ApplyTemplate(&tplaleph,true);
	pigcmap->cl_alephs.AddTail(*al1);
	pigcmap->cl_alephs.AddTail(*al2);
	sect2d.AllUpdate();
}
void CMAPDlg::CreateAleph(CIGCSector *psec1,CIGCSector *psec2)
{
	CIGCAleph *al1;
	CIGCAleph *al2;

	al1 = & CIGCAleph::CIGCAleph();
	al2 = & CIGCAleph::CIGCAleph();

	last_aleph_uid++;
	al1->igcaleph.uid = last_aleph_uid;
	last_aleph_uid++;
	al2->igcaleph.uid = last_aleph_uid;
	al1->igcaleph.connecting_aleph_uid = al2->igcaleph.uid;
	al2->igcaleph.connecting_aleph_uid = al1->igcaleph.uid;
	al1->igcaleph.sector_uid = psec1->igcsector.uid;
	al2->igcaleph.sector_uid = psec2->igcsector.uid;
	strcpy(al1->igcaleph.DestinationSectorName,psec2->igcsector.name);
	strcpy(al2->igcaleph.DestinationSectorName,psec1->igcsector.name);
	al1->ApplyTemplate(&tplaleph,true);
	al2->ApplyTemplate(&tplaleph,true);
	pigcmap->cl_alephs.AddTail(*al1);
	pigcmap->cl_alephs.AddTail(*al2);

	sect2d.AllUpdate();
}


void CMAPDlg::OnDblclkLbSectors(void)
{
	// open CsectDlg
	CSectDlg sdlg;
	sdlg.sArtPath = cArtPathClient;
	ChangeSector();
	sdlg.cursect = cursect;
	CString oldsectname = cursect->igcsector.name;
	switch (sdlg.DoModal())
	{
		case S_OK: 
		{
			LoadSectors();
			plbsect->SetCurSel(cursect->lbindex);
			if (oldsectname != cursect->igcsector.name)
			{
				// performe aleph renaming
				map2d.RenameAlephs(cursect);
			}
			Invalidate(FALSE);
			Paint2dview();
		}
			break;
		case S_SECTOR_DELETE:
			{
			if (AfxMessageBox(_T("Really delete this sector ?"),MB_YESNO|MB_DEFBUTTON2) != IDYES)
				break;
			sect2d.ChangeSector(NULL);
			map2d.igccursect = NULL;
			// perform delete of alephs
			POSITION pos = map2d.mapalephs.GetHeadPosition();
			for (int i=0;i < map2d.mapalephs.GetCount();i++)
			{
				SMapAleph *mapa = &(map2d.mapalephs.GetNext(pos));
				if ((mapa->aleph1->igcaleph.sector_uid == cursect->igcsector.uid)||
					(mapa->aleph2->igcaleph.sector_uid == cursect->igcsector.uid))
					map2d.DeleteAleph(mapa->aleph1);
			}
			// bases & rocks
			sect2d.DeleteAllBases();
			sect2d.DeleteAllRocks();
			pos = pigcmap->cl_sectors.Find(*cursect);
			pigcmap->cl_sectors.RemoveAt(pos);

			LoadSectors();
			Invalidate(FALSE);
			Paint2dview();
			}
			break;
		case S_SECTOR_CANCEL:
			break;
		default:
			break;
	}
}

void CMAPDlg::OnClickedMapNew(void)
{
	if (DiscardChanges() == IDNO) return;

	CWnd *pname = CWnd::GetDlgItem(IDC_MAP_NAME);
	pname->SetWindowText("");
	CIGCMap *pmap = new CIGCMap;
	pmap->pcore = pcore;
	mappath = "";
	map2d.igcmap = pmap;
	sect2d.cigcmap = pmap;
	map2d.igccursect = NULL;
	map2d.BuildMapTables();
	sect2d.ChangeSector(NULL);
	if (pigcmap)
		delete pigcmap;
	pigcmap = pmap;
	LoadSectors();
	Paint2dview();
	CButton *pbut = (CButton *)CWnd::GetDlgItem(ID_MAP_SAVE);
	pbut->EnableWindow(FALSE);
	pbut = (CButton *)CWnd::GetDlgItem(ID_MAP_SAVEAS);
	pbut->EnableWindow(TRUE);
	changed = true; // TODO
}

void CMAPDlg::OnClickedMapLoad(void)
{
	if (DiscardChanges() == IDNO) return;

	CString startpath = cArtPath + "\\*.igc";
	CFileDialog cfd(TRUE, "igc", startpath, OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR | OFN_NONETWORKBUTTON, "Allegiance Map|*.igc|", this);// OPENFILENAME_SIZE_VERSION_400);

	if (cfd.DoModal() == IDOK)
	{
		CString fileTitle = cfd.GetFileTitle();
		if ((fileTitle == "static_core") ||
			(fileTitle == "zone_core") ||
			(fileTitle == "training_1") ||
			(fileTitle == "training_3") ||
			(fileTitle == "training_5"))
		{
			CString mes;
			if ((fileTitle[0] != 't'))
				mes.Format("%s is not an Allegiance map",fileTitle);
			else
				mes.Format("%s is a map used by the training missions in Allegiance. Make a copy of it if you want to use it",fileTitle);

			AfxMessageBox(_T(mes));
		}
		else
		{
			CIGCMap *pmap = new CIGCMap;
			pmap->pcore = pcore;
			if (pmap->ReadFromFile(cfd.GetPathName()))
			{
				mappath.Format("%s",cfd.GetPathName());
				pmap->name.Format("%s",cfd.GetFileTitle());
				CWnd *pname = CWnd::GetDlgItem(IDC_MAP_NAME);
				pname->SetWindowText(pmap->name);
				map2d.igcmap = pmap;
				sect2d.cigcmap = pmap;
				map2d.igccursect = NULL;
				map2d.BuildMapTables();
				sect2d.ChangeSector(NULL);
				if (pigcmap)
					delete pigcmap;
				pigcmap = pmap;
				LoadSectors();
				Paint2dview();
				CButton *pbut = (CButton *)CWnd::GetDlgItem(ID_MAP_SAVE);
				pbut->EnableWindow(TRUE);
				pbut = (CButton *)CWnd::GetDlgItem(ID_MAP_SAVEAS);
				pbut->EnableWindow(TRUE);
				changed = true; // TODO
			}
			else
				delete pmap;
		}
	}
}

void CMAPDlg::OnClickedMapSave(void)
{
	UpdateData(TRUE); // no more need
	pigcmap->SaveToFile(mappath); // should check
	AfxMessageBox("Map saved to " +mappath);
	changed = false;
}

void CMAPDlg::OnClickedMapSaveas(void)
{
	CString startpath = cArtPath + "\\*.igc";
	CFileDialog cfd(FALSE,"igc",startpath,OFN_NOCHANGEDIR|OFN_NONETWORKBUTTON|OFN_OVERWRITEPROMPT,"Allegiance Map|*.igc|",this,OPENFILENAME_SIZE_VERSION_400);
	if (cfd.DoModal() == IDOK)
	{
		CString fileTitle = cfd.GetFileTitle();
		if ((fileTitle == "static_core") ||
			(fileTitle == "zone_core") ||
			(fileTitle == "training_1") ||
			(fileTitle == "training_3") ||
			(fileTitle == "training_5"))
		{
			AfxMessageBox(_T("ERROR: CANT OVERWRITE A SERVER SYSTEM FILE ! Choose another name."));
			return;
		}
		mappath.Format("%s",cfd.GetPathName());
		pigcmap->name.Format("%s",fileTitle);
		CWnd *pname = CWnd::GetDlgItem(IDC_MAP_NAME);
		pname->SetWindowText(pigcmap->name);

		OnClickedMapSave();
	}
}

int CMAPDlg::DiscardChanges(void) 
{
	if (changed)
		return AfxMessageBox(_T("Map not saved !!! Are you sure ? "),MB_YESNO|MB_DEFBUTTON2);
	return IDYES;
}

void CMAPDlg::OnClickedMapQuit(void)
{
	if (DiscardChanges() == IDNO)
		return;
	if (pigcmap)
		delete pigcmap;
	EndDialog(IDCANCEL);
}

HCURSOR CMAPDlg::OnQueryDragIcon(void)
{
	return (HCURSOR) m_hIcon;
}

void CMAPDlg::OnClickedBDelallAlephs(void)
{
	if (pigcmap == NULL) return;
	if (AfxMessageBox(_T("Really delete all alephs in all sectors ?"),MB_YESNO|MB_DEFBUTTON2) == IDYES)
	{
		pigcmap->cl_alephs.RemoveAll();
		LoadSectors();
		Invalidate(FALSE);
		Paint2dview();
	}
}

void CMAPDlg::OnClickedBDelallBases(void)
{
	if (pigcmap == NULL) return;
	if (AfxMessageBox(_T("Really delete all bases in all sectors ?"),MB_YESNO|MB_DEFBUTTON2) == IDYES)
	{
		pigcmap->cl_bases.RemoveAll();
		LoadSectors();
		Invalidate(FALSE);
		Paint2dview();
	}
}

void CMAPDlg::OnClickedBDelallRocks(void)
{
	if (pigcmap == NULL) return;
	if (AfxMessageBox(_T("Really delete all rocks in all sectors ?"),MB_YESNO|MB_DEFBUTTON2) == IDYES)
	{
		pigcmap->cl_rocks.RemoveAll();
		LoadSectors();
		Invalidate(FALSE);
		Paint2dview();
	}
}

void CMAPDlg::OnOK(void)
{
	// trap return
	//CDialog::OnOK();
}
void CMAPDlg::OnCancel(void)
{
	// trap escape
	//CDialog::OnCancel();
}

void CMAPDlg::OnClickedBRdallAlephs(void)
{
	if (pigcmap == NULL) return;
	if (pigcmap->cl_alephs.GetCount() == 0) return;
	CRandomDlg dlgrand;
	dlgrand.ra_p1 = ra_p1;
	dlgrand.ra_p2 = ra_p2;
	dlgrand.ra_p3 = ra_p3;
	dlgrand.ra_p4 = ra_p4;
	dlgrand.ra_p5 = ra_p5;
	dlgrand.ra_b19 = ra_b19;
	dlgrand.ra_b42 = ra_b42;
	
	if (dlgrand.DoModal() == IDOK)
	{
		ra_p1 = dlgrand.ra_p1;
		ra_p2 = dlgrand.ra_p2;
		ra_p3 = dlgrand.ra_p3;
		ra_p4 = dlgrand.ra_p4;
		ra_p5 = dlgrand.ra_p5;
		ra_b19 = dlgrand.ra_b19;
		ra_b42 = dlgrand.ra_b42;
		//pigcmap->RandomizeAlephs();
		UpdateData(TRUE);
		POSITION pos = pigcmap->cl_sectors.GetHeadPosition();
		for (int i=0;i < pigcmap->cl_sectors.GetCount();i++)
		{
			PtrSector psect =  &(pigcmap->cl_sectors.GetNext(pos));
			psect->RandomizeAlephs(&(pigcmap->cl_alephs),ra_p1,ra_p2,ra_p3,ra_p4,ra_p5,ra_b19,ra_b42);
		}

		LoadSectors();
		Invalidate(FALSE);
		Paint2dview();
	}
}

void CMAPDlg::OnClickedBRdallRocks(void)
{
	if (pigcmap == NULL) return;
	if (pigcmap->cl_rocks.GetCount() == 0) return;
	if (AfxMessageBox(_T("Really randomize all rocks ?"),MB_YESNO|MB_DEFBUTTON2) == IDYES)
	{
		POSITION pos = pigcmap->cl_rocks.GetHeadPosition();
		for (int i=0;i < pigcmap->cl_rocks.GetCount();i++)
		{
			PtrRock prock = &(pigcmap->cl_rocks.GetNext(pos));
			prock->RandomPosition();
			prock->RandomOrientation();
			prock->RandomSpin();
		}
		LoadSectors();
		Invalidate(FALSE);
		Paint2dview();
	}
}
void CMAPDlg::OnClickedGrid(void)
{
	CButton *cbp = (CButton *)CWnd::GetDlgItem(IDC_MAP_GRID);

	map2d.SetGrid((cbp->GetCheck()==BST_CHECKED)?true:false);
}
void CMAPDlg::OnClickedSnap(void)
{
	CButton *cbp = (CButton *)CWnd::GetDlgItem(IDC_MAP_SNAP);

	map2d.SetSnap((cbp->GetCheck()==BST_CHECKED)?true:false);
}


void CMAPDlg::OnClickedBTemplates(void)
{
	// TODO: displat menu
	CRect rect;
	CButton *cbp = (CButton *)CWnd::GetDlgItem(IDC_B_TEMPLATES);
	cbp->GetWindowRect(&rect);
	tplmenu.TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, rect.left, rect.top, this);
}
afx_msg void CMAPDlg::OnSelTemplates( UINT nID )
{
	switch(nID)
	{
	case IDM_TPL_ALEPHS: {
		CAlephDlg adlg;
		CIGCAleph tmpaleph;
		tmpaleph.CloneFrom(&tplaleph);
		adlg.curaleph = &tmpaleph;
		adlg.bTplMode = true;
		adlg.sArtPath = cArtPathClient;
		bool bCont = true;
		while (bCont)
		{
			switch(int iRes = adlg.DoModal())
			{
			case IDOK:
				tplaleph.CloneFrom(&tmpaleph);
				bCont = false;
				break;
			case IDAPPLYTOSECT:
				if (cursect == NULL) break; 
			case IDAPPLYTOALL:
				{
					if (!pigcmap) break;
					bool bRender = false;
					POSITION pos;
					switch (AfxMessageBox("Apply render too ?",MB_YESNOCANCEL))
					{
					case IDYES: bRender = true;
					case IDNO:
						pos = pigcmap->cl_alephs.GetHeadPosition();
						for (int i=0;i < pigcmap->cl_alephs.GetCount();i++)
						{
							PtrAleph paleph = &(pigcmap->cl_alephs.GetNext(pos));
							if (iRes == IDAPPLYTOSECT)
							{
								if (paleph->igcaleph.sector_uid == cursect->igcsector.uid)
									paleph->ApplyTemplate(&tmpaleph,bRender);
							}
							else
								paleph->ApplyTemplate(&tmpaleph,bRender);
						}
						break; // switch
					case IDCANCEL: break;
					}
				} break;
			case IDCANCEL:
				bCont = false;
				break;
			}
		}
		}break;
	case IDM_TPL_SECTORS:{
		CSectDlg sdlg;
		sdlg.sArtPath = cArtPathClient;
		CIGCSector tmpsector;
		tmpsector.igcsector = tplsector.igcsector;
		sdlg.cursect = &tmpsector;
		sdlg.bTplMode = true;
		bool bCont = true;
		while (bCont)
		{
			switch(sdlg.DoModal())
			{
			case S_OK:
				tplsector.igcsector = tmpsector.igcsector;
				bCont = false;
				break;
			case S_SECTOR_CANCEL:
				bCont = false;
				break;
			case S_SECTOR_DELETE: // == Apply to all
				// confirm
				// apply to all sectors
				// loop back
				if (!pigcmap) break;
				bool bCol = false;POSITION pos;
				switch (AfxMessageBox("Apply colors too ?",MB_YESNOCANCEL))
				{
				case IDYES: bCol = true;
				case IDNO:
					pos = pigcmap->cl_sectors.GetHeadPosition();
					for (int i=0;i < pigcmap->cl_sectors.GetCount();i++)
					{
						PtrSector psec = &(pigcmap->cl_sectors.GetNext(pos));
						psec->ApplyTemplate(&tmpsector,bCol);
					}
				case IDCANCEL: break;
				}
				break;
			}
		}
		}break;
	case IDM_TPL_ROCKS:{
		CRockTplDlg rdlg;
		rdlg.rocktpl = tplrock;
		bool bCont = true;
		CString s = "";
		while (bCont)
		{
			switch(int iRes = rdlg.DoModal())
			{
			case IDOK:
				tplrock = rdlg.rocktpl;
				bCont = false;
				break;
			case IDAPPLYTOSECT:
				if (cursect == NULL) break;
				s.Format("Apply to all rocks in %s ?",cursect->igcsector.name);
			case IDAPPLYTOALL:
				{
					if (!pigcmap) break;
					if (s == "")
						s = "Apply to all rocks in all sectors ?";
					POSITION pos;
					switch (AfxMessageBox(s,MB_YESNO))
					{
					case IDYES: 
						pos = pigcmap->cl_rocks.GetHeadPosition();
						for (int i=0;i < pigcmap->cl_rocks.GetCount();i++)
						{
							PtrRock prock = &(pigcmap->cl_rocks.GetNext(pos));
							if (iRes == IDAPPLYTOSECT)
							{
								if (prock->igcrock.sector_uid == cursect->igcsector.uid)
									prock->ApplyTemplate(&rdlg.rocktpl);
							}
							else
								prock->ApplyTemplate(&rdlg.rocktpl);
						}
						break; // switch
					case IDNO: break;
					}
				} break;
			case IDCANCEL:
				bCont = false;
				break;
			}
		}
		} break;
	}
}
void CMAPDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	AfxMessageBox("MAPDlg: KEY!!!");

	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMAPDlg::OnBnClickedCkzview()
{
	UpdateData(TRUE);
	LoadSectors();
	Invalidate(FALSE);
	Paint2dview();
}

void CMAPDlg::OnBnClickedBRenameSectors()
{
	if (pigcmap == NULL) return;
	if (pigcmap->cl_sectors.GetCount() == 0) return;
	CFileDialog cfd(TRUE,"txt",NULL,OFN_FILEMUSTEXIST|OFN_NOCHANGEDIR|OFN_NONETWORKBUTTON,"Text file|*.txt|",this,OPENFILENAME_SIZE_VERSION_400);
	if (cfd.DoModal() == IDOK)
	{
		switch (pigcmap->RenameSectors(cfd.GetPathName()))
		{
			case 1:
				AfxMessageBox("Error: can not read database file");
				break;
			case 2:
				AfxMessageBox("Error: too few names in database file");
				break;
			case 0:
				LoadSectors();
				Paint2dview();
		}
	}
}

void CMAPDlg::OnBnClickedCoreload()
{
	OnClickedMapNew();
	CString startpath = cArtPath + "\\*.igc";
	CFileDialog cfd(TRUE,"igc",startpath,OFN_FILEMUSTEXIST|OFN_NOCHANGEDIR|OFN_NONETWORKBUTTON,"Allegiance Core|*.igc|",this,OPENFILENAME_SIZE_VERSION_400);

	if (cfd.DoModal() == IDOK)
	{
		PtrCore pc = new CIGCCore();
		if (pc->ReadFromFile(cfd.GetPathName()))
		{
			if (pcore) 
				delete pcore;
			pcore = pc;
			sCorename = cfd.GetFileName();
			UpdateData(FALSE);
			// save in registry
			HKEY hKey;
			LONG regres = RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Microsoft Games\\Allegiance\\1.0",0, KEY_WRITE, &hKey);
			if (regres == ERROR_SUCCESS)
			{
				char *lpsz = new char[sCorename.GetLength()+1];
				strcpy(lpsz, sCorename);

				RegSetValueEx(
					hKey,      // handle to key
					"AMECore", // value name
					NULL,      // reserved
					REG_SZ,    // value type
					(BYTE *)lpsz, // value data
					sCorename.GetLength());  // size of value data
				delete lpsz;
			}
		}
		else
		{
			delete pc;
			AfxMessageBox(cfd.GetFileName() + " is not a valide core");
		}
	}
}

void CMAPDlg::OnBnClickedAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}
