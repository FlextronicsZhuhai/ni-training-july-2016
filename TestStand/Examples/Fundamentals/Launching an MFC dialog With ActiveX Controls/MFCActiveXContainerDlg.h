// MFCActiveXContainerDlg.h : main header file for the MFCACTIVEXCONTAINERDLG DLL
//

#if !defined(AFX_MFCACTIVEXCONTAINERDLG_H__0902A567_C27B_11D2_A3EC_006008CA11D4__INCLUDED_)
#define AFX_MFCACTIVEXCONTAINERDLG_H__0902A567_C27B_11D2_A3EC_006008CA11D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCActiveXContainerDlgApp
// See MFCActiveXContainerDlg.cpp for the implementation of this class
//

class CMFCActiveXContainerDlgApp : public CWinApp
{
public:
    CMFCActiveXContainerDlgApp();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMFCActiveXContainerDlgApp)
    public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CMFCActiveXContainerDlgApp)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCACTIVEXCONTAINERDLG_H__0902A567_C27B_11D2_A3EC_006008CA11D4__INCLUDED_)
