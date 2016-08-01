// ContainerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCActiveXContainerDlg.h"
#include "ContainerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContainerDlg dialog


CContainerDlg::CContainerDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CContainerDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CContainerDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void CContainerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CContainerDlg)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CContainerDlg, CDialog)
    //{{AFX_MSG_MAP(CContainerDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContainerDlg message handlers

BOOL CContainerDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // make sure dialog comes in front of the sequence editor
    SetForegroundWindow();
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
