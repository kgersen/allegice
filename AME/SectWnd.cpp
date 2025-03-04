// SectWnd.cpp : implementation file
//

#include "stdafx.h"
#include "AGM.h"
#include "IGCMap.h"
#include "2DMap.h"
#include "MAPDlg.h"
#include "GetNumDlg.h"
#include "RocksLayoutDlg.h"
#include "SectWnd.h"
#include "RandomDlg.h"

// CSectWnd

IMPLEMENT_DYNAMIC(CSectWnd, CWnd)
CSectWnd::CSectWnd()
{
	dragobject = NULL;
	menuobject = NULL;
	cursect = NULL;
	cl_pbases.RemoveAll();
	cl_palephs.RemoveAll();
	cl_procks.RemoveAll();
	grid_on = true;
	ClipBoard = NULL;
	bMakingAleph = false;

	CString s;
	alephmenu.CreatePopupMenu(); //should check
	basemenu.CreatePopupMenu(); //should check
	rockmenu.CreatePopupMenu(); //should check
	s.LoadString(IDS_PROPERTIES);
	alephmenu.AppendMenu(MF_STRING,IDM_PROPS,s);  
	basemenu.AppendMenu(MF_STRING,IDM_PROPS,s);
	rockmenu.AppendMenu(MF_STRING,IDM_PROPS,s);
	alephmenu.AppendMenu(MF_STRING,IDM_JUMP,"Warp in");
	s.LoadString(IDS_COPY);
	basemenu.AppendMenu(MF_STRING,IDM_COPYOBJECT,s);
	rockmenu.AppendMenu(MF_STRING,IDM_COPYOBJECT,s);
	s.LoadString(IDS_DELETE);
	alephmenu.AppendMenu(MF_STRING,IDM_DEL,s);
	basemenu.AppendMenu(MF_STRING,IDM_DEL,s);
	rockmenu.AppendMenu(MF_STRING,IDM_DEL,s);

	rmenu_rocks.CreatePopupMenu();
	rmenu_rocks.AppendMenu(MF_STRING,IDM_ADDROCK_ASTERIOD,"Asteriod");
	rmenu_rocks.AppendMenu(MF_STRING,IDM_ADDROCK_ASTERIODS,"Asteriods Layout");
	//rmenu_rocks.AppendMenu(MF_STRING,IDM_ADDROCKSLAYOUT,"Asteriods Layout");
	rmenu_rocks.AppendMenu(MF_STRING,IDM_ADDROCK_HELIUM,"Helium");
	rmenu_rocks.AppendMenu(MF_STRING,IDM_ADDROCK_URANIUM,"Uranium");
	rmenu_rocks.AppendMenu(MF_STRING,IDM_ADDROCK_SILICON,"Silicon");
	rmenu_rocks.AppendMenu(MF_STRING,IDM_ADDROCK_CARBON,"Carbon");
	rmenu_rocks.AppendMenu(MF_STRING,IDM_ADDROCK_THORIUM,"Thorium");

	rmenu.CreatePopupMenu(); // should check
	s.LoadString(IDS_ADDROCK); 
	//rmenu.AppendMenu(MF_STRING,IDM_ADDROCK,s);
	rmenu.AppendMenu(MF_POPUP,(UINT_PTR)rmenu_rocks.m_hMenu,s);
	s.LoadString(IDS_ADDBASE);
	rmenu.AppendMenu(MF_STRING,IDM_ADDBASE,s);
	rmenu.AppendMenu(MF_SEPARATOR);
	rmenu.AppendMenu(MF_STRING,IDM_PASTEOBJECT,"Paste"); 
	rmenu.AppendMenu(MF_SEPARATOR);
	rmenu.AppendMenu(MF_STRING,IDM_RANDOMIZE_ALEPHS,"Randomize alephs"); 
	rmenu.AppendMenu(MF_STRING,IDM_RANDOMIZE_ROCKS,"Randomize rocks"); 
	rmenu.AppendMenu(MF_SEPARATOR);
	rmenu.AppendMenu(MF_STRING,IDM_DELBASES,"Delete all bases");
	rmenu.AppendMenu(MF_STRING,IDM_DELROCKS,"Delete all rocks");
	rmenu.AppendMenu(MF_SEPARATOR);
	s.LoadString(IDS_PROPERTIES);
	rmenu.AppendMenu(MF_STRING,IDM_SECTPROPS,s);

	fontsm.CreateFont(
		14,                         // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"Arial");                 // lpszFacename
}

CSectWnd::~CSectWnd()
{
	alephmenu.DestroyMenu();
	basemenu.DestroyMenu();
	rockmenu.DestroyMenu();
	rmenu.DestroyMenu();
	rmenu_rocks.DestroyMenu();
	fontsm.DeleteObject();
}
CMenu *CSectWnd::ObjectMenu(PtrObject pobj)
{
	switch (pobj->GetType())
	{
		case igcAleph: return &alephmenu;
		case igcBase: return &basemenu;
		case igcRock: return &rockmenu;
		default:
			AfxMessageBox(_T("INTERNAL ERROR: NO MATCHING MENU"));
	}
	return NULL; //not reachable
}

BEGIN_MESSAGE_MAP(CSectWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND_RANGE(IDM_ADDBASE, IDM_ADDROCKSLAYOUT, OnRMenu)
	//ON_WM_MENUSELECT()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

#define MAP2DHALF (MAP2DSIZE/2.0f)


#define IGCCOORD2MAPX(x) (MAP2DHALF+(x)*MAP2DHALF/IGCMAX) //
#define IGCCOORD2MAPY(y) (MAP2DHALF+(-y)*MAP2DHALF/IGCMAX) //

#define IGCCOORD2UNMAPX(x) (((x) - MAP2DHALF)*IGCMAX/MAP2DHALF)
#define IGCCOORD2UNMAPY(y) ((MAP2DHALF - (y))*IGCMAX/MAP2DHALF)
#define IGCCOORDUNMAPZ(z) ((z)*IGCMAX/MAP2DSIZE)

void CSectWnd::DrawGrid(CPaintDC *pDC)
{
	if (grid_on)
	{
		int stepgrid = IGCCOORD2MAPX(RMAPSGRID)-MAP2DHALF;
		CBrush black;
		black.CreateSolidBrush(RGB(0,0,0));
		CPen pengridthin(PS_SOLID,1,RGB(0x55,0x55,0x55));
		CPen pengridthick(PS_SOLID,2,RGB(0x55,0x55,0x55));
		/*
		for (int i=-5*4;i<=5*4;i++)
		{
			if (i%5 != 0)
				pDC->SelectObject(&pengridthin);
			else
				pDC->SelectObject(&pengridthick);

			pDC->MoveTo(i*stepgrid+MAP2DHALF,0);
			pDC->LineTo(i*stepgrid+MAP2DHALF,MAP2DSIZE);
			pDC->MoveTo(0,i*stepgrid+MAP2DHALF);
			pDC->LineTo(MAP2DSIZE,i*stepgrid+MAP2DHALF);
		}
		*/
		CBrush *oldbrush = (CBrush *)pDC->SelectObject(&black);
		CPen *oldpen = pDC->SelectObject(&pengridthick);
		pDC->Ellipse(MAP2DHALF-5*4*stepgrid,MAP2DHALF-5*4*stepgrid,MAP2DHALF+5*4*stepgrid,MAP2DHALF+5*4*stepgrid);

		pDC->MoveTo(MAP2DHALF,0);
		pDC->LineTo(MAP2DHALF,MAP2DSIZE);
		pDC->MoveTo(0,MAP2DHALF);
		pDC->LineTo(MAP2DSIZE,MAP2DHALF);
		
		pDC->SelectObject(oldbrush);
		pDC->SelectObject(oldpen);
	}
}
void CSectWnd::OnPaint(void)
{
	// Do not call CWnd::OnPaint() for painting messages
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	CRect rect;
	CBrush brwhite(RGB(0xFF,0xFF,0xFF));
	CBrush brred(RGB(0xFF,0,0));
	CBrush brback(RGB(0,0,0));

	GetClientRect(rect);

	dc.SetTextColor(RGB(0xFF,0xFF,0xFF));
	dc.SetBkColor(RGB(0,0,0));

	dc.FillRect(rect, &brback);
	dc.FrameRect(rect, &brred);
	if (cursect)
	{
		CFont *oldfont;
		CPen *oldpen;
		CPen penaleph(PS_SOLID,2,RGB(0x00,0x00,0xFF));
        CPen penbase(PS_SOLID,1,RGB(0xFF,0xFF,0xFF));
		CBrush brushTeam1,brushTeam2,brushTeam3,brushTeam4,brushTeam5,brushTeam6;
		brushTeam1.CreateSolidBrush(IGCTEAM1COL);
		brushTeam2.CreateSolidBrush(IGCTEAM2COL);
		brushTeam3.CreateSolidBrush(IGCTEAM3COL);
		brushTeam4.CreateSolidBrush(IGCTEAM4COL);
		brushTeam5.CreateSolidBrush(IGCTEAM5COL);
		brushTeam6.CreateSolidBrush(IGCTEAM6COL);
		CBrush * brushbases[6] = {&brushTeam1,&brushTeam2,&brushTeam3,&brushTeam4,&brushTeam5,&brushTeam6};

		CPen penrock_other(PS_SOLID,2,RGB(0xFF,0x00,0xFF));
		CPen penrock_a(PS_SOLID,2,RGB(0xAA,0xAA,0xAA));
		CPen penrock_he(PS_SOLID,2,RGB(0xFF,0xFF,0xFF));
		CPen penrock_u(PS_SOLID,2,RGB(0xFF,0xFF,0x33));
		CPen penrock_si(PS_SOLID,2,RGB(0x00,0xFF,0x00));
		CPen penrock_c(PS_SOLID,2,RGB(0x44,0x44,0xFF));
		CPen penrock_t(PS_SOLID,2,RGB(0x44,0xFF,0xFF));

		CBrush whitebrush;
		whitebrush.CreateSolidBrush(RGB(0xFF,0xFF,0xFF));
		CBrush redbrush;
		redbrush.CreateSolidBrush(RGB(0xFF,0x00,0x00));
		CBrush *oldbrush = NULL;
		CBrush blackbrush;
		blackbrush.CreateSolidBrush(RGB(0x00,0x00,0x00));
	
		oldbrush = (CBrush *)dc.SelectObject(&whitebrush);
		oldpen = dc.SelectObject(&penaleph);
		oldfont = dc.SelectObject(&fontsm);

		DrawGrid(&dc);
		
		dc.SelectObject(&whitebrush);
		dc.SelectObject(&penaleph);
		POSITION pos = cl_palephs.GetHeadPosition();
		for (int i=0;i < cl_palephs.GetCount();i++)
		{
			PtrAleph paleph;
			paleph = cl_palephs.GetNext(pos);
			int x,y;
			x = paleph->pos2D.x;
			y = paleph->pos2D.y;
			//dc.Rectangle(x,y,x+1,y+1);
			// KG - 8/6/08 - paint differenly fixed position alephs
			if (paleph->bFixedPosition)
				dc.SelectObject(&blackbrush);
			else
				dc.SelectObject(&whitebrush);
			dc.Ellipse(x-SDOTSECT/2,y-SDOTSECT/2,x+SDOTSECT/2,y+SDOTSECT/2);
			CString cs;
			cs = paleph->igcaleph.DestinationSectorName;
			if (bShowZ)
				cs.AppendFormat("(%d)",(int)(paleph->igcaleph.posz));
			dc.SetBkMode(TRANSPARENT);
			dc.TextOut(x+6,y+6,cs);
			dc.SetBkMode(OPAQUE);
			
		}

		dc.SelectObject(&whitebrush);
		dc.SelectObject(&penbase);
		pos = cl_pbases.GetHeadPosition();
		for (int i=0;i < cl_pbases.GetCount();i++)
		{
			PtrBase pbase = cl_pbases.GetNext(pos);
			ASSERT(pbase != NULL);
			int x,y;
			x = pbase->pos2D.x;
			y = pbase->pos2D.y;
			dc.SelectObject(brushbases[pbase->igcbase.team]);
			// dc.Rectangle(x,y,x+1,y+1);
			dc.Ellipse(x-SDOTBASE/2,y-SDOTBASE/2,x+SDOTBASE/2,y+SDOTBASE/2);
			CString cs;
			cs = pbase->igcbase.name;
			if (bShowZ)
				cs.AppendFormat("(%d)",(int)(pbase->igcbase.posz));

			dc.SetBkMode(TRANSPARENT);
			dc.TextOut(x+6,y+6,cs);
			dc.SetBkMode(OPAQUE);
		}

		dc.SelectObject(&redbrush);
		pos = cl_procks.GetHeadPosition();
		for (int i=0;i < cl_procks.GetCount();i++)
		{
			PtrRock prock = cl_procks.GetNext(pos);
			ASSERT(prock != NULL);
			int x,y;
			x = prock->pos2D.x;
			y = prock->pos2D.y;
			//dc.Rectangle(x,y,x+1,y+1);
			switch (prock->igcrock.flags)
			{
				case 1: dc.SelectObject(&penrock_he); break;
				case 4: dc.SelectObject(&penrock_t); break;
				case 8: dc.SelectObject(&penrock_a); break;
				case 16: dc.SelectObject(&penrock_u); break;
				case 32: dc.SelectObject(&penrock_si); break;
				case 64: dc.SelectObject(&penrock_c); break;
				default: dc.SelectObject(&penrock_other); break;
			}
			dc.Ellipse(x-SDOTSECT/2,y-SDOTSECT/2,x+SDOTSECT/2,y+SDOTSECT/2);
			if (prock->igcrock.name[0] != 0)
			{
				CString cs;
				cs = prock->igcrock.name;
				dc.SetBkMode(TRANSPARENT);
				dc.TextOut(x+6,y+6,cs);
				dc.SetBkMode(OPAQUE);
			}
		}

		dc.TextOut(1,1,cursect->igcsector.name);
		CString sinfos;
		if (cl_procks.GetCount() == 0)
			sinfos.Format("He3 and resources from '%s' settings",cursect->igcsector.team?"home":"neutral");
		else
			sinfos.Format("%d He3 (%g/%g) - %d asteriods - %d U - %d Si - %d C",
				sectinfo.nbHelium,sectinfo.he3,sectinfo.he3max,
				sectinfo.nbAsteriod,sectinfo.nbUranium,sectinfo.nbSilicon,sectinfo.nbUranium);
		dc.SetTextColor(RGB(0x00,0x00,0xFF));
		dc.TextOut(1,16,sinfos);
		if ((dragobject != NULL) && (bSettingZ))
		{
			CString cs;
			//CPoint ps = dragobject->GetPos2D();
			cs.Format("Z coord = %f",dragobject->GetZ()+dragZ);
			dc.SetTextColor(RGB(0xFF,0x00,0x00));
			dc.SetBkColor(RGB(0xFF,0xFF,0xFF));
			CPoint p = dragobject->GetPos2D();
			dc.TextOut(p.x,p.y+24,cs);
		}
		if ((dragobject != NULL) && (!bSettingZ))
		{
			CString cs;
			//CPoint ps = dragobject->GetPos2D();
			CPoint p = dragobject->GetPos2D();
			cs.Format("3D distance to center: %d",
				dragobject->DistanceToCenter(IGCCOORD2UNMAPX(p.x),IGCCOORD2UNMAPY(p.y)));
			dc.SetTextColor(RGB(0xFF,0x00,0x00));
			dc.SetBkColor(RGB(0xFF,0xFF,0xFF));
			dc.TextOut(p.x,p.y+24,cs);
		}
		if (bMakingAleph)
		{
			CString cs;
			CPen createalephpenvalid(PS_SOLID,2,RGB(0x00,0xFF,0x00)); //green
			oldpen = dc.SelectObject(&createalephpenvalid);
			dc.MoveTo(AlephX,AlephY);
			dc.LineTo(AlephDestX,AlephDestY);
			cs = "Create inner aleph (right button to cancel)";
			dc.TextOut(AlephDestX,AlephDestY+24,cs);
		}

		dc.SelectObject(oldpen);
		dc.SelectObject(oldbrush);
		dc.SelectObject(oldfont);
	}
}
// ---------------------------- MOUSE HANDLING ---------------------------
CIGCObject *CSectWnd::IsOverObject(CPoint point)
{
	CSize sdot(SDOTSECT,SDOTSECT);
	POSITION pos = cl_palephs.GetHeadPosition();
	for (int i=0;i < cl_palephs.GetCount();i++)
	{
		CIGCAleph *paleph = cl_palephs.GetNext(pos);
		CPoint cp = paleph->pos2D;
		cp.Offset(-SDOTSECT/2,-SDOTSECT/2);
		CRect rect(cp,sdot);

		//if ((point.x == psector->pos2D.x) && (point.y == psector->pos2D.y))
		if (rect.PtInRect(point))
		{
			return (CIGCObject *)paleph;
		}
	}
	CSize bdot(SDOTBASE,SDOTBASE);
	pos = cl_pbases.GetHeadPosition();
	for (int i=0;i < cl_pbases.GetCount();i++)
	{
		CIGCBase *pbase = cl_pbases.GetNext(pos);
		CPoint cp = pbase->pos2D;
		cp.Offset(-SDOTBASE/2,-SDOTBASE/2);
		CRect rect(cp,bdot);

		//if ((point.x == psector->pos2D.x) && (point.y == psector->pos2D.y))
		if (rect.PtInRect(point))
		{
			return (CIGCObject *)pbase;
		}
	}

	pos = cl_procks.GetHeadPosition();
	for (int i=0;i < cl_procks.GetCount();i++)
	{
		CIGCRock *prock = cl_procks.GetNext(pos);
		CPoint cp = prock->pos2D;
		cp.Offset(-SDOTSECT/2,-SDOTSECT/2);
		CRect rect(cp,sdot);

		//if ((point.x == psector->pos2D.x) && (point.y == psector->pos2D.y))
		if (rect.PtInRect(point))
		{
			return (CIGCObject *)prock;
		}
	}
	return NULL;
}

void CSectWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	// 
	//CString mes;
	//mes.Format("HIT: %d , %d",point.x,point.y);
	//AfxMessageBox(_T(mes));
	ObjProps(IsOverObject(point));
}
void CSectWnd::ObjProps(PtrObject pobj)
{
	if (pobj)
	{
		switch (pobj->DispProps((CWnd *)this,cigcmap->pcore,cArtPath))
		{
		case IDOK:
			ChangeSector(cursect); // recompute 2D coords
			Invalidate(TRUE);
			UpdateWindow(); // 
			break;
		case IDDELETE:
			ObjDelete(pobj);
			break;
		default:
			break;
		}
	}
}
void CSectWnd::ObjDelete(PtrObject pobj)
{
	CMAPDlg *pdlg = (CMAPDlg *)GetParent();
	POSITION pos;
	switch (pobj->GetType())
	{
	case igcAleph:
		pdlg->map2d.DeleteAleph((PtrAleph)pobj);
		pdlg->LoadSectors();
		pdlg->Invalidate(FALSE);
		pdlg->Paint2dview();
		AllUpdate();
		break;
	case igcBase:
		pos = cigcmap->cl_bases.Find(*((PtrBase)pobj));
		cigcmap->cl_bases.RemoveAt(pos);
		pdlg->LoadSectors();
		pdlg->Invalidate(FALSE);
		pdlg->Paint2dview();
		AllUpdate();
		break;
	case igcRock:
		pos = cigcmap->cl_rocks.Find(*((PtrRock)pobj));
		cigcmap->cl_rocks.RemoveAt(pos);
		pdlg->LoadSectors();
		pdlg->Invalidate(FALSE);
		pdlg->Paint2dview();
		AllUpdate();
		break;
	default: // doah!
		break;
	}
}
void CSectWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (dragobject=IsOverObject(point))
	{
		if (nFlags & MK_CONTROL)
		{
			bSettingZ = true;
			dragpoint.y = point.y;
			dragZ = 0.0;
		}
		else
		{
			bSettingZ = false;
			dragpoint.x = point.x - dragobject->GetPos2D().x;
			dragpoint.y = point.y - dragobject->GetPos2D().y;
		}
		SetCapture();
	}
	else if (nFlags & MK_SHIFT)
	{
		dragpoint = point;
		OnRMenu(IDM_PASTEOBJECT);
	}
	// make self aleph
	if (cursect && !bSettingZ && !dragobject)
	{
		bMakingAleph = true;
		AlephX = point.x;
		AlephY = point.y;
		AlephDestX = point.x;
		AlephDestY = point.y;
		SetCapture();
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void CSectWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	// set point to real coords (with UNMAP macros)
	if (dragobject)
	{
		if (bSettingZ)
		{
			dragobject->SetZ(dragobject->GetZ()+dragZ);
			dragZ = 0.0;
		}
		else
		{
			// check in map
			CPoint savep;
			savep.x = point.x-dragpoint.x;
			savep.y = point.y-dragpoint.y;
			if (savep.x < 0) savep.x = 20;
			if (savep.y < 0) savep.y = 20;
			if (savep.x > MAP2DSIZE) savep.x = MAP2DSIZE-20;
			if (savep.y > MAP2DSIZE) savep.y = MAP2DSIZE-20;
			// save to real coords
			dragobject->ApplyPos3D(IGCCOORD2UNMAPX(savep.x),IGCCOORD2UNMAPY(savep.y),dragobject->GetZ());
		}
	}
	dragobject = NULL;
	bSettingZ = false;
	if (bMakingAleph)
	{
		bMakingAleph=false;
		CPoint savep;
		savep.x = point.x;
		savep.y = point.y;
		if (savep.x < 0) savep.x = 20;
		if (savep.y < 0) savep.y = 20;
		if (savep.x > MAP2DSIZE) savep.x = MAP2DSIZE-20;
		if (savep.y > MAP2DSIZE) savep.y = MAP2DSIZE-20;
		float X = abs(savep.x-AlephX);
		float Y = abs(savep.y-AlephY);
		float norm = X*X + Y*Y;
		norm = sqrtf(norm);
		if (norm > 10.0)
		{
			CMAPDlg *cdlg = (CMAPDlg *) CWnd::GetParent();
			cdlg->CreateAleph(cursect,IGCCOORD2UNMAPX(AlephX),IGCCOORD2UNMAPY(AlephY),cursect,IGCCOORD2UNMAPX(savep.x),IGCCOORD2UNMAPY(savep.y));
		}
	}
	AllUpdate();
	CWnd::OnLButtonUp(nFlags, point);
}

void CSectWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (bMakingAleph)
	{
		bMakingAleph = false;
		AllUpdate();
		return;
	}
	if (dragobject) // cancel a left-click drag
	{
		dragobject = NULL;
		bSettingZ = false;
		AllUpdate();
		return;
	}
	if (!cursect) return;

	CRect rect;
	GetWindowRect(&rect);
	CMenu *omenu;
	PtrObject pobj = IsOverObject(point);
	if (pobj)
	{
		omenu = ObjectMenu(pobj);
		menuobject = pobj;
	}
	else
	{
		// ->display menu
		menuobject = NULL;
		omenu = &rmenu;
		dragpoint = point; // store the point if something is created
	}
	if ((nFlags & MK_SHIFT) && (pobj)) //Shit+RMB over an object = copy
		OnRMenu(IDM_COPYOBJECT);
	else if ((nFlags & MK_CONTROL) && (pobj))
		OnRMenu(IDM_DEL);
	else
		omenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, rect.left+point.x, rect.top+point.y, this);
}

void CSectWnd::OnRButtonUp(UINT nFlags, CPoint point)
{
	bMakingAleph=false;
	CWnd::OnRButtonUp(nFlags, point);
}

void CSectWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if (dragobject)
	{
		if (bSettingZ)
		{
			dragZ = IGCCOORDUNMAPZ((point.y-dragpoint.y));
		}
		else
		{
			CPoint p;
			p.x = point.x-dragpoint.x;
			p.y = point.y-dragpoint.y;

			dragobject->SetPos2D(p);
		}
		Invalidate(TRUE);
		UpdateWindow();
	}
	if (bMakingAleph)
	{
		AlephDestX = point.x;
		AlephDestY = point.y;
		Invalidate(TRUE);
		UpdateWindow();
	}
	CWnd::OnMouseMove(nFlags, point);
}





// CSectWnd utils

void CSectWnd::ChangeSector(CIGCSector * psector)
{
	sectinfo.he3 = 0;
	sectinfo.he3max = 0;
	sectinfo.nbAsteriod = 0;
	sectinfo.nbCarbon = 0;
	sectinfo.nbHelium = 0;
	sectinfo.nbSilicon = 0;
	sectinfo.nbUranium = 0;

	cl_pbases.RemoveAll();
	cl_palephs.RemoveAll();
	cl_procks.RemoveAll();
	cursect = psector;
	if (!psector) return;

	// retrieve the aleph in psector
	POSITION pos = cigcmap->cl_alephs.GetHeadPosition();
	for (int i=0;i < cigcmap->cl_alephs.GetCount();i++)
	{
		PtrAleph paleph;
		paleph = &(cigcmap->cl_alephs.GetNext(pos));
		if (paleph->igcaleph.sector_uid == psector->igcsector.uid)
		{
			paleph->pos2D.x = IGCCOORD2MAPX(paleph->igcaleph.posx);
			paleph->pos2D.y = IGCCOORD2MAPY(paleph->igcaleph.posy);
			cl_palephs.AddTail(paleph);
		}
    }

	// retrieve the bases in psector
	pos = cigcmap->cl_bases.GetHeadPosition();
	for (int i=0;i < cigcmap->cl_bases.GetCount();i++)
	{
		PtrBase pbase;
		pbase = &(cigcmap->cl_bases.GetNext(pos));
		if (pbase->igcbase.sector_uid == psector->igcsector.uid)
		{
			pbase->pos2D.x = IGCCOORD2MAPX(pbase->igcbase.posx);
			pbase->pos2D.y = IGCCOORD2MAPY(pbase->igcbase.posy);
			cl_pbases.AddTail(pbase);
		}
    }
	// retrieve the rocks in psector
	pos = cigcmap->cl_rocks.GetHeadPosition();
	for (int i=0;i < cigcmap->cl_rocks.GetCount();i++)
	{
		PtrRock prock;
		prock = &(cigcmap->cl_rocks.GetNext(pos));
		if (prock->igcrock.sector_uid == psector->igcsector.uid)
		{
			prock->pos2D.x = IGCCOORD2MAPX(prock->igcrock.posx);
			prock->pos2D.y = IGCCOORD2MAPY(prock->igcrock.posy);
			cl_procks.AddTail(prock);
			if (prock->igcrock.flags & IGCROCK_IS_ASTERIOD)
				sectinfo.nbAsteriod ++;
			if (prock->igcrock.flags & IGCROCK_IS_URANIUM)
				sectinfo.nbUranium ++;
			if (prock->igcrock.flags & IGCROCK_IS_SILICON)
				sectinfo.nbSilicon ++;
			if (prock->igcrock.flags & IGCROCK_IS_CARBON)
				sectinfo.nbCarbon ++;
			if (prock->igcrock.flags & IGCROCK_IS_HELIUM)
			{
				sectinfo.nbHelium ++;
				sectinfo.he3 += prock->igcrock.ore;
				sectinfo.he3max += prock->igcrock.oreMax;
			}

		}
    }

}
void CSectWnd::DeleteAllBases(void)
{
	POSITION pos = cl_pbases.GetHeadPosition();
	for (int i=0;i < cl_pbases.GetCount();i++)
	{
		PtrBase pbase = cl_pbases.GetNext(pos);
		POSITION posglo = cigcmap->cl_bases.Find(*pbase);
		cigcmap->cl_bases.RemoveAt(posglo);
	}
}
void CSectWnd::DeleteAllRocks(void)
{
	POSITION pos = cl_procks.GetHeadPosition();
	for (int i=0;i < cl_procks.GetCount();i++)
	{
		PtrRock prock = cl_procks.GetNext(pos);
		POSITION posglo = cigcmap->cl_rocks.Find(*prock);
		cigcmap->cl_rocks.RemoveAt(posglo);
	}
}

void CSectWnd::AllUpdate(void)
{
	ChangeSector(cursect); // recompute 2D coords
	Invalidate(TRUE);
	UpdateWindow(); //

}

afx_msg void CSectWnd::OnRMenu( UINT nID )
{
	int rocktpl = -1;

	switch (nID)
	{
		case IDM_PROPS:
			ObjProps(menuobject);
			break;
		case IDM_JUMP:{
			// Aleph, JUMPTO
			PtrAleph paleph = (PtrAleph)menuobject;
			CMAPDlg *pdlg = (CMAPDlg *)CWnd::GetParent();
			C2DMap *p2dmap = &pdlg->map2d;
			PtrAleph potheraleph = p2dmap->FindConnectingAleph(paleph);
			pdlg->SetSector(p2dmap->FindSector(potheraleph));
			// TODO: set the mouse of the connecting aleph
			//CRect rect;
			//GetWindowRect(&rect);
			//SetMouse?(rect.left+potheraleph->pos2D.x,rect.top+potheraleph->pos2D.y);
			}break;
		case IDM_COPYOBJECT:{
			if (ClipBoard)
			{
				delete ClipBoard;
				ClipBoard = NULL;
			}
			switch (menuobject->GetType())
			{
				case igcBase:{
					PtrBase pbase = new CIGCBase;
					PtrBase pclip = (PtrBase)menuobject;
					pbase->igcbase = pclip->igcbase;
					ClipBoard = pbase;
					}break;
				case igcRock:{
					PtrRock prock = new CIGCRock;
					PtrRock pclip = (PtrRock)menuobject;
					prock->igcrock = pclip->igcrock;
					ClipBoard = prock;
					}break;
			}
			}break;
		case IDM_DEL:
			if (AfxMessageBox(_T("Confirm delete ?"),MB_YESNO|MB_DEFBUTTON2) == IDYES)
				ObjDelete(menuobject);
			break;

		case IDM_PASTEOBJECT:{
			if (ClipBoard)
			{
				CMAPDlg *pdlg = (CMAPDlg *)GetParent();
				CPoint savep = dragpoint;
				if (savep.x < 0) savep.x = 20;
				if (savep.y < 0) savep.y = 20;
				if (savep.x > MAP2DSIZE) savep.x = MAP2DSIZE-20;
				if (savep.y > MAP2DSIZE) savep.y = MAP2DSIZE-20;
				switch (ClipBoard->GetType())
				{
					case igcBase:{
						PtrBase pbase = new CIGCBase;
						PtrBase pclip = (PtrBase)ClipBoard;
						pbase->igcbase = pclip->igcbase;
						pbase->igcbase.sector_uid = cursect->igcsector.uid;
						pdlg->last_base_uid += 1;
						pbase->igcbase.uid  = pdlg->last_base_uid;
						pbase->ApplyPos3D(IGCCOORD2UNMAPX(savep.x),IGCCOORD2UNMAPY(savep.y),pbase->GetZ());
						cigcmap->cl_bases.AddTail(*pbase);
						}break;
					case igcRock:{
						PtrRock prock = new CIGCRock;
						PtrRock pclip = (PtrRock)ClipBoard;
						prock->igcrock = pclip->igcrock;
						prock->igcrock.sector_uid = cursect->igcsector.uid;
						pdlg->last_rock_uid += 1;
						prock->igcrock.uid = pdlg->last_rock_uid;
						prock->SetAutoName(prock->igcrock.name[0]!=0);//keep the display name flag
						prock->ApplyPos3D(IGCCOORD2UNMAPX(savep.x),IGCCOORD2UNMAPY(savep.y),prock->GetZ());
						cigcmap->cl_rocks.AddTail(*prock);
						}break;
				}
				AllUpdate();
			}
			}break;
		case IDM_ADDBASE:{
			//BASE CREATE
			PtrBase pbase = new CIGCBase;
			CMAPDlg *pdlg = (CMAPDlg *)GetParent();

			// check in map
			CPoint savep = dragpoint;
			if (savep.x < 0) savep.x = 20;
			if (savep.y < 0) savep.y = 20;
			if (savep.x > MAP2DSIZE) savep.x = MAP2DSIZE-20;
			if (savep.y > MAP2DSIZE) savep.y = MAP2DSIZE-20;
			pbase->ApplyPos3D(IGCCOORD2UNMAPX(savep.x),IGCCOORD2UNMAPY(savep.y),pbase->GetZ());
			pbase->igcbase.posz = 0;
			strcpy(pbase->igcbase.name,"Garrison");
			pbase->igcbase.igcstationtype = 0x0F;
			pbase->igcbase.sector_uid = cursect->igcsector.uid;
			pbase->igcbase.team = 0; // should ask
			pdlg->last_base_uid += 1;
			pbase->igcbase.uid  = pdlg->last_base_uid;
			cigcmap->cl_bases.AddTail(*pbase);
			AllUpdate();
			}break;
		case IDM_ADDROCK_ASTERIOD: rocktpl = IGCROCK_TPL_ASTERIOD;				  //switch fallback
		case IDM_ADDROCK_HELIUM: if(rocktpl == -1) rocktpl = IGCROCK_TPL_HELIUM;  //switch fallback
		case IDM_ADDROCK_URANIUM: if(rocktpl == -1) rocktpl = IGCROCK_TPL_URANIUM;  //switch fallback
		case IDM_ADDROCK_SILICON: if(rocktpl == -1) rocktpl = IGCROCK_TPL_SILICON;  //switch fallback
		case IDM_ADDROCK_CARBON:  if(rocktpl == -1) rocktpl = IGCROCK_TPL_CARBON;  // switch fallback
		case IDM_ADDROCK_THORIUM:{ if(rocktpl == -1) rocktpl = IGCROCK_TPL_THORIUM;  // switch fallback
			// ROCK CREATE 
			CMAPDlg *pdlg = (CMAPDlg *)GetParent();
			pdlg->last_rock_uid += 1;
			PtrRock prock = new CIGCRock(rocktpl,pdlg->last_rock_uid,&(pdlg->tplrock));
			// check in map
			CPoint savep = dragpoint;
			if (savep.x < 0) savep.x = 20;
			if (savep.y < 0) savep.y = 20;
			if (savep.x > MAP2DSIZE) savep.x = MAP2DSIZE-20;
			if (savep.y > MAP2DSIZE) savep.y = MAP2DSIZE-20;
			prock->igcrock.posz = ((float)rand())*2000.0f/(float)RAND_MAX - 1000.0f;
			prock->ApplyPos3D(IGCCOORD2UNMAPX(savep.x),IGCCOORD2UNMAPY(savep.y),prock->GetZ());
			prock->igcrock.sector_uid = cursect->igcsector.uid;
			cigcmap->cl_rocks.AddTail(*prock);
			AllUpdate();
			}break;
		case IDM_ADDROCK_ASTERIODS:
			{
				CRocksLayoutDlg ldlg;
				ldlg.cx = IGCCOORD2UNMAPX(dragpoint.x);
				ldlg.cy = IGCCOORD2UNMAPY(dragpoint.y);
				if (ldlg.DoModal() != IDOK)
					break;
				rocktpl = IGCROCK_TPL_ASTERIOD;
				CMAPDlg *pdlg = (CMAPDlg *)GetParent();

				for (int i=0;i<ldlg.nbrocks;i++)
				{
					pdlg->last_rock_uid += 1;
					PtrRock prock = new CIGCRock(rocktpl,pdlg->last_rock_uid,&(pdlg->tplrock));
					prock->igcrock.sector_uid = cursect->igcsector.uid;

					float r     = (float)rand()*ldlg.radius/(float)RAND_MAX; // radius
					float alpha = (float)rand()*6.28f/(float)RAND_MAX;         // (angle) radians
					float rx = ldlg.cx + r * cosf(alpha); // coords
					float ry = ldlg.cy + r * sinf(alpha);
					r = ((float)rand())*ldlg.varz*2/(float)RAND_MAX;
					float rz = ldlg.cz+r-ldlg.varz;

					prock->ApplyPos3D(rx,ry,rz);
					prock->RandomOrientation();
					prock->RandomSpin();
					cigcmap->cl_rocks.AddTail(*prock);
				}
				AllUpdate();
			}break;
		case IDM_DELBASES:
			if (AfxMessageBox(_T("Really delete all bases in this sector ?"),MB_YESNO|MB_DEFBUTTON2) == IDYES)
			{
				DeleteAllBases();
				AllUpdate();
			}
			break;
		case IDM_DELROCKS:
			if (AfxMessageBox(_T("Really delete all rocks in this sector ?"),MB_YESNO|MB_DEFBUTTON2) == IDYES)
			{
				DeleteAllRocks();
				AllUpdate();
			}
			break;
		case IDM_SECTPROPS:
			{
				CMAPDlg *pdlg = (CMAPDlg *)CWnd::GetParent();
				pdlg->OnDblclkLbSectors();
			}break;
		case IDM_RANDOMIZE_ROCKS:
			if (cl_procks.GetCount() == 0) break;
			if (AfxMessageBox(_T("Really randomize all rocks in this sector ?"),MB_YESNO|MB_DEFBUTTON2) == IDYES)
			{
				POSITION pos = cl_procks.GetHeadPosition();
				for (int i=0;i < cl_procks.GetCount();i++)
				{
					PtrRock prock = cl_procks.GetNext(pos);
					prock->RandomPosition();
					prock->RandomOrientation();
					prock->RandomSpin();
				}
				AllUpdate();
			}break;
		case IDM_RANDOMIZE_ALEPHS:
			//if (AfxMessageBox(_T("Really randomize all alephs in this sector ?"),MB_YESNO|MB_DEFBUTTON2) == IDYES)
			{/*
				POSITION pos = cl_palephs.GetHeadPosition();
				for (int i=0;i < cl_palephs.GetCount();i++)
				{
					PtrAleph paleph =  cl_palephs.GetNext(pos);
					paleph->StdRandomPosition();
				}
			*/
			CMAPDlg *pdlg = (CMAPDlg *)CWnd::GetParent();
			CRandomDlg dlgrand;
			dlgrand.ra_p1 = pdlg->ra_p1;
			dlgrand.ra_p2 = pdlg->ra_p2;
			dlgrand.ra_p3 = pdlg->ra_p3;
			dlgrand.ra_p4 = pdlg->ra_p4;
			dlgrand.ra_p5 = pdlg->ra_p5;
			dlgrand.ra_b19 = pdlg->ra_b19;
			dlgrand.ra_b42 = pdlg->ra_b42;

			if (dlgrand.DoModal() == IDOK)
			{
				pdlg->ra_p1 = dlgrand.ra_p1;
				pdlg->ra_p2 = dlgrand.ra_p2;
				pdlg->ra_p3 = dlgrand.ra_p3;
				pdlg->ra_p4 = dlgrand.ra_p4;
				pdlg->ra_p5 = dlgrand.ra_p5;
				pdlg->ra_b19 = dlgrand.ra_b19;
				pdlg->ra_b42 = dlgrand.ra_b42;

				cursect->RandomizeAlephs(&(cigcmap->cl_alephs),dlgrand.ra_p1,dlgrand.ra_p2,dlgrand.ra_p3,dlgrand.ra_p4,dlgrand.ra_p5, dlgrand.ra_b19,dlgrand.ra_b42);
				AllUpdate();

			}
			}break;
	}
	menuobject = NULL;
}



void CSectWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	AfxMessageBox("KEY!!!");
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
