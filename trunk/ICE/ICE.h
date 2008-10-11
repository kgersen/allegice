// ICE.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "BMPMDLButton.h"

#define MAXCIVS 50
#define MAXPATHS 6
const CString sPathsNames[MAXPATHS] = {
"Construction",
"Garrison",
"Supremacy",
"Tactical",
"Expansion",
"Shipyard"};
const CString sPathsBmpNames[MAXPATHS] = {
"btndrones",
"btnStarbase",
"btnOrdnance",
"btnElectronics",
"btnResearch",
"btnShipyard"};
#define tBits(x) ((x)&128?1:0),((x)&64?1:0),((x)&32?1:0),((x)&16?1:0),((x)&8?1:0),((x)&4?1:0),((x)&2?1:0),((x)&1?1:0)
// CICEApp:
// See ICE.cpp for the implementation of this class
//

class CICEApp : public CWinApp
{
public:
	CICEApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

class IMainUI
{
public:
	virtual void SelectPCE(LPARAM p) = 0;
	virtual HICON GetJumpIcon() = 0;
};