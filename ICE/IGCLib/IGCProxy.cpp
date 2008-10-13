// This is the main DLL file.

#include "stdafx.h"

#include "IGCProxy.h"

#define IGC_FILE_VERSION_TYPE   int

namespace IGCLib {

#pragma region converters

#define PtoM(field) m->field = p->field
#define MtoP(field) p->field = m->field

// String
	void String_Save(String^ m, char* p, int size)
	{
		array<Byte>^ bytes = System::Text::ASCIIEncoding::ASCII->GetBytes( m );
		pin_ptr<unsigned char> pinnedbyte = &bytes[0];
		strcpy_s(p, size, reinterpret_cast<const char*>( pinnedbyte ));
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
		memcpy(&p->floatConstants[0],pinnedBuffer,sizeof(float)*c_fcidMax);

		if (m->damageConstants->Length != c_dmgidMax*c_defidMax) throw gcnew ArgumentException("invalid size of damageConstants");
		for (int i=0;i<c_dmgidMax;i++)
		{
			if (m->damageConstants[i]->Length != c_defidMax) throw gcnew ArgumentException("invalid subsize of damageConstants");
			pinnedBuffer = &m->damageConstants[i][0];
			memcpy(&p->damageConstants[i][0],pinnedBuffer,sizeof(float)*c_defidMax);
		}
	}

// GlobalAttributeSet
	void GlobalAttributeSet_Load(GlobalAttributeSet^ m, ::GlobalAttributeSet gas)
	{
		for (int i=0;i<c_gaMax;i++)
			m->Attributes[i]=gas.GetAttribute(i);
	}

	void GlobalAttributeSet_Save(GlobalAttributeSet^ m, ::GlobalAttributeSet *gas)
	{
		for (int i=0;i<c_gaMax;i++)
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
		m->modelName = gcnew String(p->modelName);
		m->textureName = gcnew String(p->textureName);
	}
	void DataObjectIGC_Save(DataObjectIGC^ m, ::DataObjectIGC *p)
	{
		p->color.a = (float)m->color.A / 255.0f;
		p->color.r = (float)m->color.R / 255.0f;
		p->color.g = (float)m->color.G / 255.0f;
		p->color.b = (float)m->color.B / 255.0f;
		p->radius = m->radius;
		p->rotation = m->rotation;

		String_Save(m->modelName,p->modelName, sizeof(p->modelName));
		String_Save(m->textureName,p->textureName, sizeof(p->textureName));
	}
// DataCivilizationIGC
	void DataCivilizationIGC_Load(DataCivilizationIGC^ m, ::DataCivilizationIGC* p)
	{
		m->incomeMoney = p->incomeMoney;
		m->bonusMoney = p->bonusMoney;
		m->name = gcnew String(p->name);
		m->iconName = gcnew String(p->iconName);
		m->hudName  = gcnew String(p->hudName);
		TechTreeBitMask_Load(m->ttbmBaseTechs, p->ttbmBaseTechs);
		TechTreeBitMask_Load(m->ttbmNoDevTechs, p->ttbmNoDevTechs);
		GlobalAttributeSet_Load(m->gasBaseAttributes, p->gasBaseAttributes);
		m->lifepod = p->lifepod;
		m->civilizationID = p->civilizationID;
		m->initialStationTypeID = p->initialStationTypeID;
	}
	void DataCivilizationIGC(DataCivilizationIGC^ m, ::DataCivilizationIGC* p)
	{
		p->incomeMoney = m->incomeMoney;
		p->bonusMoney = m->bonusMoney;
		
		String_Save(m->name, p->name, sizeof(p->name));
		String_Save(m->iconName, p->iconName, sizeof(p->iconName));
		String_Save(m->hudName, p->hudName, sizeof(p->hudName));

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

		m->modelName = gcnew String(p->modelName);
		m->iconName = gcnew String(p->iconName);
		m->name = gcnew String(p->name);
		m->description = gcnew String(p->description);

		m->groupID = p->groupID;
		TechTreeBitMask_Load(m->ttbmRequired, p->ttbmRequired);
		TechTreeBitMask_Load(m->ttbmEffects, p->ttbmEffects);
	}
	void DataBuyableIGC_Save(DataBuyableIGC^ m, ::DataBuyableIGC *p)
	{
		p->price = m->price;
		p->timeToBuild = m->timeToBuild;
		String_Save(m->modelName,p->modelName,sizeof(p->modelName));
		String_Save(m->iconName,p->iconName,sizeof(p->iconName));
		String_Save(m->name,p->name,sizeof(p->name));
		String_Save(m->description,p->description,sizeof(p->description));
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
	DataProjectileTypeIGC^ DataProjectileTypeIGC_Read(char *data, int size)
	{
		::DataProjectileTypeIGC* p = (::DataProjectileTypeIGC*)data;
		if (size != sizeof(::DataProjectileTypeIGC))
			throw gcnew InvalidOperationException("bad core data size for Projectile");
		DataProjectileTypeIGC^ proj = gcnew DataProjectileTypeIGC();
		DataProjectileTypeIGC_Load(proj,p);
		return proj;
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
		m->inventoryLineMDL = gcnew String(p->inventoryLineMDL);
	}
	void DataPartTypeIGC_Save(DataPartTypeIGC^ m, ::DataPartTypeIGC *p)
	{
		DataBuyableIGC_Save(m,p);
		p->mass = m->mass;
		p->signature = m->signature;
		p->partID = m->partID;
		p->successorPartID = m->successorPartID;
		p->equipmentType = m->equipmentType;
		p->partMask = m->partMask;
		String_Save(m->inventoryLineMDL,p->inventoryLineMDL,sizeof(p->inventoryLineMDL));
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
		p->packType = m->packType;
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
		m->eabmCapabilities = p->eabmCapabilities;
		m->iconName = gcnew String(p->iconName);
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
		p->eabmCapabilities = m->eabmCapabilities;
		String_Save(m->iconName,p->iconName,sizeof(p->iconName));
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
		m->radius = p->radius;
		m->power = p->power;
		m->endurance = p->endurance;
		m->damageType = p->damageType;
	}
	void DataMineTypeIGC_Save(DataMineTypeIGC^ m, ::DataMineTypeIGC *p)
	{
		DataExpendableTypeIGC_Save(m,p);
		p->radius = m->radius;
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
		MtoP(treasureCode);
		MtoP(chance);
	}
// DataTreasureSetIGC
	void DataTreasureSetIGC_Load(DataTreasureSetIGC^ m, ::DataTreasureSetIGC* p)
	{
		m->name = gcnew String(p->name);
		PtoM(treasureSetID);
		PtoM(bZoneOnly);
		m->treasureDatas->Clear();
		for (int i=0;i<p->nTreasureData;i++)
		{
			TreasureData^ d = gcnew TreasureData();
			TreasureData_Load(d,p->treasureData0()+i*sizeof(::TreasureData));
			m->treasureDatas->Add(d);
		}
	}
	void DataTreasureSetIGC_Save(DataTreasureSetIGC^ m, ::DataTreasureSetIGC* p)
	{
		String_Save(m->name,p->name,sizeof(p->name));
		MtoP(treasureSetID);
		MtoP(bZoneOnly);
		p->nTreasureData = m->treasureDatas->Count;
		for (int i=0;i<p->nTreasureData;i++)
		{
			TreasureData_Save(m->treasureDatas[i],p->treasureData0()+i*sizeof(::TreasureData));
		}
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

	ProjectileList^ IGCCore::Projectiles::get()
	{
		return m_projectiles;
	}
	void IGCCore::Projectiles::set(ProjectileList^ value)
	{
		m_projectiles = value;
	}

	void IGCCore::Load(System::String ^filename)
	{
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( filename );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		FILE*       file = NULL;
		fopen_s(&file,reinterpret_cast<const char *>( pinnedName ), "rb");
		if (file)
		{
			// init
			m_constants = gcnew IGCLib::Constants();
			m_projectiles = gcnew ProjectileList();

			// open & read file
			IGC_FILE_VERSION_TYPE   iStaticCoreVersion;
			int iReadCount = fread (&iStaticCoreVersion, sizeof(iStaticCoreVersion), 1, file);
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
					if (type == OT_constants)
					{
						//memcpy(&m_constants, (void*)(pdata + sizeof(int) + sizeof(ObjectType)), sizeof(m_constants));
						Constants_Load(m_constants,(::Constants*)(pdata + sizeof(int) + sizeof(ObjectType)));
					}
					else
					{
						switch (type)
						{
							case OT_projectileType:
								{
									m_projectiles->Add(DataProjectileTypeIGC_Read((pdata + sizeof(int) + sizeof(ObjectType)), size));
									break;
								}

						}
						// IbaseIGC*   b = CreateObject(now, type, (void*)(pdata + sizeof(int) + sizeof(ObjectType)), size);
					}
					pdata += size + sizeof(int) + sizeof(ObjectType);
				}

				iDatasize -= (size + sizeof(int) + sizeof(ObjectType));
			}			
			
			delete [] pData;
		}
	}
}