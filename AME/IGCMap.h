#include <afxtempl.h>
#include <corestruct.h>
#include "mapstruct.h"

#pragma once
#include "RockTpl.h"

enum IGCObjType {igcAleph,igcBase,igcRock};

class CIGCObject // abstract class, (3 pure virtual)
{
public:
	virtual CPoint GetPos2D() = 0;
	virtual void SetPos2D(CPoint) = 0;
	virtual void ApplyPos3D(float,float,float) = 0;
	virtual IGCObjType GetType() = 0;
	virtual float GetX() = 0;
	virtual float GetY() = 0;
	virtual float GetZ() = 0;
	virtual void SetZ(float) = 0;
	void DispMenu(CPoint,CWnd * pParent);
	CIGCObject(void);
	~CIGCObject(void);
	virtual int DispProps(CWnd * pParent,PtrCore, CString) = 0;
	int DistanceToCenter(float,float);
};

class CIGCBase : public CIGCObject
{
public:
	SIGCBase igcbase;
	CPoint GetPos2D();
	void SetPos2D(CPoint);
	void ApplyPos3D(float,float,float);
	IGCObjType GetType();
	float GetX();
	float GetY();
	float GetZ();
	void SetZ(float);
	int DispProps(CWnd * pParent,PtrCore,CString);
	CPoint pos2D;
private:
	static const IGCObjType type = igcBase;
public:
	CIGCBase(void);
	~CIGCBase(void);
};
class CIGCAleph : public CIGCObject
{
public:
	SIGCAleph igcaleph;
	CPoint GetPos2D();
	void SetPos2D(CPoint);
	void ApplyPos3D(float,float,float);
	IGCObjType GetType();
	float GetX();
	float GetY();
	float GetZ();
	void SetZ(float);
	int DispProps(CWnd * pParent,PtrCore, CString);
	CPoint pos2D;
private:
	static const IGCObjType type = igcAleph;
public:
	CIGCAleph(void);
	~CIGCAleph(void);
	void OrientTo(void);
	BOOL bAutoOrient;
	BOOL bNoSpin;
	BOOL bIncludeSpin;
	void AutoAuto(void);
	void RandomPosition(float);
	void RandomPosition(float,float,float);
	void StdRandomPosition();
	void ApplyTemplate(CIGCAleph * tplaleph,bool);
	void CloneFrom(CIGCAleph * tplaleph);
	// KG 8/6/06 added fixed position
	BOOL bFixedPosition;
};

class CIGCRock : public CIGCObject
{
public:
	SIGCRock igcrock;
	CPoint GetPos2D();
	void SetPos2D(CPoint);
	void ApplyPos3D(float,float,float);
	IGCObjType GetType();
	float GetX();
	float GetY();
	float GetZ();
	void SetZ(float);
	int DispProps(CWnd * pParent,PtrCore, CString);
	CPoint pos2D;
private:
	static const IGCObjType type = igcRock;
public:
	CIGCRock(void);
	CIGCRock(int tpl,unsigned short uid,CRockTpl *);
	~CIGCRock(void);
	void FixSpin(void);
	void RandomSpin(void);
	void RandomOrientation(void);
	void RandomPosition(void);
	void SetAutoName(bool);
	void ApplyTemplate(CRockTpl *);
};

class CIGCSector
{
public:
	SIGCSector igcsector;
	CPoint pos2D;
	int lbindex;
public:
	CIGCSector(void);
	void RandomizeAlephs(CList <CIGCAleph,CIGCAleph&> *);
	void RandomizeAlephs(CList <CIGCAleph,CIGCAleph&> *,int,int,int,float,float,bool,bool);
	void ApplyTemplate(CIGCSector *,bool);
	~CIGCSector(void);
};

//overload ==

int operator==(const CIGCSector,const CIGCSector);
int operator!=(const CIGCSector,const CIGCSector);
int operator==(const CIGCAleph,const CIGCAleph);
int operator!=(const CIGCAleph,const CIGCAleph);
int operator==(const CIGCBase,const CIGCBase);
int operator!=(const CIGCBase,const CIGCBase);
int operator==(const CIGCRock,const CIGCRock);
int operator!=(const CIGCRock,const CIGCRock);

typedef struct SSectorInfos
{
	float he3;
	float he3max;
	int nbHelium;
	int nbAsteriod;
	int nbUranium;
	int nbSilicon;
	int nbCarbon;
} SectorInfos;

typedef CIGCSector *PtrSector;
typedef CIGCAleph *PtrAleph;
typedef CIGCBase *PtrBase;
typedef CIGCRock *PtrRock;
typedef CIGCObject *PtrObject;

class CIGCMap
{
public:
	CString name;
	CList <CIGCSector,CIGCSector&> cl_sectors;
	CList <CIGCBase,CIGCBase&> cl_bases;
	CList <CIGCAleph,CIGCAleph&> cl_alephs;
	CList <CIGCRock,CIGCRock&> cl_rocks;
public:
	CIGCMap(void);
	~CIGCMap(void);
	PtrCore pcore;
	BOOL CIGCMap::SaveToFile(CString);
	BOOL ReadFromFile(CString);
	CString DumpSectors(void);
	CString DumpRocks(void);
	CString CheckValidity(void);
	PtrSector FindSector(unsigned short);
	PtrAleph FindConnectingAleph(PtrAleph);
	void RandomizeAlephs(void);
	void RandomizeAlephs(float r);
	void RandomizeAlephs(float r1,float r2,float z);
	void RandomizeAlephs(int p1,int p2,int p3,float p4,float p5, bool, bool);
	void RenameAlephs(CIGCSector *psect);
	int RenameSectors(CString);

protected:
	void FixUIDs(void);
};

