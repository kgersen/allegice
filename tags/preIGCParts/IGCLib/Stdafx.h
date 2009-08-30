// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once


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
#include "Alleg\vector.h"
#include "Alleg\mask.h"
#include "Alleg\constants.h"
#include "Alleg\igc_types.h"
#include "Alleg\igc_static.h"
