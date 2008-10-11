// ==========================================================
// IGC Core structure 
//
// Design and implementation by
// - Kirth Gersen (kgersen@hotmail.com)
//
// Contributors:
//
// This file is part of ICE/AGM projects
//
// COVERED CODE IS PROVIDED UNDER THIS LICENSE ON AN "AS IS" BASIS, WITHOUT WARRANTY
// OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, WITHOUT LIMITATION, WARRANTIES
// THAT THE COVERED CODE IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE
// OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE COVERED
// CODE IS WITH YOU. SHOULD ANY COVERED CODE PROVE DEFECTIVE IN ANY RESPECT, YOU (NOT
// THE INITIAL DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME THE COST OF ANY NECESSARY
// SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER OF WARRANTY CONSTITUTES AN ESSENTIAL
// PART OF THIS LICENSE. NO USE OF ANY COVERED CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER
// THIS DISCLAIMER.
//
// Use at your own risk!
// ==========================================================
// required in include files:
//   agc.dll =   #import "C:\\Program Files\\Microsoft Games\\Allegiance\\Server\\agc.dll" no_namespace
//   best place to put it is in StdAfx.h
// ==========================================================
// Getting started:
// 			CIGCCore *cigccore = new CIGCCore;
//			CString sIGCfilepath = ... path to a .igc file
//			if (cigccore->ReadFromFile(sIGCfilepath))
//          {
//				// core read from file success
//				// add/remove/process entries with the members functions 
//				// or manipulate directly the cl_* arrays (1 for each object type).
//				// The Add<type> functions automatically compute the new UID
//				// use cigccore->SaveToFile(sIGCfilepath) to write back the .igc file
//          }

#include "StdAfx.h"
#include "Resource.h"
#include "corestruct.h"

CIGCCore::CIGCCore(void)
{
	pConstants = NULL;
}
#define FreeArray(a)	{for (int j=0;j<(a).GetSize();j++){void * p = (void *)(a).GetAt(j);	(a).SetAt(j,NULL);	delete p;}}

CIGCCore::~CIGCCore(void)
{
	UnloadCore();
}
void CIGCCore::UnloadCore()
{
	if (pConstants) delete pConstants;
	pConstants = NULL;

    FreeArray(cl_Civs);			cl_Civs.RemoveAll();
	FreeArray(cl_Counters);		cl_Counters.RemoveAll();
	FreeArray(cl_Devels);		cl_Devels.RemoveAll();
	FreeArray(cl_Drones);		cl_Drones.RemoveAll();
	FreeArray(cl_Probes);		cl_Probes.RemoveAll();
	FreeArray(cl_Mines);		cl_Mines.RemoveAll();
	FreeArray(cl_Missiles);		cl_Missiles.RemoveAll();
	FreeArray(cl_Ships);		cl_Ships.RemoveAll();
	FreeArray(cl_Parts);		cl_Parts.RemoveAll();
	FreeArray(cl_StationTypes);	cl_StationTypes.RemoveAll();
	FreeArray(cl_Projectiles);	cl_Projectiles.RemoveAll();
	FreeArray(cl_TreasureSets);	cl_TreasureSets.RemoveAll();

	mBasesMenu.DestroyMenu();
}

bool CIGCCore::ReadFromFile(CString fn)
{
	CFile cfmap;
	if (!cfmap.Open(fn,CFile::modeRead))
		return false;

    CString result;
	bool cfmap_eof = false;
	int size,cfmap_size,cfmap_read;
	short tag;
	
	UnloadCore();

	cfmap.Read(&iCoreHeader,sizeof(size));
	char *p = (char*)&iCoreHeader;
/*#ifndef __ICE
	if (p[2] != 2 || p[3] != 0x3b) // bad magic
	{
		cfmap.Close();
		return false;
	}
#endif*/
	cfmap.Read(&cfmap_size,sizeof(size));
	cfmap_read = 0;
	while (cfmap_read < cfmap_size)
	{
		cfmap.Read(&tag,sizeof(tag));
		cfmap.Read(&size,sizeof(size));
		cfmap_read += sizeof(tag) + sizeof(size);
		cfmap_read += size;
		switch((AGCObjectType)tag)
		{
		case AGC_Constants: // Assume 1 per core
			{
				ASSERT(pConstants == NULL);
				pConstants = new IGCCoreConstants;
				ASSERT(size == sizeof(*pConstants));
				cfmap.Read(pConstants,size);
			}
			break;
		case AGC_StationType ://Station Type
			{
				IGCCoreStationType *pstation = new IGCCoreStationType;
				ASSERT(size == sizeof(*pstation));
				cfmap.Read(pstation,size); 
				cl_StationTypes.Add(pstation);
			}
			break;
		case AGC_Civilization ://Civilization
			{
				IGCCoreCiv *pciv = new IGCCoreCiv;
				ASSERT(size == sizeof(*pciv));
				cfmap.Read(pciv,size);
				cl_Civs.Add(pciv);
			}
			break;
		case AGC_Development : //Devel
			{
				IGCCoreDevel *pdevel = new IGCCoreDevel;
				ASSERT(size == sizeof(*pdevel));
				cfmap.Read(pdevel,size); 
				cl_Devels.Add(pdevel);
				break;
			}
			break;
		case AGC_BucketStart: // ship
			{
				IGCCoreShip *pship = new IGCCoreShip;
				//ASSERT(size == sizeof(*pship));
				for (int i=0;i<IGCSHIPMAXWEAPONS;i++)
				{
					pship->parts[i].part_mask = 0;
					pship->parts[i].part_type = 1;
					pship->parts[i].uk1 = 140;
					pship->parts[i].uk2 = 121;
					strcpy_s(pship->parts[i].position,13,"");
					//30 00 .. 00
					pship->parts[i].todo[0] = 0x30;
					for (int j=0;j<8;j++)
						pship->parts[i].todo[1+j] = 0;

				}
				cfmap.Read(pship,size);
				pship->size = size;
				cl_Ships.Add(pship);
				break;
			}
			break;
		case AGC_PartType: // parts
			{
				IGCCorePart *ppart = new IGCCorePart;
				ppart->isspec = false;
				if (size == IGC_PROXYPARTSIZE){
					cfmap.Read(&(ppart->suk2),size);
					strcpy_s(ppart->name,25,ppart->slot);
					ppart->isspec = true;
				}
				else
					cfmap.Read(ppart,size);
				ppart->size = size;
				cl_Parts.Add(ppart);
				break;
			}
		case AGC_ChaffTypeOK /*AGC_ChaffType is bogus (36)*/ ://Counter
			{
				IGCCoreCounter *pcounter= new IGCCoreCounter;
				ASSERT(size == sizeof(*pcounter));
				cfmap.Read(pcounter,size); 
				cl_Counters.Add(pcounter);
			}
			break;
		case AGC_MissileType  :// Missile
			{
				IGCCoreMissile *pmissile= new IGCCoreMissile;
				ASSERT(size == sizeof(*pmissile));
				cfmap.Read(pmissile,size); 
				cl_Missiles.Add(pmissile);
			}
			break;
		case AGC_MineType  :// Mines
			{
				IGCCoreMine *pmine= new IGCCoreMine;
				ASSERT(size == sizeof(*pmine));
				cfmap.Read(pmine,size); 
				cl_Mines.Add(pmine);
			}
			break;
		case AGC_DroneType  :// Drones
			{
				IGCCoreDrone *pdrone= new IGCCoreDrone;
				ASSERT(size == sizeof(*pdrone));
				cfmap.Read(pdrone,size); 
				cl_Drones.Add(pdrone);
			}
			break;
		case AGC_ProbeType: // Probes & combat/station pods
			{
				IGCCoreProbe *pprobe= new IGCCoreProbe;
				ASSERT(size == sizeof(*pprobe));
				cfmap.Read(pprobe,size); 
				cl_Probes.Add(pprobe);
			}break;
		case AGC_ProjectileType: // Projectiles
			{
				IGCCoreProjectile *pprojectile= new IGCCoreProjectile;
				ASSERT(size == sizeof(*pprojectile));
				cfmap.Read(pprojectile,size); 
				cl_Projectiles.Add(pprojectile);
			}break;
		case AGC_TreasureSet: //
			{
				IGCCoreTreasureSet *ptreasureSet= new IGCCoreTreasureSet;
				//ASSERT(size == sizeof(*ptreasureSet));
				cfmap.Read(ptreasureSet,SIGCCoreTreasureSet_Size);
				ptreasureSet->name[25] = 0; // set trailing zero for C handling
				if (ptreasureSet->count)
				{
					ptreasureSet->ChanceEntries = new IGCCoreTreasureChance[ptreasureSet->count];
					for (int n=0;n<ptreasureSet->count;n++)
						cfmap.Read(&(ptreasureSet->ChanceEntries[n]),sizeof(IGCCoreTreasureChance));
				}
				cl_TreasureSets.Add(ptreasureSet);
			}break;
		default:	// unknown/unhandled tag, skip it
			cfmap.Seek(size,CFile::current);
			break;
		}
	}
	cfmap.Close();
	BuildBasesMenu(DYNMENUSID);
	//DumpCore();
	return true;
}
void CIGCCore::BuildBasesMenu(UINT uid)
{
	mBasesMenu.CreatePopupMenu();
	UINT mID = uid;
	for (int j=0;j<cl_Civs.GetSize();j++)
	{
		CMenu *submenu = new CMenu;
		submenu->CreatePopupMenu();
		PtrCoreCiv pciv = cl_Civs.GetAt(j);
		for (int b=0;b<cl_StationTypes.GetSize();b++)
		{
			PtrCoreStationType pst = cl_StationTypes.GetAt(b);
			//if ((pst->uid > (100*j)) && (pst->uid < 100*(j+1)))
			if (Depends(pst->techtree,pciv->techtree))
			{
				CString res = pst->name;
				res.AppendFormat("(%d)",pst->uid);
				submenu->AppendMenu(MF_STRING,mID+pst->uid,res);
			}
		}
		mBasesMenu.AppendMenu(MF_POPUP,(UINT_PTR)submenu->m_hMenu,pciv->name);
		delete submenu;
		//mBasesMenu.AppendMenu(MF_STRING,iBMMin+j,pciv->name);
	}
}

bool CIGCCore::Depends(BYTE *tt1, BYTE *tt2)
{
	for (int i=0;i<50;i++)
		for (int j=0;j<8;j++)
		{
			if(tt1[i] & (1<<j))
				if (tt2[i] & (1<<j))
					return true;
		}
	return false;
}

PtrCoreStationType CIGCCore::GetBase(unsigned short uid)
{
	for (int b=0;b<cl_StationTypes.GetSize();b++)
	{
		PtrCoreStationType pst = cl_StationTypes.GetAt(b);
		if (pst->uid == uid)
			return pst;
	}
	return NULL;
}

CString CIGCCore::GetBaseName(unsigned short uid)
{
	for (int b=0;b<cl_StationTypes.GetSize();b++)
	{
		PtrCoreStationType pst = cl_StationTypes.GetAt(b);
		if (pst->uid == uid)
		{
			CString res = pst->name;
			return res;
		}
	}
	return "";
}
CString CIGCCore::GetBaseCivName(unsigned short uid)
{
	//int j = uid/100;
	//if (j>=cl_Civs.GetSize())
	//	return "";
	//PtrCoreCiv pciv = cl_Civs.GetAt(j);
	//CString res = pciv->name;
	//return res;
	for (int b=0;b<cl_StationTypes.GetSize();b++)
	{
		PtrCoreStationType pst = cl_StationTypes.GetAt(b);
		if (pst->uid == uid)
		{
			for (int c=0;c<cl_Civs.GetSize();c++)
			{
				PtrCoreCiv pciv = cl_Civs.GetAt(c);
				if (Depends(pst->techtree,pciv->techtree))
				{
					CString res = pciv->name;
					return res;
				}
			}
		}
	}
	return "";


}
void CIGCCore::BuildRenders(CComboBox *cb)
{
	cb->ResetContent();
	int idx;
	for (int j=0;j<cl_Civs.GetSize();j++)
	{
		PtrCoreCiv pciv = cl_Civs.GetAt(j);
		for (int b=0;b<cl_StationTypes.GetSize();b++)
		{
			PtrCoreStationType pst = cl_StationTypes.GetAt(b);
			if ((pst->uid > (100*j)) && (pst->uid < 100*(j+1)))
			{
				CString s = "Base - ";
				s.Append(pciv->name); s.Append(" - ");
				s.Append(pst->name);
				idx = cb->AddString(s);
				cb->SetItemDataPtr(idx,(void *)pst->model);
			}
		}
	}
	for (int k=0;k<cl_Ships.GetSize();k++)
	{
		PtrCoreShip pship =  cl_Ships.GetAt(k);
		int already_added = 0;
		for (int l=0;l<cb->GetCount();l++)
		{
			if (strcmp(pship->model,(char *)cb->GetItemDataPtr(l)) == 0)
			{
				already_added = 1;
				break;
			}
		}
		if (!already_added)
		{
			CString s = "Ship - ";
			s.Append(pship->name);s.AppendFormat(" (%s)",pship->model);
			idx = cb->AddString(s); 
			cb->SetItemDataPtr(idx,(void *)pship->model);
		}
	}
	for (int k=0;k<cl_Counters.GetSize();k++)
	{
		PtrCoreCounter pcounter =  cl_Counters.GetAt(k);
		int already_added = 0;
		for (int l=0;l<cb->GetCount();l++)
		{
			if (strcmp(pcounter->model,(char *)cb->GetItemDataPtr(l)) == 0)
			{
				already_added = 1;
				break;
			}
		}
		if (!already_added)
		{
			CString s = "Counter - ";
			s.Append(pcounter->name);s.AppendFormat(" (%s)",pcounter->model);
			idx = cb->AddString(s); 
			cb->SetItemDataPtr(idx,(void *)pcounter->model);
		}
	}
	for (int k=0;k<cl_Missiles.GetSize();k++)
	{
		PtrCoreMissile pmissile =  cl_Missiles.GetAt(k);
		int already_added = 0;
		for (int l=0;l<cb->GetCount();l++)
		{
			if (strcmp(pmissile->model,(char *)cb->GetItemDataPtr(l)) == 0)
			{
				already_added = 1;
				break;
			}
		}
		if (!already_added)
		{
			CString s = "Missile - ";
			s.Append(pmissile->name);s.AppendFormat(" (%s)",pmissile->model);
			idx = cb->AddString(s); 
			cb->SetItemDataPtr(idx,(void *)pmissile->model);
		}
	}

	for (int k=0;k<cl_Mines.GetSize();k++)
	{
		PtrCoreMine pmine =  cl_Mines.GetAt(k);
		int already_added = 0;
		for (int l=0;l<cb->GetCount();l++)
		{
			if (strcmp(pmine->model,(char *)cb->GetItemDataPtr(l)) == 0)
			{
				already_added = 1;
				break;
			}
		}
		if (!already_added)
		{
			CString s = "Mine - ";
			s.Append(pmine->name);s.AppendFormat(" (%s)",pmine->model);
			idx = cb->AddString(s); 
			cb->SetItemDataPtr(idx,(void *)pmine->model);
		}
	}

	for (int k=0;k<cl_Drones.GetSize();k++)
	{
		PtrCoreDrone pdrone =  cl_Drones.GetAt(k);
		int already_added = 0;
		for (int l=0;l<cb->GetCount();l++)
		{
			if (strcmp(pdrone->model,(char *)cb->GetItemDataPtr(l)) == 0)
			{
				already_added = 1;
				break;
			}
		}
		if (!already_added)
		{
			CString s = "Drone - ";
			s.Append(pdrone->name);s.AppendFormat(" (%s)",pdrone->model);
			idx = cb->AddString(s); 
			cb->SetItemDataPtr(idx,(void *)pdrone->model);
		}
	}

}


void CIGCCore::DumpCore(void)
{
	CFile ctmp("c:\\core.txt",CFile::modeCreate|CFile::modeReadWrite);
	CString stmp;
	CString factors[25];
	/*for (int j=0;j<IGCNUMC;j++)
	{
		stmp.Format("const %d/%x = %f\n",j,j,pConstants->constants[j]);
		ctmp.Write(stmp,strlen(stmp));
	}*/
	/*
	stmp.Format("------------------------ Parts --------------------\n");
	ctmp.Write(stmp,strlen(stmp));
	for (int j=0;j<cl_Parts.GetSize();j++)
	{
		PtrCorePart ppart = cl_Parts.GetAt(j);
		stmp.Format("name = %14s - %14s - %04d - (%04X,%04X) - (%04X,%04X,%04X,%04X)",
			ppart->name,ppart->slot,ppart->size,
			ppart->suk1,ppart->suk2,
			ppart->uid,ppart->overriding_uid,ppart->type,ppart->usemask);
			if (ppart->isspec && (ppart->isspec ))
		{
			for (int i=0;i<cl_Missiles.GetSize();i++)
			{
				PtrCoreMissile pmis = cl_Missiles.GetAt(i);
				if (pmis->uid == ppart->usemask)
					stmp.AppendFormat("%s",pmis->name);
			}
			for (int i=0;i<cl_Mines.GetSize();i++)
			{
				PtrCoreMine pmine = cl_Mines.GetAt(i);
				if (pmine->uid == ppart->usemask)
					stmp.AppendFormat("%s (%g,%g,%g)",pmine->name,
						pmine->stats_radius,pmine->stats_damage,pmine->stats_s1);
			}

			for (int i=0;i<cl_Probes.GetSize();i++)
			{
				PtrCoreProbe ppro = cl_Probes.GetAt(i);
				if (ppro->uid == ppart->usemask)
					stmp.AppendFormat("%s",ppro->name);
			}

			for (int i=0;i<cl_Counters.GetSize();i++)
			{
				PtrCoreCounter pc = cl_Counters.GetAt(i);
				if (pc->uid == ppart->usemask)
					stmp.AppendFormat("%s (%g,%g,%d,%d,%g)",pc->name,
						pc->stats_ftodo[0],pc->stats_ftodo[1],
						pc->stats_stodo[0],pc->stats_stodo[1],
						pc->fuk);
			}
		}
		//stmp.AppendFormat("(%g)\n",ppart->ukf);
		ctmp.Write(stmp,strlen(stmp));
	}
	*/

	/*
	for (int j=0;j<cl_Civs.GetSize();j++)
	{
		PtrCoreCiv pciv = cl_Civs.GetAt(j);
		stmp.Format("------------------------------------------------\n");
		stmp.AppendFormat("civ = %s (%d/%x)\n",pciv->name,pciv->uid,pciv->uid);
		//for (int f=0;f<23;f++)
		//{
		stmp.AppendFormat("IGCF_ShipAgility1   = %f\n",pciv->factors[IGCF_ShipAgility1]);
		stmp.AppendFormat("IGCF_ShipAgility2   = %f\n",pciv->factors[IGCF_ShipAgility2]);
		stmp.AppendFormat("IGCF_StationHull1   = %f\n",pciv->factors[IGCF_StationHull1]);
		stmp.AppendFormat("IGCF_StationHull2   = %f\n",pciv->factors[IGCF_StationHull2]);
		stmp.AppendFormat("IGCF_StationShield1 = %f\n",pciv->factors[IGCF_StationShield1]);
		stmp.AppendFormat("IGCF_StationShield2 = %f\n",pciv->factors[IGCF_StationShield2]);
		stmp.AppendFormat("IGCF_ShipShield1    = %f\n",pciv->factors[IGCF_ShipShield1]);
		stmp.AppendFormat("IGCF_ShipShield2    = %f\n",pciv->factors[IGCF_ShipShield2]);
		stmp.AppendFormat("IGCF_UNKNOWN        = %f\n",pciv->factors[IGCF_UNKNOWN]);
		//	if (!((f+1) % 5)) stmp.AppendFormat("\n");
		//}
		//stmp.AppendFormat("\n");
		for (int f=0;f<101;f++)
		{
			stmp.AppendFormat("%02X ",pciv->bits[f]);
			if (!((f+1) % 20)) stmp.AppendFormat("\n");
		}
		stmp.AppendFormat("\n");
		ctmp.Write(stmp,strlen(stmp));
	}

	for (int c=0;c<6;c++)
		for (int j=0;j<cl_Devels.GetSize();j++)
		{
			PtrCoreDevel pdevel = cl_Devels.GetAt(j);
			if (pdevel->uk2[0] == c)
			{
			stmp.Format("------------------------------------------------\n");
			stmp.AppendFormat("devel = %s (%d,%x) - (%d,%x)\n",pdevel->name,pdevel->uid,pdevel->uid,pdevel->end,pdevel->end);
			//stmp.AppendFormat("%s\n",pdevel->description);
			for (int f=0;f<100;f++)
			{
				stmp.AppendFormat("%02X ",pdevel->uk2[f]);
				if (!((f+1) % 20)) stmp.AppendFormat("\n");
			}
			//stmp.AppendFormat("\n");
			ctmp.Write(stmp,strlen(stmp));
			}
		}
*/	ctmp.Close();

}
bool CIGCCore::SaveToFile(CString fn)
{
    CFile cfcore;
	if (!cfcore.Open(fn,CFile::modeCreate|CFile::modeReadWrite))
	{
		// handle errors
		return false;
	}
#ifdef _ICEPUB
	iCoreHeader++;
#endif
	cfcore.Write(&iCoreHeader,sizeof(iCoreHeader));

	SortEntries();
	int size = 0;
	int cfcore_size = 0;
	int cfcore_read = 0;
	short tag;
	int tag_size;

	cfcore.Write(&cfcore_size,sizeof(size)); // placeholder for total size
	tag = AGC_Constants; tag_size = sizeof(*pConstants);
	cfcore.Write(&tag,sizeof(tag));
	cfcore.Write(&tag_size,sizeof(tag_size));
	cfcore.Write(pConstants,tag_size);

	// Projectiles
	tag = AGC_ProjectileType; tag_size = sizeof(IGCCoreProjectile);
	for (int j=0;j<cl_Projectiles.GetSize();j++)
	{
		PtrCoreProjectile pprojectile = cl_Projectiles.GetAt(j);
		cfcore.Write(&tag,sizeof(tag));
		cfcore.Write(&tag_size,sizeof(tag_size));
		cfcore.Write(pprojectile,tag_size);
	}

	// Missiles
	tag = AGC_MissileType; tag_size = sizeof(IGCCoreMissile);
	for (int j=0;j<cl_Missiles.GetSize();j++)
	{
		PtrCoreMissile pmissile = cl_Missiles.GetAt(j);
		cfcore.Write(&tag,sizeof(tag));
		cfcore.Write(&tag_size,sizeof(tag_size));
		cfcore.Write(pmissile,tag_size);
	}

	// Counters
	tag = AGC_ChaffTypeOK; tag_size = sizeof(IGCCoreCounter);
	for (int j=0;j<cl_Counters.GetSize();j++)
	{
		PtrCoreCounter pcounter = cl_Counters.GetAt(j);
		cfcore.Write(&tag,sizeof(tag));
		cfcore.Write(&tag_size,sizeof(tag_size));
		cfcore.Write(pcounter,tag_size);
	}
	
	// Mines
	tag = AGC_MineType; tag_size = sizeof(IGCCoreMine);
	for (int j=0;j<cl_Mines.GetSize();j++)
	{
		PtrCoreMine pmine = cl_Mines.GetAt(j);
		cfcore.Write(&tag,sizeof(tag));
		cfcore.Write(&tag_size,sizeof(tag_size));
		cfcore.Write(pmine,tag_size);
	}

	// Probes
	tag = AGC_ProbeType; tag_size = sizeof(IGCCoreProbe);
	for (int j=0;j<cl_Probes.GetSize();j++)
	{
		PtrCoreProbe pprobe = cl_Probes.GetAt(j);
		cfcore.Write(&tag,sizeof(tag));
		cfcore.Write(&tag_size,sizeof(tag_size));
		cfcore.Write(pprobe,tag_size);
	}

	// Parts
	tag = AGC_PartType;
	for (int j=0;j<cl_Parts.GetSize();j++)
	{
		PtrCorePart ppart = cl_Parts.GetAt(j);
		cfcore.Write(&tag,sizeof(tag));
		tag_size = ppart->size;
		if (ppart->isspec)
		{
			cfcore.Write(&tag_size,sizeof(tag_size));
			cfcore.Write(&(ppart->suk2),tag_size);
		}
		else
		{
			cfcore.Write(&tag_size,sizeof(tag_size));
			cfcore.Write(ppart,tag_size);
		}
	}

	// Buckets (Ships)
	tag = AGC_BucketStart; 
	for (int j=0;j<cl_Ships.GetSize();j++)
	{
		PtrCoreShip pship = cl_Ships.GetAt(j);
		cfcore.Write(&tag,sizeof(tag));
		tag_size = pship->nb_parts*sizeof(IGCCoreShipMP)+540;
		cfcore.Write(&tag_size,sizeof(tag_size));
		cfcore.Write(pship,tag_size);
	}

	// Devels
	tag = AGC_Development; tag_size = sizeof(IGCCoreDevel);
	for (int j=0;j<cl_Devels.GetSize();j++)
	{
		PtrCoreDevel pdevel = cl_Devels.GetAt(j);
		cfcore.Write(&tag,sizeof(tag));
		cfcore.Write(&tag_size,sizeof(tag_size));
		cfcore.Write(pdevel,tag_size);
	}

	// Drones
	tag = AGC_DroneType; tag_size = sizeof(IGCCoreDrone);
	for (int j=0;j<cl_Drones.GetSize();j++)
	{
		PtrCoreDrone pdrone = cl_Drones.GetAt(j);
		cfcore.Write(&tag,sizeof(tag));
		cfcore.Write(&tag_size,sizeof(tag_size));
		cfcore.Write(pdrone,tag_size);
	}

	// Stations
	tag = AGC_StationType; tag_size = sizeof(IGCCoreStationType);
	for (int j=0;j<cl_StationTypes.GetSize();j++)
	{
		PtrCoreStationType pstation = cl_StationTypes.GetAt(j);
		cfcore.Write(&tag,sizeof(tag));
		cfcore.Write(&tag_size,sizeof(tag_size));
		cfcore.Write(pstation,tag_size);
	}

	// TreasureSets
	tag = AGC_TreasureSet; 
	for (int j=0;j<cl_TreasureSets.GetSize();j++)
	{
		PtrCoreTreasureSet ptreasureSet = cl_TreasureSets.GetAt(j);
		cfcore.Write(&tag,sizeof(tag));
		tag_size = SIGCCoreTreasureSet_Size + sizeof(IGCCoreTreasureChance)*ptreasureSet->count;
		cfcore.Write(&tag_size,sizeof(tag_size));
		cfcore.Write(ptreasureSet,SIGCCoreTreasureSet_Size);
		for (int n=0;n<ptreasureSet->count;n++)
		{
			cfcore.Write(&(ptreasureSet->ChanceEntries[n]),sizeof(IGCCoreTreasureChance));
		}
	}

	// Civs
	tag = AGC_Civilization; tag_size = sizeof(IGCCoreCiv);
	for (int j=0;j<cl_Civs.GetSize();j++)
	{
		PtrCoreCiv pCiv = cl_Civs.GetAt(j);
		cfcore.Write(&tag,sizeof(tag));
		cfcore.Write(&tag_size,sizeof(tag_size));
		cfcore.Write(pCiv,tag_size);
	}

	// write the total size and close
	cfcore.Flush();
	cfcore_size = (int)cfcore.GetLength();
	cfcore_size -= sizeof(cfcore_size)+sizeof(iCoreHeader);
	cfcore.Seek(sizeof(iCoreHeader),CFile::begin);
	cfcore.Write(&cfcore_size,sizeof(cfcore_size));
	cfcore.Close();
	return true;
}

char *CIGCCore::ProxyPartName(unsigned short uid)
{
	char *name = NULL;
	for (int i=0;i<cl_Counters.GetCount();i++)
	{
		PtrCoreCounter pcounter = cl_Counters.GetAt(i);
		if (pcounter->uid == uid)
			name = pcounter->name;
	}
	for (int i=0;i<cl_Mines.GetCount();i++)
	{
		PtrCoreMine pmine = cl_Mines.GetAt(i);
		if (pmine->uid == uid)
			name = pmine->name;
	}
	for (int i=0;i<cl_Probes.GetCount();i++)
	{
		PtrCoreProbe pprobe = cl_Probes.GetAt(i);
		if (pprobe->uid == uid)
			name = pprobe->name;
	}
	for (int i=0;i<cl_Missiles.GetCount();i++)
	{
		PtrCoreMissile pmis = cl_Missiles.GetAt(i);
		if (pmis->uid == uid)
			name = pmis->name;
	}
	return name;
}
char *CIGCCore::PartName(unsigned short uid)
{
	for (int j=0;j<cl_Parts.GetSize();j++)
	{
		PtrCorePart ppart = cl_Parts.GetAt(j);
		if (ppart->uid == uid)
			if (ppart->isspec)
				return ProxyPartName(ppart->usemask);
			else
				return ppart->name;
	}
	return NULL;
}
char *CIGCCore::DevelName(unsigned short uid)
{
	for (int j=0;j<cl_Devels.GetSize();j++)
	{
		PtrCoreDevel devel = cl_Devels.GetAt(j);
		if (devel->uid == uid)
				return devel->name;
	}
	return NULL;
}
PtrCorePart CIGCCore::ProxyGet(unsigned short uid)
{
	for (int i=0;i<cl_Parts.GetCount();i++)
	{
		PtrCorePart ppart = cl_Parts.GetAt(i);
		if (ppart->isspec)
			if (ppart->usemask == uid)
				return ppart;
	}
	return NULL;
}

PtrCoreEntry CIGCCore::ProxyPart(unsigned short uid)
{
	PtrCoreEntry pce = new CoreEntry;
	pce->entry = NULL;
	for (int i=0;i<cl_Counters.GetCount();i++)
	{
		PtrCoreCounter pcounter = cl_Counters.GetAt(i);
		if (pcounter->uid == uid)
		{
			pce->tag = (AGCObjectType)AGC_ChaffTypeOK;
			pce->IGCPartType = ET_ChaffLauncher;
			pce->usemask = pcounter->use_mask;
			pce->entry = (LPARAM)pcounter;
			return pce;
		}
	}
	for (int i=0;i<cl_Mines.GetCount();i++)
	{
		PtrCoreMine pmine = cl_Mines.GetAt(i);
		if (pmine->uid == uid)
		{
			pce->tag = AGC_MineType;
			pce->IGCPartType = ET_Dispenser;
			pce->usemask = pmine->usemask;
			pce->entry = (LPARAM)pmine;
			return pce;
		}
	}
	for (int i=0;i<cl_Probes.GetCount();i++)
	{
		PtrCoreProbe pprobe = cl_Probes.GetAt(i);
		if (pprobe->uid == uid)
		{
			pce->tag = AGC_ProbeType;
			pce->IGCPartType = ET_Dispenser;
			pce->usemask = pprobe->usemask;
			pce->entry = (LPARAM)pprobe;
			return pce;
		}
	}
	for (int i=0;i<cl_Missiles.GetCount();i++)
	{
		PtrCoreMissile pmis = cl_Missiles.GetAt(i);
		if (pmis->uid == uid)
		{
			pce->tag = AGC_MissileType;
			pce->IGCPartType = ET_Magazine;
			pce->usemask = pmis->use_flags;
			pce->entry = (LPARAM)pmis;
			return pce;
		}
	}
	delete pce;
	return NULL;
}
void CIGCCore::AddCiv(PtrCoreCiv pciv)
{
	if (!pciv) return;
	unsigned short uid;
	for (uid=1;uid<0xFFFF;uid++)
	{
		bool used = false;
		for (int j=0;j<cl_Civs.GetSize();j++)
		{
			PtrCoreCiv p = cl_Civs.GetAt(j);
			if (p->uid == uid) {
				used = true;
				break;
			}
		}
		if (!used) 
			break;
	}
	if (uid == 0xFFFF)
	{
		AfxMessageBox("No more available UID for factions");
		return;
	}
	pciv->uid = uid;
	cl_Civs.Add(pciv);
}

void CIGCCore::AddDevel(PtrCoreDevel pdevel)
{
	if (!pdevel) return;
	unsigned short uid;
	for (uid=1;uid<0xFFFF;uid++)
	{
		bool used = false;
		for (int j=0;j<cl_Devels.GetSize();j++)
		{
			PtrCoreDevel p = cl_Devels.GetAt(j);
			if (p->uid == uid) {
				used = true;
				break;
			}
		}
		if (!used) 
			break;
	}
	if (uid == 0xFFFF)
	{
		AfxMessageBox("No more available UID for devels");
		return;
	}
	pdevel->uid = uid;
	cl_Devels.Add(pdevel);
}
void CIGCCore::AddShip(PtrCoreShip pship)
{
	if (!pship) return;
	unsigned short uid;
	for (uid=1;uid<0xFFFF;uid++)
	{
		bool used = false;
		for (int j=0;j<cl_Ships.GetSize();j++)
		{
			PtrCoreShip p = cl_Ships.GetAt(j);
			if (p->uid == uid) {
				used = true;
				break;
			}
		}
		if (!used) 
			break;
	}
	if (uid == 0xFFFF)
	{
		AfxMessageBox("No more available UID for ships");
		return;
	}
	pship->uid = uid;
	cl_Ships.Add(pship);
}
void CIGCCore::AddStationType(PtrCoreStationType pstation)
{
	if (!pstation) return;
	unsigned short uid;
	for (uid=1;uid<0xFFFF;uid++)
	{
		bool used = false;
		for (int j=0;j<cl_StationTypes.GetSize();j++)
		{
			PtrCoreStationType p = cl_StationTypes.GetAt(j);
			if (p->uid == uid) {
				used = true;
				break;
			}
		}
		if (!used) 
			break;
	}
	if (uid == 0xFFFF)
	{
		AfxMessageBox("No more available UID for stations");
		return;
	}
	pstation->uid = uid;
	cl_StationTypes.Add(pstation);
}
void CIGCCore::AddDrone(PtrCoreDrone pdrone)
{
	if (!pdrone) return;
	unsigned short uid;
	for (uid=1;uid<0xFFFF;uid++)
	{
		bool used = false;
		for (int j=0;j<cl_Drones.GetSize();j++)
		{
			PtrCoreDrone p = cl_Drones.GetAt(j);
			if (p->uid == uid) {
				used = true;
				break;
			}
		}
		if (!used) 
			break;
	}
	if (uid == 0xFFFF)
	{
		AfxMessageBox("No more available UID for drones");
		return;
	}
	pdrone->uid = uid;
	cl_Drones.Add(pdrone);
}
void CIGCCore::AddProjectile(PtrCoreProjectile pproj)
{
	if (!pproj) return;
	unsigned short uid;
	for (uid=1;uid<0xFFFF;uid++)
	{
		bool used = false;
		for (int j=0;j<cl_Projectiles.GetSize();j++)
		{
			PtrCoreProjectile p = cl_Projectiles.GetAt(j);
			if (p->uid == uid) {
				used = true;
				break;
			}
		}
		if (!used) 
			break;
	}
	if (uid == 0xFFFF)
	{
		AfxMessageBox("No more available UID for projs");
		return;
	}
	pproj->uid = uid;
	cl_Projectiles.Add(pproj);
}
void CIGCCore::AddPart(PtrCorePart ppart)
{
	if (!ppart) return;
	unsigned short uid;
	for (uid=1;uid<0xFFFF;uid++)
	{
		bool used = false;
		for (int j=0;j<cl_Parts.GetSize();j++)
		{
			PtrCorePart p = cl_Parts.GetAt(j);
			if (p->uid == uid) {
				used = true;
				break;
			}
		}
		if (!used) 
			break;
	}
	if (uid == 0xFFFF)
	{
		AfxMessageBox("No more available UID for parts");
		return;
	}
	ppart->uid = uid;
	cl_Parts.Add(ppart);
}
void CIGCCore::AddMissile(PtrCoreMissile pmissile)
{
	if (!pmissile) return;
	unsigned short uid = ProxyPartUID();
	if (uid == 0xFFFF)
	{
		AfxMessageBox("No more available UID for missiles");
		return;
	}
	pmissile->uid = uid;
	cl_Missiles.Add(pmissile);
}
void CIGCCore::AddMine(PtrCoreMine pmine)
{
	if (!pmine) return;
	unsigned short uid = ProxyPartUID();
	if (uid == 0xFFFF)
	{
		AfxMessageBox("No more available UID for mines");
		return;
	}
	pmine->uid = uid;
	cl_Mines.Add(pmine);
}
void CIGCCore::AddCounter(PtrCoreCounter pcounter)
{
	if (!pcounter) return;
	unsigned short uid = ProxyPartUID();
	if (uid == 0xFFFF)
	{
		AfxMessageBox("No more available UID for counters");
		return;
	}
	pcounter->uid = uid;
	cl_Counters.Add(pcounter);
}
void CIGCCore::AddProbe(PtrCoreProbe pprobe)
{
	if (!pprobe) return;
	unsigned short uid = ProxyPartUID();
	if (uid == 0xFFFF)
	{
		AfxMessageBox("No more available UID for probes");
		return;
	}
	pprobe->uid = uid;
	cl_Probes.Add(pprobe);
}
unsigned short CIGCCore::ProxyPartUID(void)
{
	unsigned short uid;
	for (uid=1;uid<0xFFFF;uid++)
	{
		bool used = false;
		for (int j=0;j<cl_Missiles.GetSize();j++)
		{
			PtrCoreMissile p = cl_Missiles.GetAt(j);
			if (p->uid == uid) {
				used = true;
				break;
			}
		}
		for (int j=0;j<cl_Mines.GetSize();j++)
		{
			PtrCoreMine p = cl_Mines.GetAt(j);
			if (p->uid == uid) {
				used = true;
				break;
			}
		}
		for (int j=0;j<cl_Counters.GetSize();j++)
		{
			PtrCoreCounter p = cl_Counters.GetAt(j);
			if (p->uid == uid) {
				used = true;
				break;
			}
		}
		for (int j=0;j<cl_Probes.GetSize();j++)
		{
			PtrCoreProbe p = cl_Probes.GetAt(j);
			if (p->uid == uid) {
				used = true;
				break;
			}
		}
		if (!used) break;
	}
	return uid;
}
void CIGCCore::SortEntries(void)
{
	//parts
	for (int j=0;j<cl_Parts.GetSize();j++)
	{
		PtrCorePart p = cl_Parts.GetAt(j);
		if (p->overriding_uid != 0xFFFF)
		{
			for (int i=j+1;i<cl_Parts.GetSize();i++)
			{
				PtrCorePart pp = cl_Parts.GetAt(i);
				if (pp->uid == p->overriding_uid)
				{
					cl_Parts.SetAt(i,p);
					cl_Parts.SetAt(j,pp);
				}
			}
		}
	}
	//ships
	for (int j=0;j<cl_Ships.GetSize();j++)
	{
		PtrCoreShip p = cl_Ships.GetAt(j);
		if (p->overriding_uid != 0xFFFF)
		{
			for (int i=j+1;i<cl_Ships.GetSize();i++)
			{
				PtrCoreShip pp = cl_Ships.GetAt(i);
				if (pp->uid == p->overriding_uid)
				{
					cl_Ships.SetAt(i,p);
					cl_Ships.SetAt(j,pp);
				}
			}
		}
	}
	//stations
	for (int j=0;j<cl_StationTypes.GetSize();j++)
	{
		PtrCoreStationType p = cl_StationTypes.GetAt(j);
		if (p->overriding_uid != 0xFFFF)
		{
			for (int i=j+1;i<cl_StationTypes.GetSize();i++)
			{
				PtrCoreStationType pp = cl_StationTypes.GetAt(i);
				if (pp->uid == p->overriding_uid)
				{
					cl_StationTypes.SetAt(i,p);
					cl_StationTypes.SetAt(j,pp);
				}
			}
		}
	}
}
bool CIGCCore::MoveDevel(PtrCoreDevel pdevel,int dir)
{
	int curi = -1;
	for (int i=0;i<cl_Devels.GetCount();i++)
	{
		if (cl_Devels.GetAt(i) == pdevel)
			curi = i;
	}
	if (curi == -1)
		return false;
	int from;
	int stop;
	int step;
	switch (dir)
	{
		case 1:
			from = curi+1; stop = cl_Devels.GetCount(); step = 1;
			break;
		case -1:
			from = curi-1; stop = -1; step = -1;
			break;
		default:
			return false;
	}
	int imate = -1;
	PtrCoreDevel pmate = NULL;
	for (int i=from;i!=stop;i+=step)
	{
		pmate = cl_Devels.GetAt(i);
		if (pmate->root_tree == pdevel->root_tree)
		{
			imate = i; break;
		}
	}
	if (imate == -1)
		return false;
	cl_Devels.SetAt(curi,pmate);
	cl_Devels.SetAt(imate,pdevel);
	return true;
}
LPARAM CIGCCore::DeletePart(PtrCorePart ppart, bool realparttoo)
{
	if (!ppart) return NULL;
	unsigned short rp = 0xFFFF;
	PtrCoreEntry pce = NULL;
	if (ppart->isspec)
	{
		pce = ProxyPart(ppart->usemask);
	}
    int j=0;
	for (j=0;j<cl_Parts.GetSize();j++)
	{
		if (cl_Parts.GetAt(j) == ppart)
		{
			cl_Parts.RemoveAt(j);
			delete ppart;
			break;
		}
	}
	if ((pce !=NULL) & realparttoo)
	{
		switch(pce->tag)
		{
		case AGC_ProbeType:
			return DeleteProbe((PtrCoreProbe)pce->entry);
		case AGC_MineType:
			return DeleteMine((PtrCoreMine)pce->entry);
		case AGC_ChaffTypeOK:
			return DeleteCounter((PtrCoreCounter)pce->entry);
		case AGC_MissileType:
			return DeleteMissile((PtrCoreMissile)pce->entry);
		}
		delete pce;
	}
	if (cl_Parts.GetSize()==0)
		return (LPARAM)pConstants;
	else if (j<cl_Parts.GetSize())
		return (LPARAM)cl_Parts.GetAt(j);
	else
		return (LPARAM)cl_Parts.GetAt(0);
}
LPARAM CIGCCore::DeleteMine(PtrCoreMine pmine)
{
	if (!pmine) return NULL;
	PtrCorePart ppart = ProxyGet(pmine->uid);
	if (ppart) return DeletePart(ppart,true);
    int j=0;
	for (j=0;j<cl_Mines.GetSize();j++)
	{
		if (cl_Mines.GetAt(j) == pmine)
		{
			cl_Mines.RemoveAt(j);
			delete pmine;
			break;
		}
	}
	if (cl_Mines.GetSize()==0)
		return (LPARAM)pConstants;
	else if (j<cl_Mines.GetSize())
		return (LPARAM)cl_Mines.GetAt(j);
	else
		return (LPARAM)cl_Mines.GetAt(0);
}
LPARAM CIGCCore::DeleteCounter(PtrCoreCounter pcounter)
{
	if (!pcounter) return NULL;
	PtrCorePart ppart = ProxyGet(pcounter->uid);
	if (ppart) return DeletePart(ppart,true);
    int j=0;
	for (j=0;j<cl_Counters.GetSize();j++)
	{
		if (cl_Counters.GetAt(j) == pcounter)
		{
			cl_Counters.RemoveAt(j);
			delete pcounter;
			break;
		}
	}
	if (cl_Counters.GetSize()==0)
		return (LPARAM)pConstants;
	else if (j<cl_Counters.GetSize())
		return (LPARAM)cl_Counters.GetAt(j);
	else
		return (LPARAM)cl_Counters.GetAt(0);
}
LPARAM CIGCCore::DeleteMissile(PtrCoreMissile pmissile)
{
	if (!pmissile) return NULL;
	PtrCorePart ppart = ProxyGet(pmissile->uid);
	if (ppart) return DeletePart(ppart,true);
    int j=0;
	for (j=0;j<cl_Missiles.GetSize();j++)
	{
		if (cl_Missiles.GetAt(j) == pmissile)
		{
			cl_Missiles.RemoveAt(j);
			delete pmissile;
			break;
		}
	}
	if (cl_Missiles.GetSize()==0)
		return (LPARAM)pConstants;
	else if (j<cl_Missiles.GetSize())
		return (LPARAM)cl_Missiles.GetAt(j);
	else
		return (LPARAM)cl_Missiles.GetAt(0);
}
LPARAM CIGCCore::DeleteProbe(PtrCoreProbe pprobe)
{
	if (!pprobe) return NULL;
	PtrCorePart ppart = ProxyGet(pprobe->uid);
	if (ppart) return DeletePart(ppart,true);
    int j=0;
	for (j=0;j<cl_Probes.GetSize();j++)
	{
		if (cl_Probes.GetAt(j) == pprobe)
		{
			cl_Probes.RemoveAt(j);
			delete pprobe;
			break;
		}
	}
	if (cl_Probes.GetSize()==0)
		return (LPARAM)pConstants;
	else if (j<cl_Probes.GetSize())
		return (LPARAM)cl_Probes.GetAt(j);
	else
		return (LPARAM)cl_Probes.GetAt(0);
}
LPARAM CIGCCore::DeleteCiv(PtrCoreCiv pciv)
{
    int j=0;
	for (j=0;j<cl_Civs.GetSize();j++)
	{
		if (cl_Civs.GetAt(j) == pciv)
		{
			cl_Civs.RemoveAt(j);
			delete pciv;
			break;
		}
	}
	if (cl_Civs.GetSize()==0)
		return (LPARAM)pConstants;
	else if (j<cl_Civs.GetSize())
		return (LPARAM)cl_Civs.GetAt(j);
	else
		return (LPARAM)cl_Civs.GetAt(0);
}
LPARAM CIGCCore::DeleteDevel(PtrCoreDevel pdevel)
{
    int j=0;
	for (j=0;j<cl_Devels.GetSize();j++)
	{
		if (cl_Devels.GetAt(j) == pdevel)
		{
			cl_Devels.RemoveAt(j);
			delete pdevel;
			break;
		}
	}
	if (cl_Devels.GetSize()==0)
		return (LPARAM)pConstants;
	else if (j<cl_Devels.GetSize())
		return (LPARAM)cl_Devels.GetAt(j);
	else
		return (LPARAM)cl_Devels.GetAt(0);
}
LPARAM CIGCCore::DeleteDrone(PtrCoreDrone pdrone)
{
    int j=0;
	for (j=0;j<cl_Drones.GetSize();j++)
	{
		if (cl_Drones.GetAt(j) == pdrone)
		{
			cl_Drones.RemoveAt(j);
			delete pdrone;
			break;
		}
	}
	if (cl_Drones.GetSize()==0)
		return (LPARAM)pConstants;
	else if (j<cl_Drones.GetSize())
		return (LPARAM)cl_Drones.GetAt(j);
	else
		return (LPARAM)cl_Drones.GetAt(0);
}
LPARAM CIGCCore::DeleteProjectile(PtrCoreProjectile pproj)
{
    int j=0;
	for (j=0;j<cl_Projectiles.GetSize();j++)
	{
		if (cl_Projectiles.GetAt(j) == pproj)
		{
			cl_Projectiles.RemoveAt(j);
			delete pproj;
			break;
		}
	}
	if (cl_Projectiles.GetSize()==0)
		return (LPARAM)pConstants;
	else if (j<cl_Projectiles.GetSize())
		return (LPARAM)cl_Projectiles.GetAt(j);
	else
		return (LPARAM)cl_Projectiles.GetAt(0);
}
LPARAM CIGCCore::DeleteShip(PtrCoreShip pship)
{
    int j=0;
	for (j=0;j<cl_Ships.GetSize();j++)
	{
		if (cl_Ships.GetAt(j) == pship)
		{
			cl_Ships.RemoveAt(j);
			delete pship;
			break;
		}
	}
	if (cl_Ships.GetSize()==0)
		return (LPARAM)pConstants;
	else if (j<cl_Ships.GetSize())
		return (LPARAM)cl_Ships.GetAt(j);
	else
		return (LPARAM)cl_Ships.GetAt(0);
}
LPARAM CIGCCore::DeleteStationType(PtrCoreStationType pstation)
{
    int j=0;
	for (j=0;j<cl_StationTypes.GetSize();j++)
	{
		if (cl_StationTypes.GetAt(j) == pstation)
		{
			cl_StationTypes.RemoveAt(j);
			delete pstation;
			break;
		}
	}
	if (cl_StationTypes.GetSize()==0)
		return (LPARAM)pConstants;
	else if (j<cl_StationTypes.GetSize())
		return (LPARAM)cl_StationTypes.GetAt(j);
	else
		return (LPARAM)cl_StationTypes.GetAt(0);
}


bool CIGCCore::SaveDepList(CString fn)
{
    CFile cfcore;
	if (!cfcore.Open(fn,CFile::modeCreate|CFile::modeReadWrite))
	{
		// handle errors
		return false;
	}

	SortEntries();

	// Projectiles
	for (int j=0;j<cl_Projectiles.GetSize();j++)
	{
		PtrCoreProjectile pprojectile = cl_Projectiles.GetAt(j);
		//cfcore.Write(pprojectile->file_texture+"bmp.mdl\n");
	}

	// Missiles
	for (int j=0;j<cl_Missiles.GetSize();j++)
	{
		PtrCoreMissile pmissile = cl_Missiles.GetAt(j);
		//cfcore.Write(pmissile->icon+"bmp.mdl\n");
	}

	// Counters
	for (int j=0;j<cl_Counters.GetSize();j++)
	{
		PtrCoreCounter pcounter = cl_Counters.GetAt(j);
		//cfcore.Write(pcounter->icon+"bmp.mdl\n");
	}
	
	// Mines
	for (int j=0;j<cl_Mines.GetSize();j++)
	{
		PtrCoreMine pmine = cl_Mines.GetAt(j);
		//cfcore.Write(pmine->icon+"bmp.mdl\n");
	}

	// Probes
	for (int j=0;j<cl_Probes.GetSize();j++)
	{
		PtrCoreProbe pprobe = cl_Probes.GetAt(j);
		//cfcore.Write(pprobe->icon+"bmp.mdl\n");
	}

	// Parts
	for (int j=0;j<cl_Parts.GetSize();j++)
	{
		PtrCorePart ppart = cl_Parts.GetAt(j);
		if (ppart->isspec)
		{
			//cfcore.Write(ppart->slot+".mdl\n"); // txt mdl
		}
		else
		{
			//cfcore.Write(ppart->icon+"bmp.mdl\n");
			//cfcore.Write(ppart->model+".mdl\n");
			//cfcore.Write(ppart->icon+"bmp.mdl\n");
		}
	}

	// Hulls (Ships)
	for (int j=0;j<cl_Ships.GetSize();j++)
	{
		PtrCoreShip pship = cl_Ships.GetAt(j);
	}

	// Devels
	for (int j=0;j<cl_Devels.GetSize();j++)
	{
		PtrCoreDevel pdevel = cl_Devels.GetAt(j);
	}

	// Drones
	for (int j=0;j<cl_Drones.GetSize();j++)
	{
		PtrCoreDrone pdrone = cl_Drones.GetAt(j);
	}

	// Stations
	for (int j=0;j<cl_StationTypes.GetSize();j++)
	{
		PtrCoreStationType pstation = cl_StationTypes.GetAt(j);
	}

	// TreasureSets
	for (int j=0;j<cl_TreasureSets.GetSize();j++)
	{
		PtrCoreTreasureSet ptreasureSet = cl_TreasureSets.GetAt(j);
	}

	// Civs
	for (int j=0;j<cl_Civs.GetSize();j++)
	{
		PtrCoreCiv pCiv = cl_Civs.GetAt(j);
	}

	// write the total size and close
	cfcore.Close();
	return true;
}

// finders
PtrCoreStationType CIGCCore::FindStationType(short uid)
{
	if (uid==-1) return NULL;
	// Stations
	for (int j=0;j<cl_StationTypes.GetSize();j++)
	{
		PtrCoreStationType pstation = cl_StationTypes.GetAt(j);
		if (pstation->uid == uid) return pstation;
	}
	return NULL;
}
PtrCoreCiv CIGCCore::FindCiv(short uid)
{
	if (uid==-1) return NULL;
	// Civs
	for (int j=0;j<cl_Civs.GetSize();j++)
	{
		PtrCoreCiv pCiv = cl_Civs.GetAt(j);
		if (pCiv->uid == uid) return pCiv;
	}
	return NULL;
}
PtrCoreDevel CIGCCore::FindDevel(short uid)
{
	if (uid==-1) return NULL;
	// Devels
	for (int j=0;j<cl_Devels.GetSize();j++)
	{
		PtrCoreDevel pdevel = cl_Devels.GetAt(j);
		if (pdevel->uid == uid) return pdevel;
	}
	return NULL;
}
PtrCoreProbe CIGCCore::FindProbe(short uid)
{
	if (uid==-1) return NULL;
	// Probes
	for (int j=0;j<cl_Probes.GetSize();j++)
	{
		PtrCoreProbe pprobe = cl_Probes.GetAt(j);
		if (pprobe->uid == uid) return pprobe;
	}
	return NULL;
}
PtrCoreMissile CIGCCore::FindMissile(short uid)
{
	if (uid==-1) return NULL;
	// Missiles
	for (int j=0;j<cl_Missiles.GetSize();j++)
	{
		PtrCoreMissile pmissile = cl_Missiles.GetAt(j);
		if (pmissile->uid == uid) return pmissile;
	}
	return NULL;
}
PtrCoreCounter CIGCCore::FindCounter(short uid)
{
	if (uid==-1) return NULL;
	// Counters
	for (int j=0;j<cl_Counters.GetSize();j++)
	{
		PtrCoreCounter pcounter = cl_Counters.GetAt(j);
		if (pcounter->uid == uid) return pcounter;
	}
	return NULL;
}
PtrCoreMine CIGCCore::FindMine(short uid)
{
	if (uid==-1) return NULL;
	// Mines
	for (int j=0;j<cl_Mines.GetSize();j++)
	{
		PtrCoreMine pmine = cl_Mines.GetAt(j);
		if (pmine->uid == uid) return pmine;
	}
	return NULL;
}
PtrCorePart CIGCCore::FindPart(short uid)
{
	if (uid==-1) return NULL;
	for (int j=0;j<cl_Parts.GetSize();j++)
	{
		PtrCorePart ppart = cl_Parts.GetAt(j);
		if (ppart->uid == uid) return ppart;
	}
	return NULL;
}
PtrCoreShip CIGCCore::FindShip(short uid)
{
	if (uid==-1) return NULL;
	// Hulls (Ships)
	for (int j=0;j<cl_Ships.GetSize();j++)
	{
		PtrCoreShip pship = cl_Ships.GetAt(j);
		if (pship->uid == uid) return pship;
	}
	return NULL;
}
PtrCoreProjectile CIGCCore::FindProjectile(short uid)
{
	if (uid==-1) return NULL;
	// Projectiles
	for (int j=0;j<cl_Projectiles.GetSize();j++)
	{
		PtrCoreProjectile pp = cl_Projectiles.GetAt(j);
		if (pp->uid == uid) return pp;
	}
	return NULL;
}
PtrCoreDrone CIGCCore::FindDrone(short uid)
{
	if (uid==-1) return NULL;
	// Drones
	for (int j=0;j<cl_Drones.GetSize();j++)
	{
		PtrCoreDrone pdrone = cl_Drones.GetAt(j);
		if (pdrone->uid == uid) return pdrone;
	}
	return NULL;
}


LPARAM CIGCCore::BuildError(LPARAM p,char *szReason, char **pszReason)
{
	*pszReason = szReason;
	return p;
}
LPARAM CIGCCore::FindError(char **pszReason)
{
	// Civs
	for (int j=0;j<cl_Civs.GetSize();j++)
	{
		PtrCoreCiv pciv = cl_Civs.GetAt(j);
		PtrCoreStationType pgar = FindStationType(pciv->gar_uid);
		if (!pgar) 
			return BuildError((LPARAM)pciv,"invalid Garrison ID",pszReason);
		PtrCoreShip ppod = FindShip(pciv->lifepod_uid);
		if (!ppod) 
			return BuildError((LPARAM)pciv,"invalid LifePod ID",pszReason);
	}
	// Drones
	for (int j=0;j<cl_Drones.GetSize();j++)
	{
		PtrCoreDrone pdrone = cl_Drones.GetAt(j);
		if (pdrone->ss1 == 5)
		{
			PtrCoreEntry prox = ProxyPart(pdrone->part_uid);
			if (!prox) 
				return BuildError((LPARAM)pdrone,"invalid Part UID",pszReason);
			delete prox;
		}
		else
		{
			if (pdrone->part_uid != -1) 
				return BuildError((LPARAM)pdrone,"Part UID shoud be -1",pszReason);
		}
	}
	// Parts
	for (int j=0;j<cl_Parts.GetSize();j++)
	{
		PtrCorePart ppart = cl_Parts.GetAt(j);
		if (ppart->overriding_uid != -1)
		{
			PtrCorePart pover = FindPart(ppart->overriding_uid);
			if (!pover)
			{
				if (ppart->isspec)
				{
					PtrCoreEntry prox = ProxyPart(ppart->usemask);
					if (!prox) BuildError((LPARAM)ppart,"Invalid part (fatal error)",pszReason);
					LPARAM p = prox->entry;
					delete prox;
					if (p)
						return BuildError(p,"Invalid successor (overided by)",pszReason);
				}
				else
					return BuildError((LPARAM)ppart,"Invalid successor (overided by)",pszReason);
			}
		}
		if (ppart->isspec) continue;
		if (ppart->type == AGCEquipmentType_Weapon)
		{
			PtrCoreProjectile pp = FindProjectile(ppart->specs.wep.wep_projectile_uid);
			if (!pp) return BuildError((LPARAM)ppart,"Invalid weapon projectile",pszReason);
		}
	}
	// Probes
	for (int j=0;j<cl_Probes.GetSize();j++)
	{
		PtrCoreProbe pprobe = cl_Probes.GetAt(j);
		if (pprobe->stats_projectile != -1)
		{
			PtrCoreProjectile pp = FindProjectile(pprobe->stats_projectile);
			if (!pp) return BuildError((LPARAM)pprobe,"Invalid probe projectile",pszReason);
		}
	}

	// Ships
	for (int j=0;j<cl_Ships.GetSize();j++)
	{
		PtrCoreShip pship = cl_Ships.GetAt(j);
		if (pship->overriding_uid != -1)
		{
			PtrCoreShip pover = FindShip(pship->overriding_uid);
			if (!pover) return BuildError((LPARAM)pship,"Invalid successor (overided by)",pszReason);
		}

	}
	return NULL;
}