// ==========================================================
// IGC Core IO
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

#include "StdAfx.h"
#include "Resource.h"
#include "corestruct.h"


bool CIGCCore::SaveAsText(CString filepath)
{
	CStdioFile ctmp;
	CString stmp;

	try
	{
		ctmp.Open(filepath,CFile::modeCreate|CFile::modeReadWrite);
	}
	catch(char * str)
	{
		AfxMessageBox(str);
		return false;
	}
	SortEntries();
	// globals
	CString ConstLabs[c_fcidMax];
	CStdioFile cf; cf;
	if (cf.Open("ice.ini",CFile::modeRead))
	{
		for (int i=0;i<c_fcidMax;i++)
		{
			cf.ReadString(ConstLabs[i]);
			ConstLabs[i] = ConstLabs[i].Trim();
		}
		cf.Close();
	}
	else
	{
		for (int i=0;i<c_fcidMax;i++) ConstLabs[i].Format("Global%02d",i);
	}
	for (int i=0;i<c_fcidMax;i++)
	{
		stmp.Format("%-25s = %f\n",ConstLabs[i],pConstants->floatConstants[i]);
		ctmp.WriteString(stmp);
	}
	// DM/AC
	for (int i=0;i<20;i++)
	{
		for (int j=0;j<20;j++)
		{
			stmp.Format("DM%02d/AC%02d = %f\n",i,j,pConstants->damageConstants[i][j]);
			ctmp.WriteString(stmp);
		}
	}
	// Projectiles
	for (int j=0;j<cl_Projectiles.GetSize();j++)
	{
		PtrCoreProjectile p = cl_Projectiles.GetAt(j);
		stmp.Format("Projectile %d:\n",p->projectileTypeID);
		stmp.AppendFormat("\tpercentRed = %f\n", p->color.r);
		stmp.AppendFormat("\tpercentGreen = %f\n", p->color.g);
		stmp.AppendFormat("\tpercentBlue = %f\n", p->color.b);
		stmp.AppendFormat("\tpercentAlpha = %f\n", p->color.a);
		stmp.AppendFormat("\tradius = %f\n", p->radius); // particle size (radius)
		stmp.AppendFormat("\trotation = %f\n", p->rotation); // rate rotation (?)
		stmp.AppendFormat("\tmodel = %s\n",  p->modelName); // ALL '0' = file model
		stmp.AppendFormat("\ttexture = %s\n",  p->textureName); // = file texture
		stmp.AppendFormat("\tpower = %f\n", p->power); // regular damange per shot
		stmp.AppendFormat("\tarea dmg = %f\n", p->blastPower); // area damange per shot
		stmp.AppendFormat("\tarea radius = %f\n", p->blastRadius); // area damage radius
		stmp.AppendFormat("\tspeed = %f\n", p->speed); // speed
		stmp.AppendFormat("\tduratin = %f\n", p->lifespan); // life span
		stmp.AppendFormat("\tDM = %02d\n", p->damageType);
		stmp.AppendFormat("\tabsolute speed = %d\n", p->absoluteF); // absolute speed = 1
		stmp.AppendFormat("\tdirectional = %d\n", p->bDirectional); // directional = 1
		stmp.AppendFormat("\tWidth  = %f\n", p->width); // Width OverHeigth
		stmp.AppendFormat("\tambient_sound = %d\n", p->ambientSound);
		ctmp.WriteString(stmp);
	}
	// Missiles
	for (int j=0;j<cl_Missiles.GetSize();j++)
	{
		PtrCoreMissile p = cl_Missiles.GetAt(j);
	}

	// Counters
	for (int j=0;j<cl_Counters.GetSize();j++)
	{
		PtrCoreCounter p = cl_Counters.GetAt(j);
	}
	
	// Mines
	for (int j=0;j<cl_Mines.GetSize();j++)
	{
		PtrCoreMine p = cl_Mines.GetAt(j);
	}

	// Probes
	for (int j=0;j<cl_Probes.GetSize();j++)
	{
		PtrCoreProbe p = cl_Probes.GetAt(j);
	}


	ctmp.Close();
	return true;
}
bool CIGCCore::SaveAsXML(CString filepath)
{
	return false;
}
