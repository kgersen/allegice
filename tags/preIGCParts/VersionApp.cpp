// VersionApp.cpp: Implementierung der Klasse CVersionApp.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "winver.h"
#include "VersionApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CVersionApp::CVersionApp()
{

}

CVersionApp::~CVersionApp()
{

}


// Funktionsname	: CVersionApp::ReadResourceInformation
// Beschreibung	    : Liest alle Versionsinformationen
// Rückgabewert		: BOOL 
BOOL CVersionApp::ReadResourceInformation()
{
	DWORD	dwLength, dwSize, dwNullHandle;
	TCHAR	szFileName [MAX_PATH];
	LPVOID	lpVersionPtr;
	UINT	uiVerLength;
	
	
	dwSize = sizeof (szFileName) / sizeof (szFileName [0]);
	dwLength = ::GetModuleFileName (AfxGetInstanceHandle(), szFileName, dwSize);
	if (dwLength <= 0) 
		return FALSE;

	m_VersionInfo.sFilePath=szFileName;
	dwLength = ::GetFileVersionInfoSize (szFileName, &dwNullHandle);
	if (dwLength <= 0) 
		return FALSE;

	BYTE* pVersionInfo = new BYTE [dwLength];
	if (!::GetFileVersionInfo (szFileName, NULL, dwLength, pVersionInfo)) 
		return FALSE;	
	if (!::VerQueryValue (pVersionInfo, _T ("\\"), &lpVersionPtr, &uiVerLength)) 
		return FALSE;

	m_VersionInfo.vsFixedFileInfo = *(VS_FIXEDFILEINFO*)lpVersionPtr;
	
	if (!GetDynamicInfo(pVersionInfo)) 
		return FALSE;	
	if (!GetFixedFileInfo ()) 
		return FALSE;
	
	delete pVersionInfo;	

	return TRUE;
}


// Funktionsname	: CVersionApp::GetFixedFileInfo
// Beschreibung	    : 
// Rückgabewert		: BOOL 
BOOL CVersionApp::GetFixedFileInfo()
{
	m_VersionInfo.stMajorVersion.Format("%d",HIWORD (m_VersionInfo.vsFixedFileInfo.dwFileVersionMS));
	m_VersionInfo.stMinorVersion.Format("%d",LOWORD (m_VersionInfo.vsFixedFileInfo.dwFileVersionMS));
	m_VersionInfo.stDllVersion.Format ("%d.%d.%d.%d", 
		HIWORD (m_VersionInfo.vsFixedFileInfo.dwFileVersionMS), LOWORD (m_VersionInfo.vsFixedFileInfo.dwFileVersionMS),
		HIWORD (m_VersionInfo.vsFixedFileInfo.dwFileVersionLS), LOWORD (m_VersionInfo.vsFixedFileInfo.dwFileVersionLS));

	if (m_VersionInfo.vsFixedFileInfo.dwFileType == VFT_DRV)
	{
		switch (m_VersionInfo.vsFixedFileInfo.dwFileSubtype) 
		{
			case VFT2_DRV_DISPLAY:
				m_VersionInfo.stFileType = _T ("Display driver");
				break;
			case VFT2_DRV_INSTALLABLE:
				m_VersionInfo.stFileType = _T ("Installable driver");
				break;
			case VFT2_DRV_KEYBOARD:
				m_VersionInfo.stFileType = _T ("Keyboard driver");
				break;
			case VFT2_DRV_LANGUAGE:
				m_VersionInfo.stFileType = _T ("Language driver");
				break;
			case VFT2_DRV_MOUSE:
				m_VersionInfo.stFileType = _T ("Mouse driver");
				break;
			case VFT2_DRV_NETWORK:
				m_VersionInfo.stFileType = _T ("Network driver");
				break;
			case VFT2_DRV_PRINTER:
				m_VersionInfo.stFileType = _T ("Printer driver");
				break;
			case VFT2_DRV_SOUND:
				m_VersionInfo.stFileType = _T ("Sound driver");
				break;
			case VFT2_DRV_SYSTEM:
				m_VersionInfo.stFileType = _T ("System driver");
				break;
			case VFT2_UNKNOWN:
				m_VersionInfo.stFileType = _T ("Unknown driver");
				break;
		}
	}
	else if (m_VersionInfo.vsFixedFileInfo.dwFileType == VFT_FONT) 
	{
		switch (m_VersionInfo.vsFixedFileInfo.dwFileSubtype) 
		{
			case VFT2_FONT_RASTER:
				m_VersionInfo.stFileType = _T ("Raster font");
				break;
			case VFT2_FONT_TRUETYPE:
				m_VersionInfo.stFileType = _T ("Truetype font");
				break;
			case VFT2_FONT_VECTOR:
				m_VersionInfo.stFileType = _T ("Vector font");
				break;
			case VFT2_UNKNOWN:
				m_VersionInfo.stFileType = _T ("Unknown font");
				break;
		}
	}
	else if (m_VersionInfo.vsFixedFileInfo.dwFileType == VFT_APP) 
	{
		m_VersionInfo.stFileType = _T ("Application");
	}
	else if (m_VersionInfo.vsFixedFileInfo.dwFileType == VFT_DLL) 
	{
		m_VersionInfo.stFileType = _T ("Dynamic link library");
	}
	else if (m_VersionInfo.vsFixedFileInfo.dwFileType == VFT_STATIC_LIB) 
	{
		m_VersionInfo.stFileType = _T ("Static link library");
	}
	else if (m_VersionInfo.vsFixedFileInfo.dwFileType == VFT_VXD) 
	{
		m_VersionInfo.stFileType = _T ("Virtual device");
	}
	else if (m_VersionInfo.vsFixedFileInfo.dwFileType == VFT_UNKNOWN) 
	{
		m_VersionInfo.stFileType = _T ("Unknown type");
	}

	switch (m_VersionInfo.vsFixedFileInfo.dwFileOS) 
	{
		case VOS_DOS:
			m_VersionInfo.stFileOS = _T ("MS-DOS");
			break;
		case VOS_DOS_WINDOWS16:
			m_VersionInfo.stFileOS = _T ("16-bit windows running on MS-DOS");
			break;
		case VOS_DOS_WINDOWS32:
			m_VersionInfo.stFileOS = _T ("Win32 API running on MS-DOS");
			break;
		case VOS_OS216:
			m_VersionInfo.stFileOS = _T ("16-bit OS/2");
			break;
		case VOS_OS216_PM16:
			m_VersionInfo.stFileOS = _T ("16-bit Presentation manager running on 16-bit OS/2");
			break;
		case VOS_OS232:
			m_VersionInfo.stFileOS = _T ("32-bit OS/2");
			break;
		case VOS_NT:
			m_VersionInfo.stFileOS = _T ("Windows NT");
			break;
		case VOS_NT_WINDOWS32:
			m_VersionInfo.stFileOS = _T ("Win32 API on Windows NT");
			break;
		case VOS_UNKNOWN:
			m_VersionInfo.stFileOS = _T ("Unknown OS");
			break;
	}

	return (true);
}


// Funktionsname	: CVersionApp::GetDynamicInfo
// Beschreibung	    : 
// Rückgabewert		: BOOL 
// Argument         : BYTE *pVersionInfo
BOOL CVersionApp::GetDynamicInfo(BYTE *pVersionInfo)
{
	UINT	uiVerLength;
	LPVOID	lpPtr;
	CString	sQuery;
		

	if (::VerQueryValue (pVersionInfo, "\\VarFileInfo\\Translation", &lpPtr, &uiVerLength))
		m_VersionInfo.Translation = *(VERSION_INFORMATION::TRANSLATE*)lpPtr;
	
	sQuery.Format (	_T ("\\StringFileInfo\\%04x%04x\\CompanyName"),m_VersionInfo.Translation.languageId, m_VersionInfo.Translation.characterSet);
	::VerQueryValue (pVersionInfo, (LPTSTR)(LPCTSTR)sQuery, (LPVOID*)&lpPtr,&uiVerLength);
	m_VersionInfo.stCompany=CString((LPCTSTR)lpPtr);
	
	sQuery.Format (_T ("\\StringFileInfo\\%04x%04x\\LegalCopyRight"),m_VersionInfo.Translation.languageId, m_VersionInfo.Translation.characterSet);
	::VerQueryValue (pVersionInfo, (LPTSTR)(LPCTSTR)sQuery, (LPVOID*)&lpPtr,&uiVerLength);
	m_VersionInfo.stCopyRight=CString((LPCTSTR)lpPtr);

	sQuery.Format (_T ("\\StringFileInfo\\%04x%04x\\ProductName"),m_VersionInfo.Translation.languageId, m_VersionInfo.Translation.characterSet);
	::VerQueryValue (pVersionInfo, (LPTSTR)(LPCTSTR)sQuery, (LPVOID*)&lpPtr,&uiVerLength);
	m_VersionInfo.stProductName=CString((LPCTSTR)lpPtr);

	sQuery.Format (_T ("\\StringFileInfo\\%04x%04x\\ProductVersion"),m_VersionInfo.Translation.languageId, m_VersionInfo.Translation.characterSet);
	::VerQueryValue (pVersionInfo, (LPTSTR)(LPCTSTR)sQuery, (LPVOID*)&lpPtr,&uiVerLength);
	m_VersionInfo.stProductVersion=CString((LPCTSTR)lpPtr);

	sQuery.Format (_T ("\\StringFileInfo\\%04x%04x\\OriginalFileName"),m_VersionInfo.Translation.languageId, m_VersionInfo.Translation.characterSet);
	::VerQueryValue (pVersionInfo, (LPTSTR)(LPCTSTR)sQuery, (LPVOID*)&lpPtr,&uiVerLength);
	m_VersionInfo.stOriginalName=CString((LPCTSTR)lpPtr);

	sQuery.Format (_T ("\\StringFileInfo\\%04x%04x\\FileDescription"),m_VersionInfo.Translation.languageId, m_VersionInfo.Translation.characterSet);
	::VerQueryValue (pVersionInfo, (LPTSTR)(LPCTSTR)sQuery, (LPVOID*)&lpPtr,&uiVerLength);
	m_VersionInfo.stDescription=CString((LPCTSTR)lpPtr);
	
	sQuery.Format (_T ("\\StringFileInfo\\%04x%04x\\FileVersion"),m_VersionInfo.Translation.languageId, m_VersionInfo.Translation.characterSet);
	::VerQueryValue (pVersionInfo, (LPTSTR)(LPCTSTR)sQuery, (LPVOID*)&lpPtr,&uiVerLength);
	m_VersionInfo.stFileVersion=CString((LPCTSTR)lpPtr);

	sQuery.Format (_T ("\\StringFileInfo\\%04x%04x\\InternalName"),m_VersionInfo.Translation.languageId, m_VersionInfo.Translation.characterSet);
	::VerQueryValue (pVersionInfo, (LPTSTR)(LPCTSTR)sQuery, (LPVOID*)&lpPtr,&uiVerLength);
	m_VersionInfo.stInternalName=CString((LPCTSTR)lpPtr);

	return TRUE;
}


// Funktionsname	: CVersionApp::ReadFileTime
// Beschreibung	    : Liest Datum-Informationen der EXE/DLL
// Rückgabewert		: BOOL 
BOOL CVersionApp::ReadFileTime()
{
	CFile file;
	if(file.Open(m_VersionInfo.sFilePath,CFile::modeRead,NULL))
	{
		BOOL bRet=GetFileTime((HANDLE)file.m_hFile,&m_CreationTime,&m_LastAccessTime,&m_LastWriteTime);
		file.Close();
		return bRet;
	}
	return FALSE;
}


// Funktionsname	: CVersionApp::InitInstance
// Beschreibung	    : Virtuelle CWinApp-Funktion MUSS von abgeleiteter Klasse aufgerufen werden.
// Rückgabewert		: BOOL 
BOOL CVersionApp::InitInstance()
{
	ReadResourceInformation();
	ReadFileTime();

	return CWinApp::InitInstance();
}



// Funktionsname	: CVersionApp::GetAppVersion
// Beschreibung	    : Ermittelt die EXE-Version
// Rückgabewert		: CString 
CString CVersionApp::GetAppVersion()
{ 
	return m_VersionInfo.stFileVersion;
}

// Funktionsname	: CVersionApp::GetAppBuildDate
// Beschreibung	    : Ermittelt das Erstellungsdatum
// Rückgabewert		: CString 
CString CVersionApp::GetAppBuildDate()
{
	return COleDateTime(m_CreationTime).Format();
}

// Funktionsname	: CVersionApp::GetAppLastAccessDate
// Beschreibung	    : Ermittelt das Datum des letzten Zugriffes
// Rückgabewert		: CString 
CString CVersionApp::GetAppLastAccessDate()
{
	return COleDateTime(m_LastAccessTime).Format();
}


// Funktionsname	: CVersionApp::GetAppWriteDate
// Beschreibung	    : Ermittelt das letzte Schreibdatum
// Rückgabewert		: CString 
CString CVersionApp::GetAppWriteDate()
{
	return COleDateTime(m_LastWriteTime).Format();
}


// Funktionsname	: CVersionApp::GetAppFilepath
// Beschreibung	    : Ermittelt den Aktuellen EXE-Pfad
// Rückgabewert		: CString 
CString CVersionApp::GetAppFilepath()
{
	return m_VersionInfo.sFilePath;
}


// Funktionsname	: CVersionApp::GetAppCopyright
// Beschreibung	    : Ermittelt den entsprechenden Versions-Eintrag
// Rückgabewert		: CString 
CString CVersionApp::GetAppCopyright()
{
	return m_VersionInfo.stCopyRight;
}


// Funktionsname	: CVersionApp::GetAppOriginalname
// Beschreibung	    : Ermittelt den entsprechenden Versions-Eintrag
// Rückgabewert		: CString 
CString CVersionApp::GetAppOriginalname()
{
	return m_VersionInfo.stOriginalName;
}


// Funktionsname	: CVersionApp::GetAppCompany
// Beschreibung	    : Ermittelt den entsprechenden Versions-Eintrag
// Rückgabewert		: CString 
CString CVersionApp::GetAppCompany()
{
	return m_VersionInfo.stCompany;
}


// Funktionsname	: CVersionApp::GetAppDescription
// Beschreibung	    : Ermittelt den entsprechenden Versions-Eintrag
// Rückgabewert		: CString 
CString CVersionApp::GetAppDescription()
{
	return m_VersionInfo.stDescription;
}


// Funktionsname	: CVersionApp::GetAppInternalName
// Beschreibung	    : Ermittelt den entsprechenden Versions-Eintrag
// Rückgabewert		: CString 
CString CVersionApp::GetAppInternalName()
{
	return m_VersionInfo.stInternalName;
}


// Funktionsname	: CVersionApp::GetAppProductName
// Beschreibung	    : Ermittelt den entsprechenden Versions-Eintrag
// Rückgabewert		: CString 
CString CVersionApp::GetAppProductName()
{
	return m_VersionInfo.stProductName;
}


// Funktionsname	: CVersionApp::GetAppProductVersion
// Beschreibung	    : Ermittelt den entsprechenden Versions-Eintrag
// Rückgabewert		: CString 
CString CVersionApp::GetAppProductVersion()
{
	return m_VersionInfo.stProductVersion;
}
