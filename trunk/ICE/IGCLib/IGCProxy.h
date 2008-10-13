// IGCProxy.h

#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

#include "igclib.h"

namespace IGCLib {

	typedef List<IGCLib::DataProjectileTypeIGC^> ProjectileList;

	public ref class IGCCore
	{
	private:
		Constants^ m_constants;
		ProjectileList^ m_projectiles;
	public:
		property Constants^ Constants
		{
			IGCLib::Constants^ get();
			void set( IGCLib::Constants^ value );
		}
		property ProjectileList^ Projectiles
		{
			ProjectileList^ get();
			void set ( ProjectileList^ value);
		}
		void Load(String^ filename);
	};
}


