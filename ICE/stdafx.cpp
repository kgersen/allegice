// stdafx.cpp : source file that includes just the standard includes
// ICE.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#ifdef _DEBUG
void debugf(const char* format, ...)
{
    const size_t size = 2048; //Avalanche: Changed to handle longer messages (from 512)
    char         bfr[size];

    va_list vl;
    va_start(vl, format);
    _vsnprintf_s(bfr, size, (size-1), format, vl); //Avalanche: Fix off by one error. 
    va_end(vl);

    OutputDebugString(bfr);
}
#endif