/*
	MDLFile.cpp - Allegiance mdl files API 

	Copyright (C) Kirth Gersen, 2001-2002.  All rights reserved.
	v 0.96
*/
#include "StdAfx.h"
#include "mdlfile.h"
#include "BitmapGlue.h"

// constructor - init all vars to NULL/0
CMDLFile::CMDLFile(void)
{
	NumLights = 0;
	Lights = NULL;
	NumFrameDatas = 0;
	FrameDatas = NULL;
	RootObject = NULL;
	FrameVal = NULL;
	NumTextures = 0;
	Textures = NULL;
}

// destructor, free all the dyn allocated
CMDLFile::~CMDLFile(void)
{
	if (RootObject)
	{
		if (RootObject->image)
		{
			delete RootObject->image->bitmap;
			delete RootObject->image;
		}
		delete RootObject->lodval;
		if (RootObject->mesh)
		{
			delete RootObject->mesh->vertices;
			delete RootObject->mesh->faces;
			delete RootObject->mesh;
		}
		for  (int n=0;n<RootObject->nchildren;n++)
		{
			delete RootObject->childrens[n];
		}
		delete RootObject;
	}
	delete Lights;
	//	delete FrameDatas;
	// delete Textures;
}

// contruct a pre-initialized MDLObject
MDLObject *CMDLFile::NewMDLObject(void)
{
	MDLObject *o = new MDLObject;
	o->nchildren = 0;
	o->childrens = NULL;
	o->lodval = 0;
	o->type = mdl_empty;
	o->textidx = -1;
	o->mesh = NULL;
	o->image = NULL;
	return o;
}
// contruct a MDLLight from the params
MDLLight CMDLFile::NewMDLLight(int r,int g,int b,int s)
{
	MDLLight lite;
	lite.red = r/256.0f;
	lite.green = g/256.0f;
	lite.blue = b/256.0f;
	lite.speed = s/256.0f; // or time factor
	lite.todo1 = 1.25f;
	lite.todo2 = 0;
	lite.todo3 = 0.1f;
	lite.todo4 = 0;
	lite.todo5 = 0.05f;
	return lite;
}

// MDL File Parser
#define ParseVal(f,v) f.Read(&(v),(sizeof(v)))
bool CMDLFile::ReadFromFile(CString sFileName)
{
	CFile cf;
	if (!cf.Open(sFileName,CFile::modeRead))
	{
		ReadError = "cant open file";
		return false;
	}
	ULONG cookie;
	cf.Read(&cookie,4);
	CString sf = cf.GetFileName();
	if (cookie != MDLCOOKIE)
	{
		ReadError = "bad header";
		cf.Close();
		return false;
	}
	MDLHeader header;
	cf.Read(&header,MDLHEADERSIZE);
	NumTextures = 0;
	for (int i=0;i<header.nb_tags;i++)
	{
		CString tag = ParseString(&cf);
		header.TagsNames[i] = tag;
		if ((tag != "model") && (tag != "effect"))
			NumTextures++;
	}
	int idx = 0;
	int *TexturesIdx = new int[NumTextures];
	if (NumTextures)
	{
		Textures = new CString[NumTextures];
		for (int i=0;i<header.nb_tags;i++)
		{
			CString tag = header.TagsNames[i];
			if ((tag != "model") && (tag != "effect"))
			{
				Textures[idx] = tag;
				TexturesIdx[idx] = i;
				idx++;
			}
		}
	}
	ASSERT(idx==NumTextures);
	for (int i=0;i<header.l2;i++)
	{
		long uk1;
		cf.Read(&uk1,sizeof(uk1));
		CString tag = ParseString(&cf);
		header.L2Vals[i].name = tag;
		header.L2Vals[i].value = uk1;
	}
	for (int i=0;i<header.l3;i++)
	{
		CString tag = ParseString(&cf);
		header.l3names[i] = tag;
	}
	// LOOP LEVEL 3
	int lastText = -1;
	MDLObject *lastObject = NULL;
	MDLObject *stackedObjects[500];
	int sopos = -1;
	for (int L3=0;L3<header.l3;L3++)
	{
		long l3val;
		cf.Read(&l3val,sizeof(l3val));
		
		bool cont = true;
		stackpos = -1;
		// LOOL LEVEL 2
		while (cont)
		{
			long token;
			cf.Read(&token,sizeof(token));
			switch(token)
			{
			case 5:
				{
					// start of group
					// push # val
					long nentry;
					ParseVal(cf,nentry);
					stack[++stackpos] = nentry;
					break;
				}
			case 9:
				{
					long l2idx;
					cf.Read(&l2idx,sizeof(l2idx));
					if ((l2idx<0) || (l2idx>header.l2))
					{
						ReadError.Format("unmatched l2idx = %s",l2idx);
						cont = false;
						break;
					}
					else
					{
						CString l2type = header.L2Vals[l2idx].name;
						bool matched = false;
						if (l2type == "MeshGeo")
						{
							matched = true;
							long datatype;
							cf.Read(&datatype,sizeof(datatype));
							if (datatype != 7)
							{
								cont = false;
								break;
							}
							MDLMesh *mesh = new(MDLMesh);
							cf.Read(&(mesh->nvertex),sizeof(long));
							cf.Read(&(mesh->nfaces),sizeof(long));
							mesh->vertices = new MDLVertice[mesh->nvertex];
							for (int n=0;n<mesh->nvertex;n++)
							{
								// read vertice
								MDLVertice vert;
								ParseVal(cf,vert.x);
								ParseVal(cf,vert.y);
								ParseVal(cf,vert.z);
								ParseVal(cf,vert.mx);
								ParseVal(cf,vert.my);
								ParseVal(cf,vert.nx);
								ParseVal(cf,vert.ny);
								ParseVal(cf,vert.nz);
								mesh->vertices[n] = vert;
							}
							mesh->faces = new WORD[mesh->nfaces];
							for (int n=0;n<mesh->nfaces;n++)
							{
								WORD f;
								ParseVal(cf,f);
								mesh->faces[n] = f;
							}
							lastObject = NewMDLObject();
							stackedObjects[++sopos] = lastObject;
							lastObject->mesh = mesh;
							lastObject->type = mdl_mesh;
						}
						if (l2type == "ModifiableNumber")
						{
							long six;
							ParseVal(cf,six);
							matched = true;
						}
						if (l2type == "LightsGeo")
						{
							matched = true;
							long datatype;
							cf.Read(&datatype,sizeof(datatype));
							if (datatype != 7)
							{
								ReadError.Format("bad data %d in LightsGeo",datatype);
								cont = false;
								break;
							}
							if (NumLights != 0)
							{
								ReadError.Format("double ligths!!!");
								cont = false;
								break;
							}
							long nlite;
							ParseVal(cf,nlite);
							NumLights = nlite;
							Lights = new MDLLight[nlite];
							for (int n=0;n<nlite;n++)
							{
								MDLLight lite;
								ParseVal(cf,lite);
								Lights[n] = lite;
							}
						}
						if (l2type == "FrameData")
						{
							matched = true;
							long datatype;
							cf.Read(&datatype,sizeof(datatype));
							if (datatype != 7)
							{
								ReadError.Format("bad data %d in FrameData",datatype);
								cont = false;
								break;
							}
							if (NumFrameDatas != 0)
							{
								ReadError.Format("double framedata!!!");
								cont = false;
								break;
							}
							long ndata;
							ParseVal(cf,ndata);
							NumFrameDatas = ndata;
							FrameDatas = new MDLFrameData[ndata];
							for (int n=0;n<ndata;n++)
							{
								MDLFrameData data;
								data.name = ParseString(&cf);
								cf.Read(&(data.posx),sizeof(MDLFrameData)-4);
								FrameDatas[n] = data;
							}
						}
						if (l2type == "TextureGeo")
						{
							matched = true;
							long six;
							ParseVal(cf,six);
							ASSERT(lastObject != NULL);
							lastObject->textidx = lastText;
						}
						if (l2type == "LODGeo")
						{
							matched = true;
							long six;
							ParseVal(cf,six);
							lastObject = NewMDLObject();
							lastObject->type = mdl_lod;
							lastObject->nchildren = stack[stackpos]+1;
							lastObject->childrens = new PtrMDLObject[lastObject->nchildren];
							for (int n=0;n<lastObject->nchildren;n++)
							{
								lastObject->childrens[n] = stackedObjects[sopos--];
							}
							stackedObjects[++sopos] = lastObject;
							stackpos--;
						}
						if (l2type == "GroupGeo")
						{
							matched = true;
							long six;
							ParseVal(cf,six);
							lastObject = NewMDLObject();
							lastObject->type = mdl_group;
							lastObject->nchildren = stack[stackpos];
							lastObject->childrens = new PtrMDLObject[lastObject->nchildren];
							for (int n=0;n<lastObject->nchildren;n++)
							{
								lastObject->childrens[n] = stackedObjects[sopos--];
							}
							stackedObjects[++sopos] = lastObject;
							stackpos--;
						}
						if (l2type == "time")
						{
							matched = true;
							ReadError.Format("!!time!!"),
							cont = false;
							break;
						}
						if (l2type == "ImportImage")
						{
							matched = true;
							cont = false;
							long datatype;
							cf.Read(&datatype,sizeof(datatype));
							if (datatype != 7)
							{
								ReadError.Format("bad data %d in ImportImage",datatype);
								cont = false;
								break;
							}
							MDLImage *img = new MDLImage;
							cf.Read(&(img->header),sizeof(BinarySurfaceInfo));
							//cf.Read(&(img->w),sizeof(long)); // width 
							//cf.Read(&(img->h),sizeof(long)); // height
							//cf.Read(&(img->bw),sizeof(long)); // scanwidth = width * 2 (rounded to upper long) = pitch
							//cf.Read(&(img->bh),sizeof(long)); // bits per pixel
							//cf.Read(img->undecoded,sizeof(img->undecoded)); // unknonwn
							//UINT nbits = img->bw*img->h*img->bh/16;
							int size = (int)(cf.GetLength()-cf.GetPosition());
							BYTE *lpBits = new BYTE[size];
							cf.Read(lpBits,size);
							img->bitmap = lpBits;
							lastObject = NewMDLObject();
							stackedObjects[++sopos] = lastObject;
							lastObject->image = img;
							lastObject->type = mdl_image;
							break;
						}
						if (!matched)
						{
							for (int n=0;n<header.nb_tags;n++)
								if (l2type == header.TagsNames[n])
								{
									matched = true;
									lastText = -1;
									for (int p=0;p<NumTextures;p++)
									{
										if (TexturesIdx[p] == header.L2Vals[l2idx].value)
											lastText = p;
									}
									ASSERT(lastText != -1);
								}	
						}
						if (!matched)
						{
							ReadError.Format("unmatched l2type = %s\n",l2type);
							cont = false;
							break;
						}
					}
					break;
				}
			case 1:
				{
					float *val = new float;
					cf.Read(val,sizeof(*val));
					if (header.l3names[L3] == "frame")
					{
						FrameVal = val;
					}
					else
					{
						ASSERT(lastObject != NULL);
						lastObject->lodval = val;
					}
					break;
				}
			case 10:
				{
					// handle 10
					break;
				}
			case 0:
				{
					if (stackpos>=0)
					{//stack[stackpos] -=1;
					}
					else
						cont = false;
					break;
				}
			default:
				ReadError.Format("unknow token = %d\n",token);
				cont = false;
				break;
			} // switch
		} // while(cont)
	} // L3
	RootObject = lastObject;
	cf.Close();
	return true;
}

// debug purpose - dump to text 
CString CMDLFile::DumpObject(PtrMDLObject po, int level)
{
	if(!po) return "";
	CString fmt;
	CString hd = "";
	for (int n=0;n<level;n++) hd.AppendFormat("\t");
	fmt = hd;

	if(po->lodval)
		fmt.AppendFormat("[%f]",*(po->lodval));
	if(po->type == mdl_mesh)
	{
		fmt.AppendFormat("MESH: %d,%d",po->mesh->nvertex,po->mesh->nfaces);
		if(po->textidx != -1)
			fmt.AppendFormat(" - Texture = %d",po->textidx);
	}
	else
	{
		if(po->type == mdl_group)
			fmt.AppendFormat("Group[%d](\n",po->nchildren);
		else
			fmt.AppendFormat("LOD[%d](\n",po->nchildren);
		for(int n=0;n<po->nchildren;n++)
		{
			CString child = DumpObject(po->childrens[n],level+1);
			child.AppendFormat(",\n");
			fmt.AppendFormat("%s%s",hd,child);
		}
		fmt.AppendFormat("%s)\n",hd);
	}
	return fmt;
}

// MDL to X file tentative
void CMDLFile::ObjectToXFile(PtrMDLObject po,CStdioFile *cf,CString level)
{
	if(!po) return ;
	if(po->type == mdl_mesh)
	{
		// po->mesh->nvertex,po->mesh->nfaces)
		CString fmt;
		fmt.Format("Frame %s\n{",level);
		cf->WriteString(fmt);
		fmt.Format("  Mesh %s_mesh {\n",level);
		cf->WriteString(fmt);
		fmt.Format("    %d;\n",po->mesh->nvertex);
		cf->WriteString(fmt);
		for (int n=0;n<po->mesh->nvertex;n++)
		{
			fmt.Format("    %f;%f;%f; // %f %f %f",
				po->mesh->vertices[n].x,
				po->mesh->vertices[n].y,
				po->mesh->vertices[n].z,
				po->mesh->vertices[n].nx,
				po->mesh->vertices[n].ny,
				po->mesh->vertices[n].nz
				);
			if (n != (po->mesh->nvertex-1))
				fmt.AppendFormat(",\n");
			else
				fmt.AppendFormat(";\n");
			cf->WriteString(fmt);
		}
		fmt.Format("    %d;\n",po->mesh->nfaces/3);
		cf->WriteString(fmt);
		for (int n=0;n<po->mesh->nfaces;n+=3)
		{
			fmt.Format("    3;%d,%d,%d;",
				po->mesh->faces[n],
				po->mesh->faces[n+2],
				po->mesh->faces[n+1]
				);
			if (n < (po->mesh->nfaces-3))
				fmt.AppendFormat(",\n");
			else
				fmt.AppendFormat(";\n");
			cf->WriteString(fmt);
		}
		// normals here plz

		if(po->textidx != -1)
		{
			cf->WriteString("    MeshTextureCoords    {\n");
			fmt.Format("      %d;\n",po->mesh->nvertex);
			cf->WriteString(fmt);
			for (int n=0;n<po->mesh->nvertex;n++)
			{
				fmt.Format("      %f;%f;",
					po->mesh->vertices[n].mx,
					po->mesh->vertices[n].my
					);
				if (n != (po->mesh->nvertex-1))
					fmt.AppendFormat(",\n");
				else
					fmt.AppendFormat(";\n");
				cf->WriteString(fmt);
			}
			cf->WriteString("    }\n");
			cf->WriteString("    MeshMaterialList      {\n");
			cf->WriteString("    1;\n");
			fmt.Format(     "    %d;\n",po->mesh->nfaces/3);
			cf->WriteString(fmt);
			for (int n=0;n<po->mesh->nfaces;n+=3)
			{
				cf->WriteString("      0");
				if (n < (po->mesh->nfaces-3))
					cf->WriteString(",\n");
				else
					cf->WriteString(";\n");
			}
			fmt.Format(     "        Material %s\n",Textures[po->textidx]);
            cf->WriteString(fmt);

			cf->WriteString("              {\n");
			cf->WriteString("                0.990000;0.990000;0.990000;1.000000;;\n");
			cf->WriteString("                0.000000;\n");
			cf->WriteString("                0.000000;0.000000;0.000000;;\n");
			cf->WriteString("                0.990000;0.990000;0.990000;;\n");

			cf->WriteString("                TextureFileName\n");
			cf->WriteString("                {\n");
			fmt.Format("                    \"%s\";\n",Textures[po->textidx]+".bmp");
            cf->WriteString(fmt);
			cf->WriteString("                }\n");
			cf->WriteString("              }\n");
			cf->WriteString("        } // MaterialList\n");
		}
		cf->WriteString("  }\n // Mesh\n");
		cf->WriteString("}\n // Frame\n");
	}
	else
	{
		CString rootype = "LOD";
		int maxchild = po->nchildren;
		if(po->type == mdl_group)
		{
			rootype = "GROUP";
			maxchild = po->nchildren;
		}
		for(int n=0;n<po->nchildren;n++)
		{
			CString lev = level;
			lev.AppendFormat("%s-%d",rootype,n);
			ObjectToXFile(po->childrens[n],cf,lev);
		}
		cf->WriteString("//\n");
	}
}

// Whole MDL To XFile tentative
bool CMDLFile::SaveToXFile(CString sFileName)
{
	CStdioFile cf;
	if(!cf.Open(sFileName,CFile::modeCreate|CFile::modeWrite))
		return false;
	cf.WriteString("xof 0303txt 0032\n");
	PtrMDLObject po = RootObject;
	CString fmt;
	fmt.Format("//Dump of %s\n",sFileName);
	cf.WriteString(fmt);
	fmt.Format("//Lights = %d\n",NumLights);
	cf.WriteString(fmt);
	for (int n=0;n<NumLights;n++)
	{
		fmt.Format("//RGB(%f,%f,%f) | %f | (%f,%f,%f) | %f %f %f %f %f\n",
			Lights[n].red,
			Lights[n].green,
			Lights[n].blue,
			Lights[n].speed,
			Lights[n].posx,
			Lights[n].posy,
			Lights[n].posz,
			Lights[n].todo1,
			Lights[n].todo2,
			Lights[n].todo3,
			Lights[n].todo4,
			Lights[n].todo5);
		cf.WriteString(fmt);
	}
	
	fmt.Format("//FrameData = %d\n",NumFrameDatas);
	cf.WriteString(fmt);
	for (int n=0;n<NumFrameDatas;n++)
	{
		fmt.Format("//%s | %f %f %f | %f %f %f %f %f %f\n",
			FrameDatas[n].name,
			FrameDatas[n].posx,
			FrameDatas[n].posy,
			FrameDatas[n].posz,
			FrameDatas[n].nx,
			FrameDatas[n].ny,
			FrameDatas[n].nz,
			FrameDatas[n].px,
			FrameDatas[n].py,
			FrameDatas[n].pz);
		cf.WriteString(fmt);
	}
	if (po)
		//fmt = DumpObject(po,0);
		ObjectToXFile(po,&cf,"Root");
	cf.Close();
	return true;
}

// string parser in MDLFile
CString CMDLFile::ParseString(CFile *pcf)
{
	CString res="";
	char data[5];
	data[4] = 0;
	do
	{
		pcf->Read(data,4);
		res+=data;
	} while (data[3]!=0);
	return res;
}

// one day
void CMDLFile::DumpMesh(CStdioFile *sf, MDLMesh *mesh)
{
}

// warning stupid code below - should use freeimage 565 conversion
bool CMDLFile::SaveToBMP(CString fnbmp)
{
	if (!RootObject) return false;
	if (RootObject->type != mdl_image) return false;
	MDLImage *img = RootObject->image;
	if (!img) return false;
	
	UCHAR *lp24Bits = new UCHAR[img->header.m_size.x*img->header.m_size.y*3];
	WORD *lp16bits = (WORD*)img->bitmap;
	for (int y=0;y<img->header.m_size.y;y++)
		for (int x=0;x<img->header.m_size.x;x++)
		{ 
			// 16 = 5red, 6green, 5blue
			int p16 = y*img->header.m_size.x+x;
			int p24 = ((img->header.m_size.y-1-y)*img->header.m_size.x+x)*3; // inverted lines (start from bottom)
			WORD b16 = lp16bits[p16];
			ULONG	red = b16 & 0xF800;
					red = red>>11;
					red = (red*256)/32;
			ULONG	green = b16 & 0x7E0;
					green = green>>5;
					green = (green*256)/64;
			ULONG	blue = b16 & 0x1F;
					blue = (blue*256)/32;

			lp24Bits[p24] = (UCHAR)blue;
			lp24Bits[p24+1] = (UCHAR)green;
			lp24Bits[p24+2] = (UCHAR)red;
		}
	PBITMAPINFO pbmi;
    pbmi = (PBITMAPINFO) LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER)); 
    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
    pbmi->bmiHeader.biWidth = img->header.m_size.x; 
    pbmi->bmiHeader.biHeight = img->header.m_size.y; 
    pbmi->bmiHeader.biPlanes = 1; 
    pbmi->bmiHeader.biBitCount = 24; 
    pbmi->bmiHeader.biCompression = BI_RGB; 
    pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * 24 +31) & ~31) /8
                                  * pbmi->bmiHeader.biHeight; 
    pbmi->bmiHeader.biClrImportant = 0; 
	
	CreateBMP24File(fnbmp, pbmi, lp24Bits);
	return true;
}
// contruct a MDL from a bmp
// should be an overload of CMDLFile() constructor
bool CMDLFile::FromBMP(CString fname, CString bname)
{
	long w,h;
	WORD *lp16Bits = ReadBMP(fname,&w,&h);
	if (!lp16Bits)
	{
		return false;
	}
	if (RootObject)
		delete RootObject;
	RootObject = NewMDLObject();
	RootObject->type = mdl_image;
	MDLImage *mdlimage = new MDLImage;
	mdlimage->header.m_size.x = w;
	mdlimage->header.m_size.y = h;
	mdlimage->header.m_pitch = 2*w;
	mdlimage->header.m_bitCount = 16;
	mdlimage->bitmap = (BYTE*)lp16Bits;
	// TODO
	//memcpy(mdlimage->undecoded,MDLImageInit,MDLImageInitSize);
	RootObject->image = mdlimage;
	NumTextures = 0;
	Textures = new CString(bname);
	return true;
}

// string write
void CMDLFile::SaveString(CFile *pcf,CString s)
{
	pcf->Write(s,s.GetLength());
	// complete with trailing 0
	char buf = 0;
	int l = s.GetLength();
	l = l / 4;
	l = l * 4;
	l = s.GetLength()-l;
	l=4-l;
	for (int p=0;p<l;p++)
		pcf->Write(&buf,1);
}
// should be a macro
void CMDLFile::SaveTag(CFile *pcf, long tag)
{
	pcf->Write(&tag,sizeof(long));
}

// save to .mdl binary format
bool CMDLFile::SaveToFile(CString sPath)
{
	// Compute header but assume FrameVal is valid (no check)

	if (!RootObject)
		return false;
	// open file
	CFile MDLfile;
	if (!MDLfile.Open(sPath,CFile::modeCreate|CFile::modeWrite))
		return false;

	// compute header
	bool bIsNotImage = (RootObject->type != mdl_image);
	MDLHeader hdr;
	hdr.s1 = 0;
	hdr.s2 = 1;
	hdr.nb_tags = 1; // model + [effect = lights or datas] + [textures]
	hdr.TagsNames[0] = "model";
	int TexturePos = 1;
	if ((NumLights >0) || (NumFrameDatas>0))
	{
		hdr.TagsNames[hdr.nb_tags] = "effect";
		TexturePos = 2;
		hdr.nb_tags++;
	}
	for (int t=0;t<NumTextures;t++)
	{
		hdr.TagsNames[hdr.nb_tags] = Textures[t];
		hdr.nb_tags++;
	}
	// ------------------------------- L2 -----------------------------------
	hdr.l2 = 0;
	if (bIsNotImage)
	{
		hdr.l2 = 1; // ModifiableNumber,LightsGeo, time, FrameData then Texture & Group
		hdr.L2Vals[0].name = "ModifiableNumber";
		hdr.L2Vals[0].value = 0;
	}
	int LightsPos = -1;
	if (NumLights >0)
	{
		hdr.L2Vals[hdr.l2].name = "LightsGeo";
		hdr.L2Vals[hdr.l2].value = 1; //should be idx of "effect" in TagNames
		LightsPos = hdr.l2;
		hdr.l2++;
		hdr.L2Vals[hdr.l2].name = "time";
		hdr.L2Vals[hdr.l2].value = 0; 
		hdr.l2++;
	}
	int FramesPos = -1;
	if (NumFrameDatas >0)
	{
		hdr.L2Vals[hdr.l2].name = "FrameData";
		hdr.L2Vals[hdr.l2].value = 1; //should be idx of "effect" in TagNames
		FramesPos = hdr.l2;
		hdr.l2++;
	}
	int GroupPos = -1;
	if (RootObject->type == mdl_group)
	{
		hdr.L2Vals[hdr.l2].name = "GroupGeo";
		hdr.L2Vals[hdr.l2].value = 0;
		GroupPos = hdr.l2;
		hdr.l2++;
	}
	int MeshPos = -1;
	if (bIsNotImage)
	{
		hdr.L2Vals[hdr.l2].name = "MeshGeo";
		hdr.L2Vals[hdr.l2].value = 0;
		MeshPos = hdr.l2;
		hdr.l2++;
	}
	int TextPos = -1;
	int TextGeoPos = -1;
	for (int t=0;t<NumTextures;t++)
	{
		if (t==0)
		{
			TextGeoPos = hdr.l2;
			hdr.L2Vals[hdr.l2].name = "TextureGeo";
			hdr.L2Vals[hdr.l2].value = 0;
			hdr.l2++;
			TextPos = hdr.l2;
		}
		hdr.L2Vals[hdr.l2].name = hdr.TagsNames[TexturePos+t];
		hdr.L2Vals[hdr.l2].value = TexturePos+t;
		hdr.l2++;
	}
	int ImagePos = -1;
	if (!bIsNotImage)
	{
		ImagePos = hdr.l2;
		hdr.L2Vals[hdr.l2].name = "ImportImage";
		hdr.L2Vals[hdr.l2].value = 0;
		hdr.l2++;
	}
	// ------------------------------- L3 -----------------------------------
	if (bIsNotImage)
	{
		hdr.l3 = 2; // frame,[lights],[frames],object
		hdr.l3names[0] = "frame";
		if (NumLights >0)
		{
			hdr.l3names[hdr.l3-1] = "lights";
			hdr.l3++;
		}
		if (NumFrameDatas >0)
		{
			hdr.l3names[hdr.l3-1] = "frames";
			hdr.l3++;
		}
		hdr.l3names[hdr.l3-1] = "object";
	}
	else // image
	{
		hdr.l3 = 1;
		hdr.l3names[hdr.l3-1] = *Textures;
	}
	// ------------------------------- L4 -----------------------------------
	hdr.l4 = 0;
	// ------------------------------- end of header-------------------------

	// write cookie & fixed size header
	long cookie = MDLCOOKIE;
	MDLfile.Write(&cookie,4);
	MDLfile.Write(&hdr,MDLHEADERSIZE);

	// write TagsNames
	for (int t=0;t<hdr.nb_tags;t++)
	{
		SaveString(&MDLfile,hdr.TagsNames[t]);
	}
	// Write L2 entries
	for (int t=0;t<hdr.l2;t++)
	{
		SaveTag(&MDLfile,hdr.L2Vals[t].value);
		SaveString(&MDLfile,hdr.L2Vals[t].name);
	}

	// Write L3 levels name
	for (int t=0;t<hdr.l3;t++)
	{
		SaveString(&MDLfile,hdr.l3names[t]);
	}

	// write body
	// Main L3 save loop
	for (int t=0;t<hdr.l3;t++)
	{
		SaveTag(&MDLfile,t);
		if (hdr.l3names[t] == "frame")
		{
			SaveTag(&MDLfile,1);
			MDLfile.Write(FrameVal,sizeof(float));
			SaveTag(&MDLfile,9);
			SaveTag(&MDLfile,0);
			SaveTag(&MDLfile,6);
		}
		if (hdr.l3names[t] == "lights")
		{
			SaveTag(&MDLfile,9);
			SaveTag(&MDLfile,LightsPos);
			SaveTag(&MDLfile,7);
			SaveTag(&MDLfile,NumLights);
			for (int l=0;l<NumLights;l++)
			{
				MDLfile.Write(&(Lights[l]),sizeof(MDLLight));
			}
		}
		if (hdr.l3names[t] == "frames")
		{
			SaveTag(&MDLfile,9);
			SaveTag(&MDLfile,FramesPos);
			SaveTag(&MDLfile,7);
			SaveTag(&MDLfile,NumFrameDatas);
			for (int l=0;l<NumFrameDatas;l++)
			{
				SaveString(&MDLfile,FrameDatas[l].name);
				MDLfile.Write(&(FrameDatas[l].posx),sizeof(float));
				MDLfile.Write(&(FrameDatas[l].posy),sizeof(float));
				MDLfile.Write(&(FrameDatas[l].posz),sizeof(float));
				MDLfile.Write(&(FrameDatas[l].nx),sizeof(float));
				MDLfile.Write(&(FrameDatas[l].ny),sizeof(float));
				MDLfile.Write(&(FrameDatas[l].nz),sizeof(float));
				MDLfile.Write(&(FrameDatas[l].px),sizeof(float));
				MDLfile.Write(&(FrameDatas[l].py),sizeof(float));
				MDLfile.Write(&(FrameDatas[l].pz),sizeof(float));
			}
		}
		if (hdr.l3names[t] == "object")
		{
			SaveObject(RootObject,&MDLfile,GroupPos,MeshPos,TextPos,TextGeoPos);
		}
		if (!bIsNotImage)
		{
			SaveTag(&MDLfile,9);
			SaveTag(&MDLfile,ImagePos);
			SaveTag(&MDLfile,7);
			// save the image 
			MDLImage *img = RootObject->image;
			MDLfile.Write(&(img->header),sizeof(BinarySurfaceInfo));
			//MDLfile.Write(&(img->header.m_size.x),sizeof(long)); // width 
			//MDLfile.Write(&(img->header.m_size.y),sizeof(long)); // height
			//MDLfile.Write(&(img->bw),sizeof(long)); // scanwidth = width * 2 (rounded to upper long)
			//MDLfile.Write(&(img->bh),sizeof(long)); // bits per pixel
			//MDLfile.Write(img->undecoded,sizeof(img->undecoded)); // unknonwn
			UINT nbits = img->header.m_pitch *  img->header.m_size.y  *  img->header.m_bitCount/16;
			MDLfile.Write(img->bitmap,nbits);
		}
		SaveTag(&MDLfile,0);
	}
	MDLfile.Close();
	return true;
}

// SaveToFile sub part - save a child object
void CMDLFile::SaveObject(MDLObject *po,CFile *pcf, int GroupPos, int MeshPos, int TextPos, int TextGeoPos)
{
	if (po->type == mdl_group)
	{
		SaveTag(pcf,5);
		SaveTag(pcf,po->nchildren);
		for (int n=0;n<po->nchildren;n++)
		{
			SaveObject(po->childrens[n],pcf,GroupPos,MeshPos,TextPos,TextGeoPos);
			SaveTag(pcf,0);
		}
		SaveTag(pcf,9);
		SaveTag(pcf,GroupPos);
		SaveTag(pcf,6);
	}
	if (po->type == mdl_mesh)
	{
		if (po->textidx != -1)
		{
			SaveTag(pcf,9);
			SaveTag(pcf,TextPos+po->textidx);
		}
		// save mesh
		SaveTag(pcf,9);
		SaveTag(pcf,MeshPos);
		SaveTag(pcf,7);
		SaveTag(pcf,po->mesh->nvertex);
		SaveTag(pcf,po->mesh->nfaces);
		for (int v=0;v<po->mesh->nvertex;v++)
		{
			pcf->Write(&(po->mesh->vertices[v].x),sizeof(float));
			pcf->Write(&(po->mesh->vertices[v].y),sizeof(float));
			pcf->Write(&(po->mesh->vertices[v].z),sizeof(float));
			pcf->Write(&(po->mesh->vertices[v].mx),sizeof(float));
			pcf->Write(&(po->mesh->vertices[v].my),sizeof(float));
			pcf->Write(&(po->mesh->vertices[v].nx),sizeof(float));
			pcf->Write(&(po->mesh->vertices[v].ny),sizeof(float));
			pcf->Write(&(po->mesh->vertices[v].nz),sizeof(float));
		}
		for (int v=0;v<po->mesh->nfaces;v++)
		{
			pcf->Write(&(po->mesh->faces[v]),sizeof(WORD));
		}
		if (po->textidx != -1)
		{
			SaveTag(pcf,9);
			SaveTag(pcf,TextGeoPos);
			SaveTag(pcf,6);
		}
	}
}