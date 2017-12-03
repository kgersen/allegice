// RocksLayoutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AGM.h"
#include "RocksLayoutDlg.h"


// CRocksLayoutDlg dialog

IMPLEMENT_DYNAMIC(CRocksLayoutDlg, CDialog)
CRocksLayoutDlg::CRocksLayoutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRocksLayoutDlg::IDD, pParent)
{
	cx = cy = cz = 0.0;
	radius = 1000.0;
	varz = 0.0;
	nbrocks = 50;
}

CRocksLayoutDlg::~CRocksLayoutDlg()
{
}

void CRocksLayoutDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Text(pDX, IDC_RADIUS1, radius);

	DDX_Text(pDX, IDC_C1X, cx);
	DDX_Text(pDX, IDC_C1Y, cy);
	DDX_Text(pDX, IDC_C1Z, cz);

	DDX_Text(pDX, IDC_VARZ, varz);
	DDX_Text(pDX, IDC_NBROCKS, nbrocks);

	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRocksLayoutDlg, CDialog)
END_MESSAGE_MAP()


// CRocksLayoutDlg message handlers
