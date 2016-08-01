// TclEditStep.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "TclEditStep.h"
#include "TclEditDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CTclEditStepApp, CWinApp)
END_MESSAGE_MAP()


// CTclEditStepApp construction

CTclEditStepApp::CTclEditStepApp()
{
}


// The one and only CTclEditStepApp object

CTclEditStepApp theApp;


// CTclEditStepApp initialization

BOOL CTclEditStepApp::InitInstance()
{
	CWinApp::InitInstance();
	AfxEnableControlContainer();
	return TRUE;
}

void __declspec(dllexport) DisplayDialog(SequenceContext * context)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CTclEditDialog dialog(context);
	dialog.DoModal();
}
