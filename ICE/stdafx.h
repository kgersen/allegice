// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

#define WINVER 0x0601  
#define _WIN32_WINNT 0x0601  

#include <SDKDDKVer.h>

//// Modify the following defines if you have to target a platform prior to the ones specified below.
//#ifndef WINVER				// Allow use of features specific to Win 2K or later
//#define WINVER 0x0502
//#endif
//
//#ifndef _WIN32_WINNT		// Allow use of features specific to Win 2K or later
//#define _WIN32_WINNT 0x0502
//#endif
//
//#ifndef _WIN32_WINDOWS		// Allow use of features specific to Win 98 or later
//#define _WIN32_WINDOWS 0x0410
//#endif
//
//#ifndef _WIN32_IE			// Allow use of features specific to IE 5.01 or later
//#define _WIN32_IE 0x0502
//#endif

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

// Include database headers.  For a DLL or app which just includes database
// headers (no database view), conditionally include DAO and ODBC.
// If an actual view is used, always & only include the corresponding header.
// First, actual view is used:


#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// memery leaks tracking
#ifdef true
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include <math.h>
#include <string.h>
#include <stdio.h>
// change these to whatever you need
#define assert(exp)
#define ZError(psz) 

// these should be defined if you use DirectX otherwise they'll be defined here
#ifndef DWORD
typedef unsigned long       DWORD;
#endif
#ifndef BYTE
typedef unsigned char BYTE;
#endif
#ifndef D3DCOLOR_DEFINED
typedef DWORD D3DCOLOR;
#define D3DCOLOR_DEFINED
#endif

#ifndef D3DCOLORVALUE_DEFINED
typedef struct _D3DCOLORVALUE {
    float r;
    float g;
    float b;
    float a;
} D3DCOLORVALUE;
#define D3DCOLORVALUE_DEFINED
#endif

// Allegiance Source includes
// adjust paths 
// TODO: reference current alleg source files instead of these copies but requires to split igc.h into 3 files
#include "IGCLib\Alleg\vector.h"
#include "IGCLib\Alleg\mask.h"
#include "IGCLib\Alleg\constants.h"
#include "IGCLib\Alleg\igc_types.h"
#include "IGCLib\Alleg\igc_static.h"

#ifdef _DEBUG
// simple debug fucntion
void debugf(const char* format, ...);
#else
#define debugf(x)
#endif