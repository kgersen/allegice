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

#include <afxtempl.h>
#pragma once
#pragma pack(1)

#define AGC_ChaffTypeOK 26

// for reference, IGC sizes
// These constants correspond to the maximum length of a file name or a 
// player name. They should correspond to the maximum lengths in the SQL 
// database (for Name and FileName custom data types). Longer names are 
// handled via truncation. DB versions do not include the NULL terminator
//const int c_cbFileNameDB    = 12; // keep in sync with 
//const int c_cbDescriptionDB = 200;
//const int c_cbNameDB        = 24;
//const int c_cbLocAbrevDB    = 8;
//const int c_cbFileName      = c_cbFileNameDB    + 1;
//const int c_cbDescription   = c_cbDescriptionDB + 1;
//const int c_cbName          = c_cbNameDB        + 1;
//const int c_cbLocAbrev      = c_cbLocAbrevDB    + 1;
//const int c_cbCDKey         = 32 + 1; // TODO: fill in the correct length
//const int c_cbPassportName  = 256 + 1;
//

// max length for string
#define IGC_NAMEMAX 25
#define IGC_DESCRIPTIONMAX 200

#define IGCNUMC 40
typedef struct SIGCCoreConstants // tag=0x22 size=440*4
{
	float constants[IGCNUMC];
	float damages[20][20];
} IGCCoreConstants;
#define IGCCPROSPERITY 12

#define IGCDMMAX 20
#define IGCACMAX 20
const CString IGCArmorClasses[IGCACMAX] = {
"asteroid","light","medium","heavy",
"extra heavy","utility","minor base hull","major base hull",
"lt/med shld","minor base shld","major base shld","parts",
"lt base hull","lt base shld","large shield","AC15",
"AC16","AC17","AC18","AC19"
};
typedef IGCCoreConstants * PtrCoreConstants;

#define IGCSTATIONF_CAPSCANDOCK 128
#define IGCSTATIONF_STARTINGBASE 64

#define IGCSTATIONF_BUILDON_HELIUM 1
#define IGCSTATIONF_BUILDON_THORIUM 4
#define IGCSTATIONF_BUILDON_ASTERIOD 8
#define IGCSTATIONF_BUILDON_URANIUM 16
#define IGCSTATIONF_BUILDON_SILICON 32
#define IGCSTATIONF_BUILDON_CARBON 64

// type is class in fact, used for capture equivalence
#define IGCSTATION_TYPE_GARRISON 0
#define IGCSTATION_TYPE_OUTPOST  1 
#define IGCSTATION_TYPE_SHIPYARD 2
#define IGCSTATION_TYPE_TELEPORT 3
#define IGCSTATION_TYPE_REFINERY 4
#define IGCSTATION_TYPE_EXPANSION 5
#define IGCSTATION_TYPE_SUPREMACY 6
#define IGCSTATION_TYPE_TACTICAL 7
#define IGCSTATION_TYPE_PLATFORM 8
#define IGCSTATION_TYPE_URANIUMMINE 9
#define IGCSTATION_TYPE_CARBONMINE 10
#define IGCSTATION_TYPE_SILICONMINE 11
#define IGCSTATION_TYPE_NBVALS 20 // 12 in fact, 13 is for 'test'
const CString IGCStationTypeNames[IGCSTATION_TYPE_NBVALS] = 
{
	"Garrison","Outpost","Shipyard","Teleport","Refinery",
	"Expansion","Supremacy","Tactical","Platform",
	"Mine: Uranium","Mine: Carbon","Mine: Silicon",
	"Custom1",
	"Custom2",
	"Custom3",
	"Custom4",
	"Custom5",
	"Custom6",
	"Custom7",
	"Custom8",
};
/*
const StationAbilityBitMask     c_sabmUnload                = 0x01;      //Ability to offload mined minerals
const StationAbilityBitMask     c_sabmStart                 = 0x02;      //           start the game at this station
const StationAbilityBitMask     c_sabmRestart               = 0x04;      //           restart after dying
const StationAbilityBitMask     c_sabmRipcord               = 0x08;      //           teleport to the station
const StationAbilityBitMask     c_sabmCapture               = 0x10;      //           be captured
const StationAbilityBitMask     c_sabmLand                  = 0x20;      //           land at
const StationAbilityBitMask     c_sabmRepair                = 0x40;      //           get repaired
const StationAbilityBitMask     c_sabmRemoteLeadIndicator   = 0x80;      //           shows up in the loadout menu of stations
const StationAbilityBitMask     c_sabmReload                = 0x100;     //           free fuel and ammo on launch
const StationAbilityBitMask     c_sabmFlag                  = 0x200;     //           counts for victory
const StationAbilityBitMask     c_sabmPedestal              = 0x400;     //           be a pedestal for a flag
const StationAbilityBitMask     c_sabmTeleportUnload        = 0x800;     //           be a pedestal for a flag
const StationAbilityBitMask     c_sabmCapLand               = 0x1000;    //           land capital ships
const StationAbilityBitMask     c_sabmRescue                = 0x2000;    //           rescue pods
const StationAbilityBitMask     c_sabmRescueAny             = 0x4000;    //           not used (but reserved for pods)
*/
typedef struct SIGCCoreStationType //
{
	AGCMoney cost;
	AGCMoney research_time;
	char model[13];
	char pad1;//CC or 00
	char icon[13];
	char name[25];
	char description[200];
	BYTE group;
	BYTE zero;
	UCHAR techtree[100];
	char pad2[2]; // CD CD
	float stats_s1; // sig multiplier
	float stats_s2; // hull
	float stats_s3; // shield
	float stats_s4; // hull repair rate
	float stats_s5; // shield repair rate
	float stats_s6; // scan range
	AGCMoney stats_income;
	float stats_s7; // scale
	UCHAR TechTreeLocal[50];
	/* was :
	UCHAR pad3[12];// all 00
	long dockable; // 0x10 if dockable, 0 otherwise
	UCHAR pad4[13];// all 00
	UCHAR stats_isgar;// 1 = yes , 0 otherwise
	UCHAR stats_flags; // 128 = capital can dock, 64 = starting base (gar) (TBC)
	UCHAR stats_dockable; // = 1 if dockable, 0 otherwise
	UCHAR pad5[18];// all 00
	*/
	unsigned short uid;
	short overriding_uid;
	UCHAR ACHull;
	UCHAR ACShld;
	unsigned short AbilityBitMask; // (as in igc.h)
	/* was:
	  UCHAR stats_sh2; // StationAbilityBitMask (low)
	  UCHAR stats_sh3; // StationAbilityBitMask (high)
	*/
	unsigned short buildon; // see IGCSTATIONF_BUILDON_* values
	UCHAR type; // see IGCSTATION_TYPE_* value - capture related ?
	UCHAR pad6; // CD
	unsigned short stats_ss0; // drone uid
	unsigned short Sounds[13];
	UCHAR uk3[13];//3*16+1-6-2-28
	char constructor[25];
} IGCCoreStationType;
typedef IGCCoreStationType * PtrCoreStationType;

#define IGCF_ShipSpeed             0
#define IGCF_ShipAcceleration      1
#define IGCF_ShipAgility1          2
#define IGCF_ShipAgility2          3
#define IGCF_StationHull1          4
#define IGCF_StationHull2          5
#define IGCF_StationShield1        6
#define IGCF_StationShield2        7
#define IGCF_ShipHull              8
#define IGCF_ShipShield1           9
#define IGCF_ShipShield2          10
#define IGCF_ShipSensors          11
#define IGCF_ShipSignature        12
#define IGCF_ShipEnergy           13
#define IGCF_PWRange              14
#define IGCF_EWRange              15
#define IGCF_MissileTrack         16
#define IGCF_He3Speed             17
#define IGCF_He3Yield             18
#define IGCF_UNKNOWN              19    // To Be Confirmed: starting money
#define IGCF_Ripcord              20
#define IGCF_PWDamage             21
#define IGCF_MissileDamage        22
#define IGCF_Cost                 23
#define IGCF_ResearchTime         24

typedef struct SIGCCoreCiv // size = 268
{
	float ukf[2]; // 0=starting money modifier,1=bonus money
	char name[25];
	char model[13];
	char obj[13];
	UCHAR techtree[101];// first = 02
	float factors[25];
	unsigned short lifepod_uid; // lifepod ID
	unsigned short uid;
	unsigned short gar_uid; // uid in StationType (or last "base" uid)
	CHAR end[2]; // CD CD
} IGCCoreCiv;
typedef IGCCoreCiv * PtrCoreCiv;

typedef struct SIGCCoreDevel // size = 468 0x1D4, tag = 0x20
{
	UINT cost;
	UINT research_time;
	char model[13];
	UCHAR uk1; // cc
	char icon[13]; // always 'icontech'
	char name[25];
	char description[200];
	UCHAR pad1;//00
	UCHAR root_tree;// tree root (0=construction,1=garrison,2=sup,3=tac,4=exp,5=sy)
	UCHAR techtree[100];
	UCHAR pad2[2]; // cd cd
	float factors[25];//
	unsigned short uid;
	unsigned short cat; // sound
} IGCCoreDevel;
typedef IGCCoreDevel *PtrCoreDevel;
#define IGCHullAbility_Board			1
#define IGCHullAbility_Rescue			2
#define IGCHullAbility_Lifepod			4
#define IGCHullAbility_NoPickup			8
#define IGCHullAbility_NoEjection		16
#define IGCHullAbility_NoRipcord		32
#define IGCHullAbility_IsRip			64
#define IGCHullAbility_Fighter			128
#define IGCHullAbility_Captital			256
#define IGCHullAbility_F2				(2*256)
#define IGCHullAbility_IsDock			(4*256)
#define IGCHullAbility_F8				(8*256)
#define IGCHullAbility_IsSmallRip		(16*256)
#define IGCHullAbility_RipToSmallRip    (32*256)
#define IGCHullAbility_IsMiner			(64*256)
#define IGCHullAbility_IsConstructor	(128*256)

typedef struct SIGCCoreShipMP // size 30
{
	unsigned short uk1; // sound
	unsigned short uk2; // sound
	char position[13];
	UCHAR todo[9];//30 00 .. 00
	unsigned short part_mask;//usemask of weapon
	unsigned short part_type;//1=normal, 0=other player (turret).
} IGCCoreShipMP;
#define IGCSHIPMAXPARTS 14
#define IGCSHIPMAXUSE 8
#define IGCSHIPMAXWEAPONS 20
const CString IGCShipUseMasks[IGCSHIPMAXUSE]=
{
	"Counter",	"*",
		"Missile", "Pack","Shield","Cloak","*","Afterburner",
};
typedef short     EquipmentType; // this is PartTypeID in the database
const EquipmentType   ET_ChaffLauncher  = 0;
const EquipmentType   ET_Weapon         = 1;
const EquipmentType   ET_Magazine       = 2; // missiles
const EquipmentType   ET_Dispenser      = 3; // mines & probes
const EquipmentType   ET_Shield         = 4;
const EquipmentType   ET_Cloak          = 5;
const EquipmentType   ET_Pack           = 6; // ammo & fuel
const EquipmentType   ET_Afterburner    = 7;
const EquipmentType   ET_MAX            = 8;

typedef struct SIGCCoreShip // tag = 1D, size = 540 to 690
{
	AGCMoney cost;
	BYTE header[4]; // all zero
	char model[13];
	BYTE pad1; // CC
	char icon[13];
	char name[25];
	char description[200]; // check len
	BYTE zero;
	char group; 
	UCHAR techtree[100];
	BYTE pad2[2]; //00 00
	float stats_s1; // mass
	float stats_s2; // sig%
	float stats_s3; // speed
	float stats_s4; // SAX = MaxRollRate in radians
	float stats_s5; // SAY = MaxPitchRate in radians
	float stats_s6; // SAZ = MaxYawRate in radians
	float stats_s7; // SBX = DriftRoll (unit ?)
	float stats_s8; // SBY = DriftPitch (unit ?) 
	float stats_s9; // SBZ = DriftYaw  (unit ?)
	float stats_s10; // max thrust
	float stats_s11; // STM (side thrust multiplier)
	float stats_s12; // RTM (reverse thrust multiplier)
	float stats_s13; // scan
	float stats_s14; // fuel
	float stats_s15; // lock mode (ecm)
	float stats_s16; // scale
	float stats_s17; // energy
	float stats_s18; // recharge
	float stats_s19; // rip time
	float stats_s20; // rip cost
	unsigned short stats_ss1; // ammo capacity
	unsigned short uid; // confirmed
	short overriding_uid; // -1 if none
	UCHAR nb_parts; // part size = 30
	UCHAR mnt_nbwpslots;
	float stats_hp; 
	UCHAR TODO2[2];//1C 02
	unsigned short AC;
	unsigned short stats_ld1; // missiles capacity
	unsigned short stats_ld2; // pack capacity
	unsigned short stats_ld3; // CM capacity
	unsigned short def_loadout[IGCSHIPMAXPARTS];// -1 or part uid
	unsigned short hullability;
	UCHAR TODO3[14];// all zero
	unsigned short can_use[IGCSHIPMAXUSE]; // usage masks,see IGCShipUseMasks
	unsigned short Sound_Interior;
	unsigned short Sound_Exterior;
	unsigned short Sound_ThrustInterior;
	unsigned short Sound_ThrustExterior;
	unsigned short Sound_TurnInterior;
    unsigned short Sound_TurnExterior;
	UCHAR TODO4[2];// all zero
	IGCCoreShipMP parts[IGCSHIPMAXWEAPONS];
	int size;
} IGCCoreShip;
typedef IGCCoreShip *PtrCoreShip;
typedef IGCCoreShipMP *PtrCoreShipMP;
const CString ICGPartType[AGCEquipmentType_MAX] =
{
	"ChaffLauncher",
	"Weapon",
	"Magazine",
	"Dispenser",
	"Shield",
	"Cloak",
	"Pack",
	"Afterburner"
};

// size of proxy
#define IGC_PROXYPARTSIZE 0x18
typedef struct SIGCCorePart // tag 0x1E, size = var
{
	UCHAR header[8]; // all zero
	char model[13];
	char pad1; // CC
	char icon[13];
	char name[25];
	char description[200]; // check len
	short group;
	UCHAR techtree[100];
	char pad2[2]; // CC CC
	float stats_s1; // GS1
	unsigned short suk1;// suk1+suk2 = float = sig modifier (%) (NON SPECS PARTS)
	short suk2;// START FOR MISSILE/CHAFF/MINES (SPECS PARTS) = amuont
	unsigned short uid; //
	short overriding_uid; // uid of part that overrides this one (-1 if none)
	short type; // 1 = weapon, 2 = shield, 5 = cloak, 7 = after, 6 = default
	/*  AGCEquipmentType_ChaffLauncher = 0,
		AGCEquipmentType_Weapon = 1,
		AGCEquipmentType_Magazine = 2,
		AGCEquipmentType_Dispenser = 3,
		AGCEquipmentType_Shield = 4,
		AGCEquipmentType_Cloak = 5, 
		AGCEquipmentType_Pack = 6,
		AGCEquipmentType_Afterburner = 7,
		AGCEquipmentType_MAX = 8
	type = launch count for proxy part*/
	unsigned short usemask; // = uid a corresponding object for SPECS PARTS
	char slot[13];
	UCHAR pad3[1]; // CC -  END FOR MISSILE/CHAFF/MINES (SPECS PARTS)
	char pad4[2]; // all CC
	union Uspecs {
		struct Spak {
			BYTE pak_stats_ss1; // Type (0=Ammo,1=fuel)
			BYTE pak_pad1; // CC
			unsigned short pak_stats_ss2; // Quantity
		} pak;
		struct Swep {
			float wep_stats_s1; // Time ready
			float wep_stats_s2; // Shot interval
			float wep_stats_s3; // Energy consumption
			float wep_stats_s4; // Particle spread
			unsigned short wep_stats_ss1; // ammo consumption
			unsigned short wep_projectile_uid;
			unsigned short wep_stats_ss2; // activation sound
			unsigned short wep_stats_ss3; // shot sound
			unsigned short wep_stats_ss4; // burst sound
			BYTE wep_pad1[2]; // CC CC
		} wep;
		struct Sshld {
			float shld_stats_s1; //Recharge rate
			float shld_stats_s2; //Hitpoints
			BYTE shld_AC; // armor class
			BYTE shld_pad; //CC
			unsigned short shld_sound1;//Activate sound
			unsigned short shld_sound2;//Desactivate sound
			BYTE shld_pad1[2]; // CC CC
		} shld;
		struct Saftb {
			float aftb_stats_s1; // Rate of consumption
			float aftb_stats_s2; // Thrust amount
			float aftb_stats_s3; // % acceleration
			float aftb_stats_s4; // Release duration
			unsigned short aftb_stats_ss1; // activate sound
			unsigned short aftb_stats_ss2; // desactivate sound
		} aftb;
		struct Sclk {
			float clk_stats_s1; // Energy drain
			float clk_stats_s2; // Sig reduction
			float clk_stats_s3; // Activation duration
			float clk_stats_s4; // Release duration
			unsigned short clk_sound1; // sound on
			unsigned short clk_sound2; // sound off
		} clk;
	} specs;
	UCHAR TODO[1000]; // assume max
	int size;
	bool isspec;
} IGCCorePart;
typedef IGCCorePart *PtrCorePart;

typedef struct SIGCCoreCounter // tag = 1A, size = 0x1D4
{
	float pcRED; // all zero = percent RGBA
	float pcGreen;
	float pcBlue;
	float pcAlpha;
	float stats_s1; // radius
	float stats_s2; // rate rotation
	UCHAR pad0[13]; // all 0
	char icon[13];
	char pad1[2]; //CC
	float stats_s3; // load time
	float stats_s4; // life span
	float stats_s5; // sig
	AGCMoney stats_s6; // cost
	long stats_s7; // build time (seconds)
	char model[13];
	char pad3; // C
	char type[13]; //part
	char name[25];
	char description[200];
	BYTE group;
	BYTE zero;
	UCHAR techtree[100];
	char pad4[2]; // CC
	float stats_s8; // sig mod (%)
	float stats_s9; // mass
	unsigned short use_mask;
	unsigned short stats_ss1;//1 - todo
	float stats_s10; // hitpoints
	BYTE AC; // 0B default (part)
	UCHAR pad5[1]; //  CD 
	unsigned short uid;
	unsigned short stats_ss2;//0
	char ukbmp[13];
	UCHAR pad6; //CC
	float stats_s11; // strength
} IGCCoreCounter;
typedef IGCCoreCounter *PtrCoreCounter;

#define IGCMISSILE_EFFECT_NONE				0
#define IGMISSILE_EFFECT_BASECAPTURE		1
#define IGCMISSILE_EFFECT_RESONATOR			2
#define IGCMISSILE_EFFECT_RESONATORSINGLE   4
#define IGCMISSILE_EFFECT_NBVALS   4
const CString ICGMissileEffects[IGCMISSILE_EFFECT_NBVALS] =
{
	"none",
	"capture",
	"resonator both sides",
	"resonator one side"
};
const unsigned short ICGMissileEffectsValues[IGCMISSILE_EFFECT_NBVALS] =
{
	IGCMISSILE_EFFECT_NONE,				
	IGMISSILE_EFFECT_BASECAPTURE,
	IGCMISSILE_EFFECT_RESONATOR,			
	IGCMISSILE_EFFECT_RESONATORSINGLE
};
typedef struct SIGCCoreMissile // tag = 0x17, size = 0x2C0
{
	UCHAR header[16]; // ALL ZERO - Checked
	float stats_s1; // scale
	float stats_s2; // rate rotation
	char ldbmp[13];
	UCHAR pad0[13]; // ALL ZERO - Checked
	UCHAR pad1[2];  // CC - Checked
	float stats_s3; // reload time
	float stats_s4; // life span
	float stats_s5; // sig
	AGCMoney cost;
	int pad2; // Zero - Checked
	char model[13];
	UCHAR pad3; // C - Checked
	char type[13]; //part
	char name[25];
	char description[200];
	BYTE group;
	BYTE zero;
	UCHAR techtree[100];
	char pad4[2];//CC - checked
	float stats_sig; // sig%
	float stats_s6; // mass
	unsigned short use_flags;
	unsigned short stats_ss1; // cargo payload
	float stats_s16; // hitpoints
	BYTE AC; // 0B
	UCHAR pad5[1]; // 0B CD - Checked
	unsigned short uid;
	unsigned short special_effect; // 1 for nerve, 2 for reso , 0 otherwise
	char icon[13]; // SWARM = append '\00s'      
	char pad6;//CD - Checked
	float stats_s7; // accel
	float stats_s8; // turn radius
	float stats_s9; // launch velocity
	float stats_s10; // lock time
	float stats_s11; // ready time
	float stats_s12; // max lock
	float stats_s13; // CM resistance
	float stats_s14; // salvo ratio
	float stats_s15; // lock radius
	float stats_power; // power
	float stats_blast_power; // blastPower
	float stats_blast_radius; // blastRadius
	float stats_unused2; // width (default 0)
	unsigned short DM; 
	unsigned short stats_ss3; //sound launch
	unsigned short stats_ss4; //sound flight
	UCHAR end[2]; //CDCD Checked
} IGCCoreMissile;
typedef IGCCoreMissile *PtrCoreMissile;
typedef struct SIGCCoreMine // tag = 0x18, size = 480
{
	float pcRED; // all zero = percent RGBA
	float pcGreen;
	float pcBlue;
	float pcAlpha;
	UCHAR pad0[4]; // all 'CC' (could be float 'scale')
	float stats_s1; // rate rotation 
	UCHAR pad1[13]; // all '00'
	char icon[13]; //fxmine
	UCHAR pad2[2]; // all 'CC'
	float stats_s2; // load time
	float stats_duration;
	float stats_s3; // sig
	AGCMoney cost;
	UCHAR pad3[4]; // all '00'
	char model[13];// inactive & loadout bmp (prefix with 'l')
	UCHAR pad4; // CC
	char type[13]; //part
	char name[25];
	char description[200];
	BYTE group;
	BYTE zero;
	UCHAR techtree[100];
	UCHAR pad5[2]; // CC
	float stats_s4; // ship sig%
	float stats_s5; // mass
	unsigned short usemask; //usemask
	unsigned short stats_ss2; //cargo payload
	float stats_s6; // hitpoints
	BYTE AC; // OB
	UCHAR pad6[1]; // CD 
	unsigned short uid;
	unsigned short pad_zero; // 0000
	char ukbmp[13]; // icon bmp
	UCHAR pad7; // CC
	float stats_radius;
	float stats_damage;
	float stats_endurance; // endurance
	BYTE DM; // 10
	UCHAR pad8[3]; // CD CD CD
} IGCCoreMine;
typedef IGCCoreMine *PtrCoreMine;
typedef struct SIGCCoreDrone // tag = 21 size = 384
{
	AGCMoney cost; // 1 for con, 4000 for miner
	AGCMoney research_time; // 1 for con, 90 for miner
	char model[13];
	UCHAR pad1; // CC
	UCHAR uks1[13]; // null string
	char name[25];
	char description[200];
	BYTE group;
	BYTE zero;
	UCHAR techtree[100];
	UCHAR pad2[2]; // CC
	float f1; // ?, def = 0.5
	float f2; // ?, def = 0.5 
	float f3; // ?, def = 0.5
	BYTE ss1; // AI script: miner=0,wingman=2,layer=5,con=6,carrier=9 
	UCHAR pad3; // CC
	unsigned short ship_uid;
	unsigned short uid;
	short part_uid; // -1 if none, otherwise uid of mines/probes
} IGCCoreDrone;
typedef IGCCoreDrone *PtrCoreDrone;
typedef struct SIGCCoreProbe // tag = 0x19 (AGC_ProbeType), size = 492
{
	UCHAR header[16]; // ALL '0' = 4 floats = RGBA values (as in SIGCCoreMine)
	float stats_s1; // scale
	float stats_s2; // rate rotation
	char model[13];
	char model1[13];
	char pad1[2]; // CC CC
	float stats_s3; // arming time
	float stats_s4; // lifespan
	float stats_s5; // sig
	AGCMoney cost;
	UCHAR TODO1[4];// all '0'
	char ukbmp[13]; // inactive/loadout model
	char pad2; // CC
	char type[13]; // part
	char name[25];
	char description[200];
	BYTE group;
	BYTE zero;
	UCHAR techtree[100];
	char pad3[2]; // CD CD
	UCHAR TODO2[4];// all '0', might be a float 
	float stats_s6; // mass
	unsigned short usemask; // usemask
	unsigned short stats_ss2; // cargo playload
	float stats_s7; // hitpoints
	BYTE AC;// 0B
	char pad4; // CD
	unsigned short uid;
	unsigned short stats_ss3; //features (bits mask, as in AbilityBitMask in igc.h)
	char icon[13];
	char pad5; // CD
	float stats_s8; // scan range
	float stats_s9; // shot interval
	float stats_s10; // accuracy
	float stats_s11; // leading
	short stats_ss4; // ammo capacity
	short stats_projectile;
	short stats_sound; // 720 mainly (soundprobe)
	UCHAR pad6[2];    // CD CD 
	float stats_activation_delay; // -1 or # secs for teleport activation
} IGCCoreProbe;
typedef IGCCoreProbe *PtrCoreProbe;

typedef struct SIGCCoreProjectile // tag = 0x16 (AGC_ProjectileType), size = 88 
{
	float percentRed;
	float percentGreen;
	float percentBlue;
	float percentAlpha;
	float stats_s1; // particle size (radius)
	float stats_s2; // rate rotation (?)
	char  file_model[13]; // ALL '0' = file model
	char  file_texture[13]; // = file texture
	UCHAR pad2[2]; // CC CC
	float stats_s3; // regular damange per shot
	float stats_s4; // area damange per shot
	float stats_s5; // area damage radius
	float stats_s6; // speed
	float stats_s7; // life span
	unsigned short uid;
	BYTE DM;
	BYTE stats_ss1; // absolute speed = 1
	BYTE stats_ss2; // directional = 1
	UCHAR pad3[3]; // CC CC CC
	float stats_s8; // Width OverHeigth
	unsigned short ambient_sound;
	UCHAR pad4[2];// CC CC
} IGCCoreProjectile;
typedef IGCCoreProjectile *PtrCoreProjectile;

typedef struct SIGCCoreTreasureChance
{
	WORD uid;
	BYTE Code; // 1-> uid = part uid, 2-> uid = 31 for powerup, 4-> uid = amount of $
	BYTE Chance;
} IGCCoreTreasureChance;

#define SIGCCoreTreasureSet_Size (26+2+2+2)
typedef struct SIGCCoreTreasureSet // tag = AGC_TreasureSet (0x1C), size = 92
{
	char name[26];
	WORD uid;
	WORD count;
	WORD uk; //= 200
	IGCCoreTreasureChance *ChanceEntries;
} IGCCoreTreasureSet;

typedef IGCCoreTreasureSet * PtrCoreTreasureSet;

typedef struct SCoreEntry
{
	AGCObjectType tag;
	int IGCPartType;
	unsigned short usemask;
	LPARAM entry;
	CString name;
} CoreEntry;
typedef CoreEntry *PtrCoreEntry;

#pragma pack()

class CIGCCore
{
public:
	CIGCCore(void);
	~CIGCCore(void);
	void UnloadCore();
	UINT iCoreHeader;
	PtrCoreConstants pConstants;
	CArray<PtrCoreCiv,PtrCoreCiv> cl_Civs;
	CArray<PtrCoreStationType,PtrCoreStationType> cl_StationTypes;
	CArray<PtrCoreDevel,PtrCoreDevel> cl_Devels;
	CArray<PtrCoreShip,PtrCoreShip> cl_Ships;
	CArray<PtrCorePart,PtrCorePart> cl_Parts;
	CArray<PtrCoreCounter,PtrCoreCounter> cl_Counters;
	CArray<PtrCoreMissile,PtrCoreMissile> cl_Missiles;
	CArray<PtrCoreMine,PtrCoreMine> cl_Mines;
	CArray<PtrCoreDrone,PtrCoreDrone> cl_Drones;
	CArray<PtrCoreProbe,PtrCoreProbe> cl_Probes;
	CArray<PtrCoreProjectile,PtrCoreProjectile> cl_Projectiles;
	CArray<PtrCoreTreasureSet,PtrCoreTreasureSet> cl_TreasureSets;
	bool ReadFromFile(CString);
	bool SaveToFile(CString);
	CMenu mBasesMenu;
	CComboBox cbRenders;
	void BuildBasesMenu(UINT);
	void BuildRenders(CComboBox *);
	PtrCoreStationType GetBase(unsigned short uid);
	CString GetBaseName(unsigned short uid);
	CString GetBaseCivName(unsigned short uid);
	void DumpCore(void);
	char *ProxyPartName(unsigned short uid);
	char *PartName(unsigned short uid);
	char *DevelName(unsigned short uid);
	PtrCoreEntry ProxyPart(unsigned short uid);
	void AddCiv(PtrCoreCiv);
	void AddDevel(PtrCoreDevel);
	void AddShip(PtrCoreShip);
	void AddStationType(PtrCoreStationType);
	void AddDrone(PtrCoreDrone);
	void AddProjectile(PtrCoreProjectile);
	void AddPart(PtrCorePart);
	void AddMissile(PtrCoreMissile);
	void AddMine(PtrCoreMine);
	void AddCounter(PtrCoreCounter);
	void AddProbe(PtrCoreProbe);
	unsigned short ProxyPartUID(void);
	bool MoveDevel(PtrCoreDevel pdevel,int dir);
	PtrCorePart ProxyGet(unsigned short uid);
	LPARAM DeleteProbe(PtrCoreProbe pprobe);
	LPARAM DeleteMissile(PtrCoreMissile pmissile);
	LPARAM DeleteCounter(PtrCoreCounter pcounter);
	LPARAM DeleteMine(PtrCoreMine pmine);
	LPARAM DeletePart(PtrCorePart ppart,bool);
	LPARAM DeleteCiv(PtrCoreCiv pciv);
	LPARAM DeleteStationType(PtrCoreStationType pstation);
	LPARAM DeleteShip(PtrCoreShip pship);
	LPARAM DeleteProjectile(PtrCoreProjectile pproj);
	LPARAM DeleteDrone(PtrCoreDrone pdrone);
	LPARAM DeleteDevel(PtrCoreDevel pdevel);
	bool SaveDepList(CString fn);
	bool Depends(BYTE *tt1, BYTE *tt2);

	PtrCoreStationType FindStationType(short uid);
	PtrCoreCiv FindCiv(short uid);
	PtrCoreDevel FindDevel(short uid);
	PtrCoreProbe FindProbe(short uid);
	PtrCoreMissile FindMissile(short uid);
	PtrCoreCounter FindCounter(short uid);
	PtrCoreMine FindMine(short uid);
	PtrCorePart FindPart(short uid);
	PtrCoreShip FindShip(short uid);
	PtrCoreProjectile FindProjectile(short uid);
	PtrCoreDrone FindDrone(short uid);

	LPARAM BuildError(LPARAM p,char *szReason,char **pszReason);
	LPARAM FindError(char **pszReason);

	bool SaveAsText(CString);
	bool SaveAsXML(CString);
protected:
	void SortEntries(void);
	CoreEntry error_entry;

};
typedef CIGCCore *PtrCore;