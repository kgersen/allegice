#include "StdAfx.h"
#include "rocktpl.h"

CRockTpl::CRockTpl(void)
{
	for (int i=0;i<ROCKTPLMAX;i++)
	{
		Names[i] = RockTplNames[i];
		Types[i] = RockTplTypes[i];
		sig_fact[i] = RockTplSigFact[i];
		hitpoints_fact[i] = RockTplHPFact[i];
		radius_min[i] = RockTplRadiusMin[i];
		radius_max[i] = RockTplRadiusMax[i];
		sig_size[i] = TRUE;
		hp_size[i] = TRUE;
		random_radius[i] = TRUE;
		radius_Included[i] = FALSE;
		hp_Included[i] = FALSE;
		sig_Included[i] = FALSE;

		radius[i] = 200;
		hitpoints[i] = GenHP(i,radius[i]);
		sig[i] = GenSig(i,radius[i]);
	}
}

CRockTpl::~CRockTpl(void)
{
}

CRockTpl & CRockTpl::operator=( CRockTpl &other )
{
	for (int i=0;i<ROCKTPLMAX;i++)
	{
		Names[i] = other.Names[i];
		Types[i] = other.Types[i];
		sig_fact[i] = other.sig_fact[i];
		hitpoints_fact[i] = other.hitpoints_fact[i];
		radius_min[i] = other.radius_min[i];
		radius_max[i] = other.radius_max[i];
		sig_size[i] = other.sig_size[i];
		hp_size[i] = other.hp_size[i];
		random_radius[i] = other.random_radius[i];
		radius[i] = other.radius[i];
		sig[i] = other.sig[i];
		hitpoints[i] = other.hitpoints[i];
		hp_Included[i] = other.hp_Included[i];
		radius_Included[i] = other.radius_Included[i];
		sig_Included[i] = other.sig_Included[i];
	}
	return *this;
}
float CRockTpl::GenSig(int i, unsigned short r)
{
	if (sig_size[i])
		return sig_fact[i] * r;
	else
		return sig[i];
}
float CRockTpl::GenHP(int i, unsigned short r)
{
	if (hp_size[i])
		return hitpoints_fact[i] * r;
	else
		return hitpoints[i];
}
unsigned short CRockTpl::GenRadius(int i)
{
	if (random_radius[i])
		return (rand() * (radius_max[i]-radius_min[i])) / RAND_MAX + radius_min[i];
	else
		return radius[i];
}