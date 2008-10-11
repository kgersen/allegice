// MDLView.cpp : implementation file
//

#include "stdafx.h"
#include "ICE.h"
#include "corestruct.h"
#include "BMPMDLButton.h"
#include "MDLView.h"

// CMDLView dialog

IMPLEMENT_DYNAMIC(CMDLView, CDialog)
CMDLView::CMDLView(CWnd* pParent /*=NULL*/)
	: CDialog(CMDLView::IDD, pParent)
{
	sArtPath = "";
	sModel = "";
	rawdata = NULL;
}

CMDLView::~CMDLView()
{
	if (rawdata)
		delete rawdata;
}

void CMDLView::DoDataExchange(CDataExchange* pDX)
{
	CString todo1;
	ASSERT(sArtPath != "");
	if (!rawdata) return;
	if (!pDX->m_bSaveAndValidate) // data to dialog
	{
		todo1.Format("%08x - ",0);
		for (UINT i=0;i<rawsize;i++)
		{
			todo1.AppendFormat("%02X ",rawdata[i]);
			if (!((i+1)%16)) todo1.AppendFormat("\r\n%08x - ",i+1);
		}
	}
	DDX_Text(pDX, IDC_TODO1, todo1);
	if (pDX->m_bSaveAndValidate) // dialog to data
	{
	}
	CDialog::DoDataExchange(pDX);
}

BOOL CMDLView::OnInitDialog(void)
{
	CDialog::OnInitDialog();
	VERIFY(mdlbmp.SubclassDlgItem(IDC_PICT, this));
	mdlbmp.LoadMDLFile(sArtPath+"\\"+sModel+"bmp.mdl");

	CFile fMDL;
	CString sMDL = sArtPath+"\\"+sModel+".mdl";
	if (!fMDL.Open(sMDL,CFile::modeRead))
	{
		CString res;
		res.Format("Cant read MDL file %s",sMDL);
		AfxMessageBox(res);
	}
	else
	{
		rawsize = fMDL.GetLength();
		rawdata = new UCHAR[rawsize];
		fMDL.Read(rawdata,rawsize);
		fMDL.Close();
		UpdateData(FALSE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BEGIN_MESSAGE_MAP(CMDLView, CDialog)
	ON_BN_CLICKED(IDC_DECODEH, OnBnClickedDecodeh)
	ON_BN_CLICKED(IDC_DECODESEL, OnBnClickedDecodesel)
END_MESSAGE_MAP()


// CMDLView message handlers

void CMDLView::OnBnClickedDecodeh()
{
	CEdit *cetodo = (CEdit *) CWnd::GetDlgItem(IDC_TODO1);
	int i,j;
	cetodo->GetSel(i,j);

	// NT SPECIFIC
   HLOCAL h = cetodo->GetHandle();
   LPCTSTR lpszText = (LPCTSTR)LocalLock(h);
	char res[1000];
	strncpy(res,&(lpszText[i]),j-i);
	SetDlgItemText(IDC_DECDEC,res);
	unsigned short f;
	unsigned char *pf;
	unsigned int b1,b2;
	pf = (unsigned char *)&f;
	sscanf(res,"%x %x",&b1,&b2);
	pf[0] = b1;
	pf[1] = b2;
	CString sres;
	sres.Format("%04X = %d",f,f);
	SetDlgItemText(IDC_DECFLOAT,sres);
	
   LocalUnlock(h);
	// END OF NT SPECIFIC
}

void CMDLView::OnBnClickedDecodesel()
{
	CEdit *cetodo = (CEdit *) CWnd::GetDlgItem(IDC_TODO1);
	int i,j;
	cetodo->GetSel(i,j);

	// NT SPECIFIC
   HLOCAL h = cetodo->GetHandle();
   LPCTSTR lpszText = (LPCTSTR)LocalLock(h);
	char res[1000];
	strncpy(res,&(lpszText[i]),j-i);
	SetDlgItemText(IDC_DECDEC,res);
	float f;
	unsigned char *pf;
	unsigned int b1,b2,b3,b4;
	pf = (unsigned char *)&f;
	sscanf(res,"%x %x %x %x",&b1,&b2,&b3,&b4);
	pf[0] = b1;
	pf[1] = b2;
	pf[2] = b3;
	pf[3] = b4;
	CString sres;
	sres.Format("%g",f);
	SetDlgItemText(IDC_DECFLOAT,sres);
	
   LocalUnlock(h);
	// END OF NT SPECIFIC
}
