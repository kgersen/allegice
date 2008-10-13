using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace IGCLib
{

    public class  DataProjectileTypeIGC : DataObjectIGC
    {
        public float power { get; set; }
        public float blastPower { get; set; }
        public float blastRadius { get; set; }
        public float speed { get; set; }
        public float lifespan { get; set; }
        public short projectileTypeID { get; set; }
        public byte damageType { get; set; }
        public bool absoluteF { get; set; }
        public bool bDirectional { get; set; }
        public float width { get; set; }
        public short ambientSound { get; set; }
    }
    public enum EquipmentType : short
    {
       ET_ChaffLauncher  = 0,
       ET_Weapon         = 1,
       ET_Magazine       = 2,
       ET_Dispenser      = 3,
       ET_Shield         = 4,
       ET_Cloak          = 5,
       ET_Pack           = 6,
       ET_Afterburner    = 7
    }
    public class  DataPartTypeIGC : DataBuyableIGC
    {
        public float mass { get; set; }
        public float signature { get; set; }
        public short partID { get; set; }
        public DataPartTypeIGC successorPart { get; set; }
        public EquipmentType equipmentType { get; set; }
        public short partMask { get; set; }
        public string inventoryLineMDL { get; set; }
    }

    public class DataWeaponTypeIGC : DataPartTypeIGC
    {
        public float dtimeReady { get; set; }
        public float dtimeBurst { get; set; }
        public float energyPerShot { get; set; }
        public float dispersion { get; set; }
        public short cAmmoPerShot { get; set; }
        public DataProjectileTypeIGC projectile { get; set; }
        public short activateSound { get; set; }
        public short singleShotSound { get; set; }
        public short burstSound { get; set; }
    }

    public class DataShieldTypeIGC : DataPartTypeIGC
    {
        public float rateRegen { get; set; }
        public float maxStrength { get; set; }
        public byte defenseType { get; set; }
        public short activateSound { get; set; }
        public short deactivateSound { get; set; }
    }

    public class DataCloakTypeIGC : DataPartTypeIGC
    {
        public float energyConsumption { get; set; }
        public float maxCloaking { get; set; }
        public float onRate { get; set; }
        public float offRate { get; set; }
        public short engageSound { get; set; }
        public short disengageSound { get; set; }
    }

    public class DataAfterburnerTypeIGC : DataPartTypeIGC
    {
        public float fuelConsumption { get; set; }
        public float maxThrust { get; set; }
        public float onRate { get; set; }
        public float offRate { get; set; }
        public short interiorSound { get; set; }
        public short exteriorSound { get; set; }
    }

    public enum PackType : byte
    {
        c_packAmmo    = 0,
        c_packFuel    = 1
    }

    public class DataPackTypeIGC : DataPartTypeIGC
    {
        public PackType packType { get; set; }
        public short amount { get; set; }
    }

    public class LauncherDef : DataBuyableIGC
    {
        public float signature { get; set; }
        public float mass { get; set; }
        public short partMask { get; set; }
        public short expendableSize { get; set; }
    }

    public class DataExpendableTypeIGC : DataObjectIGC
    {
        public float loadTime { get; set; }
        public float lifespan { get; set; }
        public float signature { get; set; }
        public LauncherDef launcherDef { get; set; }
        public float hitPoints { get; set; }
        public byte defenseType { get; set; }
        public short expendabletypeID { get; set; }
        public short eabmCapabilities { get; set; }
        public string iconName { get; set; }
    }

    public class DataMissileTypeIGC : DataExpendableTypeIGC
    {
        public float acceleration { get; set; }
        public float turnRate { get; set; }
        public float initialSpeed { get; set; }
        public float lockTime { get; set; }
        public float readyTime { get; set; }
        public float maxLock { get; set; }
        public float chaffResistance { get; set; }
        public float dispersion { get; set; }
        public float lockAngle { get; set; }
        public float power { get; set; }
        public float blastPower { get; set; }
        public float blastRadius { get; set; }
        public float width { get; set; }
        public byte damageType { get; set; }
        public bool bDirectional { get; set; }
        public short launchSound { get; set; }
        public short ambientSound { get; set; }
    }

    public class DataMineTypeIGC : DataExpendableTypeIGC
    {
        public float mineradius { get; set; }
        public float power { get; set; }
        public float endurance { get; set; }
        public byte damageType { get; set; }
    }

    public class DataChaffTypeIGC : DataExpendableTypeIGC
    {
        public float chaffStrength { get; set; }
    }

    public class DataProbeTypeIGC : DataExpendableTypeIGC
    {
        public float scannerRange { get; set; }
        public float dtimeBurst { get; set; }
        public float dispersion { get; set; }
        public float accuracy { get; set; }
        public short ammo { get; set; }
        public DataProjectileTypeIGC projectile { get; set; }
        public short ambientSound { get; set; }
        public float dtRipcord { get; set; }
    }

    public enum TreasureCode : byte
    {
        c_tcPart        = 1,
        c_tcPowerup     = 2,
        c_tcDevelopment = 3,
        c_tcCash        = 4,
        c_tcFlag        = 5
    }

    public struct PowerupCode
    {
        public const short   c_pcHull   = 0x01;
        public const short   c_pcShield = 0x02;
        public const short   c_pcEnergy = 0x04;
        public const short   c_pcFuel   = 0x08;
        public const short   c_pcAmmo   = 0x10;
    }

    public class  TreasureData
    {
        public short treasureID{ get; set; }
        public TreasureCode treasureCode { get; set; }
        public byte  chance{ get; set; }
    }

    public class DataTreasureSetIGC
    {
        public string  name { get; set; }
        public short   treasureSetID { get; set; }
        public bool    bZoneOnly { get; set; }
        public TreasureData[] data { get; set; }
    }

    public enum StationClassID : byte
    {
        c_scStarbase                    = 0,
        c_scGarrison                    = 1,
        c_scShipyard                    = 2,
        c_scRipcord                     = 3,
        c_scMining                      = 4,
        c_scResearch                    = 5,
        c_scOrdinance                   = 6,
        c_scElectronics                 = 7
    }
    public class  DataStationTypeIGC : DataBuyableIGC
    {
        public float signature { get; set; }
        public float maxArmorHitPoints { get; set; }
        public float maxShieldHitPoints { get; set; }
        public float armorRegeneration { get; set; }
        public float shieldRegeneration { get; set; }
        public float scannerRange { get; set; }
        public int income { get; set; }
        public float radius { get; set; }
        public TechTreeBitMask ttbmLocal { get; set; }
        public short stationTypeID { get; set; }
        public DataStationTypeIGC successorStationType { get; set; }
        public byte defenseTypeArmor { get; set; }
        public byte defenseTypeShield { get; set; }
        public short sabmCapabilities { get; set; }
        public short aabmBuild { get; set; }
        public StationClassID classID { get; set; }

        public DataDroneTypeIGC constructionDroneType { get; set; }

        public short constructorNeedRockSound { get; set; }
        public short constructorUnderAttackSound { get; set; }
        public short constructorDestroyedSound { get; set; }
        public short completionSound { get; set; }

        public short interiorSound { get; set; }
        public short exteriorSound { get; set; }
        public short interiorAlertSound { get; set; }

        public short underAttackSound { get; set; }
        public short criticalSound { get; set; }
        public short destroyedSound { get; set; }
        public short capturedSound { get; set; }

        public short enemyCapturedSound { get; set; }
        public short enemyDestroyedSound { get; set; }

        public string textureName { get; set; }
        public string builderName { get; set; }
    }



    public enum PilotType : byte
    {
        c_ptMiner       =  0,
        c_ptWingman     =  2,
        c_ptLayer       =  5,
        c_ptBuilder     =  6,
        c_ptCarrier     =  9,
        c_ptPlayer      = 10,
        c_ptCheatPlayer = 11
    }

    public class DataDroneTypeIGC : DataBuyableIGC
    {
        public float shootSkill { get; set; }
        public float moveSkill { get; set; }
        public float bravery { get; set; }
        public PilotType pilotType { get; set; }
        public DataHullTypeIGC hullType { get; set; }
        public short droneTypeID { get; set; }
        public DataExpendableTypeIGC etidLaid { get; set; }
    }

    //public struct  Constants
    //{
    //    public float[]   floatConstants;// [c_fcidMax];
    //    public float[][] damageConstants;//[c_dmgidMax][c_defidMax];
    //}

    public struct YawPitchRoll
    {
        public float yaw;
        public float pitch;
        public float roll;
    }

    public struct HardpointData
    {
        public short interiorSound;
        public short turnSound;
        public string frameName; // [c_cbFileName];
        public string locationAbreviation; //[c_cbLocAbrev];
        public short partMask;
        public bool bFixed;
    }
    public class DataHullTypeIGC : DataBuyableIGC
    {
        public float mass { get; set; }
        public float signature { get; set; }
        public float speed { get; set; }
        public YawPitchRoll maxTurnRates { get; set; } //yaw, pitch, roll
        public YawPitchRoll turnTorques { get; set; } //yaw, pitch, roll
        public float thrust { get; set; }
        public float sideMultiplier { get; set; }
        public float backMultiplier { get; set; }
        public float scannerRange { get; set; }
        public float maxFuel { get; set; }
        public float ecm { get; set; }
        public float length { get; set; }
        public float maxEnergy { get; set; }
        public float rechargeRate { get; set; }
        public float ripcordSpeed { get; set; }
        public float ripcordCost { get; set; }

        public short maxAmmo { get; set; }

        public short hullID { get; set; }
        DataHullTypeIGC successorHull { get; set; }
        public byte maxWeapons { get; set; }
        public byte maxFixedWeapons { get; set; }
        public float hitPoints { get; set; }
        public short hardpointOffset { get; set; }

        public byte defenseType { get; set; }

        public short capacityMagazine { get; set; }
        public short capacityDispenser { get; set; }
        public short capacityChaffLauncher { get; set; }

        public DataPartTypeIGC[] preferredPartsTypes { get; set; } //[c_cMaxPreferredPartTypes]

        public short habmCapabilities { get; set; }
        public string textureName { get; set; }

        public short[] pmEquipment { get; set; }//[ET_MAX]

        public short interiorSound { get; set; }
        public short exteriorSound { get; set; }
        public short mainThrusterInteriorSound { get; set; }
        public short mainThrusterExteriorSound { get; set; }
        public short manuveringThrusterInteriorSound { get; set; }
        public short manuveringThrusterExteriorSound { get; set; }

        HardpointData[] Hardpoints { get; set; }
    }
    
    public abstract class HullAbilityBitMask
    {
        public const short c_habmBoard                 = 0x01;
        public const short c_habmRescue                = 0x02;
        public const short c_habmLifepod               = 0x04;
        public const short c_habmCaptureThreat         = 0x08;
        public const short c_habmLandOnCarrier         = 0x10;
        public const short c_habmNoRipcord             = 0x20;
        public const short c_habmIsRipcordTarget       = 0x40;
        public const short c_habmFighter               = 0x80;
        public const short c_habmRemoteLeadIndicator   = 0x100;
        public const short c_habmThreatToStation       = 0x200;
        public const short c_habmCarrier               = 0x400;
        public const short c_habmLeadIndicator         = 0x800;
        public const short c_habmIsLtRipcordTarget     = 0x1000;
        public const short c_habmCanLtRipcord          = 0x2000;
        public const short c_habmMiner                 = 0x4000;
        public const ushort c_habmBuilder              = 0x8000;
    }
    public abstract class StationAbilityBitMask
    {
        public const short     c_sabmUnload                = 0x01;      //Ability to offload mined minerals
        public const short     c_sabmStart                 = 0x02;      //           start the game at this station
        public const short     c_sabmRestart               = 0x04;      //           restart after dying
        public const short     c_sabmRipcord               = 0x08;      //           teleport to the station
        public const short     c_sabmCapture               = 0x10;      //           be captured
        public const short     c_sabmLand                  = 0x20;      //           land at
        public const short     c_sabmRepair                = 0x40;      //           get repaired
        public const short     c_sabmRemoteLeadIndicator   = 0x80;      //           shows up in the loadout menu of stations
        public const short     c_sabmReload                = 0x100;     //           free fuel and ammo on launch
        public const short     c_sabmFlag                  = 0x200;     //           counts for victory
        public const short     c_sabmPedestal              = 0x400;     //           be a pedestal for a flag
        public const short     c_sabmTeleportUnload        = 0x800;     //           be a pedestal for a flag
        public const short     c_sabmCapLand               = 0x1000;    //           land capital ships
        public const short     c_sabmRescue                = 0x2000;    //           rescue pods
        public const short     c_sabmRescueAny             = 0x4000;    //           not used (but reserved for pods)
    }
    public abstract class AsteroidAbilityBitMask
    {
        public const short c_aabmMineHe3 = 0x01;      //Has minable ore of some type (all mutually exclusive)
        public const short c_aabmMineLotsHe3 = 0x02;
        public const short c_aabmMineGold = 0x04;

        public const short c_aabmBuildable = 0x08;      //Buildings can be built on it
        public const short c_aabmSpecial = 0x10;      //Special buildings can be built on it
    }
    public abstract class ExpendableAbilityBitMask
    {
        public const short c_eabmCapture = 0x01;
        public const short c_eabmWarpBombDual = 0x02; // KGJV: both sides aleph rez
        public const short c_eabmWarpBombSingle = 0x04; // KGJV: one side aleph rez
        public const short c_eabmWarpBomb = c_eabmWarpBombDual | c_eabmWarpBombSingle; // KGJV: both types into one for backward compatibility
        public const short c_eabmQuickReady = 0x08;
        public const short c_eabmRipcord = 0x10;
        public const short c_eabmShootStations = 0x20;
        public const short c_eabmShootShips = 0x40;
        public const short c_eabmShootMissiles = 0x80;
        public const short c_eabmShootOnlyTarget = 0x1000;
        public const short c_eabmRescue = StationAbilityBitMask.c_sabmRescue;     //0x2000 Rescue lifepods that collide with it
        public const short c_eabmRescueAny = StationAbilityBitMask.c_sabmRescueAny;  //0x4000 Rescue any lifepod that collide with it
    }
}
