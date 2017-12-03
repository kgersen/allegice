// GetNumDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AGM.h"
#include "GetNumDlg.h"


// CGetNumDlg dialog

IMPLEMENT_DYNAMIC(CGetNumDlg, CDialog)
CGetNumDlg::CGetNumDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetNumDlg::IDD, pParent)
{
	caption = "INIT IT PLEASE";
	value = 0;
}

CGetNumDlg::~CGetNumDlg()
{
}

void CGetNumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CAPTION, caption);
	DDX_Text(pDX, IDC_NUMBER, value);
}


BEGIN_MESSAGE_MAP(CGetNumDlg, CDialog)
END_MESSAGE_MAP()


// CGetNumDlg message handlers
