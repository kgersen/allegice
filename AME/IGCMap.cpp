#include "stdafx.h"
#include "Resource.h"
#include "igcmap.h"
#ifdef _AGM
#include "AlephDlg.h"
#include "BaseDlg.h"
#include "RockDlg.h"
#endif

CIGCObject::CIGCObject(void)
{
}
CIGCObject::~CIGCObject(void)
{
}
int CIGCObject::DistanceToCenter(float X, float Y)
{
	float norm = X*X + Y*Y + GetZ()*GetZ();
	norm = sqrtf(norm);
	return (int)norm;
}
CIGCSector::CIGCSector(void)
{

	strncpy(igcsector.pad1  ,"\x0\x0",  2);// 00,00,
	strncpy(igcsector.pad3  ,"\x0",     1);// 00
	strncpy(igcsector.ending,"\xCC\xCC",2);//"CC","CC"

	igcsector.starSeed = 0x173; // 
	igcsector.LightColor.blue = 0xAA;
	igcsector.LightColor.green = 0xAA;
	igcsector.LightColor.red = 0xFF;
	igcsector.LightX = 1;
	igcsector.LightY = -1;
	igcsector.LightZ = 1;
	igcsector.debrisCount = 800;
	igcsector.starCount = 500;
	igcsector.PanetRadius = 125;
	igcsector.PlanetSinPct = 40;
	igcsector.PlanetLonPct = 100;
	strcpy(igcsector.globe,"globe1");
	strcpy(igcsector.nebbg,"nebplnt01bmp");
	igcsector.team = 0;

}
void CIGCSector::RandomizeAlephs(CList <CIGCAleph,CIGCAleph&> *cla)
{
	RandomizeAlephs(cla,5625,4250,1875,0.25f,0.1f,false,false);
}
// NormalRand() return a random double between -1 & 1
/*
r              => 0 max_rand
r/(max_rand/2) => 0 2
r/(max_rand/2)-1 => -1 1
*/
#define NormalRand() (((float)rand()/((float)RAND_MAX/2.0f))-1.0f)
#ifndef PI
#define PI (3.1415926538f)
#endif
void CIGCSector::RandomizeAlephs(CList <CIGCAleph,CIGCAleph&> *cla,
	int BASERAD, 
	int BASERADHOME, 
	int DISVAR, 
	float ANGLEVAR, 
	float ALEPHRADFACTOR,
	bool b19, bool b42
)
{
	CString csRender = "";
	if (b19)
		csRender = "plnt19";
	if (b42)
		csRender = "plnt42";
	int NumAlephs = 0;
	POSITION pos = cla->GetHeadPosition();
	for (int i=0;i < cla->GetCount();i++)
	{
		PtrAleph paleph =  &(cla->GetNext(pos));
		if (paleph->igcaleph.sector_uid == igcsector.uid)
			if (strcmp(paleph->igcaleph.renderbmp,csRender))
				NumAlephs++;
	}
	if (NumAlephs <1) return;

	float angledelta=2*PI/NumAlephs;
	//randomize the starting angle for aleph placement
	float baseangle=NormalRand()*PI+PI;
	//decrease radius based on number of alephs, unless they are home sector alephs
	float rad;
	if (igcsector.team > 0) // HOMESECTOR
		rad=BASERADHOME;
	else
		rad=BASERAD/(1+NumAlephs*ALEPHRADFACTOR);
	pos = cla->GetHeadPosition();
	for (int i=0;i < cla->GetCount();i++)
	{
		PtrAleph paleph =  &(cla->GetNext(pos));
		if (paleph->igcaleph.sector_uid == igcsector.uid)
			if (strcmp(paleph->igcaleph.renderbmp,csRender))
		{
			//shift the angle on a per aleph basis
			float angle=baseangle+angledelta*ANGLEVAR*NormalRand();
			//vary the radius and Z on a per aleph basis
			float x = paleph->igcaleph.posx;
			float y = paleph->igcaleph.posy;
			float z = paleph->igcaleph.posz;
			x= (DISVAR*NormalRand()+rad)*cosf(angle);
			y= (DISVAR*NormalRand()+rad)*sinf(angle);
			z= DISVAR*NormalRand();
			// do not randomize fixed aleph
			if (!paleph->bFixedPosition)
				paleph->ApplyPos3D(x,y,z);
			baseangle+=angledelta;
		}
	}
}
void CIGCSector::ApplyTemplate(CIGCSector *tplsect,bool bCol)
{
	if (tplsect)
	{
		if (bCol)
		{
			igcsector.LightColor = tplsect->igcsector.LightColor;
			igcsector.LightX = tplsect->igcsector.LightX;
			igcsector.LightY = tplsect->igcsector.LightY;
			igcsector.LightZ = tplsect->igcsector.LightZ;
		}
		if (strcmp(tplsect->igcsector.globe,"Random")==0)
		{
			int globe = 1+ (rand() * 8 / RAND_MAX) ;
			CString s;
			s.Format("globe%d",globe);
			strcpy(igcsector.globe,s);
		}
		else
			strcpy(igcsector.globe,tplsect->igcsector.globe);
		if (strcmp(tplsect->igcsector.nebbg,"Random")==0)
		{
			int neb = rand() * ICGBASE_NEBPLNT / RAND_MAX;
			strcpy(igcsector.nebbg,IGCNebplnt[neb]);
		}
		else
			strcpy(igcsector.nebbg ,tplsect->igcsector.nebbg);
	}
}
CIGCSector::~CIGCSector(void)
{

}
// overloading implementation
int operator==(const CIGCSector s1, const CIGCSector s2)
{
	return (s1.igcsector.uid == s2.igcsector.uid);
}

int operator!=(const CIGCSector s1, const CIGCSector s2)
{
	return (s1.igcsector.uid != s2.igcsector.uid);
}

int operator==(const CIGCAleph s1, const CIGCAleph s2)
{
	return (s1.igcaleph.uid == s2.igcaleph.uid);
}
int operator!=(const CIGCAleph s1, const CIGCAleph s2)
{
	return (s1.igcaleph.uid != s2.igcaleph.uid);
}
int operator==(const CIGCBase s1, const CIGCBase s2)
{
	return (s1.igcbase.uid == s2.igcbase.uid);
}
int operator!=(const CIGCBase s1, const CIGCBase s2)
{
	return (s1.igcbase.uid != s2.igcbase.uid);
}

int operator==(const CIGCRock s1, const CIGCRock s2)
{
	return (s1.igcrock.uid == s2.igcrock.uid);
}
int operator!=(const CIGCRock s1, const CIGCRock s2)
{
	return (s1.igcrock.uid != s2.igcrock.uid);
}

CIGCBase::CIGCBase(void)
{
	strncpy(igcbase.pad1,  "\xF0\xF0",             2);
	igcbase.uk = 0;
	igcbase.ending = '\xCD';// 'CD'
	igcbase.O1x  = 0;
	igcbase.O1y  = 1;
	igcbase.O1z  = 0;
	igcbase.O2x  = 0;
	igcbase.O2y  = 0;
	igcbase.O2z  = 1;
	igcbase.spinX = 0;
	igcbase.spinY = 0;
	igcbase.spinZ = 0;
	igcbase.spinspeed  = 0;


}
CIGCBase::~CIGCBase(void)
{
}

CIGCAleph::CIGCAleph(void)
: bAutoOrient(false)
{
	strncpy(igcaleph.pad1,  "\xCD\xCD\xCD",                  3); // CD,CD,CD,
	strncpy(igcaleph.ending,"\xCD\xCD",                      2); // CD,CD
	igcaleph.radius = 100; // KG 8/6/08
	igcaleph.sig = 1;
	bAutoOrient = true;
	bNoSpin = true;
	bIncludeSpin = true;
	bFixedPosition = false; // KG 8/6/08
	StdRandomPosition();
	igcaleph.spinx = igcaleph.O1x; 
	igcaleph.spiny = igcaleph.O1y;
	igcaleph.spinz = igcaleph.O1z;
	igcaleph.spinspeed = 0.2f; 
	strcpy(igcaleph.renderbmp,"plnt19"); //
	strcpy(igcaleph.imagebmp,"aleph");
}
CIGCAleph::~CIGCAleph(void)
{
}

CIGCRock::CIGCRock(void)
{
	igcrock.textureName[0] = 0;
	igcrock.dispandhp = '\xF0';// 'F0'

}
CIGCRock::CIGCRock(int tpl,unsigned short uid,CRockTpl *rtpl)
{
	igcrock.uid = uid;
	CString name;
	name.Format("%d",uid);
	igcrock.textureName[0] = 0;
	igcrock.dispandhp = '\xF0';// fullhealth & display gauge
	//igcrock.radius = 200 + (tpl>IGCROCK_TPL_HELIUM?200:0); //
	//igcrock.radius += igcrock.radius/2 - igcrock.radius*rand()/RAND_MAX; // add +/- 50%
	//igcrock.hitpoints = igcrock.radius * 5;
	//igcrock.sig = igcrock.radius / 10;
	igcrock.ore = 0;
	igcrock.oreMax = 0;

//             render         icon
// asteriod = bgrnd03 = 0 / meteoricon = 0
// asteriod = bgrnd05 = 2 / meteoricon = 0
// helium   = bgrnd56 = 9 / heliumrock = 1
// uranium  = bgrnd51 = 4 / hotrock    = 5
// silicon  = bgrnd52 = 5 / copperrock = 3
// carbon   = bgrnd53 = 6 / carbonrock = 2
// thorium  = bgrnd55 = 8 / goldrock = 4
	int iTplIdx;
	switch (tpl)
	{
		case IGCROCK_TPL_ASTERIOD: // Asteriod
			igcrock.flags = IGCROCK_IS_ASTERIOD;
			name.Insert(0,'a');
			strcpy(igcrock.iconbmp,IGCRockIcons[0]);
			strcpy(igcrock.renderbmp,IGCRockRenders[(rand()>(RAND_MAX/2))?0:2]);
			igcrock.dispandhp = '\xF1';// dont display gauge
			iTplIdx = 0;
			break;
		case IGCROCK_TPL_HELIUM: // Helium
			igcrock.flags = IGCROCK_IS_HELIUM;
			name.Insert(0,"He");
			strcpy(igcrock.iconbmp,IGCRockIcons[1]);
			strcpy(igcrock.renderbmp,IGCRockRenders[9]);
			iTplIdx = 1;
			break;
		case IGCROCK_TPL_URANIUM: // Uranium
			igcrock.flags = IGCROCK_IS_URANIUM;
			name.Insert(0,'U');
			strcpy(igcrock.iconbmp,IGCRockIcons[5]);
			strcpy(igcrock.renderbmp,IGCRockRenders[4]);
			iTplIdx = 2;
			break;
		case IGCROCK_TPL_SILICON: // Silicon
			igcrock.flags = IGCROCK_IS_SILICON;
			name.Insert(0,"Si");
			strcpy(igcrock.iconbmp,IGCRockIcons[3]);
			strcpy(igcrock.renderbmp,IGCRockRenders[5]);
			iTplIdx = 2;
			break;
		case IGCROCK_TPL_CARBON: // Carbon
			igcrock.flags = IGCROCK_IS_CARBON;
			name.Insert(0,'C');
			strcpy(igcrock.iconbmp,IGCRockIcons[2]);
			strcpy(igcrock.renderbmp,IGCRockRenders[6]);
			iTplIdx = 2;
			break;
		case IGCROCK_TPL_THORIUM: // Thorium
			igcrock.flags = IGCROCK_IS_THORIUM;
			name.Insert(0,'T');
			strcpy(igcrock.iconbmp,IGCRockIcons[4]);
			strcpy(igcrock.renderbmp,IGCRockRenders[8]);
			iTplIdx = 2;
			break;
		default:
			AfxMessageBox(_T("INTERNAL ERROR: UNEXPECTED tpl in CIGCRock(tpl)"));
			break;
	}
	if (tpl)
	{
		strcpy(igcrock.name,name);
	}
	else
	{
		strcpy(&(igcrock.name[1]),name);
		igcrock.name[0] = 0;
	}
	igcrock.radius = rtpl->GenRadius(iTplIdx);
	igcrock.hitpoints = rtpl->GenHP(iTplIdx,igcrock.radius);
	igcrock.sig = rtpl->GenSig(iTplIdx,igcrock.radius);
	if (tpl == IGCROCK_TPL_HELIUM)
	{
		igcrock.ore = 65; // igcrock.radius / 5; // kg - 6/8/8
		igcrock.oreMax = 65; // igcrock.radius / 5; // kg - 6/8/8
	}
	RandomOrientation();
	RandomSpin();	
}
void CIGCRock::SetAutoName(bool disp)
{
	CString name;
	name.Format("%d",igcrock.uid);
	switch (igcrock.flags)
	{
		case IGCROCK_IS_HELIUM : name.Insert(0,"He"); break;
		case IGCROCK_IS_URANIUM : name.Insert(0,'U'); break;
		case IGCROCK_IS_SILICON : name.Insert(0,"Si"); break;
		case IGCROCK_IS_CARBON : name.Insert(0,'C'); break;
		default:
		  name.Insert(0,'a'); break;
	}
	if (disp)
	{
		strcpy(igcrock.name,name);
	}
	else
	{
		strcpy(&(igcrock.name[1]),name);
		igcrock.name[0] = 0;
	}
}
void CIGCRock::ApplyTemplate(CRockTpl *rtpl)
{
	int iTplIdx = -1;
	for (int i=0;i<ROCKTPLMAX;i++)
	{
		if (rtpl->Types[i] & igcrock.flags)
		{
			iTplIdx = i;
		}
	}
	if (iTplIdx == -1) return;
	if (rtpl->radius_Included[iTplIdx])
	{
		igcrock.radius = rtpl->GenRadius(iTplIdx);
	}
	if (rtpl->sig_Included[iTplIdx])
	{
		igcrock.sig = rtpl->GenSig(iTplIdx,igcrock.radius);
	}
	if (rtpl->hp_Included[iTplIdx])
	{
		igcrock.hitpoints = rtpl->GenHP(iTplIdx,igcrock.radius);
	}
}

CIGCRock::~CIGCRock(void)
{
}
IGCObjType CIGCAleph::GetType()
{
	return igcAleph;
}
IGCObjType CIGCBase::GetType()
{
	return igcBase;
}
IGCObjType CIGCRock::GetType()
{
	return igcRock;
}

CPoint CIGCAleph::GetPos2D()
{
	return pos2D;
}
void CIGCAleph::SetPos2D(CPoint point)
{
	pos2D = point;
};

CPoint CIGCBase::GetPos2D()
{
	return pos2D;
}
void CIGCBase::SetPos2D(CPoint point)
{
	pos2D = point;
}


CPoint CIGCRock::GetPos2D()
{
	return pos2D;
}

void CIGCRock::SetPos2D(CPoint point)
{
	pos2D = point;
}

void CIGCAleph::ApplyPos3D(float x,float y,float z)
{
	igcaleph.posx = x;
	igcaleph.posy = y;
	igcaleph.posz = z;
	OrientTo();
}

void CIGCBase::ApplyPos3D(float x,float y,float z)
{
	igcbase.posx = x;
	igcbase.posy = y;
	igcbase.posz = z;
}

void CIGCRock::ApplyPos3D(float x,float y,float z)
{
	igcrock.posx = x;
	igcrock.posy = y;
	igcrock.posz = z;
}
// -------------------------------------------------------------------
CIGCMap::CIGCMap()
{
	name = "";
}

CIGCMap::~CIGCMap(void)
{
}

BOOL CIGCMap::SaveToFile(CString fn)
{
	CString vals = CheckValidity();
	if (vals != "")
	{
#ifdef _AGM
		AfxMessageBox(_T("WARNING INVALID MAP: " + vals));
#endif
	}
    CFile cfmap;
	CFileException e;
	if( !cfmap.Open( fn, CFile::modeCreate|CFile::modeReadWrite , &e ) )
	{
		return FALSE;
	}

	int size = 0;
	int cfmap_size = 0;
	int cfmap_read = 0;
	short tag;

	cfmap.Write(&cfmap_size,sizeof(size));

	// write sectors
	tag = IGCTAG_SECTOR;
	size = sizeof(SIGCSector);
	POSITION pos = cl_sectors.GetHeadPosition();
	for (int i=0;i < cl_sectors.GetCount();i++)
	{
		CIGCSector *psector = &(cl_sectors.GetNext(pos));
		cfmap.Write(&tag,sizeof(tag));			// the tag
		cfmap.Write(&size,sizeof(size));		// the size
		cfmap.Write(&psector->igcsector,size);  // the struct
	}

	// write alephs
	tag = IGCTAG_ALEPH;
	size = sizeof(SIGCAleph);
	pos = cl_alephs.GetHeadPosition();
	for (int i=0;i < cl_alephs.GetCount();i++)
	{
		CIGCAleph *paleph = &(cl_alephs.GetNext(pos));
		cfmap.Write(&tag,sizeof(tag));		// the tag
		cfmap.Write(&size,sizeof(size));    // the size
		// KG 8/5/08 - add leading '*' to name for fixed position aleph name
		SIGCAleph igcdata = paleph->igcaleph; //structure copy
		if (paleph->bFixedPosition)
		{
			// right shift
			for (int i=IGC_NAMEMAX-1;i>0;i--)
				igcdata.DestinationSectorName[i]=igcdata.DestinationSectorName[i-1];
			igcdata.DestinationSectorName[0] = '*';
		}
		cfmap.Write(&igcdata,size);  // the struct
	}

	// write rocks
	tag = IGCTAG_ROCK;
	size = sizeof(SIGCRock);
	pos = cl_rocks.GetHeadPosition();
	for (int i=0;i < cl_rocks.GetCount();i++)
	{
		CIGCRock *prock = &(cl_rocks.GetNext(pos));
		cfmap.Write(&tag,sizeof(tag));		// the tag
		cfmap.Write(&size,sizeof(size));    // the size
		cfmap.Write(&prock->igcrock,size);  // the struct
	}

	// write bases
	tag = IGCTAG_BASE;
	size = sizeof(SIGCBase);
	pos = cl_bases.GetHeadPosition();
	for (int i=0;i < cl_bases.GetCount();i++)
	{
		CIGCBase *pbase = &(cl_bases.GetNext(pos));
		cfmap.Write(&tag,sizeof(tag));		// the tag
		cfmap.Write(&size,sizeof(size));    // the size
		cfmap.Write(&pbase->igcbase,size);  // the struct
	}
	cfmap.Flush();
	cfmap_size = cfmap.GetLength();
	cfmap_size -= sizeof(cfmap_size);
	cfmap.Seek(0,CFile::begin);
	cfmap.Write(&cfmap_size,sizeof(cfmap_size));
	cfmap.Close();
	return TRUE;
}
BOOL CIGCMap::ReadFromFile(CString fn)
{
	CFile cfmap;
	CFileException e;
	if( !cfmap.Open( fn, CFile::modeRead , &e ) )
	{
		return FALSE;
	}

	bool cfmap_eof = false;
	int size,cfmap_size,cfmap_read;
	short tag;

	cfmap.Read(&cfmap_size,sizeof(size));
	cfmap_read = 0;
	while (cfmap_read < cfmap_size)
	{
		cfmap.Read(&tag,sizeof(tag));
		cfmap.Read(&size,sizeof(size));
		cfmap_read += sizeof(tag) + sizeof(size);
		switch (tag)
		{
			case IGCTAG_SECTOR:
				SIGCSector igcsector;
				CIGCSector *sector;
				cfmap.Read(&igcsector,sizeof(SIGCSector));
				cfmap_read += sizeof(SIGCSector);
				sector = new CIGCSector();
				sector->igcsector = igcsector;
				cl_sectors.AddTail(*sector);
				break;
			case IGCTAG_BASE:
				SIGCBase igcbase;
				CIGCBase *base;
				cfmap.Read(&igcbase,sizeof(SIGCBase));
				cfmap_read += sizeof(SIGCBase);
				if (!FindSector(igcbase.sector_uid))
				{
					AfxMessageBox("Corrupted map: found a station without sector !!!. Cleaned");

				}
				else
				{
					base = new CIGCBase();
					base->igcbase = igcbase;
					cl_bases.AddTail(*base);
				}
				break;
			case IGCTAG_ALEPH:
				SIGCAleph igcaleph;
				CIGCAleph *aleph;
				cfmap.Read(&igcaleph,sizeof(SIGCAleph));
				cfmap_read += sizeof(SIGCAleph);
				if (!FindSector(igcaleph.sector_uid))
				{
					AfxMessageBox("Corrupted map: found an aleph without sector !!!. Cleaned");

				}
				else
				{
					aleph = new CIGCAleph();
					aleph->igcaleph = igcaleph;
					// KG 8/5/08 - remove leading '*' from fixed position aleph
					if (igcaleph.DestinationSectorName[0] == '*')
					{
						aleph->bFixedPosition = true;
						// perform left shift of dest name to remove leading '*'
						for (int i=0;i<IGC_NAMEMAX-2;i++)
						  aleph->igcaleph.DestinationSectorName[i] = aleph->igcaleph.DestinationSectorName[i+1];
						aleph->igcaleph.DestinationSectorName[IGC_NAMEMAX-1] = 0;

					}
					else
						aleph->bFixedPosition = false; // this is done in CIGCAleph() already by in case someone change it

					aleph->AutoAuto();
					cl_alephs.AddTail(*aleph);
				}
				break;
			case IGCTAG_ROCK:
				SIGCRock igcrock;
				CIGCRock *rock;
				cfmap.Read(&igcrock,sizeof(SIGCRock));
				cfmap_read += sizeof(SIGCRock);
				if (!FindSector(igcrock.sector_uid))
				{
					AfxMessageBox("Corrupted map: found a rock without sector !!!. Cleaned");
				}
				else
				{
					rock = new CIGCRock();
					rock->igcrock = igcrock;
					cl_rocks.AddTail(*rock);
				}
				rock->FixSpin();
				break;
			default:	// unknown tag, skip it
				cfmap.Seek(size,CFile::current);
				cfmap_read += size;
				break;
		}
	}
	cfmap.Close();
	if (cfmap_read != cfmap_size)
		return FALSE;
#ifdef _AGM
	FixUIDs();
#endif
	return TRUE;
}
// return a sector given an uid
PtrSector CIGCMap::FindSector(unsigned short uid)
{
	POSITION pos = cl_sectors.GetHeadPosition();
	for (int i=0;i < cl_sectors.GetCount();i++)
	{
		PtrSector psector = &(cl_sectors.GetNext(pos));
		if (psector->igcsector.uid == uid)
			return psector;
	}	
	return NULL;
}
CString CIGCMap::DumpSectors()
{
	CString sres = "";
	CIGCSector *psector;

	POSITION pos = cl_sectors.GetHeadPosition();
	sres.Format("Dumping %d sector(s)\n",cl_sectors.GetCount());
	for (int i=0;i < cl_sectors.GetCount();i++)
	{
		psector = &(cl_sectors.GetNext(pos));
		sres.AppendFormat("Sector %s\n",psector->igcsector.name);
		sres.AppendFormat("  2dpos  = %08.2f %08.2f\n",psector->igcsector.posx,psector->igcsector.posy);
		sres.AppendFormat("  team   = %d\n",psector->igcsector.team);
	}
	return sres;
}

CString CIGCMap::DumpRocks()
{
	CString sres = "";
	CIGCRock rock;

	POSITION pos = cl_rocks.GetHeadPosition();
	for (int i=0;i < cl_rocks.GetCount();i++)
	{
		rock = cl_rocks.GetNext(pos);

		sres += rock.igcrock.name;
		sres += ":\n";
		sres.AppendFormat("  sig       = %08.2f\n",rock.igcrock.sig); 
		sres.AppendFormat("  position  = %08.2f %08.2f %08.2f\n",rock.igcrock.posx,rock.igcrock.posy,rock.igcrock.posz);
		sres.AppendFormat("  flags     = %04X\n",rock.igcrock.flags);
		sres.AppendFormat("  hitpoints = %08.2f\n",rock.igcrock.hitpoints);
		sres.AppendFormat("  size      = %04d\n",rock.igcrock.radius);
		sres.AppendFormat("  render    = %s\n",rock.igcrock.renderbmp);
		sres.AppendFormat("  texturename = %s\n",rock.igcrock.textureName);
		sres.AppendFormat("  icon      = %s\n",rock.igcrock.iconbmp);
		sres.AppendFormat("  hull      = %01X\n",rock.igcrock.dispandhp >>4);
		sres.AppendFormat("  dispHe    = %01X\n",rock.igcrock.dispandhp & 0x0F);

	}
	return sres;
}


int CIGCAleph::DispProps(CWnd * pParent,PtrCore pcore, CString cArtPath)
{
#ifdef _AGM
	CAlephDlg adlg;
	adlg.curaleph = this;
	adlg.sArtPath = cArtPath;
	return adlg.DoModal();
#else
	return 0;
#endif
}

int CIGCBase::DispProps(CWnd * pParent,PtrCore pcore, CString cArtPath)
{
#ifdef _AGM
	CBaseDlg bdlg;
	bdlg.curbase = this;
	bdlg.pcore = pcore;
	return bdlg.DoModal();
#else
	return 0;
#endif
}
int CIGCRock::DispProps(CWnd * pParent,PtrCore pcore, CString cArtPath)
{
#ifdef _AGM
	CRockDlg rdlg;
	rdlg.currock = this;
	rdlg.pcore = pcore;
	rdlg.cArtPath = cArtPath;
	return rdlg.DoModal();
#else
	return 0;
#endif
}

// fix bad uids (from beta) 
void CIGCMap::FixUIDs()
{
	bool bFixed = false;
	if (cl_sectors.GetCount() == 0) return; // empty map

	unsigned short min_suid = 0xFFFF;
	POSITION pos = cl_sectors.GetHeadPosition();
	for (int i=0;i < cl_sectors.GetCount();i++)
	{
		PtrSector psect = &(cl_sectors.GetNext(pos));
		if (psect->igcsector.uid <min_suid)
			min_suid = psect->igcsector.uid;

	}
	if (min_suid <UID_SEED)
	{
		bFixed = true;
		pos = cl_sectors.GetHeadPosition();
		for (int i=0;i < cl_sectors.GetCount();i++)
		{
			PtrSector psect = &(cl_sectors.GetNext(pos));
			psect->igcsector.uid += UID_SEED;

		}
		min_suid = UID_SEED; // to fix other objects
	}
	else
		min_suid = 0; // to fix other objects

	unsigned short min_buid = 0xFFFF;
	pos = cl_bases.GetHeadPosition();
	for (int i=0;i < cl_bases.GetCount();i++)
	{
		PtrBase pbase = &(cl_bases.GetNext(pos));
		pbase->igcbase.sector_uid += min_suid;
		if (pbase->igcbase.uid <min_buid)
			min_buid = pbase->igcbase.uid;
	}
	if (min_buid < UID_SEED)
	{
		bFixed = true;
		pos = cl_bases.GetHeadPosition();
		for (int i=0;i < cl_bases.GetCount();i++)
		{
			PtrBase pbase = &(cl_bases.GetNext(pos));
			pbase->igcbase.uid += UID_SEED;
		}
	}

	unsigned short min_ruid = 0xFFFF;
	pos = cl_rocks.GetHeadPosition();
	for (int i=0;i < cl_rocks.GetCount();i++)
	{
		PtrRock prock = &(cl_rocks.GetNext(pos));
		prock->igcrock.sector_uid += min_suid;
		if (prock->igcrock.uid <min_ruid)
			min_ruid = prock->igcrock.uid;
	}
	if (min_ruid < UID_SEED)
	{
		bFixed = true;
		pos = cl_rocks.GetHeadPosition();
		for (int i=0;i < cl_rocks.GetCount();i++)
		{
			PtrRock prock = &(cl_rocks.GetNext(pos));
			prock->igcrock.uid += UID_SEED;
		}
	}

	unsigned short min_auid = 0xFFFF;
	pos = cl_alephs.GetHeadPosition();
	for (int i=0;i < cl_alephs.GetCount();i++)
	{
		PtrAleph paleph = &(cl_alephs.GetNext(pos));
		paleph->igcaleph.sector_uid += min_suid;
		if (paleph->igcaleph.uid <min_auid)
			min_auid = paleph->igcaleph.uid;
	}
	if (min_auid < UID_SEED)
	{
		bFixed = true;
		pos = cl_alephs.GetHeadPosition();
		for (int i=0;i < cl_alephs.GetCount();i++)
		{
			PtrAleph paleph = &(cl_alephs.GetNext(pos));
			paleph->igcaleph.uid += UID_SEED;
			paleph->igcaleph.connecting_aleph_uid += UID_SEED;
		}
	}

	if (bFixed)
		AfxMessageBox(_T("MAP IS INVALID, BAD UNIQUE IDs. FIXED. SAVE IT BACK BEFORE USING IT."));

	// added: check that every aleph has a matching connecting aleph
	int iFixed = 0;
	bool bKeepGoing = true;
	while (bKeepGoing)
	{
		bKeepGoing = false;
		pos = cl_alephs.GetHeadPosition();
		for (int i=0;i < cl_alephs.GetCount();i++)
		{
			PtrAleph paleph = &(cl_alephs.GetNext(pos));
			PtrAleph pac = FindConnectingAleph(paleph);
			if ((pac == NULL) || (pac == paleph))
			{
				bKeepGoing = true;
				iFixed++;
#ifdef _DEBUG
				CString mes;
				mes.Format("BOGUS ALEPH (%d) %s in sector ",(pac == paleph),paleph->igcaleph.DestinationSectorName);
				POSITION poss = cl_sectors.GetHeadPosition();
				for (int ii=0;ii < cl_sectors.GetCount();ii++)
				{
					PtrSector psector = &(cl_sectors.GetNext(poss));
					if (psector->igcsector.uid == paleph->igcaleph.sector_uid) 
						mes.AppendFormat("%s ",psector->igcsector.name);
				}
				AfxMessageBox(mes);
#endif
				POSITION posd = cl_alephs.Find(*paleph);
				cl_alephs.RemoveAt(posd);
				i = cl_alephs.GetCount(); // terminate the 'for'
			}
		}
	}
	if (iFixed)
	{
		CString mes;
		mes.Format("MAP IS INVALID, %d BOGUS ALEPH(S) FOUND. FIXED. SAVE IT BACK BEFORE USING IT.",iFixed);
		AfxMessageBox(_T(mes));
	}
}
// -----------
// find an aleph given an aleph
PtrAleph CIGCMap::FindConnectingAleph(PtrAleph pigcaleph)
{
	POSITION pos = cl_alephs.GetHeadPosition();
	for (int i=0;i < cl_alephs.GetCount();i++)
	{
		PtrAleph paleph = &(cl_alephs.GetNext(pos));
		if (paleph->igcaleph.connecting_aleph_uid == pigcaleph->igcaleph.uid)
			return paleph;
	}
	return NULL;
}
// ----------
// rename aleph when destination sector change name
void CIGCMap::RenameAlephs(CIGCSector *psect)
{
	POSITION pos = cl_alephs.GetHeadPosition();
	for (int i=0;i < cl_alephs.GetCount();i++)
	{
		CIGCAleph *paleph = &(cl_alephs.GetNext(pos));
		if (paleph->igcaleph.sector_uid == psect->igcsector.uid) // aleph in this sector
		{
			CIGCAleph *pal = FindConnectingAleph(paleph); // connecting aleph
			if (pal)
				strcpy(pal->igcaleph.DestinationSectorName,psect->igcsector.name);
		}
	}
}
// ----------
int CIGCMap::RenameSectors(CString fn_names)
{
	CStdioFile cfnames;
	CFileException e;
	if( !cfnames.Open( fn_names, CFile::modeRead , &e ) )
	{
		return 1;
	}
	CStringArray aNames;
	CString sname;
	while (cfnames.ReadString(sname))
	{
		sname.Trim();
		if (sname != "")
			aNames.Add(sname);
	}
	if (aNames.GetCount() <cl_sectors.GetCount())
		return 2;
	
	POSITION pos = cl_sectors.GetHeadPosition();
	for (int i=0;i < cl_sectors.GetCount();i++)
	{
		PtrSector psect = &(cl_sectors.GetNext(pos));
		int idx = (rand()*aNames.GetCount())/RAND_MAX;
		strncpy(psect->igcsector.name,aNames.GetAt(idx),25);
		aNames.RemoveAt(idx);
		RenameAlephs(psect);
	}
	aNames.RemoveAll();
	cfnames.Close();
	return 0;
}
// randomize all alephs -
void CIGCMap::RandomizeAlephs(float r1,float r2,float z)
{
		POSITION pos = cl_alephs.GetHeadPosition();
		for (int i=0;i < cl_alephs.GetCount();i++)
		{
			PtrAleph paleph =  &(cl_alephs.GetNext(pos));
			paleph->RandomPosition(r1,r2,z);
		}
}
// randomize all alephs - default version
void CIGCMap::RandomizeAlephs()
{
	POSITION pos = cl_sectors.GetHeadPosition();
	for (int i=0;i < cl_sectors.GetCount();i++)
	{
		PtrSector psect =  &(cl_sectors.GetNext(pos));
		psect->RandomizeAlephs(&cl_alephs);
	}
}
// randomize all alephs - param version
void CIGCMap::RandomizeAlephs(int p1,int p2,int p3,float p4,float p5, bool b19, bool b42)
{
	POSITION pos = cl_sectors.GetHeadPosition();
	for (int i=0;i < cl_sectors.GetCount();i++)
	{
		PtrSector psect =  &(cl_sectors.GetNext(pos));
		psect->RandomizeAlephs(&cl_alephs,p1,p2,p3,p4,p5,b19,b42);
	}
}
// randomize all alephs - "move" version
void CIGCMap::RandomizeAlephs(float r)
{
		POSITION pos = cl_alephs.GetHeadPosition();
		for (int i=0;i < cl_alephs.GetCount();i++)
		{
			PtrAleph paleph =  &(cl_alephs.GetNext(pos));
			paleph->RandomPosition(r);
		}
}
CString CIGCMap::CheckValidity(void)
{
	CString res;
	int maxteam = 0;
	bool homesect[6] = {false,false,false,false,false,false};
	bool gars[6] = {false,false,false,false,false,false};

	if (cl_sectors.GetCount() == 0) return "No sector !!!";
	POSITION pos = cl_sectors.GetHeadPosition();
	for (int i=0;i < cl_sectors.GetCount();i++)
	{
		PtrSector psect = &(cl_sectors.GetNext(pos));
		if (psect->igcsector.team)
		{
			homesect[psect->igcsector.team - 1] = true;
			if (psect->igcsector.team > maxteam)
				maxteam = psect->igcsector.team;
		}
	}
	// check garrison/starbase
	pos = cl_bases.GetHeadPosition();
	for (int i=0;i < cl_bases.GetCount();i++)
	{
		PtrBase pbase = &(cl_bases.GetNext(pos));
		int basetype = pbase->igcbase.igcstationtype % 100;
		//if ((basetype == 10) || (basetype == 15))
		//{
		//	gars[pbase->igcbase.team] = true;
		//}
		PtrCoreStationType pst = pcore->GetBase(pbase->igcbase.igcstationtype);
		if (pst)
			if (pst->sabmCapabilities & c_sabmFlag)
				gars[pbase->igcbase.team] = true;
	}
	for (int i=0;i<6;i++)
	{
		if (gars[i] && (!homesect[i]))
		{
			res.Format("Team %d has a starting base but no home sector",i+1);
			return res;
		}
	}
	for (int i=0;i<maxteam;i++)
	{
		if (!(gars[i]))
		{
			res.Format("Team %d need a starting base",i+1);
			return res;
		}
	}
	if (maxteam <2)
		return("Need at least 2 teams (1 home sector, 1 garrison/Starbase each)");
	return "";
}
float CIGCAleph::GetX()
{
	return igcaleph.posx;
}
float CIGCBase::GetX()
{
	return igcbase.posx;
}
float CIGCRock::GetX()
{
	return igcrock.posx;
}

float CIGCAleph::GetY()
{
	return igcaleph.posy;
}
float CIGCBase::GetY()
{
	return igcbase.posy;
}
float CIGCRock::GetY()
{
	return igcrock.posy;
}

float CIGCAleph::GetZ()
{
	return igcaleph.posz;
}
float CIGCBase::GetZ()
{
	return igcbase.posz;
}
float CIGCRock::GetZ()
{
	return igcrock.posz;
}

void CIGCAleph::SetZ(float z)
{
	 igcaleph.posz = z;
}
void CIGCBase::SetZ(float z)
{
	igcbase.posz = z;
}
void CIGCRock::SetZ(float z)
{
	igcrock.posz = z;
}

// orient an aleph towards the center
// TODO: add a 3Dpoint param and orient aleph towards that point
void CIGCAleph::OrientTo(void)
{
	if (bAutoOrient)
	{
		// Com_Tropper contrib
		float HighestCoord = fabsf(igcaleph.posx);

		if (fabs(igcaleph.posy) > HighestCoord) 
			HighestCoord = fabsf(igcaleph.posy);
		if (fabs(igcaleph.posz) > HighestCoord) 
			HighestCoord = fabsf(igcaleph.posz);

		if (HighestCoord != 0)
		{
			igcaleph.O1x = (-igcaleph.posx) / HighestCoord;
			igcaleph.O1y = (-igcaleph.posy) / HighestCoord;
			igcaleph.O1z = (-igcaleph.posz) / HighestCoord;
		}
		else
		{
			igcaleph.O1x = 0;
			igcaleph.O1y = 0;
			igcaleph.O1z = 0;
		}
	}
	if (bNoSpin)
	{
		igcaleph.spinx = igcaleph.O1x;
		igcaleph.spiny = igcaleph.O1y;
		igcaleph.spinz = igcaleph.O1z;
	}
}

// for loading aleph (upon map load from file)
void CIGCAleph::AutoAuto(void)
{
	float x,y,z;
	x = igcaleph.O1x;
	y = igcaleph.O1y;
	z = igcaleph.O1z;
	OrientTo();
	if (((x == igcaleph.O1x) && (y == igcaleph.O1y) && (z == igcaleph.O1z)) ||
		((x == -igcaleph.posx) && (y == -igcaleph.posy) && (z == -igcaleph.posz)))
		bAutoOrient = TRUE;
	else
	{
		bAutoOrient = FALSE;
	}
	igcaleph.O1x = x;
	igcaleph.O1y = y;
	igcaleph.O1z = z;
	if (((igcaleph.O1x == igcaleph.spinx) && (igcaleph.O1y == igcaleph.spiny) && (igcaleph.O1z == igcaleph.spinz))||
		igcaleph.spinspeed == 0)
		bNoSpin = true;
}
// fix bad spin from prev. beta
void CIGCRock::FixSpin(void)
{
	if ((igcrock.spinX == 0) && (igcrock.spinY == 0) && (igcrock.spinZ == 0))
		RandomSpin();
	else // normalize
	{
		float maxf = fabsf(igcrock.spinX);
		if (fabsf(igcrock.spinY)>maxf) maxf = fabsf(igcrock.spinY);
		if (fabsf(igcrock.spinZ)>maxf) maxf = fabsf(igcrock.spinZ);
		igcrock.spinX = igcrock.spinX/maxf;
		igcrock.spinY = igcrock.spinY/maxf;
		igcrock.spinZ = igcrock.spinZ/maxf;
	}
}

void CIGCRock::RandomSpin(void)
{
	// spin axis vector must not be zero and must be normalized
	igcrock.spinX = igcrock.spinY = igcrock.spinZ = 0;
	while ((igcrock.spinX == 0) && (igcrock.spinY == 0) && (igcrock.spinZ == 0))
	{
		float x,y,z,maxf;
		x = 5.0f-10.0f*((float)rand()/(float)RAND_MAX);
		y = 5.0f-10.0f*((float)rand()/(float)RAND_MAX);
		z = 5.0f-10.0f*((float)rand()/(float)RAND_MAX);
		maxf = fabsf(x);
		if (fabsf(y)>maxf) maxf = fabsf(y);
		if (fabsf(z)>maxf) maxf = fabsf(z);
		igcrock.spinX = x/maxf;
		igcrock.spinY = y/maxf;
		igcrock.spinZ = z/maxf;
	}
	igcrock.spinspeed = ((float)rand()/(float)RAND_MAX)/5.0f; // max is 0.2

}

void CIGCRock::RandomOrientation(void)
{
	igcrock.O1x = 1.0f-2.0f*((float)rand()/(float)RAND_MAX);
	igcrock.O1y = 1.0f-2.0f*((float)rand()/(float)RAND_MAX);
	igcrock.O1z = 1.0f-2.0f*((float)rand()/(float)RAND_MAX);

	float maxf = fabsf(igcrock.O1x);
	if (fabsf(igcrock.O1y)>maxf) maxf = fabsf(igcrock.O1y);
	if (fabsf(igcrock.O1z)>maxf) maxf = fabsf(igcrock.O1z);
	igcrock.O1x = igcrock.O1x/maxf;
	igcrock.O1y = igcrock.O1y/maxf;
	igcrock.O1z = igcrock.O1z/maxf;

	igcrock.O2x = 1.0f-2.0f*((float)rand()/(float)RAND_MAX);
	igcrock.O2y = 1.0f-2.0f*((float)rand()/(float)RAND_MAX);
	igcrock.O2z = 1.0f-2.0f*((float)rand()/(float)RAND_MAX);

	maxf = fabsf(igcrock.O2x);
	if (fabsf(igcrock.O2y)>maxf) maxf = fabsf(igcrock.O2y);
	if (fabsf(igcrock.O2z)>maxf) maxf = fabsf(igcrock.O2z);
	igcrock.O2x = igcrock.O2x/maxf;
	igcrock.O2y = igcrock.O2y/maxf;
	igcrock.O2z = igcrock.O2z/maxf;

}

void CIGCRock::RandomPosition(void)
{
	// TODO IAGCVectorPtr ivector = IAGCVectorPtr(_uuidof(AGCVector));
	/*if (ivector)
	{
		ivector->InitRandomPosition(7000);
		igcrock.posx = ivector->GetX();
		igcrock.posy = ivector->GetY();
		igcrock.posz = ivector->GetZ();
	}*/
}

void CIGCAleph::RandomPosition(float xy_max_radius,float xy_min_radius, float z_height) // (4000,2500,2000)
{
	// random init in a pseudo torus 
	float r     = (float)rand()*xy_max_radius/(float)RAND_MAX +xy_min_radius; // radius
	float alpha = (float)rand()*6.28f/(float)RAND_MAX;         // (angle) radians
	igcaleph.posx = r * cosf(alpha); // coords
	igcaleph.posy = r * sinf(alpha);
	r = ((float)rand())*z_height/(float)RAND_MAX;
	igcaleph.posz = r-(z_height/2.0f);

	OrientTo();
}
// randomize 'move'
void CIGCAleph::RandomPosition(float radius) //
{
	igcaleph.posx = igcaleph.posx + radius/2.0f-((float)rand()*radius/(float)RAND_MAX);
	igcaleph.posy = igcaleph.posy + radius/2.0f-((float)rand()*radius/(float)RAND_MAX);
	igcaleph.posz = igcaleph.posz + radius/2.0f-((float)rand()*radius/(float)RAND_MAX);
	OrientTo();
}

void CIGCAleph::StdRandomPosition() 
{
	RandomPosition(4000.0,2500.0,2000.0);
}
void CIGCAleph::CloneFrom(CIGCAleph * tplaleph)
{
	if (tplaleph)
	{
		igcaleph = tplaleph->igcaleph;
		bIncludeSpin = tplaleph->bIncludeSpin;
		bAutoOrient = tplaleph->bAutoOrient;
		bNoSpin =  tplaleph->bNoSpin;
	}
}

void CIGCAleph::ApplyTemplate(CIGCAleph * tplaleph, bool bRender)
{
	if (tplaleph)
	{
		if (tplaleph->bIncludeSpin)
		{
			igcaleph.O1x = tplaleph->igcaleph.O1x;
			igcaleph.O1y = tplaleph->igcaleph.O1y;
			igcaleph.O1z = tplaleph->igcaleph.O1z;
			igcaleph.spinx = tplaleph->igcaleph.spinx;
			igcaleph.spiny = tplaleph->igcaleph.spiny;
			igcaleph.spinz = tplaleph->igcaleph.spinz;
			igcaleph.spinspeed = tplaleph->igcaleph.spinspeed;
			bAutoOrient = tplaleph->bAutoOrient;
			bNoSpin =  tplaleph->bNoSpin;
			OrientTo();
		}
		igcaleph.radius = tplaleph->igcaleph.radius;
		igcaleph.sig = tplaleph->igcaleph.sig;
		if (tplaleph->igcaleph.imagebmp[0])
		{
			strcpy_s(igcaleph.imagebmp,13,tplaleph->igcaleph.imagebmp);
		}
		if (bRender)
		{
			if (strcmp(tplaleph->igcaleph.renderbmp,"Random")==0)
			{
				if (rand()>RAND_MAX/2)
					strcpy(igcaleph.renderbmp,"plnt19");
				else
					strcpy(igcaleph.renderbmp,"plnt42");
			}
			else
				strcpy(igcaleph.renderbmp,tplaleph->igcaleph.renderbmp);
		}

	}
}
