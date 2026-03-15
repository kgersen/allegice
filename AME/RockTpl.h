#pragma once
#include "mapstruct.h"

#define ROCKTPLMAX 3
const CString RockTplNames[ROCKTPLMAX] = {"Asteroid","Helium","Tech rocks"};
const unsigned short RockTplTypes[ROCKTPLMAX] = 
{	IGCROCK_IS_ASTERIOD,
	IGCROCK_IS_HELIUM,
	IGCROCK_IS_URANIUM|IGCROCK_IS_SILICON|IGCROCK_IS_CARBON|IGCROCK_IS_THORIUM
};
/* server code reference
static const AsteroidTypeRow asteroidTypes[] = 
{
    { "asteroid",       "\0a",  { 0.0f, 0,        0,                      0, 25000, 400,  "bgrnd03", "", "meteoricon" } },
    { "asteroid",       "\0a",  { 0.0f, 0,        0,                      0, 25000, 400,  "bgrnd05", "", "meteoricon" } },
    { "asteroid",       "\0a",  { 0.0f, 0,        c_aabmBuildable,        0, 10000, 200,  "bgrnd03", "", "meteoricon" } },
    { "asteroid",       "\0a",  { 0.0f, 0,        c_aabmBuildable,        0, 10000, 200,  "bgrnd05", "", "meteoricon" } },
    { "Helium 3",       "He",   { 1.0f, 1.0f,     c_aabmMineHe3,          0, 25000, 100,  "bgrnd56", "", "heliumrock" } },
    { "Uranium",        "U",    { 0.0f, 0,        (c_aabmSpecial << 0),   0, 25000, 200,  "bgrnd51", "", "hotrock"    } },
    { "Silicon",        "Si",   { 0.0f, 0,        (c_aabmSpecial << 1),   0, 25000, 200,  "bgrnd52", "", "copperrock" } },
    { "Carbonaceous",   "C",    { 0.0f, 0,        (c_aabmSpecial << 2),   0, 25000, 200,  "bgrnd53", "", "carbonrock" } }
};
*/
const unsigned short RockTplRadiusMin[ROCKTPLMAX] = {200,100,200};
const unsigned short RockTplRadiusMax[ROCKTPLMAX] = {400,200,400};
const float RockTplHPFact[ROCKTPLMAX] = {10000/100,25000/200,25000/400};
const float RockTplSigFact[ROCKTPLMAX] = {.01f,.01f,.01f}; // KG 6/8/8 
class CRockTpl
{
public:
	CRockTpl(void);
	CRockTpl & operator=( CRockTpl & );
	CString Names[ROCKTPLMAX];
	unsigned short Types[ROCKTPLMAX];
	float sig[ROCKTPLMAX];
	float hitpoints[ROCKTPLMAX];
	BOOL sig_size[ROCKTPLMAX];
	BOOL hp_size[ROCKTPLMAX];
	float sig_fact[ROCKTPLMAX];
	float hitpoints_fact[ROCKTPLMAX];
	unsigned short radius[ROCKTPLMAX];
	BOOL random_radius[ROCKTPLMAX];
	int radius_min[ROCKTPLMAX];
	int radius_max[ROCKTPLMAX];
	BOOL radius_Included[ROCKTPLMAX];
	BOOL hp_Included[ROCKTPLMAX];
	BOOL sig_Included[ROCKTPLMAX];
	~CRockTpl(void);
	float GenSig(int,unsigned short);
	float GenHP(int,unsigned short);
	unsigned short GenRadius(int);
};
