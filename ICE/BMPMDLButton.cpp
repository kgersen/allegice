// BMPMDLButton.cpp : implementation file
//

#include "stdafx.h"
//#include "ICE.h"
#include "..\AMT\BitmapGlue.h"
#include "BMPMDLButton.h"
#include "..\AMT\MDLFile.h"

// CBMPMDLButton

IMPLEMENT_DYNAMIC(CBMPMDLButton, CBitmapButton)
CBMPMDLButton::CBMPMDLButton()
{
}

CBMPMDLButton::~CBMPMDLButton()
{
}

void CBMPMDLButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	if (m_bitmap.m_hObject == NULL)
	{
		CBrush br(RGB(0xFF,0,0));
		pDC->FillRect(&lpDrawItemStruct->rcItem, &br);
		pDC->TextOut(10,10,"NO BITMAP");
	}
	else
		CBitmapButton::DrawItem(lpDrawItemStruct);

}

void CBMPMDLButton::LoadMDLFile(CString sMDLPath)
{
	if (m_bitmap.m_hObject != NULL)
	{
		m_bitmap.DeleteObject();
	}
	CMDLFile mdlfile;
	if (!mdlfile.ReadFromFile(sMDLPath))
	{
		CString res;
		res.Format("Cant read file %s",sMDLPath);
		//AfxMessageBox(res);
		return;
	}

	if (!mdlfile.RootObject)
	{
		CString res;
		res.Format("error invalid type, file %s",sMDLPath);
		AfxMessageBox(res);
		return;
	}
	if (mdlfile.RootObject->type != mdl_image)
	{
		CString res;
		res.Format("error invalid type, file %s",sMDLPath);
		AfxMessageBox(res);
		return;
	}
	else
	{
		int width = mdlfile.RootObject->image->header.m_size.x; //bw/2;
		int height = mdlfile.RootObject->image->header.m_size.y; //y;
		CDC *myDC = GetDC();
		int screenbpp = myDC->GetDeviceCaps(BITSPIXEL);
		ReleaseDC(myDC);
		HANDLE *pout = NULL;
		BYTE * bits = ConvertFromRawBits(
				screenbpp, &pout,
				mdlfile.RootObject->image->bitmap,
				width,height,
				mdlfile.RootObject->image->header.m_pitch,
				mdlfile.RootObject->image->header.m_bitCount,
				mdlfile.RootObject->image->header.m_redMask, mdlfile.RootObject->image->header.m_greenMask, mdlfile.RootObject->image->header.m_blueMask,
				TRUE);
		if (!m_bitmap.CreateBitmap(width,height,1,screenbpp,bits))
		{
			CString res;
			res.Format("error loading MDL image file '%s'",sMDLPath);
			AfxMessageBox(res);
		}
		FreeConvertedRawBits(pout);
		/*
		CRect rect,rectp;
		GetParent()->GetWindowRect(&rectp);
		GetWindowRect(&rect);
		*/
		//rect.SetRect(rect.left,rect.top,rect.left+width,rect.top+height);
		//rect.NormalizeRect();
		//MoveWindow(rectp.left-rect.left,rectp.top-rect.top,width,height,FALSE);
		//CString res;
		//res.Format("L=%d,T=%d,R=%d,B=%d",rect.left,rect.top,rect.right,rect.bottom);
		//AfxMessageBox(res);
	}
}


BEGIN_MESSAGE_MAP(CBMPMDLButton, CBitmapButton)
END_MESSAGE_MAP()



// CBMPMDLButton message handlers

/* old version
void CBMPMDLButton::LoadMDLFile(CString sMDLPath)
{
	CFile fMDL;
	if (m_bitmap.m_hObject != NULL)
	{
		m_bitmap.DeleteObject();
	}
	if (!fMDL.Open(sMDLPath,CFile::modeRead))
	{
		CString res;
		res.Format("Cant read BMP.MDF file %s",sMDLPath);
		//AfxMessageBox(res);
		return;
	}
	bool bCont = true;
	int cc = 0;
	while (bCont)
	{
		BYTE c;
		bCont = (fMDL.Read(&c,1) == 1);
		if (c == 0xCC) cc++;
		else cc=0;
		if (cc == 3) bCont = false;
	}
	if (cc !=3)
	{
		CString res;
		res.Format("invalid BMP.MDF file %s",sMDLPath);
		AfxMessageBox(res);
	}
	else
	{
		ULONGLONG iCCPos = fMDL.Seek(0,CFile::current);
		int width,height;

		fMDL.Seek(iCCPos - 36,CFile::begin);
		fMDL.Read(&width,sizeof(width));
		fMDL.Read(&height,sizeof(height));
		int lBmpScanWidth;

		fMDL.Read(&lBmpScanWidth,sizeof(lBmpScanWidth));

		int clBmpWidth = lBmpScanWidth / 2;
		int clBmpHeight = height;
		//CString res;
		//res.Format("W=%d,H=%d,SW=%d,bmpsize=%d",width,height,lBmpScanWidth,clBmpWidth * clBmpHeight * 2);
		//AfxMessageBox(res);

		BYTE *lpBits = new BYTE[clBmpWidth * clBmpHeight * 2];
		fMDL.Seek(iCCPos,CFile::begin);
		fMDL.Read(lpBits,clBmpWidth * clBmpHeight * 2);
		m_bitmap.CreateBitmap(width,height,1,16,lpBits);
		delete lpBits;
		CRect rect,rectp;
		GetParent()->GetWindowRect(&rectp);
		GetWindowRect(&rect);
		//rect.SetRect(rect.left,rect.top,rect.left+width,rect.top+height);
		//rect.NormalizeRect();
		//MoveWindow(rectp.left-rect.left,rectp.top-rect.top,width,height,FALSE);
		//CString res;
		//res.Format("L=%d,T=%d,R=%d,B=%d",rect.left,rect.top,rect.right,rect.bottom);
		//AfxMessageBox(res);
	}
	fMDL.Close();
}
*/