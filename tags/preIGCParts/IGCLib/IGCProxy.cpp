// This is the main DLL file.
using namespace System;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Collections::Generic;

#include "stdafx.h"
#include "IGCProxy.h"

#define IGC_FILE_VERSION_TYPE   int

namespace IGCLib {

#pragma region macros & converters

// Macros
#define PtoM(field) m->field = p->field
#define PtoMc(field,type) m->field = (type)p->field
#define MtoP(field) p->field = m->field
#define MtoPc(field,type) p->field = (type)m->field
#define String_Load(p) String_Load_Implt(p,sizeof(p))
#define String_Save(m,p) String_Save_Implt(m,p,sizeof(p))
// String
	String^ String_Load_Implt(char *p,int size)
	{
		String^ m = gcnew String(p);
		if (m->Length > size) m->Remove(size);
		return m;
	}
	void String_Save_Implt(String^ m, char* p, int size)
	{
		if (String::IsNullOrEmpty(m)) { *p = 0; return; }
		memset(p,0,size);

		array<Byte>^ bytes = System::Text::ASCIIEncoding::ASCII->GetBytes( m );
		pin_ptr<unsigned char> pinnedbyte = &bytes[0];

		memcpy(p, reinterpret_cast<const char*>( pinnedbyte ),Math::Min(m->Length,size));
	}
// Constants
	void Constants_Load(Constants^ m, ::Constants* p)
	{
		m->floatConstants = gcnew array<float>(c_fcidMax);
		pin_ptr<float> pinnedBuffer = &m->floatConstants[0];
		memcpy(pinnedBuffer,(const void *)(&p->floatConstants[0]),sizeof(float)*c_fcidMax);
		m->damageConstants = gcnew array<array<float>^>(c_dmgidMax);
		for (int i=0;i<c_dmgidMax;i++)
		{
			m->damageConstants[i] = gcnew array<float>(c_defidMax);
			pinnedBuffer = &m->damageConstants[i][0];
			memcpy(pinnedBuffer,(const void *)(&p->damageConstants[i][0]),sizeof(float)*c_defidMax);
		}
	}
	void Constants_Save(Constants^ m, ::Constants* p)
	{
		if (m->floatConstants->Length != c_fcidMax) throw gcnew ArgumentException("invalid size of floatConstants");
        pin_ptr<float> pinnedBuffer = &m->floatConstants[0];
		float *mp = pinnedBuffer;
		memcpy(&p->floatConstants[0],mp,sizeof(float)*c_fcidMax);

		//if (m->damageConstants->Length != c_dmgidMax*c_defidMax) throw gcnew ArgumentException("invalid size of damageConstants");
		for (int i=0;i<c_dmgidMax;i++)
		{
			if (m->damageConstants[i]->Length != c_defidMax) throw gcnew ArgumentException("invalid subsize of damageConstants");
			pinnedBuffer = &m->damageConstants[i][0];
			mp = pinnedBuffer;
			memcpy(&p->damageConstants[i][0],mp,sizeof(float)*c_defidMax);
		}
	}

// GlobalAttributeSet
	void GlobalAttributeSet_Load(GlobalAttributeSet^ m, ::GlobalAttributeSet gas)
	{
		for (::GlobalAttribute i=0;i<c_gaMax;i++)
			m->Attributes[i]=gas.GetAttribute(i);
	}

	void GlobalAttributeSet_Save(GlobalAttributeSet^ m, ::GlobalAttributeSet *gas)
	{
		for (::GlobalAttribute i=0;i<c_gaMax;i++)
			gas->SetAttribute(i,m->Attributes[i]);
	}
// TechTreeBitMask
	void TechTreeBitMask_Load(TechTreeBitMask^ m, ::TechTreeBitMask ttbm)
	{
		for (int i=0;i<c_ttbMax;i++)
			m->bits->Set(i,ttbm.GetBit(i));
	}
	void TechTreeBitMask_Save(TechTreeBitMask^ m, ::TechTreeBitMask* ttbm)
	{
		ttbm->ClearAll();
		for (int i=0;i<c_ttbMax;i++)
			if (m->bits->Get(i))
				ttbm->SetBit(i);
	}
// DataObjectIGC
	void DataObjectIGC_Load(DataObjectIGC^ m, ::DataObjectIGC *p)
	{
		m->color = Color::FromArgb((int)(p->color.a*255.0f),(int)(p->color.r*255.0f),(int)(p->color.g*255.0f),(int)(p->color.b*255.0f));
		m->radius = p->radius;
		m->rotation = p->rotation;
		m->modelName = String_Load(p->modelName);
		m->textureName = String_Load(p->textureName);
	}
	void DataObjectIGC_Save(DataObjectIGC^ m, ::DataObjectIGC *p)
	{
		p->color.a = (float)m->color.A / 255.0f;
		p->color.r = (float)m->color.R / 255.0f;
		p->color.g = (float)m->color.G / 255.0f;
		p->color.b = (float)m->color.B / 255.0f;
		p->radius = m->radius;
		p->rotation = m->rotation;

		String_Save(m->modelName,p->modelName);
		String_Save(m->textureName,p->textureName);
	}
// DataCivilizationIGC
	void DataCivilizationIGC_Load(DataCivilizationIGC^ m, ::DataCivilizationIGC* p)
	{
		m->incomeMoney = p->incomeMoney;
		m->bonusMoney = p->bonusMoney;
		m->name = String_Load(p->name);
		m->iconName = String_Load(p->iconName);
		m->hudName  = String_Load(p->hudName);
		TechTreeBitMask_Load(m->ttbmBaseTechs, p->ttbmBaseTechs);
		TechTreeBitMask_Load(m->ttbmNoDevTechs, p->ttbmNoDevTechs);
		GlobalAttributeSet_Load(m->gasBaseAttributes, p->gasBaseAttributes);
		m->lifepod = p->lifepod;
		m->civilizationID = p->civilizationID;
		m->initialStationTypeID = p->initialStationTypeID;
	}
	void DataCivilizationIGC_Save(DataCivilizationIGC^ m, ::DataCivilizationIGC* p)
	{
		p->incomeMoney = m->incomeMoney;
		p->bonusMoney = m->bonusMoney;
		
		String_Save(m->name, p->name);
		String_Save(m->iconName, p->iconName);
		String_Save(m->hudName, p->hudName);

		TechTreeBitMask_Save(m->ttbmBaseTechs,&p->ttbmBaseTechs);
		TechTreeBitMask_Save(m->ttbmNoDevTechs,&p->ttbmNoDevTechs);
		GlobalAttributeSet_Save(m->gasBaseAttributes, &p->gasBaseAttributes);
		p->lifepod = m->lifepod;
		p->civilizationID = m->civilizationID;
		p->initialStationTypeID = m->initialStationTypeID;
	}
// DataBuyableIGC
	void DataBuyableIGC_Load(DataBuyableIGC^ m, ::DataBuyableIGC *p)
	{
		m->price = p->price;
		m->timeToBuild = p->timeToBuild;

		m->modelName = String_Load(p->modelName);
		m->iconName = String_Load(p->iconName);
		m->name = String_Load(p->name);
		m->description = String_Load(p->description);

		m->groupID = p->groupID;
		TechTreeBitMask_Load(m->ttbmRequired, p->ttbmRequired);
		TechTreeBitMask_Load(m->ttbmEffects, p->ttbmEffects);
	}
	void DataBuyableIGC_Save(DataBuyableIGC^ m, ::DataBuyableIGC *p)
	{
		p->price = m->price;
		p->timeToBuild = m->timeToBuild;
		String_Save(m->modelName,p->modelName);
		String_Save(m->iconName,p->iconName);
		String_Save(m->name,p->name);
		String_Save(m->description,p->description);
		p->groupID = m->groupID;
		TechTreeBitMask_Save(m->ttbmRequired, &p->ttbmRequired);
		TechTreeBitMask_Save(m->ttbmEffects, &p->ttbmEffects);
	}
// DataProjectileTypeIGC
	void DataProjectileTypeIGC_Load(DataProjectileTypeIGC^ m, ::DataProjectileTypeIGC* p)
	{
		DataObjectIGC_Load(m,p);
		m->power = p->power;
		m->blastPower = p->blastPower;
		m->blastRadius = p->blastRadius;
		m->speed = p->speed;
		m->lifespan = p->lifespan;
		m->projectileTypeID = p->projectileTypeID;
		m->damageType = p->damageType;
		m->absoluteF = p->absoluteF;
		m->bDirectional = p->bDirectional;
		m->width = p->width;
		m->ambientSound = p->ambientSound;
	}
	void DataProjectileTypeIGC_Save(DataProjectileTypeIGC^ m, ::DataProjectileTypeIGC *p)
	{
		DataObjectIGC_Save(m,p);
		p->power = m->power;
		p->blastPower = m->blastPower;
		p->blastRadius = m->blastRadius;
		p->speed = m->speed;
		p->lifespan = m->lifespan;
		p->projectileTypeID = m->projectileTypeID;
		p->damageType = m->damageType;
		p->absoluteF = m->absoluteF;
		p->bDirectional = m->bDirectional;
		p->width = m->width;
		p->ambientSound = m->ambientSound;
	}
// DataDevelopmentIGC
	void DataDevelopmentIGC_Load(DataDevelopmentIGC^ m, ::DataDevelopmentIGC *p)
	{
		DataBuyableIGC_Load(m,p);
		GlobalAttributeSet_Load(m->gas, p->gas);
		m->developmentID = p->developmentID;
		m->completionSound = p->completionSound;
	}
	void DataDevelopmentIGC_Save(DataDevelopmentIGC^ m, ::DataDevelopmentIGC *p)
	{
		DataBuyableIGC_Save(m,p);
		GlobalAttributeSet_Save(m->gas, &p->gas);
		p->developmentID = m->developmentID;
		p->completionSound = m->completionSound;
	}
// DataPartTypeIGC
	void DataPartTypeIGC_Load(DataPartTypeIGC^ m, ::DataPartTypeIGC *p)
	{
		DataBuyableIGC_Load(m,p);
		m->mass = p->mass;
		m->signature = p->signature;
		m->partID = p->partID;
		m->successorPartID = p->successorPartID;
		m->equipmentType = (EquipmentType)p->equipmentType;
		m->partMask = p->partMask;
		m->inventoryLineMDL = String_Load(p->inventoryLineMDL);
	}
	void DataPartTypeIGC_Save(DataPartTypeIGC^ m, ::DataPartTypeIGC *p)
	{
		DataBuyableIGC_Save(m,p);
		p->mass = m->mass;
		p->signature = m->signature;
		p->partID = m->partID;
		p->successorPartID = m->successorPartID;
		p->equipmentType = (::EquipmentType)m->equipmentType;
		p->partMask = m->partMask;
		String_Save(m->inventoryLineMDL,p->inventoryLineMDL);
	}
// DataWeaponTypeIGC
	void DataWeaponTypeIGC_Load(DataWeaponTypeIGC^ m, ::DataWeaponTypeIGC *p)
	{
		DataPartTypeIGC_Load(m,p);
		m->dtimeReady = p->dtimeReady;
		m->dtimeBurst = p->dtimeBurst;
		m->energyPerShot = p->energyPerShot;
		m->dispersion = p->dispersion;
		m->projectileTypeID = p->projectileTypeID;
		m->activateSound = p->activateSound;
		m->singleShotSound = p->singleShotSound;
		m->burstSound = p->burstSound;
	}
	void DataWeaponTypeIGC_Save(DataWeaponTypeIGC^ m, ::DataWeaponTypeIGC *p)
	{
		DataPartTypeIGC_Save(m,p);
		p->dtimeReady = m->dtimeReady;
		p->dtimeBurst = m->dtimeBurst;
		p->energyPerShot = m->energyPerShot;
		p->dispersion = m->dispersion;
		p->projectileTypeID = m->projectileTypeID;
		p->activateSound = m->activateSound;
		p->singleShotSound = m->singleShotSound;
		p->burstSound = m->burstSound;
	}
// DataPackTypeIGC
	void DataPackTypeIGC_Load(DataPackTypeIGC^ m, ::DataPackTypeIGC *p)
	{
		DataPartTypeIGC_Load(m,p);
		m->packType = (PackType)p->packType;
		m->amount = p->amount;
	}
	void DataPackTypeIGC_Save(DataPackTypeIGC^ m, ::DataPackTypeIGC *p)
	{
		DataPartTypeIGC_Save(m,p);
		p->packType = (::PackType)m->packType;
		p->amount = m->amount;
	}
// LauncherDef
	void LauncherDef_Load(LauncherDef^ m, ::LauncherDef *p)
	{
		DataBuyableIGC_Load(m,p);
		m->signature = p->signature;
		m->mass = p->mass;
		m->partMask = p->partMask;
		m->expendableSize = p->expendableSize;
	};
	void LauncherDef_Save(LauncherDef^ m, ::LauncherDef *p)
	{
		DataBuyableIGC_Save(m,p);
		p->signature = m->signature;
		p->mass = m->mass;
		p->partMask = m->partMask;
		p->expendableSize = m->expendableSize;
	};
// DataExpendableTypeIGC
	void DataExpendableTypeIGC_Load(DataExpendableTypeIGC^ m,::DataExpendableTypeIGC *p)
	{
		DataObjectIGC_Load(m,p);
		m->loadTime = p->loadTime;
		m->lifespan = p->lifespan;
		m->signature = p->signature;
		LauncherDef_Load(m->launcherDef,&p->launcherDef);
		m->hitPoints = p->hitPoints;
		m->defenseType = p->defenseType;
		m->expendabletypeID = p->expendabletypeID;
		m->eabmCapabilities = (ExpendableAbilityBitMask)p->eabmCapabilities;
		m->iconName = String_Load(p->iconName);
	}
	void DataExpendableTypeIGC_Save(DataExpendableTypeIGC^ m,::DataExpendableTypeIGC *p)
	{
		DataObjectIGC_Save(m,p);
		p->loadTime = m->loadTime;
		p->lifespan = m->lifespan;
		p->signature = m->signature;
		LauncherDef_Save(m->launcherDef,&p->launcherDef);
		p->hitPoints = m->hitPoints;
		p->defenseType = m->defenseType;
		p->expendabletypeID = m->expendabletypeID;
		p->eabmCapabilities = (::AbilityBitMask)m->eabmCapabilities;
		String_Save(m->iconName,p->iconName);
	}
// DataMissileTypeIGC
	void  DataMissileTypeIGC_Load(DataMissileTypeIGC^ m, ::DataMissileTypeIGC* p)
	{
		DataExpendableTypeIGC_Load(m,p);
		PtoM(acceleration);
		PtoM(turnRate);
		PtoM(initialSpeed);
		PtoM(lockTime);
		PtoM(readyTime);
		PtoM(maxLock);
		PtoM(chaffResistance);
		PtoM(dispersion);
		PtoM(lockAngle);
		PtoM(power);
		PtoM(blastPower);
		PtoM(blastRadius);
		PtoM(width);
		PtoM(damageType);
		PtoM(bDirectional);
		PtoM(launchSound);
		PtoM(ambientSound);
	};
	void  DataMissileTypeIGC_Save(DataMissileTypeIGC^ m, ::DataMissileTypeIGC* p)
	{
		DataExpendableTypeIGC_Save(m,p);
		MtoP(acceleration);
		MtoP(turnRate);
		MtoP(initialSpeed);
		MtoP(lockTime);
		MtoP(readyTime);
		MtoP(maxLock);
		MtoP(chaffResistance);
		MtoP(dispersion);
		MtoP(lockAngle);
		MtoP(power);
		MtoP(blastPower);
		MtoP(blastRadius);
		MtoP(width);
		MtoP(damageType);
		MtoP(bDirectional);
		MtoP(launchSound);
		MtoP(ambientSound);
	};
// DataMineTypeIGC
	void DataMineTypeIGC_Load(DataMineTypeIGC^ m, ::DataMineTypeIGC *p)
	{
		DataExpendableTypeIGC_Load(m,p);
		m->mineRadius = p->radius;
		m->power = p->power;
		m->endurance = p->endurance;
		m->damageType = p->damageType;
	}
	void DataMineTypeIGC_Save(DataMineTypeIGC^ m, ::DataMineTypeIGC *p)
	{
		DataExpendableTypeIGC_Save(m,p);
		p->radius = m->mineRadius;
		p->power = m->power;
		p->endurance = m->endurance;
		p->damageType = m->damageType;
	}
// DataChaffTypeIGC
	void DataChaffTypeIGC_Load(DataChaffTypeIGC^ m,::DataChaffTypeIGC *p)
	{
		DataExpendableTypeIGC_Load(m,p);
		m->chaffStrength = p->chaffStrength;
	}
	void DataChaffTypeIGC_Save(DataChaffTypeIGC^ m,::DataChaffTypeIGC *p)
	{
		DataExpendableTypeIGC_Save(m,p);
		p->chaffStrength = m->chaffStrength;
	}
// DataProbeTypeIGC
	void DataProbeTypeIGC_Load(DataProbeTypeIGC^ m, ::DataProbeTypeIGC *p)
	{
		DataExpendableTypeIGC_Load(m,p);
		m->scannerRange = p->scannerRange;
		m->dtimeBurst = p->dtimeBurst;
		m->dispersion = p->dispersion;
		m->accuracy = p->accuracy;
		m->ammo = p->ammo;
		m->projectileTypeID = p->projectileTypeID;
		m->ambientSound = p->ambientSound;
		m->dtRipcord = p->dtRipcord;
	}
	void DataProbeTypeIGC_Save(DataProbeTypeIGC^ m, ::DataProbeTypeIGC *p)
	{
		DataExpendableTypeIGC_Save(m,p);
		p->scannerRange = m->scannerRange;
		p->dtimeBurst = m->dtimeBurst;
		p->dispersion = m->dispersion;
		p->accuracy = m->accuracy;
		p->ammo = m->ammo;
		p->projectileTypeID = m->projectileTypeID;
		p->ambientSound = m->ambientSound;
		p->dtRipcord = m->dtRipcord;
	}
// DataShieldTypeIGC
	void DataShieldTypeIGC_Load(DataShieldTypeIGC^ m,::DataShieldTypeIGC* p)
    {
		DataPartTypeIGC_Load(m,p);
		m->rateRegen = p->rateRegen;
		m->maxStrength = p->maxStrength;
		m->defenseType = p->defenseType;
		m->activateSound = p->activateSound;
		m->deactivateSound = p->deactivateSound;
    }
	void DataShieldTypeIGC_Save(DataShieldTypeIGC^ m,::DataShieldTypeIGC* p)
    {
		DataPartTypeIGC_Save(m,p);
		p->rateRegen = m->rateRegen;
		p->maxStrength = m->maxStrength;
		p->defenseType = m->defenseType;
		p->activateSound = m->activateSound;
		p->deactivateSound = m->deactivateSound;
    }
// DataCloakTypeIGC
	void DataCloakTypeIGC_Load(DataCloakTypeIGC^ m,::DataCloakTypeIGC* p)
    {
		DataPartTypeIGC_Load(m,p);
		m->energyConsumption = p->energyConsumption;
		m->maxCloaking = p->maxCloaking;
		m->onRate = p->onRate;
		m->offRate = p->offRate;
		m->engageSound = p->engageSound;
		m->disengageSound = p->disengageSound;
    }
	void DataCloakTypeIGC_Save(DataCloakTypeIGC^ m,::DataCloakTypeIGC* p)
    {
		DataPartTypeIGC_Save(m,p);
		p->energyConsumption = m->energyConsumption;
		p->maxCloaking = m->maxCloaking;
		p->onRate = m->onRate;
		p->offRate = m->offRate;
		p->engageSound = m->engageSound;
		p->disengageSound = m->disengageSound;
    }
// DataAfterburnerTypeIGC
	void DataAfterburnerTypeIGC_Load(DataAfterburnerTypeIGC^ m, ::DataAfterburnerTypeIGC* p)
    {
		DataPartTypeIGC_Load(m,p);
		m->fuelConsumption = p->fuelConsumption;
		m->maxThrust = p->maxThrust;
		m->onRate = p->onRate;
		m->offRate = p->offRate;
		m->interiorSound = p->interiorSound;
		m->exteriorSound = p->exteriorSound;
    }
	void DataAfterburnerTypeIGC_Save(DataAfterburnerTypeIGC^ m, ::DataAfterburnerTypeIGC* p)
    {
		DataPartTypeIGC_Save(m,p);
		p->fuelConsumption = m->fuelConsumption;
		p->maxThrust = m->maxThrust;
		p->onRate = m->onRate;
		p->offRate = m->offRate;
		p->interiorSound = m->interiorSound;
		p->exteriorSound = m->exteriorSound;
    }
// TreasureData
	void TreasureData_Load(TreasureData^ m,::TreasureData* p)
	{
		PtoM(treasureID);
		m->treasureCode = (TreasureCode)p->treasureCode;
		PtoM(chance);
	}
	
	void TreasureData_Save(TreasureData^ m,::TreasureData* p)
	{
		MtoP(treasureID);
		MtoPc(treasureCode,::PackType);
		MtoP(chance);
	}
// DataTreasureSetIGC
	void DataTreasureSetIGC_Load(DataTreasureSetIGC^ m, ::DataTreasureSetIGC* p)
	{
		m->name = String_Load(p->name);
		PtoM(treasureSetID);
		PtoM(bZoneOnly);
		m->treasureDatas->Clear();
		for (int i=0;i<p->nTreasureData;i++)
		{
			TreasureData^ d = gcnew TreasureData();
			TreasureData_Load(d,p->treasureData0()+i);
			m->treasureDatas->Add(d);
		}
	}
	void DataTreasureSetIGC_Save(DataTreasureSetIGC^ m, ::DataTreasureSetIGC* p)
	{
		String_Save(m->name,p->name);
		MtoP(treasureSetID);
		MtoP(bZoneOnly);
		p->nTreasureData = (short)m->treasureDatas->Count;
		for (int i=0;i<p->nTreasureData;i++)
		{
			TreasureData_Save(m->treasureDatas[i],p->treasureData0()+i);
		}
	}
// DataStationTypeIGC
	void DataStationTypeIGC_Load(DataStationTypeIGC^ m,::DataStationTypeIGC* p)
	{
		DataBuyableIGC_Load(m,p);
		PtoM(signature);
		PtoM(maxArmorHitPoints);
		PtoM(maxShieldHitPoints);
		PtoM(armorRegeneration);
		PtoM(shieldRegeneration);
		PtoM(scannerRange);
		PtoM(income);
		PtoM(radius);
		TechTreeBitMask_Load(m->ttbmLocal,p->ttbmLocal);
		PtoM(stationTypeID);
		PtoM(successorStationTypeID);
		PtoM(defenseTypeArmor);
		PtoM(defenseTypeShield);
		PtoMc(sabmCapabilities,StationAbilityBitMask);
		PtoMc(aabmBuild,AsteroidAbilityBitMask);
		PtoM(classID);
		PtoM(constructionDroneTypeID);
		PtoM(constructorNeedRockSound);
		PtoM(constructorUnderAttackSound);
		PtoM(constructorDestroyedSound);
		PtoM(completionSound);
		PtoM(interiorSound);
		PtoM(exteriorSound);
		PtoM(interiorAlertSound);
		PtoM(underAttackSound);
		PtoM(criticalSound);
		PtoM(destroyedSound);
		PtoM(capturedSound);
		PtoM(enemyCapturedSound);
		PtoM(enemyDestroyedSound);
		m->textureName = String_Load(p->textureName);
		m->builderName = String_Load(p->builderName);
	}
	void DataStationTypeIGC_Save(DataStationTypeIGC^ m,::DataStationTypeIGC* p)
	{
		DataBuyableIGC_Save(m,p);
		MtoP(signature);
		MtoP(maxArmorHitPoints);
		MtoP(maxShieldHitPoints);
		MtoP(armorRegeneration);
		MtoP(shieldRegeneration);
		MtoP(scannerRange);
		MtoP(income);
		MtoP(radius);
		TechTreeBitMask_Save(m->ttbmLocal,&p->ttbmLocal);
		MtoP(stationTypeID);
		MtoP(successorStationTypeID);
		MtoP(defenseTypeArmor);
		MtoP(defenseTypeShield);
		MtoPc(sabmCapabilities,::StationAbilityBitMask);
		MtoPc(aabmBuild,::AsteroidAbilityBitMask);
		MtoP(classID);
		MtoP(constructionDroneTypeID);
		MtoP(constructorNeedRockSound);
		MtoP(constructorUnderAttackSound);
		MtoP(constructorDestroyedSound);
		MtoP(completionSound);
		MtoP(interiorSound);
		MtoP(exteriorSound);
		MtoP(interiorAlertSound);
		MtoP(underAttackSound);
		MtoP(criticalSound);
		MtoP(destroyedSound);
		MtoP(capturedSound);
		MtoP(enemyCapturedSound);
		MtoP(enemyDestroyedSound);
		String_Save(m->textureName,p->textureName);
		String_Save(m->builderName,p->builderName);
	}
// DataDroneTypeIGC
	void DataDroneTypeIGC_Load(DataDroneTypeIGC^ m, ::DataDroneTypeIGC* p)
	{
		DataBuyableIGC_Load(m,p);
		PtoM(shootSkill);
		PtoM(moveSkill);
		PtoM(bravery);
		PtoMc(pilotType,PilotType);
		PtoM(hullTypeID);
		PtoM(droneTypeID);
		PtoM(etidLaid);
	}
	void DataDroneTypeIGC_Save(DataDroneTypeIGC^ m, ::DataDroneTypeIGC* p)
	{
		DataBuyableIGC_Save(m,p);
		MtoP(shootSkill);
		MtoP(moveSkill);
		MtoP(bravery);
		MtoPc(pilotType,::PilotType);
		MtoP(hullTypeID);
		MtoP(droneTypeID);
		MtoP(etidLaid);
	}
// HardpointData
	void HardpointData_Load(HardpointData^ m,::HardpointData* p)
	{
		PtoM(interiorSound);
		PtoM(turnSound);
		m->frameName = String_Load(p->frameName);
		m->locationAbreviation = String_Load(p->locationAbreviation);
		PtoM(partMask);
		PtoM(bFixed);
	};
	void HardpointData_Save(HardpointData^ m,::HardpointData* p)
	{
		MtoP(interiorSound);
		MtoP(turnSound);
		String_Save(m->frameName , p->frameName);
		String_Save(m->locationAbreviation, p->locationAbreviation);
		MtoP(partMask);
		MtoP(bFixed);
	};
// DataHullTypeIGC
	void DataHullTypeIGC_Load(DataHullTypeIGC^ m,::DataHullTypeIGC *p)
	{
		DataBuyableIGC_Load(m,p);
		PtoM(mass);
		PtoM(signature);
		PtoM(speed);

		m->maxTurnRates.Yaw = p->maxTurnRates[c_axisYaw];
		m->maxTurnRates.Pitch = p->maxTurnRates[c_axisPitch];
		m->maxTurnRates.Roll = p->maxTurnRates[c_axisRoll];

		m->turnTorques.Yaw = p->turnTorques[c_axisYaw];
		m->turnTorques.Pitch = p->turnTorques[c_axisPitch];
		m->turnTorques.Roll = p->turnTorques[c_axisRoll];

		PtoM(thrust);
		PtoM(sideMultiplier);
		PtoM(backMultiplier);
		PtoM(scannerRange);
		PtoM(maxFuel);
		PtoM(ecm);
		PtoM(length);
		PtoM(maxEnergy);
		PtoM(rechargeRate);
		PtoM(ripcordSpeed);
		PtoM(ripcordCost);

		PtoM(maxAmmo);

		PtoM(hullID);
		PtoM(successorHullID);
		//Mount             maxWeapons;
		//Mount             maxFixedWeapons;
		PtoM(hitPoints);
		//short               hardpointOffset;
		m->HardPoints->Clear();
		for (int i=0;i<p->maxWeapons;i++)
		{
			HardpointData^ hp = gcnew HardpointData();
			HardpointData_Load(hp,&((::HardpointData*)(((char*)p) + p->hardpointOffset))[i]);
			m->HardPoints->Add(hp);
		}

		PtoM(defenseType);

		PtoM(capacityMagazine);
		PtoM(capacityDispenser);
		PtoM(capacityChaffLauncher);

		for (int i=0;i<c_cMaxPreferredPartTypes;i++)
			m->preferredPartsTypes[i] = p->preferredPartsTypes[i];

		PtoMc(habmCapabilities,HullAbilityBitMask);
		m->textureName = String_Load(p->textureName);

		for (int i=0;i<ET_MAX;i++)
			m->pmEquipment[i] = p->pmEquipment[i];

		PtoM(interiorSound);
		PtoM(exteriorSound);
		PtoM(mainThrusterInteriorSound);
		PtoM(mainThrusterExteriorSound);
		PtoM(manuveringThrusterInteriorSound);
		PtoM(manuveringThrusterExteriorSound);
	}
	void DataHullTypeIGC_Save(DataHullTypeIGC^ m,::DataHullTypeIGC *p)
	{
		DataBuyableIGC_Save(m,p);
		MtoP(mass);
		MtoP(signature);
		MtoP(speed);
		
		p->maxTurnRates[c_axisYaw] = m->maxTurnRates.Yaw;
		p->maxTurnRates[c_axisPitch] = m->maxTurnRates.Pitch;
		p->maxTurnRates[c_axisRoll] = m->maxTurnRates.Roll; 

		p->turnTorques[c_axisYaw] = m->turnTorques.Yaw;
		p->turnTorques[c_axisPitch] = m->turnTorques.Pitch;
		p->turnTorques[c_axisRoll] = m->turnTorques.Roll; 

		MtoP(thrust);
		MtoP(sideMultiplier);
		MtoP(backMultiplier);
		MtoP(scannerRange);
		MtoP(maxFuel);
		MtoP(ecm);
		MtoP(length);
		MtoP(maxEnergy);
		MtoP(rechargeRate);
		MtoP(ripcordSpeed);
		MtoP(ripcordCost);

		MtoP(maxAmmo);

		MtoP(hullID);
		MtoP(successorHullID);

		MtoP(hitPoints);
		p->hardpointOffset=sizeof(::DataHullTypeIGC);
		p->maxWeapons = (::Mount)m->HardPoints->Count;
		Mount maxFixed = 0; 
		for (int i=0;i<m->HardPoints->Count;i++)
		{
			if (m->HardPoints[i]->bFixed) maxFixed++;
			HardpointData_Save(m->HardPoints[i],(::HardpointData*)(((char*)p) + p->hardpointOffset + i * sizeof(::HardpointData)));
		}
		p->maxFixedWeapons = maxFixed;

		MtoP(defenseType);

		MtoP(capacityMagazine);
		MtoP(capacityDispenser);
		MtoP(capacityChaffLauncher);

		for (int i=0;i<c_cMaxPreferredPartTypes;i++)
			p->preferredPartsTypes[i] = m->preferredPartsTypes[i];

		MtoPc(habmCapabilities,::HullAbilityBitMask);
		String_Save(m->textureName, p->textureName);

		for (int i=0;i<ET_MAX;i++)
			p->pmEquipment[i] = m->pmEquipment[i];

		MtoP(interiorSound);
		MtoP(exteriorSound);
		MtoP(mainThrusterInteriorSound);
		MtoP(mainThrusterExteriorSound);
		MtoP(manuveringThrusterInteriorSound);
		MtoP(manuveringThrusterExteriorSound);
	}
// DataLauncherTypeIGC
	void DataLauncherTypeIGC_Load(DataLauncherTypeIGC^ m,::DataLauncherTypeIGC* p)
	{
		PtoM(amount);
		PtoM(partID);
		PtoM(successorPartID);
		PtoM(launchCount);
		PtoM(expendabletypeID);
		m->inventoryLineMDL = String_Load(p->inventoryLineMDL);
	}
	void DataLauncherTypeIGC_Save(DataLauncherTypeIGC^ m,::DataLauncherTypeIGC* p)
	{
		MtoP(amount);
		MtoP(partID);
		MtoP(successorPartID);
		MtoP(launchCount);
		MtoP(expendabletypeID);
		String_Save(m->inventoryLineMDL, p->inventoryLineMDL);
	}

#pragma endregion
#pragma region readers/writers

// Exceptions
	void MSizeAssert(int size1,int size2,String^ msg)
	{
		if (size1 != size2)
			throw gcnew InvalidOperationException("bad sized "+msg+" block found"); 
	}

	DataTreasureSetIGC^ ReadtreasureSetIGC(char *data, int size)
	{
		DataTreasureSetIGC^ m = gcnew DataTreasureSetIGC();
		::DataTreasureSetIGC* p = (::DataTreasureSetIGC *)data;
		MSizeAssert(size, sizeof(::DataTreasureSetIGC)+p->nTreasureData*sizeof(::TreasureData), "TreasureSet");
		DataTreasureSetIGC_Load(m,p);
		return m;
	}
	DataCivilizationIGC^ ReadcivilizationIGC(char *data, int size)
	{
		MSizeAssert(size, sizeof(::DataCivilizationIGC),"Civilization");
		DataCivilizationIGC^ m = gcnew DataCivilizationIGC();
		DataCivilizationIGC_Load(m,(::DataCivilizationIGC *)data);
		return m;
	}
	DataProjectileTypeIGC^ ReadprojectileTypeIGC(char *data, int size)
	{
		MSizeAssert(size, sizeof(::DataProjectileTypeIGC),"ProjectileType");
		DataProjectileTypeIGC^ proj = gcnew DataProjectileTypeIGC();
		DataProjectileTypeIGC_Load(proj,(::DataProjectileTypeIGC*)data);
		return proj;
	}
	DataHullTypeIGC^ ReadhullTypeIGC(char *data, int size)
	{
		DataHullTypeIGC^ m = gcnew DataHullTypeIGC();
		::DataHullTypeIGC* p = (::DataHullTypeIGC *)data;
		MSizeAssert(size, sizeof(::DataHullTypeIGC)+p->maxWeapons*sizeof(::HardpointData),"HullType");
		DataHullTypeIGC_Load(m,p);
		return m;
	}
	DataStationTypeIGC^ ReadstationTypeIGC(char *data, int size)
	{
		MSizeAssert(size, sizeof(::DataStationTypeIGC),"StationType");
		DataStationTypeIGC^ m = gcnew DataStationTypeIGC();
		DataStationTypeIGC_Load(m,(::DataStationTypeIGC *)data);
		return m;
	}
	DataDevelopmentIGC^ ReaddevelopmentIGC(char *data, int size)
	{
		MSizeAssert(size, sizeof(::DataDevelopmentIGC),"Development");
		DataDevelopmentIGC^ m = gcnew DataDevelopmentIGC();
		DataDevelopmentIGC_Load(m,(::DataDevelopmentIGC *)data);
		return m;
	}
	DataMissileTypeIGC^ ReadmissileTypeIGC(char *data, int size)
	{
		MSizeAssert(size, sizeof(::DataMissileTypeIGC),"MissileType");
		DataMissileTypeIGC^ m = gcnew DataMissileTypeIGC();
		DataMissileTypeIGC_Load(m,(::DataMissileTypeIGC *)data);
		return m;
	}
	DataMineTypeIGC^ ReadmineTypeIGC(char *data, int size)
	{
		MSizeAssert(size, sizeof(::DataMineTypeIGC),"MineType");
		DataMineTypeIGC^ m = gcnew DataMineTypeIGC();
		DataMineTypeIGC_Load(m,(::DataMineTypeIGC *)data);
		return m;
	}
	DataChaffTypeIGC^ ReadchaffTypeIGC(char *data, int size)
	{
		DataChaffTypeIGC^ m = gcnew DataChaffTypeIGC();
		DataChaffTypeIGC_Load(m,(::DataChaffTypeIGC *)data);
		return m;
	}
	DataProbeTypeIGC^ ReadprobeTypeIGC(char *data, int size)
	{
		DataProbeTypeIGC^ m = gcnew DataProbeTypeIGC();
		DataProbeTypeIGC_Load(m,(::DataProbeTypeIGC *)data);
		return m;
	}
	DataDroneTypeIGC^ ReaddroneTypeIGC(char *data, int size)
	{
		DataDroneTypeIGC^ m = gcnew DataDroneTypeIGC();
		DataDroneTypeIGC_Load(m,(::DataDroneTypeIGC *)data);
		return m;
	}
	DataLauncherTypeIGC^ ReadlauncherTypeIGC(char *data, int size)
	{
		DataLauncherTypeIGC^ m = gcnew DataLauncherTypeIGC();
		DataLauncherTypeIGC_Load(m,(::DataLauncherTypeIGC *)data);
		return m;
	}
	DataPartTypeIGC^ ReadpartTypeIGC(char *data, int size)      
	{
		::DataPartTypeIGC* p = (::DataPartTypeIGC *)data;
		switch (p->equipmentType)
		{
			case ET_Weapon:
			{
				DataWeaponTypeIGC^ mm = gcnew DataWeaponTypeIGC();
				DataWeaponTypeIGC_Load(mm,(::DataWeaponTypeIGC*)p);
				return mm;
			} break;
			case ET_Shield:
			{
				DataShieldTypeIGC^ mm = gcnew DataShieldTypeIGC();
				DataShieldTypeIGC_Load(mm,(::DataShieldTypeIGC*)p);
				return mm;
			} break;
			case ET_Cloak:
			{
				DataCloakTypeIGC^ mm = gcnew DataCloakTypeIGC();
				DataCloakTypeIGC_Load(mm,(::DataCloakTypeIGC*)p);
				return mm;
			} break;
			case ET_Pack:
			{
				DataPackTypeIGC^ mm = gcnew DataPackTypeIGC();
				DataPackTypeIGC_Load(mm,(::DataPackTypeIGC*)p);
				return mm;
			} break;
			case ET_Afterburner:
			{
				DataAfterburnerTypeIGC^ mm = gcnew DataAfterburnerTypeIGC();
				DataAfterburnerTypeIGC_Load(mm,(::DataAfterburnerTypeIGC*)p);
				return mm;
			} break;
			default: throw gcnew InvalidOperationException("bad part type found"); 
		}
		//return nullptr;
	}
	void DataPartType_Save(DataPartTypeIGC^ m, ::DataPartTypeIGC *p)
	{
		if (m->GetType() == DataAfterburnerTypeIGC::typeid)
		{
			DataAfterburnerTypeIGC_Save((DataAfterburnerTypeIGC^)m, (::DataAfterburnerTypeIGC*)p);
			return;
		}
		if (m->GetType() == DataCloakTypeIGC::typeid)
		{
			DataCloakTypeIGC_Save((DataCloakTypeIGC^)m, (::DataCloakTypeIGC*)p);
			return;
		}
		if (m->GetType() == DataPackTypeIGC::typeid)
		{
			DataPackTypeIGC_Save((DataPackTypeIGC^)m, (::DataPackTypeIGC *)p);
			return;
		}
		if (m->GetType() == DataShieldTypeIGC::typeid)
		{
			DataShieldTypeIGC_Save((DataShieldTypeIGC^)m, (::DataShieldTypeIGC *)p);
			return;
		}
		if (m->GetType() == DataWeaponTypeIGC::typeid)
		{
			DataWeaponTypeIGC_Save((DataWeaponTypeIGC^)m, (::DataWeaponTypeIGC *)p);
			return;
		}
		// throw something?
	}
#pragma endregion
	IGCLib::Constants^ IGCCore::Constants::get()
	{
		return m_constants;
	}
	
	void IGCCore::Constants::set( IGCLib::Constants^ value )
	{
		if( value->floatConstants->Length != c_fcidMax )
			throw gcnew ArgumentOutOfRangeException( "floatConstants", "invalid number for constants" );
		m_constants = value;
	}

	// load from igc file
	void IGCCore::Load(System::String ^filename)
	{
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( filename );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		FILE*       file = NULL;
		fopen_s(&file,reinterpret_cast<const char *>( pinnedName ), "rb");
		if (file)
		{
			// init
			m_constants       = gcnew IGCLib::Constants();
			m_projectileTypes = gcnew List<DataProjectileTypeIGC^>();
			m_treasureSets    = gcnew List<DataTreasureSetIGC^>();
			m_civilizations   = gcnew List<DataCivilizationIGC^>();
			m_hullTypes       = gcnew List<DataHullTypeIGC^>();
			m_stationTypes    = gcnew List<DataStationTypeIGC^>(); 
			m_developments    = gcnew List<DataDevelopmentIGC^>(); 
			m_missileTypes    = gcnew List<DataMissileTypeIGC^>(); 
			m_mineTypes       = gcnew List<DataMineTypeIGC^>(); 
			m_chaffTypes      = gcnew List<DataChaffTypeIGC^>(); 
			m_probeTypes      = gcnew List<DataProbeTypeIGC^>(); 
			m_droneTypes      = gcnew List<DataDroneTypeIGC^>(); 
			m_launcherTypes   = gcnew List<DataLauncherTypeIGC^>();   
			m_partTypes       = gcnew List<DataPartTypeIGC^>(); 

			// open & read file
			int iCoreVer;
			int iReadCount = fread (&iCoreVer, sizeof(iCoreVer), 1, file);
			CoreVersion = iCoreVer;
			int iDatasize;
			iReadCount = fread (&iDatasize, sizeof(iDatasize), 1, file);
			char* pData = new char[iDatasize+4];      //leave a little extra space for the encryption (which takes dword chunks)
			iReadCount = fread (pData, sizeof(char), iDatasize, file);

			char *pdata = pData;
			while (iDatasize > 0)
			{
				ObjectType  type = *((ObjectType*)pdata);
				int size = *((int*)(pdata + sizeof(ObjectType)));

				if (c_maskStaticTypes & (__int64(1) << __int64(type)))
				{
					switch (type)
					{
						case OT_constants:
						{
							Constants_Load(m_constants,(::Constants*)(pdata + sizeof(int) + sizeof(ObjectType)));
							break;
						}

#define OBJECT(CLS) case OT_##CLS## : { m_##CLS##s->Add(Read##CLS##IGC((pdata + sizeof(int) + sizeof(ObjectType)), size)); } break;

						OBJECT(treasureSet)
						OBJECT(civilization)
						OBJECT(projectileType)
						OBJECT(hullType)
						OBJECT(stationType)
						OBJECT(development)
						OBJECT(missileType)
						OBJECT(mineType)
						OBJECT(chaffType)
						OBJECT(probeType)
						OBJECT(droneType)
						case OT_partType:
						{
							//Part types and magazine part types get special treatment
							if (size == sizeof(::DataLauncherTypeIGC))
								m_launcherTypes->Add(ReadlauncherTypeIGC((pdata + sizeof(int) + sizeof(ObjectType)), size));
							else
								m_partTypes->Add(ReadpartTypeIGC((pdata + sizeof(int) + sizeof(ObjectType)), size));
						}
						break;
						// IbaseIGC*   b = CreateObject(now, type, (void*)(pdata + sizeof(int) + sizeof(ObjectType)), size);
					}
					pdata += size + sizeof(int) + sizeof(ObjectType);
				}

				iDatasize -= (size + sizeof(int) + sizeof(ObjectType));
			}			
			
			delete [] pData;
			fclose(file);
		}
	}
	// save to igc file
	void IGCCore::Save(System::String ^filename)
	{
		FileStream^ stream = gcnew FileStream(filename,FileMode::Create);
		BinaryWriter^ br = gcnew BinaryWriter(stream);
		br->Write(CoreVersion);
		// total size placeholder, write 0 but keep offset for later update
		int iDatasize = 0;
		int sizeoffset = (int)br->Seek(0,SeekOrigin::Current); br->Write(iDatasize);
		// Constants
		br->Write(::OT_constants); iDatasize+= sizeof(::ObjectType);
		int size = sizeof(::Constants);
		br->Write(size); iDatasize+= sizeof(int);
		array<Byte>^ buff = gcnew array<Byte>(size);
		pin_ptr<Byte> pp = &buff[0];
		unsigned char *p = pp;
		Constants_Save(m_constants,(::Constants*)p);
		br->Write(buff); iDatasize+= size; 
/*
save order (as found in legacy cores)
	OT_projectileType
	OT_missileType
	OT_chaffType
	OT_mineType
	OT_probeType
	OT_partType
	OT_hullType
	OT_development
	OT_droneType
	OT_stationType
	OT_treasureSet
	OT_civilization
*/
		// Projectiles
		for each (DataProjectileTypeIGC^ m in m_projectileTypes)
		{
			br->Write(::OT_projectileType); iDatasize+= sizeof(::ObjectType);
			size = sizeof(::DataProjectileTypeIGC); br->Write(size); iDatasize+= sizeof(int);
			buff = gcnew array<Byte>(size); pin_ptr<Byte> pp = &buff[0]; p = pp;
			DataProjectileTypeIGC_Save(m,(::DataProjectileTypeIGC*)p);
			br->Write(buff); iDatasize+= size;
		}
  
		// ExpendableTypes - missile chaff mine probe
		for each (DataMissileTypeIGC^ m in m_missileTypes)
		{
			br->Write(::OT_missileType); iDatasize+= sizeof(::ObjectType);
			size = sizeof(::DataMissileTypeIGC); br->Write(size); iDatasize+= sizeof(int);
			buff = gcnew array<Byte>(size); pin_ptr<Byte> pp = &buff[0]; p = pp;
			DataMissileTypeIGC_Save(m,(::DataMissileTypeIGC*)p);
			br->Write(buff); iDatasize+= size;
		}
		for each (DataChaffTypeIGC^ m in m_chaffTypes)
		{
			br->Write(::OT_chaffType); iDatasize+= sizeof(::ObjectType);
			size = sizeof(::DataChaffTypeIGC); br->Write(size); iDatasize+= sizeof(int);
			buff = gcnew array<Byte>(size); pin_ptr<Byte> pp = &buff[0]; p = pp;
			DataChaffTypeIGC_Save(m,(::DataChaffTypeIGC*)p);
			br->Write(buff); iDatasize+= size;
		}
		for each (DataMineTypeIGC^ m in m_mineTypes)
		{
			br->Write(::OT_mineType); iDatasize+= sizeof(::ObjectType);
			size = sizeof(::DataMineTypeIGC); br->Write(size); iDatasize+= sizeof(int);
			buff = gcnew array<Byte>(size); pin_ptr<Byte> pp = &buff[0]; p = pp;
			DataMineTypeIGC_Save(m,(::DataMineTypeIGC*)p);
			br->Write(buff); iDatasize+= size;
		}
		for each (DataProbeTypeIGC^ m in m_probeTypes)
		{
			br->Write(::OT_probeType); iDatasize+= sizeof(::ObjectType);
			size = sizeof(::DataProbeTypeIGC); br->Write(size); iDatasize+= sizeof(int);
			buff = gcnew array<Byte>(size); pin_ptr<Byte> pp = &buff[0]; p = pp;
			DataProbeTypeIGC_Save(m,(::DataProbeTypeIGC*)p);
			br->Write(buff); iDatasize+= size;
		}
		// PartTypes - launcher & part
		for each (DataLauncherTypeIGC^ m in m_launcherTypes)
		{
			br->Write(::OT_partType); iDatasize+= sizeof(::ObjectType);
			size = sizeof(::DataLauncherTypeIGC); br->Write(size); iDatasize+= sizeof(int);
			buff = gcnew array<Byte>(size); pin_ptr<Byte> pp = &buff[0]; p = pp;
			DataLauncherTypeIGC_Save(m,(::DataLauncherTypeIGC*)p);
			br->Write(buff); iDatasize+= size;
		}
		for each (DataPartTypeIGC^ m in m_partTypes)
		{
			br->Write(::OT_partType); iDatasize+= sizeof(::ObjectType);
			size = 0;
			if (m->GetType() == DataAfterburnerTypeIGC::typeid) size = sizeof(::DataAfterburnerTypeIGC);
			if (m->GetType() == DataCloakTypeIGC::typeid) size = sizeof(::DataCloakTypeIGC);
			if (m->GetType() == DataPackTypeIGC::typeid) size = sizeof(::DataPackTypeIGC);
			if (m->GetType() == DataShieldTypeIGC::typeid) size = sizeof(::DataShieldTypeIGC);
			if (m->GetType() == DataWeaponTypeIGC::typeid) size = sizeof(::DataWeaponTypeIGC);
			if (size == 0) throw gcnew InvalidOperationException("bad part type found"); 
			br->Write(size); iDatasize+= sizeof(int);
			buff = gcnew array<Byte>(size); pin_ptr<Byte> pp = &buff[0]; p = pp;
			DataPartType_Save(m,(::DataPartTypeIGC*)p);
			br->Write(buff); iDatasize+= size;
		}
		// HullTypes
		for each (DataHullTypeIGC^ m in m_hullTypes)
		{
			br->Write(::OT_hullType); iDatasize+= sizeof(::ObjectType);
			size = sizeof(::DataHullTypeIGC) + m->HardPoints->Count*sizeof(::HardpointData);
			br->Write(size); iDatasize+= sizeof(int);
			buff = gcnew array<Byte>(size); pin_ptr<Byte> pp = &buff[0]; p = pp;
			DataHullTypeIGC_Save(m,(::DataHullTypeIGC*)p);
			br->Write(buff); iDatasize+= size;
		}
		// Developments
		for each (DataDevelopmentIGC^ m in m_developments)
		{
			br->Write(::OT_development); iDatasize+= sizeof(::ObjectType);
			size = sizeof(::DataDevelopmentIGC); br->Write(size); iDatasize+= sizeof(int);
			buff = gcnew array<Byte>(size); pin_ptr<Byte> pp = &buff[0]; p = pp;
			DataDevelopmentIGC_Save(m,(::DataDevelopmentIGC*)p);
			br->Write(buff); iDatasize+= size;
		}
		// DroneTypes
		for each (DataDroneTypeIGC^ m in m_droneTypes)
		{
			br->Write(::OT_droneType); iDatasize+= sizeof(::ObjectType);
			size = sizeof(::DataDroneTypeIGC); br->Write(size); iDatasize+= sizeof(int);
			buff = gcnew array<Byte>(size); pin_ptr<Byte> pp = &buff[0]; p = pp;
			DataDroneTypeIGC_Save(m,(::DataDroneTypeIGC*)p);
			br->Write(buff); iDatasize+= size;
		}
		// StationTypes
		for each (DataStationTypeIGC^ m in m_stationTypes)
		{
			br->Write(::OT_stationType); iDatasize+= sizeof(::ObjectType);
			size = sizeof(::DataStationTypeIGC); br->Write(size); iDatasize+= sizeof(int);
			buff = gcnew array<Byte>(size); pin_ptr<Byte> pp = &buff[0]; p = pp;
			DataStationTypeIGC_Save(m,(::DataStationTypeIGC*)p);
			br->Write(buff); iDatasize+= size;
		}
		// TreasureSets
		for each (DataTreasureSetIGC^ m in m_treasureSets)
		{
			br->Write(::OT_treasureSet); iDatasize+= sizeof(::ObjectType);
			size = sizeof(::DataTreasureSetIGC) + m->treasureDatas->Count * sizeof(::TreasureData);
			br->Write(size); iDatasize+= sizeof(int);
			buff = gcnew array<Byte>(size); pin_ptr<Byte> pp = &buff[0]; p = pp;
			DataTreasureSetIGC_Save(m,(::DataTreasureSetIGC*)p);
			br->Write(buff); iDatasize+= size;
		}
		// Civilizations
		for each (DataCivilizationIGC^ m in m_civilizations)
		{
			br->Write(::OT_civilization); iDatasize+= sizeof(::ObjectType);
			size = sizeof(::DataCivilizationIGC); br->Write(size); iDatasize+= sizeof(int);
			buff = gcnew array<Byte>(size); pin_ptr<Byte> pp = &buff[0]; p = pp;
			DataCivilizationIGC_Save(m,(::DataCivilizationIGC*)p);
			br->Write(buff); iDatasize+= size;
		}
		// end - rewind to write total size;
		br->Seek(sizeoffset,SeekOrigin::Begin);
		br->Write(iDatasize);
		br->Close();
		stream->Close();
	}

#pragma region IGC MAP objects read/write
	// reader/writer
	Vector Vector_Load(::Vector p)
	{
		Vector m;
		m.X = p.X();
		m.Y = p.Y();
		m.Z = p.Z();
		return m;
	}
	::Vector Vector_Save(Vector m)
	{
		::Vector p(m.X,m.Y,m.Z);
		return p;
	}
	Rotation Rotation_Load(::Rotation p)
	{
		Rotation m;
		m.Axis = Vector_Load(p.axis());
		m.Angle = p.angle();
		return m;
	}
	::Rotation Rotation_Save(Rotation m)
	{
		::Rotation p(Vector_Save(m.Axis),m.Angle);
		return p;
	}
	DataAsteroidIGC^ ReadasteroidIGC(char *data, int size)
	{
		DataAsteroidIGC^ m = gcnew DataAsteroidIGC();
		::DataAsteroidIGC *p = (::DataAsteroidIGC *)data;
		PtoM(signature);
		m->position = Vector_Load(p->position);
		m->up = Vector_Load(p->up);
		m->forward = Vector_Load(p->forward);
		m->rotation = Rotation_Load(p->rotation);
		PtoM(asteroidDef.ore);
		PtoM(asteroidDef.oreMax);
		PtoMc(asteroidDef.aabmCapabilities,AsteroidAbilityBitMask);
		PtoM(asteroidDef.asteroidID);
		PtoM(asteroidDef.hitpoints);
		PtoM(asteroidDef.radius);
		m->asteroidDef.modelName = String_Load(p->asteroidDef.modelName);
		m->asteroidDef.textureName = String_Load(p->asteroidDef.textureName);
		m->asteroidDef.iconName = String_Load(p->asteroidDef.iconName);
		PtoM(clusterID);
		m->name = String_Load(p->name);
		PtoM(fraction);		
		return m;
	}

	DataStationIGC^ ReadstationIGC(char *data, int size)
	{
		DataStationIGC^ m = gcnew DataStationIGC();
		::DataStationIGC *p = (::DataStationIGC *)data;

		m->position = Vector_Load(p->position);
		m->up = Vector_Load(p->up);
		m->forward = Vector_Load(p->forward);
		m->rotation = Rotation_Load(p->rotation);
		PtoM(clusterID);
		PtoM(sideID);
		PtoM(stationID);
		PtoM(stationTypeID);
		PtoM(bpHull);
		PtoM(bpShield);
		m->name = String_Load(p->name);
		return m;
	}

	DataClusterIGC^ ReadclusterIGC(char *data, int size)
	{
		DataClusterIGC^ m = gcnew DataClusterIGC();
		::DataClusterIGC *p = (::DataClusterIGC *)data;
		PtoM(starSeed);
		m->lightDirection = Vector_Load(p->lightDirection);
		m->lightColor = Color::FromArgb(p->lightColor);
		PtoM(screenX);
		PtoM(screenY);
		PtoM(clusterID);
		PtoM(nDebris);
		PtoM(nStars);
		m->name = String_Load(p->name);
		m->posterName = String_Load(p->posterName);
		m->planetName = String_Load(p->planetName);
		PtoM(planetSinLatitude);
		PtoM(planetLongitude);
		PtoM(planetRadius);
		PtoM(activeF);
		PtoM(bHomeSector);

		return m;
	}

	DataMineExport^ ReadmineIGC(char *data, int size)
	{
		DataMineExport^ m = gcnew DataMineExport();
		::DataMineExport* p = (::DataMineExport *) data;

		m->p0 = Vector_Load(p->p0);
		PtoM(time0);
		PtoM(mineID);
		PtoM(exportF);

		PtoM(clusterID);
		PtoM(minetypeID);
		PtoM(launcherID);
		PtoM(sideID);
		PtoM(fraction);
		PtoM(createNow);

		return m;
	}

	DataProbeExport^ ReadprobeIGC(char *data, int size)
	{
		DataProbeExport^ m = gcnew DataProbeExport();
		::DataProbeExport* p = (::DataProbeExport*)data;

		m->p0 = Vector_Load(p->p0);
		PtoM(time0);
		PtoM(probeID);
		PtoM(exportF);

		PtoM(probetypeID);
		PtoM(sideID);
		PtoM(clusterID);
		PtoM(shipID);
		PtoM(otTarget);
		PtoM(oidTarget);
		PtoM(createNow);

		return m;
	}

	DataTreasureIGC^ ReadtreasureIGC(char *data, int size)
	{
		DataTreasureIGC^ m = gcnew DataTreasureIGC();
		::DataTreasureIGC* p = (::DataTreasureIGC*)data;

		m->p0 = Vector_Load(p->p0);
		m->v0 = Vector_Load(p->v0);
		PtoM(lifespan);
		PtoM(time0);
		PtoM(objectID);
		PtoM(treasureID);
		PtoM(clusterID);
		PtoM(amount);
		PtoMc(treasureCode,TreasureCode);
		PtoM(createNow);

		return m;
	}

	DataWarpIGC^ ReadwarpIGC(char *data, int size)
	{
		DataWarpIGC^m = gcnew DataWarpIGC();
		::DataWarpIGC* p = (::DataWarpIGC*)data;

		PtoM(warpDef.warpID);
		PtoM(warpDef.destinationID);
		PtoM(warpDef.radius);
		m->warpDef.textureName = String_Load(p->warpDef.textureName);
		m->warpDef.iconName = String_Load(p->warpDef.iconName);
		m->name = String_Load(p->name);
		m->position = Vector_Load(p->position);
		m->forward = Vector_Load(p->forward);
		m->rotation = Rotation_Load(p->rotation);
		PtoM(signature);
		PtoM(clusterID);

		return m;
	}
// writers

	void DataClusterIGC_Save(DataClusterIGC^ m,::DataClusterIGC* p)
	{
		MtoP(starSeed);
		p->lightDirection = Vector_Save(m->lightDirection);
		p->lightColor = m->lightColor.ToArgb();
		MtoP(screenX);
		MtoP(screenY);
		MtoP(clusterID);
		MtoP(nDebris);
		MtoP(nStars);
		String_Save(m->name,p->name);
		String_Save(m->posterName,p->posterName);
		String_Save(m->planetName,p->planetName);
		MtoP(planetSinLatitude);
		MtoP(planetLongitude);
		MtoP(planetRadius);
		MtoP(activeF);
		MtoP(bHomeSector);
	}
	void DataWarpIGC_Save(DataWarpIGC ^ m,::DataWarpIGC* p)
	{
		MtoP(warpDef.warpID);
		MtoP(warpDef.destinationID);
		MtoP(warpDef.radius);
		String_Save(m->warpDef.textureName,p->warpDef.textureName);
		String_Save(m->warpDef.iconName,p->warpDef.iconName);
		String_Save(m->name,p->name);
		p->position = Vector_Save(m->position);
		p->forward = Vector_Save(m->forward);
		p->rotation = Rotation_Save(m->rotation);
		MtoP(signature);
		MtoP(clusterID);
	}
	void DataAsteroidIGC_Save(DataAsteroidIGC^ m,::DataAsteroidIGC* p)
	{
		MtoP(signature);
		p->position = Vector_Save(m->position);
		p->up = Vector_Save(m->up);
		p->forward = Vector_Save(m->forward);
		p->rotation = Rotation_Save(m->rotation);
		MtoP(asteroidDef.ore);
		MtoP(asteroidDef.oreMax);
		MtoPc(asteroidDef.aabmCapabilities,::AsteroidAbilityBitMask);
		MtoP(asteroidDef.asteroidID);
		MtoP(asteroidDef.hitpoints);
		MtoP(asteroidDef.radius);
		String_Save(m->asteroidDef.modelName,p->asteroidDef.modelName);
		String_Save(m->asteroidDef.textureName,p->asteroidDef.textureName);
		String_Save(m->asteroidDef.iconName,p->asteroidDef.iconName);
		MtoP(clusterID);
		String_Save(m->name,p->name);
		MtoP(fraction);
	}
	void DataStationIGC_Save(DataStationIGC^ m,::DataStationIGC* p)
	{
		p->position = Vector_Save(m->position);
		p->up = Vector_Save(m->up);
		p->forward = Vector_Save(m->forward);
		p->rotation = Rotation_Save(m->rotation);
		MtoP(clusterID);
		MtoP(sideID);
		MtoP(stationID);
		MtoP(stationTypeID);
		MtoP(bpHull);
		MtoP(bpShield);
		String_Save(m->name,p->name);
	}
	void DataProbeExport_Save(DataProbeExport^ m,::DataProbeExport* p)
	{
		p->p0 = Vector_Save(m->p0);
		MtoP(time0);
		MtoP(probeID);
		MtoP(exportF);

		MtoP(probetypeID);
		MtoP(sideID);
		MtoP(clusterID);
		MtoP(shipID);
		MtoP(otTarget);
		MtoP(oidTarget);
		MtoP(createNow);
	}
	void DataMineExport_Save(DataMineExport^ m,::DataMineExport* p)
	{
		p->p0 = Vector_Save(m->p0);
		MtoP(time0);
		MtoP(mineID);
		MtoP(exportF);

		MtoP(clusterID);
		MtoP(minetypeID);
		MtoP(launcherID);
		MtoP(sideID);
		MtoP(fraction);
		MtoP(createNow);
	}
	void DataTreasureIGC_Save(DataTreasureIGC^ m,::DataTreasureIGC* p)
	{
		p->p0 = Vector_Save(m->p0);
		p->v0 = Vector_Save(m->v0);
		MtoP(lifespan);
		MtoP(time0);
		MtoP(objectID);
		MtoP(treasureID);
		MtoP(clusterID);
		MtoP(amount);
		MtoPc(treasureCode,::TreasureCode);
		MtoP(createNow);
	}

#pragma endregion

	void IGCMap::Load(String^ filename)
	{
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( filename );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		FILE*       file = NULL;
		fopen_s(&file,reinterpret_cast<const char *>( pinnedName ), "rb");
		if (file)
		{
			// init
			m_asteroids = gcnew List<DataAsteroidIGC^>();
			m_stations = gcnew List<DataStationIGC^>();
			m_clusters = gcnew List<DataClusterIGC^>();
			m_mines = gcnew List<DataMineExport^>();
			m_probes = gcnew List<DataProbeExport^>();
			m_treasures = gcnew List<DataTreasureIGC^>();
			m_warps = gcnew List<DataWarpIGC^>();
			// open & read file
			//int iCoreVer;
			//int iReadCount = fread (&iCoreVer, sizeof(iCoreVer), 1, file);
			//CoreVersion = iCoreVer;
			int iDatasize;
			int iReadCount = fread (&iDatasize, sizeof(iDatasize), 1, file);
			char* pData = new char[iDatasize+4];      //leave a little extra space for the encryption (which takes dword chunks)
			iReadCount = fread (pData, sizeof(char), iDatasize, file);

			char *pdata = pData;
			while (iDatasize > 0)
			{
				ObjectType  type = *((ObjectType*)pdata);
				int size = *((int*)(pdata + sizeof(ObjectType)));

				if (c_maskMapTypes & (__int64(1) << __int64(type)))
				{
					switch (type)
					{
#define OBJECT(CLS) case OT_##CLS## : { m_##CLS##s->Add(Read##CLS##IGC((pdata + sizeof(int) + sizeof(ObjectType)), size)); } break;
						OBJECT(asteroid)
						OBJECT(station)
						OBJECT(cluster)
						OBJECT(mine)
						OBJECT(probe)
						OBJECT(treasure)
						OBJECT(warp)
					}
					pdata += size + sizeof(int) + sizeof(ObjectType);
				}

				iDatasize -= (size + sizeof(int) + sizeof(ObjectType));
			}			
			
			delete [] pData;
			fclose(file);
		}
	}
	void IGCMap::Save(String^ filename)
	{
		FileStream^ stream = gcnew FileStream(filename,FileMode::Create);
		BinaryWriter^ br = gcnew BinaryWriter(stream);
		// total size placeholder, write 0 but keep offset for later update
		int iDatasize = 0;
		int sizeoffset = (int)br->Seek(0,SeekOrigin::Current); br->Write(iDatasize);

		//OT_cluster 
		for each (IGCLib::DataClusterIGC^ m in m_clusters)
		{
			br->Write(::OT_cluster); iDatasize+= sizeof(::ObjectType);
			int size = sizeof(::DataClusterIGC); br->Write(size); iDatasize+= sizeof(int);
			array<Byte>^ buff = gcnew array<Byte>(size); pin_ptr<Byte> pp = &buff[0];
			unsigned char *p = pp;
			DataClusterIGC_Save(m,(::DataClusterIGC*)p);
			br->Write(buff); iDatasize+= size;
		}
		//OT_warp
		for each (IGCLib::DataWarpIGC^ m in m_warps)
		{
			br->Write(::OT_warp); iDatasize+= sizeof(::ObjectType);
			int size = sizeof(::DataWarpIGC); br->Write(size); iDatasize+= sizeof(int);
			array<Byte>^ buff = gcnew array<Byte>(size); pin_ptr<Byte> pp = &buff[0];
			unsigned char *p = pp;
			DataWarpIGC_Save(m,(::DataWarpIGC*)p);
			br->Write(buff); iDatasize+= size;
		}
		//OT_asteroid 
		for each (IGCLib::DataAsteroidIGC^ m in m_asteroids)
		{
			br->Write(::OT_asteroid); iDatasize+= sizeof(::ObjectType);
			int size = sizeof(::DataAsteroidIGC); br->Write(size); iDatasize+= sizeof(int);
			array<Byte>^ buff = gcnew array<Byte>(size); pin_ptr<Byte> pp = &buff[0];
			unsigned char *p = pp;
			DataAsteroidIGC_Save(m,(::DataAsteroidIGC*)p);
			br->Write(buff); iDatasize+= size;
		}
		//OT_station
		for each (IGCLib::DataStationIGC^ m in m_stations)
		{
			br->Write(::OT_station); iDatasize+= sizeof(::ObjectType);
			int size = sizeof(::DataStationIGC); br->Write(size); iDatasize+= sizeof(int);
			array<Byte>^ buff = gcnew array<Byte>(size); pin_ptr<Byte> pp = &buff[0];
			unsigned char *p = pp;
			DataStationIGC_Save(m,(::DataStationIGC*)p);
			br->Write(buff); iDatasize+= size;
		}
		//OT_probe
		for each (IGCLib::DataProbeExport^ m in m_probes)
		{
			br->Write(::OT_probe); iDatasize+= sizeof(::ObjectType);
			int size = sizeof(::DataProbeExport); br->Write(size); iDatasize+= sizeof(int);
			array<Byte>^ buff = gcnew array<Byte>(size); pin_ptr<Byte> pp = &buff[0];
			unsigned char *p = pp;
			DataProbeExport_Save(m,(::DataProbeExport*)p);
			br->Write(buff); iDatasize+= size;
		}
		//OT_mine
		for each (IGCLib::DataMineExport^ m in m_mines)
		{
			br->Write(::OT_mine); iDatasize+= sizeof(::ObjectType);
			int size = sizeof(::DataMineExport); br->Write(size); iDatasize+= sizeof(int);
			array<Byte>^ buff = gcnew array<Byte>(size); pin_ptr<Byte> pp = &buff[0];
			unsigned char *p = pp;
			DataMineExport_Save(m,(::DataMineExport*)p);
			br->Write(buff); iDatasize+= size;
		}
		//OT_treasure
		for each (IGCLib::DataTreasureIGC^ m in m_treasures)
		{
			br->Write(::OT_treasure); iDatasize+= sizeof(::ObjectType);
			int size = sizeof(::DataTreasureIGC); br->Write(size); iDatasize+= sizeof(int);
			array<Byte>^ buff = gcnew array<Byte>(size); pin_ptr<Byte> pp = &buff[0];
			unsigned char *p = pp;
			DataTreasureIGC_Save(m,(::DataTreasureIGC*)p);
			br->Write(buff); iDatasize+= size;
		}

		// end - rewind to write total size;
		br->Seek(sizeoffset,SeekOrigin::Begin);
		br->Write(iDatasize);
		br->Close();
		stream->Close();
	}
}