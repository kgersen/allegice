// IGCProxy.h

#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Collections::Generic;

#include "igclib.h"

namespace IGCLib {

	public ref class IGCCore
	{
	private:
		Constants^ m_constants;
	public:
		property Constants^ Constants
		{
			IGCLib::Constants^ get();
			void set( IGCLib::Constants^ value );
		}
		
		int   CoreVersion;

		List<DataProjectileTypeIGC^>^ m_projectileTypes;
		List<DataTreasureSetIGC^>^	  m_treasureSets;
		List<DataCivilizationIGC^>^	  m_civilizations;
		List<DataHullTypeIGC^>^	      m_hullTypes;
		List<DataStationTypeIGC^>^    m_stationTypes;
		List<DataDevelopmentIGC^>^    m_developments;
		List<DataMissileTypeIGC^>^    m_missileTypes;
		List<DataMineTypeIGC^>^       m_mineTypes;
		List<DataChaffTypeIGC^>^      m_chaffTypes;
		List<DataProbeTypeIGC^>^      m_probeTypes;
		List<DataDroneTypeIGC^>^      m_droneTypes;
		List<DataLauncherTypeIGC^>^   m_launcherTypes;
		List<DataPartTypeIGC^>^       m_partTypes;
		void Load(String^ filename);
		void Save(System::String ^filename);
	};
}


