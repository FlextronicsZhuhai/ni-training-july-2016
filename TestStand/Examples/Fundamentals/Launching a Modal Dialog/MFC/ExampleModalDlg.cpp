// ExampleModalDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ModalDialog.h"
#include "ExampleModalDlg.h"

#include "tsapivc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern "C"
{

void __declspec(dllexport) __stdcall ShowModalMfcDlg(TS::SequenceContext *seqContext)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    TS::IEnginePtr engine = seqContext->GetEngine();
    VARIANT_BOOL shouldAbort;

    long modalId = engine->NotifyStartOfModalDialogEx(seqContext, &shouldAbort);
    if(!shouldAbort)
    {
        CExampleModalDlg dlg(CWnd::FromHandle((HWND)modalId));

        dlg.DoModal();
    }

    engine->NotifyEndOfModalDialog(modalId);

}

}

/////////////////////////////////////////////////////////////////////////////
// CExampleModalDlg dialog


CExampleModalDlg::CExampleModalDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CExampleModalDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CExampleModalDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void CExampleModalDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CExampleModalDlg)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExampleModalDlg, CDialog)
    //{{AFX_MSG_MAP(CExampleModalDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExampleModalDlg message handlers

void CExampleModalDlg::OnOK() 
{
    // NOTE: Add extra validation here
    
    CDialog::OnOK();
}
