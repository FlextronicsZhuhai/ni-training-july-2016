// TclEditStep.h : main header file for the TclEditStep DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTclEditStepApp
// See TclEditStep.cpp for the implementation of this class
//

class CTclEditStepApp : public CWinApp
{
public:
	CTclEditStepApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
