/*
**  Copyright (C) 2008 FAZ Dev Team. All Rights Reserved.
**
**  File:    igc.h
**
**  Author: KGJV 
**
**  Description:
**      extracted types of IGC.h - see igc_static.h
**
**  History:
*/
#ifndef IGC_TYPES_H
#define IGC_TYPES_H

// ExplosionType
typedef int ExplosionType;
const ExplosionType c_etMine            = 1;
const ExplosionType c_etMissile         = 2;
const ExplosionType c_etProjectile      = 2;    //Intentional duplication
const ExplosionType c_etSmallShip       = 3;
const ExplosionType c_etProbe           = 3;    //Intentional duplication
const ExplosionType c_etBigShip         = 4;
const ExplosionType c_etSmallStation    = 5;
const ExplosionType c_etAsteroid        = 6;
const ExplosionType c_etLargeStation    = 7;

// ConstantID
typedef short   FloatConstantID;
const FloatConstantID   c_fcidLensMultiplier           = 0;
const FloatConstantID   c_fcidRadiusUniverse           = 1;
const FloatConstantID   c_fcidOutOfBounds              = 2;
const FloatConstantID   c_fcidExitWarpSpeed            = 3;
const FloatConstantID   c_fcidExitStationSpeed         = 4;
const FloatConstantID   c_fcidDownedShield             = 5;
const FloatConstantID   c_fcidSecondsBetweenPaydays    = 6;
const FloatConstantID   c_fcidCapacityHe3              = 7;
const FloatConstantID   c_fcidValueHe3                 = 8;
const FloatConstantID   c_fcidAmountHe3                = 9;
const FloatConstantID   c_fcidMountRate                = 10;

const FloatConstantID   c_fcidStartingMoney            = 11;
const FloatConstantID   c_fcidWinTheGameMoney          = 12;
const FloatConstantID   c_fcidRipcordTime              = 13;

const FloatConstantID   c_fcidHe3Regeneration          = 14;

const FloatConstantID   c_fcidPointsWarp            = 15;
const FloatConstantID   c_fcidPointsAsteroid        = 16;
const FloatConstantID   c_fcidPointsTech            = 17;
const FloatConstantID   c_fcidPointsMiner           = 18;
const FloatConstantID   c_fcidPointsBuilder         = 19;
const FloatConstantID   c_fcidPointsLayer           = 20;
const FloatConstantID   c_fcidPointsCarrier         = 21;
const FloatConstantID   c_fcidPointsPlayer          = 22;
const FloatConstantID   c_fcidPointsBaseKill        = 23;
const FloatConstantID   c_fcidPointsBaseCapture     = 24;

const FloatConstantID   c_fcidPointsFlags           = 25;
const FloatConstantID   c_fcidPointsArtifacts       = 26;
const FloatConstantID   c_fcidPointsRescues         = 27;

const FloatConstantID   c_fcidRatingAdd             = 28;
const FloatConstantID   c_fcidRatingDivide          = 29;

const FloatConstantID    c_fcidIncome               = 30;
const FloatConstantID    c_fcidLifepodEndurance     = 31;

const FloatConstantID    c_fcidWarpBombDelay        = 32;

const FloatConstantID    c_fcidLifepodCost          = 33;
const FloatConstantID    c_fcidTurretCost           = 34;
const FloatConstantID    c_fcidDroneCost            = 35;
const FloatConstantID    c_fcidPlayerCost           = 36;
const FloatConstantID    c_fcidBaseClusterCost      = 37;
const FloatConstantID    c_fcidClusterDivisor       = 38;

const FloatConstantID    c_fcidMax                  = 40;


//Redefined data types (so we can change them later)
const int NA = -1; // meaning unspecified, none, or all.
const float fNA = -1; // To support supression of compiler warnings.  Floats should probably all be doubles anyways, but hey.  --Dhauzimmer, 8/14/04


// ObjectType
//
// Note: if you add or change any new ObjectTypes, then please notify
// Mark C or John T so that AGCIDL.idl will be updated.
//
//
typedef  short   ObjectType;
const ObjectType    OT_invalid          = -1;

const ObjectType  OT_modelBegin         =  0;
const ObjectType    OT_ship             =  0;                //All classes derived from model
const ObjectType    OT_station          =  1;
const ObjectType    OT_missile          =  2;
const ObjectType    OT_mine             =  3;
const ObjectType    OT_probe            =  4;
const ObjectType    OT_asteroid         =  5;

const ObjectType    OT_projectile       =  6;
const ObjectType    OT_warp             =  7;
const ObjectType    OT_treasure         =  8;           //All of the above are models
const ObjectType    OT_buoy             =  9;
const ObjectType    OT_chaff            = 10;
const ObjectType    OT_buildingEffect   = 11;
const ObjectType  OT_modelEnd           = 11;

const ObjectType    OT_side             = 12;
const ObjectType    OT_cluster          = 13;
const ObjectType    OT_bucket           = 14;

const ObjectType  OT_partBegin          = 15;
const ObjectType    OT_weapon           = 15;
const ObjectType    OT_shield           = 16;
const ObjectType    OT_cloak            = 17;
const ObjectType    OT_pack             = 18;
const ObjectType    OT_afterburner      = 19;
const ObjectType  OT_launcherBegin      = 20;
const ObjectType    OT_magazine         = 20;
const ObjectType    OT_dispenser        = 21;
const ObjectType  OT_launcherEnd        = 21;
const ObjectType  OT_partEnd            = 21;


const ObjectType  OT_staticBegin        = 22;
const ObjectType    OT_projectileType   = 22;      //All static objects
const ObjectType    OT_missileType      = 23;
const ObjectType    OT_mineType         = 24;
const ObjectType    OT_probeType        = 25;
const ObjectType    OT_chaffType        = 26;
const ObjectType    OT_civilization     = 27;
const ObjectType    OT_treasureSet      = 28;

const ObjectType  OT_bucketStart        = 29;
const ObjectType    OT_hullType         = 29;
const ObjectType    OT_partType         = 30;
const ObjectType    OT_stationType      = 31;
const ObjectType    OT_development      = 32;
const ObjectType    OT_droneType        = 33;
const ObjectType  OT_bucketEnd          = 33;
const ObjectType  OT_staticEnd          = 33;

const ObjectType    OT_constants        = 34;
const ObjectType    OT_allsrvUser       = 35; // used by the admin object model
const ObjectType    OT_Max              = 36;// don't put anything after this
                                             // OT_Max should be less then 256 for
                                             // AGC event firing. 

const   __int64         c_maskStaticTypes = (__int64(1) << __int64(OT_projectileType)) | 
                                            (__int64(1) << __int64(OT_treasureSet)) | 
                                            (__int64(1) << __int64(OT_hullType)) | 
                                            (__int64(1) << __int64(OT_partType)) | 
                                            (__int64(1) << __int64(OT_missileType)) | 
                                            (__int64(1) << __int64(OT_mineType)) | 
                                            (__int64(1) << __int64(OT_probeType)) | 
                                            (__int64(1) << __int64(OT_civilization)) | 
                                            (__int64(1) << __int64(OT_stationType)) | 
                                            (__int64(1) << __int64(OT_development)) | 
                                            (__int64(1) << __int64(OT_droneType)) | 
                                            (__int64(1) << __int64(OT_chaffType)) | 
                                            (__int64(1) << __int64(OT_constants)); 

const   __int64         c_maskMapTypes =    (__int64(1) << __int64(OT_asteroid)) | 
                                            (__int64(1) << __int64(OT_station))  | 
                                            (__int64(1) << __int64(OT_cluster))  | 
                                            (__int64(1) << __int64(OT_mine))     |
                                            (__int64(1) << __int64(OT_probe))    |
                                            (__int64(1) << __int64(OT_treasure)) |
                                            (__int64(1) << __int64(OT_warp));


typedef short   SoundID;

//*ID are unique IDs for something
typedef short           ObjectID;
typedef ObjectID        BucketID;
typedef ObjectID        PartID;
typedef ObjectID        ShipID;
typedef ObjectID        BuoyID;
typedef ObjectID        AsteroidID;
typedef ObjectID        HullID;
typedef ObjectID        StationTypeID;
typedef ObjectID        DroneTypeID;
typedef ObjectID        DevelopmentID;
typedef ObjectID        SectorID;
typedef ObjectID        WarpID;
typedef ObjectID        ProjectileTypeID;
typedef ObjectID        TreasureID;
typedef ObjectID        SideID;
typedef ObjectID        StationID;
typedef ObjectID        MissileID;
typedef ObjectID        ChaffID;
typedef ObjectID        MineID;
typedef ObjectID        ProbeID;
typedef ObjectID        ExpendableTypeID;
typedef ObjectID        CivID;
typedef ObjectID        MunitionID;
typedef ObjectID        TreasureSetID;
typedef int             SquadID;


typedef short     EquipmentType; // this is PartTypeID in the database
const EquipmentType   ET_ChaffLauncher  = 0;
const EquipmentType   ET_Weapon         = 1;
const EquipmentType   ET_Magazine       = 2;
const EquipmentType   ET_Dispenser      = 3;
const EquipmentType   ET_Shield         = 4;
const EquipmentType   ET_Cloak          = 5;
const EquipmentType   ET_Pack           = 6;
const EquipmentType   ET_Afterburner    = 7;
const EquipmentType   ET_MAX            = 8;



typedef char     PackType;
const PackType      c_packAmmo    = 0;
const PackType      c_packFuel    = 1;

typedef char     BuoyType;
const BuoyType      c_buoyWaypoint = 0;
const BuoyType      c_buoyCluster  = 1;

typedef unsigned char     DamageTypeID;
typedef unsigned char     DefenseTypeID;

const DamageTypeID      c_dmgidNoWarn   = 0x20;
const DamageTypeID      c_dmgidNoDebris = 0x40;
const DamageTypeID      c_dmgidNoFlare =  0x80;
const DamageTypeID      c_dmgidMask = 0x1f;

const DamageTypeID      c_dmgidCollision = c_dmgidNoDebris | c_dmgidNoFlare | c_dmgidNoWarn;
const DamageTypeID      c_dmgidMax = 20;

const DefenseTypeID     c_defidAsteroid       = 0;
const DefenseTypeID     c_defidMax = 20;

typedef int     TechTreeBit;

const TechTreeBit   c_ttbShipyardAllowed  = 1;
const TechTreeBit   c_ttbExpansionAllowed = 2;
const TechTreeBit   c_ttbTacticalAllowed  = 3;
const TechTreeBit   c_ttbSupremacyAllowed = 4;

// these #defs need to be modified when the number of bits changes
const TechTreeBit   c_ttbMax = 400;
#define CbTechBits 400 // keep in sync w/ TechBits sql data type
#define CbTechBitName 40
#define cTechs 400

typedef short   GlobalAttributeID;
typedef short   GlobalAttribute;
const GlobalAttribute   c_gaMaxSpeed                    =  0;   //Implemented
const GlobalAttribute   c_gaThrust                      =  1;   //I

const GlobalAttribute   c_gaTurnRate                    =  2;   //I
const GlobalAttribute   c_gaTurnTorque                  =  3;   //I

const GlobalAttribute   c_gaMaxArmorStation             =  4;   //I
const GlobalAttribute   c_gaArmorRegenerationStation    =  5;   //I

const GlobalAttribute   c_gaMaxShieldStation            =  6;   //I
const GlobalAttribute   c_gaShieldRegenerationStation   =  7;   //I

const GlobalAttribute   c_gaMaxArmorShip                =  8;   //I
const GlobalAttribute   c_gaMaxShieldShip               =  9;   //I
const GlobalAttribute   c_gaShieldRegenerationShip      = 10;   //I

const GlobalAttribute   c_gaScanRange                   = 11;   //I
const GlobalAttribute   c_gaSignature                   = 12;   //I

const GlobalAttribute   c_gaMaxEnergy                   = 13;   //I

const GlobalAttribute   c_gaSpeedAmmo                   = 14;   //I
const GlobalAttribute   c_gaLifespanEnergy              = 15;   //I

const GlobalAttribute   c_gaTurnRateMissile             = 16;   //I

const GlobalAttribute   c_gaMiningRate                  = 17;   //I
const GlobalAttribute   c_gaMiningYield                 = 18;   //I
const GlobalAttribute   c_gaMiningCapacity              = 19;   //I

const GlobalAttribute   c_gaRipcordTime                 = 20;   //I

const GlobalAttribute   c_gaDamageGuns                  = 21;   //I
const GlobalAttribute   c_gaDamageMissiles              = 22;   //I

const GlobalAttribute   c_gaDevelopmentCost             = 23;   //I
const GlobalAttribute   c_gaDevelopmentTime             = 24;   //I

const GlobalAttribute   c_gaMax = 25;

typedef unsigned char StationClassID;
const StationClassID    c_scStarbase                    = 0;
const StationClassID    c_scGarrison                    = 1;
const StationClassID    c_scShipyard                    = 2;
const StationClassID    c_scRipcord                     = 3;
const StationClassID    c_scMining                      = 4;
const StationClassID    c_scResearch                    = 5;
const StationClassID    c_scOrdinance                   = 6;
const StationClassID    c_scElectronics                 = 7;

typedef char    WarningMask;
const WarningMask   c_wmOutOfBounds   = 0x01;
const WarningMask   c_wmCrowdedSector = 0x02;

typedef char BuyableGroupID;

/*
· Max Speed: Up the sides maximum speed 
· Rate of Yaw: Increase angle of turn per sec
· Rate of Pitch: Increase angle of turn per sec
· Rate of acceleration: Increase your acceleration
· Energy level: Boosts available energy for firing weapons and other stuff.
· Energy Level recharge rate: Faster recharge rate
· Mounts: Give ships bigger carrying capabilities.
· Shield strength: Better shields more hp
· Shield Recharge: Better recharge.
· Hull strength: Better Armor more hp
· Afterburner fuel efficiency: More miles per gallon
· Afterburner speed multiplier: Top speed enhanced
· Signature: Dampens your global signature.
· Scan Range: Ups the area by an amount
· Space station shield strength: More hit points.
· Space station hull strength: More hull hit points
· Miner productivity: Increase the dollar amount given to players at the completion of a round trip.
· Weapon Cost: Make all weapons a little cheaper
· Equipment Cost: make all equipment cheaper
· Ship Cost: Make ships cheaper
· Missile Speed/Accuracy?/Recalc time: A global attribute to improve Missiles chance of hitting.
· Projectile Damage: Ups damage
· Missile Damage: Ups damage
· Weapon Range: Improves distance
· Drone targeting : Improves accuracy
· Auto turret accuracy rating.: Improves accuracy (possibly same as above.)
*/


/*
** PilotType ... these are the various automatic pilots that can be plugged into a ship
*/
typedef unsigned char PilotType;
const PilotType c_ptMiner       =  0;
const PilotType c_ptWingman     =  2;
const PilotType c_ptLayer       =  5;
const PilotType c_ptBuilder     =  6;
const PilotType c_ptCarrier     =  9;
const PilotType c_ptPlayer      = 10;
const PilotType c_ptCheatPlayer = 11;

// Masks
typedef short                   PartMask;

typedef short                   AbilityBitMask;

typedef AbilityBitMask          HullAbilityBitMask;
const HullAbilityBitMask        c_habmBoard                 = 0x01;
const HullAbilityBitMask        c_habmRescue                = 0x02;
const HullAbilityBitMask        c_habmLifepod               = 0x04;
const HullAbilityBitMask        c_habmCaptureThreat         = 0x08;
const HullAbilityBitMask        c_habmLandOnCarrier         = 0x10;
const HullAbilityBitMask        c_habmNoRipcord             = 0x20;
const HullAbilityBitMask        c_habmIsRipcordTarget       = 0x40;
const HullAbilityBitMask        c_habmFighter               = 0x80;
const HullAbilityBitMask        c_habmRemoteLeadIndicator   = 0x100;
const HullAbilityBitMask        c_habmThreatToStation       = 0x200;
const HullAbilityBitMask        c_habmCarrier               = 0x400;
const HullAbilityBitMask        c_habmLeadIndicator         = 0x800;
const HullAbilityBitMask        c_habmIsLtRipcordTarget     = 0x1000;
const HullAbilityBitMask        c_habmCanLtRipcord          = 0x2000;
const HullAbilityBitMask        c_habmMiner                 = 0x4000;
const HullAbilityBitMask        c_habmBuilder               = (short)0x8000;

typedef AbilityBitMask          StationAbilityBitMask;
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

typedef AbilityBitMask          AsteroidAbilityBitMask;
const AsteroidAbilityBitMask    c_aabmMineHe3      = 0x01;      //Has minable ore of some type (all mutually exclusive)
const AsteroidAbilityBitMask    c_aabmMineLotsHe3  = 0x02;
const AsteroidAbilityBitMask    c_aabmMineGold     = 0x04;

const AsteroidAbilityBitMask    c_aabmBuildable    = 0x08;      //Buildings can be built on it
const AsteroidAbilityBitMask    c_aabmSpecial      = 0x10;      //Special buildings can be built on it

typedef TLargeBitMask<c_ttbMax> TechTreeBitMask;

typedef AbilityBitMask          ExpendableAbilityBitMask;
const ExpendableAbilityBitMask  c_eabmCapture         = 0x01;
const ExpendableAbilityBitMask  c_eabmWarpBombDual    = 0x02; // KGJV: both sides aleph rez
const ExpendableAbilityBitMask  c_eabmWarpBombSingle  = 0x04; // KGJV: one side aleph rez
const ExpendableAbilityBitMask  c_eabmWarpBomb        = c_eabmWarpBombDual | c_eabmWarpBombSingle; // KGJV: both types into one for backward compatibility
const ExpendableAbilityBitMask  c_eabmQuickReady      = 0x08;
const ExpendableAbilityBitMask  c_eabmRipcord         = 0x10;
const ExpendableAbilityBitMask  c_eabmShootStations   = 0x20;
const ExpendableAbilityBitMask  c_eabmShootShips      = 0x40;
const ExpendableAbilityBitMask  c_eabmShootMissiles   = 0x80;
const ExpendableAbilityBitMask  c_eabmShootOnlyTarget = 0x1000;
const ExpendableAbilityBitMask  c_eabmRescue          = c_sabmRescue;     //0x2000 Rescue lifepods that collide with it
const ExpendableAbilityBitMask  c_eabmRescueAny       = c_sabmRescueAny;  //0x4000 Rescue any lifepod that collide with it

// various types
typedef float HitPoints;
typedef int   Money;
typedef char  Mount;

typedef unsigned char Axis;
const Axis c_axisYaw       = 0;
const Axis c_axisPitch     = 1;
const Axis c_axisRoll      = 2;
const Axis c_axisThrottle  = 3;
const Axis c_axisMax       = 4;

//Constants used to avoid having to allocate arrays.
const Mount   c_maxUnmannedWeapons = 4;
const Mount   c_maxMountedWeapons = 8;

#endif // IGC_TYPES_H