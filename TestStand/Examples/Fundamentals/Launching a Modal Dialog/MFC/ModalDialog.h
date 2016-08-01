// ModalDialog.h : main header file for the MODALDIALOG DLL
//

#if !defined(AFX_MODALDIALOG_H__30CCAAB0_B878_4B19_BE8E_1F228B922AFE__INCLUDED_)
#define AFX_MODALDIALOG_H__30CCAAB0_B878_4B19_BE8E_1F228B922AFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CModalDialogApp
// See ModalDialog.cpp for the implementation of this class
//

class CModalDialogApp : public CWinApp
{
public:
    CModalDialogApp();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CModalDialogApp)
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CModalDialogApp)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODALDIALOG_H__30CCAAB0_B878_4B19_BE8E_1F228B922AFE__INCLUDED_)
