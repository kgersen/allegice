// IGCLIB.H
// Managed versions of IGC enums, structs and classes
// keep in sync with native ones

using namespace System;
using namespace System::Collections;
using namespace System::Drawing;

namespace IGCLib
{ 
	public enum class AsteroidAbilityBitMask : ::AsteroidAbilityBitMask
    {
        c_aabmMineHe3 = 0x01,      //Has minable ore of some type (all mutually exclusive)
        c_aabmMineLotsHe3 = 0x02,
        c_aabmMineGold = 0x04,

        c_aabmBuildable = 0x08,      //Buildings can be built on it
        c_aabmSpecial = 0x10      //Special buildings can be built on it
    };

	public enum class HullAbilityBitMask : unsigned short
    {
        c_habmBoard                 = 0x01,
        c_habmRescue                = 0x02,
        c_habmLifepod               = 0x04,
        c_habmCaptureThreat         = 0x08,
        c_habmLandOnCarrier         = 0x10,
		c_habmNoRipcord             = 0x20,
		c_habmIsRipcordTarget       = 0x40,
		c_habmFighter               = 0x80,
		c_habmRemoteLeadIndicator   = 0x100,
		c_habmThreatToStation       = 0x200,
		c_habmCarrier               = 0x400,
		c_habmLeadIndicator         = 0x800,
		c_habmIsLtRipcordTarget     = 0x1000,
		c_habmCanLtRipcord          = 0x2000,
		c_habmMiner                 = 0x4000,
		c_habmBuilder               = 0x8000
    };

	public enum class StationAbilityBitMask : unsigned short
    {
        c_sabmUnload                = 0x01,      //Ability to offload mined minerals
        c_sabmStart                 = 0x02,      //           start the game at this station
        c_sabmRestart               = 0x04,      //           restart after dying
        c_sabmRipcord               = 0x08,      //           teleport to the station
        c_sabmCapture               = 0x10,      //           be captured
        c_sabmLand                  = 0x20,      //           land at
        c_sabmRepair                = 0x40,      //           get repaired
        c_sabmRemoteLeadIndicator   = 0x80,      //           shows up in the loadout menu of stations
        c_sabmReload                = 0x100,     //           free fuel and ammo on launch
        c_sabmFlag                  = 0x200,     //           counts for victory
        c_sabmPedestal              = 0x400,     //           be a pedestal for a flag
        c_sabmTeleportUnload        = 0x800,     //           be a pedestal for a flag
        c_sabmCapLand               = 0x1000,    //           land capital ships
        c_sabmRescue                = 0x2000,    //           rescue pods
        c_sabmRescueAny             = 0x4000    //           not used (but reserved for pods)
    };

	public enum class ExpendableAbilityBitMask : unsigned short
    {
        c_eabmCapture = 0x01,
        c_eabmWarpBombDual = 0x02, // KGJV: both sides aleph rez
        c_eabmWarpBombSingle = 0x04, // KGJV: one side aleph rez
		c_eabmWarpBomb = ::c_eabmWarpBombDual | ::c_eabmWarpBombSingle, // KGJV: both types into one for backward compatibility
        c_eabmQuickReady = 0x08,
        c_eabmRipcord = 0x10,
        c_eabmShootStations = 0x20,
        c_eabmShootShips = 0x40,
        c_eabmShootMissiles = 0x80,
        c_eabmShootOnlyTarget = 0x1000,
		c_eabmRescue = ::c_eabmRescue,     //0x2000 Rescue lifepods that collide with it
		c_eabmRescueAny = ::c_sabmRescueAny  //0x4000 Rescue any lifepod that collide with it
    };

	public ref struct Constants
    {
	public:
		property array<float>^   floatConstants;// [c_fcidMax];
		property array<array<float>^>^ damageConstants;//[c_dmgidMax][c_defidMax];
	};

	public ref struct GlobalAttributeSet
    {
	public:
        property array<float>^  Attributes; //[c_gaMax];
		static array<String^>^ Names = gcnew array<String^> {
			"Max Speed",
			"Thrust",
			"Turn Rate",
			"Turn Torque",
			"Max Armor Station",
			"Armor Regeneration Station",
			"Max Shield Station",
			"Shield Regeneration Station",
			"Max Armor Ship",
			"Max Shield Ship",
			"Shield Regeneration Ship",
			"Scan Range",
			"Signature",
			"Max Energy",
			"Speed Ammo",
			"Lifespan Energy",
			"TurnRate Missile",
			"Mining Rate",
			"Mining Yield",
			"Mining Capacity",
			"Ripcord Time",
			"Damage Guns",
			"Damage Missiles",
			"Development Cost",
			"Development Time"
		};
		GlobalAttributeSet()
		{
			Attributes = gcnew array<float>(c_gaMax);
		}
	};

	public ref class TechTreeBitMask
	{
	public:
		property BitArray ^ bits;
		TechTreeBitMask()
		{
			bits = gcnew BitArray(c_ttbMax,false);
		}
	};

	public ref class  DataObjectIGC
    {
	public:
		property Color color;
        property float radius;
        property float rotation;
		property String^ modelName;
        property String^ textureName;
	};

	public ref class DataCivilizationIGC
    {
	public:
		property float incomeMoney;
        property float bonusMoney;
        property String^ name;
        property String^ iconName;
        property String^ hudName;
        property TechTreeBitMask^ ttbmBaseTechs;
        property TechTreeBitMask^ ttbmNoDevTechs;
        property GlobalAttributeSet^ gasBaseAttributes;
		property short lifepod;
        property short civilizationID;
        property short initialStationTypeID;
		DataCivilizationIGC()
		{
			ttbmBaseTechs = gcnew TechTreeBitMask();
			ttbmNoDevTechs = gcnew TechTreeBitMask();
			gasBaseAttributes = gcnew GlobalAttributeSet();
		}

	};

    public ref class  DataBuyableIGC
    {
	public:
		property Money price;
        property unsigned int timeToBuild;
        property String^ modelName;
        property String^ iconName;
        property String^ name;
        property String^ description;
        property BuyableGroupID groupID;
        property TechTreeBitMask^ ttbmRequired;
        property TechTreeBitMask^ ttbmEffects;
		DataBuyableIGC()
		{
			ttbmRequired = gcnew TechTreeBitMask();
			ttbmEffects = gcnew TechTreeBitMask();
		}
    };

    public ref class  DataProjectileTypeIGC : DataObjectIGC
    {
	public:
		property float power;
		property float blastPower;
        property float blastRadius;
        property float speed;
        property float lifespan;
        property ProjectileTypeID projectileTypeID;
        property DamageTypeID damageType;
        property bool absoluteF;
        property bool bDirectional;
        property float width;
		property SoundID ambientSound;
	};

	public ref class DataDevelopmentIGC : public DataBuyableIGC
    {
	public:
		property GlobalAttributeSet^ gas;
        property DevelopmentID developmentID;
        property SoundID completionSound;
		DataDevelopmentIGC() : DataBuyableIGC()
		{
			gas = gcnew GlobalAttributeSet();
		}
	};

	public enum class EquipmentType : short
    {
       ET_ChaffLauncher  = 0,
       ET_Weapon         = 1,
       ET_Magazine       = 2,
       ET_Dispenser      = 3,
       ET_Shield         = 4,
       ET_Cloak          = 5,
       ET_Pack           = 6,
       ET_Afterburner    = 7,
	   ET_MAX			 = 8
    };

    public ref class  DataPartTypeIGC : public DataBuyableIGC
    {
	public:
		property float mass;
        property float signature;
        property PartID partID;
        property PartID successorPartID;
        property EquipmentType equipmentType;
        property PartMask partMask;
        property String^ inventoryLineMDL;
    };		

    public ref class DataWeaponTypeIGC : public DataPartTypeIGC
    {
	public:
		property float               dtimeReady;
		property float               dtimeBurst;
		property float               energyPerShot;
		property float               dispersion;
		property short               cAmmoPerShot;
		property ProjectileTypeID    projectileTypeID;
		property SoundID             activateSound;
		property SoundID             singleShotSound;
		property SoundID             burstSound;
    };

    public ref class DataShieldTypeIGC : public DataPartTypeIGC
    {
	public:
		property float           rateRegen;
		property float           maxStrength;
		property DefenseTypeID   defenseType;
		property SoundID         activateSound;
		property SoundID         deactivateSound;
    };

    public ref class DataCloakTypeIGC : public DataPartTypeIGC
    {
	public:
		property float           energyConsumption;
		property float           maxCloaking;
		property float           onRate;
		property float           offRate;
		property SoundID         engageSound;
		property SoundID         disengageSound;
    };

    public ref class DataAfterburnerTypeIGC : public DataPartTypeIGC
    {
	public:
		property float           fuelConsumption;
		property float           maxThrust;
		property float           onRate;
		property float           offRate;
		property SoundID         interiorSound;
		property SoundID         exteriorSound;
    };

    public enum class PackType : Byte
    {
        c_packAmmo    = 0,
        c_packFuel    = 1
    };

    public ref class DataPackTypeIGC : public DataPartTypeIGC
    {
	public:
		property PackType        packType;
		property short           amount;
	};

	public ref class LauncherDef : public DataBuyableIGC
    {
	public:
		property float               signature;
		property float               mass;
		property PartMask            partMask;
		property short               expendableSize;
	};

    public ref class DataExpendableTypeIGC : public DataObjectIGC
    {
	public:
		property float               loadTime;
		property float               lifespan;
		property float               signature;
		property LauncherDef^        launcherDef;
		property HitPoints           hitPoints;
		property DefenseTypeID       defenseType;
		property ExpendableTypeID    expendabletypeID;
		property ExpendableAbilityBitMask      eabmCapabilities;
		property String^             iconName;
		DataExpendableTypeIGC()
		{
			launcherDef = gcnew LauncherDef();
		}
    };

	public ref class  DataMissileTypeIGC : public DataExpendableTypeIGC
	{
	public:
		property float               acceleration;
		property float               turnRate;
		property float               initialSpeed;
		property float               lockTime;
		property float               readyTime;
		property float               maxLock;
		property float               chaffResistance;
		property float               dispersion;
		property float               lockAngle;
		property float               power;
		property float               blastPower;
		property float               blastRadius;
		property float               width;

		property DamageTypeID        damageType;

		property bool                bDirectional;

		property SoundID             launchSound;
		property SoundID             ambientSound;
	};

	public ref class  DataMineTypeIGC : public DataExpendableTypeIGC
	{
	public:
		property float               radius;
		property float               power;
		property float               endurance;
		property DamageTypeID        damageType;
	};

	public ref class  DataChaffTypeIGC : public DataExpendableTypeIGC
	{
	public:
		property float               chaffStrength;
	};

	public ref class  DataProbeTypeIGC : public DataExpendableTypeIGC
	{
	public:
		property float               scannerRange;

		property float               dtimeBurst;
		property float               dispersion;
		property float               accuracy;

		property short               ammo;

		property ProjectileTypeID    projectileTypeID;

		property SoundID             ambientSound;
		property float               dtRipcord;
	};

    public enum class TreasureCode : Byte
    {
        c_tcPart        = 1,
        c_tcPowerup     = 2,
        c_tcDevelopment = 3,
        c_tcCash        = 4,
        c_tcFlag        = 5
    };

    public ref struct PowerupCode
    {
	public:
		static short   c_pcHull   = 0x01;
        static short   c_pcShield = 0x02;
        static short   c_pcEnergy = 0x04;
        static short   c_pcFuel   = 0x08;
        static short   c_pcAmmo   = 0x10;
	};
	public ref struct TreasureData
	{
	public:
		property ObjectID        treasureID;
		property TreasureCode    treasureCode;
		property unsigned char   chance;
	};

	public ref class DataTreasureSetIGC
	{
	public:
		property String^         name;
		property TreasureSetID   treasureSetID;
		//short           nTreasureData;
		property bool            bZoneOnly;
		property List<TreasureData^>^ treasureDatas;
		DataTreasureSetIGC()
		{
			treasureDatas = gcnew List<TreasureData^>();
		}
	};

	public ref class  DataStationTypeIGC : public DataBuyableIGC
	{
	public:
		property float                   signature;
		property float                   maxArmorHitPoints;
		property float                   maxShieldHitPoints;
		property float                   armorRegeneration;
		property float                   shieldRegeneration;
		property float                   scannerRange;
		property Money                   income;
		property float                   radius;
		property TechTreeBitMask^        ttbmLocal;
		property StationTypeID           stationTypeID;
		property StationTypeID           successorStationTypeID;
		property DefenseTypeID           defenseTypeArmor;
		property DefenseTypeID           defenseTypeShield;
		property StationAbilityBitMask   sabmCapabilities;
		property AsteroidAbilityBitMask  aabmBuild;
		property Byte                    classID;

		property DroneTypeID             constructionDroneTypeID;

		property SoundID                 constructorNeedRockSound;
		property SoundID                 constructorUnderAttackSound;
		property SoundID                 constructorDestroyedSound;
		property SoundID                 completionSound;

		property SoundID                 interiorSound;
		property SoundID                 exteriorSound;
		property SoundID                 interiorAlertSound;

		property SoundID                 underAttackSound;
		property SoundID                 criticalSound;
		property SoundID                 destroyedSound;
		property SoundID                 capturedSound;

		property SoundID                 enemyCapturedSound;
		property SoundID                 enemyDestroyedSound;

		property String^                 textureName;
		property String^                 builderName;
		DataStationTypeIGC()
		{
			ttbmLocal = gcnew TechTreeBitMask();
		}
	};

	public enum class PilotType : Byte
	{
		c_ptMiner       =  0,
		c_ptWingman     =  2,
		c_ptLayer       =  5,
		c_ptBuilder     =  6,
		c_ptCarrier     =  9,
		c_ptPlayer      = 10,
		c_ptCheatPlayer = 11
	};

	public ref class DataDroneTypeIGC : public DataBuyableIGC
	{
	public:
		property float               shootSkill;
		property float               moveSkill;
		property float               bravery;
		property PilotType           pilotType;
		property HullID              hullTypeID;
		property DroneTypeID         droneTypeID;
		property ExpendableTypeID    etidLaid;
	};

	public ref class  HardpointData
	{
	public:
		property SoundID     interiorSound;
		property SoundID     turnSound;
		property String^     frameName;
		property String^     locationAbreviation;
		property PartMask    partMask;
		property bool        bFixed;
	};

	public ref struct YawPitchRoll
    {
	public:
        property float Yaw;
        property float Pitch;
        property float Roll;
    };

	public ref class  DataHullTypeIGC : public DataBuyableIGC
	{
	public:
		property float               mass;
		property float               signature;
		property float               speed;
		property YawPitchRoll^		 maxTurnRates;    //yaw, pitch, roll
		property YawPitchRoll^       turnTorques;      //yaw, pitch, roll
		property float               thrust;
		property float               sideMultiplier;
		property float               backMultiplier;
		property float               scannerRange;
		property float               maxFuel;
		property float               ecm;
		property float               length;
		property float               maxEnergy;
		property float               rechargeRate;
		property float               ripcordSpeed;
		property float               ripcordCost;

		property short               maxAmmo;

		property HullID              hullID;
		property HullID              successorHullID;
		//Mount             maxWeapons;
		//Mount             maxFixedWeapons;
		property HitPoints           hitPoints;
		//short               hardpointOffset;
		property List<HardpointData^>^ HardPoints;

		property DefenseTypeID       defenseType;

		property short               capacityMagazine;
		property short               capacityDispenser;
		property short               capacityChaffLauncher;

		property array<PartID>^      preferredPartsTypes; //[c_cMaxPreferredPartTypes];

		property HullAbilityBitMask  habmCapabilities;
		property String^             textureName; // [c_cbFileName];

		property array<PartMask>^    pmEquipment; // [ET_MAX];

		property SoundID             interiorSound;
		property SoundID             exteriorSound;
		property SoundID             mainThrusterInteriorSound;
		property SoundID             mainThrusterExteriorSound;
		property SoundID             manuveringThrusterInteriorSound;
		property SoundID             manuveringThrusterExteriorSound;

		DataHullTypeIGC()
		{
			preferredPartsTypes = gcnew array<PartID>(c_cMaxPreferredPartTypes);
			pmEquipment = gcnew array<PartMask>(ET_MAX);
			HardPoints = gcnew List<HardpointData^>(c_maxMountedWeapons);
			maxTurnRates = gcnew YawPitchRoll();
			turnTorques = gcnew YawPitchRoll();
		}
	};

	public ref class  DataLauncherTypeIGC
	{
	public:
		property short           amount;
		property PartID          partID;
		property PartID          successorPartID;
		property short           launchCount;
		property ObjectID        expendabletypeID;
		property String^         inventoryLineMDL;
	};
}

