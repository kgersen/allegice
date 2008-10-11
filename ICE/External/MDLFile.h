/*
	MDLFile.h - Allegiance mdl files API header

	Copyright (C) Kirth Gersen, 2001-2002.  All rights reserved.
	v 0.95
*/
#pragma once
#define MDLCOOKIE 0xDEBADF00

typedef struct SMDLL2
{
	CString name;
	long value;
} MDLL2;

#define MDLHEADERSIZE (2*2+4*4)
typedef struct SMDLHeader
{
	short s1;
	short s2;
	long nb_tags;
	long l2;
	long l3;
	long l4;
	CString TagsNames[250];
	MDLL2 L2Vals[250];
	CString l3names[250];
} MDLHeader;

typedef  char* MDLString;

typedef struct SMLDLight //size = 12 float
{
	float red;
	float green;
	float blue;
	float speed; // or time factor
	float posx;
	float posy;
	float posz;
	float todo1; // 1.25 (0 = crash !)
	float todo2; // 0
	float todo3; // 0.1
	float todo4; // 0
	float todo5; // 0.05
} MDLLight;


typedef struct SMDLFrameData // size = name + 9 float
{
	CString name;
	float posx;
	float posy;
	float posz;
	float nx;
	float ny;
	float nz;
	float px;
	float py;
	float pz;
} MDLFrameData;

typedef struct SMDLVertice
{
	float x;
	float y;
	float z;
	float mx;
	float my;
	float nx; 
	float ny;
	float nz;
} MDLVertice;

typedef struct SMDLMesh
{
	long nvertex;
	long nfaces;
	MDLVertice *vertices;
	WORD *faces;
} MDLMesh;


// kg update:
class WinPoint {
public:
	LONG x;
	LONG y;
};

class BinarySurfaceInfo {
public:
    WinPoint m_size;
    int      m_pitch;
    DWORD    m_bitCount;
    DWORD    m_redMask;
    DWORD    m_greenMask;
    DWORD    m_blueMask;
    DWORD    m_alphaMask;
    bool     m_bColorKey;
};

#define MDLImageInitSize 20

typedef struct SMDLImage
{
	BinarySurfaceInfo header;
	//long w;
	//long h;
	//long bw;
	//long bh;
	//BYTE undecoded[MDLImageInitSize];// 00 F8 00 00 E0 07 00 00 1F 00 00 00 00 00 00 00 00 CC CC CC
	BYTE *bitmap;
} MDLImage;
//const BYTE MDLImageInit[MDLImageInitSize] = {0x00,0xF8,0x00,0x00,0xE0,0x07,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xCC,0xCC};


enum MDLType {mdl_empty,mdl_mesh,mdl_group,mdl_lod,mdl_image};

typedef struct SMDLObject
{
	MDLType type;
	int nchildren;
	struct SMDLObject **childrens;
	MDLMesh *mesh;
    float *lodval;
	int textidx;
	MDLImage *image;
} MDLObject;
typedef MDLObject *PtrMDLObject;

class CMDLFile
{
public:
	CMDLFile(void);
	~CMDLFile(void);
	bool ReadFromFile(CString sFileName);
	bool SaveToXFile(CString sFileName);
	bool SaveToBMP(CString fname);
	bool FromBMP(CString fname, CString bname);
	int NumLights;
	MDLLight *Lights;
	int NumFrameDatas;
	MDLFrameData *FrameDatas;
	MDLObject *RootObject;
	CString ReadError;
	int NumTextures;
	CString *Textures;
	float *FrameVal;
	MDLObject *NewMDLObject(void);
	MDLLight NewMDLLight(int r,int g,int b,int s);
protected:
	CString ParseString(CFile *pcf);
	void DumpMesh(CStdioFile *,MDLMesh *);
	CString CMDLFile::DumpObject(PtrMDLObject,int);
	void ObjectToXFile(PtrMDLObject po,CStdioFile *cf, CString level);
	void SaveString(CFile *pcf,CString s);
	void SaveTag(CFile *pcf,long tag);
	void SaveObject(MDLObject *po,CFile *pcf, int GroupPos, int MeshPos, int TextPos, int TextGeoPos);

private:
	long stack[200];
	int stackpos;

public:
	// save to .mdl binary format
	bool SaveToFile(CString sPath);
};
#define MAX(x,y) ((x)>(y)?(x):(y))
#define Upper4(x) (((x)/4)*4+4)