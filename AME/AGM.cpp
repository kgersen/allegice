// AGM.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"
#include "AGM.h"
#include <corestruct.h>
#include "MAPDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CAGMApp

BEGIN_MESSAGE_MAP(CAGMApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CAGMApp construction

CAGMApp::CAGMApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CAGMApp object

CAGMApp theApp;


// CAGMApp initialization

BOOL CAGMApp::InitInstance()
{
	srand( (unsigned)time( NULL ) );
	CWinApp::InitInstance();

	//if (!AfxSocketInit())
	//{
	//	AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
	//	return FALSE;
	//}

	AfxEnableControlContainer();

//---------------------------------
	char pdata[255]; // main alleg folder
	DWORD psize = 255;
	char adata[255]; // artwork folder
	DWORD asize = 255;

	char cdata[255]; // lastest core 
	DWORD csize = 255;

	LONG regres,regresa,regresc;
	HKEY hKey;

	// read the parameters in the registry
	regres = RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Microsoft Games\\Allegiance\\1.0",0, KEY_READ, &hKey);
	if (regres != ERROR_SUCCESS)
	{
		regres = RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Microsoft Games\\Allegiance\\1.4", 0, KEY_READ, &hKey);
		if (regres != ERROR_SUCCESS)
		{
			AfxMessageBox(_T("Allegiance not found in registry !!!"));
			return FALSE;
		}
	}
	regres  = RegQueryValueEx(hKey,"EXE Path",NULL,NULL,(LPBYTE)pdata,&psize);
	regresa = RegQueryValueEx(hKey,"ArtPath",NULL,NULL,(LPBYTE)adata,&asize);
	regresc = RegQueryValueEx(hKey,"AMECore",NULL,NULL,(LPBYTE)cdata,&csize);
	RegCloseKey(hKey);

	if (regres != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("Allegiance folder not found in registry !!!"));
		return FALSE;
	}
	//------------------------------------
	CoInitialize(NULL);
	CMAPDlg dlg;
	dlg.cArtPath = pdata;
	dlg.sCorename =  "static_core.igc";

	if (regresa != ERROR_SUCCESS)
		dlg.cArtPath += "\\Artwork";
	else
		dlg.cArtPath = adata;
	if (regresc ==  ERROR_SUCCESS)
		dlg.sCorename = cdata;

	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();

	if (nResponse == IDOK)
	{
		//
	}
	else if (nResponse == IDCANCEL)
	{
		//
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	CoUninitialize();
	return FALSE;
}


