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
		void Save(String ^filename);
	};

	public ref class IGCMap
	{
	public:
		//OT_asteroid 
		//OT_station
		//OT_cluster 
		//OT_mine
		//OT_probe
		//OT_treasure
		//OT_warp
		List<DataAsteroidIGC^>^ m_asteroids;
		List<DataStationIGC^>^ m_stations;
		List<DataClusterIGC^>^ m_clusters;
		List<DataMineExport^>^ m_mines;
		List<DataProbeExport^>^ m_probes;
		List<DataTreasureIGC^>^ m_treasures;
		List<DataWarpIGC^>^ m_warps;

		void Load(String^ filename);
		void Save(String ^filename);
	};
}


