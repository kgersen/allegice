// igcmap.h
// structures used in custom map
#pragma once
#define UID_SEED 0x041A

typedef struct rgbval
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
} Srgbval;

#define IGCTAG_MINE 0x0003
typedef struct SIGCMine // tag+ len = "03,00,20,00,00,00", len = 0x20
{
	BYTE TODO[32];
} IGCMine;
/*
	[MapID] [MapID] NOT NULL ,
	[MineID] [smallint] NOT NULL ,
	[MineTypeID] [smallint] NOT NULL ,
	[SideID] [tinyint] NOT NULL ,
	[SectorID] [SectorID] NOT NULL ,
	[LocationX] [real] NOT NULL ,
	[LocationY] [real] NOT NULL ,
	[LocationZ] [real] NOT NULL 
*/
#define IGCTAG_TREASURE 0x0008
typedef struct SIGCTreasure // tag+ len = "08,00,2c,00,00,00", len = 0x2C
{
	BYTE TODO[44];
} IGCTreasure;
/*
	[MapID] [MapID] NOT NULL ,
	[Lifespan] [real] NOT NULL ,
	[TreasureID] [smallint] NOT NULL ,
	[LocationX] [real] NOT NULL ,
	[LocationY] [real] NOT NULL ,
	[LocationZ] [real] NOT NULL ,
	[SectorID] [SectorID] NOT NULL ,
	[Amount] [smallint] NOT NULL ,
	[TreasureCode] [smallint] NOT NULL 
*/

#define IGCTAG_PROBE 0x0004
typedef struct SIGCProbe // tag+ len = "04,00,24,00,00,00", len = 0x24
{
	float posx;
	float posy;
	float posz;
	float ukf1;
	unsigned short probe_uid;
	unsigned short uks1;
	short minetype_uid;
	BYTE team;
	unsigned short sector_uid;
	BYTE uk[10]; // FF FF FF FF FF FF 01 00 80 3F
} IGCProbe;

#define IGCTAG_SECTOR 0x000D
typedef struct SIGCSector // tag+ len = "0D,00,5C,00,00,00",
{
	short starSeed; /* =starSeed 0x0173(371) or 0x0144(324) or 0x5DB3(23987) */
	char pad1[2]; // 00,00,
	float LightX; // 1
	float LightY; // -1
	float LightZ; // 1
	Srgbval LightColor; //AA AA FF (ambiant)
	float posx;
	float posy;
	unsigned short uid;
	short debrisCount; // def= 800
	short starCount; // def = 500
	char name[25]; //name of sector 
	char globe[13]; //"globe1" to "globe9"
	char nebbg[13]; // "nebplntxxbmp" xx=01-12,16,19,23-25,29-31,33,35-37,40-45
	BYTE PlanetSinPct; //40 = max 100
	BYTE PlanetLonPct; //100 = max 100
	BYTE PanetRadius; //125 
	char pad3[1]; // 00
	unsigned char team;
	char ending[2]; //"CC","CC"
} IGCSector;
#define ICGBASE_NEBPLNT 30
const CString IGCNebplnt[ICGBASE_NEBPLNT]={
"nebplnt01bmp","nebplnt02bmp","nebplnt03bmp",
"nebplnt04bmp","nebplnt05bmp","nebplnt06bmp", 
"nebplnt07bmp","nebplnt08bmp","nebplnt09bmp",
"nebplnt10bmp","nebplnt11bmp","nebplnt12bmp",
"nebplnt16bmp","nebplnt19bmp","nebplnt23bmp",
"nebplnt24bmp","nebplnt25bmp","nebplnt29bmp",
"nebplnt30bmp","nebplnt31bmp","nebplnt33bmp",
"nebplnt35bmp","nebplnt36bmp","nebplnt37bmp",
"nebplnt40bmp","nebplnt41bmp","nebplnt42bmp",
"nebplnt43bmp","nebplnt44bmp","nebplnt45bmp"
};
#define IGCTAG_BASE 0x0001
typedef struct SIGCBase // tag+len = "01,00,58,00,00,00"
{
	float posx;
	float posy;
	float posz;
	float O1x; // 0.0
	float O1y; // 1.0
	float O1z; //
	float O2x; //
	float O2y; //
	float O2z; //
	float spinX; //
	float spinY; //
	float spinZ; //
	float spinspeed; //
	unsigned short sector_uid;
	BYTE team; // 0,1,...
	BYTE uk; // 00
	unsigned short uid; //
	unsigned short igcstationtype; 
	char pad1[2]; // F0,F0 = hull/shield percentage
	char name[25];
	char ending; // 'CD'
} IGCBase;
#define IGCTAG_ALEPH 0x0007
typedef struct SIGCAleph // tag+len = "07,00,6C,00,00,00"
{
	unsigned short uid;
	unsigned short connecting_aleph_uid;
	unsigned short radius; //00C8 (size)
	char renderbmp[13];// "plnt19"(blue) or "plnt42"(brown)
	char imagebmp[13];// "aleph"
	char DestinationSectorName[25];//
	char pad1[3]; // CD,CD,CD,
	// 3Dposition pos,size=36/4 = 9 = 3*3 set of single, 1 set = pos, 2nd set, orientation,
	float posx,posy,posz;
	float O1x,O1y,O1z;
	float spinx,spiny,spinz;
	float spinspeed; //CD,CC,4C,3E = 0.2
	float sig; // 
	unsigned short sector_uid;
	char ending[2]; // CD,CD
} ICGAleph;

#define IGCTAG_ROCK 0x0005
typedef struct SIGCRock // tag+len = "05,00,90,00,00,00"
{
	float sig; // std= radius / 100
	float posx,posy,posz;
	float O1x,O1y,O1z; 
	float O2x,O2y,O2z; 
	float spinX,spinY,spinZ; 
	float spinspeed;
	float ore;
	float oreMax;
	unsigned short flags; // 1 = helium, 4 = ? , 8 = buildable asteriod, 16 = U, 32 = Si, 64 = Carb 
	unsigned short uid;
	float hitpoints; // std: radius * 5 
	unsigned short radius; // 
	char renderbmp[13]; //bgrndxx xx=03-05,50-57 or any <name> when <name>.cvh <name>.mdl <name>bmp.mdl exist in client artwork 
	char textureName[13]; // 00,CD,...,CD,
	char iconbmp[13];// "meteoricon", "heliumrock", "carbonrock", "copperrock" (si), "goldrock" (grey), "hotrock" (u), "waterrock" (dark blue)
	char pad2[3]; // CD,CD,CD,
	unsigned short sector_uid;
	char name[25]; // leading '0' if not to appears 
	unsigned char dispandhp; // 4 high bits = % of hitpoints, F to 0 (0 = phantom rock)
							// 4 low bits = 0 = disp HP gauge, 1 = dont
} ICGRock;
/* original IGC struct
struct  DataAsteroidIGC
{
    float               signature;
    Vector              position;
    Vector              up;
    Vector              forward;
    Rotation            rotation;
    AsteroidDef         asteroidDef;
    SectorID            clusterID;
    char                name[c_cbName];
    BytePercentage      fraction;
};

struct AsteroidDef
{
    float                   ore;
    float                   oreMax;
    AsteroidAbilityBitMask  aabmCapabilities;
    AsteroidID              asteroidID;
    HitPoints               hitpoints;
    short                   radius;
    char                    modelName[c_cbFileName];
    char                    textureName[c_cbFileName];
    char                    iconName[c_cbFileName];
};
*/
#define IGCROCK_IS_ASTERIOD 8
#define IGCROCK_IS_THORIUM 4
#define IGCROCK_IS_HELIUM 1
#define IGCROCK_IS_URANIUM 16
#define IGCROCK_IS_SILICON 32
#define IGCROCK_IS_CARBON 64

#define IGCROCK_TPL_ASTERIOD 0
#define IGCROCK_TPL_HELIUM   1
#define IGCROCK_TPL_URANIUM  2
#define IGCROCK_TPL_SILICON  3
#define IGCROCK_TPL_CARBON   4
#define IGCROCK_TPL_THORIUM  5

#define IGCMAXROCKRENDERS 11
const CString IGCRockRenders[IGCMAXROCKRENDERS+1] = 
   {"bgrnd03","bgrnd04","bgrnd05","bgrnd50","bgrnd51","bgrnd52","bgrnd53","bgrnd54","bgrnd55","bgrnd56","bgrnd57","custom"};
//     0         1         2         3        4          5         6         7         8         9        10      
// asteriod = bgrnd03 = 0 / meteoricon = 0
// asteriod = bgrnd05 = 2 / meteoricon = 0
// helium   = bgrnd56 = 9 / heliumrock = 1
// uranium  = bgrnd51 = 4 / hotrock    = 5
// silicon  = bgrnd52 = 5 / copperrock = 3
// carbon   = bgrnd53 = 6 / carbonrock = 2
// thorium  = bgrnd55 = 8 / goldrock = 4
#define IGCMAXROCKICONS 7
const CString IGCRockIcons[IGCMAXROCKICONS] = {"meteoricon","heliumrock","carbonrock","copperrock","goldrock","hotrock","waterrock"};
//                                                  0            1             2           3           4          5          6
#define IGCMAXMAPS 15
const CString IGCMapTypeNames[IGCMAXMAPS+1] = {"Single Ring", "Double Ring", "Pinwheel", "Diamond Ring", "Snowflake", "Split Bases", "Brawl", "Big Ring", "HiLo", "HiHigher", "Star", "InsideOut", "Grid", "EastWest", "LargeSplit","CUSTOM"};

#define IGCMAX 8000.0f      //asumme x,y,z values go from -8000 to 8000
#define MAP2DSIZE 450		// H & W of sector map in pixel
#define W2DMAP (152+75)
#define H2DMAP (105+52)

#define RMAPSGRID 375.0 // size (real coord) of small grid squares 

#define SDOTSECT (10) // size of sector on minimap, aleph and rock on sector map
#define SDOTBASE (16) // size of base on sector map

// team color (as in the game)
#define IGCTEAM1COL RGB(206,178,0x00) //yellow 
#define IGCTEAM2COL RGB(0,28*2,57*2)  // blue RGB(0,28,57)
#define IGCTEAM3COL RGB(66*2,0,24*2)  // purple RGB(66,0,24)
#define IGCTEAM4COL RGB(57,105,0)     // green
#define IGCTEAM5COL RGB(140,65,66)    // pink
#define IGCTEAM6COL RGB(49,203,124)   // cyan