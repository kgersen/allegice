using namespace System;
using namespace System::Collections;
using namespace System::Drawing;

namespace IGCLib
{
	public ref struct Constants
    {
	public:
		array<float>^   floatConstants;// [c_fcidMax];
		array<array<float>^>^ damageConstants;//[c_dmgidMax][c_defidMax];
	};

	public ref struct GlobalAttributeSet
    {
	public:
        array<float>^  Attributes; //[c_gaMax];
		GlobalAttributeSet()
		{
			Attributes = gcnew array<float>(c_gaMax);
		}
	};

	public ref class TechTreeBitMask
	{
	public:
		BitArray ^ bits;
		TechTreeBitMask()
		{
			bits = gcnew BitArray(c_ttbMax,false);
		}
	};

	public ref class  DataObjectIGC
    {
	public:
		Color color;
        float radius;
        float rotation;
		String^ modelName;
        String^ textureName;
	};

	public ref class DataCivilizationIGC
    {
	public:
		float incomeMoney;
        float bonusMoney;
        String^ name;
        String^ iconName;
        String^ hudName;
        TechTreeBitMask^ ttbmBaseTechs;
        TechTreeBitMask^ ttbmNoDevTechs;
        GlobalAttributeSet^ gasBaseAttributes;
		short lifepod;
        short civilizationID;
        short initialStationTypeID;
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
		int price;
        unsigned int timeToBuild;
        String^ modelName;
        String^ iconName;
        String^ name;
        String^ description;
        Byte groupID;
        TechTreeBitMask^ ttbmRequired;
        TechTreeBitMask^ ttbmEffects;
		DataBuyableIGC()
		{
			ttbmRequired = gcnew TechTreeBitMask();
			ttbmEffects = gcnew TechTreeBitMask();
		}
    };

    public ref class  DataProjectileTypeIGC : DataObjectIGC
    {
	public:
		float power;
		float blastPower;
        float blastRadius;
        float speed;
        float lifespan;
        short projectileTypeID;
        Byte damageType;
        bool absoluteF;
        bool bDirectional;
        float width;
		short ambientSound;
	};

	public ref class DataDevelopmentIGC : public DataBuyableIGC
    {
	public:
		GlobalAttributeSet^ gas;
        short developmentID;
        short completionSound;
		DataDevelopmentIGC() : DataBuyableIGC()
		{
			gas = gcnew GlobalAttributeSet();
		}
	};

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
    };

    public ref class  DataPartTypeIGC : public DataBuyableIGC
    {
	public:
		float mass;
        float signature;
        short partID;
        short successorPartID;
        EquipmentType equipmentType;
        short partMask;
        String^ inventoryLineMDL;
    };		

    public ref class DataWeaponTypeIGC : public DataPartTypeIGC
    {
	public:
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

    public ref class DataShieldTypeIGC : public DataPartTypeIGC
    {
	public:
		float           rateRegen;
		float           maxStrength;
		DefenseTypeID   defenseType;
		SoundID         activateSound;
		SoundID         deactivateSound;
    };

    public ref class DataCloakTypeIGC : public DataPartTypeIGC
    {
	public:
		float           energyConsumption;
		float           maxCloaking;
		float           onRate;
		float           offRate;
		SoundID         engageSound;
		SoundID         disengageSound;
    };

    public ref class DataAfterburnerTypeIGC : public DataPartTypeIGC
    {
	public:
		float           fuelConsumption;
		float           maxThrust;
		float           onRate;
		float           offRate;
		SoundID         interiorSound;
		SoundID         exteriorSound;
    };

    public enum PackType : Byte
    {
        c_packAmmo    = 0,
        c_packFuel    = 1
    };

    public ref class DataPackTypeIGC : public DataPartTypeIGC
    {
	public:
		PackType        packType;
		short           amount;
	};

	public ref class LauncherDef : public DataBuyableIGC
    {
	public:
		float               signature;
		float               mass;
		PartMask            partMask;
		short               expendableSize;
	};

    public ref class DataExpendableTypeIGC : public DataObjectIGC
    {
	public:
		float               loadTime;
		float               lifespan;
		float               signature;
		LauncherDef^        launcherDef;
		HitPoints           hitPoints;
		DefenseTypeID       defenseType;
		ExpendableTypeID    expendabletypeID;
		AbilityBitMask      eabmCapabilities;
		String^             iconName;
    };

	public ref class  DataMissileTypeIGC : public DataExpendableTypeIGC
	{
	public:
		float               acceleration;
		float               turnRate;
		float               initialSpeed;
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

	public ref class  DataMineTypeIGC : public DataExpendableTypeIGC
	{
	public:
		float               radius;
		float               power;
		float               endurance;
		DamageTypeID        damageType;
	};

	public ref class  DataChaffTypeIGC : public DataExpendableTypeIGC
	{
	public:
		float               chaffStrength;
	};

	public ref class  DataProbeTypeIGC : public DataExpendableTypeIGC
	{
	public:
		float               scannerRange;

		float               dtimeBurst;
		float               dispersion;
		float               accuracy;

		short               ammo;

		ProjectileTypeID    projectileTypeID;

		SoundID             ambientSound;
		float               dtRipcord;
	};

    public enum TreasureCode : Byte
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
		ObjectID        treasureID;
		TreasureCode    treasureCode;
		unsigned char   chance;
	};

	public ref class DataTreasureSetIGC
	{
	public:
		String^         name;
		TreasureSetID   treasureSetID;
		short           nTreasureData;
		bool            bZoneOnly;
		List<TreasureData^>^ treasureDatas;
		DataTreasureSetIGC()
		{
			treasureDatas = gcnew List<TreasureData^>();
		}
	};

	public ref class  DataStationTypeIGC : public DataBuyableIGC
	{
	public:
		float                   signature;
		float                   maxArmorHitPoints;
		float                   maxShieldHitPoints;
		float                   armorRegeneration;
		float                   shieldRegeneration;
		float                   scannerRange;
		Money                   income;
		float                   radius;
		TechTreeBitMask^        ttbmLocal;
		StationTypeID           stationTypeID;
		StationTypeID           successorStationTypeID;
		DefenseTypeID           defenseTypeArmor;
		DefenseTypeID           defenseTypeShield;
		StationAbilityBitMask   sabmCapabilities;
		AsteroidAbilityBitMask  aabmBuild;
		Byte                    classID;

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

		String^                 textureName;
		String^                 builderName;
		DataStationTypeIGC()
		{
			ttbmLocal = gcnew TechTreeBitMask();
		}
	};

	public ref class DataDroneTypeIGC : public DataBuyableIGC
	{
	public:
		float               shootSkill;
		float               moveSkill;
		float               bravery;
		PilotType           pilotType;
		HullID              hullTypeID;
		DroneTypeID         droneTypeID;
		ExpendableTypeID    etidLaid;
	};

	public ref class  HardpointData
	{
	public:
		SoundID     interiorSound;
		SoundID     turnSound;
		String^     frameName;
		String^     locationAbreviation;
		PartMask    partMask;
		bool        bFixed;
	};

	public ref struct YawPitchRoll
    {
	public:
        float Yaw;
        float Pitch;
        float Roll;
    };

	public ref class  DataHullTypeIGC : public DataBuyableIGC
	{
	public:
		float               mass;
		float               signature;
		float               speed;
		YawPitchRoll		maxTurnRates;    //yaw, pitch, roll
		YawPitchRoll        turnTorques;      //yaw, pitch, roll
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
		//Mount             maxWeapons;
		//Mount             maxFixedWeapons;
		HitPoints           hitPoints;
		//short               hardpointOffset;
		array<HardpointData^>^ HardPoints;

		DefenseTypeID       defenseType;

		short               capacityMagazine;
		short               capacityDispenser;
		short               capacityChaffLauncher;

		array<PartID>^      preferredPartsTypes; //[c_cMaxPreferredPartTypes];

		HullAbilityBitMask  habmCapabilities;
		String^             textureName; // [c_cbFileName];

		array<PartMask>^    pmEquipment; // [ET_MAX];

		SoundID             interiorSound;
		SoundID             exteriorSound;
		SoundID             mainThrusterInteriorSound;
		SoundID             mainThrusterExteriorSound;
		SoundID             manuveringThrusterInteriorSound;
		SoundID             manuveringThrusterExteriorSound;

		DataHullTypeIGC()
		{
			preferredPartsTypes = gcnew array<PartID>(c_cMaxPreferredPartTypes);
			pmEquipment = gcnew array<PartMask>(ET_MAX);
			HardPoints = gcnew array<HardpointData^>(c_maxMountedWeapons);
		}
	};
}

/*
?using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace IGCLib
{
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
*/