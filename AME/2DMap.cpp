// SectWnd.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>
#include "AGM.h"
#include "IGCMap.h"
#include "2DMap.h"
#include "MAPDlg.h"


// CSectWnd

IMPLEMENT_DYNAMIC(C2DMap, CWnd)
C2DMap::C2DMap()
{
	dragsector = NULL;
	createaleph = NULL;
	igccursect = NULL;
	bGrid = true;
	bSnap = true;
	sDispSectName = "";
}

C2DMap::~C2DMap()
{
}

BEGIN_MESSAGE_MAP(C2DMap, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// round to the closest integer
float C2DMap::Snap(float r)
{
	if (bSnap)
	{
		float f = r * 10.0f;
		if (fabs(f - floor(f))>0.5f)
			return (floor(f)+((f>=0.0f)?1.0f:-1.0f))/10.0f;
		else
			return floor(f)/10.0f;
	}
	else
		return r;
}
#define MAP2DWFB 20
#define MAP2DHFB 20
#define MAP2DSCALEX(x,scale) (MAP2DWFB + ((x) * (scale)))
#define MAP2DSCALEY(y,scale,h) ((h) - MAP2DHFB - ((y) * (scale)))

#define MAP2DUNSCALEX(x,scale) (Snap(((x) - MAP2DWFB)/(scale)))
#define MAP2DUNSCALEY(y,scale,h) (Snap(-(((y) - (h) + MAP2DHFB) /(scale))))

void C2DMap::OnPaint()
{
	CPaintDC dc(this);

	CRect rect;
	GetClientRect(rect);
	CBrush brwhite(RGB(0xFF,0xFF,0xFF));
	CBrush brred(RGB(0xFF,0,0));
	CBrush brback(RGB(0,0,0));

	// black gd, red frame
	dc.FillRect(rect, &brback);
	dc.FrameRect(rect, &brred);

	if (igcmap == NULL) return; // display help here ?

	dc.SetBkColor(RGB(0,0,0));
	CPen redpen(PS_SOLID,1,RGB(0xFF,0,0)); // red
	CPen whitepen(PS_SOLID,1,RGB(0xFF,0xFF,0xFF)); // white
	CPen alephpen(PS_SOLID,2,RGB(0x00,0x00,0xFF)); // blue
	CPen createalephpen(PS_SOLID,2,RGB(0xFF,0xFF,0x00)); //yellow
	CPen createalephpenvalid(PS_SOLID,2,RGB(0x00,0xFF,0x00)); //green
	CPen *oldpen = NULL;
	CBrush whitebrush;
	whitebrush.CreateSolidBrush(RGB(0xFF,0xFF,0xFF));
	CBrush redbrush;
	redbrush.CreateSolidBrush(RGB(0xFF,0x00,0x00));
	CBrush *oldbrush = NULL;
	
	oldpen = (CPen *)dc.SelectObject(&whitepen);
	oldbrush = (CBrush *)dc.SelectObject(&whitebrush);

	if (bGrid)
	{
		int cx = (maxx/10); // 0.1 step -> /10)
		int cy = (maxy/10);
		int x;
		for (x=MAP2DWFB;x<=MapW-MAP2DWFB;x+=cx)
		{
			dc.MoveTo(x,MAP2DHFB);
			dc.LineTo(x,MapH-MAP2DHFB);
		}
		int y;
		for (y=MapH-MAP2DHFB;y>=MAP2DHFB;y-=cy)
		{
			dc.MoveTo(MAP2DWFB,y);
			dc.LineTo(MapW-MAP2DWFB,y);
		}
		dc.SelectObject(&redpen);
		y = MAP2DSCALEY(1.5,maxy,MapH);
		x = MAP2DSCALEX(2.0,maxx);
		if (y >= 0)
		{
			dc.MoveTo(MAP2DWFB,MapH-MAP2DHFB);
			dc.LineTo(x,MapH-MAP2DHFB);
			dc.LineTo(x,y);
			dc.LineTo(MAP2DWFB,y);
			dc.LineTo(MAP2DWFB,MapH-MAP2DHFB);
		}
		
	}
	dc.SetTextColor(RGB(0xFF,0xFF,0xFF));
	dc.SetBkColor(RGB(0,0,0));

	if (sDispSectName != "")
	{
		dc.TextOut(1,1,sDispSectName);
	}
	// paint alephs
	dc.SelectObject(&alephpen);

	POSITION pos = mapalephs.GetHeadPosition();
	for (int i=0;i < mapalephs.GetCount();i++)
	{
		SMapAleph *mapa = &(mapalephs.GetNext(pos));
		dc.MoveTo(mapa->sect1->pos2D.x,mapa->sect1->pos2D.y);
		dc.LineTo(mapa->sect2->pos2D.x,mapa->sect2->pos2D.y);
	}

	CBrush brushTeam1,brushTeam2,brushTeam3,brushTeam4,brushTeam5,brushTeam6;
	brushTeam1.CreateSolidBrush(IGCTEAM1COL);
	brushTeam2.CreateSolidBrush(IGCTEAM2COL);
	brushTeam3.CreateSolidBrush(IGCTEAM3COL);
	brushTeam4.CreateSolidBrush(IGCTEAM4COL);
	brushTeam5.CreateSolidBrush(IGCTEAM5COL);
	brushTeam6.CreateSolidBrush(IGCTEAM6COL);
	CBrush * brushbases[7] = {&whitebrush,&brushTeam1,&brushTeam2,&brushTeam3,&brushTeam4,&brushTeam5,&brushTeam6};

	//paint sectors
	pos = igcmap->cl_sectors.GetHeadPosition();
	for (int i=0;i < igcmap->cl_sectors.GetCount();i++)
	{
		CIGCSector *psector;
		psector = &(igcmap->cl_sectors.GetNext(pos));
		int x = psector->pos2D.x;
		int y = psector->pos2D.y;
		if (psector == igccursect)
		{
			dc.SelectObject(&redpen);
			dc.SelectObject(&redbrush);
		}
		else
		{
			dc.SelectObject(&whitepen);
			dc.SelectObject(brushbases[psector->igcsector.team]);
		}

		//dc.RoundRect(x-SDOTSECT/2,y-SDOTSECT/2,x+SDOTSECT/2,y+SDOTSECT/2,SDOTSECT,SDOTSECT);
		dc.Ellipse(x-SDOTSECT/2,y-SDOTSECT/2,x+SDOTSECT/2,y+SDOTSECT/2);
	}
	if (createaleph)
	{
		PtrSector psectundermouse = IsOverSector(createalephTOpos2D);
		if (psectundermouse && (psectundermouse != createaleph))
            dc.SelectObject(&createalephpenvalid);
		else
            dc.SelectObject(&createalephpen);
		dc.MoveTo(createaleph->pos2D.x,createaleph->pos2D.y);
		dc.LineTo(createalephTOpos2D.x,createalephTOpos2D.y);
	}
	dc.SelectObject(oldpen);
	dc.SelectObject(oldbrush);
}
void C2DMap::Rescale()
{
	// compute scale (should use CDC mapping)
	if (!igcmap) return;
	maxx = 0.5;
	maxy = 0.5;
	POSITION pos = igcmap->cl_sectors.GetHeadPosition();
	for (int i=0;i < igcmap->cl_sectors.GetCount();i++)
	{
		CIGCSector *psector = &(igcmap->cl_sectors.GetNext(pos));
		if (psector->igcsector.posx > maxx)
			maxx = psector->igcsector.posx;
		if (psector->igcsector.posy > maxy)
			maxy = psector->igcsector.posy;
	}

	if (maxx>maxy)
		maxy = maxx;
	else
		maxx = maxy;
	maxc = maxx;
	maxx = (MapW-MAP2DWFB*2)/maxx;
	maxy = (MapH-MAP2DWFB*2)/maxy;
	//make it prop

	pos = igcmap->cl_sectors.GetHeadPosition();
	for (int i=0;i < igcmap->cl_sectors.GetCount();i++)
	{
		CIGCSector *psector = &(igcmap->cl_sectors.GetNext(pos));
		int x = MAP2DSCALEX(psector->igcsector.posx,maxx);
		int y = MAP2DSCALEY(psector->igcsector.posy,maxy,MapH);
		psector->pos2D.x = x;
		psector->pos2D.y = y;
	}
}
//---------------------------- MOUSE HANDLING -----------------------------------
// return sector under the point or null if no sector
CIGCSector *C2DMap::IsOverSector(CPoint point)
{
	if (igcmap == NULL) return NULL;
	CSize sdot(SDOTSECT,SDOTSECT);
	POSITION pos = igcmap->cl_sectors.GetHeadPosition();
	for (int i=0;i < igcmap->cl_sectors.GetCount();i++)
	{
		CIGCSector *psector;
		psector = &(igcmap->cl_sectors.GetNext(pos));
		// should test over dot  of size SDOTSECT centered
		CPoint cp = psector->pos2D;
		cp.Offset(-SDOTSECT/2,-SDOTSECT/2);
		CRect rect(cp,sdot);

		//if ((point.x == psector->pos2D.x) && (point.y == psector->pos2D.y))
		if (rect.PtInRect(point))
		{
			return psector;
		}
	}
	return NULL;
}


void C2DMap::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (IsOverSector(point))
	{
		CMAPDlg *pdlg = (CMAPDlg *)CWnd::GetParent();
		pdlg->OnDblclkLbSectors();
	}
	//CWnd::OnLButtonDblClk(nFlags, point);
}

void C2DMap::OnLButtonDown(UINT nFlags, CPoint point)
{
	//CString mes;
	//mes.Format("HIT AT %d,%d",point.x,point.y);
	//AfxMessageBox(_T(mes));
	if (createaleph) // cancel  creating an aleph
	{
		createaleph = NULL;
		Rescale();
		Invalidate(TRUE);
		UpdateWindow();
	}
	else
	{
		if (dragsector=IsOverSector(point))
		{
			CMAPDlg *pdlg = (CMAPDlg *)CWnd::GetParent();
			pdlg->SetSector(dragsector);
			dragpoint.x = point.x - dragsector->pos2D.x;
			dragpoint.y = point.y - dragsector->pos2D.y;
			dragorigin = dragsector->pos2D;
			SetCapture();
		}
	}
	CWnd::OnLButtonDown(nFlags, point);
}
void C2DMap::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	if (dragsector)
	{
		if (dragorigin != dragsector->pos2D)
		{
			dragsector->igcsector.posx = MAP2DUNSCALEX(dragsector->pos2D.x,maxx);
			dragsector->igcsector.posy = MAP2DUNSCALEY(dragsector->pos2D.y,maxy,MapH);
			// dont allow neg values for now
			if (dragsector->igcsector.posx <0.0)
				dragsector->igcsector.posx = 0.0;
			if (dragsector->igcsector.posy <0.0)
				dragsector->igcsector.posy = 0.0;
		}
		dragsector = NULL;
		Rescale();
		Invalidate(TRUE);
		UpdateWindow();
	}
	CWnd::OnLButtonUp(nFlags, point);
}

void C2DMap::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (dragsector) // cancel drag sector
	{
		dragsector = NULL;
		Rescale();
		Invalidate(TRUE);
		UpdateWindow();
	}
	else
	{ // start an aleph creation
		if (createaleph = IsOverSector(point))
		{
			createalephTOpos2D = point;
			SetCapture();
		}
	}
	CWnd::OnRButtonDown(nFlags, point);
}

void C2DMap::OnRButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	if (createaleph)
	{
		CIGCSector *destaleph = IsOverSector(point);
		if (destaleph) // mouse was released over a sector so create an aleph
		{
			if (destaleph != createaleph) // dont create to self :)
			{
				CMAPDlg *cdlg = (CMAPDlg *) CWnd::GetParent();
				cdlg->CreateAleph(createaleph,destaleph);
				BuildMapTables();
			}
		}
		createaleph = NULL;
		Rescale();
		Invalidate(TRUE);
		UpdateWindow();

	}
	CWnd::OnRButtonUp(nFlags, point);
}
void C2DMap::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	if (igcmap == NULL) return;
	if (dragsector) // cancel drag sector
	{
		dragsector = NULL;
		Rescale();
		Invalidate(TRUE);
		UpdateWindow();
	}
	else
	{ // start an aleph creation
		if (IsOverSector(point))
		{
			AfxMessageBox("Cant create sector over a sector");
		}
		else
		{
			float x = MAP2DUNSCALEX(point.x,maxx);
			float y = MAP2DUNSCALEY(point.y,maxy,MapH);
			// dont allow neg values for now
			if (x <0.0)	x = 0.0;
			if (y <0.0)	y = 0.0;
			CMAPDlg *pdlg = (CMAPDlg *) CWnd::GetParent();
			pdlg->NewSector(x,y);
		}
	}

	CWnd::OnRButtonDblClk(nFlags, point);
}

void C2DMap::OnMouseMove(UINT nFlags, CPoint point)
{
	if (dragsector)
	{
		dragsector->pos2D.x = MAP2DSCALEX(MAP2DUNSCALEX(point.x-dragpoint.x,maxx),maxx);
		dragsector->pos2D.y = MAP2DSCALEY(MAP2DUNSCALEY(point.y-dragpoint.y,maxy,MapH),maxy,MapH);
		Invalidate(TRUE);
		UpdateWindow();
		return;
	}
	if (createaleph)
	{
		createalephTOpos2D.x = point.x;
		createalephTOpos2D.y = point.y;
		Invalidate(TRUE);
		UpdateWindow();
		return;
	}
	CString tmp = sDispSectName;
	if (PtrSector psect = IsOverSector(point))
		sDispSectName = psect->igcsector.name;
	else
		sDispSectName = "";

	if (tmp != sDispSectName)
	{
		Invalidate(TRUE);
		UpdateWindow();
	}
	CWnd::OnMouseMove(nFlags, point);
}
//--------------------------------------------------------------------------
void C2DMap::BuildMapTables(void)
{
	mapalephs.RemoveAll();
	SMapAleph *pmapaleph;
	if (igcmap == NULL) return;
	POSITION pos = igcmap->cl_alephs.GetHeadPosition();
	for (int i=0;i < igcmap->cl_alephs.GetCount();i++)
	{
		CIGCAleph *paleph;
		paleph = &(igcmap->cl_alephs.GetNext(pos));
		if (!KnownAleph(paleph))
		{
			pmapaleph = new SMapAleph;
			pmapaleph->aleph1 = paleph;
			pmapaleph->sect1 = FindSector(paleph);
			pmapaleph->aleph2 = FindConnectingAleph(paleph);
			pmapaleph->sect2 = FindSector(pmapaleph->aleph2);
			mapalephs.AddTail(*pmapaleph);
		}
	}
	Rescale();
}

// find a sector given an aleph
CIGCSector *C2DMap::FindSector(CIGCAleph * paleph)
{
	POSITION pos = igcmap->cl_sectors.GetHeadPosition();
	for (int i=0;i < igcmap->cl_sectors.GetCount();i++)
	{
		CIGCSector *psector;
		psector = &(igcmap->cl_sectors.GetNext(pos));
		if (psector->igcsector.uid == paleph->igcaleph.sector_uid)
			return psector;
	}
	return NULL;
}
// find an aleph given an aleph
CIGCAleph *C2DMap::FindConnectingAleph(CIGCAleph * pigcaleph)
{
	POSITION pos = igcmap->cl_alephs.GetHeadPosition();
	for (int i=0;i < igcmap->cl_alephs.GetCount();i++)
	{
		CIGCAleph *paleph = &(igcmap->cl_alephs.GetNext(pos));
		if (paleph->igcaleph.connecting_aleph_uid == pigcaleph->igcaleph.uid)
			return paleph;
	}
	return NULL;
}
// rename aleph when destination sector change name
void C2DMap::RenameAlephs(CIGCSector *psect)
{
	POSITION pos = igcmap->cl_alephs.GetHeadPosition();
	for (int i=0;i < igcmap->cl_alephs.GetCount();i++)
	{
		CIGCAleph *paleph = &(igcmap->cl_alephs.GetNext(pos));
		if (paleph->igcaleph.sector_uid == psect->igcsector.uid) // aleph in this sector
		{
			CIGCAleph *pal = FindConnectingAleph(paleph); // connecting aleph
			if (pal)
				strcpy(pal->igcaleph.DestinationSectorName,psect->igcsector.name);
		}
	}
}
// delete an aleph and the connecting one
void C2DMap::DeleteAleph(CIGCAleph *pigcaleph)
{
	POSITION pos;
	PtrAleph pcal = FindConnectingAleph(pigcaleph);
	if (pcal == pigcaleph)
	{
		AfxMessageBox("!!! BOGUS ALEPH, SELF CONNECTING !!! Removing anyway");
	} else if (pcal)
	{
		pos = igcmap->cl_alephs.Find(*pcal);
		igcmap->cl_alephs.RemoveAt(pos);
	}
	else
	{
		AfxMessageBox("!!! BOGUS ALEPH, NO CONNECTING ALEPH FOUND !!! Removing anyway");
	}
	pos = igcmap->cl_alephs.Find(*pigcaleph);
	igcmap->cl_alephs.RemoveAt(pos);
	
}
bool C2DMap::KnownAleph(CIGCAleph * paleph)
{
	POSITION pos = mapalephs.GetHeadPosition();
	for (int i=0;i < mapalephs.GetCount();i++)
	{
		SMapAleph *mapa = &(mapalephs.GetNext(pos));
		if ((mapa->aleph1 == paleph) || (mapa->aleph2 == paleph))
			return true;
	}
	return false;
}

void C2DMap::SetGrid(bool b)
{
	bGrid = b;
	Rescale();
	Invalidate(TRUE);
	UpdateWindow();
}

void C2DMap::SetSnap(bool b)
{
	bSnap = b;
	Rescale();
	Invalidate(TRUE);
	UpdateWindow();
}
