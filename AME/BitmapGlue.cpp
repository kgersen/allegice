/*
	BitmapGlue.c - Allegiance mdl bitmap glue - freeimage implementation

	requires freeimage includes & link time lib (http://www.6ixsoft.com/)
	Copyright (C) Kirth Gersen, 2001-2002.  All rights reserved.
	v 0.94
*/
#include "stdafx.h"
#include <freeimage.h>

// save a bmp file in 24 bits format
void CreateBMP24File(CString pszFile, PBITMAPINFO pbi,LPBYTE lpBits) 
 { 
    HANDLE hf;                 // file handle 
    BITMAPFILEHEADER hdr;       // bitmap file-header 
    PBITMAPINFOHEADER pbih;     // bitmap info-header 
    DWORD dwTotal;              // total count of bytes 
    DWORD cb;                   // incremental count of bytes 
    BYTE *hp;                   // byte pointer 
    DWORD dwTmp; 

    pbih = (PBITMAPINFOHEADER) pbi; 

    if (!lpBits) 
		return; 

    // Create the .BMP file. 
    hf = CreateFile(pszFile, 
                   GENERIC_READ | GENERIC_WRITE, 
                   (DWORD) 0, 
                    NULL, 
                   CREATE_ALWAYS, 
                   FILE_ATTRIBUTE_NORMAL, 
                   (HANDLE) NULL); 
    if (hf == INVALID_HANDLE_VALUE) 
		return; 

    hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M" 
    // Compute the size of the entire file. 
    hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + pbih->biSize + pbih->biSizeImage); 
    hdr.bfReserved1 = 0; 
    hdr.bfReserved2 = 0; 

    // Compute the offset to the array of color indices. 
    hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER)+pbih->biSize; 

    // Copy the BITMAPFILEHEADER into the .BMP file. 
    if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), 
        (LPDWORD) &dwTmp,  NULL)) 
    {
		//;
    }

    // Copy the BITMAPINFOHEADER and RGBQUAD array into the file. 
    if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER), (LPDWORD) &dwTmp, ( NULL))) 
		printf("error: CreateBMPFile - WriteFile - step2"); 

    // Copy the array of color indices into the .BMP file. 
    dwTotal = cb = pbih->biSizeImage; 
    hp = lpBits; 
    if (!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL)) 
		printf("error: CreateBMPFile - WriteFile - step3"); 

    // Close the .BMP file. 
     if (!CloseHandle(hf)) 
		printf("error: CreateBMPFile - CloseHandle"); 

}

// read a BMP file and convert it to 565 alleg format
// params:
//	pszFile = bmp file
// result:
//  return pointer to bitmap data, null if error
//  return bitmap dims in rw & rh
WORD *ReadBMP(CString pszFile, long *rw, long *rh)
{
	FIBITMAP *dib = NULL;

	dib = FreeImage_Load(FIF_BMP,pszFile,BMP_DEFAULT);
	if (dib != NULL) 
	{
		FIBITMAP *dib16 = FreeImage_ConvertTo16Bits565(dib); 
		FreeImage_Unload(dib);

		*rw = FreeImage_GetWidth(dib16);
		*rh = FreeImage_GetHeight(dib16);
		long w = *rw;
		long h = *rh;

		WORD *lp16Bits = new WORD[w*h];
		WORD *lpBits = (WORD *)FreeImage_GetBits(dib16);
		for (int y=0;y<h;y++)
			for (int x=0;x<w;x++)
			{
				int p16s = y*w+x;
				int p16d = ((h-1-y)*w+x);
				lp16Bits[p16d] = lpBits[p16s];
			}
		FreeImage_Unload(dib16);
		return lp16Bits;
	}
	else
	return NULL;
}
BYTE* ConvertFromRawBits(
    int outbpp, HANDLE **pout,
	BYTE *bits, int width, int height, int pitch, unsigned bpp, unsigned red_mask, unsigned green_mask, unsigned blue_mask, BOOL topdown

)
{
	*pout = NULL;
	if (outbpp == bpp) return bits;

	FIBITMAP *dib = FreeImage_ConvertFromRawBits(bits,width,height,pitch,bpp,red_mask,green_mask,blue_mask,topdown);
	FIBITMAP *outdib = NULL;
	if (dib)
	{
		if (outbpp==32)
			 outdib = FreeImage_ConvertTo32Bits(dib);
		if (outbpp==16)
			 outdib = FreeImage_ConvertTo16Bits565(dib);
		FreeImage_Unload(dib);
	}
	if (outdib)
	{
		*pout = (HANDLE *)outdib;
		return FreeImage_GetBits(outdib);
	}
	return NULL;
}
void FreeConvertedRawBits(HANDLE *pout)
{
	if (pout) FreeImage_GetBits((FIBITMAP *)pout);
}
