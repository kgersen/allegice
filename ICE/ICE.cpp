// ICE.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ICE.h"
#include "corestruct.h"
#include "CivDlg.h"
#include "ChaffDlg.h"
#include "DevelDlg.h"
#include "DroneDlg.h"
#include "MineDlg.h"
#include "MissileDlg.h"
#include "PartDlg.h"
#include "ProbeDlg.h"
#include "ProjectileDlg.h"
#include "ShipDlg.h"
#include "StationDlg.h"
#include "ConstantsDlg.h"
#include "TreasureDlg.h"
#include "ICEDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CICEApp

BEGIN_MESSAGE_MAP(CICEApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CICEApp construction

CICEApp::CICEApp()
{
	// Place all significant initialization in InitInstance
}


// The one and only CICEApp object

CICEApp theApp;


// CICEApp initialization

BOOL CICEApp::InitInstance()
{
	CVersionApp::InitInstance();
//---------------------------------
	char pdata[255];
	DWORD psize = 255;
	LONG regres;
	HKEY hKey;

	// read the parameters in the registry - try 1.4 (steam) then 1.2 (regular)
 	regres = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Microsoft Games\\Allegiance\\1.4", 0, KEY_READ, &hKey);
	if (regres != ERROR_SUCCESS)
		regres = RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Microsoft Games\\Allegiance\\1.2",0, KEY_READ, &hKey);
	if (regres != ERROR_SUCCESS)
		regres = RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Microsoft Games\\Allegiance\\1.4", 0, KEY_READ, &hKey);

	if (regres != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("Allegiance is not installed !!!"));
		return FALSE;
	}

	regres = RegQueryValueEx(hKey,"ArtPath",NULL,NULL,(LPBYTE)pdata,&psize);
	RegCloseKey(hKey);

	// create igpp based on the registry
	if (regres != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("Allegiance ArtPath key not found in registry !!!"));
		return FALSE;
	}
//------------------------------------

	CICEDlg dlg;
	dlg.sTitle = GetAppDescription() + " " + GetAppVersion()+ " " + GetAppInternalName();
	dlg.sVersion = GetAppProductName() + " " + GetAppVersion() + " " + GetAppInternalName();
	dlg.cArtPath = pdata;
	//dlg.cArtPath = dlg.cArtPath + "\\artwork";
	m_pMainWnd = &dlg;

	dlg.iBackIcon = LoadIcon(IDI_ICONBACK);
	dlg.iJumpIcon = LoadIcon(IDI_ICONFWD);

	if (m_lpCmdLine[0] != _T('\0'))
	{
      // Open a file passed as the first command line parameter.
      dlg.sCoreArg = m_lpCmdLine;
	  dlg.sCoreArg.Trim("\"");
	}
  

	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.

	return FALSE;
}
