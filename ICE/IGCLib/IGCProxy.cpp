// This is the main DLL file.

#include "stdafx.h"

#include "IGCProxy.h"

#define IGC_FILE_VERSION_TYPE   int

namespace IGCLib {
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
						m_constants->FromNative((::Constants*)(pdata + sizeof(int) + sizeof(ObjectType)));
					}
					else
					{
						switch (type)
						{
							case OT_projectileType:
								{
									m_projectiles->Add(DataProjectileTypeIGC::FromNative((pdata + sizeof(int) + sizeof(ObjectType)), size));
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
