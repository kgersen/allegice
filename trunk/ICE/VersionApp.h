// VersionApp.h: Schnittstelle für die Klasse CVersionApp.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VERSIONAPP_H__910C010B_5EC2_11D3_9EB9_0000E87CD125__INCLUDED_)
#define AFX_VERSIONAPP_H__910C010B_5EC2_11D3_9EB9_0000E87CD125__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#pragma comment(lib,"version.lib") 

typedef struct tagVersionInformation
{
	CString sFilePath;
	CString	stCompany;
	CString	stCopyRight;
	CString	stDescription;
	CString	stFileVersion;
	CString stMajorVersion;
	CString stMinorVersion;
	CString	stInternalName;
	CString	stOriginalName;
	CString	stProductName;
	CString	stProductVersion;
	CString	stDllVersion;
	CString	stFileOS;
	CString	stFileType;
	CString stLanguageId;
	CString stCharSet;
	VS_FIXEDFILEINFO vsFixedFileInfo;
	struct TRANSLATE 
	{
		WORD languageId;
		WORD characterSet;
	} Translation;
}VERSION_INFORMATION, *LPVERSION_INFORMATION;

class CVersionApp : public CWinApp  
{
public:		
	CString GetAppProductVersion();
	CString GetAppProductName();
	CString GetAppInternalName();
	CString GetAppDescription();
	CString GetAppCompany();
	CString GetAppWriteDate();
	CString GetAppLastAccessDate();
	CString GetAppOriginalname();
	CString GetAppCopyright();
	CString GetAppFilepath();
	CString GetAppBuildDate();	
	CString GetAppVersion();


	virtual BOOL InitInstance();
	CVersionApp();
	virtual ~CVersionApp();

protected:
	BOOL ReadFileTime();
	BOOL GetFixedFileInfo();
	BOOL GetDynamicInfo(BYTE* pVersionInfo);
	BOOL ReadResourceInformation();
	VERSION_INFORMATION m_VersionInfo;
	FILETIME m_CreationTime,m_LastAccessTime,m_LastWriteTime;
};

#endif // !defined(AFX_VERSIONAPP_H__910C010B_5EC2_11D3_9EB9_0000E87CD125__INCLUDED_)
