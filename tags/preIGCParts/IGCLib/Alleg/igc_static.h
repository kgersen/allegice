/*
**  Copyright (C) 2008 FAZ Dev Team. All Rights Reserved.
**
**  File:    igc.h
**
**  Author: KGJV 
**
**  Description:
**      extracted static definitions of IGC.h for standalone usage
**
**  History:
*/
/*
This file can be included alone for usage without link to the whole allegiance source 
(aka without linking with zlib, utilizy and igc projects):

required includes & defines to do so:

#include <math.h>
// change these to whatever you need
#define assert(exp)
#define ZError(psz) 

// these should be defined if you use DirectX otherwise they'll be defined here
#ifndef DWORD
typedef unsigned long       DWORD;
#endif
#ifndef D3DCOLOR_DEFINED
typedef DWORD D3DCOLOR;
#define D3DCOLOR_DEFINED
#endif

#ifndef D3DCOLORVALUE_DEFINED
typedef struct _D3DCOLORVALUE {
    float r;
    float g;
    float b;
    float a;
} D3DCOLORVALUE;
#define D3DCOLORVALUE_DEFINED
#endif

// adjust paths 
#include "..\Zlib\vector.h"
#include "..\Zlib\mask.h"
#include "..\_Utility\constants.h"
#include "..\igc\igc_types.h"
#include "..\igc\igc_static.h" >>THIS IS THIS FILE<<
*/

#ifndef IGC_STATIC_H
#define IGC_STATIC_H

// GlobalAttributeSet
struct GlobalAttributeSet
{
    public:
        GlobalAttributeSet(void)
        {
            //Initialize();
        }
        
        void    Initialize(void)
        {
            for (int i = 0; (i < c_gaMax); i++)
                m_attributes[i] = 1.0f;
        }

        void    Set(const float*    a)
        {
            for (int i = 0; (i < c_gaMax); i++)
                m_attributes[i] = a[i];
        }

        void    Apply(const GlobalAttributeSet& gas)
        {
            for (int i = 0; (i < c_gaMax); i++)
            {
                assert (m_attributes[i] > 0.0f);
                assert (m_attributes[i] < 100.0f);
                assert (gas.m_attributes[i] > 0.0f);
                assert (gas.m_attributes[i] < 100.0f);

                m_attributes[i] *= gas.m_attributes[i];
            }
        }

        float    GetAttribute(GlobalAttribute ga) const
        {
            assert (m_attributes[ga] > 0.0f);
            assert (m_attributes[ga] < 100.0f);

            return m_attributes[ga];
        }
        void    SetAttribute(GlobalAttribute ga, float v)
        {
            m_attributes[ga] = v;
        }

        bool    operator == (const GlobalAttributeSet& gas) const
        {
            for (int i = 0; (i < c_gaMax); i++)
            {
                if (m_attributes[i] != gas.m_attributes[i])
                    return false;
            }

            return true;
        }

    private:
        float   m_attributes[c_gaMax];
};




// static structs
struct  HardpointData
{
    //float       minDot;                     //Manned turrets only
    SoundID     interiorSound;
    SoundID     turnSound;

    char        frameName[c_cbFileName];
    //char        hudName[c_cbFileName];
    char        locationAbreviation[c_cbLocAbrev];
    PartMask    partMask;
    bool        bFixed;
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

struct  WarpDef
{
    WarpID              warpID;
    WarpID              destinationID;
    short               radius;
    char                textureName[c_cbFileName];
    char                iconName[c_cbFileName];
};

//Exported data structures ... these data structures define the data used by Initialize()
//for the various classes.
struct  DataClusterIGC
{
    unsigned int        starSeed;
    Vector              lightDirection;
    D3DCOLOR            lightColor;
    float               screenX;
    float               screenY;
    SectorID            clusterID;
    short               nDebris;
    short               nStars;
    char                name[c_cbName];
    char                posterName[c_cbFileName];
    char                planetName[c_cbFileName];
    BytePercentage      planetSinLatitude;
    BytePercentage      planetLongitude;
    unsigned char       planetRadius;
    bool                activeF;
    bool                bHomeSector;
};

struct  DataBuyableIGC
{
    Money               price;
    DWORD               timeToBuild;
    char                modelName[c_cbFileName + 1]; // because we allow a 1 character prefix
    char                iconName[c_cbFileName];
    char                name[c_cbName];
    char                description[c_cbDescription];
    BuyableGroupID      groupID;
    TechTreeBitMask     ttbmRequired;
    TechTreeBitMask     ttbmEffects;
};

const int   c_cMaxPreferredPartTypes = 14;
struct  DataHullTypeIGC : public DataBuyableIGC
{
    float               mass;
    float               signature;
    float               speed;
    float               maxTurnRates[3];    //yaw, pitch, roll
    float               turnTorques[3];      //yaw, pitch, roll
    float               thrust;
    float               sideMultiplier;
    float               backMultiplier;
    float               scannerRange;
    float               maxFuel;
    float               ecm;
    float               length;
    float               maxEnergy;
    float               rechargeRate;
    float               ripcordSpeed;
    float               ripcordCost;

    short               maxAmmo;

    HullID              hullID;
    HullID              successorHullID;
    Mount               maxWeapons;
    Mount               maxFixedWeapons;
    HitPoints           hitPoints;
    short               hardpointOffset;

    DefenseTypeID       defenseType;

    short               capacityMagazine;
    short               capacityDispenser;
    short               capacityChaffLauncher;

    PartID              preferredPartsTypes[c_cMaxPreferredPartTypes];

    HullAbilityBitMask  habmCapabilities;
    char                textureName[c_cbFileName];

    //char                pilotHUDName[c_cbFileName];
    //char                observerHUDName[c_cbFileName];

    PartMask            pmEquipment[ET_MAX];

    SoundID             interiorSound;
    SoundID             exteriorSound;
    SoundID             mainThrusterInteriorSound;
    SoundID             mainThrusterExteriorSound;
    SoundID             manuveringThrusterInteriorSound;
    SoundID             manuveringThrusterExteriorSound;


    // HardpointData[] comes here
	// KGJV- added
	HardpointData*   GetHardpointData(int i)
    {
		HardpointData *d = (HardpointData*)(this + 1);
        return d + i;
    }
};

struct  DataPartTypeIGC : public DataBuyableIGC
{
    float               mass;
    float               signature;
    PartID              partID;
    PartID              successorPartID;
    EquipmentType       equipmentType;
    PartMask            partMask;
    char                inventoryLineMDL[c_cbFileName];
};

struct  DataWeaponTypeIGC : public DataPartTypeIGC
{
    float               dtimeReady;
    float               dtimeBurst;
    float               energyPerShot;
    float               dispersion;
    short               cAmmoPerShot;
    ProjectileTypeID    projectileTypeID;
    SoundID             activateSound;
    SoundID             singleShotSound;
    SoundID             burstSound;
};

struct  DataShieldTypeIGC : public DataPartTypeIGC
{
    float           rateRegen;
    float           maxStrength;
    DefenseTypeID   defenseType;
    SoundID         activateSound;
    SoundID         deactivateSound;
};

struct  DataCloakTypeIGC : public DataPartTypeIGC
{
    float           energyConsumption;
    float           maxCloaking;
    float           onRate;
    float           offRate;
    SoundID         engageSound;
    SoundID         disengageSound;
};

struct  DataAfterburnerTypeIGC : public DataPartTypeIGC
{
    float           fuelConsumption;
    float           maxThrust;
    float           onRate;
    float           offRate;
    SoundID         interiorSound;
    SoundID         exteriorSound;
};

struct  DataPackTypeIGC : public DataPartTypeIGC
{
    PackType        packType;
    short           amount;
};

struct  DataLauncherTypeIGC
{
    short           amount;
    PartID          partID;
    PartID          successorPartID;
    short           launchCount;
    ObjectID        expendabletypeID;
    char            inventoryLineMDL[c_cbFileName];
};

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

struct  DataObjectIGC
{
    D3DCOLORVALUE       color;
    float               radius;
    float               rotation;
    char                modelName[c_cbFileName];
    char                textureName[c_cbFileName];
};

struct  DataBuoyIGC
{
    Vector              position;
    SectorID            clusterID;
    BuoyType            type;
    BuoyID              buoyID;

    DataBuoyIGC (void) {buoyID = NA;}
};

struct  DataProjectileTypeIGC : public DataObjectIGC
{
    float               power;
    float               blastPower;
    float               blastRadius;
    float               speed;
    float               lifespan;
    ProjectileTypeID    projectileTypeID;
    DamageTypeID        damageType;
    bool                absoluteF;
    bool                bDirectional;
    float               width;
    SoundID             ambientSound;
};

struct  LauncherDef : public DataBuyableIGC
{
    float               signature;
    float               mass;
    PartMask            partMask;
    short               expendableSize;
};

struct  DataExpendableTypeIGC : public DataObjectIGC
{
    float               loadTime;
    float               lifespan;
    float               signature;
    LauncherDef         launcherDef;
    HitPoints           hitPoints;
    DefenseTypeID       defenseType;
    ExpendableTypeID    expendabletypeID;
    AbilityBitMask      eabmCapabilities;
    char                iconName[c_cbFileName];
};

struct  DataMissileTypeIGC : public DataExpendableTypeIGC
{
    float               acceleration;
    float               turnRate;
    float               initialSpeed;
    //float               armTime;
    float               lockTime;
    float               readyTime;

    float               maxLock;
    float               chaffResistance;

    float               dispersion;
    float               lockAngle;

    float               power;

    float               blastPower;
    float               blastRadius;

    float               width;

    DamageTypeID        damageType;

    bool                bDirectional;

    SoundID             launchSound;
    SoundID             ambientSound;
};

struct  DataMineTypeIGC : public DataExpendableTypeIGC
{
    float               radius;
    float               power;
    float               endurance;
    DamageTypeID        damageType;
};

struct  DataChaffTypeIGC : public DataExpendableTypeIGC
{
    float               chaffStrength;
};

struct  DataProbeTypeIGC : public DataExpendableTypeIGC
{
    float               scannerRange;

    float               dtimeBurst;
    float               dispersion;
    float               accuracy;

    short               ammo;

    ProjectileTypeID    projectileTypeID;

    SoundID             ambientSound;
    float               dtRipcord;
};

struct  DataCivilizationIGC
{
    float               incomeMoney;
    float               bonusMoney;
    char                name[c_cbName];
    char                iconName[c_cbFileName];
    char                hudName[c_cbFileName];
    TechTreeBitMask     ttbmBaseTechs;
    TechTreeBitMask     ttbmNoDevTechs;
    GlobalAttributeSet  gasBaseAttributes;
    HullID              lifepod;
    CivID               civilizationID;
    StationTypeID       initialStationTypeID;
};

typedef char    TreasureCode;
const TreasureCode  c_tcPart        = 1;
const TreasureCode  c_tcPowerup     = 2;
const TreasureCode  c_tcDevelopment = 3;
const TreasureCode  c_tcCash        = 4;
const TreasureCode  c_tcFlag        = 5;

typedef ObjectID    PowerupCode;
const PowerupCode   c_pcHull   = 0x01;
const PowerupCode   c_pcShield = 0x02;
const PowerupCode   c_pcEnergy = 0x04;
const PowerupCode   c_pcFuel   = 0x08;
const PowerupCode   c_pcAmmo   = 0x10;

struct  TreasureData
{
    ObjectID        treasureID;
    TreasureCode    treasureCode;
    unsigned char   chance;
};

struct DataTreasureSetIGC
{
    char            name[c_cbName];
    TreasureSetID   treasureSetID;
    short           nTreasureData;
    bool            bZoneOnly;

    TreasureData*   treasureData0(void)
    {
        return (TreasureData*)(this + 1);
    }
};

struct  DataStationTypeIGC : public DataBuyableIGC
{
    float                   signature;
    float                   maxArmorHitPoints;
    float                   maxShieldHitPoints;
    float                   armorRegeneration;
    float                   shieldRegeneration;
    float                   scannerRange;
    Money                   income;
    float                   radius;
    TechTreeBitMask         ttbmLocal;
    StationTypeID           stationTypeID;
    StationTypeID           successorStationTypeID;
    DefenseTypeID           defenseTypeArmor;
    DefenseTypeID           defenseTypeShield;
    StationAbilityBitMask   sabmCapabilities;
    AsteroidAbilityBitMask  aabmBuild;
    StationClassID          classID;

    DroneTypeID             constructionDroneTypeID;

    SoundID                 constructorNeedRockSound;
    SoundID                 constructorUnderAttackSound;
    SoundID                 constructorDestroyedSound;
    SoundID                 completionSound;

    SoundID                 interiorSound;
    SoundID                 exteriorSound;
    SoundID                 interiorAlertSound;

    SoundID                 underAttackSound;
    SoundID                 criticalSound;
    SoundID                 destroyedSound;
    SoundID                 capturedSound;

    SoundID                 enemyCapturedSound;
    SoundID                 enemyDestroyedSound;

    char                    textureName[c_cbFileName];
    char                    builderName[c_cbName];
};

struct DataDevelopmentIGC : public DataBuyableIGC
{
    GlobalAttributeSet  gas;
    DevelopmentID       developmentID;
    SoundID             completionSound;
};

struct DataDroneTypeIGC : public DataBuyableIGC
{
    float               shootSkill;
    float               moveSkill;
    float               bravery;
    PilotType           pilotType;
    HullID              hullTypeID;
    DroneTypeID         droneTypeID;
    ExpendableTypeID    etidLaid;
};
// IGC map 
typedef unsigned long Time;

struct  DataMineBase
{
    Vector              p0;
    Time                time0;
    MineID              mineID;
    bool                exportF;
};

struct DataMineExport : public DataMineBase
{
    SectorID            clusterID;
    ExpendableTypeID    minetypeID;
    ShipID              launcherID;
    SideID              sideID;
    BytePercentage      fraction;
    bool                createNow;
};
struct  DataProbeBase
{
    Vector              p0;
    Time                time0;
    ProbeID             probeID;
    bool                exportF;
};

struct DataProbeExport : public DataProbeBase
{
    ExpendableTypeID    probetypeID;
    SideID              sideID;
    SectorID            clusterID;
    ShipID              shipID;
    ObjectType          otTarget;
    ObjectID            oidTarget;
    bool                createNow;
};

struct  DataStationIGC
{
    Vector              position;
    Vector              up;
    Vector              forward;
    Rotation            rotation;
    SectorID            clusterID;
    SideID              sideID;
    StationID           stationID;
    StationTypeID       stationTypeID;
    BytePercentage      bpHull;
    BytePercentage      bpShield;
    char                name[c_cbName];
};

struct  DataWarpIGC
{
    WarpDef             warpDef;
    char                name[c_cbName];
    Vector              position;
    Vector              forward;
    Rotation            rotation;
    float               signature;
    SectorID            clusterID;
};

struct  DataTreasureIGC
{
    Vector              p0;
    Vector              v0;
    float               lifespan;
    Time                time0;
    ObjectID            objectID;
    TreasureID          treasureID;
    SectorID            clusterID;
    short               amount;
    TreasureCode        treasureCode;
    bool                createNow;
};
// from missionigc.h
struct  Constants
{
    float   floatConstants[c_fcidMax];
    float   damageConstants[c_dmgidMax][c_defidMax];
};
#endif //IGC_STATIC_H