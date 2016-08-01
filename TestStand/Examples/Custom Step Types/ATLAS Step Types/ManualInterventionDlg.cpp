// ManualInterventionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Utils.h"
#include "ManualInterventionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CManualInterventionDlg dialog

CManualInterventionDlg::CManualInterventionDlg(
    const TS::IEnginePtr &engine, 
    CWnd* pParent /*=NULL*/) : 
    CDialog(CManualInterventionDlg::IDD, pParent), 
    m_Engine(engine), 
    m_ManualInterventionHandled(false)
{
    //{{AFX_DATA_INIT(CManualInterventionDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

void CManualInterventionDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CManualInterventionDlg)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CManualInterventionDlg, CDialog)
    //{{AFX_MSG_MAP(CManualInterventionDlg)
    ON_BN_CLICKED(IDC_CONTINUE, OnContinue)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManualInterventionDlg message handlers

void CManualInterventionDlg::InitLabels()
{
    SetWindowText((LPCTSTR)GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("MI_DLG_TITLE")));
    SetDlgItemText(IDC_CONTINUE, (LPCTSTR)GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("CONTINUE_BTN_LABEL")));
    SetDlgItemText(IDC_MI_MESSAGE_STATIC, (LPCTSTR)GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("MI_MESSAGE_STATIC")));
}

BOOL CManualInterventionDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    InitLabels();
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

bool CManualInterventionDlg::Display(
    const TS::ExecutionPtr& execution, 
    const RTSAX::ITpsServerExPtr& tpsServer)
{
    m_ManualInterventionHandled = false;

    for(;;)
    {
        // Check TestStand Execution States
        ExecutionRunStates runState;
        ExecutionTerminationStates termState;
        execution->GetStates(&runState,&termState);

        // If stopped or termination operation occurs, close the dialog and return
        if ((runState == ExecRunState_Stopped) || (termState != ExecTermState_Normal))
        {
            m_ManualInterventionHandled = true;
            break;
        }

        // check to see if manual intervention is still enabled
        // not sure if this is necessary, but just making sure
        VARIANT_BOOL MiEnabled;
        HRESULT hr = tpsServer->get_MiEnabled(&MiEnabled);
        THROW_IF_FAILED(hr);
        if (MiEnabled == VARIANT_FALSE)
            break;

        MSG message;
        if (::PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            ::TranslateMessage(&message);
            ::DispatchMessage(&message);
        }

        // by clicking on the Continue button
        if (m_ManualInterventionHandled)
            break;
    }

    DestroyWindow();

    return m_ManualInterventionHandled;
}

void CManualInterventionDlg::OnContinue() 
{
    m_ManualInterventionHandled = true; // handled in Display()
}
